//
// Created by Or Aviv on 2019-01-01.
//

#include <stdio.h>
#include <stdlib.h>
#include "uniqueOrderedList.h"


typedef struct uniqueOrderedList_t{
    Element data;
    struct uniqueOrderedList_t* next;
    copyElements copyFunction;
    freeElements freeFunction;
    elementsEquals equalsFunction;
    elementGreaterThan greaterThanFunction;
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
UniqueOrderedList uniqueOrderedListCreate(copyElements copyFunc, freeElements freeFunc, elementsEquals equalsFunc, elementGreaterThan greaterFunc)
{
    if( !copyFunc || !freeFunc || !equalsFunc || !greaterFunc )
    {
        return NULL;
    }

    UniqueOrderedList list = malloc(sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }

    list->copyFunction = copyFunc;
    list->freeFunction = freeFunc;
    list->equalsFunction = equalsFunc;
    list->greaterThanFunction = greaterFunc;

    return list;

}


void uniqueOrderedListDestroy(UniqueOrderedList list)
{
    if (list == NULL) return;

    for (Element head = list;  head != NULL ; head = uniqueOrderedListGetNext(head))
    {
        freeElements(head);
    }
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
    UniqueOrderedList new_list = uniqueOrderedListCreate
            (list->copyFunction,
             list-> freeFunction,
             list->equalsFunction,
             list->greaterThanFunction);
    UniqueOrderedList* new_list_head = new_list;
    UniqueOrderedList temp_list = list;
    while (temp_list != NULL)
    {
        new_list = temp_list;
        new_list = new_list->next;
        temp_list = temp_list->next;
    }
    free(temp_list);
    return new_list_head;
}

/**
* Returns the number of elements in a list.
* return values:
* 	-1 if the list passed is NULL.
* 	size of the list otherwise.
*/
int uniqueOrderedListSize(UniqueOrderedList list)
{
    if (list == NULL)
        return -1;
    int counter = 0;
    UniqueOrderedList temp_list = list;
    while (temp_list != NULL)
    {
        counter++;
        temp_list = temp_list->next;
    }
    free(temp_list);
    return counter;
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
    UniqueOrderedList temp_list = list;
    bool answer = false;
    while (temp_list != NULL && !answer)
    {
        answer = list->equalsFunction(element, temp_list->data);
        temp_list = temp_list->next;
    }
    free(temp_list);
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
    if (list == NULL || element == NULL)
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    UniqueOrderedList* head = list;
    while ( list != NULL)
    {
        if (list->equalsFunction(list->data, element))
            return UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS;
        if (list->greaterThanFunction(element, list->data))
        {
            if (!list->greaterThanFunction(element, (list->next)->data) || (list->next) == NULL)
            {
                UniqueOrderedList new_element = uniqueOrderedListCreate
                        (list->copyFunction,
                         list->freeFunction,
                         list->equalsFunction,
                         list->greaterThanFunction);
                new_element->data = element;
                new_element->next = list->next;
                list->next = new_element;
                list = head;
                free(head);
                return UNIQUE_ORDERED_LIST_SUCCESS;
            }
        }
        list = list->next;
    }
    list = head;
    free(head);
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
    UniqueOrderedList head = list;
    UniqueOrderedList* support_node = malloc(sizeof(*support_node));
    if (list->equalsFunction(list->data, element))
    {
        list = list->next;
        free(head);
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    while (list != NULL)
    {
        if (list->equalsFunction((list->next)->data, element))
        {
            support_node = list->next;
            list->next = (list->next)->next;
            free(support_node);
            list = head;
            free(head);
            return UNIQUE_ORDERED_LIST_SUCCESS;
        }
        list = list->next;
    }
    list = head;
    free(head);
    free(support_node);
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
Element uniqueOrderedListGetLowest(UniqueOrderedList);

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
Element uniqueOrderedListGetGreatest(UniqueOrderedList);

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
    return list->next;
}

/**
* Removes all elements from target list.
*/
void uniqueOrderedListClear(UniqueOrderedList);
