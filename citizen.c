//
// Created by Or Aviv on 2018-12-30.
//

#include "citizen.h"
#include "uniqueOrderedList/uniqueOrderedList.h"
#include "candidate.h"

#define MAX_NAME_SIZE 80


typedef struct citizen_t{
    char name[MAX_NAME_SIZE];
    int age;
    int id;
    int num_of_educational_years;
    UniqueOrderedList *candidates;
};

