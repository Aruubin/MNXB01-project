#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//Use the bash script to trim the data file
void trimBoras()
{
	Int_t SystemTest = system("./DataTrimBoras.sh");
	
	//Test to make sure the system function was successful
	//Otherwise, let us know
	if(SystemTest == -1){
		std::cout<<"Data trimming failed"<<endl;
	}
}
