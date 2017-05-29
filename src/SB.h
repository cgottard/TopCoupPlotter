//
// Created by Carlo A. Gottardo on 26/09/16.
//

#ifndef VALIDATION_SB_H
#define VALIDATION_SB_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "AtlasStyle.h"
#include "AtlasUtils.h"
#include "AtlasLabels.h"
#include <stdlib.h>
#include <stdio.h>
#include "TColor.h"
#include <TString.h>
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "THStack.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include <vector>
#include "AtlasStyle.h"
class SB {

private:
std::string label = "";
std::string tcut = "";

std::map<std::string, TH1F> histos = {
  std::make_pair<std::string, TH1F>("nleptons",     {"nlep", "Leptons number; #font[52]{Lepton multiplicity}; Events", 12, 0, 12}),
  std::make_pair<std::string, TH1F>("nJets",        {"nJets", "Jets multiplicity; #font[52]{Jet ultiplicity}; Events ", 10, 0, 10}),
  std::make_pair<std::string, TH1F>("bdt",          {"bdt", "BDT score; #font[52]{BDT score}; Events", 40, -0.4, 0.4}),
  std::make_pair<std::string, TH1F>("lep1",         {"pT_1lep", "lepton 1 pT; #font[52]{p}_{T} [GeV]; Events", 30, 0, 300}),
  std::make_pair<std::string, TH1F>("lep2",         {"pT_2lep", "lepton 2 pT; #font[52]{p}_{T} [GeV]; Events", 30, 0, 300}),
  std::make_pair<std::string, TH1F>("lep3",         {"pT_3lep", "lepton 3 pT; #font[52]{p}_{T} [GeV]; Events", 30, 0, 300}),
  std::make_pair<std::string, TH1F>("nMu",        {"nMu", "Muon multiplicity", 6, 0, 6}),
  std::make_pair<std::string, TH1F>("t1lj_pt",        {"pT1_jets", "#font[52]{LFV light jet }#font[52]{p}_{T} [GeV]", 30, 0, 300}),
  std::make_pair<std::string, TH1F>("t2bj_pt",        {"pT2_jets", "#font[52]{SM b-jet }#font[52] {p}_{T} [GeV]", 30, 0, 300}),
  std::make_pair<std::string, TH1F>("el_orig",        {"el_orig", "#font[52]{Fake electrons truth origin}; TruthOrigin; Events", 45, 0, 45}),
  std::make_pair<std::string, TH1F>("mu_orig",        {"mu_orig", "#font[52]{Fake muon truth origin}; TruthOrigin; Events", 45, 0, 45}),
//for BDT
 std::make_pair<std::string, TH1F>("t1_m",          {"t1_m", "LFV top mass; LFV top mass [GeV]; Events", 40, 0, 400}),
 std::make_pair<std::string, TH1F>("t2_m",          {"t2_m", "SM top mass; SM top mass [GeV]; Events", 35, 50, 400}),
 std::make_pair<std::string, TH1F>("mll",           {"OSSF", "OSSF mass;  #font[52]{m}_{ll} [GeV]; Events", 32, 0, 160}),
 std::make_pair<std::string, TH1F>("nBJets",        {"nBJets", "bJets multiplicity; b-Jets multiplicity; Events", 4, 0, 4}),
 std::make_pair<std::string, TH1F>("t1m_pt",        {"t1m_pt", "LFV muon p_{T}; LFV muon  #font[52]{p}_{T} [GeV]; Events", 50, 0, 250}),
 std::make_pair<std::string, TH1F>("t1e_pt",        {"t1e_pt", "LFV electron p_{T};LFV electron  #font[52]{p}_{T} [GeV]; Events", 50, 0, 250}),
 std::make_pair<std::string, TH1F>("eT_miss",       {"eT_miss", "eT_{miss}; #font[52]{E}_{T}^{miss} [GeV]; Events", 30, 0, 300}),
 std::make_pair<std::string, TH1F>("ht",           {"ht", "p_{T} scalar sum (e,#mu,jets); #font[52]{H}_{T} [GeV]; Events", 40, 0, 1200})
};

public:
  SB(std::string lab);
  TH1F* GetHist(std::string name){return &histos.at(name);}
  std::string GetName(){return label;}
  void PrintHist(std::string label);
  friend void PlotSB(std::vector<SB> & samples, std::string reg_lab, std::string folder);
  
};


#endif //VALIDATION_SB_H
