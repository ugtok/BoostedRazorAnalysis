#include "common/DataStruct.h"
#include "common/treestream.h"

#include "Analysis_Changgi.h" // Specify here the implementations for you Analysis

struct settings {

  //-----------------------------------------------------------------------------
  // -- Constants
  //-----------------------------------------------------------------------------
  settings() :
    runOnSkim                ( true  ),
    saveSkimmedNtuple        ( false ),
    doPileupReweighting      ( true  ),
    applyWTagSF              ( false ),
    applyBTagSF              ( false ),
    //applyHadTopTagSF         ( false ),
    scaleQCD                 ( false ),
    doHTReweighting          ( false ),
    varySystematics          ( false ),
    systematicsFileName      ( "systematics/2016_10_31_1SigmaUpDown_NoPdf.txt" ),
    treeName                 ( runOnSkim ? "B2GTree"   : "B2GTTreeMaker/B2GTree" ),
    totWeightHistoName       ( runOnSkim ? "totweight" : "EventCounter/totweight" ), // saved in ntuple
    mcPileupHistoName        ( runOnSkim ? "pileup_mc" : "EventCounter/pileup" ),    // saved in ntuple
    useJSON                  ( false ), // Default is not appliying any JSON, but Golden JSON (tighter selection) can be applied on top of the Default Silver JSON
    jsonFileName             ( "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-280385_13TeV_PromptReco_Collisions16_JSON.txt" ),
    pileupDir                ( "pileup/Oct21_Golden_JSON/" ),
    intLumi                  ( 27655.802 /* brilcalc - Oct21 Golden JSON */ ), // Tot int lumi in (pb^-1),
    lumiUncertainty          ( 0.062 ),
    useXSecFileForBkg        ( true  ), // true: use file below, false: use value in the ntuple (evt_XSec)
    xSecFileName             ( "common/BackGroundXSec.txt" ),
    triggerEffScaleFactor    (  1.00 ),
    triggerEffUncertainty    (  0.01 )
  {
    if (runOnSkim) {
      totWeightHistoNamesSignal.push_back("totweight_T1tttt"); // lsp mass vs gluino mass scan, also used for T5ttcc and T5tttt
      totWeightHistoNamesSignal.push_back("totweight_T2tt");   // T2tt
    } else {
      totWeightHistoNamesSignal.push_back("EventCounter/h_totweight_T1tttt");
      totWeightHistoNamesSignal.push_back("EventCounter/h_totweight_T2tt");
    }
  };
  ~settings(){};

  const bool runOnSkim;
  const bool saveSkimmedNtuple;
  const bool doPileupReweighting;
  const bool applyWTagSF;
  const bool applyBTagSF;
  //const bool applyHadTopTagSF;
  const bool scaleQCD;
  const bool doHTReweighting;
  const bool varySystematics;
  const std::string systematicsFileName;
  const std::string treeName;
  const std::string totWeightHistoName;
  const std::string mcPileupHistoName;
  const bool useJSON;
  const std::string jsonFileName;
  const std::string pileupDir;
  const double intLumi;
  const double lumiUncertainty;
  const bool useXSecFileForBkg;
  const std::string xSecFileName;
  const double triggerEffScaleFactor;
  const double triggerEffUncertainty;
  std::vector<std::string> totWeightHistoNamesSignal;

  //-----------------------------------------------------------------------------
  // -- Declare variables to be read by treestream
  //-----------------------------------------------------------------------------
  // --- Structs can be filled by calling fillObjects()
  // --- after the call to stream.read(...)
  //-----------------------------------------------------------------------------
  // -- Select variables to be read
  //-----------------------------------------------------------------------------

  void selectVariables(itreestream& stream, DataStruct& data) {
    stream.select("evt_RunNumber", data.evt.RunNumber);
    stream.select("evt_LumiBlock", data.evt.LumiBlock);
    stream.select("evt_EventNumber", data.evt.EventNumber);
    //stream.select("evt_NGoodVtx", data.evt.NGoodVtx);
    //stream.select("evt_LHA_PDF_ID", data.evt.LHA_PDF_ID);
    stream.select("evt_MR", data.evt.MR);
    stream.select("evt_MTR", data.evt.MTR);
    stream.select("evt_R", data.evt.R);
    stream.select("evt_R2", data.evt.R2);
    stream.select("evt_AK8_MR", data.evt.AK8_MR);
    stream.select("evt_AK8_MTR", data.evt.AK8_MTR);
    stream.select("evt_AK8_R", data.evt.AK8_R);
    stream.select("evt_AK8_R2", data.evt.AK8_R2);
    stream.select("evt_XSec", data.evt.XSec);
    stream.select("evt_Gen_Weight", data.evt.Gen_Weight);
    stream.select("evt_Gen_Ht", data.evt.Gen_Ht);
    stream.select("SUSY_Stop_Mass", data.evt.SUSY_Stop_Mass);
    stream.select("SUSY_Gluino_Mass", data.evt.SUSY_Gluino_Mass);
    stream.select("SUSY_LSP_Mass", data.evt.SUSY_LSP_Mass);
    
    stream.select("met_size", data.met.size);
    stream.select("met_Pt", data.met.Pt);
    stream.select("met_Phi", data.met.Phi);
    
    stream.select("pu_NtrueInt", data.pu.NtrueInt);
    
    stream.select("scale_size", data.syst_scale.size);
    stream.select("scale_Weights", data.syst_scale.Weights);
    
    stream.select("pdf_size", data.syst_pdf.size);
    stream.select("pdf_Weights", data.syst_pdf.Weights);
    
    stream.select("alphas_size", data.syst_alphas.size);
    stream.select("alphas_Weights", data.syst_alphas.Weights);
    
    stream.select("Flag_BadPFMuonFilter", data.filter.BadPFMuonFilter);
    stream.select("Flag_BadChargedCandidateFilter", data.filter.BadChargedCandidateFilter);
    stream.select("Flag_HBHENoiseFilter", data.filter.HBHENoiseFilter);
    stream.select("Flag_HBHENoiseIsoFilter", data.filter.HBHENoiseIsoFilter);
    stream.select("Flag_CSCTightHaloFilter", data.filter.CSCTightHaloFilter);
    stream.select("Flag_CSCTightHaloTrkMuUnvetoFilter", data.filter.CSCTightHaloTrkMuUnvetoFilter);
    stream.select("Flag_CSCTightHalo2015Filter", data.filter.CSCTightHalo2015Filter);
    stream.select("Flag_globalTightHalo2016Filter", data.filter.globalTightHalo2016Filter);
    stream.select("Flag_globalSuperTightHalo2016Filter", data.filter.globalSuperTightHalo2016Filter);
    stream.select("Flag_HcalStripHaloFilter", data.filter.HcalStripHaloFilter);
    stream.select("Flag_hcalLaserEventFilter", data.filter.hcalLaserEventFilter);
    stream.select("Flag_EcalDeadCellTriggerPrimitiveFilter", data.filter.EcalDeadCellTriggerPrimitiveFilter);
    stream.select("Flag_EcalDeadCellBoundaryEnergyFilter", data.filter.EcalDeadCellBoundaryEnergyFilter);
    stream.select("Flag_goodVertices", data.filter.goodVertices);
    stream.select("Flag_eeBadScFilter", data.filter.eeBadScFilter);
    stream.select("Flag_ecalLaserCorrFilter", data.filter.ecalLaserCorrFilter);
    stream.select("Flag_trkPOGFilters", data.filter.trkPOGFilters);
    stream.select("Flag_chargedHadronTrackResolutionFilter", data.filter.chargedHadronTrackResolutionFilter);
    stream.select("Flag_muonBadTrackFilter", data.filter.muonBadTrackFilter);
    stream.select("Flag_trkPOG_manystripclus53X", data.filter.trkPOG_manystripclus53X);
    stream.select("Flag_trkPOG_toomanystripclus53X", data.filter.trkPOG_toomanystripclus53X);
    stream.select("Flag_trkPOG_logErrorTooManyClusters", data.filter.trkPOG_logErrorTooManyClusters);
    stream.select("Flag_METFilters", data.filter.METFilters);
    
    stream.select("HLT_PFJet200", data.hlt.PFJet200);
    stream.select("HLT_PFJet200_prescale", data.hlt.PFJet200_prescale);
    stream.select("HLT_PFJet260", data.hlt.PFJet260);
    stream.select("HLT_PFJet260_prescale", data.hlt.PFJet260_prescale);
    stream.select("HLT_PFJet320", data.hlt.PFJet320);
    stream.select("HLT_PFJet320_prescale", data.hlt.PFJet320_prescale);
    stream.select("HLT_PFJet400", data.hlt.PFJet400);
    stream.select("HLT_PFJet400_prescale", data.hlt.PFJet400_prescale);
    stream.select("HLT_PFJet450", data.hlt.PFJet450);
    stream.select("HLT_PFJet450_prescale", data.hlt.PFJet450_prescale);
    stream.select("HLT_PFJet500", data.hlt.PFJet500);
    stream.select("HLT_PFJet500_prescale", data.hlt.PFJet500_prescale);
    stream.select("HLT_AK8PFJet360_TrimMass30", data.hlt.AK8PFJet360_TrimMass30);
    stream.select("HLT_AK8PFJet360_TrimMass30_prescale", data.hlt.AK8PFJet360_TrimMass30_prescale);
    stream.select("HLT_AK8PFJet40", data.hlt.AK8PFJet40);
    stream.select("HLT_AK8PFJet40_prescale", data.hlt.AK8PFJet40_prescale);
    stream.select("HLT_AK8PFJet60", data.hlt.AK8PFJet60);
    stream.select("HLT_AK8PFJet60_prescale", data.hlt.AK8PFJet60_prescale);
    stream.select("HLT_AK8PFJet80", data.hlt.AK8PFJet80);
    stream.select("HLT_AK8PFJet80_prescale", data.hlt.AK8PFJet80_prescale);
    stream.select("HLT_AK8PFJet140", data.hlt.AK8PFJet140);
    stream.select("HLT_AK8PFJet140_prescale", data.hlt.AK8PFJet140_prescale);
    stream.select("HLT_AK8PFJet200", data.hlt.AK8PFJet200);
    stream.select("HLT_AK8PFJet200_prescale", data.hlt.AK8PFJet200_prescale);
    stream.select("HLT_AK8PFJet260", data.hlt.AK8PFJet260);
    stream.select("HLT_AK8PFJet260_prescale", data.hlt.AK8PFJet260_prescale);
    stream.select("HLT_AK8PFJet320", data.hlt.AK8PFJet320);
    stream.select("HLT_AK8PFJet320_prescale", data.hlt.AK8PFJet320_prescale);
    stream.select("HLT_AK8PFJet400", data.hlt.AK8PFJet400);
    stream.select("HLT_AK8PFJet400_prescale", data.hlt.AK8PFJet400_prescale);
    stream.select("HLT_AK8PFJet450", data.hlt.AK8PFJet450);
    stream.select("HLT_AK8PFJet450_prescale", data.hlt.AK8PFJet450_prescale);
    stream.select("HLT_AK8PFJet500", data.hlt.AK8PFJet500);
    stream.select("HLT_AK8PFJet500_prescale", data.hlt.AK8PFJet500_prescale);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30", data.hlt.AK8DiPFJet250_200_TrimMass30);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30_prescale", data.hlt.AK8DiPFJet250_200_TrimMass30_prescale);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30", data.hlt.AK8DiPFJet280_200_TrimMass30);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30_prescale", data.hlt.AK8DiPFJet280_200_TrimMass30_prescale);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20", data.hlt.AK8DiPFJet250_200_TrimMass30_BTagCSV_p20);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_prescale", data.hlt.AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_prescale);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20", data.hlt.AK8DiPFJet280_200_TrimMass30_BTagCSV_p20);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_prescale", data.hlt.AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_prescale);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV0p45", data.hlt.AK8DiPFJet250_200_TrimMass30_BTagCSV0p45);
    stream.select("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV0p45_prescale", data.hlt.AK8DiPFJet250_200_TrimMass30_BTagCSV0p45_prescale);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p45", data.hlt.AK8DiPFJet280_200_TrimMass30_BTagCSV0p45);
    stream.select("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p45_prescale", data.hlt.AK8DiPFJet280_200_TrimMass30_BTagCSV0p45_prescale);
    stream.select("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v2", data.hlt.AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v2);
    stream.select("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v2_prescale", data.hlt.AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v2_prescale);
    stream.select("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45", data.hlt.AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45);
    stream.select("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45_prescale", data.hlt.AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45_prescale);
    stream.select("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50", data.hlt.AK8PFHT650_TrimR0p1PT0p03Mass50);
    stream.select("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_prescale", data.hlt.AK8PFHT650_TrimR0p1PT0p03Mass50_prescale);
    stream.select("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50", data.hlt.AK8PFHT700_TrimR0p1PT0p03Mass50);
    stream.select("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_prescale", data.hlt.AK8PFHT700_TrimR0p1PT0p03Mass50_prescale);
    stream.select("HLT_PFHT550_4JetPt50", data.hlt.PFHT550_4JetPt50);
    stream.select("HLT_PFHT550_4JetPt50_prescale", data.hlt.PFHT550_4JetPt50_prescale);
    stream.select("HLT_PFHT650_4JetPt50", data.hlt.PFHT650_4JetPt50);
    stream.select("HLT_PFHT650_4JetPt50_prescale", data.hlt.PFHT650_4JetPt50_prescale);
    stream.select("HLT_PFHT750_4JetPt50", data.hlt.PFHT750_4JetPt50);
    stream.select("HLT_PFHT750_4JetPt50_prescale", data.hlt.PFHT750_4JetPt50_prescale);
    stream.select("HLT_ECALHT800", data.hlt.ECALHT800);
    stream.select("HLT_ECALHT800_prescale", data.hlt.ECALHT800_prescale);
    stream.select("HLT_PFHT200", data.hlt.PFHT200);
    stream.select("HLT_PFHT200_prescale", data.hlt.PFHT200_prescale);
    stream.select("HLT_PFHT250", data.hlt.PFHT250);
    stream.select("HLT_PFHT250_prescale", data.hlt.PFHT250_prescale);
    stream.select("HLT_PFHT300", data.hlt.PFHT300);
    stream.select("HLT_PFHT300_prescale", data.hlt.PFHT300_prescale);
    stream.select("HLT_PFHT350", data.hlt.PFHT350);
    stream.select("HLT_PFHT350_prescale", data.hlt.PFHT350_prescale);
    stream.select("HLT_PFHT400", data.hlt.PFHT400);
    stream.select("HLT_PFHT400_prescale", data.hlt.PFHT400_prescale);
    stream.select("HLT_PFHT475", data.hlt.PFHT475);
    stream.select("HLT_PFHT475_prescale", data.hlt.PFHT475_prescale);
    stream.select("HLT_PFHT600", data.hlt.PFHT600);
    stream.select("HLT_PFHT600_prescale", data.hlt.PFHT600_prescale);
    stream.select("HLT_PFHT650", data.hlt.PFHT650);
    stream.select("HLT_PFHT650_prescale", data.hlt.PFHT650_prescale);
    stream.select("HLT_PFHT800", data.hlt.PFHT800);
    stream.select("HLT_PFHT800_prescale", data.hlt.PFHT800_prescale);
    stream.select("HLT_PFHT900", data.hlt.PFHT900);
    stream.select("HLT_PFHT900_prescale", data.hlt.PFHT900_prescale);
    stream.select("HLT_MET200", data.hlt.MET200);
    stream.select("HLT_MET200_prescale", data.hlt.MET200_prescale);
    stream.select("HLT_MET250", data.hlt.MET250);
    stream.select("HLT_MET250_prescale", data.hlt.MET250_prescale);
    stream.select("HLT_MET300", data.hlt.MET300);
    stream.select("HLT_MET300_prescale", data.hlt.MET300_prescale);
    stream.select("HLT_MET600", data.hlt.MET600);
    stream.select("HLT_MET600_prescale", data.hlt.MET600_prescale);
    stream.select("HLT_MET700", data.hlt.MET700);
    stream.select("HLT_MET700_prescale", data.hlt.MET700_prescale);
    stream.select("HLT_PFMET300", data.hlt.PFMET300);
    stream.select("HLT_PFMET300_prescale", data.hlt.PFMET300_prescale);
    stream.select("HLT_PFMET400", data.hlt.PFMET400);
    stream.select("HLT_PFMET400_prescale", data.hlt.PFMET400_prescale);
    stream.select("HLT_PFMET500", data.hlt.PFMET500);
    stream.select("HLT_PFMET500_prescale", data.hlt.PFMET500_prescale);
    stream.select("HLT_PFMET600", data.hlt.PFMET600);
    stream.select("HLT_PFMET600_prescale", data.hlt.PFMET600_prescale);
    stream.select("HLT_PFHT300_PFMET100", data.hlt.PFHT300_PFMET100);
    stream.select("HLT_PFHT300_PFMET100_prescale", data.hlt.PFHT300_PFMET100_prescale);
    stream.select("HLT_PFHT300_PFMET110", data.hlt.PFHT300_PFMET110);
    stream.select("HLT_PFHT300_PFMET110_prescale", data.hlt.PFHT300_PFMET110_prescale);
    stream.select("HLT_Rsq0p25", data.hlt.Rsq0p25);
    stream.select("HLT_Rsq0p25_prescale", data.hlt.Rsq0p25_prescale);
    stream.select("HLT_Rsq0p30", data.hlt.Rsq0p30);
    stream.select("HLT_Rsq0p30_prescale", data.hlt.Rsq0p30_prescale);
    stream.select("HLT_RsqMR240_Rsq0p09_MR200", data.hlt.RsqMR240_Rsq0p09_MR200);
    stream.select("HLT_RsqMR240_Rsq0p09_MR200_prescale", data.hlt.RsqMR240_Rsq0p09_MR200_prescale);
    stream.select("HLT_RsqMR240_Rsq0p09_MR200_4jet", data.hlt.RsqMR240_Rsq0p09_MR200_4jet);
    stream.select("HLT_RsqMR240_Rsq0p09_MR200_4jet_prescale", data.hlt.RsqMR240_Rsq0p09_MR200_4jet_prescale);
    stream.select("HLT_RsqMR270_Rsq0p09_MR200", data.hlt.RsqMR270_Rsq0p09_MR200);
    stream.select("HLT_RsqMR270_Rsq0p09_MR200_prescale", data.hlt.RsqMR270_Rsq0p09_MR200_prescale);
    stream.select("HLT_RsqMR270_Rsq0p09_MR200_4jet", data.hlt.RsqMR270_Rsq0p09_MR200_4jet);
    stream.select("HLT_RsqMR270_Rsq0p09_MR200_4jet_prescale", data.hlt.RsqMR270_Rsq0p09_MR200_4jet_prescale);
    stream.select("HLT_Mu30_eta2p1_PFJet150_PFJet50", data.hlt.Mu30_eta2p1_PFJet150_PFJet50);
    stream.select("HLT_Mu30_eta2p1_PFJet150_PFJet50_prescale", data.hlt.Mu30_eta2p1_PFJet150_PFJet50_prescale);
    stream.select("HLT_Mu40_eta2p1_PFJet200_PFJet50", data.hlt.Mu40_eta2p1_PFJet200_PFJet50);
    stream.select("HLT_Mu40_eta2p1_PFJet200_PFJet50_prescale", data.hlt.Mu40_eta2p1_PFJet200_PFJet50_prescale);
    stream.select("HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50", data.hlt.Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50);
    stream.select("HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50_prescale", data.hlt.Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50_prescale);
    stream.select("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50", data.hlt.Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50);
    stream.select("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_prescale", data.hlt.Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_prescale);
    stream.select("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140", data.hlt.Ele50_CaloIdVT_GsfTrkIdT_PFJet140);
    stream.select("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140_prescale", data.hlt.Ele50_CaloIdVT_GsfTrkIdT_PFJet140_prescale);
    stream.select("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165", data.hlt.Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    stream.select("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_prescale", data.hlt.Ele50_CaloIdVT_GsfTrkIdT_PFJet165_prescale);
    stream.select("HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF", data.hlt.Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF);
    stream.select("HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF_prescale", data.hlt.Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF_prescale);
    stream.select("HLT_Ele15_IsoVVVL_BTagCSV0p72_PFHT400", data.hlt.Ele15_IsoVVVL_BTagCSV0p72_PFHT400);
    stream.select("HLT_Ele15_IsoVVVL_BTagCSV0p72_PFHT400_prescale", data.hlt.Ele15_IsoVVVL_BTagCSV0p72_PFHT400_prescale);
    stream.select("HLT_Ele15_IsoVVVL_PFHT350_PFMET50", data.hlt.Ele15_IsoVVVL_PFHT350_PFMET50);
    stream.select("HLT_Ele15_IsoVVVL_PFHT350_PFMET50_prescale", data.hlt.Ele15_IsoVVVL_PFHT350_PFMET50_prescale);
    stream.select("HLT_Ele15_IsoVVVL_PFHT400_PFMET50", data.hlt.Ele15_IsoVVVL_PFHT400_PFMET50);
    stream.select("HLT_Ele15_IsoVVVL_PFHT400_PFMET50_prescale", data.hlt.Ele15_IsoVVVL_PFHT400_PFMET50_prescale);
    stream.select("HLT_Ele15_IsoVVVL_PFHT600", data.hlt.Ele15_IsoVVVL_PFHT600);
    stream.select("HLT_Ele15_IsoVVVL_PFHT600_prescale", data.hlt.Ele15_IsoVVVL_PFHT600_prescale);
    stream.select("HLT_Ele15_IsoVVVL_PFHT350", data.hlt.Ele15_IsoVVVL_PFHT350);
    stream.select("HLT_Ele15_IsoVVVL_PFHT350_prescale", data.hlt.Ele15_IsoVVVL_PFHT350_prescale);
    stream.select("HLT_Ele15_IsoVVVL_PFHT400", data.hlt.Ele15_IsoVVVL_PFHT400);
    stream.select("HLT_Ele15_IsoVVVL_PFHT400_prescale", data.hlt.Ele15_IsoVVVL_PFHT400_prescale);
    stream.select("HLT_Ele50_IsoVVVL_PFHT400", data.hlt.Ele50_IsoVVVL_PFHT400);
    stream.select("HLT_Ele50_IsoVVVL_PFHT400_prescale", data.hlt.Ele50_IsoVVVL_PFHT400_prescale);
    stream.select("HLT_Ele23_WPLoose_Gsf_CentralPFJet30_BTagCSV07", data.hlt.Ele23_WPLoose_Gsf_CentralPFJet30_BTagCSV07);
    stream.select("HLT_Ele23_WPLoose_Gsf_CentralPFJet30_BTagCSV07_prescale", data.hlt.Ele23_WPLoose_Gsf_CentralPFJet30_BTagCSV07_prescale);
    stream.select("HLT_Ele27_WPLoose_Gsf_CentralPFJet30_BTagCSV07", data.hlt.Ele27_WPLoose_Gsf_CentralPFJet30_BTagCSV07);
    stream.select("HLT_Ele27_WPLoose_Gsf_CentralPFJet30_BTagCSV07_prescale", data.hlt.Ele27_WPLoose_Gsf_CentralPFJet30_BTagCSV07_prescale);
    stream.select("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200", data.hlt.Ele27_eta2p1_WPLoose_Gsf_HT200);
    stream.select("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_prescale", data.hlt.Ele27_eta2p1_WPLoose_Gsf_HT200_prescale);
    stream.select("HLT_Mu3er_PFHT140_PFMET125", data.hlt.Mu3er_PFHT140_PFMET125);
    stream.select("HLT_Mu3er_PFHT140_PFMET125_prescale", data.hlt.Mu3er_PFHT140_PFMET125_prescale);
    stream.select("HLT_Mu6_PFHT200_PFMET80_BTagCSV0p72", data.hlt.Mu6_PFHT200_PFMET80_BTagCSV0p72);
    stream.select("HLT_Mu6_PFHT200_PFMET80_BTagCSV0p72_prescale", data.hlt.Mu6_PFHT200_PFMET80_BTagCSV0p72_prescale);
    stream.select("HLT_Mu6_PFHT200_PFMET100", data.hlt.Mu6_PFHT200_PFMET100);
    stream.select("HLT_Mu6_PFHT200_PFMET100_prescale", data.hlt.Mu6_PFHT200_PFMET100_prescale);
    stream.select("HLT_Mu10_CentralPFJet30_BTagCSV0p54PF", data.hlt.Mu10_CentralPFJet30_BTagCSV0p54PF);
    stream.select("HLT_Mu10_CentralPFJet30_BTagCSV0p54PF_prescale", data.hlt.Mu10_CentralPFJet30_BTagCSV0p54PF_prescale);
    stream.select("HLT_Mu15_IsoVVVL_BTagCSV0p72_PFHT400", data.hlt.Mu15_IsoVVVL_BTagCSV0p72_PFHT400);
    stream.select("HLT_Mu15_IsoVVVL_BTagCSV0p72_PFHT400_prescale", data.hlt.Mu15_IsoVVVL_BTagCSV0p72_PFHT400_prescale);
    stream.select("HLT_Mu15_IsoVVVL_PFHT350_PFMET50", data.hlt.Mu15_IsoVVVL_PFHT350_PFMET50);
    stream.select("HLT_Mu15_IsoVVVL_PFHT350_PFMET50_prescale", data.hlt.Mu15_IsoVVVL_PFHT350_PFMET50_prescale);
    stream.select("HLT_Mu15_IsoVVVL_PFHT400_PFMET50", data.hlt.Mu15_IsoVVVL_PFHT400_PFMET50);
    stream.select("HLT_Mu15_IsoVVVL_PFHT400_PFMET50_prescale", data.hlt.Mu15_IsoVVVL_PFHT400_PFMET50_prescale);
    stream.select("HLT_Mu15_IsoVVVL_PFHT600", data.hlt.Mu15_IsoVVVL_PFHT600);
    stream.select("HLT_Mu15_IsoVVVL_PFHT600_prescale", data.hlt.Mu15_IsoVVVL_PFHT600_prescale);
    stream.select("HLT_Mu15_IsoVVVL_PFHT350", data.hlt.Mu15_IsoVVVL_PFHT350);
    stream.select("HLT_Mu15_IsoVVVL_PFHT350_prescale", data.hlt.Mu15_IsoVVVL_PFHT350_prescale);
    stream.select("HLT_Mu15_IsoVVVL_PFHT400", data.hlt.Mu15_IsoVVVL_PFHT400);
    stream.select("HLT_Mu15_IsoVVVL_PFHT400_prescale", data.hlt.Mu15_IsoVVVL_PFHT400_prescale);
    stream.select("HLT_Mu50_IsoVVVL_PFHT400", data.hlt.Mu50_IsoVVVL_PFHT400);
    stream.select("HLT_Mu50_IsoVVVL_PFHT400_prescale", data.hlt.Mu50_IsoVVVL_PFHT400_prescale);
    stream.select("HLT_Mu45_eta2p1", data.hlt.Mu45_eta2p1);
    stream.select("HLT_Mu45_eta2p1_prescale", data.hlt.Mu45_eta2p1_prescale);
    stream.select("HLT_Mu50", data.hlt.Mu50);
    stream.select("HLT_Mu50_prescale", data.hlt.Mu50_prescale);
    stream.select("HLT_Mu55", data.hlt.Mu55);
    stream.select("HLT_Mu55_prescale", data.hlt.Mu55_prescale);
    stream.select("HLT_Mu300", data.hlt.Mu300);
    stream.select("HLT_Mu300_prescale", data.hlt.Mu300_prescale);
    stream.select("HLT_Mu350", data.hlt.Mu350);
    stream.select("HLT_Mu350_prescale", data.hlt.Mu350_prescale);
    stream.select("HLT_Ele105_CaloIdVT_GsfTrkIdT", data.hlt.Ele105_CaloIdVT_GsfTrkIdT);
    stream.select("HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale", data.hlt.Ele105_CaloIdVT_GsfTrkIdT_prescale);
    stream.select("HLT_Ele115_CaloIdVT_GsfTrkIdT", data.hlt.Ele115_CaloIdVT_GsfTrkIdT);
    stream.select("HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale", data.hlt.Ele115_CaloIdVT_GsfTrkIdT_prescale);
    stream.select("HLT_IsoMu18", data.hlt.IsoMu18);
    stream.select("HLT_IsoMu18_prescale", data.hlt.IsoMu18_prescale);
    stream.select("HLT_IsoTkMu18", data.hlt.IsoTkMu18);
    stream.select("HLT_IsoTkMu18_prescale", data.hlt.IsoTkMu18_prescale);
    stream.select("HLT_IsoMu20", data.hlt.IsoMu20);
    stream.select("HLT_IsoMu20_prescale", data.hlt.IsoMu20_prescale);
    stream.select("HLT_IsoTkMu20", data.hlt.IsoTkMu20);
    stream.select("HLT_IsoTkMu20_prescale", data.hlt.IsoTkMu20_prescale);
    stream.select("HLT_IsoMu22", data.hlt.IsoMu22);
    stream.select("HLT_IsoMu22_prescale", data.hlt.IsoMu22_prescale);
    stream.select("HLT_IsoTkMu22", data.hlt.IsoTkMu22);
    stream.select("HLT_IsoTkMu22_prescale", data.hlt.IsoTkMu22_prescale);
    stream.select("HLT_IsoMu24", data.hlt.IsoMu24);
    stream.select("HLT_IsoMu24_prescale", data.hlt.IsoMu24_prescale);
    stream.select("HLT_IsoTkMu24", data.hlt.IsoTkMu24);
    stream.select("HLT_IsoTkMu24_prescale", data.hlt.IsoTkMu24_prescale);
    stream.select("HLT_IsoTkMu24_eta2p1", data.hlt.IsoTkMu24_eta2p1);
    stream.select("HLT_IsoTkMu24_eta2p1_prescale", data.hlt.IsoTkMu24_eta2p1_prescale);
    stream.select("HLT_IsoMu27", data.hlt.IsoMu27);
    stream.select("HLT_IsoMu27_prescale", data.hlt.IsoMu27_prescale);
    stream.select("HLT_IsoTkMu27", data.hlt.IsoTkMu27);
    stream.select("HLT_IsoTkMu27_prescale", data.hlt.IsoTkMu27_prescale);
    stream.select("HLT_Ele22_eta2p1_WPLoose_Gsf", data.hlt.Ele22_eta2p1_WPLoose_Gsf);
    stream.select("HLT_Ele22_eta2p1_WPLoose_Gsf_prescale", data.hlt.Ele22_eta2p1_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele22_eta2p1_WPTight_Gsf", data.hlt.Ele22_eta2p1_WPTight_Gsf);
    stream.select("HLT_Ele22_eta2p1_WPTight_Gsf_prescale", data.hlt.Ele22_eta2p1_WPTight_Gsf_prescale);
    stream.select("HLT_Ele23_WPLoose_Gsf", data.hlt.Ele23_WPLoose_Gsf);
    stream.select("HLT_Ele23_WPLoose_Gsf_prescale", data.hlt.Ele23_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele24_WPLoose_Gsf", data.hlt.Ele24_WPLoose_Gsf);
    stream.select("HLT_Ele24_WPLoose_Gsf_prescale", data.hlt.Ele24_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele24_eta2p1_WPLoose_Gsf", data.hlt.Ele24_eta2p1_WPLoose_Gsf);
    stream.select("HLT_Ele24_eta2p1_WPLoose_Gsf_prescale", data.hlt.Ele24_eta2p1_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele25_eta2p1_WPLoose_Gsf", data.hlt.Ele25_eta2p1_WPLoose_Gsf);
    stream.select("HLT_Ele25_eta2p1_WPLoose_Gsf_prescale", data.hlt.Ele25_eta2p1_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele25_eta2p1_WPTight_Gsf", data.hlt.Ele25_eta2p1_WPTight_Gsf);
    stream.select("HLT_Ele25_eta2p1_WPTight_Gsf_prescale", data.hlt.Ele25_eta2p1_WPTight_Gsf_prescale);
    stream.select("HLT_Ele27_WPLoose_Gsf", data.hlt.Ele27_WPLoose_Gsf);
    stream.select("HLT_Ele27_WPLoose_Gsf_prescale", data.hlt.Ele27_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele27_WPTight_Gsf", data.hlt.Ele27_WPTight_Gsf);
    stream.select("HLT_Ele27_WPTight_Gsf_prescale", data.hlt.Ele27_WPTight_Gsf_prescale);
    stream.select("HLT_Ele27_eta2p1_WPLoose_Gsf", data.hlt.Ele27_eta2p1_WPLoose_Gsf);
    stream.select("HLT_Ele27_eta2p1_WPLoose_Gsf_prescale", data.hlt.Ele27_eta2p1_WPLoose_Gsf_prescale);
    stream.select("HLT_Ele27_eta2p1_WPTight_Gsf", data.hlt.Ele27_eta2p1_WPTight_Gsf);
    stream.select("HLT_Ele27_eta2p1_WPTight_Gsf_prescale", data.hlt.Ele27_eta2p1_WPTight_Gsf_prescale);
    stream.select("HLT_Ele32_eta2p1_WPTight_Gsf", data.hlt.Ele32_eta2p1_WPTight_Gsf);
    stream.select("HLT_Ele32_eta2p1_WPTight_Gsf_prescale", data.hlt.Ele32_eta2p1_WPTight_Gsf_prescale);
    
    stream.select("gen_size", data.gen.size);
    stream.select("gen_ID", data.gen.ID);
    stream.select("gen_Status", data.gen.Status);
    stream.select("gen_Mom0ID", data.gen.Mom0ID);
    stream.select("gen_Mom0Status", data.gen.Mom0Status);
    stream.select("gen_Mom1ID", data.gen.Mom1ID);
    stream.select("gen_Mom1Status", data.gen.Mom1Status);
    stream.select("gen_Dau0ID", data.gen.Dau0ID);
    stream.select("gen_Dau0Status", data.gen.Dau0Status);
    stream.select("gen_Dau1ID", data.gen.Dau1ID);
    stream.select("gen_Dau1Status", data.gen.Dau1Status);
    stream.select("gen_Pt", data.gen.Pt);
    stream.select("gen_Eta", data.gen.Eta);
    stream.select("gen_Phi", data.gen.Phi);
    stream.select("gen_E", data.gen.E);
    stream.select("gen_Mass", data.gen.Mass);
    stream.select("gen_Charge", data.gen.Charge);
    
    stream.select("el_size", data.ele.size);
    stream.select("el_Pt", data.ele.Pt);
    stream.select("el_Eta", data.ele.Eta);
    stream.select("el_Phi", data.ele.Phi);
    stream.select("el_E", data.ele.E);
    //stream.select("el_Charge", data.ele.Charge);
    //stream.select("el_Key", data.ele.Key);
    stream.select("el_Iso03", data.ele.Iso03);
    //stream.select("el_Iso03db", data.ele.Iso03db);
    stream.select("el_MiniIso", data.ele.MiniIso);
    stream.select("el_Dxy", data.ele.Dxy);
    stream.select("el_Dz", data.ele.Dz);
    stream.select("el_DB", data.ele.DB);
    stream.select("el_DBerr", data.ele.DBerr);
    stream.select("el_vidVeto", data.ele.vidVeto);
    stream.select("el_vidLoose", data.ele.vidLoose);
    stream.select("el_vidMedium", data.ele.vidMedium);
    stream.select("el_vidTight", data.ele.vidTight);
    stream.select("el_vidHEEP", data.ele.vidHEEP);
    stream.select("el_vidVetonoiso", data.ele.vidVetonoiso);
    stream.select("el_vidLoosenoiso", data.ele.vidLoosenoiso);
    stream.select("el_vidMediumnoiso", data.ele.vidMediumnoiso);
    stream.select("el_vidTightnoiso", data.ele.vidTightnoiso);
    stream.select("el_vidHEEPnoiso", data.ele.vidHEEPnoiso);
    stream.select("el_IsPartOfNearAK4Jet", data.ele.IsPartOfNearAK4Jet);
    stream.select("el_IsPartOfNearAK8Jet", data.ele.IsPartOfNearAK8Jet);
    stream.select("el_IsPartOfNearSubjet", data.ele.IsPartOfNearSubjet);
    stream.select("el_IsoVeto", data.ele.IsoVeto);
    stream.select("el_IsoLoose", data.ele.IsoLoose);
    stream.select("el_IsoMedium", data.ele.IsoMedium);
    stream.select("el_IsoTight", data.ele.IsoTight);
    stream.select("el_DRNearGenEleFromSLTop", data.ele.DRNearGenEleFromSLTop);
    stream.select("el_PtNearGenEleFromSLTop", data.ele.PtNearGenEleFromSLTop);
    stream.select("el_PtNearGenTop", data.ele.PtNearGenTop);
    stream.select("el_LepAK4JetFrac", data.ele.LepAK4JetFrac);
    stream.select("el_LepAK8JetFrac", data.ele.LepAK8JetFrac);
    stream.select("el_LepSubjetFrac", data.ele.LepSubjetFrac);
    stream.select("el_LepAK4JetMassDrop", data.ele.LepAK4JetMassDrop);
    stream.select("el_LepAK8JetMassDrop", data.ele.LepAK8JetMassDrop);
    stream.select("el_LepSubjetMassDrop", data.ele.LepSubjetMassDrop);
    stream.select("el_AK4JetV1DR", data.ele.AK4JetV1DR);
    stream.select("el_AK4JetV2DR", data.ele.AK4JetV2DR);
    stream.select("el_AK4JetV3DR", data.ele.AK4JetV3DR);
    stream.select("el_AK8JetV1DR", data.ele.AK8JetV1DR);
    stream.select("el_AK8JetV2DR", data.ele.AK8JetV2DR);
    stream.select("el_AK8JetV3DR", data.ele.AK8JetV3DR);
    stream.select("el_SubjetV1DR", data.ele.SubjetV1DR);
    stream.select("el_SubjetV2DR", data.ele.SubjetV2DR);
    stream.select("el_SubjetV3DR", data.ele.SubjetV3DR);
    stream.select("el_AK4JetV1PtRel", data.ele.AK4JetV1PtRel);
    stream.select("el_AK4JetV2PtRel", data.ele.AK4JetV2PtRel);
    stream.select("el_AK4JetV3PtRel", data.ele.AK4JetV3PtRel);
    stream.select("el_AK8JetV1PtRel", data.ele.AK8JetV1PtRel);
    stream.select("el_AK8JetV2PtRel", data.ele.AK8JetV2PtRel);
    stream.select("el_AK8JetV3PtRel", data.ele.AK8JetV3PtRel);
    stream.select("el_SubjetV1PtRel", data.ele.SubjetV1PtRel);
    stream.select("el_SubjetV2PtRel", data.ele.SubjetV2PtRel);
    stream.select("el_SubjetV3PtRel", data.ele.SubjetV3PtRel);
    
    stream.select("mu_size", data.mu.size);
    stream.select("mu_Pt", data.mu.Pt);
    stream.select("mu_Eta", data.mu.Eta);
    stream.select("mu_Phi", data.mu.Phi);
    stream.select("mu_E", data.mu.E);
    //stream.select("mu_Charge", data.mu.Charge);
    //stream.select("mu_Key", data.mu.Key);
    stream.select("mu_Iso04", data.mu.Iso04);
    stream.select("mu_MiniIso", data.mu.MiniIso);
    stream.select("mu_Dxy", data.mu.Dxy);
    stream.select("mu_Dz", data.mu.Dz);
    stream.select("mu_DB", data.mu.DB);
    stream.select("mu_DBerr", data.mu.DBerr);
    stream.select("mu_IsSoftMuon", data.mu.IsSoftMuon);
    stream.select("mu_IsLooseMuon", data.mu.IsLooseMuon);
    stream.select("mu_IsMediumMuon", data.mu.IsMediumMuon);
    stream.select("mu_IsTightMuon", data.mu.IsTightMuon);
    stream.select("mu_IsHighPtMuon", data.mu.IsHighPtMuon);
    stream.select("mu_IsPartOfNearAK4Jet", data.mu.IsPartOfNearAK4Jet);
    stream.select("mu_IsPartOfNearAK8Jet", data.mu.IsPartOfNearAK8Jet);
    stream.select("mu_IsPartOfNearSubjet", data.mu.IsPartOfNearSubjet);
    stream.select("mu_DRNearGenMuFromSLTop", data.mu.DRNearGenMuFromSLTop);
    stream.select("mu_PtNearGenMuFromSLTop", data.mu.PtNearGenMuFromSLTop);
    stream.select("mu_PtNearGenTop", data.mu.PtNearGenTop);
    stream.select("mu_LepAK4JetFrac", data.mu.LepAK4JetFrac);
    stream.select("mu_LepAK8JetFrac", data.mu.LepAK8JetFrac);
    stream.select("mu_LepSubjetFrac", data.mu.LepSubjetFrac);
    stream.select("mu_LepAK4JetMassDrop", data.mu.LepAK4JetMassDrop);
    stream.select("mu_LepAK8JetMassDrop", data.mu.LepAK8JetMassDrop);
    stream.select("mu_LepSubjetMassDrop", data.mu.LepSubjetMassDrop);
    stream.select("mu_AK4JetV1DR", data.mu.AK4JetV1DR);
    stream.select("mu_AK4JetV2DR", data.mu.AK4JetV2DR);
    stream.select("mu_AK4JetV3DR", data.mu.AK4JetV3DR);
    stream.select("mu_AK8JetV1DR", data.mu.AK8JetV1DR);
    stream.select("mu_AK8JetV2DR", data.mu.AK8JetV2DR);
    stream.select("mu_AK8JetV3DR", data.mu.AK8JetV3DR);
    stream.select("mu_SubjetV1DR", data.mu.SubjetV1DR);
    stream.select("mu_SubjetV2DR", data.mu.SubjetV2DR);
    stream.select("mu_SubjetV3DR", data.mu.SubjetV3DR);
    stream.select("mu_AK4JetV1PtRel", data.mu.AK4JetV1PtRel);
    stream.select("mu_AK4JetV2PtRel", data.mu.AK4JetV2PtRel);
    stream.select("mu_AK4JetV3PtRel", data.mu.AK4JetV3PtRel);
    stream.select("mu_AK8JetV1PtRel", data.mu.AK8JetV1PtRel);
    stream.select("mu_AK8JetV2PtRel", data.mu.AK8JetV2PtRel);
    stream.select("mu_AK8JetV3PtRel", data.mu.AK8JetV3PtRel);
    stream.select("mu_SubjetV1PtRel", data.mu.SubjetV1PtRel);
    stream.select("mu_SubjetV2PtRel", data.mu.SubjetV2PtRel);
    stream.select("mu_SubjetV3PtRel", data.mu.SubjetV3PtRel);
    
    stream.select("jetAK4Puppi_size", data.jetsAK4Puppi.size);
    stream.select("jetAK4Puppi_Pt", data.jetsAK4Puppi.Pt);
    stream.select("jetAK4Puppi_Eta", data.jetsAK4Puppi.Eta);
    stream.select("jetAK4Puppi_Phi", data.jetsAK4Puppi.Phi);
    stream.select("jetAK4Puppi_E", data.jetsAK4Puppi.E);
    //stream.select("jetAK4Puppi_Charge", data.jetsAK4Puppi.Charge);
    stream.select("jetAK4Puppi_CSVv2", data.jetsAK4Puppi.CSVv2);
    stream.select("jetAK4Puppi_CMVAv2", data.jetsAK4Puppi.CMVAv2);
    //stream.select("jetAK4Puppi_CvsL", data.jetsAK4Puppi.CvsL);
    //stream.select("jetAK4Puppi_CvsB", data.jetsAK4Puppi.CvsB);
    stream.select("jetAK4Puppi_GenPartonEta", data.jetsAK4Puppi.GenPartonEta);
    stream.select("jetAK4Puppi_GenPartonPhi", data.jetsAK4Puppi.GenPartonPhi);
    stream.select("jetAK4Puppi_GenPartonPt", data.jetsAK4Puppi.GenPartonPt);
    stream.select("jetAK4Puppi_GenPartonE", data.jetsAK4Puppi.GenPartonE);
    stream.select("jetAK4Puppi_GenPartonCharge", data.jetsAK4Puppi.GenPartonCharge);
    stream.select("jetAK4Puppi_PartonFlavour", data.jetsAK4Puppi.PartonFlavour);
    stream.select("jetAK4Puppi_HadronFlavour", data.jetsAK4Puppi.HadronFlavour);
    stream.select("jetAK4Puppi_GenJetEta", data.jetsAK4Puppi.GenJetEta);
    stream.select("jetAK4Puppi_GenJetPhi", data.jetsAK4Puppi.GenJetPhi);
    stream.select("jetAK4Puppi_GenJetPt", data.jetsAK4Puppi.GenJetPt);
    stream.select("jetAK4Puppi_GenJetE", data.jetsAK4Puppi.GenJetE);
    stream.select("jetAK4Puppi_GenJetCharge", data.jetsAK4Puppi.GenJetCharge);
    stream.select("jetAK4Puppi_jecFactor0", data.jetsAK4Puppi.jecFactor0);
    stream.select("jetAK4Puppi_jecUncertainty", data.jetsAK4Puppi.jecUncertainty);
    stream.select("jetAK4Puppi_JERSF", data.jetsAK4Puppi.JERSF);
    stream.select("jetAK4Puppi_JERSFUp", data.jetsAK4Puppi.JERSFUp);
    stream.select("jetAK4Puppi_JERSFDown", data.jetsAK4Puppi.JERSFDown);
    stream.select("jetAK4Puppi_SmearedPt", data.jetsAK4Puppi.SmearedPt);
    //stream.select("jetAK4Puppi_Keys", data.jetsAK4Puppi.Keys);
    stream.select("jetAK4Puppi_looseJetID", data.jetsAK4Puppi.looseJetID);
    stream.select("jetAK4Puppi_tightJetID", data.jetsAK4Puppi.tightJetID);
    stream.select("jetAK4Puppi_tightLepVetoJetID", data.jetsAK4Puppi.tightLepVetoJetID);
    
    stream.select("jetAK8Puppi_size", data.jetsAK8Puppi.size);
    stream.select("jetAK8Puppi_Pt", data.jetsAK8Puppi.Pt);
    stream.select("jetAK8Puppi_Eta", data.jetsAK8Puppi.Eta);
    stream.select("jetAK8Puppi_Phi", data.jetsAK8Puppi.Phi);
    stream.select("jetAK8Puppi_E", data.jetsAK8Puppi.E);
    //stream.select("jetAK8Puppi_Charge", data.jetsAK8Puppi.Charge);
    stream.select("jetAK8Puppi_CSVv2", data.jetsAK8Puppi.CSVv2);
    stream.select("jetAK8Puppi_CMVAv2", data.jetsAK8Puppi.CMVAv2);
    //stream.select("jetAK8Puppi_CvsL", data.jetsAK8Puppi.CvsL);
    //stream.select("jetAK8Puppi_CvsB", data.jetsAK8Puppi.CvsB);
    stream.select("jetAK8Puppi_GenPartonEta", data.jetsAK8Puppi.GenPartonEta);
    stream.select("jetAK8Puppi_GenPartonPhi", data.jetsAK8Puppi.GenPartonPhi);
    stream.select("jetAK8Puppi_GenPartonPt", data.jetsAK8Puppi.GenPartonPt);
    stream.select("jetAK8Puppi_GenPartonE", data.jetsAK8Puppi.GenPartonE);
    stream.select("jetAK8Puppi_GenPartonCharge", data.jetsAK8Puppi.GenPartonCharge);
    stream.select("jetAK8Puppi_PartonFlavour", data.jetsAK8Puppi.PartonFlavour);
    stream.select("jetAK8Puppi_HadronFlavour", data.jetsAK8Puppi.HadronFlavour);
    stream.select("jetAK8Puppi_GenJetEta", data.jetsAK8Puppi.GenJetEta);
    stream.select("jetAK8Puppi_GenJetPhi", data.jetsAK8Puppi.GenJetPhi);
    stream.select("jetAK8Puppi_GenJetPt", data.jetsAK8Puppi.GenJetPt);
    stream.select("jetAK8Puppi_GenJetE", data.jetsAK8Puppi.GenJetE);
    stream.select("jetAK8Puppi_GenJetCharge", data.jetsAK8Puppi.GenJetCharge);
    stream.select("jetAK8Puppi_jecFactor0", data.jetsAK8Puppi.jecFactor0);
    stream.select("jetAK8Puppi_jecUncertainty", data.jetsAK8Puppi.jecUncertainty);
    stream.select("jetAK8Puppi_JERSF", data.jetsAK8Puppi.JERSF);
    //stream.select("jetAK8Puppi_JERSFUp", data.jetsAK8Puppi.JERSFUp);
    //stream.select("jetAK8Puppi_JERSFDown", data.jetsAK8Puppi.JERSFDown);
    stream.select("jetAK8Puppi_SmearedPt", data.jetsAK8Puppi.SmearedPt);
    //stream.select("jetAK8Puppi_DoubleBAK8", data.jetsAK8Puppi.DoubleBAK8);
    //stream.select("jetAK8Puppi_DoubleBCA15", data.jetsAK8Puppi.DoubleBCA15);
    stream.select("jetAK8Puppi_vSubjetIndex0", data.jetsAK8Puppi.vSubjetIndex0);
    stream.select("jetAK8Puppi_vSubjetIndex1", data.jetsAK8Puppi.vSubjetIndex1);
    stream.select("jetAK8Puppi_tau1", data.jetsAK8Puppi.tau1);
    stream.select("jetAK8Puppi_tau2", data.jetsAK8Puppi.tau2);
    stream.select("jetAK8Puppi_tau3", data.jetsAK8Puppi.tau3);
    stream.select("jetAK8Puppi_softDropMass", data.jetsAK8Puppi.softDropMass);
    //stream.select("jetAK8Puppi_Keys", data.jetsAK8Puppi.Keys);
    stream.select("jetAK8Puppi_HasNearGenTop", data.jetsAK8Puppi.HasNearGenTop);
    stream.select("jetAK8Puppi_NearGenTopIsHadronic", data.jetsAK8Puppi.NearGenTopIsHadronic);
    stream.select("jetAK8Puppi_NearGenWIsHadronic", data.jetsAK8Puppi.NearGenWIsHadronic);
    stream.select("jetAK8Puppi_NearGenWToENu", data.jetsAK8Puppi.NearGenWToENu);
    stream.select("jetAK8Puppi_NearGenWToMuNu", data.jetsAK8Puppi.NearGenWToMuNu);
    stream.select("jetAK8Puppi_NearGenWToTauNu", data.jetsAK8Puppi.NearGenWToTauNu);
    stream.select("jetAK8Puppi_looseJetID", data.jetsAK8Puppi.looseJetID);
    stream.select("jetAK8Puppi_tightJetID", data.jetsAK8Puppi.tightJetID);
    stream.select("jetAK8Puppi_tightLepVetoJetID", data.jetsAK8Puppi.tightLepVetoJetID);
    stream.select("jetAK8Puppi_DRNearGenTop", data.jetsAK8Puppi.DRNearGenTop);
    stream.select("jetAK8Puppi_DRNearGenWFromTop", data.jetsAK8Puppi.DRNearGenWFromTop);
    stream.select("jetAK8Puppi_DRNearGenBFromTop", data.jetsAK8Puppi.DRNearGenBFromTop);
    stream.select("jetAK8Puppi_DRNearGenLepFromSLTop", data.jetsAK8Puppi.DRNearGenLepFromSLTop);
    stream.select("jetAK8Puppi_DRNearGenNuFromSLTop", data.jetsAK8Puppi.DRNearGenNuFromSLTop);
    stream.select("jetAK8Puppi_PtNearGenTop", data.jetsAK8Puppi.PtNearGenTop);
    stream.select("jetAK8Puppi_PtNearGenBFromTop", data.jetsAK8Puppi.PtNearGenBFromTop);
    stream.select("jetAK8Puppi_PtNearGenWFromTop", data.jetsAK8Puppi.PtNearGenWFromTop);
    stream.select("jetAK8Puppi_PtNearGenLepFromSLTop", data.jetsAK8Puppi.PtNearGenLepFromSLTop);
    stream.select("jetAK8Puppi_PtNearGenNuFromSLTop", data.jetsAK8Puppi.PtNearGenNuFromSLTop);
    
    stream.select("subjetAK8Puppi_size", data.subjetsAK8Puppi.size);
    stream.select("subjetAK8Puppi_Pt", data.subjetsAK8Puppi.Pt);
    stream.select("subjetAK8Puppi_Eta", data.subjetsAK8Puppi.Eta);
    stream.select("subjetAK8Puppi_Phi", data.subjetsAK8Puppi.Phi);
    stream.select("subjetAK8Puppi_E", data.subjetsAK8Puppi.E);
    //stream.select("subjetAK8Puppi_Charge", data.subjetsAK8Puppi.Charge);
    stream.select("subjetAK8Puppi_CSVv2", data.subjetsAK8Puppi.CSVv2);
    stream.select("subjetAK8Puppi_CMVAv2", data.subjetsAK8Puppi.CMVAv2);
    //stream.select("subjetAK8Puppi_CvsL", data.subjetsAK8Puppi.CvsL);
    //stream.select("subjetAK8Puppi_CvsB", data.subjetsAK8Puppi.CvsB);
    //stream.select("subjetAK8Puppi_GenPartonEta", data.subjetsAK8Puppi.GenPartonEta);
    //stream.select("subjetAK8Puppi_GenPartonPhi", data.subjetsAK8Puppi.GenPartonPhi);
    //stream.select("subjetAK8Puppi_GenPartonPt", data.subjetsAK8Puppi.GenPartonPt);
    //stream.select("subjetAK8Puppi_GenPartonE", data.subjetsAK8Puppi.GenPartonE);
    //stream.select("subjetAK8Puppi_GenPartonCharge", data.subjetsAK8Puppi.GenPartonCharge);
    //stream.select("subjetAK8Puppi_PartonFlavour", data.subjetsAK8Puppi.PartonFlavour);
    //stream.select("subjetAK8Puppi_HadronFlavour", data.subjetsAK8Puppi.HadronFlavour);
    //stream.select("subjetAK8Puppi_GenJetEta", data.subjetsAK8Puppi.GenJetEta);
    //stream.select("subjetAK8Puppi_GenJetPhi", data.subjetsAK8Puppi.GenJetPhi);
    //stream.select("subjetAK8Puppi_GenJetPt", data.subjetsAK8Puppi.GenJetPt);
    //stream.select("subjetAK8Puppi_GenJetE", data.subjetsAK8Puppi.GenJetE);
    //stream.select("subjetAK8Puppi_GenJetCharge", data.subjetsAK8Puppi.GenJetCharge);
    //stream.select("subjetAK8Puppi_jecFactor0", data.subjetsAK8Puppi.jecFactor0);
    //stream.select("subjetAK8Puppi_Keys", data.subjetsAK8Puppi.Keys);
    //stream.select("subjetAK8Puppi_looseJetID", data.subjetsAK8Puppi.looseJetID);
    //stream.select("subjetAK8Puppi_tightJetID", data.subjetsAK8Puppi.tightJetID);
    //stream.select("subjetAK8Puppi_tightLepVetoJetID", data.subjetsAK8Puppi.tightLepVetoJetID);
    
    //stream.select("genjetAK8SD_size", data.genjetsAK8.size);
    //stream.select("genjetAK8SD_Pt", data.genjetsAK8.Pt);
    //stream.select("genjetAK8SD_Eta", data.genjetsAK8.Eta);
    //stream.select("genjetAK8SD_Phi", data.genjetsAK8.Phi);
    //stream.select("genjetAK8SD_E", data.genjetsAK8.E);
    //stream.select("genjetAK8SD_Charge", data.genjetsAK8.Charge);
    
  }


} settings;
