#include <fstream>
#include <iostream>

using namespace std;

#include "tempTrender.h"

tempTrender::tempTrender(string filePath) {
	ifstream file(filePath.c_str());
	string helpString;
	while(file >> helpString)
	{
		if (helpString.find("UTC") != string::npos) 
		{
			break;
		}
		
	}
	while(file >> helpString)
	{
		string firstTwo = helpString.substr(0,2);
		if (firstTwo == "19" || firstTwo == "20")
		{
			string date = helpString.substr(0,10);
			string hour = helpString.substr(11,2);
			string rest = helpString.substr(20);
			
			cout << date << endl;
		} 
	}
	
	//cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	//cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
	file.close();
}
