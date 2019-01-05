//
// Created by Or Aviv on 2018-12-30.
//

#ifndef MTMELECTIONS_CITIZEN_H
#define MTMELECTIONS_CITIZEN_H


#include <stdbool.h>
#include "uniqueOrderedList/uniqueOrderedList.h"

typedef struct citizen_t* Citizen;

Element copyCitizen (Element citizen);
void freeCitizen (Element citizen);
bool citizensEqual (Element first_citizen, Element second_citizen);
bool citizenGreaterThan (Element first_citizen, Element second_citizen);



#endif //MTMELECTIONS_CITIZEN_H
