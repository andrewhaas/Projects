#include <iostream>
#include <cstdlib>
using namespace std;
int main(int count, char** value){
  int number;
  number = atoi(value[1]);//reads input into an int
    if(number != 0){//checks if input was correctly read
      for(int i= 2; i<=(number+1)/2;i++){//checks for factors
	if(number%i==0){
	  cout<<"Composite"<<endl;
	  return 0;
	}
      }
      cout<<"Prime"<<endl;
      return 0;
    }//If it fails to read the input
    cout<<"Incorrect data type inputted, please retry with an positive integer"<<endl;
    return 0;
}
