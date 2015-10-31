#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "definitions.txt"
#include "objects.h"

/*
#define TABLE_SIZE 60
#define SHARK 10
#define DOLPHIN 9
#define TURTLE 8
#define TUNA 7
#define MULLET 6
#define SARDINE 5
#define OCTOPUS 4
#define SHRIMP 3
#define JELLYFISH 2
#define ZOOPLANKTON 1
#define PHYTOPLANKTON 0
*/


using namespace std;

Organism::Organism(){
             //initialise common Organism data
             movesMade = 0;
             age = 0;
             food = foodNeeded;
                       }

NonPlanktonic::NonPlanktonic (){
                           }
                           
Planktonic::Planktonic (){
                           }

Shark::Shark (int Population[11]){
             //initialise Shark's data
             maxSize = 1000;
             growth = 0.04;
             speed = 10;
             size = maxSize / 2;
             info = "Shark";
             foodNeeded = maxSize / 12;
             maxAge = maxSize / 20; 
             rank = 10;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}
             
Dolphin::Dolphin (int Population[11]){
             //initialise Dolphin's data
             maxSize = 900;
             growth = 0.04;
             speed = 10;
             size = maxSize / 2;
             info = "Dolphin";
             foodNeeded = maxSize / 12;
             maxAge = maxSize / 20; 
             rank = 9;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Turtle::Turtle (int Population[11]){
             //initialise Turtle's data
             maxSize = 700;
             growth = 0.03;
             speed = 4;
             size = maxSize / 2;
             info = "Turtle";
             foodNeeded = maxSize / 16;
             maxAge = maxSize / 20; 
             rank = 8;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Tuna::Tuna (int Population[11]){
             //initialise Tuna's data
             maxSize = 500;
             growth = 0.03;
             speed = 7;
             size = maxSize / 2;
             info = "Tuna";
             foodNeeded = maxSize / 10;
             maxAge = maxSize / 20; 
             rank = 7;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Mullet::Mullet (int Population[11]){
             //initialise Mullet's data
             maxSize = 300;
             growth = 0.02;
             speed = 6;
             size = maxSize / 2;
             info = "Mullet";
             foodNeeded = maxSize / 12;
             maxAge = maxSize / 20; 
             rank = 6;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Sardine::Sardine (int Population[11]){
             //initialise Sardine's data
             maxSize = 200;
             growth = 0.02;
             speed = 6;
             size = maxSize / 2;
             info = "Sardine";
             foodNeeded = maxSize / 12;
             maxAge = maxSize / 20; 
             rank = 5;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Octopus::Octopus (int Population[11]){
             //initialise Octopus's data
             maxSize = 200;
             growth = 0.02;
             speed = 5;
             size = maxSize / 2;
             info = "Octopus";
             foodNeeded = maxSize / 18;
             maxAge = maxSize / 20; 
             rank = 4;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Shrimp::Shrimp (int Population[11]){
             //initialise Shrimp's data
             maxSize = 100;
             growth = 0.02;
             speed = 8;
             size = maxSize / 2;
             info = "Shrimp";
             foodNeeded = maxSize / 14;
             maxAge = maxSize / 20; 
             rank = 3;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Jellyfish::Jellyfish (int Population[11]){
             //initialise Jellyfish's data
             maxSize = 100;
             growth = 0.01;
             speed = 5;
             size = maxSize / 2;
             info = "Jellyfish";
             foodNeeded = maxSize / 18;
             maxAge = maxSize / 20; 
             rank = 2;
             sex= 1+ ((Population[rank]+2) % 2);
             mated =1;
}

Zooplankton::Zooplankton (){
             //initialise Zooplankton's data
             maxSize = 60;
             growth = 0.01;
             speed = 2;
             size = maxSize / 2;
             info = "Zooplankton";
             foodNeeded = maxSize / 16;
             maxAge = maxSize / 20; 
             rank = 1;
             sex=0;
             mated=1;
}

Phytoplankton::Phytoplankton (){
             //initialise Phytoplankton's data
             maxSize = 60;
             growth = 0.01;
             speed = 2;
             size = maxSize / 2;
             maxAge = maxSize / 20; 
             info = "Phytoplankton";
             foodNeeded = 0;
             rank = 0;
             sex=0;
             mated=1;
}


void Organism::randomize( Organism* Chart[TABLE_SIZE][TABLE_SIZE]){    
     Position target;
     do{
        target.x = rand() % TABLE_SIZE;
        target.y = rand() % TABLE_SIZE;
     }while(Chart[target.x][target.y] != NULL);
     Chart[target.x][target.y] = this;
     pos = target;
}


int Organism::place( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Position target){   
     if(Chart[target.x][target.y] == NULL){
        Chart[target.x][target.y] = this;
        pos = target;
        return 0;
     }
     else
        return 1;
}


void Organism::move( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE] , Position FreeSpace[9], int Population[11], int Deaths[11]){
     FreeSpace[0].x = 0;
     FreeSpace[0].y = 0;
     int i,j,k=1,nextmove;
     int br_l=-1,br_r=1,br_u=-1,br_d=1;
     Position target;
     Organism* toEat = NULL;
     movesMade++;
     // Set Motion Limits
     if(movesMade%(12/speed) == 0){
        if(pos.x==0)
           br_l=0;
        if(pos.x==TABLE_SIZE-1)
           br_r=0;
        if(pos.y==0)
           br_u=0;
        if(pos.y==TABLE_SIZE-1)
           br_d=0;
     // Calculate Free Motion Space
     for(i=br_l;i<=br_r;i++)
        for(j=br_u;j<=br_d;j++){
           if(Chart[pos.x+i][pos.y+j]==NULL){
              FreeSpace[k].x = i;
              FreeSpace[k].y = j;
              k++;
           }
           else{
     // Determine Possible Edible Targets
              if(rank > Chart[pos.x+i][pos.y+j]->rank & (rank-6) < Chart[pos.x+i][pos.y+j]->rank)
                 toEat = Chart[pos.x+i][pos.y+j];
        }
     }
     // Move
     if(food>foodNeeded|toEat==NULL){
        nextmove = rand() % k;
        target.x = FreeSpace[nextmove].x + pos.x;
        target.y = FreeSpace[nextmove].y + pos.y;
        Chart[pos.x][pos.y] = NULL;
        pos = target;
        Chart[pos.x][pos.y] = this;}
     // Eat
     else if(food<foodNeeded & toEat !=NULL){
        target = toEat->pos;
        food+= toEat->size;
        Population[toEat->rank]--;
        Deaths[toEat->rank]++;                
        Chart[pos.x][pos.y] = NULL;
        Creatures[toEat->order] = NULL;
        toEat = NULL;
        pos = target;
        Chart[pos.x][pos.y] = this;
     }
   }
}


void Organism::grow( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE], int Population[11], int Deaths[11]){

     age ++;

     // Compute Size
     if(food>=foodNeeded | rank==0)
        if (size<maxSize)
           size += growth*size;
     else
        size -= (foodNeeded-food);      
     food=0;
     
     // Handle Death
     if(size<=0 | age>=maxAge){
         Population[rank]--;
         Deaths[rank]++;
         Creatures[order] = NULL;
         Chart[pos.x][pos.y] = NULL;
     }
}


void Organism::mate( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE]){
     int i,j;     
     int br_l=-1,br_r=1,br_u=-1,br_d=1;
     // Set Limits
     if(pos.x==0)
        br_l=0;
     if(pos.x==TABLE_SIZE-1)
        br_r=0;
     if(pos.y==0)
        br_u=0;
     if(pos.y==TABLE_SIZE-1)
        br_d=0;
     // Determine if mating is possible and set needed values
     for(i=br_l;i<=br_r;i++)
        for(j=br_u;j<=br_d;j++)
           if(Chart[pos.x+i][pos.y+j]!=NULL)
              if (Chart[pos.x+i][pos.y+j]->rank==rank)
                 if(Chart[pos.x+i][pos.y+j]->sex + sex==3)
                    if(Chart[pos.x+i][pos.y+j]->mated==0 & mated==0){     
                       mated =1;
                       Chart[pos.x+i][pos.y+j]->mated=2;
                        j=br_d;
                        i=br_r;
                    }                                     
}


int Organism::reproduce( Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE], int Population[11],int nextC){
     int r;
     Position inputPos;
     inputPos.x=-1; 
     inputPos.y=-1;
     // If mating was possible reproduce
     if(sex>0){
        if(mated==2 & Population[rank]<8 + 6*(10-rank)){
           r= (11-rank)*4/7 + rand()%(12-rank);
           for(int z=0;z<=r;z++)
              nextC = create(Chart,Creatures,Population,nextC,rank,inputPos);
           mated--;
        }
        else if (mated ==1)
           mated--;     
     }
     return nextC;
}


void Organism::setOrder(int target){
     order = target;
}


void Organism::setSize(double target){
     size = target;
}


void Organism::print(){    
     cout << info << " in position ("<<pos.x <<"."<<pos.y<<"), is "<<age<<" days old.\nHas a size of "<< size <<", growth rate of ";
     cout << growth << ", food needed in a week "<<foodNeeded*7<<".\nHas eaten today: "<<food<<endl;
}


string Organism::getInfo(){
       return info;
}


int Organism::getRank(){
       return rank;
}


int Organism::getAge(){
       return age;
}


int Organism::getOrder(){
       return order;
}


double Organism::getSize(){
       return size;
}


double Organism::getFood(){
       return food;
}


Position Organism::getPos(){
       return pos;
}


int start( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] , int nextC ){
     // Reset Arrays
     for (int i=0;i<TABLE_SIZE;i++)
          for (int j=0;j<TABLE_SIZE;j++)
              Chart[i][j]=NULL;
     for (int i=0;i<11;i++)
          Population[i]=0; 
     for (int i=0;i<TABLE_SIZE*TABLE_SIZE;i++)
          if(Creatures[i]!=NULL)
               Creatures[i]=NULL;       
     
     Position inputPos;
     inputPos.x=-1; 
     inputPos.y=-1;
     // Create Default Oranisms     
     for(int i=0;i<=5;i++)   
        nextC = create(Chart,Creatures,Population,nextC,SHARK,inputPos);    
     for(int i=0;i<=6;i++)   
        nextC = create(Chart,Creatures,Population,nextC,DOLPHIN,inputPos);    
     for(int i=0;i<=11;i++)   
        nextC = create(Chart,Creatures,Population,nextC,TURTLE,inputPos);    
     for(int i=0;i<=13;i++)   
        nextC = create(Chart,Creatures,Population,nextC,TUNA,inputPos);
     for(int i=0;i<=18;i++)   
        nextC = create(Chart,Creatures,Population,nextC,MULLET,inputPos);
     for(int i=0;i<=22;i++)   
        nextC = create(Chart,Creatures,Population,nextC,SARDINE,inputPos);
     for(int i=0;i<=26;i++)   
        nextC = create(Chart,Creatures,Population,nextC,OCTOPUS,inputPos);
     for(int i=0;i<=32;i++)   
        nextC = create(Chart,Creatures,Population,nextC,SHRIMP,inputPos);
     for(int i=0;i<=38;i++)   
        nextC = create(Chart,Creatures,Population,nextC,JELLYFISH,inputPos);
     for(int i=0;i<=64;i++)   
        nextC = create(Chart,Creatures,Population,nextC,ZOOPLANKTON,inputPos);
     for(int i=0;i<=76;i++)   
        nextC = create(Chart,Creatures,Population,nextC,PHYTOPLANKTON,inputPos);

     // Print Start and return next Free Creatures Slot
     cout<< "Simulation Start\t(Press Esc or P to Pause)" << endl;
     return nextC;
}

  
int nextCreature(Organism* Creatures[TABLE_SIZE*TABLE_SIZE] , int nextC){
     // Search for emtpy slots in array Creatures
     if(Creatures[nextC] != NULL){
        while(Creatures[nextC]!=NULL)
           if (nextC < TABLE_SIZE*TABLE_SIZE)
              nextC++;
           else 
              nextC=0;
     }
     return nextC;         
}


int create( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] , int nextC,  int type, Position inputPos){
     // Determine type of created Organism
     switch (type){
        case SHARK:
           Creatures[nextC] = new Shark(Population);
           break;
        case TURTLE:
           Creatures[nextC] = new Turtle(Population);
           break;
        case DOLPHIN:
           Creatures[nextC] = new Dolphin(Population);
           break;
        case TUNA:
           Creatures[nextC] = new Tuna(Population);
           break;
        case MULLET:
           Creatures[nextC] = new Mullet(Population);
           break;
        case SARDINE:
           Creatures[nextC] = new Sardine(Population);
           break;
        case OCTOPUS:
           Creatures[nextC] = new Octopus(Population);
           break;
        case SHRIMP:
           Creatures[nextC] = new Shrimp(Population);
           break;
        case JELLYFISH:
           Creatures[nextC] = new Jellyfish(Population);  
           break;
        case ZOOPLANKTON:
           Creatures[nextC] = new Zooplankton();    
           break;
        case PHYTOPLANKTON:
           Creatures[nextC] = new Phytoplankton();        
           break;
     }
     // Set proper values and return next free Creatures slot
     if(inputPos.x==-1 & inputPos.y==-1){
        Creatures[nextC] -> randomize(Chart);
        Population[type]++;
        Creatures[nextC] -> setOrder(nextC);
        nextC = nextCreature(Creatures,nextC);
        }
     else
        if(Creatures[nextC]->place(Chart,inputPos) == 0){
             Population[type]++;
             Creatures[nextC] -> setOrder(nextC);
             nextC = nextCreature(Creatures,nextC);
        }
           
     return nextC;
}


int plankton( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] , int nextC){
    int r;
    Position inputPos;
    inputPos.x=-1; 
    inputPos.y=-1;
    // Compute Random extra plankton created
    r= 15 + rand()%20;
    for(int z=0;z<=r;z++ )
       nextC = create(Chart,Creatures,Population,nextC,ZOOPLANKTON,inputPos);
    r= 30 + rand()%25;
    for(int z=0;z<=r;z++ )
       nextC = create(Chart,Creatures,Population,nextC,PHYTOPLANKTON,inputPos);
    // Return next free Creatures slot
    return nextC;
}


int step( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11] , Position FreeSpace[9], int Deaths[11], int nextC){
    // Execute Step Actions
    for(int i=0;i<TABLE_SIZE*TABLE_SIZE;i++)
       if(Creatures[i]!=NULL){
          Creatures[i]->move(Chart,Creatures , FreeSpace, Population,Deaths);
          Creatures[i]->mate(Chart,Creatures);}
           
    // Return next free Creatures slot
    return nextC;
}


int stepDay( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11], int Deaths[11],Spill OilSpills[5] , int nextC){
    // Execute Day Step Actions
    nextC = plankton(Chart,Creatures,Population,nextC);
    for(int i=0;i<TABLE_SIZE*TABLE_SIZE;i++)
       if(Creatures[i]!=NULL){
          nextC = Creatures[i]->reproduce(Chart,Creatures,Population, nextC);
          Creatures[i]->grow(Chart,Creatures,Population,Deaths);
       }
       
    for (int i=0;i<5;i++)
        if (OilSpills[i].size!=0)
            if(OilSpills[i].duration>0){
               oilSpill(Chart,Creatures,Population,Deaths,OilSpills[i].pos,OilSpills[i].size);
               OilSpills[i].duration--;
            }
            else{
                OilSpills[i].size=0;
                OilSpills[i].pos.x=0;
                OilSpills[i].pos.y=0;
                OilSpills[i].duration=0;
            }
    
    // Return next free Creatures slot
    return nextC;
}


void harpoon(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position target){
    int caught=0;
    cout<<"The harpoon caught: "<<endl;
    for (int z=0;z<6;z++){
        if(Chart[target.x][target.y+z]!=NULL)
          if(Chart[target.x][target.y+z]->getOrder()>1){
            cout<<Chart[target.x][target.y+z]->getAge()<<" day old "<<Chart[target.x][target.y+z]->getInfo();
            cout<<" with size: "<<Chart[target.x][target.y+z]->getSize()<<endl;
            Population[Chart[target.x][target.y+z]->getRank()]--;
            Deaths[Chart[target.x][target.y+z]->getRank()]++;
            Creatures[Chart[target.x][target.y+z]->getOrder()] = NULL;
            Chart[Chart[target.x][target.y+z]->getPos().x][Chart[target.x][target.y+z]->getPos().y] = NULL;
            caught = 1;
        }
    }
    if(caught==0)
        cout<<"Nothing! Bad luck!"<<endl;        
}


void fishnet(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position target,int netSize){
    int caught=0;
    cout<<"The net caught: "<<endl;
    for(int w=0;w<netSize;w++)
      for (int z=0;z<netSize;z++){
        if(Chart[target.x+w][target.y+z]!=NULL)
          if(Chart[target.x+w][target.y+z]->getOrder()>1){
            cout<<Chart[target.x+w][target.y+z]->getAge()<<" day old "<<Chart[target.x+w][target.y+z]->getInfo();
            cout<<" with size: "<<Chart[target.x+w][target.y+z]->getSize()<<endl;
            Population[Chart[target.x+w][target.y+z]->getRank()]--;
            Deaths[Chart[target.x+w][target.y+z]->getRank()]++;
            Creatures[Chart[target.x+w][target.y+z]->getOrder()] = NULL;
            Chart[Chart[target.x+w][target.y+z]->getPos().x][Chart[target.x+w][target.y+z]->getPos().y] = NULL;
            caught = 1;
          }
      }
    if(caught==0)
        cout<<"Nothing! Bad luck!"<<endl;        
}


void oilSpill(Organism* Chart[TABLE_SIZE][TABLE_SIZE], Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int Deaths[11],Position target,int spillSize){
    int caught=0;
    
    cout<<"The spill hit: "<<endl;
    for(int w=0;w<spillSize;w++)
      for (int z=0;z<spillSize;z++){
        if(Chart[target.x+w][target.y+z]!=NULL)
          if(Chart[target.x+w][target.y+z]->getOrder()>1){
            cout<<Chart[target.x+w][target.y+z]->getAge()<<" day old "<<Chart[target.x+w][target.y+z]->getInfo();
            cout<<" with size: "<<Chart[target.x+w][target.y+z]->getSize()<<endl;
            Chart[target.x+w][target.y+z]->setSize(Chart[target.x+w][target.y+z]->getSize()/2);
            caught = 1;
          }
      }
    if(caught==0)
        cout<<"Nothing! Bad luck!"<<endl;
    
}


int menu( Organism* Chart[TABLE_SIZE][TABLE_SIZE] , Organism* Creatures[TABLE_SIZE*TABLE_SIZE] ,int Population[11],int Deaths[11] ,Spill OilSpills[5], int nextC , int* hour, int* stop, int* simSpeed){
    char input, entry;
    int i=0;
    double deaths=0;
    Organism* selected;
    string inputString;
    int type=0,number=0, previusC;
    int searchPosition=0;
    Position inputPos;
    do{
       inputPos.x=0; inputPos.y=0;
       type=0;
       deaths=0;
       number=0;
       searchPosition=0;
       i=0;
       
       cout << "Simulation Paused at Day: "<< *hour/12 +1 <<". Menu:" << endl<< "To Resume, press 1.\nTo Restart press 2."<<endl;
       cout <<"To Set Speed, press 3.\nTo Add Organisms Manually, press 4.\nTo Preview Organism info, press 5.\n";
       cout<<"To Cause a Phenomenon, press 6.\nTo Exit, press 9."<<endl;
       cin >> input;
       switch (input){
          case '1':
             break;
          case '2':
             nextC = start(Chart,Creatures,Population,nextC);
             *hour = 0;
             break;
          case '3':
             cout<<"Set Simulation Speed (Time Step in milliseconds):";
             cin >> *simSpeed ;
             input=0;
             break;
          case '4':
             cout<<"Specify type of organism you want to add:\n11->Shark   10->Dolphin   9->Turtle   8->Tuna   7->Mullet   6->Sardine\n5->Octopus   4->Shrimp   3->Jellyfish   2->Zooplankton   1->Phytoplankton\n0->Cancel\n";
             cin >> type ;
             if(type>0){
                cout<<"Specify number of organisms you wish to add (Set 0 to cancel): ";
                cin >> number ;
                if(number>0){
                   cout<<"Specify the position for each new organism (Set -1 for random): "<<endl;  
                   for(i=0;i<number;i++){
                      cout<<"Organism "<<i<<" x: ";
                      cin >>inputString;
                      inputPos.x = rangeCheck(inputString);
                      if(inputPos.x!=-2){
                         cout<<"Organism "<<i<<" y: ";
                         cin >>inputString;
                         inputPos.y = rangeCheck(inputString);
                      }
                      
                      if(inputPos.x==-1|inputPos.y==-1)
                      {inputPos.x=-1; input=-1;}
                                  
                      previusC = nextC;
                      while(nextC==previusC & inputPos.x!=-2 & inputPos.y!=-2){
                         nextC = create(Chart,Creatures,Population,nextC,type-1,inputPos);
                         if ( nextC!=previusC)
                            cout<<"Organism placed in the Chart "<<endl;
                         else{
                            cout<<"Position taken, pick another one or Q to cancel"<<endl;
                            cout<<"Organism "<<i<<" x: ";
                            cin >>inputString;
                            inputPos.x = rangeCheck(inputString);
                            if(inputPos.x!=-2){
                               cout<<"Organism "<<i<<" y: ";
                               cin >>inputString;
                               inputPos.y = rangeCheck(inputString);
                            }
                         }
                      }
                   }
                number=0;
                }
             }
             input=0;
             break;
          case '5':
             cout<<"Press 1 to view Species Info, 2 to view single Organism Info."<<endl;
             cin >> entry;
             if(entry=='1'){
                 cout<< "Select type of organism:\n11->Shark   10->Dolphin   9->Turtle   8->Tuna   7->Mullet   6->Sardine\n5->Octopus   4->Shrimp   3->Jellyfish   2->Zooplankton   1->Phytoplankton\n0->Cancel\n";
                 cin>>type;
                 type--;
                 searchPosition=0;
                 if(type>0&type<12){
                     cout<<"Category: ";
                     switch (type){
                          case SHARK:
                          cout<<" Shark";
                          break;
                     case TURTLE:
                          cout<<" Turtle";
                          break;
                     case DOLPHIN:
                          cout<<" Dolphin";
                          break;
                     case TUNA:
                          cout<<" Tuna";
                          break;
                     case MULLET:
                          cout<<" Mullet";
                          break;
                     case SARDINE:
                          cout<<" Sardine";
                          break;
                     case OCTOPUS:
                          cout<<" Octopus";
                          break;
                     case SHRIMP:
                          cout<<" Shrimp";
                          break;
                     case JELLYFISH:
                          cout<<" Jellyfish";
                          break;
                     case ZOOPLANKTON:
                          cout<<" Zooplankton";    
                          break;
                     case PHYTOPLANKTON:
                          cout<<" Phytoplankton";        
                          break;}
                     cout<<"Population: "<<Population[type]<<endl;
                     if(Population[type]>0){
                         cout<<"Average Food: "<<avgFood(Creatures,Population,type,&searchPosition)<<endl;
                         cout<<endl<<"Average size: "<<avgSize(Creatures,Population,type,&searchPosition)<<endl;
                         for(i=0;i<11;i++)
                              deaths+=Deaths[i];
                         cout<<"Death Rate: "<<(Deaths[type]/deaths)*100<<" % of total deaths"<<endl;
                         cout<<"Average age: "<< avgAge(Creatures,Population,type,&searchPosition);
                     }
                 }
             }
             else if(entry=='2'){
                 cout<< "Select type of organism:\n11->Shark   10->Dolphin   9->Turtle   8->Tuna   7->Mullet   6->Sardine\n5->Octopus   4->Shrimp   3->Jellyfish   2->Zooplankton   1->Phytoplankton\n0->Cancel\n";
                 cin>>type;
                 type--;
                 if(type>0&type<12){
                     i=0;
                     searchPosition=0;
                     cout<<"There are "<<Population[type]<<" of type:";
                     switch (type){
                          case SHARK:
                          cout<<" Shark";
                          break;
                     case TURTLE:
                          cout<<" Turtle";
                          break;
                     case DOLPHIN:
                          cout<<" Dolphin";
                          break;
                     case TUNA:
                          cout<<" Tuna";
                          break;
                     case MULLET:
                          cout<<" Mullet";
                          break;
                     case SARDINE:
                          cout<<" Sardine";
                          break;
                     case OCTOPUS:
                          cout<<" Octopus";
                          break;
                     case SHRIMP:
                          cout<<" Shrimp";
                          break;
                     case JELLYFISH:
                          cout<<" Jellyfish";
                          break;
                     case ZOOPLANKTON:
                          cout<<" Zooplankton";    
                          break;
                     case PHYTOPLANKTON:
                          cout<<" Phytoplankton";        
                          break;}
                     cout<<"."<<endl;
                     
                     for(i=0;i<Population[type];i++){
                         selected = find(Creatures,type,&searchPosition);
                         cout<< selected->getInfo() << " " << i+1<<" in position ("<<selected->getPos().x<<"."<<selected->getPos().y<<")"<<endl;
                         searchPosition++;
                     }
                     
                     cout << "Select the number of the desired organism."<<endl;
                     cin >> number;
                     searchPosition=0;
                     for(i=0;i<number;i++){
                         selected = find(Creatures,type,&searchPosition);
                         searchPosition++;
                         }
                     
                     selected->print();
                 }
             }
             else
                 cout<<"Invalid Entry";
             input=0;
             break;
          case '6':
             cout<<"Select Phenomenon (Press 1 for Harpoon, 2 for Fishnet or 3 for Oil Spill):\n";
             cin>>entry;
             switch(entry){
               case '1':
                 cout<< "Select Location for the Harpoon:\n(Kills all fish at target location and 4 steps downwards)\nX:";
                 cin>> inputPos.x;
                 cout<< "Y:";
                 cin>> inputPos.y;
                 harpoon(Chart,Creatures,Population,Deaths,inputPos);
                 break;
               case '2':
                 cout<< "Select Location for the Net:\n(Kills all fish at target location and a square of given size)\nX: ";
                 cin>> inputPos.x;
                 cout<< "Y: ";
                 cin>> inputPos.y;
                 cout<< "Select Net Size: ";
                 cin>>number;
                 fishnet(Chart,Creatures,Population,Deaths,inputPos,number);
                 break;
               case '3':
                 cout<< "Select Location for the Oil Spill:\n(Reduces the size of all fish in target area for two days)\nX: ";
                 cin>> inputPos.x;
                 cout<< "Y: ";
                 cin>> inputPos.y;
                 cout<< "Select Spill Size: ";
                 cin>>number;
                 int i=0;
                 while(i<5){
                 if(OilSpills[i].size==0){
                    OilSpills[i].size=number;
                    OilSpills[i].pos=inputPos;
                    OilSpills[i].duration=5;
                    i=6;
                    }    
                 else
                     i++;        
                     }
                 if(i==5)
                    cout<<"Unable to cause an oil spill.Too many existing spills.\n";
                 break;}
             input=0;
             break;
          case '9':
             *stop = 1;
             break;
          default:
             cout << "Improper input. Please insert a proper value." <<endl;
             break;
       }
       cout<<input<<endl;
     }while(input!='1' & input!='2' & input!='3' & input!='4' & input!='9');
    
    // Return next free Creatures slot
    return nextC;
}


void printPopulation(int Population[11]){
     cout<< "Sharks: "<< Population[SHARK]<<endl<< "Dolphins: "<< Population[DOLPHIN]<<endl;
     cout<< "Turtles: "<< Population[TURTLE]<<endl<< "Tunas: "<< Population[TUNA]<<endl;
     cout<< "Mullets: "<< Population[MULLET]<<endl<< "Sardines: "<< Population[SARDINE]<<endl;
     cout<< "Octopuses: "<< Population[OCTOPUS]<<endl<< "Shrimps: "<< Population[SHRIMP]<<endl;
     cout<< "Jellyfish: "<< Population[JELLYFISH]<<endl<< "Zooplankton: "<< Population[ZOOPLANKTON]<<endl;
     cout<< "Phytoplankton: "<< Population[PHYTOPLANKTON]<<endl<<endl;
}


int rangeCheck(string inputString){
     const char * inputChar = inputString.c_str ();
     int number;
     char * pEnd;
     if(inputString=="0")
        number=0;
     else{
        number=strtol(inputChar,&pEnd,10);
        if(number==0)
           number=-2;
     }
          
     if(number>-2&number<TABLE_SIZE)        
        return number;
     else{
        cout<<"Invalid entry, organism creation canceled ;"<<endl;
        return -2;
     }
}


Organism* find(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int rank,int* start){
     int stop=0;
     while ((*start)< TABLE_SIZE*TABLE_SIZE & stop ==0){
         if(Creatures[*start]!=NULL){
             if(Creatures[*start]->getRank()==rank){
                 
                 stop =1;}
             else{
                 (*start)++;
                 }
         }
         else
             (*start)++;     
     }
     if (stop==0)
         return NULL;
     else
         return Creatures[*start];
}


double avgSize(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int rank,int* start){
     int i;
     double sum=0;
     *start=0;
     for (i=0;i<Population[rank];i++)
         sum+= find(Creatures, rank, start)->getSize();
     
     return (sum/Population[rank]);
}


double avgFood(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int rank,int* start){
     int i;
     double sum=0;
     *start=0;
     for (i=0;i<Population[rank];i++)
         sum+= find(Creatures, rank, start)->getFood();
     
     return (sum/Population[rank]);
}


double avgAge(Organism* Creatures[TABLE_SIZE*TABLE_SIZE],int Population[11],int rank,int* start){
     int i;
     double sum=0;
     *start=0;
     for (i=0;i<Population[rank];i++)
         sum+= find(Creatures, rank, start)->getAge();
     
     return (sum/(double)Population[rank]);
}



    
