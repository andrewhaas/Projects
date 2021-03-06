#include <map>
#include <set> 
#include <string>
#include <iterator>
#include <iostream>
#include "food_item.h"
#include "warehouse.h"

using namespace std;

warehouse::warehouse()
{

}

warehouse::warehouse(string _name, map<string, food_item> items){
  name = _name;
  for(map<string,food_item>::iterator i = items.begin(); i != items.end();i++){
    vector<food_item> items;
    inventory[i->first] = items;
  }
}

 warehouse::~warehouse(){

  }

void warehouse::add_item(food_item item, int number){
    for(int i = 0; i< number; i++){
      inventory[item.get_upc()].push_back(item);
    }
    cout<<"here"<<endl;
  }

void warehouse::remove_item(food_item item, int number){
    for(int i = number; i>0; i--){
      if(inventory[item.get_upc()].size() <=0){
	return;
      }
      inventory[item.get_upc()].erase(inventory[item.get_upc()].begin());
    }
  }

map<string, vector<food_item> > warehouse::get_all(){
  return inventory;
}

 void warehouse::update(){
   for(map<string,vector<food_item> >::iterator i = inventory.begin(); i != inventory.end();i++){
      if(i->second.size()>0){
	int expired_count = 0;
	 for(vector<food_item>::iterator j = i->second.begin(); j != i->second.end();j++){
	   j->decrease_lifetime();
	   if(j->get_lifetime()==0){
	     expired_count++;
	   }
	 }
	 for(int k = expired_count; k>0; k--){
	   i->second.erase(i->second.begin());
	 }
      }
   }
 }
 
string warehouse::to_string(){

   return name;
 }


