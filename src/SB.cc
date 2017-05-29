//
// Created by Carlo A. Gottardo on 26/09/16.
//

#include "SB.h"

using namespace std;

SB::SB(string lab){label=lab;}

void SB::PrintHist(string label) {
  string out_file = "hist_" + label + ".root";
  TFile *output = new TFile(out_file.c_str(), "RECREATE");

  for (auto const &ent : histos) {
    ent.second.Write();
  }
  output->Write();
  output->Close();
  delete output;
  return;
}
//grey 13

void PlotSB(vector<SB> & samples, string reg_lab, string folder)
{
  int palette[18];
  palette[0] = 1; palette[1] = 2; palette[2] = 3; palette[3] = 4;
  palette[4] = 5; palette[5] = 6; palette[6] = 7; palette[7] = 8;
  palette[8] = 64; palette[9] = 874; palette[10] = 9; palette[11] = 808;
  palette[12] = 840; palette[13] = 30;palette[14] = 901; palette[15] = 32;
  palette[16] = 58; palette[17] = 60;
  stringstream ylabel;

  for (auto &histo : samples[0].histos) //for each variable
  {
    string variable = histo.first;
    string units = " GeV";
    if (strcmp(variable.c_str(), "bdt")==0 || strcmp(variable.c_str(), "nBJets")==0 || strcmp(variable.c_str(), "mu_orig")==0 || strcmp(variable.c_str(), "el_orig")==0 ) units = "";
    gStyle->SetOptStat(0);
    SetAtlasStyle();
    TCanvas *c = new TCanvas("plot", "plot",0.,0.,600,600);
    TLegend *legend=new TLegend(0.60,0.68,0.92,0.92);
    legend->SetBorderSize(0);  // no border
    legend->SetNColumns(2);
    legend->SetTextSize(0.03);
    legend->SetTextFont(42);
    THStack *hs = new THStack("hs","hs");
   
    for(int i=1; i<samples.size(); ++i) //for each sample
    {
      cout << "Stacking: "<<samples[i].GetName() << endl;
      samples[i].GetHist(variable)->SetLineColor(kBlack);
      samples[i].GetHist(variable)->GetYaxis()->SetTitle("Events");
      samples[i].GetHist(variable)->SetFillColor(palette[i]);
      hs->Add(samples[i].GetHist(variable));
      legend->AddEntry(samples[i].GetHist(variable),samples[i].GetName().c_str() ,"f");
    }
    float max = hs->GetMaximum();
    hs->SetMaximum(1.3*max);
    hs->SetTitle(samples[0].GetHist(variable)->GetTitle());
    hs->Draw("HIST");

  
    ylabel.str("");
    ylabel << "Events / " << samples[0].GetHist(variable)->GetXaxis()->GetBinWidth(1) << units;
	  samples[0].GetHist(variable)->SetLineColor(kBlack);
	  samples[0].GetHist(variable)->SetLineWidth(6);
	  samples[0].GetHist(variable)->GetYaxis()->SetTitle(ylabel.str().c_str());
	  samples[0].GetHist(variable)->Draw("HIST SAME");
      samples[0].GetHist(variable)->SetFillStyle(3005);
	  hs->GetXaxis()->SetTitle(samples[0].GetHist(variable)->GetXaxis()->GetTitle());
    hs->GetYaxis()->SetTitle(samples[0].GetHist(variable)->GetYaxis()->GetTitle());
    legend->AddEntry(samples[0].GetHist(variable),"Signal" ,"l");
    legend->Draw();
    ATLASLabel(0.20,0.90,"Internal",1);
    myText(0.2,0.85,1,"#sqrt{s}= 13 TeV, 36.5 fb^{-1}");
    myText(0.2,0.80,1,reg_lab.c_str());
	  c->Update();
    string pdfname = "./"+folder+"/"+variable+".pdf";
	  c->SaveAs(pdfname.c_str());
  
    delete hs;
    delete legend;
    delete c;
  }
}
