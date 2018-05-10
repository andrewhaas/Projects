#include <iostream>  
#include <string>
#include <stdlib.h>
#include <set>
#include <map>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "report.h"
#include "food_item.h"
#include "warehouse.h"
#include "request.h"

using namespace std;

 struct comparator {
	bool operator() (request r1,request l1) { 
	  if (r1.date->tm_year < l1.date->tm_year){
	    return true;
	  }
	  if (r1.date->tm_year == l1.date->tm_year && r1.date->tm_mon < l1.date->tm_mon){
	    return true;
	  }
	  if (r1.date->tm_year == l1.date->tm_year && r1.date->tm_mon == l1.date->tm_mon && r1.date->tm_mday < l1.date->tm_mday){
	    return true;
	  }
	  if(r1.get_upc()<l1.get_upc()){
	    return true;
	  }
	  return false;
	}
      } myobject;

report::report(){

}

report::~report(){

}

void report::create_report(string file_name){
  ifstream infile(file_name.c_str());
  if (!infile) {
    cout << "Unable to open file ";
    exit(1);   
  }
  string current_line;
  while(getline(infile, current_line)){
    string delim = " ";
    string first = current_line.substr(0, current_line.find(delim));
    if(first == "FoodItem"){
      string upc= "UPC Code: ";
      string life= "Shelf life: ";
      string name= "Name: ";

      int start = current_line.find(upc)+ upc.length();
      int end = current_line.find(delim,start)-start;
      string upc_code = current_line.substr(start,end);

      start = current_line.find(life)+ life.length();
      end = current_line.find(delim,start)-start;
      string shelf_life = current_line.substr(start,end);

      start = current_line.find(name)+ name.length();
      string item_name = current_line.substr(start);

      food_item food(upc_code,atoi(shelf_life.c_str()),item_name);

      items[upc_code]= food;
    }
    else if(first == "Warehouse"){
      string ware_house = "Warehouse - ";
      int start = current_line.find(ware_house)+ ware_house.length();
      int end = current_line.find(delim,start)-start;
      string name = current_line.substr(start,end);
      warehouse inventory(name, items);
      warehouses[name]=inventory;
     
    }
     else if(first == "Start"){
      string date = "Start date: ";
      int start = current_line.find(date)+ date.length();
      int end = current_line.find(delim,start)-start;
      string start_date = current_line.substr(start,end);
      time_t now = time(0);
      starting_date = localtime(&now);
      string month= start_date.substr(0,2);
      string day=start_date.substr(3,2);
      string year=start_date.substr(6);
      int _month= atoi(month.c_str())-1;
      int _day= atoi(day.c_str());
      int _year= atoi(year.c_str())-1900;
      starting_date->tm_mon= _month;
      starting_date->tm_mday= _day;
      starting_date->tm_year= _year;
      starting_date->tm_hour= 0;
      starting_date->tm_min= 0;
      starting_date->tm_sec= 0;
      }
     else if(first == "Receive:"){
      string receive = "Receive: ";
      int start = current_line.find(receive)+ receive.length();
      int end = current_line.find(delim,start)-start;
      string upc_code = current_line.substr(start,end);
      start = current_line.find(upc_code)+ upc_code.length()+1;
      end = current_line.find(delim,start)-start;
      string count = current_line.substr(start,end);
      
      string warehouse_name= upc_code+" "+ count;
      start = current_line.find(warehouse_name)+ warehouse_name.length()+1;
      end = current_line.find(delim,start)-start;
      string name = current_line.substr(start,end);
      food_item food(upc_code, items[upc_code].get_lifetime(), name);
      warehouses[name].add_item(food, atoi(count.c_str()));
    }
    else if(first == "Request:"){
      request r(current_line);
      time_t temp = time(0);
      r.date;
      int day=(starting_date->tm_mday)+1-1; 
      int month= (starting_date->tm_mon)+1-1;
      int year=(starting_date->tm_year)+1-1;
      r.date->tm_mon= month;
      r.date->tm_mday= day;
      r.date->tm_year= year;
      requests.push_back(r);
    }
    else if(first == "Next"){

      vector<request>::iterator i = requests.begin();
      while(i != requests.end()){
	if(!(i->is_filled())){ 
	  food_item food(i->get_upc(), items[i->get_upc()].get_lifetime(),items[i->get_upc()].get_name());
	  cout<<warehouses[i->get_warehouse()].get_all()[i->get_upc()].size()<<endl;
        if(warehouses[i->get_warehouse()].get_all()[i->get_upc()].size()>=i->get_quantity()){
	  warehouses[i->get_warehouse()].remove_item(food, i->get_quantity());
	  i->complete_request();
	  
        }else{
	  warehouses[i->get_warehouse()].remove_item(food,warehouses[i->get_warehouse()].get_all()[i->get_upc()].size());
	  failed_requests.push_back(*i);
	  i= requests.erase(i);
	  i--;
	}	}i++;
      
      }
	for(map<string, warehouse>::iterator i = warehouses.begin();i != warehouses.end();i++){
	  i->second.update();
	} char buffer [20];
      starting_date->tm_mday=starting_date->tm_mday+1;

    }
    else{
      vector<request>::iterator i = requests.begin();
      while(i != requests.end()){
	if(!(i->is_filled())){	
	  food_item food(i->get_upc(), items[i->get_upc()].get_lifetime(),items[i->get_upc()].get_name());
        if(warehouses[i->get_warehouse()].get_all()[i->get_upc()].size()>=i->get_quantity()){
	  warehouses[i->get_warehouse()].remove_item(food, i->get_quantity());
	  i->complete_request();
	  
        }else{
	  warehouses[i->get_warehouse()].remove_item(food,warehouses[i->get_warehouse()].get_all()[i->get_upc()].size());
	  failed_requests.push_back(*i);
	  i= requests.erase(i);
	  i--;
	}	}i++;    
      }
	for(map<string, warehouse>::iterator i = warehouses.begin();i != warehouses.end();i++){
	  i->second.update();
      }
      sort(failed_requests.begin(),failed_requests.end(), myobject);
      sort(requests.begin(),requests.end(), myobject);
      return;
    }
  }
}


map<string,food_item> report::get_unstocked_items(){
  map<string, food_item> unstocked_foods = items;
  for(map<string,warehouse>::iterator i = warehouses.begin(); i!=warehouses.end();i++){
    map<string,vector<food_item> > current_inventory = i->second.get_all();
    for(map<string,vector<food_item> >::iterator j = current_inventory.begin(); j!= current_inventory.end(); j++){
      if(j->second.size()!=0){
	unstocked_foods.erase(j->first);
	}
      }
    }
  
  return unstocked_foods;
}

map<string, food_item> report::get_stocked_items(){
  map<string, food_item> stocked_foods;
  map<string, int> locations;
  for(map<string, food_item>::iterator i = items.begin(); i!=items.end();i++){
    locations[i->first]=0;
  }
  for(map<string,warehouse>::iterator i = warehouses.begin(); i!=warehouses.end();i++){
    map<string,vector<food_item> > current_inventory = i->second.get_all();
    for(map<string,vector<food_item> >::iterator j = current_inventory.begin(); j!=current_inventory.end(); j++){
      if(j->second.size()>0){
	map<string, int>::iterator k = locations.find(j->first);
	if(k != locations.end()){
	  k->second = k->second+1;
	}
      }
    }
  }
  for(map<string, int>::iterator i = locations.begin(); i!=locations.end();i++){
    if(i->second>1){
      stocked_foods[i->first] = (items.find(i->first))->second;
    }
  }
  return stocked_foods;
}

map<string, food_item> report::get_foods(){
  return items;
}

map<string, warehouse> report::get_all(){
  return warehouses;
}

