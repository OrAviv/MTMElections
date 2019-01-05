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

Element copyCity(Element city)
{
    if (city == NULL)
        return NULL;

    City new_city = malloc(sizeof(*city));
    if (new_city == NULL)
        return NULL;

    new_city = *(City*)city;
    return new_city;
}
void freeCity (Element city)
{
    free(city);
}
bool citysEqual (Element first_city, Element second_city)
{
    if (first_city == NULL || second_city == NULL)
        return NULL;

    City f_city = copyCity(first_city);
    City s_city = copyCity(second_city);

    if (uniqueOrderedListSize(f_city->citizens) == uniqueOrderedListSize(s_city->citizens))
    {
        freeCity(f_city);
        freeCity(s_city);
        return true;
    }

    freeCity(f_city);
    freeCity(s_city);
    return false;
}
bool cityGreaterThan (Element first_city, Element second_city)
{
    if (first_city == NULL || second_city == NULL)
        return NULL;
    if (citysEqual(first_city,second_city))
        return false;

    City f_city = copyCity(first_city);
    City s_city = copyCity(second_city);

    if (uniqueOrderedListSize(f_city->citizens) == uniqueOrderedListSize(s_city->citizens))
    {
        freeCity(f_city);
        freeCity(s_city);
        return true;
    }
}