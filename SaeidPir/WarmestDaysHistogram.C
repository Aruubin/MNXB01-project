#include <TH1D.h>
#include <TF1.h>
 
 void WarmestDaysHistogram(){
   
   ifstream in;
   in.open("WarmestDaysHist.txt");
   
   Float_t y;
   Int_t nlines = 0;
   TFile *f = new TFile("basic01.root","RECREATE");
   TH1F *Warmest = new TH1F("Warmest","Coldest & Warmest Days in Lund;Day of Year;Entries",366,0.5,366.5);
   Warmest->SetLineColor(2);

   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","y");
   
   while (1) {
      in >> y;
		cout << y << endl;
     if (!in.good()) break;

 Int_t counter0 = nlines+1;
		Warmest->SetBinContent(counter0, y);
		nlines++;
		
   }
   
   
   printf(" found %d points\n",nlines);

   in.close();
   
   f->Write();
}
