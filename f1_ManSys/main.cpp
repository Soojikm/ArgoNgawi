#include <iostream>
#include "f1.h"

using namespace std;

void menu() {
    cout << "\n=== SISTEM MANAJEMEN F1 ===" << endl;
    cout << "1. Tambah Tim Baru" << endl;
    cout << "2. Tambah Hasil Balapan" << endl;
    cout << "3. Tampilkan Semua Tim & Statistik" << endl;
    cout << "4. Cari Tim" << endl;
    cout << "5. Hapus Tim" << endl;
    cout << "6. Hapus Data Balapan" << endl;
    cout << "7. Update Data Tim" << endl;
    cout << "8. Update Hasil Balapan" << endl;
    cout << "9. Lihat Klasemen" << endl;
    cout << "0. Exit" << endl;
    cout << "------------------------------" << endl;
    cout << "Pilih menu: ";
}

int main() {
    ListTeam L;
    createListTeam(L);

    int pilihan = -1;
    int subPilihan;
    int tahunBerdiri, noBalapan;
    int posisi[2], penalti[2];

    string pil;

    string namaTeam, negara, namaSirkuit;
    string warnaLivery[3], noDriver[2];

    adrTeam t;
    adrRace r;

    while (pilihan != 0) {
        menu();
        cin >> pilihan;

        // menu 1
        if (pilihan == 1) {
            cout << "\n=== Data Tim Baru ===" << endl;
            cout << "Nama Tim: ";
            cin >> namaTeam;
            cout << "Negara Asal: ";
            cin >> negara;
            cout << "Tahun Berdiri: ";
            cin >> tahunBerdiri;
            cout << "Warna Livery 1: ";
            cin >> warnaLivery[0];
            cout << "Warna Livery 2: ";
            cin >> warnaLivery[1];
            cout << "Warna Livery 3: ";
            cin >> warnaLivery[2];
            cout << "Nama Driver 1: ";
            cin >> noDriver[0];
            cout << "Nama Driver 2: ";
            cin >> noDriver[1];

            t = createElemenTeam(namaTeam, negara, tahunBerdiri, warnaLivery, noDriver);
            addTeam(L, t);

            cout << "------------------------------" << endl;
            cout << "Tim berhasil ditambahkan" << endl;
            cout << "------------------------------" << endl;
        }

        // menu 2
        else if (pilihan == 2) {
            cout << "\n=== Data Balapan Baru ===" << endl;
            cout << "Masukkan Nama Tim: ";
            cin >> namaTeam;

            t = searchTeam(L, namaTeam);
            if (t == NULL) {
                cout << "Tim tidak ditemukan" << endl;
                continue;
            }

            cout << "Nomor Seri Balapan: ";
            cin >> noBalapan;
            cout << "Nama Sirkuit: ";
            cin >> namaSirkuit;

            for (int i = 0; i < 2; i++) {
                cout << "Posisi Finish " << t->info.noDriver[i] << ": ";
                cin >> posisi[i];
                cout << "Penalti " << t->info.noDriver[i] << ": ";
                cin >> penalti[i];
            }

            bool crash = false;
            for (int i = 0; i < 2; i++) {
                if (isPositionTaken(L, NULL, noBalapan, posisi[i])) {
                    crash = true;
                }
            }

            if (crash) {
                cout << "GAGAL! Posisi sudah dipakai pembalap lain" << endl;
            }
            else if (searchRace(t, noBalapan) != NULL) {
                cout << "GAGAL! Seri balapan sudah ada" << endl;
            }
            else {
                r = createElemenRace(noBalapan, namaSirkuit, posisi, penalti);
                addRace(t, r);
                cout << "Data balapan berhasil ditambahkan" << endl;
            }
        }

        // menu 3
        else if (pilihan == 3) {
            displayTeams(L);
        }

        // menu 4
        else if (pilihan == 4) {
            cout << "Cari Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);

            if (t != NULL) {
                cout << "Tim ditemukan: " << t->info.namaTeam << endl;
                cout << "Total poin: " << totalPoints(t) << endl;
            } else {
                cout << "Tim tidak ditemukan" << endl;
            }
        }

        // menu 5
        else if (pilihan == 5) {
            cout << "Nama Tim yang dihapus: ";
            cin >> namaTeam;
            deleteTeam(L, namaTeam);
        }

        // menu 6
        else if (pilihan == 6) {
            cout << "Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);

            if (t != NULL) {
                cout << "Seri Balapan: ";
                cin >> noBalapan;
                deleteRace(t, noBalapan);
            } else {
                cout << "Tim tidak ditemukan" << endl;
            }
        }

        // menu 7
        else if (pilihan == 7) {
            cout << "Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);

            if (t != NULL) {
                cout << "Nama Baru: ";
                cin >> namaTeam;
                cout << "Negara Baru: ";
                cin >> negara;
                cout << "Tahun Baru: ";
                cin >> tahunBerdiri;
                cout << "Warna 1: ";
                cin >> warnaLivery[0];
                cout << "Warna 2: ";
                cin >> warnaLivery[1];
                cout << "Warna 3: ";
                cin >> warnaLivery[2];
                cout << "Driver 1: ";
                cin >> noDriver[0];
                cout << "Driver 2: ";
                cin >> noDriver[1];

                updateTeam(t, namaTeam, negara, tahunBerdiri, warnaLivery, noDriver);

                cout << "Apakah ingin menghapus data race?(y/n)";
                cin >> pil;
                if (pil == "y"){
                    deleteAllRace(t);
                }
            }
        }

        // menu 8
        else if (pilihan == 8) {
            cout << "Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);

            if (t != NULL) {
                cout << "Seri Balapan: ";
                cin >> noBalapan;

                r = searchRace(t, noBalapan);
                if (r != NULL) {
                    for (int i = 0; i < 2; i++) {
                        cout << "Posisi baru " << t->info.noDriver[i] << ": ";
                        cin >> posisi[i];
                        cout << "Penalti baru: ";
                        cin >> penalti[i];
                    }
                    updateRace(t, noBalapan, posisi, penalti, L);
                } else {
                    cout << "Balapan tidak ditemukan" << endl;
                }
            }
        }

        // menu 9
        else if (pilihan == 9) {
            cout << "1. Poin Terbesar\n2. Poin Terkecil\n3. A-Z\n4. Z-A\n";
            cout << "Pilih klasemen: ";
            cin >> subPilihan;

            if (subPilihan == 1){
                    showGlobalStandings(L, 1);
            }
            else if (subPilihan == 2) {
                    showGlobalStandings(L, 2);
            }
            else if (subPilihan == 3) {
                    showTeamsSortedByName(L, 1);
            }
            else if (subPilihan == 4) {
                    showTeamsSortedByName(L, 2);
            }
        }

        // exit
        else if (pilihan == 0) {
            cout << "\nKeluar program" << endl;
            cout << "\nGoodByeee" << endl;
        }

        else {
            cout << "Pilihan tidak valid" << endl;
        }
    }

    return 0;
}
