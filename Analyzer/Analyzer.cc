//-----------------------------------------------------------------------------
// File:        Analyzer.cc
// Created:     24-Nov-2015
// Author:      Janos Karancsi
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "common/utils.h" // Helper functions
#include "settings.h"         // Define all Analysis specific settings here

using namespace std;

int main(int argc, char** argv) {
  // ------------------------------
  // -- Parse command line stuff --
  // ------------------------------

  // Get file list and histogram filename from command line
  utils::commandLine cmdline;
  utils::decodeCommandLine(argc, argv, cmdline);

  itreestream stream(cmdline.fileNames, settings.treeName);      
  if ( !stream.good() ) utils::error("unable to open ntuple file(s)");                         

  if ( cmdline.isData ) cout << "Running on Data." << endl;
  else cout << "Running on MC." << endl;

  // Get number of events to be read
  int nevents = stream.size();
  cout << "Number of events: " << nevents << endl;

  if (cmdline.quickTest) {
    cout << "quickTest (cmdline): true"<< endl;
    cout << "--> Doing a quick test on 1/100 statitics"<< endl;
    nevents /= 100;
  }

  // Select variables to be read
  DataStruct data;
  settings.selectVariables(stream, data);

  /*
	 Notes:
	
	 1. Use
	   ofile = outputFile(cmdline.outputfile, stream)
	
	 to skim events to output file in addition to writing out histograms.
	
	 2. Use
	   ofile.addEvent(event-weight)
	
	 to specify that the current event is to be added to the output file.
	 If omitted, the event-weight is defaulted to 1.
	
	 3. Use
	    ofile.count(cut-name, event-weight)
	
	 to keep track, in the count histogram, of the number of events
	 passing a given cut. If omitted, the event-weight is taken to be 1.
	 If you want the counts in the count histogram to appear in a given
	 order, specify the order, before entering the event loop, as in
	 the example below
	 
	    ofile.count("NoCuts", 0)
		ofile.count("GoodEvent", 0)
		ofile.count("Vertex", 0)
		ofile.count("MET", 0)
  */

  // Constuct the Analysis (specified in settings.h)
  Analysis ana;

  // ---------------------------------------------------------------------------
  // -- output file                                                           --
  // ---------------------------------------------------------------------------

  utils::outputFile* ofile;
  if ( settings.saveSkimmedNtuple ) {
    cout << "saveSkimmedNtuple (settings): true" << endl;
    ofile = new utils::outputFile(cmdline.outputFileName, stream);
  } else {
    ofile = new utils::outputFile(cmdline.outputFileName);
    cout << "saveSkimmedNtuple (settings): false" << endl;
  }
  TDirectory* out_dir = gDirectory;

  // ---------------------------------------------------------------------------
  // -- Read systematics file                                                 --
  // ---------------------------------------------------------------------------

  // Initialize all systemtics (0 - off)
  struct Systematics {
    double nSigmaPU = 0;
    double nSigmaAlphaS = 0;
    double nSigmaScale  = 0;
    unsigned int numScale = 0;
    unsigned int numPdf = 0;
  } syst;

  if (settings.doSystematics) {
    cout << "doSystematics (settings): true" << endl;

    if ( cmdline.systematicsFileName == "" ) utils::error("doSystematics true, but command line argument systematicsFileName=<filename> was not given");
    cout << "systematicsFileName (cmdline): " << cmdline.numSyst << endl;
    std::ifstream systFile(cmdline.systematicsFileName.c_str());
    if ( !systFile.good() ) utils::error("unable to open systematics file: " + cmdline.systematicsFileName);

    if ( cmdline.numSyst <= 0 ) utils::error("doSystematics true, but command line argument numSyst=<positive integer> was not given");
    cout << "numSyst (cmdline): " << cmdline.numSyst << endl;

    // read nth line
    // error if end of file reached
    std::string line;
    for (int i=1; i<=cmdline.numSyst; ++i) if ( ! std::getline(systFile, line) ) 
      utils::error("systematics file contains less lines than numSyst");
    std::stringstream nth_line;
    nth_line<<line;

    // Assign the systematic sigmas:
    nth_line>>syst.nSigmaPU;
    nth_line>>syst.nSigmaAlphaS;
    nth_line>>syst.nSigmaScale;
    nth_line>>syst.numScale;
    nth_line>>syst.numPdf;
    cout << " nSigmaPU     = " << syst.nSigmaPU << endl;
    cout << " nSigmaAlphaS = " << syst.nSigmaAlphaS << endl;
    cout << " nSigmaScale  = " << syst.nSigmaScale << endl;
    cout << " numScale     = " << syst.numScale << endl;
    cout << " numPdf       = " << syst.numPdf << endl;
  } else {
    cout << "doSystematics (settings): false" << endl;
  }

  // ---------------------------------------------------------------------------
  // -- Declare histograms                                                    --
  // ---------------------------------------------------------------------------

  // Histogram weight
  double w;
  TH1::SetDefaultSumw2();

  // This section is moved and defined in the Analysis class
  // this class specifies what histograms/cuts/methods etc. you want to implement
  // This is useful if someone wants to do quick study/define other search region etc.
  // But also, common methods in all anaylsis are defined in common/AnalysisBase.*

  ana.define_histo_options(w, data, cmdline.dirname, settings.runOnSkim);

  ana.init_common_histos();
  ana.init_analysis_histos();

  // --------------------------------------------------------------
  // -- Calculate the normalization factor for the event weights --
  // -- The original MC weight will be divided by this quantity  --
  // --------------------------------------------------------------

  cout << endl;
  double weightnorm = 1 ;
  if ( !cmdline.isData ) {
    cout << "intLumi (settings): " << settings.intLumi << endl; // given in settings.h

    double xsec = ana.get_xsec_from_ntuple(cmdline.fileNames, settings.treeName); // treename given in settings.h
    if ( xsec==0 ) return 1;
    cout << "xsec (ntuple): " << xsec << endl;

    double totweight = ana.get_totweight_from_ntuple(cmdline.fileNames, settings.totWeightHistoName); // weight histo name given in settings.h
    cout << "totweight (ntuple): " << totweight << endl;

    weightnorm = (xsec*settings.intLumi)/totweight;
    cout << "weightnorm (calc): " << weightnorm << endl;
  }

  // ---------------------------------------
  // --- Pileup Reweighting              ---
  // ---------------------------------------
  
  if ( !cmdline.isData && settings.doPileupReweighting ) {
    cout << "doPileupReweighting (settings): true" << endl;
    ana.init_pileup_reweightin(settings.pileupDir, settings.mcPileupHistoName, cmdline.fileNames);
  } else cout << "doPileupReweighting (settings): false" << endl;

  // ------------------------------------------------------------------------------
  // -- Define the order of cuts (and corresponding bins in the counts histogram --
  // ------------------------------------------------------------------------------

  // Define cuts that are common in all analyses
  // Given in common/AnalysisBase.h
  ana.define_preselections(data);

  // Define cuts that specific to this analysis
  // Given in [Name]_Analysis.h specified in setting.h
  ana.define_selections(data);

  // Define bin order for counts histogram
  ofile->count("NoCuts", 0);
  cout << endl;
  cout << "Number of events counted after applying" << endl;
  cout << "- Baseline cuts (common for all analysis):" << endl;
  for (auto cut : ana.baseline_cuts) {
    ofile->count(cut.name, 0);
    cout << "  "<<cut.name << endl;
  }
  cout << endl;  
  cout << "- Analysis specific cuts:\n";
  for (auto cut : ana.analysis_cuts) {
    ofile->count(cut.name, 0);
    cout << "  "<<cut.name << endl;
  }

  ofile->count("Signal", 0); // Dont worry, we blind data ;)

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

  cout << endl;
  cout << "Start looping on events ..." << endl;
  for(int entry=0; entry < nevents; ++entry) {

    // Read event into memory
    stream.read(entry);

    // Calculate variables that do not exist in ntuple
    ana.calculate_variables(data);

    if ( entry%100000==0 ) cout << entry << " events analyzed." << endl;

    w = 1;
    if ( !cmdline.isData ) {
      // Event weight normalized to luminosity
      w *= data.evt.Gen_Weight*weightnorm;

      // Pileup reweighting
      h_nvtx->Fill(data.evt.NGoodVtx, w);
      if ( settings.doPileupReweighting ) {
	w *= ana.get_pileup_weight(data.evt.pu_NtrueInt, settings.doSystematics, syst.nSigmaPU);
	h_nvtx_rw->Fill(data.evt.NGoodVtx, w);
      }

      if ( settings.doSystematics ) {
	// LHE weight variations
	// More info about them here:
	// https://github.com/jkarancs/B2GTTrees/blob/master/plugins/B2GEdmExtraVarProducer.cc#L165-L237

	// Alpha_s variations
	// A set of two weights
	// Only stored for NLO, otherwise vector size==0
	// If vector was not filled (LO samples), not doing any weighting
	if ( data.evt.alphas_Weights.size() == 2 )
	  w *= ana.get_alphas_weight(data.evt.alphas_Weights, syst.nSigmaAlphaS, data.evt.LHA_PDF_ID);

	// Scale variations
	// A set of six weights, unphysical combinations excluded
	// If numScale=0 is specified, not doing any weighting
	if ( syst.numScale >= 1 && syst.numScale <= 3 )
	  w *= ana.get_scale_weight(data.evt.scale_Weights, syst.nSigmaScale, syst.numScale);

	// PDF weights
	// A set of 100 weights for the nominal PDF
	// If numPdf=0 is specified, not doing any weighting
	if ( syst.numPdf >= 1 && syst.numPdf <= data.evt.pdf_Weights.size() )
	  w *= data.evt.pdf_Weights[syst.numPdf-1];
	else if ( syst.numPdf > data.evt.pdf_Weights.size() )
	  utils::error("numPdf (syst) specified is larger than the number of PDF weights in the ntuple");
      }
    }

    ofile->count("NoCuts", w);

    // Apply preselections and save counts
    bool pass_all = true;
    for (auto cut : ana.baseline_cuts) if (pass_all)
      if ( ( pass_all = cut.func() ) ) ofile->count(cut.name, w);

    // _______________________________________________________
    //                  BLINDING DATA

    // Before doing anything serious (eg. filling any histogram)
    // Define Signal region and blind it!!!!!!!!!!!!!!!!!!!!!!!!
    bool DATA_BLINDED = ! ( cmdline.isData && ana.signal_selection(data) );

    /*
      Some more warning to make sure :)
     _   _   _   ____    _        _____   _   _   _____    _____   _   _    _____   _   _   _ 
    | | | | | | |  _ \  | |      |_   _| | \ | | |  __ \  |_   _| | \ | |  / ____| | | | | | |
    | | | | | | | |_) | | |        | |   |  \| | | |  | |   | |   |  \| | | |  __  | | | | | |
    | | | | | | |  _ <  | |        | |   | . ` | | |  | |   | |   | . ` | | | |_ | | | | | | |
    |_| |_| |_| | |_) | | |____   _| |_  | |\  | | |__| |  _| |_  | |\  | | |__| | |_| |_| |_|
    (_) (_) (_) |____/  |______| |_____| |_| \_| |_____/  |_____| |_| \_|  \_____| (_) (_) (_)

    */

    //________________________________________________________
    //

    if (DATA_BLINDED) {

      // If option (saveSkimmedNtuple) is specified save all 
      // skimmed events selected by the analysis to the output file
      // tree is copied and current weight is saved as "eventWeight"
      if ( settings.saveSkimmedNtuple ) if (ana.pass_skimming(data)) ofile->addEvent(w);

      // Apply analysis cuts and fill histograms
      // These are all defined in [Name]_Analysis.cc (included from settings.h)
      // You specify there also which cut is applied for each histo
      // But all common baseline cuts are alreay applied above
      if ( pass_all ) ana.fill_analysis_histos(data, w);

      // Save counts for the analysis cuts
      for (auto cut : ana.analysis_cuts) if (pass_all)
        if ( ( pass_all = cut.func() ) ) ofile->count(cut.name, w);

      // Count Signal events
      if ( pass_all && ana.signal_selection(data) ) ofile->count("Signal", w);

    } // end Blinding

  } // end event loop

  stream.close();
  out_dir->cd();
  ana.save_analysis_histos();
  ofile->close();
  return 0;
}
