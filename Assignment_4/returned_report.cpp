#include <iostream>  
#include <string>
#include <stdlib.h>
#include <set>
#include <map>
#include <ctime>
#include <fstream>
#include <vector>
#include <iterator>
#include "request.h"
#include "report.h"
#include "food_item.h"
#include "warehouse.h"

using namespace std;


int main(int argc, char* argv[])
{
if(argc>2){
  cout<<"You have entered to many parameters, please enter only a filepath"<<endl;
  return 1;
}
 if(argc<2){
   cout<<"you have entered to few parameters, please enter a filepath"<<endl;
   return 1;
 }
 
 report _report;
 _report.create_report(argv[1]);
 cout<<"Report by Andrew Haas"<<endl;
 cout<<"\n";
 cout<<"Underfilled orders:"<<endl;
 for(vector<request>::iterator i = _report.failed_requests.begin();i!=_report.failed_requests.end();i++){
    char buffer [20];
      strftime (buffer,20,"%m/%d/%Y",i->date);
      cout<<buffer<<" "<<i->get_upc()<<" "<<_report.get_foods()[i->get_upc()+""].get_name()<<endl;
 }
 cout<<""<<endl;
 cout<<"Well-Stocked Products:"<<endl;
 map<string,food_item> well_stocked = _report.get_stocked_items();
 for(map<string,food_item>::iterator i = well_stocked.begin();i!=well_stocked.end();i++){
   cout<<i->second.get_upc()<< " "<< i->second.get_name()<<endl;
 }
}
