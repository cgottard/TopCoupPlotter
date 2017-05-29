#include <iostream>
#include "TLorentzVector.h"
#include "SB.h"
#include "nominal.h"
#include "TEntryList.h"

using namespace std;

void SB_func(string cut, string reg_label, string folder);

bool desc_sort(float i, float j) { return i > j; }
bool asc_sort(float i, float j) { return i < j; }


int main()
{
 string TRIG = "(hasTrigMatchedEl || hasTrigMatchedMu)";
 string VAL = "(hasTrigMatchedEl || hasTrigMatchedMu) && ((nEl==3 && nMu==0) || (nEl==0 && nMu==3))  && nJets>0 && pT_1lep>27.0 && Alt$(OSSF_M[0]>15.0, 1) && Alt$(OSSF_M[1]>15.0, 1)";

// selector
 //*******************************
 string tcut = VAL;
 string reg_lab = "(eee, >0j) Sherpa221";
 string folder = "AllSherpa221";
 //*******************************
 
  string command = "mkdir -p ./"+folder;
  const int dir_err = system(command.c_str());
 
 SB_func(tcut, reg_lab , folder);
return 0;
}


void SB_func(string cut, string reg_label, string folder) {
  
  vector<SB> samples;
  string label = "";string in_file = "";
  ifstream f_list; f_list.open("sb.txt", ios::in);
  float weight{0.};
  
  while (true) {
    nominal N;
    f_list >> label >> in_file;
    if(f_list.eof()) break;
    samples.push_back(SB(label));
    cout << "Reading: " << in_file << ", label " << label << endl;

    TFile *temp = new TFile(in_file.c_str(), "READ");
    N.Init((TTree *)temp->Get("nominal"));
    N.fChain->Draw(">>eventlist", cut.c_str(), "entrylist");
    TEntryList *elist = (TEntryList *)gDirectory->Get("eventlist");
    N.fChain->SetEntryList(elist);
    long nEvents = elist->GetN();
    cout << "DEBUG: events " << nEvents << endl;
    for (Long64_t i = 0; i < nEvents; ++i) {
      N.fChain->GetEntry(elist->GetEntry(i));
      

        weight = N.xs_weight * N.weight_mc * N.weight_jvt * N.weight_leptonSF * N.weight_bTagSF_77 * N.weight_pileup * 36470.16;
        samples.back().GetHist("nleptons")->Fill((N.nEl + N.nMu), weight);
        samples.back().GetHist("nJets")->Fill(N.nJets, weight);
        samples.back().GetHist("nBJets")->Fill(N.nBJets77, weight);
        samples.back().GetHist("eT_miss")->Fill(N.met_met / 1000., weight);
        samples.back().GetHist("ht")->Fill(N.ht, weight);
        samples.back().GetHist("lep1")->Fill(N.pT_1lep, weight);
        samples.back().GetHist("lep2")->Fill(N.pT_2lep, weight);
        samples.back().GetHist("lep3")->Fill(N.pT_3lep, weight);
        samples.back().GetHist("t1_m")->Fill(N.t1_m, weight);
        samples.back().GetHist("t2_m")->Fill(N.t2_m, weight);
        samples.back().GetHist("t1m_pt")->Fill(N.t1m_pt, weight);
        samples.back().GetHist("t1e_pt")->Fill(N.t1e_pt, weight);
        samples.back().GetHist("bdt")->Fill(N.BDT, weight);
        samples.back().GetHist("mll")->Fill(N.mll, weight);
        samples.back().GetHist("t1lj_pt")->Fill(N.t1lj_pt, weight);
        samples.back().GetHist("t2bj_pt")->Fill(N.t2bj_pt, weight);

    }
  }
  PlotSB(samples, reg_label, folder);

return;
}
