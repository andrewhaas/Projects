#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main(){
  double input_seconds;
  int minutes, hours, seconds;
  bool keep_looping=true;
  cout<<"Please enter the amount of seconds to convert"<<endl;
  while(keep_looping)
    {
  if(cin>>input_seconds && input_seconds>=0){
    keep_looping=false;
    seconds= round(input_seconds);
    hours= seconds/3600;
    seconds=seconds-(hours*3600);
    minutes=seconds/60;
    seconds= seconds- (60*minutes);
    cout<<input_seconds<<" seconds ---> "<< setfill('0')<<setw(2)<<hours<<":"<<setfill('0')<<setw(2)<<minutes<<":"<<setfill('0')<<setw(2)<<seconds<<endl;
 }
  else{
    cout<<"Incorrect input type, please put in a non-negative number."<<endl;
    cin.clear();
}

    }
}
