#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void trim()
{
	Int_t systemTest = system("./trimData.sh");
	
	//Test to make sure the system function was successful
	//Otherwise, let us know
	if(systemTest == -1){
		cout << "Data trimming failed" << endl;
	}
}


