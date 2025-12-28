#include <iostream>
#include <iomanip> // Untuk merapikan tabel
#include "f1.h"

using namespace std;

// info poin f1
int hitungPoin(int posisi, int penalti) {
    int poinDasar = 0;
    if (posisi == 1){
            poinDasar = 25;
    }else if (posisi == 2){
        poinDasar = 18;
    }else if (posisi == 3){
        poinDasar = 15;
    }else if (posisi == 4){
        poinDasar = 12;
    }else if (posisi == 5){
        poinDasar = 10;
    }else if (posisi == 6){
        poinDasar = 8;
    }else if (posisi == 7){
        poinDasar = 6;
    }else if (posisi == 8){
        poinDasar = 4;
    }else if (posisi == 9){
        poinDasar = 2;
    }else if (posisi == 10){
        poinDasar = 1;
    }else {
            poinDasar = 0;
    }
    int poinAkhir = poinDasar - penalti;
    if (poinAkhir < 0){
            poinAkhir = 0;
    }
    return poinAkhir;
}

// parent (team) -> dll
void createListTeam(ListTeam &L) {
    L.first = NULL;
    L.last = NULL;
}

bool isEmptyTeam(ListTeam L) {
    return (L.first == NULL);
}

adrTeam createElemenTeam(string nama, string negara, int tahun, string warnaLivery[], string noDriver[]) {
    adrTeam p = new ElemenTeam;
    p->info.namaTeam = nama;
    p->info.negaraAsal = negara;
    p->info.tahunBerdiri = tahun;
    for (int i=0; i<3; i++) {
        p->info.warnaLivery[i] = warnaLivery[i];
    }
    for (int i=0; i<2; i++) {
            p->info.noDriver[i] = noDriver[i];
    }
    p->next = NULL;
    p->prev = NULL;
    p->firstRace = NULL;
    return p;
}

void addTeam(ListTeam &L, adrTeam p) {
    if (isEmptyTeam(L)) {
        L.first = p;
        L.last = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

adrTeam searchTeam(ListTeam L, string namaTeam) {
    adrTeam p = L.first;
    while (p != NULL) {
        if (p->info.namaTeam == namaTeam) {
                return p;
        }
        p = p->next;
    }
    return NULL;
}

void deleteTeam(ListTeam &L, string namaTeam) {
    adrTeam p = searchTeam(L, namaTeam);
    if (p == NULL) {
        cout << "------------------------------" << endl;
        cout << "Tim tidak ditemukan" << endl;
        cout << "------------------------------" << endl;
    } else {
        deleteAllRace(p);
        if (p == L.first && p == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else if (p == L.first) {
            L.first = p->next;
            L.first->prev = NULL;
        } else if (p == L.last) {
            L.last = p->prev;
            L.last->next = NULL;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete p;
        cout << "------------------------------" << endl;
        cout << "Tim " << namaTeam << " berhasil dihapus " << endl;
        cout << "------------------------------" << endl;
    }
}

void updateTeam(adrTeam t, string namaBaru, string negaraBaru, int tahunBaru, string warnaBaru[], string noDriverBaru[]) {
    if (t != NULL) {
        t->info.namaTeam = namaBaru;
        t->info.negaraAsal = negaraBaru;
        t->info.tahunBerdiri = tahunBaru;
        for(int i=0; i<3; i++) {
                t->info.warnaLivery[i] = warnaBaru[i];
        }
        for(int i=0; i<2; i++) {
                t->info.noDriver[i] = noDriverBaru[i];
        }
        cout << "------------------------------" << endl;
        cout << "Data Tim berhasil diupdate" << endl;
        cout << "------------------------------" << endl;
    }
}

// child (race) -> sll
adrRace createElemenRace(int noBalapan, string namaSirkuit, string driverName, int posisi, int penalti) {
    adrRace r = new ElemenRace;
    r->info.noBalapan = noBalapan;
    r->info.namaSirkuit = namaSirkuit;
    r->info.namaDriver = driverName;
    r->info.posisi = posisi;
    r->info.poin = hitungPoin(posisi, penalti);
    r->next = NULL;
    return r;
}

void addRace(adrTeam team, adrRace r) {
    if (team != NULL) {
        if (team->firstRace == NULL) {
            team->firstRace = r;
        } else {
            adrRace p = team->firstRace;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = r;
        }
    }
}

adrRace searchRace(adrTeam team, int noBalapan) {
    if (team != NULL) {
        adrRace r = team->firstRace;
        while (r != NULL) {
            if (r->info.noBalapan == noBalapan){
                    return r;
            }
            r = r->next;
        }
    }
    return NULL;
}

void deleteRace(adrTeam team, int noBalapan) {
    if (team != NULL && team->firstRace != NULL) {
        adrRace p = team->firstRace;
        adrRace prec = NULL;
        bool found = false;

        // cari node
        while (p != NULL && !found) {
            if (p->info.noBalapan == noBalapan){
                    found = true;
            }else {
                prec = p;
                p = p->next;
            }
        }

        if (found) {
            if (prec == NULL) { // hapus elemen pertama
                team->firstRace = p->next;
            } else { // hapus elemen tengah / akhir
                prec->next = p->next;
            }
            delete p;
            cout << "------------------------------" << endl;
            cout << "Data Balapan berhasil dihapus" << endl;
            cout << "------------------------------" << endl;
        } else {
            cout << "------------------------------" << endl;
            cout << "Seri Balapan tidak ditemukan" << endl;
            cout << "------------------------------" << endl;
        }
    } else {
        cout << "------------------------------" << endl;
        cout << "Data kosong" << endl;
        cout << "------------------------------" << endl;
    }
}

void deleteAllRace(adrTeam team) {
    while (team->firstRace != NULL) {
        adrRace temp = team->firstRace;
        team->firstRace = team->firstRace->next;
        delete temp;
    }
}

void updateRace(adrTeam team, int noBalapan, int posisiBaru, int penaltiBaru) {
    adrRace r = searchRace(team, noBalapan);
    if (r != NULL) {
        r->info.posisi = posisiBaru;
        r->info.poin = hitungPoin(posisiBaru, penaltiBaru);
        cout << "\n------------------------------" << endl;
        cout << "Data Balapan berhasil diupdate" << endl;
        cout << "------------------------------\n" << endl;
    } else {
        cout << "\n------------------------------" << endl;
        cout << "Balapan tidak ditemukan" << endl;
        cout << "------------------------------\ns" << endl;
    }
}

// statistik
int totalPoints(adrTeam T) {
    int total = 0;
    adrRace r = T->firstRace;
    while (r != NULL) {
        total += r->info.poin;
        r = r->next;
    }
    return total;
}

int maxPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0;
    }

    int mx = T->firstRace->info.poin;
    adrRace r = T->firstRace->next;
    while (r != NULL) {
        if (r->info.poin > mx) {
            mx = r->info.poin;
        }
        r = r->next;
    }
    return mx;
}

int minPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0;
    }

    int mn = T->firstRace->info.poin;
    adrRace r = T->firstRace->next;
    while (r != NULL) {
        if (r->info.poin < mn) {
            mn = r->info.poin;
        }
        r = r->next;
    }
    return mn;
}

float avgPoint(adrTeam T) {
    if (T->firstRace == NULL){
            return 0.0;
    }

    int sum = 0, count = 0;
    adrRace r = T->firstRace;
    while (r != NULL) {
        sum += r->info.poin;
        count++;
        r = r->next;
    }
    return (float)sum / count;
}

bool isPositionTaken(ListTeam L, int noBalapan, int checkPosisi) {
    adrTeam p = L.first;
    while (p != NULL) {
        adrRace r = p->firstRace;
        while (r != NULL) {
            if (r->info.noBalapan == noBalapan && r->info.posisi == checkPosisi) {
                return true;
            }
            r = r->next;
        }
        p = p->next;
    }
    return false; // Posisi aman berarti kosong
}

// display dan sorting

void displayTeams(ListTeam L) {
    if (isEmptyTeam(L)) {
        cout << "Belum ada data tim" << endl;
        return;
    }
    adrTeam p = L.first;
    int i = 1;
    while (p != NULL) {
        cout << "\n========================================" << endl;
        cout << "TIM #" << i << ": " << p->info.namaTeam << " (" << p->info.negaraAsal << ")" << endl;
        cout << "Drivers: " << p->info.noDriver[0] << " & " << p->info.noDriver[1] << endl;
        cout << "----------------------------------------" << endl;
        cout << "Race History" << endl;
        adrRace r = p->firstRace;
        if (r == NULL) {
            cout << "  (Belum ada data balapan)" << endl;
        } else {
            while (r != NULL) {
                cout << "  -> Seri #" << r->info.noBalapan
                     << " (" << r->info.namaSirkuit << ") - "
                     << r->info.namaDriver << ": " // menampilkan Driver
                     << "P " << r->info.posisi << ", "
                     << r->info.poin << " pts" << endl;
                r = r->next;
            }
            cout << "----------------------------------------" << endl;
            cout << "Statistik Tim:" << endl;
            cout << "  Total Poin : " << totalPoints(p) << endl;
            cout << "  Rata-rata  : " << avgPoint(p) << endl;
            cout << "  Poin Tertinggi: " << maxPoint(p) << endl;
            cout << "  Poin Terendah : " << minPoint(p) << endl;
        }
        cout << "========================================" << endl;
        p = p->next;
        i++;
    }
}

// helper struct untuk sorting
struct TeamData {
    string nama;
    string negara;
    int totalPoin;
};

void showGlobalStandings(ListTeam L, int modeSort) {
    if (isEmptyTeam(L)) {
        cout << "\n------------------------------" << endl;
        cout << "Data Kosong" << endl;
        return;
    }

    int count = 0;
    adrTeam p = L.first;
    while(p != NULL){
            count++;
            p = p->next;
    }

    TeamData* data = new TeamData[count];
    p = L.first;
    int idx = 0;
    while(p != NULL) {
        data[idx].nama = p->info.namaTeam;
        data[idx].negara = p->info.negaraAsal;
        data[idx].totalPoin = totalPoints(p);
        p = p->next;
        idx++;
    }


    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            bool swapCondition = false;

            if (modeSort == 1) {
                if(data[j].totalPoin < data[j+1].totalPoin){
                    swapCondition = true;
                }
            } else {
                if(data[j].totalPoin > data[j+1].totalPoin){
                    swapCondition = true;
                }
            }

            if(swapCondition) {
                TeamData temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }

    string label = (modeSort == 1) ? "TERBESAR" : "TERKECIL";
    cout << "\n=== KLASEMEN TIM (" << label << ") ===" << endl;
    cout << "Rank | Tim (Negara)             | Total Poin" << endl;
    cout << "--------------------------------------------" << endl;
    for(int i=0; i<count; i++) {
        cout << setw(4) << i+1 << " | "
             << data[i].nama << " (" << data[i].negara << ") \t| "
             << data[i].totalPoin << endl;
    }
    cout << "--------------------------------------------" << endl;

    delete[] data;
}

void showTeamsSortedByName(ListTeam L, int mode) {
    if (isEmptyTeam(L)) {
        cout << "\n------------------------------" << endl;
        cout << "Data Kosong" << endl;
        return;
    }

    int count = 0;
    adrTeam p = L.first;
    while(p != NULL) { count++; p = p->next; }

    TeamData* data = new TeamData[count];
    p = L.first;
    int idx = 0;
    while(p != NULL) {
        data[idx].nama = p->info.namaTeam;
        data[idx].negara = p->info.negaraAsal;
        data[idx].totalPoin = totalPoints(p);
        p = p->next;
        idx++;
    }

    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            bool swapCondition = false;

            if (mode == 1) {
                if(data[j].nama > data[j+1].nama){
                    swapCondition = true;
                }
            } else {
                if(data[j].nama < data[j+1].nama){
                        swapCondition = true;
                }
            }

            if(swapCondition) {
                TeamData temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }

    string label = (mode == 1) ? "A - Z" : "Z - A";
    cout << "\n=== DAFTAR TIM (" << label << ") ===" << endl;
    cout << "No   | Tim (Negara)             | Total Poin" << endl;
    cout << "--------------------------------------------" << endl;
    for(int i=0; i<count; i++) {
        cout << setw(4) << i+1 << " | "
             << data[i].nama << " (" << data[i].negara << ") \t| "
             << data[i].totalPoin << endl;
    }
    cout << "--------------------------------------------" << endl;

    delete[] data;
}

// helper struct untuk sorting race
struct ResultData {
    string namaTeam;
    string namaDriver;
    int posisi;
    int poin;
};

void showCircuitStandings(ListTeam L, string namaSirkuit) {
    if (isEmptyTeam(L)) return;

    ResultData results[50];
    int count = 0;

    adrTeam p = L.first;
    while(p != NULL) {
        adrRace r = p->firstRace;
        while(r != NULL) {
            if(r->info.namaSirkuit == namaSirkuit) {
                results[count].namaTeam = p->info.namaTeam;
                results[count].namaDriver = r->info.namaDriver;
                results[count].posisi = r->info.posisi;
                results[count].poin = r->info.poin;
                count++;
            }
            r = r->next;
        }
        p = p->next;
    }

    if (count == 0) {
        cout << "\n-------------------------------------------" << endl;
        cout << "Tidak ada data balapan di Sirkuit " << namaSirkuit << endl;
        return;
    }

    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            if(results[j].posisi > results[j+1].posisi) {
                ResultData temp = results[j];
                results[j] = results[j+1];
                results[j+1] = temp;
            }
        }
    }

    cout << "\n=== HASIL BALAPAN: " << namaSirkuit << " ===" << endl;
    cout << "P   | Driver (Tim)               | Poin" << endl;
    cout << "----------------------------------------" << endl;
    for(int i=0; i<count; i++) {
        cout << setw(3) << results[i].posisi << " | "
             << results[i].namaDriver << " (" << results[i].namaTeam << ") \t| "
             << results[i].poin << endl;
    }
    cout << "----------------------------------------" << endl;
}

void showRaceStatsByNo(ListTeam L, int noBalapan) {
     if (isEmptyTeam(L)){
            return;
     }
    cout << "\n=== HASIL BALAPAN SERI #" << noBalapan << " ===" << endl;
    adrTeam p = L.first;
    bool foundAny = false;

    while(p != NULL) {
        adrRace r = p->firstRace;
        while(r != NULL) {
            if(r->info.noBalapan == noBalapan) {
                 cout << "Pos " << r->info.posisi << ": "
                      << r->info.namaDriver << " (" << p->info.namaTeam << ") - "
                      << r->info.poin << " pts" << endl;
                 foundAny = true;
            }
            r = r->next;
        }
        p = p->next;
    }
    if(!foundAny){
        cout << "Data tidak ditemukan" << endl;
    }
}
