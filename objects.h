#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>
#include "definitions.txt"

//#define TABLE_SIZE 60



using namespace std;

// Organism position structure
struct Position {
     int x;
     int y;
};


// Oil spill structure
struct Spill {
     Position pos;
     int size;
     int duration;
};


// Top-level class for all organisms
class Organism
{
	public:
		// class constructor
		Organism();
		
        // class methods
		// Randomize Method, places new organisms at random free places in Chart Array
        void randomize( Organism* Chart[TABLE_SIZE][TABLE_SIZE]);
        // Place Method, places new organisms at user's input places in Chart Array
        int place( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Position);
        // Move Method, computes the way an organism moves/eats
        void move( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE] , Position FreeSpace[9], int Population[11], int Deaths[11]);
        // Grow Method, computes size changes of organisms daily based on food consumption
        void grow( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE], int Population[11], int Deaths[11]);
        // Mate Method, handles mate-finding for reproducion
        void mate( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE]);
        // Reproduce Method, handles creation of organisms after reproduction
        int reproduce( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE], int Population[11],int nextC);
        // 
        void setOrder(int);
        // 
        void setSize(double);
        // Print Method, prints info about organism
        void print();
        //
        string getInfo();
        //
        double getSize();
        //
        double getFood();
        //
        Position getPos();
        //
        int getRank();
        //
        int getAge();
        //
        int getOrder();
        						
    protected:
        //  class variables
        int movesMade;
        int sex;
		int rank;
        int order; 
        int mated;
        int age;
   		double food;
		double growth;
		int speed;
		int maxSize;
		int maxAge;
        Position pos;
        string info;
		int foodNeeded;
		double size;
		
};

// Planktonic
class Planktonic : public Organism {
	public:
		// class constructor
		Planktonic();
            
};

// Non Planktonic
class NonPlanktonic : public Organism {
	public:
		// class constructor
		NonPlanktonic();
    
};

// Shark
class Shark : public NonPlanktonic {
	public:
		// class constructor
		Shark(int Population[11]);
						 
        
};

// Dolphin
class Dolphin : public NonPlanktonic {
	public:
		// class constructor
		Dolphin(int Population[11]);
						
};
// Turtle
class Turtle : public NonPlanktonic {
	public:
		// class constructor
		Turtle(int Population[11]);
						
};
// Tuna
class Tuna : public NonPlanktonic {
	public:
		// class constructor
		Tuna(int Population[11]);
						
};

// Mullet
class Mullet : public NonPlanktonic {
	public:
		// class constructor
		Mullet(int Population[11]);
						
};
// Sardine
class Sardine : public NonPlanktonic {
	public:
		// class constructor
		Sardine(int Population[11]);
						
};
// Octopus
class Octopus : public NonPlanktonic {
	public:
		// class constructor
		Octopus(int Population[11]);
						
};

// Shrimp
class Shrimp : public NonPlanktonic {
	public:
		// class constructor
		Shrimp(int Population[11]);
						
};

// Jellyfish
class Jellyfish : public NonPlanktonic {
	public:
		// class constructor
		Jellyfish(int Population[11]);
						
};

// Phytoplankton
class Phytoplankton : public Planktonic {
	public:
		// class constructor
		Phytoplankton();
						
};

// Zooplankton
class Zooplankton : public Planktonic {
	public:
		// class constructor
		Zooplankton();
						
        //  class variables    
};

// Simualation Start Function, initializes the simulation
int start( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] , int);
// NextCreature Function, used to find the next free slot in the Creatures Array
int nextCreature(Organism* Creatures[TABLE_SIZE*TABLE_SIZE] , int);
// Create Function, used to create any organism
int create( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11], int, int, Position);
// Plankton Function, used to produce plankton daily
int plankton( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11], int);
// Step Function, performs all action within a simulation step
int step( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11], Position FreeSpace[9], int Deaths[11], int);
// Daily Step Function, performs all action at the end of a Simulation Day
int stepDay( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11], int Deaths[11], Spill OilSpills[5], int);
// Menu Function, handles menu input/ output and user interaction
int menu (Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] ,int Deaths[11],Spill OilSpills[5], int, int*, int*, int*);
// Print Population Function, prints all organism populations
void printPopulation(int Population[11]);
// Range Check Function, checks if input is within given range
int rangeCheck(string);
// Find Function, searches Creatures table for objects of given type
Organism* find(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int,int*);
// Average Size Function, calculates the average size of a species
double avgSize(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int,int*);
// Average Food Function, calculates the average food of a species
double avgFood(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int,int*);
//Average Age Function, calculates the average age of a species
double avgAge(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int,int*);
// Harpoon Function, controls the use of the harpoon
void harpoon(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position);
// Fishnet Function, controls the use of the fishnet
void fishnet(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position,int);
// Oil Spill Function, controls the use of the oil spill
void oilSpill(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position,int);
#endif // OBJECTS_H
