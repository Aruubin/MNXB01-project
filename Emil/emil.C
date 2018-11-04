#include <iostream>
#include <fstream>

using namespace std;

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void each_day(Int_t year){
	
	Int_t yearCount = 0; //counter
	Int_t readYear = -1;
	Int_t month = -1;
	Int_t day = -1;
	Int_t readHour = -1;
	Double_t temp = -1.0;
	string quality;
	
	string helpString; //help variable
	
	//open input file
	ifstream infile("smhi_opendata_Lund.csv");
	
	ofstream file("example.csv");
	
	char c;
	Int_t line_no = 1;
	while(infile.get(c)){
		
		if(line_no > 12){
			file << c;
		}
		
		if(&c == "\n"){
			line_no++;
			cout << "new line" << endl;
		}
	}
	
	file.close();
	
	infile.close();
	
	//while(file >> year >> helpString >> month >> helpString >> day){
		
		//cout << "yas" << endl;
		//file >> helpString >> helpString_2;
		//if(helpString == "1961-01-01"){
			//cout << "hello" << endl;
		//}
		
		//yearCount ++;
		
		//string cool = "1961-01-01";
		
		//if(file >> cool){
			//break;}
	//}
}

