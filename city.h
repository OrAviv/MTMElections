//
// Created by Or Aviv on 2018-12-30.
//

#ifndef MTMELECTIONS_CITY_H
#define MTMELECTIONS_CITY_H

#include <stdlib.h>
#include <stdbool.h>
#include "uniqueOrderedList/uniqueOrderedList.h"
#include "libmtm/set.h"

typedef struct city_t* City;

City copyCity (ElementList city);
void freeCity (ElementList city);
bool equlCities(ElementList first_city, ElementList second_city);


#endif //MTMELECTIONS_CITY_H
