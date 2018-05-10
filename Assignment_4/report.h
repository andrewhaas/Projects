#ifndef REPORT_H
#define REPORT_H

#include<string>
#include<vector>
#include<set>
#include<ctime>
#include"warehouse.h"
#include"food_item.h"
#include"request.h"
class report
{
 public:
  report();
  ~report();
  void create_report(std::string file_name);
  std::map<std::string, food_item> get_stocked_items();
  std::map<std::string, food_item> get_foods();
  std::map<std::string, food_item> get_unstocked_items();
  std::map<std::string, warehouse> get_all();
  std::vector<request> requests;
  std::vector<request> failed_requests;
  struct tm *starting_date;
  

 private:
  std::map<std::string, food_item> items;
  std::map<std::string, warehouse> warehouses;

  bool compare(request&,request&);
};
#endif
  

