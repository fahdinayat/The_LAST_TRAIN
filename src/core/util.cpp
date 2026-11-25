#include <iostream>
#include <cstdlib>
#include "util.h"
using namespace std;
int clampInt(int val, int minVal, int maxVal)
{
if (val < minVal) return minVal;
if (val > maxVal) return maxVal;
return val;
}
void printHeader(const char* title)
{
cout << "=== " << title << " ===" << endl;
}
void clearScreen()
{
system("cls");
}
void trimWhitespace(char* str)
{
    int i=0;
    while(str[i]!='\0')
        i++;
    int start=0;
    while(str[start]==' ')
        start++;

    int end=i-1;
  
    while(end >=start && str[end]==' ')
        end--;
    
        int j=0;
    while(start<=end){
        str[j]=str[start];
        j++;
        start++;
    }
    str[j]='\0';


}
bool stringEquals(const char* a, const char* b){
    int i=0;
    while(a[i]!='\0' && b[i]!='\0'){
        if(a[i]!=b[i])
            return false;
        i++;
    }
    
return a[i]==b[i];
}