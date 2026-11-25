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
                            if (startFloor<1 || startFloor>5 || startRoom<1 || startRoom>4) return false;
                            return true;
                        

                     }
