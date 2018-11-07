#include <iostream>

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TROOT.h>
#include <TRint.h>
#include <THStack.h>

#include "ReadVisby.C"
#include "ReadBoras.C"

using namespace std;

void Visby_comparison(){
	
	gStyle->SetOptStat(0); //Let's make our plots look a bit better. Get rid of the stat box
	gStyle->SetOptTitle(0); //Get rid of the title (good plots use legends instead)
	gStyle->SetTitleSize(0.05, "x"); //Use bigger text on the axes
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetLabelSize(0.05, "x"); //Use bigger labels too
	gStyle->SetLabelSize(0.05, "y");
	gStyle->SetPadTopMargin(0.05); //Change the margins to fit our new sizes
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.16);
	
	gROOT->ProcessLine(".L DataTrimVisby.C+");
	gROOT->ProcessLine(".L ReadVisby.C+");
	gROOT->ProcessLine(".L DataTrimBoras.C+");
	gROOT->ProcessLine(".L ReadBoras.C+");
	
	TCanvas* c1 = new TCanvas("c1", "c1", 900, 600);
	
	Visby_hist();
	Boras_hist();
	
	THStack *hs = new THStack("hs","");
	hVisby->SetFillColor(kRed);
	hs->Add(hVisby);
	hBoras->SetFillColor(kGreen);
	hs->Add(hBoras)
	
	TCanvas *cs = new TCanvas("cs","cs",10,10,700,900);
	cs->cd; hs->Draw("nostack"); T.DrawTextNDC(.5,.95,"Comparison of Visby and Boras");
	
	
}
