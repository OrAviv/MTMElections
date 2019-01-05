//
// Created by Or Aviv on 2018-12-30.
//

#ifndef MTMELECTIONS_CITY_H
#define MTMELECTIONS_CITY_H

#include <stdlib.h>
#include <stdbool.h>
#include "uniqueOrderedList/uniqueOrderedList.h"

typedef struct city_t* City;

Element copyCity(Element city);
void freeCity (Element city);
bool citysEqual (Element first_city, Element second_city);
bool cityGreaterThan (Element first_city, Element second_city);



#endif //MTMELECTIONS_CITY_H
