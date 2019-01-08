//
// Created by Or Aviv on 2018-12-30.
//

#include "city.h"
#include "uniqueOrderedList/uniqueOrderedList.h"

#define MAX_CITY_NAME 80


struct city_t{
  char city_name[MAX_CITY_NAME];
  int ciy_identifier;
  UniqueOrderedList candidates;
  UniqueOrderedList citizens;
};


City copyCity (ElementList city);
void freeCity (ElementList city);
bool equlCities(ElementList first_city, ElementList second_city);