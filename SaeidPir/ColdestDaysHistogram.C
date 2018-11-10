#include <TH1D.h>
#include <TF1.h>
 
 void ColdestDaysHistogram(){
   
   ifstream in;
   in.open("ColdestDaysHist.txt");
   
   Float_t y;
   Int_t nlines = 0;
   TFile *f0 = new TFile("basic00.root","RECREATE");
   TH1F *Coldest = new TH1F("Coldest","Coldest Days;Day of Year;Entries",366,0.5,366.5);
   Coldest->SetLineColor(4);

   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","y");
   
   while (1) {
      in >> y;
		cout << y << endl;
     if (!in.good()) break;

 Int_t counter0 = nlines+1;
		Coldest->SetBinContent(counter0, y);
		nlines++;
   }
   
   
   printf(" found %d points\n",nlines);

   in.close();
   
   f0->Write();
}
