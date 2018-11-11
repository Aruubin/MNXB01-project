#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
using namespace std;

#include <TH1D.h>
#include <TF1.h>
///////////////////////////////////
///								///
///    Lund weather assesment	///
///								///
///////////////////////////////////



	

int SaeidRootFinal()
{
    
    int x1=57019, x2=5;
    double data[x1][x2], ColdestDay[55][5]={0}, WarmestDay[55][5]={0}, HistFig3_1[55]={0};
    double HistFig3_2[366][2]={0}, HistFig3_1_1[55]={0}, HistFig3_1_2[366][2]={0};
  
  ///////////////////////////////////////////
  //// Extract practical data from "smhi-opendata_Lund.csv" file 
  //// by Bash. Separately prepared Bash file is linked to this file
  ///////////////////////////////////////////
  
  	int SystemTest = system("./ExtractBash.sh");

	if(SystemTest == -1){
		std::cout<<"Data trimming failed"<<endl;
	}
  
  //////////////////////////////////////////////////
  ////		Import extracted data by Bash to C++ arrays and find 
  ////		Coldest and Warmest days in different years
  //////////////////////////////////////////////////  
    /// Year
    ifstream input0("year.txt");
    for (int i=0 ; i<x1 ; i++)
    {
        input0 >> data[i][0];
    }
    
    /// Month
    ifstream input1("month.txt");
    for (int i=0 ; i<x1 ; i++)
    {
        input1 >> data[i][1];
    }
    
    /// Day
    ifstream input2("day.txt");
    for (int i=0 ; i<x1 ; i++)
    {
        input2 >> data[i][2];
    }
    
    /// time
    ifstream input3("time.txt");
    for (int i=0 ; i<x1 ; i++)
    {
        input3 >> data[i][3];
    }
    
    /// temperature
    ifstream input4("temperature_01.txt");
    for (int i=0 ; i<x1 ; i++)
    {
        input4 >> data[i][4];
    }
 
    ////////////////////////////////////////////////////
    //// Find Coldest and Warmest day of each year
    
    for (int i3=0; i3<55 ; ++i3)
    {
        for (int i1=0 ; i1<x1 ; ++i1)
        {
            for (int i2=0 ; i2<x2 ; ++i2)
            {
                if (data[i1][0]==(1961+i3))
                {
                    if (data[i1][4]<ColdestDay[i3][4])
                    {
                        ColdestDay[i3][0]=data[i1][0];
                        ColdestDay[i3][1]=data[i1][1];
                        ColdestDay[i3][2]=data[i1][2];
                        ColdestDay[i3][3]=data[i1][3];
                        ColdestDay[i3][4]=data[i1][4];

                    }
                    else if (data[i1][4]>WarmestDay[i3][4])
                    {
                        WarmestDay[i3][0]=data[i1][0];
                        WarmestDay[i3][1]=data[i1][1];
                        WarmestDay[i3][2]=data[i1][2];
                        WarmestDay[i3][3]=data[i1][3];
                        WarmestDay[i3][4]=data[i1][4];

                    }
                }
            }
        }
    }
    
	///////////////////////////////////////////////////////////////////
    // In this section first 2 files which one of them contain coldest day
    // in each year and the other warmest day in each year with complete 
    // data about corresponding year,month,day,time and temperature are 
    // exported as .txt files then two specific .txt files which are supposed
    // to be used for filling Histogram are generated
    ///////////////////////////////////////////////////////////////////////
    
    // exported coldest days .txt file with extra data
    ofstream out1( "ColdestDays.txt" );
    if( out1.is_open() )
    {
        for (int i1=0 ; i1<55 ; ++i1)
        {
            for (int i2=0 ; i2<5 ; ++i2)
            {
                out1 << ColdestDay[i1][i2] << " ";
            }
                out1 << "\n";
        }
        out1.close();
    }
    
// exported warmest days .txt file with extra data
    ofstream out2( "WarmestDays.txt" );
    if( out2.is_open() )
    {
        for (int i1=0 ; i1<55 ; ++i1)
        {
            for (int i2=0 ; i2<5 ; ++i2)
            {
                out2 << WarmestDay[i1][i2] << " ";
            }
            out2 << "\n";
        }
        out1.close();
    }
    
    
// Data related to Coldest days 
    for (int i1=0; i1<55 ; ++i1)
    {
                if(ColdestDay[i1][1]==1)
                    HistFig3_1[i1]=ColdestDay[i1][2];
                else if(ColdestDay[i1][1]==2)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31;
                else if(ColdestDay[i1][1]==3)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28;
                else if(ColdestDay[i1][1]==4)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31;
                else if(ColdestDay[i1][1]==5)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30;
                else if(ColdestDay[i1][1]==6)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31;
                else if(ColdestDay[i1][1]==7)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30;
                else if(ColdestDay[i1][1]==8)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30+31;
                else if(ColdestDay[i1][1]==9)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30+31+31;
                else if(ColdestDay[i1][1]==10)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30+31+31+30;
                else if(ColdestDay[i1][1]==11)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30+31+31+30+31;
                else if(ColdestDay[i1][1]==12)
                    HistFig3_1[i1]=ColdestDay[i1][2]+31+28+31+30+31+30+31+31+30+31+30;
    }
    
    
    for (int i1=0 ; i1<366 ; ++i1)
    {
        HistFig3_2[i1][0]=i1;
    }
    
    
      for (int i1=0 ; i1<55 ; ++i1)
    {
        for (int i2=0 ; i2<366 ; ++i2)
        {
            if (HistFig3_1[i1]==i2)
            { ++HistFig3_2[i2][1];}
        }
    }
    
    /*    // check point
     for (int i1=0 ; i1<366 ; ++i1)
     cout << HistFig3_2[i1][0] << "  " << HistFig3_2[i1][1] << "\n";
     */
    
    
    
    // export file containing ColdestDays for Hist-Figs to a .txt file
    ofstream out3( "ColdestDaysHist.txt" );
    if( out3.is_open() )
    {
        for (int i1=0 ; i1<366 ; ++i1)
        {
            out3 << HistFig3_2[i1][1] << "\n";
        }
        out3.close();
    }

    
    // Data related to Warmest days
    for (int i1=0; i1<55 ; ++i1)
    {
        if(WarmestDay[i1][1]==1)    // based on month number I find which day in the year it is
            HistFig3_1_1[i1]=WarmestDay[i1][2];
        else if(WarmestDay[i1][1]==2)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31;
        else if(WarmestDay[i1][1]==3)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28;
        else if(WarmestDay[i1][1]==4)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31;
        else if(WarmestDay[i1][1]==5)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30;
        else if(WarmestDay[i1][1]==6)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31;
        else if(WarmestDay[i1][1]==7)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30;
        else if(WarmestDay[i1][1]==8)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30+31;
        else if(WarmestDay[i1][1]==9)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30+31+31;
        else if(WarmestDay[i1][1]==10)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30+31+31+30;
        else if(WarmestDay[i1][1]==11)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30+31+31+30+31;
        else if(WarmestDay[i1][1]==12)
            HistFig3_1_1[i1]=WarmestDay[i1][2]+31+28+31+30+31+30+31+31+30+31+30;
    }
    

    /*  // check point
    for (int i1=0 ; i1<55 ; ++i1)
        cout << HistFig3_1_1[i1] << "\n";
    */
    

    for (int i1=0 ; i1<366 ; ++i1)
    {
        HistFig3_1_2[i1][0]=i1;
    }
    
    
    for (int i1=0 ; i1<55 ; ++i1)
    {
        for (int i2=0 ; i2<366 ; ++i2)
        {
            if (HistFig3_1_1[i1]==i2)
            { ++HistFig3_1_2[i2][1];}
        }
    }

    /*  //check point
    for (int i1=0 ; i1<366 ; ++i1)
        cout << HistFig3_1_2[i1][0] << "  " << HistFig3_1_2[i1][1] << "\n";
     */
    

    
    // export file containing WarmestDays for Hist-Figs to a .txt file
    ofstream out4( "WarmestDaysHist.txt" );
    if( out4.is_open() )
    {
        for (int i1=0 ; i1<366 ; ++i1)
        {
            out4 << HistFig3_1_2[i1][1] << "\n";
        }
        out4.close();
    }
    
    
    ////////////////////////////////////////////////////////////
    //////*    			Histogram Section     */  		////////
    ////////////////////////////////////////////////////////////
       ifstream in1;
   in1.open("WarmestDaysHist.txt");
   
   Float_t y1;
   Int_t nlines1 = 0;
   TFile *f = new TFile("basic01.root","RECREATE");
   TH1F *Warmest = new TH1F("Warmest","Coldest & Warmest Days in Lund;Day of Year;Entries",366,0.5,366.5);
   Warmest->GetXaxis()->CenterTitle("Day of Year");
   Warmest->GetYaxis()->CenterTitle("Entries");

   TNtuple *ntuple1 = new TNtuple("ntuple1","data from ascii file","y1");
   
   while (1) {
      in1 >> y1;
		cout << y1 << endl;
     if (!in1.good()) break;

 Int_t counter0 = nlines1+1;
		Warmest->SetBinContent(counter0, y1);
		nlines1++;
		
   }
   printf(" found %d points\n",nlines1);
   in1.close();
   f->Write();
   
   
   
      ifstream in0;
   in0.open("ColdestDaysHist.txt");
   
   Float_t y0;
   Int_t nlines = 0;
   TFile *f0 = new TFile("basic00.root","RECREATE");
   TH1F *Coldest = new TH1F("Coldest","Coldest Days;Day of Year;Entries",366,0.5,366.5);
   Coldest->GetXaxis()->CenterTitle("Day of Year");
   Coldest->GetYaxis()->CenterTitle("Entries");

   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","y0");
   
   while (1) {
      in0 >> y0;
		cout << y0 << endl;
     if (!in0.good()) break;

 Int_t counter0 = nlines+1;
		Coldest->SetBinContent(counter0, y0);
		nlines++;
   }
   printf(" found %d points\n",nlines);
   in0.close();
   f0->Write();
   
   
   
    	//Use the plot modification given in the skeleton code in order to make the figure neat
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetTitleSize(0.05, "x"); 
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetLabelSize(0.05, "x");
	gStyle->SetLabelSize(0.05, "y");
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.16);

	//Put both Warmest & Coldest Days histograms in one plot
	Warmest->SetLineColor(2);
	Coldest->SetLineColor(4);
	Warmest->Draw("");
	Coldest->Draw("same");
	Coldest->SetLineColor(4);
	Coldest->SetLineWidth(3);
	Warmest->SetLineColor(2);
	Warmest->SetLineWidth(3);
 
	//fit function on histograms
	TF1 *ff1 = new TF1("ff1", "gaus", 1, 366);
	ff1->SetLineColor(1); // 1 = "black" 
	ff1->SetLineWidth(4); 
	ff1->SetLineStyle(1); // 2 = "- - -" }
	Warmest->Fit("ff1", "WL");
	TF1 *ff2 = new TF1("ff2", "gaus", 1, 100);
	ff2->SetLineColor(1); // 1 = "black" 
	ff2->SetLineWidth(4); 
	ff2->SetLineStyle(6); // 2 = "- - -" }
	Coldest->Fit("ff2", "WL");

	TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
	leg->SetFillStyle(0); //Hollow fill (transparent)
	leg->SetBorderSize(0); //Get rid of the border
	leg->AddEntry(Warmest, "Warmest Day", "F"); //Use object title, draw fill
	leg->AddEntry(Coldest, "Coldest Day", "F"); //Use custom title
	Warmest->Draw();
	Coldest->Draw("SAME"); //Draw on top of the existing plot
	leg->Draw(); //Legends are automatically drawn with "SAME"
    
    cout << "\n";
    return 0;
}
