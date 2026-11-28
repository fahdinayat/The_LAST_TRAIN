#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"

bool handleUseCommand(char itemSymbol, int currentFloor, int currentRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES])
{
if(!hasItem(inventory,inventoryCount,itemSymbol)){
    cout << "You don't have that item." << endl;
    return false;
}
if (itemSymbol == ENT_MEDICAL_KIT){
    if (currentFloor != 4 || currentRoom != 1){
        cout << "The Medical Kit can only be used on the Passenger in F4-R1." << endl;
        return false;
    }
if (objectives[OBJ_PASSENGER_RESCUED]){
    cout << "The Passenger is already rescued." << endl;
    return false; }
applyResourceDelta(energy, time, COST_ITEM_USE_ENERGY, COST_ITEM_USE_TIME);
applyScoreDelta(score, SCORE_RESCUE_PASSENGER);
objectives[OBJ_PASSENGER_RESCUED] = true;
removeItem(inventory, inventoryCount, ENT_MEDICAL_KIT);
cout << "Passenger rescued!" << endl;
return true;
}
if(itemSymbol==ENT_CAT_CARRIER){
    if(currentFloor!=3 || currentRoom!=3){
        cout<<"The Cat Carrier can only be used to save cat at F3-R3"<<endl;
        return false;
    }
    if(objectives[OBJ_CAT_SECURED]==true){
        cout<<"The Cat is already rescued"<<endl;
        return false;
    }
    applyResourceDelta(energy,time,COST_ITEM_USE_ENERGY,COST_ITEM_USE_TIME);
    applyScoreDelta(score,SCORE_SECURE_CAT);
    objectives[OBJ_CAT_SECURED]=true;
    removeItem(inventory,inventoryCount,ENT_CAT_CARRIER);
    cout<<"Cat Rescued!"<< endl;
    return true;
    
}
if(itemSymbol==ENT_FUSE){
    if(currentFloor!=3 || currentRoom!=4){
        cout<<"The Fuse can only be used in F3-R4"<<endl;
        return false;
    }
    if(objectives[OBJ_FUSE_INSTALLED]==true){
        cout<<"The Fuse is already installed"<<endl;
        return false;
    }
    if(!installFuseControlPanel(inventory,inventoryCount,objectives,score)){
    return false;
    }
    cout<<"Fuse Installed!"<<endl;
    return true;
    
}
if(itemSymbol==ENT_CABINET_TRAIN_KEY){
    if(currentFloor!=5 || currentRoom!=2){
        cout<<"The Train key can only be used in F5-R2"<<endl;
        return false;
    }
    if (objectives[OBJ_PASSENGER_RESCUED]==false || objectives[OBJ_CAT_SECURED]==false){
        cout<<"Cat and Passenger needs to be recued before boarding"<<endl;
        return false;

    }
    applyResourceDelta(energy,time,COST_ITEM_USE_ENERGY,COST_ITEM_USE_TIME);
    applyScoreDelta(score,SCORE_PREPARE_TRAIN);
    objectives[OBJ_TRAIN_PREPARED]=true;
    objectives[OBJ_MISSION_WON]=true;
    applyScoreDelta(score,SCORE_MISSION_VICTORY);

    cout<<"Congrats Mission Won!"<< endl;
    return true;
    
}
cout << "That item can't be used." << endl;
return false;
}
