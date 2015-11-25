#ifndef ANALYZER_H
#define ANALYZER_H
//-----------------------------------------------------------------------------
// File:        Analyzer.h
// Description: Analyzer header for ntuples created by B2GTTreeMaker
// Created:     Tue Nov 24 2015
// Author:      Sezen Sekmen, Janos Karancsi
//-----------------------------------------------------------------------------
// -- System

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "common/treestream.h"
#include "common/treestream.cc"

// -- Root

#include "TROOT.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TH1D.h"
#include "TH2D.h"
//-----------------------------------------------------------------------------
// -- Declare variables to be read
//-----------------------------------------------------------------------------
#include "common/DataStruct.h"
DataStruct data;

//-----------------------------------------------------------------------------
// --- Structs can be filled by calling fillObjects()
// --- after the call to stream.read(...)
//-----------------------------------------------------------------------------
// -- Select variables to be read
//-----------------------------------------------------------------------------
void selectVariables(itreestream& stream)
{

  stream.select("gen_size", data.gen.size);
  stream.select("gen_Pt", &data.gen.Pt, NGEN, 'F', 0);
  
  stream.select("vtx_size", data.evt.vtx_size);
  stream.select("vtx_z", &data.evt.vtx_z, 100, 'F', 0);
  stream.select("vtx_rho", data.evt.vtx_rho, 100, 'F', 0);
  //stream.select("vtx_chi", data.evt.vtx_chi, 100, 'F', 0);
  stream.select("vtx_ndof", data.evt.vtx_ndof, 100, 'I', 0);
  
  /*
  //stream.select("gen_Mass", data.gen.Mass);
  stream.select("gen_Pt", data.gen.Pt);
  stream.select("gen_Eta", data.gen.Eta);
  //stream.select("gen_Y", data.gen.Y);
  stream.select("gen_Phi", data.gen.Phi);
  stream.select("gen_E", data.gen.E);
  //stream.select("gen_Charge", data.gen.Charge);
  stream.select("gen_ID", data.gen.ID);
  stream.select("gen_Status", data.gen.Status);
  stream.select("gen_Mom0ID", data.gen.MomID);

  stream.select("el_size", data.ele.size);
  //stream.select("el_Mass", data.ele.Mass);
  stream.select("el_Pt", data.ele.Pt);
  stream.select("el_Eta", data.ele.Eta);
  //stream.select("el_Y", data.ele.Y);
  stream.select("el_Phi", data.ele.Phi);
  stream.select("el_E", data.ele.E);
  //stream.select("el_Charge", data.ele.Charge);
  stream.select("el_Iso03", data.ele.Iso03);
  //stream.select("el_D0", data.ele.D0);
  //stream.select("el_Dz", data.ele.Dz);
  //stream.select("el_dEtaIn", data.ele.dEtaIn);
  //stream.select("el_dPhiIn", data.ele.dPhiIn);
  //stream.select("el_HoE", data.ele.HoE);
  //stream.select("el_full5x5siee", data.ele.full5x5siee);
  //stream.select("el_ooEmooP", data.ele.ooEmooP);
  //stream.select("el_missHits", data.ele.missHits);
  //stream.select("el_hasMatchedConVeto", data.ele.hasMatchedConVeto);
  //stream.select("el_isEB", data.ele.isEB);
  stream.select("el_isVeto", data.ele.isVeto);
  stream.select("el_isLoose", data.ele.isLoose);
  stream.select("el_isTight", data.ele.isTight);
  stream.select("el_isMedium", data.ele.isMedium);
  //stream.select("el_scEta", data.ele.scEta);
  
  stream.select("mu_size", data.mu.size);
  //stream.select("mu_Mass", data.mu.Mass);
  stream.select("mu_Pt", data.mu.Pt);
  stream.select("mu_Eta", data.mu.Eta);
  //stream.select("mu_Y", data.mu.Y);
  stream.select("mu_Phi", data.mu.Phi);
  stream.select("mu_E", data.mu.E);
  //stream.select("mu_Charge", data.mu.Charge);
  stream.select("mu_Iso04", data.mu.Iso04);
  //stream.select("mu_D0", data.mu.D0);
  //stream.select("mu_D0err", data.mu.D0err);
  //stream.select("mu_Dxy", data.mu.Dxy);
  //stream.select("mu_Dxyerr", data.mu.Dxyerr);
  //stream.select("mu_Dz", data.mu.Dz);
  //stream.select("mu_Dzerr", data.mu.Dzerr);
  stream.select("mu_IsLooseMuon", data.mu.IsLooseMuon);
  stream.select("mu_IsSoftMuon", data.mu.IsSoftMuon);
  stream.select("mu_IsTightMuon", data.mu.IsTightMuon);
  //stream.select("mu_IsPFMuon", data.mu.IsPFMuon);
  //stream.select("mu_IsGlobalMuon", data.mu.IsGlobalMuon);
  //stream.select("mu_IsTrackerMuon", data.mu.IsTrackerMuon);
  //stream.select("mu_GlbTrkNormChi2", data.mu.GlbTrkNormChi2);
  //stream.select("mu_NumberValidMuonHits", data.mu.NumberValidMuonHits);
  //stream.select("mu_NumberMatchedStations", data.mu.NumberMatchedStations);
  //stream.select("mu_NumberValidPixelHits", data.mu.NumberValidPixelHits);
  //stream.select("mu_NumberTrackerLayers", data.mu.NumberTrackerLayers);
  //stream.select("mu_NumberOfValidTrackerHits", data.mu.NumberOfValidTrackerHits);
  //stream.select("mu_NumberOfPixelLayers", data.mu.NumberOfPixelLayers);
  //stream.select("mu_InTrkNormChi2", data.mu.InTrkNormChi2);
  //stream.select("mu_SumChargedHadronPt", data.mu.SumChargedHadronPt);
  //stream.select("mu_SumNeutralHadronPt", data.mu.SumNeutralHadronPt);
  //stream.select("mu_SumPhotonPt", data.mu.SumPhotonPt);
  //stream.select("mu_SumPUPt", data.mu.SumPUPt);
  //stream.select("mu_GenMuonY", data.mu.GenMuonY);
  //stream.select("mu_GenMuonEta", data.mu.GenMuonEta);
  //stream.select("mu_GenMuonPhi", data.mu.GenMuonPhi);
  //stream.select("mu_GenMuonPt", data.mu.GenMuonPt);
  //stream.select("mu_GenMuonE", data.mu.GenMuonE);
  //stream.select("mu_GenMuonCharge", data.mu.GenMuonCharge);
  
  //stream.select("jetAK4_size", data.jetsAK4.size);
  //stream.select("jetAK4_Mass", data.jetsAK4.Mass);
  //stream.select("jetAK4_Pt", data.jetsAK4.Pt);
  //stream.select("jetAK4_Eta", data.jetsAK4.Eta);
  //stream.select("jetAK4_Y", data.jetsAK4.Y);
  //stream.select("jetAK4_Phi", data.jetsAK4.Phi);
  //stream.select("jetAK4_E", data.jetsAK4.E);
  //stream.select("jetAK4_Charge", data.jetsAK4.Charge);
  //stream.select("jetAK4_CSV", data.jetsAK4.CSV);
  //stream.select("jetAK4_CSVV1", data.jetsAK4.CSVV1);
  //stream.select("jetAK4_GenPartonY", data.jetsAK4.GenPartonY);
  //stream.select("jetAK4_GenPartonEta", data.jetsAK4.GenPartonEta);
  //stream.select("jetAK4_GenPartonPhi", data.jetsAK4.GenPartonPhi);
  //stream.select("jetAK4_GenPartonPt", data.jetsAK4.GenPartonPt);
  //stream.select("jetAK4_GenPartonE", data.jetsAK4.GenPartonE);
  //stream.select("jetAK4_GenPartonCharge", data.jetsAK4.GenPartonCharge);
  //stream.select("jetAK4_PartonFlavour", data.jetsAK4.PartonFlavour);
  //stream.select("jetAK4_HadronFlavour", data.jetsAK4.HadronFlavour);
  //stream.select("jetAK4_GenJetY", data.jetsAK4.GenJetY);
  //stream.select("jetAK4_GenJetEta", data.jetsAK4.GenJetEta);
  //stream.select("jetAK4_GenJetPhi", data.jetsAK4.GenJetPhi);
  //stream.select("jetAK4_GenJetPt", data.jetsAK4.GenJetPt);
  //stream.select("jetAK4_GenJetE", data.jetsAK4.GenJetE);
  //stream.select("jetAK4_GenJetCharge", data.jetsAK4.GenJetCharge);
  //stream.select("jetAK4_muonMultiplicity", data.jetsAK4.muonMultiplicity);
  //stream.select("jetAK4_PhotonEnergy", data.jetsAK4.PhotonEnergy);
  //stream.select("jetAK4_ElectronEnergy", data.jetsAK4.ElectronEnergy);
  //stream.select("jetAK4_MuonEnergy", data.jetsAK4.MuonEnergy);
  //stream.select("jetAK4_HFHadronEnergy", data.jetsAK4.HFHadronEnergy);
  //stream.select("jetAK4_HFEMEnergy", data.jetsAK4.HFEMEnergy);
  //stream.select("jetAK4_ChargedHadronMultiplicity", data.jetsAK4.ChargedHadronMultiplicity);
  //stream.select("jetAK4_numberOfDaughters", data.jetsAK4.numberOfDaughters);
  //stream.select("jetAK4_chargedMultiplicity", data.jetsAK4.chargedMultiplicity);
  //stream.select("jetAK4_neutralHadronMultiplicity", data.jetsAK4.neutralHadronMultiplicity);
  //stream.select("jetAK4_neutralHadronEnergy", data.jetsAK4.neutralHadronEnergy);
  //stream.select("jetAK4_neutralEmEnergy", data.jetsAK4.neutralEmEnergy);
  //stream.select("jetAK4_chargedEmEnergy", data.jetsAK4.chargedEmEnergy);
  //stream.select("jetAK4_chargedHadronEnergy", data.jetsAK4.chargedHadronEnergy);
  //stream.select("jetAK4_photonMultiplicity", data.jetsAK4.photonMultiplicity);
  //stream.select("jetAK4_electronMultiplicity", data.jetsAK4.electronMultiplicity);
  //stream.select("jetAK4_HFHadronMultiplicity", data.jetsAK4.HFHadronMultiplicity);
  //stream.select("jetAK4_HFEMMultiplicity", data.jetsAK4.HFEMMultiplicity);
  //stream.select("jetAK4_ChargeMuEnergy", data.jetsAK4.ChargeMuEnergy);
  //stream.select("jetAK4_neutralMultiplicity", data.jetsAK4.neutralMultiplicity);
  //stream.select("jetAK4_jecFactor0", data.jetsAK4.jecFactor0);
  //stream.select("jetAK4_jetArea", data.jetsAK4.jetArea);
  //stream.select("jetAK4_SmearedPt", data.jetsAK4.SmearedPt);
  //stream.select("jetAK4_SmearedPEta", data.jetsAK4.SmearedPEta);
  //stream.select("jetAK4_SmearedPhi", data.jetsAK4.SmearedPhi);
  //stream.select("jetAK4_SmearedE", data.jetsAK4.SmearedE);
  //stream.select("jetAK4_JERup", data.jetsAK4.JERup);
  //stream.select("jetAK4_JERdown", data.jetsAK4.JERdown);
  
  stream.select("jetAK8_size", data.jetsAK8.size);
  //stream.select("jetAK8_Mass", data.jetsAK8.Mass);
  stream.select("jetAK8_Pt", data.jetsAK8.Pt);
  stream.select("jetAK8_Eta", data.jetsAK8.Eta);
  //stream.select("jetAK8_Y", data.jetsAK8.Y);
  stream.select("jetAK8_Phi", data.jetsAK8.Phi);
  stream.select("jetAK8_E", data.jetsAK8.E);
  //stream.select("jetAK8_Charge", data.jetsAK8.Charge);
  stream.select("jetAK8_CSV", data.jetsAK8.CSV);
  stream.select("jetAK8_CSVV1", data.jetsAK8.CSVV1);
  //stream.select("jetAK8_GenPartonY", data.jetsAK8.GenPartonY);
  //stream.select("jetAK8_GenPartonEta", data.jetsAK8.GenPartonEta);
  //stream.select("jetAK8_GenPartonPhi", data.jetsAK8.GenPartonPhi);
  //stream.select("jetAK8_GenPartonPt", data.jetsAK8.GenPartonPt);
  //stream.select("jetAK8_GenPartonE", data.jetsAK8.GenPartonE);
  //stream.select("jetAK8_GenPartonCharge", data.jetsAK8.GenPartonCharge);
  //stream.select("jetAK8_PartonFlavour", data.jetsAK8.PartonFlavour);
  //stream.select("jetAK8_HadronFlavour", data.jetsAK8.HadronFlavour);
  //stream.select("jetAK8_GenJetY", data.jetsAK8.GenJetY);
  //stream.select("jetAK8_GenJetEta", data.jetsAK8.GenJetEta);
  //stream.select("jetAK8_GenJetPhi", data.jetsAK8.GenJetPhi);
  //stream.select("jetAK8_GenJetPt", data.jetsAK8.GenJetPt);
  //stream.select("jetAK8_GenJetE", data.jetsAK8.GenJetE);
  //stream.select("jetAK8_GenJetCharge", data.jetsAK8.GenJetCharge);
  //stream.select("jetAK8_muonMultiplicity", data.jetsAK8.muonMultiplicity);
  //stream.select("jetAK8_PhotonEnergy", data.jetsAK8.PhotonEnergy);
  //stream.select("jetAK8_ElectronEnergy", data.jetsAK8.ElectronEnergy);
  //stream.select("jetAK8_MuonEnergy", data.jetsAK8.MuonEnergy);
  //stream.select("jetAK8_HFHadronEnergy", data.jetsAK8.HFHadronEnergy);
  //stream.select("jetAK8_HFEMEnergy", data.jetsAK8.HFEMEnergy);
  //stream.select("jetAK8_ChargedHadronMultiplicity", data.jetsAK8.ChargedHadronMultiplicity);
  //stream.select("jetAK8_numberOfDaughters", data.jetsAK8.numberOfDaughters);
  //stream.select("jetAK8_chargedMultiplicity", data.jetsAK8.chargedMultiplicity);
  //stream.select("jetAK8_neutralHadronMultiplicity", data.jetsAK8.neutralHadronMultiplicity);
  //stream.select("jetAK8_neutralHadronEnergy", data.jetsAK8.neutralHadronEnergy);
  //stream.select("jetAK8_neutralEmEnergy", data.jetsAK8.neutralEmEnergy);
  //stream.select("jetAK8_chargedEmEnergy", data.jetsAK8.chargedEmEnergy);
  //stream.select("jetAK8_chargedHadronEnergy", data.jetsAK8.chargedHadronEnergy);
  //stream.select("jetAK8_photonMultiplicity", data.jetsAK8.photonMultiplicity);
  //stream.select("jetAK8_electronMultiplicity", data.jetsAK8.electronMultiplicity);
  //stream.select("jetAK8_HFHadronMultiplicity", data.jetsAK8.HFHadronMultiplicity);
  //stream.select("jetAK8_HFEMMultiplicity", data.jetsAK8.HFEMMultiplicity);
  //stream.select("jetAK8_ChargeMuEnergy", data.jetsAK8.ChargeMuEnergy);
  //stream.select("jetAK8_neutralMultiplicity", data.jetsAK8.neutralMultiplicity);
  //stream.select("jetAK8_jecFactor0", data.jetsAK8.jecFactor0);
  //stream.select("jetAK8_jetArea", data.jetsAK8.jetArea);
  //stream.select("jetAK8_SmearedPt", data.jetsAK8.SmearedPt);
  //stream.select("jetAK8_SmearedPEta", data.jetsAK8.SmearedPEta);
  //stream.select("jetAK8_SmearedPhi", data.jetsAK8.SmearedPhi);
  //stream.select("jetAK8_SmearedE", data.jetsAK8.SmearedE);
  //stream.select("jetAK8_JERup", data.jetsAK8.JERup);
  //stream.select("jetAK8_JERdown", data.jetsAK8.JERdown);
  stream.select("jetAK8_vSubjetIndex0", data.jetsAK8.vSubjetIndex0);
  stream.select("jetAK8_vSubjetIndex1", data.jetsAK8.vSubjetIndex1);
  stream.select("jetAK8_topSubjetIndex0", data.jetsAK8.topSubjetIndex0);
  stream.select("jetAK8_topSubjetIndex1", data.jetsAK8.topSubjetIndex1);
  stream.select("jetAK8_topSubjetIndex2", data.jetsAK8.topSubjetIndex2);
  stream.select("jetAK8_topSubjetIndex3", data.jetsAK8.topSubjetIndex3);
  stream.select("jetAK8_tau1", data.jetsAK8.tau1);
  stream.select("jetAK8_tau2", data.jetsAK8.tau2);
  stream.select("jetAK8_tau3", data.jetsAK8.tau3);
  stream.select("jetAK8_trimmedMass", data.jetsAK8.trimmedMass);
  stream.select("jetAK8_prunedMass", data.jetsAK8.prunedMass);
  stream.select("jetAK8_filteredMass", data.jetsAK8.filteredMass);
  stream.select("jetAK8_softDropMass", data.jetsAK8.softDropMass);
  stream.select("jetAK8_topMass", data.jetsAK8.topMass);
  stream.select("jetAK8_wMass", data.jetsAK8.wMass);
  stream.select("jetAK8_nSubJets", data.jetsAK8.nSubJets);
  stream.select("jetAK8_minmass", data.jetsAK8.minmass);
  
  stream.select("subjetAK8_size", data.subjetsAK8.size);
  //stream.select("subjetAK8_Mass", data.subjetsAK8.Mass);			
  stream.select("subjetAK8_Pt", data.subjetsAK8.Pt);
  stream.select("subjetAK8_Eta", data.subjetsAK8.Eta);
  //stream.select("subjetAK8_Y", data.subjetsAK8.Y);
  stream.select("subjetAK8_Phi", data.subjetsAK8.Phi);
  stream.select("subjetAK8_E", data.subjetsAK8.E);
  //stream.select("subjetAK8_Charge", data.subjetsAK8.Charge);
  stream.select("subjetAK8_CSV", data.subjetsAK8.CSV);
  stream.select("subjetAK8_CSVV1", data.subjetsAK8.CSVV1);
  //stream.select("subjetAK8_GenPartonY", data.subjetsAK8.GenPartonY);
  //stream.select("subjetAK8_GenPartonEta", data.subjetsAK8.GenPartonEta);
  //stream.select("subjetAK8_GenPartonPhi", data.subjetsAK8.GenPartonPhi);
  //stream.select("subjetAK8_GenPartonPt", data.subjetsAK8.GenPartonPt);
  //stream.select("subjetAK8_GenPartonE", data.subjetsAK8.GenPartonE);
  //stream.select("subjetAK8_GenPartonCharge", data.subjetsAK8.GenPartonCharge);
  //stream.select("subjetAK8_PartonFlavour", data.subjetsAK8.PartonFlavour);
  //stream.select("subjetAK8_HadronFlavour", data.subjetsAK8.HadronFlavour);
  //stream.select("subjetAK8_GenJetY", data.subjetsAK8.GenJetY);
  //stream.select("subjetAK8_GenJetEta", data.subjetsAK8.GenJetEta);
  //stream.select("subjetAK8_GenJetPhi", data.subjetsAK8.GenJetPhi);
  //stream.select("subjetAK8_GenJetPt", data.subjetsAK8.GenJetPt);
  //stream.select("subjetAK8_GenJetE", data.subjetsAK8.GenJetE);
  //stream.select("subjetAK8_GenJetCharge", data.subjetsAK8.GenJetCharge);
  //stream.select("subjetAK8_muonMultiplicity", data.subjetsAK8.muonMultiplicity);
  //stream.select("subjetAK8_PhotonEnergy", data.subjetsAK8.PhotonEnergy);
  //stream.select("subjetAK8_ElectronEnergy", data.subjetsAK8.ElectronEnergy);
  //stream.select("subjetAK8_MuonEnergy", data.subjetsAK8.MuonEnergy);
  //stream.select("subjetAK8_HFHadronEnergy", data.subjetsAK8.HFHadronEnergy);
  //stream.select("subjetAK8_HFEMEnergy", data.subjetsAK8.HFEMEnergy);
  //stream.select("subjetAK8_ChargedHadronMultiplicity", data.subjetsAK8.ChargedHadronMultiplicity);
  //stream.select("subjetAK8_numberOfDaughters", data.subjetsAK8.numberOfDaughters);
  //stream.select("subjetAK8_chargedMultiplicity", data.subjetsAK8.chargedMultiplicity);
  //stream.select("subjetAK8_neutralHadronMultiplicity", data.subjetsAK8.neutralHadronMultiplicity);
  //stream.select("subjetAK8_neutralHadronEnergy", data.subjetsAK8.neutralHadronEnergy);
  //stream.select("subjetAK8_neutralEmEnergy", data.subjetsAK8.neutralEmEnergy);
  //stream.select("subjetAK8_chargedEmEnergy", data.subjetsAK8.chargedEmEnergy);
  //stream.select("subjetAK8_chargedHadronEnergy", data.subjetsAK8.chargedHadronEnergy);
  //stream.select("subjetAK8_photonMultiplicity", data.subjetsAK8.photonMultiplicity);
  //stream.select("subjetAK8_electronMultiplicity", data.subjetsAK8.electronMultiplicity);
  //stream.select("subjetAK8_HFHadronMultiplicity", data.subjetsAK8.HFHadronMultiplicity);
  //stream.select("subjetAK8_HFEMMultiplicity", data.subjetsAK8.HFEMMultiplicity);
  //stream.select("subjetAK8_ChargeMuEnergy", data.subjetsAK8.ChargeMuEnergy);
  //stream.select("subjetAK8_neutralMultiplicity", data.subjetsAK8.neutralMultiplicity);
  //stream.select("subjetAK8_jecFactor0", data.subjetsAK8.jecFactor0);
  //stream.select("subjetAK8_jetArea", data.subjetsAK8.jetArea);
  //stream.select("subjetAK8_SmearedPt", data.subjetsAK8.SmearedPt);
  //stream.select("subjetAK8_SmearedPEta", data.subjetsAK8.SmearedPEta);
  //stream.select("subjetAK8_SmearedPhi", data.subjetsAK8.SmearedPhi);
  //stream.select("subjetAK8_SmearedE", data.subjetsAK8.SmearedE);
  //stream.select("subjetAK8_JERup", data.subjetsAK8.JERup);
  //stream.select("subjetAK8_JERdown", data.subjetsAK8.JERdown);
  
  //stream.select("subjetsCmsTopTag_size", data.subjetsCmsTopTag.size);
  //stream.select("subjetsCmsTopTag_Mass", data.subjetsCmsTopTag.Mass);			
  //stream.select("subjetsCmsTopTag_Pt", data.subjetsCmsTopTag.Pt);
  //stream.select("subjetsCmsTopTag_Eta", data.subjetsCmsTopTag.Eta);
  //stream.select("subjetsCmsTopTag_Y", data.subjetsCmsTopTag.Y);
  //stream.select("subjetsCmsTopTag_Phi", data.subjetsCmsTopTag.Phi);
  //stream.select("subjetsCmsTopTag_E", data.subjetsCmsTopTag.E);
  //stream.select("subjetsCmsTopTag_Charge", data.subjetsCmsTopTag.Charge);
  //stream.select("subjetsCmsTopTag_CSV", data.subjetsCmsTopTag.CSV);
  //stream.select("subjetsCmsTopTag_CSVV1", data.subjetsCmsTopTag.CSVV1);
  //stream.select("subjetsCmsTopTag_GenPartonY", data.subjetsCmsTopTag.GenPartonY);
  //stream.select("subjetsCmsTopTag_GenPartonEta", data.subjetsCmsTopTag.GenPartonEta);
  //stream.select("subjetsCmsTopTag_GenPartonPhi", data.subjetsCmsTopTag.GenPartonPhi);
  //stream.select("subjetsCmsTopTag_GenPartonPt", data.subjetsCmsTopTag.GenPartonPt);
  //stream.select("subjetsCmsTopTag_GenPartonE", data.subjetsCmsTopTag.GenPartonE);
  //stream.select("subjetsCmsTopTag_GenPartonCharge", data.subjetsCmsTopTag.GenPartonCharge);
  //stream.select("subjetsCmsTopTag_PartonFlavour", data.subjetsCmsTopTag.PartonFlavour);
  //stream.select("subjetsCmsTopTag_HadronFlavour", data.subjetsCmsTopTag.HadronFlavour);
  //stream.select("subjetsCmsTopTag_GenJetY", data.subjetsCmsTopTag.GenJetY);
  //stream.select("subjetsCmsTopTag_GenJetEta", data.subjetsCmsTopTag.GenJetEta);
  //stream.select("subjetsCmsTopTag_GenJetPhi", data.subjetsCmsTopTag.GenJetPhi);
  //stream.select("subjetsCmsTopTag_GenJetPt", data.subjetsCmsTopTag.GenJetPt);
  //stream.select("subjetsCmsTopTag_GenJetE", data.subjetsCmsTopTag.GenJetE);
  //stream.select("subjetsCmsTopTag_GenJetCharge", data.subjetsCmsTopTag.GenJetCharge);
  //stream.select("subjetsCmsTopTag_muonMultiplicity", data.subjetsCmsTopTag.muonMultiplicity);
  //stream.select("subjetsCmsTopTag_PhotonEnergy", data.subjetsCmsTopTag.PhotonEnergy);
  //stream.select("subjetsCmsTopTag_ElectronEnergy", data.subjetsCmsTopTag.ElectronEnergy);
  //stream.select("subjetsCmsTopTag_MuonEnergy", data.subjetsCmsTopTag.MuonEnergy);
  //stream.select("subjetsCmsTopTag_HFHadronEnergy", data.subjetsCmsTopTag.HFHadronEnergy);
  //stream.select("subjetsCmsTopTag_HFEMEnergy", data.subjetsCmsTopTag.HFEMEnergy);
  //stream.select("subjetsCmsTopTag_ChargedHadronMultiplicity", data.subjetsCmsTopTag.ChargedHadronMultiplicity);
  //stream.select("subjetsCmsTopTag_numberOfDaughters", data.subjetsCmsTopTag.numberOfDaughters);
  //stream.select("subjetsCmsTopTag_chargedMultiplicity", data.subjetsCmsTopTag.chargedMultiplicity);
  //stream.select("subjetsCmsTopTag_neutralHadronMultiplicity", data.subjetsCmsTopTag.neutralHadronMultiplicity);
  //stream.select("subjetsCmsTopTag_neutralHadronEnergy", data.subjetsCmsTopTag.neutralHadronEnergy);
  //stream.select("subjetsCmsTopTag_neutralEmEnergy", data.subjetsCmsTopTag.neutralEmEnergy);
  //stream.select("subjetsCmsTopTag_chargedEmEnergy", data.subjetsCmsTopTag.chargedEmEnergy);
  //stream.select("subjetsCmsTopTag_chargedHadronEnergy", data.subjetsCmsTopTag.chargedHadronEnergy);
  //stream.select("subjetsCmsTopTag_photonMultiplicity", data.subjetsCmsTopTag.photonMultiplicity);
  //stream.select("subjetsCmsTopTag_electronMultiplicity", data.subjetsCmsTopTag.electronMultiplicity);
  //stream.select("subjetsCmsTopTag_HFHadronMultiplicity", data.subjetsCmsTopTag.HFHadronMultiplicity);
  //stream.select("subjetsCmsTopTag_HFEMMultiplicity", data.subjetsCmsTopTag.HFEMMultiplicity);
  //stream.select("subjetsCmsTopTag_ChargeMuEnergy", data.subjetsCmsTopTag.ChargeMuEnergy);
  //stream.select("subjetsCmsTopTag_neutralMultiplicity", data.subjetsCmsTopTag.neutralMultiplicity);
  //stream.select("subjetsCmsTopTag_jecFactor0", data.subjetsCmsTopTag.jecFactor0);
  //stream.select("subjetsCmsTopTag_jetArea", data.subjetsCmsTopTag.jetArea);
  //stream.select("subjetsCmsTopTag_SmearedPt", data.subjetsCmsTopTag.SmearedPt);
  //stream.select("subjetsCmsTopTag_SmearedPEta", data.subjetsCmsTopTag.SmearedPEta);
  //stream.select("subjetsCmsTopTag_SmearedPhi", data.subjetsCmsTopTag.SmearedPhi);
  //stream.select("subjetsCmsTopTag_SmearedE", data.subjetsCmsTopTag.SmearedE);
  //stream.select("subjetsCmsTopTag_JERup", data.subjetsCmsTopTag.JERup);
  //stream.select("subjetsCmsTopTag_JERdown", data.subjetsCmsTopTag.JERdown);
  
  // Extra variables
  stream.select("evt_NLep", data.evt.NLep);
  stream.select("evt_NTopHad", data.evt.NTopHad);
  stream.select("evt_NTopLep", data.evt.NTopLep);
  stream.select("evt_NTop", data.evt.NTop);
  stream.select("evt_HtLep", data.evt.HtLep);
  stream.select("evt_HtTop", data.evt.HtTop);
  stream.select("evt_Ht", data.evt.Ht);
  stream.select("evt_HtAll", data.evt.HtAll);
  stream.select("evt_HtEx", data.evt.HtEx);
  stream.select("evt_HtExFr", data.evt.HtExFr);
  stream.select("evt_HtTopFr", data.evt.HtTopFr);
  stream.select("evt_TTHadDR", data.evt.TTHadDR);
  stream.select("evt_TTHadDPhi", data.evt.TTHadDPhi);
  stream.select("evt_TTHadDEta", data.evt.TTHadDEta);
  stream.select("evt_TTHadMass", data.evt.TTHadMass);
  stream.select("evt_TTHadPz", data.evt.TTHadPz);
  stream.select("evt_TTHadHz", data.evt.TTHadHz);
  stream.select("evt_TTHadDPz", data.evt.TTHadDPz);
  stream.select("evt_TTHadMR", data.evt.TTHadMR);
  stream.select("evt_TTHadMTR", data.evt.TTHadMTR);
  stream.select("evt_TTHadR", data.evt.TTHadR);
  //stream.select("evt_TTHadR2", data.evt.TTHadR2); // Calculate instead
  stream.select("evt_MR", data.evt.MR);
  stream.select("evt_MTR", data.evt.MTR);
  stream.select("evt_R", data.evt.R);
  //stream.select("evt_R2", data.evt.R2); // Calculate instead
  stream.select("evt_AK4_MR", data.evt.AK4_MR);
  stream.select("evt_AK4_MTR", data.evt.AK4_MTR);
  stream.select("evt_AK4_R", data.evt.AK4_R);
  //stream.select("evt_AK4_R2", data.evt.AK4_R2); // Calculate instead
  stream.select("evt_weight", data.evt.weight);
  
  stream.select("evt_RunNumber", data.evt.RunNumber);
  //stream.select("evt_LumiBlock", data.evt.LumiBlock);
  //stream.select("evt_EventNumber", data.evt.EventNumber);
  stream.select("evt_npv", data.evt.npv);
  
  stream.select("vtx_size", data.evt.vtx_size);
  stream.select("vtx_z", data.evt.vtx_z);
  stream.select("vtx_rho", data.evt.vtx_rho);
  //stream.select("vtx_chi", data.evt.vtx_chi);
  stream.select("vtx_ndof", data.evt.vtx_ndof);
  
  stream.select("met_NoHF_Pt", data.met.Pt);
  stream.select("met_NoHF_Phi", data.met.Phi);
  stream.select("met_NoHF_Px", data.met.Px);
  stream.select("met_NoHF_Py", data.met.Py);
  
  stream.select("Flag_HBHEIsoNoiseFilterResult", data.evt.Flag_HBHEIsoNoiseFilterResult);
  stream.select("Flag_HBHENoiseFilterResult", data.evt.Flag_HBHENoiseFilterResult);
  stream.select("Flag_HBHENoiseFilterResultRun1", data.evt.Flag_HBHENoiseFilterResultRun1);
  stream.select("Flag_HBHENoiseFilterResultRun2Loose", data.evt.Flag_HBHENoiseFilterResultRun2Loose);
  stream.select("Flag_HBHENoiseFilterResultRun2Tight", data.evt.Flag_HBHENoiseFilterResultRun2Tight);
  stream.select("Flag_trackingFailureFilter", data.evt.Flag_trackingFailureFilter);
  stream.select("Flag_goodVertices", data.evt.Flag_goodVertices);
  stream.select("Flag_CSCTightHaloFilter", data.evt.Flag_CSCTightHaloFilter);
  stream.select("Flag_trkPOGFilters", data.evt.Flag_trkPOGFilters);
  stream.select("Flag_trkPOG_logErrorTooManyClusters", data.evt.Flag_trkPOG_logErrorTooManyClusters);
  stream.select("Flag_EcalDeadCellTriggerPrimitiveFilter", data.evt.Flag_EcalDeadCellTriggerPrimitiveFilter);
  stream.select("Flag_ecalLaserCorrFilter", data.evt.Flag_ecalLaserCorrFilter);
  stream.select("Flag_trkPOG_manystripclus53X", data.evt.Flag_trkPOG_manystripclus53X);
  stream.select("Flag_eeBadScFilter", data.evt.Flag_eeBadScFilter);
  stream.select("Flag_METFilters", data.evt.Flag_METFilters);
  stream.select("Flag_HBHENoiseFilter", data.evt.Flag_HBHENoiseFilter);
  stream.select("Flag_trkPOG_toomanystripclus53X", data.evt.Flag_trkPOG_toomanystripclus53X);
  stream.select("Flag_hcalLaserEventFilter", data.evt.Flag_hcalLaserEventFilter);
  
  stream.select("HLT_AK8PFJet360_TrimMass30", data.evt.HLT_AK8PFJet360_TrimMass30);
  stream.select("HLT_PFJet450", data.evt.HLT_PFJet450);
  stream.select("HLT_PFJet500", data.evt.HLT_PFJet500);
  stream.select("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50", data.evt.HLT_AK8PFHT700_TrimR0p1PT0p03Mass50);
  stream.select("HLT_PFHT750_4Jet", data.evt.HLT_PFHT750_4Jet);
  stream.select("HLT_PFHT750_4JetPt50", data.evt.HLT_PFHT750_4JetPt50);
  stream.select("HLT_ECALHT800", data.evt.HLT_ECALHT800);
  stream.select("HLT_PFHT800", data.evt.HLT_PFHT800);
  stream.select("HLT_PFHT900", data.evt.HLT_PFHT900);
  stream.select("HLT_PFHT350", data.evt.HLT_PFHT350);
  stream.select("HLT_PFHT400", data.evt.HLT_PFHT400);
  stream.select("HLT_PFHT475", data.evt.HLT_PFHT475);
  stream.select("HLT_PFHT600", data.evt.HLT_PFHT600);
  stream.select("HLT_PFHT650", data.evt.HLT_PFHT650);
  stream.select("HLT_PFHT550_4Jet", data.evt.HLT_PFHT550_4Jet);
  stream.select("HLT_PFHT650_4Jet", data.evt.HLT_PFHT650_4Jet);
  stream.select("HLT_Rsq0p25", data.evt.HLT_Rsq0p25);
  stream.select("HLT_Rsq0p30", data.evt.HLT_Rsq0p30);
  stream.select("HLT_RsqMR240_Rsq0p09_MR200_4jet", data.evt.HLT_RsqMR240_Rsq0p09_MR200_4jet);
  stream.select("HLT_RsqMR240_Rsq0p09_MR200", data.evt.HLT_RsqMR240_Rsq0p09_MR200);
  stream.select("HLT_RsqMR270_Rsq0p09_MR200_4jet", data.evt.HLT_RsqMR270_Rsq0p09_MR200_4jet);
  stream.select("HLT_RsqMR270_Rsq0p09_MR200", data.evt.HLT_RsqMR270_Rsq0p09_MR200);
  stream.select("HLT_Mu10_CentralPFJet30_BTagCSV0p5PF", data.evt.HLT_Mu10_CentralPFJet30_BTagCSV0p5PF);
  stream.select("HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p5PF", data.evt.HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p5PF);
  stream.select("HLT_Ele15_IsoVVVL_BTagtop8CSV07_PFHT400", data.evt.HLT_Ele15_IsoVVVL_BTagtop8CSV07_PFHT400);
  stream.select("HLT_Ele15_IsoVVVL_PFHT600", data.evt.HLT_Ele15_IsoVVVL_PFHT600);
  stream.select("HLT_Ele15_PFHT300", data.evt.HLT_Ele15_PFHT300);
  stream.select("HLT_Mu15_IsoVVVL_BTagCSV07_PFHT400", data.evt.HLT_Mu15_IsoVVVL_BTagCSV07_PFHT400);
  stream.select("HLT_Mu15_IsoVVVL_PFHT600", data.evt.HLT_Mu15_IsoVVVL_PFHT600);
  stream.select("HLT_Mu15_PFHT300", data.evt.HLT_Mu15_PFHT300);
  stream.select("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50", data.evt.HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50);
  stream.select("HLT_Mu40_eta2p1_PFJet200_PFJet50", data.evt.HLT_Mu40_eta2p1_PFJet200_PFJet50);
  stream.select("HLT_Mu45_eta2p1", data.evt.HLT_Mu45_eta2p1);
  stream.select("HLT_Mu50", data.evt.HLT_Mu50);
  stream.select("HLT_Ele32_eta2p1_WPLoose_Gsf", data.evt.HLT_Ele32_eta2p1_WPLoose_Gsf);
  stream.select("HLT_Ele32_eta2p1_WPTight_Gsf", data.evt.HLT_Ele32_eta2p1_WPTight_Gsf);
  stream.select("HLT_IsoMu24_eta2p1", data.evt.HLT_IsoMu24_eta2p1);
  stream.select("HLT_IsoMu27", data.evt.HLT_IsoMu27);
  stream.select("HLT_IsoTkMu24_eta2p1", data.evt.HLT_IsoTkMu24_eta2p1);
  stream.select("HLT_IsoTkMu27", data.evt.HLT_IsoTkMu27);
  
  stream.select("jetAK8_HasNearGenTop", data.jetsAK8.HasNearGenTop);
  stream.select("jetAK8_NearGenTopIsHadronic", data.jetsAK8.NearGenTopIsHadronic);
  stream.select("jetAK8_NearGenWIsHadronic", data.jetsAK8.NearGenWIsHadronic);
  stream.select("jetAK8_NearGenWToENu", data.jetsAK8.NearGenWToENu);
  stream.select("jetAK8_NearGenWToMuNu", data.jetsAK8.NearGenWToMuNu);
  stream.select("jetAK8_NearGenWToTauNu", data.jetsAK8.NearGenWToTauNu);
  stream.select("jetAK8_PassTopTag", data.jetsAK8.PassTopTag);
  stream.select("jetAK8_DRNearGenTop", data.jetsAK8.DRNearGenTop);
  stream.select("jetAK8_DRNearGenWFromTop", data.jetsAK8.DRNearGenWFromTop);
  stream.select("jetAK8_DRNearGenBFromTop", data.jetsAK8.DRNearGenBFromTop);
  stream.select("jetAK8_DRNearGenLepFromSLTop", data.jetsAK8.DRNearGenLepFromSLTop);
  stream.select("jetAK8_DRNearGenNuFromSLTop", data.jetsAK8.DRNearGenNuFromSLTop);
  stream.select("jetAK8_PtNearGenTop", data.jetsAK8.PtNearGenTop);
  stream.select("jetAK8_PtNearGenBFromTop", data.jetsAK8.PtNearGenBFromTop);
  stream.select("jetAK8_PtNearGenWFromTop", data.jetsAK8.PtNearGenWFromTop);
  stream.select("jetAK8_PtNearGenLepFromSLTop", data.jetsAK8.PtNearGenLepFromSLTop);
  stream.select("jetAK8_PtNearGenNuFromSLTop", data.jetsAK8.PtNearGenNuFromSLTop);
  
  stream.select("el_DRNearGenEleFromSLTop", data.ele.DRNearGenEleFromSLTop);
  stream.select("el_PtNearGenEleFromSLTop", data.ele.PtNearGenEleFromSLTop);
  stream.select("el_PtNearGenTop", data.ele.PtNearGenTop);
  stream.select("el_IsPartOfNearAK4Jet", data.ele.IsPartOfNearAK4Jet);
  stream.select("el_IsPartOfNearAK8Jet", data.ele.IsPartOfNearAK8Jet);
  stream.select("el_IsPartOfNearSubjet", data.ele.IsPartOfNearSubjet);
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
  
  stream.select("mu_DRNearGenMuFromSLTop", data.mu.DRNearGenMuFromSLTop);
  stream.select("mu_PtNearGenMuFromSLTop", data.mu.PtNearGenMuFromSLTop);
  stream.select("mu_PtNearGenTop", data.mu.PtNearGenTop);
  stream.select("mu_IsPartOfNearAK4Jet", data.mu.IsPartOfNearAK4Jet);
  stream.select("mu_IsPartOfNearAK8Jet", data.mu.IsPartOfNearAK8Jet);
  stream.select("mu_IsPartOfNearSubjet", data.mu.IsPartOfNearSubjet);
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
  */
}
//-----------------------------------------------------------------------------
// -- Utilities
//-----------------------------------------------------------------------------
void
error(std::string message)
{
  std::cout << "** error ** " << message << std::endl;
  exit(0);
}

std::string 
strip(std::string line)
{
  int l = line.size();
  if ( l == 0 ) return std::string("");
  int n = 0;
  while (((line[n] == 0)    ||
	  (line[n] == ' ' ) ||
	  (line[n] == '\n') ||
	  (line[n] == '\t')) && n < l) n++;

  int m = l-1;
  while (((line[m] == 0)    ||
	  (line[m] == ' ')  ||
	  (line[m] == '\n') ||
	  (line[m] == '\t')) && m > 0) m--;
  return line.substr(n,m-n+1);
}

std::string
nameonly(std::string filename)
{
  int i = filename.rfind("/");
  int j = filename.rfind(".");
  if ( j < 0 ) j = filename.size();
  return filename.substr(i+1,j-i-1);
}
//-----------------------------------------------------------------------------
struct outputFile
{
  outputFile(std::string filename)
    : filename_(filename),
      file_(new TFile(filename_.c_str(), "recreate")),
      tree_(0),
      b_weight_(0),
      entry_(0),
      SAVECOUNT_(50000)
  {
    file_->cd();
    hist_ = new TH1D("counts", "", 1,0,1);
    hist_->SetBit(TH1::kCanRebin);
    hist_->SetStats(0);
  }
  
  outputFile(std::string filename, itreestream& stream, int savecount=50000) 
    : filename_(filename),
      file_(new TFile(filename.c_str(), "recreate")),
      tree_(stream.tree()->CloneTree(0)),
      b_weight_(tree_->Branch("eventWeight", &weight_, "eventWeight/D")),
      entry_(0),
      SAVECOUNT_(savecount)
  {
    std::cout << "events will be skimmed to file "
	      << filename_ << std::endl;
    file_->cd();
    hist_ = new TH1D("counts", "", 1,0,1);
    hist_->SetBit(TH1::kCanRebin);
    hist_->SetStats(0);
  }
  
  void addEvent(double weight=1)
  {
    if ( tree_ == 0 ) return;
    
    weight_ = weight;
    file_   = tree_->GetCurrentFile();
    file_->cd();
    tree_->Fill();
    
    entry_++;
    if ( entry_ % SAVECOUNT_ == 0 )
      tree_->AutoSave("SaveSelf");
  }
  
  void count(std::string cond, double w=1.0)
  {
    hist_->Fill(cond.c_str(), w);
  }
  
  void close()
  {
    std::cout << "==> histograms saved to file " << filename_ << std::endl;
    if ( tree_ != 0 )
      {
	std::cout << "==> events skimmed to file " << filename_ << std::endl;
	file_ = tree_->GetCurrentFile();
      }
    file_->cd();
    //file_->Write("", TObject::kWriteDelete);
    file_->Write();
    file_->ls();
    file_->Close();
  }
  
  std::string filename_;  
  TFile* file_;
  TTree* tree_;
  TH1D*  hist_;
  TBranch* b_weight_;
  double     weight_;
  int    entry_;
  int    SAVECOUNT_;
};

struct commandLine
{
  std::string progname;
  std::string filelist;
  double xsect;
  double totweight;
  double lumi;
  std::string outputfilename;
};


void
decodeCommandLine(int argc, char** argv, commandLine& cl)
{
  cl.progname = std::string(argv[0]);

  // 1st (optional) argument
  if ( argc > 1 )
    cl.filelist = std::string(argv[1]);
  else
    cl.filelist = std::string("filelist.txt");
  
  // 2nd (optional) argument
  if ( argc > 2 )
    cl.xsect = atof(argv[2]);
  else
    cl.xsect = -1;
  
  // 3rd (optional) argument
  if ( argc > 3 )
    cl.totweight = atof(argv[3]);
  else
    cl.totweight = -1;
  
  // 4th (optional) argument
  if ( argc > 4 )
    cl.lumi = atof(argv[4]);
  else
    cl.lumi = -1;
  
  // 5th (optional) command line argument
  if ( argc > 5 )
    cl.outputfilename = std::string(argv[5]);
  else
    cl.outputfilename = cl.progname + std::string("_histograms");
  
  // Make sure extension is ".root"
  std::string name = cl.outputfilename;
  if ( name.substr(name.size()-5, 5) != std::string(".root") )
    cl.outputfilename += std::string(".root");
}

// Read ntuple filenames from file list

std::vector<std::string>
getFilenames(std::string filelist)
{
  std::ifstream stream(filelist.c_str());
  if ( !stream.good() ) error("unable to open file: " + filelist);
  
  // Get list of ntuple files to be processed
  
  std::vector<std::string> v;
  std::string filename;
  while ( stream >> filename )
    if ( strip(filename) != "" ) v.push_back(filename);
  return v;
}

#endif
