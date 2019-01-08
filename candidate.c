//
// Created by Or Aviv on 2018-12-30.
//

#include <stdbool.h>
#include "candidate.h"

struct candidate_t{
    int id;
    int preference;
};

Element copyCandidate (Element candidate)
{
    if(candidate == NULL)
        return NULL;
    Candidate new_candidatre = malloc(sizeof(*new_candidatre));
    if (new_candidatre == NULL)
        return NULL;
    new_candidatre = *(Candidate*)candidate;
    return new_candidatre;
}
void freeCandidate (Element candidate)
{
    free(candidate);
}
bool candidatesEqual(Element first_candidate, Element second_candidate)
{
    if (first_candidate == NULL || second_candidate == NULL)
        return NULL;
    if ( *(Candidate*)first_candidate == *(Candidate*)second_candidate)
        return true;
    else
        return false;
}
bool candiateGratearThan (Element first_candidate, Element second_candidate)
{
    if (first_candidate == NULL || second_candidate == NULL)
        return NULL;
    bool return_value;
    Candidate f_candidate = *(Candidate*)first_candidate;
    Candidate s_candidate = *(Candidate*)second_candidate;

    if (f_candidate->preference > s_candidate->preference)
        return_value = false;
    else
        return_value = true;

    free(f_candidate);
    free(s_candidate);
    return return_value;
}