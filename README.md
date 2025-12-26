# 🏎️ F1 Team Management System

Program  untuk mengelola data tim Formula 1 beserta statistik hasil balapannya. Program ini dibangun menggunakan struktur data **Multi-Linked List** di mana setiap Tim dapat memiliki banyak catatan Balapan. Dibuat untuk memenuhi kriteria Tugas Besar Mata Kuliah Struktur Data

## Struktur Data
Program ini menggunakan model **Multi-Linked List 1-N**

## Fitur Utama
### 1. Manajemen Tim (Parent)
- **Insert:** Menambahkan tim baru.
- **Delete:** Menghapus tim beserta seluruh histori balapannya.
- **Search:** Mencari tim berdasarkan nama.
- **Update:** Mengubah data profil tim (Livery, Driver, dll).
- **Show All:** Menampilkan Tim beserta data balapannya.

### 2. Manajemen Balapan (Child)
- **Insert:** Menambahkan hasil balapan ke tim tertentu.
- **Delete:** Menghapus data balapan spesifik.
- **Update:** Mengubah poin pada balapan tertentu.

### 3. Statistik & Laporan
- **Total Poin:** Menghitung total poin konstruktor.
- **Rata-rata:** Menghitung rata-rata poin per balapan.
- **Max/Min:** Menentukan hasil balapan terbaik dan terburuk.

## Instalasi & Cara Menjalankan

1. **Clone Repositori atau Download**
   ```bash
   git clone https://github.com/wafdit/Tubes_AKA_Pinjol.git
   ```
2. **Buka terminal/CMD di folder proyek**
    ```bash
    cd Pinjol_Main
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
