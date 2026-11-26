#include <iostream>
#include <fstream>
#include "logger.h"
using namespace std;
bool saveGameStateToFile(const char* filename,
                         int playerFloor, int playerRoom,
                         int energy, int time, int score,
                         const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                         const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft,
                         const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                         const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
                            ofstream out(filename);
                            if(!out){
                                cout<<"Can't open file"<<endl;
                                return false;
                            }
                           
                             out<<playerFloor<<" "<<playerRoom<<endl;
                             out<<energy<<" "<<time<<" "<<score<<endl;
                             out<<inventoryCount<<endl;
                             for (int k=0;k<inventoryCount;k++){
                                    out<<inventory[k]<<" ";

                             }
                             out<<endl;
                             for(int i=0;i<NUM_OBJECTIVES;i++){
                                out<<objectives[i]<<" ";
                             }
                             out<<endl;
                             out<<emergencyTripsLeft<<endl;
                             for(int floor=5;floor>0;floor--){
                                for(int room=1;room<=4;room++){
                                    out<<entityCounts[floor-1][room-1]<<" ";
                                    for(int i=0;i<entityCounts[floor-1][room-1];i++)
                                         out<<roomEntities[floor-1][room-1][i]<<" ";
                                        out<<endl;
                                    
                                }
                                
                                
                             }
                                out.close();
                                return true;
                            }
bool loadGameStateFromFile(const char* filename,
                           int& playerFloor, int& playerRoom,
                           int& energy, int& time, int& score,
                           char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                           bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                           char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                           int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
                            ifstream in(filename);
                            if(!in) {cout<<"Can't open file"<<endl;
                            return false; }
                            in>>playerFloor;
                            in>>playerRoom;
                            in>>energy;
                            in>>time;
                            in>>score;
                            in>>inventoryCount;
                            if (inventoryCount>=0 && inventoryCount<=MAX_INVENTORY_CAPACITY){
                                for (int i=0;i<inventoryCount;i++){
                                    in>>inventory[i];
                                }
                            }
                            else return false;
                            for(int k=0; k<NUM_OBJECTIVES;k++){
                                int v;
                                in>>v;
                                objectives[k]= (v==1);
                            }
                            in>>emergencyTripsLeft;
                            for(int floor=5;floor>0;floor--){
                                for (int room=1;room<=4;room++){
                                    in>>entityCounts[floor-1][room-1];
                                    if(entityCounts[floor-1][room-1]>=0 && entityCounts[floor-1][room-1]<=MAX_ENTITIES_PER_ROOM){
                                        for(int i=0;i<entityCounts[floor-1][room-1];i++)
                                                in>>roomEntities[floor-1][room-1][i];
                                    }
                                    else return false;
                                }
                                
                            }
                            in.close();
                            return true;
                           }                          
                             
                             
void writeGameSummaryReport(const char* filename, int score, int remainingEnergy, int remainingTime, const bool objectives[NUM_OBJECTIVES], bool victory){
    ofstream out(filename);
    if(!out) {
        cout<<"Can't open file"<<endl;
        return;
    }
    const char* names[NUM_OBJECTIVES] = {"Master Key", "Clue Digit 4", "Clue Digit 2", "Clue Digit 7", "Cabinet Unlocked", "Train Key", "Fuse Collected", "Fuse Installed", "Lift Pass", "Lift 2 Active", "Passenger Rescued", "Cat Carrier", "Cat Secured", "Train Prepared", "Mission Won", "Mission Failed"};
    out<<"Score: "<<score<<endl;
    out<<"Remaining Energy: "<<remainingEnergy<<endl;
    out<<"Remaining Time: "<<remainingTime<<endl;
    for (int i=0;i<NUM_OBJECTIVES;i++){
        if(objectives[i]==1){ 
            out<<"[ X ] "<<names[i]<<endl;
        }
        else 
            out<<"[   ] "<<names[i]<<endl;
    }
    if (victory==1){
        out<<" CONGRATS YOU HAVE WON THE GAME!"<<endl;
    }
    else out<<" YOU HAVE LOST THE GAME"<<endl;
    out.close();
}