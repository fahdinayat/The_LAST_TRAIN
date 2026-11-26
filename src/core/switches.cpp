#include<iostream>
#include "switches.h"
using namespace std;
bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft){
   if (fromFloor != 2 && fromFloor != 4 && fromFloor != 5) return false;
   if (toFloor != 2 && toFloor != 4 && toFloor != 5) return false;

   if (fromFloor == toFloor) return false;

    if(lift2Operational==1 || emergencyTripsLeft>0) return true;
    else return false;
    
}