#include<physics.h>

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    if(inventoryCount>=MAX_INVENTORY_CAPACITY) return false;
    inventory[inventoryCount]=itemSymbol;
    inventoryCount=inventoryCount+1;
    return true;
}
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    int pos=0;
    while (pos < inventoryCount){
        if(inventory[pos]==itemSymbol){
            int j=pos;
            while( j < inventoryCount-1){
                inventory[j]=inventory[j+1];
                j++;}
                inventoryCount--;
            
            return true;
        }
        pos++;
    }
    return false;
}