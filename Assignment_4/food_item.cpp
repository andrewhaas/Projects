#include "food_item.h"

using namespace std;
food_item::food_item(){

}

food_item::food_item(string upc_num, int life, string _name){

  upc = upc_num;
  lifetime = life;
  name = _name;

}

food_item::~food_item(){

}

void food_item::decrease_lifetime(){

  lifetime--;

}

string food_item::get_name(){

  return name;
}

int food_item::get_lifetime(){

  return lifetime;
}

string food_item::get_upc(){

  return upc;
}

string food_item::to_string(){

  return upc + " " + name;
}

