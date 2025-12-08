#ifndef F1_H_INCLUDED
#define F1_H_INCLUDED


using namespace std;

//anaknya
struct RaceStat {
    int points;
    int raceNumber;
};

//ortunya
struct Team {
    string name;
    string baseCountry;
    int founded;
    string liveryColors[3];
    string NumberDriver[2];
};

typedef struct ElemenTeam* adrTeam;
typedef struct ElemenRace* adrRace;

struct ElemenRace {
    RaceStat info;
    adrRace next;
    adrRace prev;
};

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

// Parent List Ops
void createListTeam(ListTeam &L);
bool isEmptyTeam(ListTeam L);

// alokasi
adrTeam createElemenTeam(string name, string baseCountry, int founded, string liveryColors[3]);
adrRace createElemenRace(int raceNumber, int points);

// tambah
void addTeam(ListTeam &L, adrTeam p);
void addRace(adrTeam team, adrRace r);

// Update data team
void updateTeam(adrTeam t, string newName,string newBaseCountry, int newFounded, string newLiveryColors[3]);
void updateRace(adrTeam team, int raceNumber, int newRaceNumber, int newPoints);

// Hapus
void deleteRace(adrTeam team, int raceNumber);
void deleteAllRace(adrTeam team);
void deleteTeam(ListTeam &L, string teamName);

// Search
adrTeam searchTeam(ListTeam L, string name);
// Display
void displayTeams(ListTeam L);
// Statistik Hitungan
int totalPoints(adrTeam T);
int maxPoint(adrTeam T);
int minPoint(adrTeam T);
float avgPoint(adrTeam T);

#endif // F1_H_INCLUDED
