#include <iostream>
#include <limits>
using namespace std;

// Struct untuk informasi barang
struct Barang {
    string namaBarang;
    string kondisi;
    int jumlah;
};

// Struct untuk data login
struct Login {
    string nama;
    string nim;
};

// Struct untuk menyimpan data inventaris
struct Inventaris {
    Barang barang;
    Login login;
};

// Nilai tetap untuk array
const int maxArray = 50;

// Deklarasi array pointer Inventaris untuk menyimpan data inventaris
Inventaris* daftarInventaris[maxArray];
int totalBarang = 0, totalLogin = 0, pilihan;

// Prototype fungsi dan prosedur
// Jadi penggunaan bintang 2 pada parameter fungsi tersebut untuk menunjukkan bahwa parameter yang diterima adalah sebuah array pointer dari pointer (pointer ke pointer).
int cariIndexBarang(const string& namaBarang);
int login(Inventaris** daftarInventaris);
int menu();
void lihatBarang(Inventaris** daftarInventaris, int totalBarang);
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang);
void updateBarang(Inventaris** daftarInventaris, int totalBarang);
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang);

// Fungsi main
int main() {
    login(daftarInventaris);
    return 0;
}

// Fungsi untuk menampilkan menu dan CRUD
int menu() {
    cout << "\n===== PILIHAN MENU =====\n";
    cout << "1. Lihat Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Keluar\n";
    cin >> pilihan;
    
    // Validasi input
    while (cin.fail() || pilihan < 1 || pilihan > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 5: ";
        cin >> pilihan;
    }

    // Deklarasi dari tiap fungsi CRUD dan penggunaan rekursif
    // Pada parameter fungsi tambah dan hapus, saya menggunakan Operator Address-of / operator alamat (&) 
    switch (pilihan) {
        case 1:
            lihatBarang(daftarInventaris, totalBarang);
            break;
        case 2:
            tambahBarang(daftarInventaris, &totalBarang);
            break;
        case 3: 
            updateBarang(daftarInventaris, totalBarang);
            break;
        case 4:
            hapusBarang(daftarInventaris, &totalBarang);
            break;
        case 5:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }

    // Rekursi menu setelah operasi selesai
    menu();
    return 0;
}

// Fungsi fitur login
int login(Inventaris** daftarInventaris) {
    // Alokasi memori dinamis untuk setiap objek Inventaris
    for (int i = 0; i < maxArray; ++i) {
        daftarInventaris[i] = new Inventaris;
    }

    totalBarang = 0;
    totalLogin = 0;

    // Saya juga menggunakan Operator Arrow (->) untuk mengakses anggota dari objek yang di tunjuk
    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Nama : ";
        cin >> daftarInventaris[totalLogin]->login.nama;
        cout << "NIM : ";
        cin >> daftarInventaris[totalLogin]->login.nim;

        if ((daftarInventaris[totalLogin]->login.nama == "nanda" || daftarInventaris[totalLogin]->login.nama == "Nanda") && daftarInventaris[totalLogin]->login.nim == "135") {
            cout << "Login berhasil!\n";
            cout << "\nSELAMAT DATANG DI INVENTORY SEKOLAH\n";
            menu();
            return 1;
        } else {
            cout << "Login gagal. Silakan coba lagi.\n";
            totalLogin++;
        }
    }

    if (totalLogin == 3) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti.\n";
        return 0;
    }
    return 0;
}

// Fungsi untuk mencari index barang berdasarkan nama
int cariIndexBarang(const string& namaBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (daftarInventaris[i]->barang.namaBarang == namaBarang) { // Disini juga terdapat penggunaan Operator Arrow (->)
            return i;
        }
    }
    return -1; // Jika barang tidak ditemukan
}

// Prosedur untuk menampilkan semua daftar barang
void lihatBarang(Inventaris** daftarInventaris, int totalBarang) {
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            // Disini juga terdapat penggunaan Operator Arrow (->) untuk menampilkan informasi dari setiap barang
            cout << "Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << endl;
        }
    } else {
        cout << "\nBelum ada barang di inventory\n";
    }
}

// Prosedur untuk menambahkan barang baru
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang) {
    // Ini adalah penggunaan Operator Dereference (*) pada *totalBarang untuk mengakses nilai yang di simpan di alamat memori yang di tunjuk oleh pointer totalBarang
    if (*totalBarang < maxArray) {
        cout << "Masukkan nama barang : ";
        cin.ignore();
        getline(cin, daftarInventaris[*totalBarang]->barang.namaBarang);
        
        cout << "Masukkan jumlah barang : ";
        while (!(cin >> daftarInventaris[*totalBarang]->barang.jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Kondisi barang : ";
        cin.ignore();
        getline(cin, daftarInventaris[*totalBarang]->barang.kondisi);

        (*totalBarang)++;
        cout << "Data barang berhasil ditambahkan.\n";
    } else {
        cout << "Penyimpanan penuh. Tidak dapat menambahkan data lagi.\n";
    }
}

// Prosedur untuk mengubah data barang
void updateBarang(Inventaris** daftarInventaris, int totalBarang) {
    string update;
    cout << "Masukkan nama barang yang akan diubah datanya : ";
    cin.ignore();
    getline(cin, update);

    int index = cariIndexBarang(update);
    if (index != -1) {
        cout << "Masukkan nama barang yang baru : ";
        getline(cin, daftarInventaris[index]->barang.namaBarang);
        
        cout << "Masukkan jumlah barang yang baru : ";
        while (!(cin >> daftarInventaris[index]->barang.jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Kondisi barang yang baru : ";
        cin.ignore();
        getline(cin, daftarInventaris[index]->barang.kondisi);
        cout << "Data barang berhasil diupdate.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus data barang
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang) {
    // Pada fungsi ini juga menerapkan Operator Dereference
    string update;
    cout << "Masukkan nama barang yang akan dihapus datanya : ";
    cin.ignore();
    getline(cin, update);

    int index = cariIndexBarang(update);
    if (index != -1) {
        for (int i = index; i < *totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        (*totalBarang)--;
        cout << "Data barang berhasil dihapus.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}
