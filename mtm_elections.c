//
// Created by Or Aviv on 2018-12-30.
//

#include "mtm_elections.h"


struct mtm_elections_t{
    UniqueOrderedList cities;
};

typedef int (*RankFunc)(MtmElections, int, void*);
//
//MtmElections mtmElectionsCreate()
//{}
//
//void mtmElectionsDestroy(MtmElections mtmElections)
//{}
//
//MtmElectionsResult mtmElectionsAddCity(MtmElections mtmElections, const char* cityName, int cityId)
//{}
//
//MtmElectionsResult mtmElectionsAddCitizen(MtmElections mtmElections, const char* citizenName,
//                                          int citizenId, int citizenAge, int yearsOfEducation, int cityId)
//{}
//
//MtmElectionsResult MtmElectionsCitizenGetName(MtmElections mtmElections, int citizenId, char** name)
//
//MtmElectionsResult MtmElectionsCitizenGetCity(MtmElections mtmElections, int citizenId, int* cityId);
//
//MtmElectionsResult MtmElectionsCitizenGetAge(MtmElections mtmElections, int citizenI d, int* age);
//
//MtmElectionsResult MtmElectionsCitizenGetEducation(MtmElections mtmElections, int citizenId, int* yearsOfEducation);
//
//MtmElectionsResult mtmElectionsAddCandidate(MtmElections mtmElections, int candidateId, int cityId);
//
//MtmElectionsResult mtmElectionsWithdrawCandidate(MtmElections mtmElections, int candidateId, int cityId);
//
//MtmElectionsResult mtmElectionsSupportCandidate(MtmElections mtmElections, int citizenId, int candidateId, int priority);
//
//MtmElectionsResult mtmElectionsCancelSupport(MtmElections mtmElections, int citizenId, int candidateId);
//
//MtmElectionsResult mtmElectionsChangeAddress(MtmElections mtmElections, int citizenId, int cityId);
//
//int mtmElectionsRankByAge(MtmElections mtmElections, int citizen, void* pAge);
//
//UniqueOrderedList mtmElectionsPerformElections(MtmElections mtmElections, RankFunc rank, void* auxilaryData, const char* filename);
//
//MtmElectionsResult mtmElectionsMayorOfCity(MtmElections mtmElections, int cityId, int* mayor, const char* filename);