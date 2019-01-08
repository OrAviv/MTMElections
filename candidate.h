//
// Created by Or Aviv on 2018-12-30.
//

#ifndef MTMELECTIONS_CANDIDATE_H
#define MTMELECTIONS_CANDIDATE_H

#include "citizen.h"
#include <stdlib.h>

typedef struct candidate_t* Candidate;

Element copyCandidate (Element candidate);
void freeCandidate (Element candidate);
bool candidatesEqual(Element first_candidate, Element second_candidate);
bool candiateGratearThan (Element first_candidate, Element second_candidate);

#endif //MTMELECTIONS_CANDIDATE_H
