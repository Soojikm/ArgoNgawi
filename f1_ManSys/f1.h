#ifndef F1_H_INCLUDED
#define F1_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// CHILD (Statistik Balapan) SLL
struct RaceStat {
    int noBalapan;
    string namaSirkuit;
    int posisi[2];    // Array untuk 2 driver
    int penalti[2];   // Array untuk 2 driver
    int poin[2];
};

typedef struct ElemenRace* adrRace;

struct ElemenRace {
    RaceStat info;
    adrRace next;
};

// PARENT (Tim F1) DLL
struct Team {
    string namaTeam;
    string negaraAsal;
    int tahunBerdiri;
    string warnaLivery[3];
    string noDriver[2];
};

typedef struct ElemenTeam* adrTeam;

struct ElemenTeam {
    Team info;
    adrTeam next;
    adrTeam prev;
    adrRace firstRace;
};

struct ListTeam {
    adrTeam first;
    adrTeam last;
};

// PARENT (TEAM)
void createListTeam(ListTeam &L);
bool isEmptyTeam(ListTeam L);
adrTeam createElemenTeam(string nama, string negara, int tahun, string warnaLivery[], string noDriver[]);
void addTeam(ListTeam &L, adrTeam p);
void deleteTeam(ListTeam &L, string namaTeam);
void updateTeam(adrTeam t, string namaBaru, string negaraBaru, int tahunBaru, string warnaBaru[], string noDriverBaru[]);
adrTeam searchTeam(ListTeam L, string namaTeam);
void displayTeams(ListTeam L);

// CHILD (RACE)
adrRace createElemenRace(int noBalapan, string namaSirkuit, int posisi[], int penalti[]);  // Input array
void addRace(adrTeam team, adrRace r);
void deleteRace(adrTeam team, int noBalapan);
void deleteAllRace(adrTeam team);
void updateRace(adrTeam team, int noBalapan, int posisiBaru[], int penaltiBaru[], ListTeam &L);
adrRace searchRace(adrTeam team, int noBalapan);

// STATISTIK POIN
int totalPoints(adrTeam T);
int maxPoint(adrTeam T);
int minPoint(adrTeam T);
float avgPoint(adrTeam T);
int hitungPoin(int posisi, int penalti);

//CEK POSISI
bool isPositionTaken(ListTeam L,adrRace self, int noBalapan, int posisi);  // cek kedua posisi

// FITUR SORTING & TAMPILAN
void showGlobalStandings(ListTeam L, int modeSort);
void showTeamsSortedByName(ListTeam L, int modeSort);
void showCircuitStandings(ListTeam L, string namaSirkuit);
void showRaceStatsByNo(ListTeam L, int noBalapan);

#endif // F1_H_INCLUDED
