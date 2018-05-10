#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <set> 
#include <string>
#include <iterator>
#include <iostream>
#include <ctime>
#include "food_item.h"
#include "warehouse.h"
 
class request
{
 private: 
  std::string warehouse;
  std::string upc_code;
  int quantity;
  bool filled;
 public:
  request();
 
  request(std::string);
  ~request();
  std::string get_warehouse();
  void complete_request();
  bool is_filled();
  std::string get_upc();
  int get_quantity();
  struct tm *date;
};
#endif
