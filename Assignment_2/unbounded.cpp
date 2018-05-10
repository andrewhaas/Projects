/* Andrew Haas
 * January 20, 2018
 */



#include <iostream>
#include <string>
#include <cstdlib>
#include "unbounded.h"

using namespace std;
//Default Constructor
unbounded::unbounded(){
  value = "0";
}
//Constructor method
unbounded::unbounded(string _value){
  value = _value;
}
//Copy Constructor method
unbounded::unbounded(const unbounded & other){
  value=other.value;
}
//Overrides the '+' operator to allow for the addition of unbounded integers.
const unbounded unbounded::operator+ (const unbounded & rhs) const
{
  string left = value;
  string right = rhs.value;
  string result = "" ;
  int left_pos  = left.length()  - 1;//starting index
  int right_pos = right.length() - 1;//starting index
  int carry_over = 0;//carry for addition
  while (carry_over > 0 || left_pos >= 0 || right_pos >= 0)//loops until there is nothing left to add
   {
     int left_digit  = left_pos  >= 0 ? left[left_pos--]   - '0' : 0; //if there isn't a digit uses 0
     int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;//if there isn't a digit uses 0
     int sum = carry_over + left_digit + right_digit; //sums the digits and the carry
     carry_over = sum / 10;//creates the carry digit for the next sum
     sum   = sum % 10; //gets the single digit value of the sum
     result.insert (0, 1, (char)('0'+sum));//inserts the value into the final result.
   }
  while (result[0] == '0' && result.length() > 1) //gets rid of all the preceeding  zeros
   {
     result.erase(0, 1);
   }
  
  return result;
  
}
//Override of the '-' operator to allow for unbounded subtraction.
const unbounded unbounded::operator- (const unbounded & rhs) const 
{
  string left = value;
  string right = rhs.value;
  string result = "";
  int left_pos  = left.length()-1;//starting index
  int right_pos = right.length()-1;//starting index
  int carry_over = 0;//subtraction carry digit
  int difference; //difference between digits
  for(left_pos; left_pos>=0; left_pos--){ //goes through ever digit of the left integer assuming it is larger than the right one 
    if(right_pos>=0){//checks if the right index is not at the end
      difference = left[left_pos] -(right[right_pos]+carry_over);//computes the difference between digits and carry
    right_pos--;
    }
    else{
      difference = left[left_pos] -carry_over; //computes difference of carry and left integer's digit
    }
    if(difference>=0){//checks if there was a postive difference
      carry_over = 0;//Doesn't carry
    }
    else{//if difference is negative it adds 10 to make it positive and then has a carry of 1
      difference +=10;
      carry_over =1;
    }//Had small bug getting letters occasionally so made it so it would only give numbers with %48
    result=((char)('0'+  difference%48))+result; //adds digit to the final result. 
  
   }
  if(difference<0){// if the final difference is negative returns an unbounded with value 0
    return unbounded();
  }
  while (result[0] == '0' && result.length() > 1)//removes preceeding 0's
   {
     result.erase(0, 1);
   }
  if(right_pos>left_pos){// if the right side is bigger returns an unbounded of value 0;
     return unbounded();
   }
  
   return unbounded(result);
  
}
//Overrides the '/' operator to allow for dividion between unbounded integers
const unbounded unbounded::operator/ (const unbounded & rhs) const
{
  string right = rhs.value;
  string left = value;
  unbounded result = unbounded();
  string value = "";
  int left_pos  = 0;//starting index
  int right_pos = right.length();//starting index
  int temporary = left[left_pos]- '0';//temporary value to build on
  if(right.length()>left.length()){//if the divisior is larger returns an unbounded with a value of 0
    return unbounded();
  }
  while((temporary- atoi(right.c_str()))>0){//creates an initial number to be the first dividee
    temporary = temporary*10 + (left[++left_pos]-'0');// places the next digit 
    }
  while(left.length()>left_pos){//loops until the left integer is out of digits
    value += temporary/(atoi(right.c_str())) +'0';//adds the current qoutient to the overall value
    temporary =(temporary%(atoi(right.c_str()))) *10 + left[++left_pos]-'0';//updates temporary for the next set of digits
  }
    return unbounded(value);
 
}
//Overrides the '*' operator to allow for unbounded integers to be multiplied
const unbounded unbounded::operator* (const unbounded & rhs) const
{
  string right = rhs.value;
  string left = value;
  string result ="0";
  int right_position = 0;//starting index
  while(right_position< right.length()){//loops through the multiplier
    result = result.append("0");//adds a 0 to the final result
    int right_value = right[right_position++]-'0';//gets the numerical value of the current digit
    for(int i =0; i<right_value;i++){
      result = (unbounded(result)+ unbounded(left)).value;//multiplies the current result by the next value
    }
  }
  return unbounded(result);
}
//Override the '%' operator to allow unbounded integers to mod each other
const unbounded unbounded::operator% (const unbounded & rhs) const
{
  unbounded factor = unbounded(value)/rhs; //gets the amount of times rhs can go int the left integer
  factor = factor * rhs;//multiplies the amount of times by the value of rhs
  return (unbounded(value) - factor);//returns the difference between the sum of all the rhs's and the left integer
}
//Overrides the '=' operator to allow for the value of one unbounded to be set the value of another
unbounded & unbounded::operator= (const unbounded & rhs)
{
  value = rhs.value;
  return *this;
}
//Method that returns the string value contained within the unbounded integer
string unbounded::get_value() const
{
  return value;
}
