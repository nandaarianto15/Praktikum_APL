#include <iostream>
using namespace std;

// struct untuk kelompokkan berbagai jenis tipe data yang diperlukan, contoh dalam database mirip seperti table
struct tableBarang {
    string namaBarang;
    string kondisi;
    int jumlah;
};

// prototype fungsi dan prosedur
int cariNamaBarang(const string namaBarang, const tableBarang namaBarangs[], int totalBarang);
int login();
int menu();
void lihatBarang();
void tambahBarang();
void updateBarang();
void hapusBarang();

// nilai tetap untuk array
const int maxArray = 50;

// deklarasi array, nama dan nim untuk fitur login, menentukan nilai awal variabel totalBarang dan totalLogin
tableBarang barang[maxArray];
string nama, nim, update;
int totalBarang = 0, totalLogin = 0, pilihan;

// fungsi main
int main() {
    login();

    return 0;
}

// fungsi untuk menampilkan menu dan CRUD
int menu() {
    cout << "\n===== PILIHAN MENU =====\n";
    cout << "1. Lihat Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Keluar\n";
    cin >> pilihan;
    
    // deklarasi dari tiap fungsi CRUD dan penggunaan rekursif
    switch (pilihan) {
        case 1:
            lihatBarang();
            menu();
            break;
        case 2:
            tambahBarang();
            menu();
            break;
        case 3: 
            updateBarang();
            menu();
            break;
        case 4:
            hapusBarang();
            menu();
            break;
        case 5:
            cout << "Terima Kasih.\n";
            return 0;

        default:
            cout << "Pilihan tidak valid.\n";
    }
    return 0;
}

// fungsi fitur login
int login() {
    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Nama : ";
        cin >> nama;
        cout << "NIM : ";
        cin >> nim;

        if ((nama == "nanda" || nama == "Nanda") && nim == "135") {
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

// fungsi untuk mencari index barang berdasarkan nama
int cariNamaBarang(const string namaBarang, const tableBarang namaBarangs[], int totalBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (namaBarangs[i].namaBarang == namaBarang) {
            return i;
        }
    }
    return -1; // jika barang tidak ditemukan
}

// prosedur untuk menampilkan semua daftar barang
void lihatBarang() {
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            cout << "Nama Barang : " << barang[i].namaBarang << " | Kondisi Barang : " << barang[i].kondisi << " | Jumlah Barang : " << barang[i].jumlah << endl;
        }
    } else {
        cout << "\nBelum ada barang di inventory\n";
    }
}

// prosedur untuk menambahkan barang baru
void tambahBarang() {
    if (totalBarang < maxArray) {
        cout << "Masukkan nama barang : ";
        cin >> barang[totalBarang].namaBarang;
        cout << "Masukkan jumlah barang : ";
        cin >> barang[totalBarang].jumlah;
        cout << "Kondisi barang : ";
        cin >> barang[totalBarang].kondisi;
        totalBarang++;
        cout << "Data barang berhasil di tambahkan.\n";
    } else {
        cout << "Penyimpanan penuh. Tidak dapat menambahkan data lagi.\n";
    }
}

// prosedur untuk mengubah data barang
void updateBarang() {
    cout << "Masukkan nama barang yang akan di ubah datanya : ";
    cin >> update;

    int index = cariNamaBarang(update, barang, totalBarang);
    if (index != -1) {
        cout << "Masukkan nama barang yang baru : ";
        cin >> barang[index].namaBarang;
        cout << "Masukkan jumlah barang yang baru : ";
        cin >> barang[index].jumlah;
        cout << "Kondisi barang yang baru : ";
        cin >> barang[index].kondisi;
        cout << "Data barang berhasil di update\n";
    } else {
        cout << "Nama barang tidak ditemukan\n";
    }
}

// prosedur untuk menghapus data barang
void hapusBarang() {
    cout << "Masukkan nama barang yang akan di hapus datanya : ";
    cin >> update;

    int index = cariNamaBarang(update, barang, totalBarang);
        if (index != -1) {
            for (int i = index; i < totalBarang - 1; ++i) {
                barang[i] = barang[i + 1];
            }
            totalBarang--;
            cout << "Data barang berhasil dihapus.\n";
        } else {
            cout << "Nama barang tidak ditemukan.\n";
    }
}