# 🏎️ F1 Team Management System

Program  untuk mengelola data tim Formula 1 beserta statistik hasil balapannya. Program ini dibangun menggunakan struktur data **Multi-Linked List** di mana setiap Tim dapat memiliki banyak catatan Balapan. Dibuat untuk memenuhi kriteria Tugas Besar Mata Kuliah Struktur Data

## Struktur Data
Program ini menggunakan model **Multi Linked List 1-N** dengan spesifikasi sebagai berikut.
* **Relasi:** 1-N (One-to-Many).
* **List Parent (Tim):** Double Linked List (DLL).
* **List Child (Race):** Single Linked List (SLL).

## Fitur Utama
### 1. Manajemen Tim (Parent)
- **Insert:** Menambahkan tim baru beserta atribut lengkap (Negara, Tahun, Livery, Driver).
- **Delete:** Menghapus tim beserta seluruh histori balapannya.
- **Search:** Mencari tim berdasarkan nama.
- **Update:** Mengubah data profil tim (Livery, Driver, dll).
- **Show All:** Menampilkan Tim beserta data balapannya.

### 2. Manajemen Balapan (Child)
- **Insert:** Menambahkan hasil balapan ke tim tertentu(disertai pemilihan **Driver**).
- **Delete:** Menghapus data balapan spesifik.
- **Update:** Mengubah poin pada balapan tertentu.
- **Validasi** Mencegah input posisi ganda (Contoh: Tidak boleh ada dua pembalap Juara 1 di seri balapan yang sama).

### 3. Statistik & Laporan
- **Sistem Poin Otomatis:** Konversi posisi finish ke Poin F1 standar.
- **Statistik Tim:** Menghitung Total Poin, Rata-rata, Poin Tertinggi (Max), dan Terendah (Min).
- **Klasemen Global:** Mengurutkan tim berdasarkan Total Poin (Terbesar & Terkecil).
- **Sorting Nama:** Mengurutkan daftar tim berdasarkan abjad (A-Z & Z-A).
- **Laporan Sirkuit:** Menampilkan hasil balapan spesifik berdasarkan nama Sirkuit atau Nomor Seri Balapan.

## Instalasi & Cara Menjalankan

1. **Clone Repositori atau Download**
   ```bash
   git clone https://github.com/Soojikm/ArgoNgawi
   ```
2. **Buka terminal/CMD di folder proyek**
    ```bash
    cd f1_ManSys
    ```
3. **Compile** ketiga file (`main.cpp`, `f1.cpp`, `f1.h`) dengan perintah:

    ```bash
    g++ main.cpp f1.cpp -o f1_app
    ```

4.  **Jalankan**

    * **Windows:**
        ```bash
        f1_app.exe
        ```
    * **Linux/Mac:**
        ```bash
        ./f1_app
        ```

## Catatan Penggunaan (PENTING)
> **GUNAKAN UNDERSCORE (_) SEBAGAI PENGGANTI SPASI.**

**Contoh Input yang Benar:**
* Nama Tim: `Red_Bull_Racing`
* Negara: `Austria`

**Contoh Input yang Salah:**
* Nama Tim: `Red Bull Racing` (Program akan menganggap spasi sebagai pemisah input berikutnya)

## Authors
Project ini dikerjakan oleh 2 anggota sebagai berikut.
- Wafiq Aditiya Wiyono
- Wildan Bugi Rivansyah
