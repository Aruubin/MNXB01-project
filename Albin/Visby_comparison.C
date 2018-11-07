#include <iostream>

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TROOT.h>
#include <TRint.h>

#include "ReadVisby.C"
#include "rootlogon_Visby.C"

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
	
	TCanvas* c1 = new TCanvas("c1", "Temp canvas", 900, 600);
	
	Visby_hist();
	
}
