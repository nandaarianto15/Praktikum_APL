#include <iostream>
using namespace std;

// nilai tetap untuk array
const int maxArray = 50;

// struct untuk kelompokkan berbagai jenis data yang diperlukan, contoh dalam database ibarat kaya table
struct tableBarang {
    string namaBarang;
    string kondisi;
    int jumlah;
};

// fungsi void hanya untuk mengembalikan fungsi atau tampilkan informasi, tanpa mengembalikan nilai 
// untuk nyimpen menu aja, biar codingan gak berhamburan
void menu() {
    cout << "\n===== PILIHAN MENU =====\n";
    cout << "1. Lihat Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Keluar\n";
}

// fungsi untuk mencari index berdasarkan nama barang
int cariNamaBarang(const string namaBarang, const tableBarang namaBarangs[], int totalBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (namaBarangs[i].namaBarang == namaBarang) {
            return i;
        }
    }
    return 1;
}

// fungsi utama
int main() {
    // deklarasi array, nama dan nim untuk fitur login, menentukan nilai awal variabel totalBarang dan totalLogin
    tableBarang barang[maxArray];
    string nama, nim, update;
    int totalBarang = 0, totalLogin = 0, pilihan;
    
    // fitur login
    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Nama : ";
        cin >> nama;
        cout << "NIM : ";
        cin >> nim;

        if (nama == "nanda" && nim == "135" || nama == "Nanda" && nim == "135") {
            cout << "Login berhasil!\n";
            break;
        } else {
            cout << "Login gagal. Silakan coba lagi.";
            totalLogin++;
        }
    }

    if (totalLogin == 3) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti.";
        return 0;
    }

    // menu utama
    while (true) {
        menu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: // Tampilkan data barang
                if (totalBarang > 0) {
                    cout << "\n ===== Data Barang di Inventory Sekolah ===== \n";
                    for (int i = 0; i < totalBarang; i++) {
                        cout << "Nama Barang : " << barang[i].namaBarang << " | Kondisi Barang : " << barang[i].kondisi << " | Jumlah Barang : " << barang[i].jumlah << endl;
                    }
                } else {
                    cout << "\nBelum ada barang di inventory\n";
                }
                break;
            case 2: // Tambahkan data barang
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
                break;
            case 3: // Ubah data barang (berdasarkan nama barang)
                cout << "Masukkan nama barang yang akan di ubah : ";
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
            break;
        }
    }
}