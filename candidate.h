//
// Created by Or Aviv on 2018-12-30.
//

#ifndef MTMELECTIONS_CANDIDATE_H
#define MTMELECTIONS_CANDIDATE_H

#include "citizen.h"


typedef struct candidate_t* Candidate;

typedef Candidate CopyCandiate (Candidate candidate);
typedef void freeCandidate (Candidate candidate);
typedef bool candidatesEqual (Candidate first_candidate, Candidate second_candidate);
typedef bool candidateGreaterThan (Candidate first_candidate, Candidate second_candidate);

#endif //MTMELECTIONS_CANDIDATE_H
