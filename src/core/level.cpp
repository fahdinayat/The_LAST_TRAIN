#include<level.h>
const char* getEntityName(char entitySymbol){
    switch(entitySymbol){
        case '<': return "Master Key";
        case ')': return "Energy Pack";
        case '\\': return "Emergency Toolkit";
        case '4': return "Clue Digit 4";
        case '*': return "Fuse";
        case '~': return "Cat";
        case ';': return "Control Panel";
        case '(': return "Lift Pass";
        case '!': return "Injured Passenger";
        case '%': return "Medical Kit";
        case '$': return "Emergency Access Card";
        case '2': return "Clue Digit 2";
        case '7': return "Clue Digit 7";
        case '^': return "Train Key";
        case '@': return "Cat Carrier";
        case '&': return "Observation Token";
        default : return "Unknown";

    }}
bool validateStartingRoom(int startFloor, int startRoom,
                          const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
                            (void)horizontalConn;
                            if (startFloor<1||startFloor>5||startRoom<1||startRoom>4) return false;
                            return true;
                        

                     }
bool loadBuildingMap(const char* filename, char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{
ifstream in(filename);
if (!in){
    cout<<"Can't open file"<<endl;
    return false;
}
char lines[17][MAX_LINE_LEN];
for (int i=0;i<17;i++){
    if (!in.getline(lines[i], MAX_LINE_LEN)){
        in.close();
        return false;
}
}
in.close();
for (int f=NUM_FLOORS-1;f>=0;f--){
    for (int g=0;g<ROOMS_PER_FLOOR-1;g++)
        horizontalConn[f][g]=CONN_NONE;
    for (int r = 0; r < ROOMS_PER_FLOOR; r++){
        entityCounts[f][r] = 0;
    for (int k = 0; k < MAX_ENTITIES_PER_ROOM; k++)
        roomEntities[f][r][k] = ENT_NONE;
}
}
int startCol[ROOMS_PER_FLOOR] = {9, 21, 33, 45};
int endCol[ROOMS_PER_FLOOR] = {19, 31, 43, 55};
int connCol[ROOMS_PER_FLOOR - 1] = {20, 32, 44};
for (int floor=0;floor<NUM_FLOORS;floor++){
    char* labelLine=lines[14-3*floor];
    char* itemLine=lines[15-3*floor];
    int labelLen=0;
    while(labelLine[labelLen]!='\0')
        labelLen++;
    int itemLen=0;
    while(itemLine[itemLen]!='\0')
        itemLen++;

for (int g=0;g<ROOMS_PER_FLOOR-1;g++){   
    char c = ' ';
    if (connCol[g] < labelLen) c =labelLine[connCol[g]];
    if (c=='D' || c=='W' || c=='#' || c=='L' ) horizontalConn[floor][g] = c;
}

for (int room=0;room<ROOMS_PER_FLOOR;room++){
    for (int col=startCol[room];col<=endCol[room] && col<itemLen; col++){
        char c=itemLine[col];
        if (c!=' ' && entityCounts[floor][room]<MAX_ENTITIES_PER_ROOM ){
            roomEntities[floor][room][entityCounts[floor][room]]=c;
            entityCounts[floor][room]++;
        }

}
}
}
if (entityCounts[0][3]==1 && roomEntities[0][3][0]==ENT_ENERGY_PACK){
    roomEntities[0][3][1]=ENT_ENERGY_PACK;
                            entityCounts[0][3]=2;
                        }
return true;
}
bool loadInitialState(const char* filename,
                      int& playerFloor, int& playerRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft){
                        ifstream in(filename);
                        if(!in){
                            cout<<"Can't open file"<<endl;
                            return false;
                        }
                        playerFloor=1;
                        playerRoom=1;
                        energy=INITIAL_ENERGY;
                        time=INITIAL_TIME;
                        score=INITIAL_SCORE;
                        emergencyTripsLeft=0;
                        inventoryCount=0;
                       
                        for(int i=0;i<MAX_INVENTORY_CAPACITY;i++){
                            inventory[i]=ENT_NONE;
                        }
            
                        for (int i=0;i<NUM_OBJECTIVES;i++){
                            objectives[i]=false;
                        }
                        char label[MAX_LINE_LEN];
                        char word[MAX_LINE_LEN];
                        while (in>>label){
                        if (stringEquals(label, "INITIAL_ENERGY:")) in>>energy;
                        else if (stringEquals(label, "INITIAL_TIME:")) in>>time;
                        else if (stringEquals(label, "INITIAL_SCORE:")) in>>score;
                        else in>>word;
                        }
                        in.close();
                        energy=clampInt(energy,0, MAX_ENERGY);
                        time=clampInt(time,0, MAX_TIME);
                        return true;
}