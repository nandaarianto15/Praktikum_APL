#include <iostream>
using namespace std;

// struct untuk informasi barang
struct Barang {
    string namaBarang;
    string kondisi;
    int jumlah;
};

// struct untuk data login
struct Login {
    string nama;
    string nim;
};

// struct untuk menyimpan data inventaris
struct Inventaris {
    Barang barang;
    Login login;
};

// nilai tetap untuk array
const int maxArray = 50;

// deklarasi array untuk menyimpan data inventaris
Inventaris daftarInventaris[maxArray];
int totalBarang = 0, totalLogin = 0, pilihan;

// prototype fungsi dan prosedur
int cariIndexBarang(const string& namaBarang);
int login();
int menu();
void lihatBarang();
void tambahBarang();
void updateBarang();
void hapusBarang();

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
        cin >> daftarInventaris[totalLogin].login.nama;
        cout << "NIM : ";
        cin >> daftarInventaris[totalLogin].login.nim;

        if ((daftarInventaris[totalLogin].login.nama == "nanda" || daftarInventaris[totalLogin].login.nama == "Nanda") && daftarInventaris[totalLogin].login.nim == "135") {
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
int cariIndexBarang(const string& namaBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (daftarInventaris[i].barang.namaBarang == namaBarang) {
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
            cout << "Nama Barang : " << daftarInventaris[i].barang.namaBarang << " | Kondisi Barang : " << daftarInventaris[i].barang.kondisi << " | Jumlah Barang : " << daftarInventaris[i].barang.jumlah << endl;
        }
    } else {
        cout << "\nBelum ada barang di inventory\n";
    }
}

// prosedur untuk menambahkan barang baru
void tambahBarang() {
    if (totalBarang < maxArray) {
        cout << "Masukkan nama barang : ";
        cin >> daftarInventaris[totalBarang].barang.namaBarang;
        cout << "Masukkan jumlah barang : ";
        cin >> daftarInventaris[totalBarang].barang.jumlah;
        cout << "Kondisi barang : ";
        cin >> daftarInventaris[totalBarang].barang.kondisi;
        totalBarang++;
        cout << "Data barang berhasil ditambahkan.\n";
    } else {
        cout << "Penyimpanan penuh. Tidak dapat menambahkan data lagi.\n";
    }
}

// prosedur untuk mengubah data barang
void updateBarang() {
    string update;
    cout << "Masukkan nama barang yang akan diubah datanya : ";
    cin >> update;

    int index = cariIndexBarang(update);
    if (index != -1) {
        cout << "Masukkan nama barang yang baru : ";
        cin >> daftarInventaris[index].barang.namaBarang;
        cout << "Masukkan jumlah barang yang baru : ";
        cin >> daftarInventaris[index].barang.jumlah;
        cout << "Kondisi barang yang baru : ";
        cin >> daftarInventaris[index].barang.kondisi;
        cout << "Data barang berhasil diupdate.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}

// prosedur untuk menghapus data barang
void hapusBarang() {
    string update;
    cout << "Masukkan nama barang yang akan dihapus datanya : ";
    cin >> update;

    int index = cariIndexBarang(update);
    if (index != -1) {
        for (int i = index; i < totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        totalBarang--;
        cout << "Data barang berhasil dihapus.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}
