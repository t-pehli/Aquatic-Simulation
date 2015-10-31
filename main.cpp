#include <cstdlib>
#include "definitions.txt"
#include <iostream>
#include <cstdio>
#include "objects.h"
#include <windows.h>
#include <time.h>

//#define TABLE_SIZE 60



using namespace std;




int main(int argc, char *argv[])
{ 
     srand ( time(NULL) );
     // Creation af basic arrays
     Organism* Chart[TABLE_SIZE][TABLE_SIZE] = { NULL };      // Main Chart/Map, member interactions are based here
     Organism* Creatures[TABLE_SIZE*TABLE_SIZE] = { NULL };   // Creatures Array, contains all created creatures at any time
     Position FreeSpace[9];                                   // Free Positions Array, used to compute an organism's moves 
     int Population[11] = {0};                                // Population Array, contains the population of every species
     Spill OilSpills[5] = {0};                                // Oil Spill Array, contains info for existing oil spills
     int Deaths[11] = {0};                                    // Deaths Array, contains the number of deaths of every species
     //Simulation Initialization
     int stop=0;    int simSpeed=1000;     int nextC = 0;     int hour=0;
     nextC = start(Chart,Creatures,Population,nextC);

     // Main Loop
     while(stop == 0){
       
        cout << "Hour: " << (2*hour)%24;        
        nextC = step(Chart,Creatures,Population,FreeSpace,Deaths,nextC);
        if (hour%12 == 0){
           cout <<"\t\t\tDay: "<< hour/12 +1  << endl;
           nextC = stepDay(Chart,Creatures,Population,Deaths,OilSpills,nextC);
        }
        else
           cout << endl;
        hour++;
        printPopulation(Population);

        if(GetAsyncKeyState(VK_ESCAPE)!=0 | GetAsyncKeyState(0x050) !=0){
           nextC = menu(Chart,Creatures,Population,Deaths,OilSpills,nextC,&hour,&stop,&simSpeed);
        }
        Sleep(simSpeed);
     }


    return EXIT_SUCCESS;
}

