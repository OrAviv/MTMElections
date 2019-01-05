//
// Created by Or Aviv on 2019-01-01.
//

#include <stdio.h>
#include <stdlib.h>
#include "uniqueOrderedList.h"


typedef struct elementList_t {
    Element data;
    struct elementList_t* next;
};

typedef struct uniqueOrderedList_t{
    copyElements copyFunction;
    freeElements freeFunction;
    elementsEquals equalsFunction;
    elementGreaterThan greaterThanFunction;

    ElementList element_list;
    int size;
    ElementList* head;
    int iterator;
};

/**
* Allocates a new List.
*
* Creates a new empty list. This function receives the functions which will be
* used for copying elements into the list, freeing them when needed,
* comparing if elements are greater from each other and comparing it elements
* are equal.
* ** note that the internal iterator is not valid after calling this function.
* return values:
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new List in case of success.
*/
UniqueOrderedList uniqueOrderedListCreate(copyElements copyFunc,
                                          freeElements freeFunc,
                                          elementsEquals equalsFunc,
                                          elementGreaterThan greaterFunc)
{
    if( !copyFunc || !freeFunc || !equalsFunc || !greaterFunc )
    {
        return NULL;
    }

    UniqueOrderedList list = malloc(sizeof(*list));
    ElementList new_element_node = malloc(sizeof(*new_element_node));

    if (list == NULL || new_element_node == NULL)
    {
        free(list);
        free(new_element_node);
        return NULL;
    }
    list->copyFunction = copyFunc;
    list->freeFunction = freeFunc;
    list->equalsFunction = equalsFunc;
    list->greaterThanFunction = greaterFunc;
    list->element_list = new_element_node;
    list->size = 1;
    list->head = new_element_node;
    list->iterator = 1;
    return list;
}


void uniqueOrderedListDestroy(UniqueOrderedList list)
{
    if (list == NULL) return;

    for (ElementList head = uniqueOrderedListGetLowest(list);  head != NULL ; head = uniqueOrderedListGetNext(head))
    {
        list->freeFunction(head);
    }
    free(list);
}

/**
* Creates a copy of target list.
*
* The new copy will contain all the elements from the source list in the same
* order and will use the same functions as the original list for copying,
* freeing and comparing elements.
* ** note that the internal iterator of the new copy
*     is not valid after calling this function.
* return values:
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A List containing the same elements with same order.
*/
UniqueOrderedList uniqueOrderedListCopy(UniqueOrderedList list)
{
    if (list == NULL)
        return NULL;
    list->element_list = uniqueOrderedListGetLowest(list);
    UniqueOrderedList new_list = uniqueOrderedListCreate
            (list->copyFunction,
             list-> freeFunction,
             list->equalsFunction,
             list->greaterThanFunction);
    ElementList new_element = new_list->copyFunction(list->element_list->data);
    new_list->head = new_element;
    new_list->element_list = new_list->head;
    new_list->size = 0;
    while (list->element_list->next != NULL)
    {
        list->element_list = uniqueOrderedListGetNext(list);
        if (uniqueOrderedListInsert(new_list, list->element_list->data) == UNIQUE_ORDERED_LIST_SUCCESS)
            continue;
        else
            return NULL;
    }
    return new_list;
}

/**
* Returns the number of elements in a list.
* return values:
* 	-1 if the list passed is NULL.
* 	size of the list otherwise.
*/
int uniqueOrderedListSize(UniqueOrderedList list)
{
    if (list == NULL || list->element_list == NULL)
        return -1;
    list->element_list = uniqueOrderedListGetGreatest(list);
    list->element_list = uniqueOrderedListGetLowest(list);
    return list->size;
}

/**
 * Checks if an element exists in the list. The element will be
 * considered in the list if one of the elements in the list it determined equal
 * using the comparison function used to initialize the list.
 * return values:
 * 	true - if there exists an element which is equal to the element passed to the function.
 * 	false - otherwise.
 */
bool uniqueOrderedListContains(UniqueOrderedList list, Element element)
{
    if (list == NULL)
        return NULL;
    list->element_list = uniqueOrderedListGetLowest(list);
    if (list->element_list == NULL)
        return NULL;
    bool answer = false;
    while (list->element_list != NULL && !answer)
    {
        answer = list->equalsFunction(element, list->element_list->data);
        if (answer)
            return answer;
        list->element_list = uniqueOrderedListGetNext(list);
    }
    return answer;
}

/**
 * Inserts an element into the list if there is no element equals to it in the list.
 * the element is inserted in it's place according to the order determined by the
 * greater comparison function used to initialize the list.
 * return values:
 * UNIQUE_ORDERED_LIST_NULL_ARGUMENT - one of the arguments passed is NULL
 * UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS - there exists an element which is equal
 * 											 to the new element
 * UNIQUE_ORDERED_LIST_SUCCESS - in case of successful insertion.
 */
UniqueOrderedListResult uniqueOrderedListInsert(UniqueOrderedList list , Element element)
{
    if (list == NULL || element == NULL || list->element_list == NULL)
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    list->element_list = uniqueOrderedListGetLowest(list);
    while ( list->element_list != NULL)
    {
        if (uniqueOrderedListContains(list, element))
            return UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS;
        if (list->greaterThanFunction(element, list->element_list->data))
        {
            if (!list->greaterThanFunction(element, (list->element_list->next)->data) || (list->element_list->next) == NULL)
            {
                ElementList temp_element = list->copyFunction(element);
                temp_element->next = list->element_list->next->next;
                list->element_list->next = temp_element;
                list->size++;
                return UNIQUE_ORDERED_LIST_SUCCESS;
            }
        }
        else if (list->element_list == list->head)
        {
            ElementList new_element = list->copyFunction(element);
            new_element->next =list->head;
            list->head = new_element;
            list->element_list = new_element;
            list->size++;
        }
        list->element_list = uniqueOrderedListGetNext(list);
    }
}

/**
 * removes an element from the list if there is an element equals to it in the list.
 * the element removed is the one equals to the passed element according to the equals
 * function passed when initializing the list.
 * ** note that the internal iterator is not valid after calling this function.
 * return values:
 * UNIQUE_ORDERED_LIST_NULL_ARGUMENT - one of the arguments passed is NULL
 * UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST - there is no element which is equal
 * 											 to the passed element
 * UNIQUE_ORDERED_LIST_SUCCESS - in case of successful removal.
 */
UniqueOrderedListResult uniqueOrderedListRemove(UniqueOrderedList list, Element element)
{
    if ( list == NULL || element == NULL)
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    list->element_list = uniqueOrderedListGetLowest(list);
    if (list->equalsFunction(list->element_list->data, element))
    {
        list->head = uniqueOrderedListGetNext(list);
        list->freeFunction(list->element_list);
        list->size--;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    ElementList* support_node = malloc(sizeof(*support_node));
    while (list->element_list != NULL)
    {
        if (list->equalsFunction((list->element_list->next)->data, element))
        {
            support_node = list->element_list->next;
            list->element_list->next = (list->element_list->next)->next;
            list->freeFunction(support_node);
            list->size--;
            return UNIQUE_ORDERED_LIST_SUCCESS;
        }
        list->element_list = uniqueOrderedListGetNext(list);
    }
    list->freeFunction(support_node);
    return UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST;
}

/**
* Sets the internal iterator to the first (lowest) element and retrieves it.
*
* The list has an internal iterator (also called current element) to allow
* iteration over the list's elements. This function sets the iterator to point
* to the first (lowest) element in the list and return it.
* Use this to start iteraing over the list, searching from the lowest element of
* the list and/or get the first (lowest) element in the list.
* (To continue iteration use uniqueOrderedListGetNext)
* example:
* void f(UniqueOrderedList list) {
*   Element first = uniqueOrderedListGetLowest(list);
*   printf("The lowest element is at address %x\n", first);
* }
*
* return values:
* NULL is a NULL pointer was sent or the list is empty.
* The lowest element of the list otherwise
 */
Element uniqueOrderedListGetLowest(UniqueOrderedList list)
{
    if (list == NULL || list->element_list == NULL)
        return NULL;
    list->iterator = 1;
    return list->head;
}

/**
* Sets the internal iterator to the last (greatest) element and retrieves it.
* the next element of the element returned should be NULL.
* example:
* void f(UniqueOrderedList list) {
*   Element last = uniqueOrderedListGetGreatest(list);
*   printf("The greatest element is at address %x\n", last);
* }
*
* return values:
* NULL is a NULL pointer was sent or the list is empty.
* The greatest element of the list otherwise
 */
Element uniqueOrderedListGetGreatest(UniqueOrderedList list)
{
    if (list == NULL || list->element_list == NULL)
        return NULL;
    list->element_list = uniqueOrderedListGetLowest(list);
    while (list->element_list->next != NULL)
    {
        list->element_list = uniqueOrderedListGetNext(list);
    }
    list->size = list->iterator;
    return list->element_list;
}

/**
* Advances the list's iterator to the next element and return it
*
* return values
* NULL if reached the end of the list, the iterator is at an invalid state or
* a NULL sent as argument
* The next element on the list in case of success
*/
Element uniqueOrderedListGetNext(UniqueOrderedList list)
{
    if (list == NULL || list->element_list == NULL) return NULL;
    if (list->element_list->next != NULL)
    {
        list->iterator++;
        return list->element_list->next;
    }
    else return NULL;
}

/**
* Removes all elements from target list.
*/
void uniqueOrderedListClear(UniqueOrderedList list)
{
    if (list == NULL || list->element_list == NULL)
        return;
    list->element_list = uniqueOrderedListGetLowest(list);
    while (uniqueOrderedListRemove(list, list->element_list) == UNIQUE_ORDERED_LIST_SUCCESS)
    {
        continue;
    }
}
