#include <map>
#include <set> 
#include <string>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include "food_item.h"
#include "warehouse.h"
#include "request.h"
#include <ctime>

using namespace std;

request::request(){

}

request::request(string _request){
   string request = "Request: ";
   int start = _request.find(request)+ request.length();
   int end = _request.find(" ",start)-start;
   string upc = _request.substr(start,end);

   upc_code = upc;
     
   start = _request.find(upc)+ upc.length()+1;
   end = _request.find(" ",start)-start;
   string count =_request.substr(start,end);
   quantity = atoi(count.c_str());
      
 
   warehouse = _request.substr(end+start+1);
   filled = false;

}


request::~request(){

}

string request::get_warehouse(){
  return warehouse;
}



void request::complete_request(){
  filled = true;
}

string request::get_upc(){
  return upc_code;
}

int request::get_quantity(){
  return quantity;
}

bool request::is_filled(){
  return filled;
}
