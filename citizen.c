//
// Created by Or Aviv on 2018-12-30.
//

#include <stdlib.h>
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

Element copyCitizen (Element citizen)
{
    if(citizen == NULL)
        return NULL;

    Citizen* new_citizen = malloc(sizeof(*new_citizen));
    if (new_citizen == NULL)
        return NULL;
    *new_citizen = *(Citizen*)citizen;
    return new_citizen;
}

void freeCitizen (Element citizen)
{
    free(citizen);
}
bool citizensEqual (Element first_citizen, Element second_citizen)
{
    if (first_citizen == NULL || second_citizen == NULL)
        return NULL;

    Citizen f_citizen = copyCitizen(first_citizen);
    Citizen s_citizen = copyCitizen(second_citizen);

    if (f_citizen->name == s_citizen->name)
        if (f_citizen->age == s_citizen->age)
            if (f_citizen->id == s_citizen->id)
                if (f_citizen->num_of_educational_years == s_citizen->num_of_educational_years)
                {
                    freeCitizen(f_citizen);
                    freeCitizen(s_citizen);
                    return true;
                }
    return false;
}
bool citizenGreaterThan (Element first_citizen, Element second_citizen)
{
    bool answer = NULL;
    if (first_citizen == NULL || second_citizen == NULL)
        return answer;

    Citizen f_citizen = copyCitizen(first_citizen);
    Citizen s_citizen = copyCitizen(second_citizen);

    if (f_citizen->age > s_citizen->age)
        answer = true;
    else answer = false;

    freeCitizen(f_citizen);
    freeCitizen(s_citizen);
    return answer;
}
