#include<iostream>
#include<fstream>
#include "viewer_iface.h"
#include "util.h"
#include "level.h"

// Terminal UI and dashboard rendering using primitive parameters

void renderRoomDetails(int floor, int room,const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                       int entityCount){
                        cout<<"---Floor"<<floor<<"-Room"<<room<<"---"<<endl;
                        if (entityCount<=0){
                            cout<<"Nothing here"<<endl;
                            return; }
                        for(int i=0;i<entityCount;i++){
                            char symbol=roomEntities[floor-1][room-1][i];
                            cout<<symbol<<" "<<getEntityName(symbol)<<endl;
                        }
                       
                }
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]){
    const char* names[NUM_OBJECTIVES] = {"Master Key", "Clue Digit 4", "Clue Digit 2", "Clue Digit 7", "Cabinet Unlocked", "Train Key", "Fuse Collected", "Fuse Installed", "Lift Pass", "Lift 2 Active", "Passenger Rescued", "Cat Carrier", "Cat Secured", "Train Prepared", "Mission Won", "Mission Failed"};
    for (int i=0;i<NUM_OBJECTIVES;i++){
        if(objectives[i])cout<<"[ X ] ";
        else cout<<"[ ] ";
        cout<<names[i]<<endl;
    }
}

void renderAsciiBuilding(int playerFloor,int playerRoom)
{
ifstream in("data/building.txt");
if (!in)
{
cout<<"Can't open file"<<endl;
return;
}
char lines[17][MAX_LINE_LEN];
int count = 0;
while (count < 17 && in.getline(lines[count], MAX_LINE_LEN))
count++;
in.close();
if (count < 17) return;
if (playerFloor>=1 && playerFloor<=NUM_FLOORS && playerRoom>=1 && playerRoom<=ROOMS_PER_FLOOR)
{
int row = 14 - 3*(playerFloor-1);
int col = 12 + 12*(playerFloor-1);
lines[row][col] = '[';
lines[row][col+1] = 'Y';
lines[row][col+2] = 'O';
lines[row][col+3] = 'U';
lines[row][col+4] = ']';
}
for (int i = 0; i < count; i++)
cout << lines[i] << endl;
}