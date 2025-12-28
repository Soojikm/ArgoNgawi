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
    string namaTeam, negara, warnaLivery[3], noDriver[2], namaSirkuit, namaDriverPilihan;
    int tahunBerdiri, noBalapan, posisi, penalti, driverIndex;
    int subPilihan, pilihulang;
    adrTeam t;
    adrRace r;

    while (pilihan != 0) {
        menu();
        cin >> pilihan;

        if (pilihan == 1) {
            cout << endl;
            cout << endl;
            cout << "=== Data Tim Baru ===" << endl;
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
            cout << "------------------------------\n" << endl;

        } else if (pilihan == 2) {
            cout << endl;
            cout << "=== Data Balapan Baru ===" << endl;
            cout << "Masukkan Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);
            if (t != NULL) {
                cout << endl;
                cout << "== Driver yang Balapan ==" << endl;
                cout << "1. " << t->info.noDriver[0] << endl;
                cout << "2. " << t->info.noDriver[1] << endl;
                cout << "Pilih driver: ";
                cin >> driverIndex;

                if (driverIndex == 1){
                    namaDriverPilihan = t->info.noDriver[0];
                }else if (driverIndex == 2){
                    namaDriverPilihan = t->info.noDriver[1];
                }else {
                    cout << "Pilihan tidak sesuai, dikembalikan ke Driver 1." << endl;
                    namaDriverPilihan = t->info.noDriver[0];
                }
                cout << "Nomor Seri Balapan: ";
                cin >> noBalapan;
                cout << "Nama Sirkuit: ";
                cin >> namaSirkuit;
                cout << "Posisi Finish: ";
                cin >> posisi;
                cout << "Penalti Poin (0 jika tidak ada): ";
                cin >> penalti;

                if (isPositionTaken(L, noBalapan, posisi)) {
                    cout << "\n------------------------------" << endl;
                    cout << "GAGAL! Posisi " << posisi << " di Seri #" << noBalapan
                         << " sudah diisi oleh pembalap lain" << endl;
                    cout << "------------------------------\n" << endl;
                } else {
                    r = createElemenRace(noBalapan, namaSirkuit, namaDriverPilihan, posisi, penalti);
                    addRace(t, r);
                    cout << "\n------------------------------" << endl;
                    cout << "Data balapan berhasil ditambahkan" << endl;
                    cout << "------------------------------\n" << endl;
                }
            }else {
                cout << "\n------------------------------" << endl;
                cout << "Tim tidak ditemukan" << endl;
                cout << "------------------------------\n" << endl;
            }

        }else if (pilihan == 3) {
            cout << endl;
            displayTeams(L);

        }else if (pilihan == 4) {
            cout << endl;
            cout << "=== Pencarian Tim ===" << endl;
            cout << "Cari Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);
            if (t != NULL) {
                cout << "\n------------------------------" << endl;
                cout << "Tim Ditemukan: " << t->info.namaTeam << endl;
                cout << "Total Poin Konstruktor: " << totalPoints(t) << endl;
                cout << "------------------------------\n" << endl;
            } else {
                cout << "\n------------------------------" << endl;
                cout << "Tim tidak ditemukan" << endl;
                cout << "------------------------------\n" << endl;
            }

        }else if (pilihan == 5) {
            cout << endl;
            cout << "=== Penghapusan Tim ===" << endl;
            cout << "Hapus Nama Tim: ";
            cin >> namaTeam;
            deleteTeam(L, namaTeam);

        }else if (pilihan == 6) {
            cout << endl;
            cout << "=== Penghapusan Data Balapan ===" << endl;
            cout << "Masukkan Nama Tim: ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);
            if (t != NULL) {
                cout << "\n------------------------------" << endl;
                cout << "Seri Balapan yang dihapus: ";
                cin >> noBalapan;
                cout << "------------------------------\n" << endl;
                deleteRace(t, noBalapan);
            } else {
                cout << "\n------------------------------" << endl;
                cout << "Tim tidak ditemukan" << endl;
                cout << "------------------------------\n" << endl;
            }

        } else if (pilihan == 7) {
            cout << endl;
            cout << "=== Update Data Tim ===" << endl;
            cout << "Nama Tim yang ingin diupdate: ";
            cin >> namaTeam;
             t = searchTeam(L, namaTeam);
             if (t != NULL) {
                cout << "Nama Baru: ";
                cin >> namaTeam;
                cout << "Negara Baru: ";
                cin >> negara;
                cout << "Tahun Berdiri Baru: ";
                cin >> tahunBerdiri;
                cout << "Warna 1 Baru: ";
                cin >> warnaLivery[0];
                cout << "Warna 2 Baru: ";
                cin >> warnaLivery[1];
                cout << "Warna 3 Baru: ";
                cin >> warnaLivery[2];
                cout << "Driver 1 Baru: ";
                cin >> noDriver[0];
                cout << "Driver 2 Baru: ";
                cin >> noDriver[1];
                updateTeam(t, namaTeam, negara, tahunBerdiri, warnaLivery, noDriver);
             }

        } else if (pilihan == 8) {
            cout << endl;
            cout << "=== Update Data Balapan Tim ===" << endl;
            cout << "Masukkan Nama Tim : ";
            cin >> namaTeam;
            t = searchTeam(L, namaTeam);
            if (t != NULL) {
                cout << "Seri Balapan yang diupdate: ";
                cin >> noBalapan;
                r = searchRace(t, noBalapan);
                if (r != NULL) {
                    cout << "Posisi Finish baru: ";
                    cin >> posisi;
                    cout << "Penalti baru: ";
                    cin >> penalti;

                    bool crash = false;
                    if (posisi != r->info.posisi) { // hanya dicek jika posisi berubah
                        if (isPositionTaken(L, noBalapan, posisi)) {
                            crash = true;
                        }
                    }
                    if (crash) {
                        cout << "\n------------------------------" << endl;
                        cout << "GAGAL UPDATE! Posisi " << posisi << " sudah diisi pembalap lain." << endl;
                        cout << "------------------------------\n" << endl;
                    } else {
                        updateRace(t, noBalapan, posisi, penalti);
                    }
                }else {
                    cout << "Data balapan tidak ditemukan di tim ini" << endl;
                }
            }

        } else if (pilihan == 9) {
            cout << endl;
            cout << "\n=== KLASEMEN ===" << endl;
            cout << "1. Klasemen Tim (Poin Terbesar)" << endl;
            cout << "2. Klasemen Tim (Poin Terkecil)" << endl;
            cout << "3. Daftar Tim (A - Z)" << endl;
            cout << "4. Daftar Tim (Z - A)" << endl;
            cout << "5. Klasemen Balapan (Sirkuit)" << endl;
            cout << "6. Klasemen Balapan (Seri)" << endl;
            cout << "Pilih Info: ";
            cin >> subPilihan;

            if (subPilihan == 1) {
                showGlobalStandings(L, 1);
            } else if (subPilihan == 2) {
                showGlobalStandings(L, 2);
            } else if (subPilihan == 3) {
                showTeamsSortedByName(L, 1);
            } else if (subPilihan == 4) {
                showTeamsSortedByName(L, 2);
            } else if (subPilihan == 5) {
                cout << "Masukkan Nama Sirkuit: ";
                cin >> namaSirkuit;
                showCircuitStandings(L, namaSirkuit);
            } else if (subPilihan == 6) {
                cout << "Masukkan Nomor Seri: ";
                cin >> noBalapan;
                showRaceStatsByNo(L, noBalapan);
            } else {
                cout << "Pilihan tidak valid." << endl;
            }

        } else if (pilihan == 0) {
            cout << endl;
            cout << "------------------------------" << endl;
            cout << "Keluar program" << endl;
            cout << "------------------------------" << endl;
            cout << "~goodbye" << endl;
            cout << "havefun" << endl;
        } else {
            cout << "Pilihan tidak valid" << endl;
        }
    }
    return 0;
}
