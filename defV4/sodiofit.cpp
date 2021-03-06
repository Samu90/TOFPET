#include "iostream"
#include "string"
#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "string"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "SourceClass.h"

#define CHID 315

void mainfun(string outputname){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0000);
  
  Source* Sour = new Source("Na22",2);
  TCanvas* canvas = new TCanvas(("HistoSource"+Sour->GetSourceName()).c_str(),("HistoSource"+Sour->GetSourceName()).c_str(),1200,800);

  Sour->GetPlot()->Draw();

  TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x*[4]-(2*[1]*[1]/([1]+2*[1])))) + 1)+ [5] * exp(-( x-[6] )*( x-[6] )/( 2* [7]* [7])) + [8] / (exp( (x*[9]-(2*[6]*[6]/([1]+2*[6])))) + 1)",27,88);

  spectrum->SetParLimits(0,1200,1400);
  spectrum->SetParLimits(1,34,40);
  spectrum->SetParLimits(2,1,5);
  spectrum->SetParLimits(3,400,800);
  spectrum->SetParLimits(4,0.6,1.2);
  spectrum->SetParLimits(5,80,130);
  spectrum->SetParLimits(6,73,76);
  spectrum->SetParLimits(7,1,5);
  spectrum->SetParLimits(8,100,200);
  spectrum->SetParLimits(9,0.6,1.2);
  
  Sour->GetPlot()->Fit("SpectrumFit","R");

  Double_t xmin,xmax;
  
  spectrum->GetRange(&xmin,&xmax);
  
  TF1* gauss1 = new TF1("gauss1","gaus",xmin,xmax);
  TF1* gauss2 = new TF1("gauss2","gaus",xmin,xmax);
  TF1* fd1 = new TF1("fd1","[0] / (exp( (x*[1]-(2*[2]*[2]/([3]+2*[2])))) + 1)",xmin,xmax);
  TF1* fd2 = new TF1("fd2","[0] / (exp( (x*[1]-(2*[2]*[2]/([3]+2*[2])))) + 1)",xmin,xmax);
  
  
  gauss1->FixParameter(0,spectrum->GetParameter(0));
  gauss1->FixParameter(1,spectrum->GetParameter(1));
  gauss1->FixParameter(2,spectrum->GetParameter(2));
  
  gauss2->FixParameter(0,spectrum->GetParameter(5));
  gauss2->FixParameter(1,spectrum->GetParameter(6));
  gauss2->FixParameter(2,spectrum->GetParameter(7));
  
  fd1->FixParameter(0,spectrum->GetParameter(3));
  fd1->FixParameter(1,spectrum->GetParameter(4));
  fd1->FixParameter(2,spectrum->GetParameter(1));
  fd1->FixParameter(3,spectrum->GetParameter(1));

  fd2->FixParameter(0,spectrum->GetParameter(8));
  fd2->FixParameter(1,spectrum->GetParameter(9));
  fd2->FixParameter(2,spectrum->GetParameter(6));
  fd2->FixParameter(3,spectrum->GetParameter(1));

  
  gauss1->SetLineStyle(10);
  gauss1->SetLineColor(kRed);
  gauss2->SetLineStyle(10);
  gauss2->SetLineColor(kBlue);
  fd1->SetLineStyle(10);
  fd1->SetLineColor(kBlack);
  fd2->SetLineStyle(10);
  fd2->SetLineColor(kGreen);
  
  gauss1->Draw("SAME");
  gauss2->Draw("SAME");
  fd1->Draw("SAME");
  fd2->Draw("SAME");
  
  
  canvas->SaveAs(("HistoSource"+Sour->GetSourceName()+outputname+".png").c_str());
  canvas->SaveAs(("HistoSource"+Sour->GetSourceName()+outputname+".pdf").c_str());
  
}
