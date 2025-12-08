#include "f1.h"
#include <iostream>
using namespace std;



void createListTeam(ListTeam &L) {
    L.first = NULL;
    L.last = NULL;
}

bool isEmptyTeam(ListTeam L) {
    return (L.first == NULL);
}

adrTeam createElemenTeam(string name, string baseCountry, int founded, string liveryColors[3]) {
    adrTeam p = new ElemenTeam;
    p->info.name = name;
    p->info.baseCountry = baseCountry;
    p->info.founded = founded;
    p->info.liveryColors[0] = liveryColors[0];
    p->info.liveryColors[1] = liveryColors[1];
    p->info.liveryColors[2] = liveryColors[2];

    p->next = NULL;
    p->prev = NULL;
    p->firstRace = NULL;
    return p;
}

adrRace createElemenRace(int raceNumber, int points) {
    adrRace r = new ElemenRace;
    r->info.raceNumber = raceNumber;
    r->info.points = points;
    r->next = NULL;
    r->prev = NULL;
    return r;
}

adrTeam searchTeam(ListTeam L, string name) {
    adrTeam p = L.first;
    while (p != NULL) {
        if (p->info.name == name){
          return p;
        }
        p = p->next;
    }
    return NULL;
}

adrRace searchRace(adrTeam team, int raceNumber) {
    adrRace r = team->firstRace;
    while (r != NULL) {
        if (r->info.raceNumber == raceNumber) {
                return r;
        }
        r = r->next;
    }
    return NULL;
}

int maxPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0;
    }
    int mx = T->firstRace->info.points;
    adrRace r = T->firstRace->next;
    while (r != NULL) {
        if (r->info.points > mx) mx = r->info.points;
        r = r->next;
    }
    return mx;
}

int minPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0;
    }
    int mn = T->firstRace->info.points;
    adrRace r = T->firstRace->next;
    while (r != NULL) {
        if (r->info.points < mn) mn = r->info.points;
        r = r->next;
    }
    return mn;
}

float avgPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0;
    }
    int sum = 0, count = 0;
    adrRace r = T->firstRace;
    while (r != NULL) {
        sum += r->info.points;
        count++;
        r = r->next;
    }
    return (float)sum / count;
}

