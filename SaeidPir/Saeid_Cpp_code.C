#include <iostream>    //this code is for C++ compiler not for root
#include <stdio.h>		//this code is for C++ compiler not for root
#include <ctype.h>		//this code is for C++ compiler not for root
#include <math.h>		//this code is for C++ compiler not for root
#include <stdlib.h>		//this code is for C++ compiler not for root
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

// Lund weather assesment

// import year data into c++ in year[] char format


int main()
{
    
    int x1=57019, x2=5;
    double data[x1][x2], ColdestDay[55][5]={0}, WarmestDay[55][5]={0}, HistFig3_1[55]={0};
    double HistFig3_2[366][2]={0}, HistFig3_1_1[55]={0}, HistFig3_1_2[366][2]={0};
    
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
 
    
    
    /// Find Coldest and Warmest day of each year
    
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
    

    // export file containing Coldest and Warmest day of each year to a .txt file
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
    
    
    // export file containing Warmest day of each year to a .txt file
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
    
    /////////////////////////////// Data for histogram-Fig.3
    
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
    ofstream out3( "ColdestDays-Hist-Fig3.txt" );
    if( out3.is_open() )
    {
        for (int i1=0 ; i1<366 ; ++i1)
        {
            out3 << HistFig3_2[i1][0] << "  " << HistFig3_2[i1][1] << "\n";
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
    ofstream out4( "WarmestDays-Hist-Fig3.txt" );
    if( out4.is_open() )
    {
        for (int i1=0 ; i1<366 ; ++i1)
        {
            out4 << HistFig3_1_2[i1][0] << "  " << HistFig3_1_2[i1][1] << "\n";
        }
        out4.close();
    }
    
    
    cout << "\n";
    return 0;
}
