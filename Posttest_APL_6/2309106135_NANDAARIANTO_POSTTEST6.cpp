#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

// Struct untuk informasi barang
struct Barang {
    int id_barang;
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
int cariIndexBarang(const int& namaBarang);
int login(Inventaris** daftarInventaris);
int menu();
int menuSorting();

// CRUD
void lihatBarang(Inventaris** daftarInventaris, int totalBarang);
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang);
void updateBarang(Inventaris** daftarInventaris, int* totalBarang);
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang);

// Metode Sorting
// Bubble Sort adalah metode sorting yang di bebaskan sementara quick dan insertion sort adalah main quest nya
void bubbleSortById(Inventaris** daftarInventaris, int totalBarang);
void quickSortByQuantity(Inventaris** daftarInventaris, int low, int high);
int partisi(Inventaris** daftarInventaris, int low, int high);
void insertionSortByName(Inventaris** daftarInventaris, int totalBarang);

int interpolationSearchAscending(Inventaris** daftarInventaris, int kiri, int kanan, int target);
int binarySearchDescending(Inventaris** daftarInventaris, int kiri, int kanan, int target);

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
        cout << "Input tidak valid. Masukkan angka antara 1 dan 5 : ";
        cin >> pilihan;
    }

    // Deklarasi dari tiap fungsi CRUD dan penggunaan rekursif
    // Pada parameter fungsi tambah, update dan hapus, saya menggunakan Operator Address-of / operator alamat (&) 
    switch (pilihan) {
        case 1:
            lihatBarang(daftarInventaris, totalBarang);
            break;
        case 2:
            tambahBarang(daftarInventaris, &totalBarang);
            break;
        case 3: 
            updateBarang(daftarInventaris, &totalBarang);
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

// Fungsi untuk mencari index barang berdasarkan id
int cariIndexBarang(const int& idBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (daftarInventaris[i]->barang.id_barang == idBarang) {
            return i;
        }
    }
    return -1; // Jika barang tidak ditemukan
}


// Fungi untuk menampilkan metode sorting
int menuSorting() {
    int pilihanSort;

    cout << "\n===== Pilihan Metode Sorting =====\n";
    cout << "1. Bubble Sort By ID(Ascending)\n";
    cout << "2. Quick Sort By Quantity (Descending)\n";
    cout << "3. Insertion Sort By Name(Ascending)\n";
    cout << "4. Exit\n";
    cin >> pilihanSort;
    
    // Validasi input
    while (cin.fail() || pilihanSort < 1 || pilihanSort > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 4 : ";
        cin >> pilihanSort;
    }

    switch (pilihanSort) {
        case 1:
            bubbleSortById(daftarInventaris, totalBarang);
            break;
        case 2:
            quickSortByQuantity(daftarInventaris, 0, totalBarang - 1);
            break;
        case 3: 
            insertionSortByName(daftarInventaris, totalBarang);
            break;
        case 4:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }
    return 0;
}

// Fungsi untuk menampilkan metode searching
int menuSearch() {
    int pilihanSearch, targetBinary, targetInterpolation, hasilPencarianBinary, hasilPencarianInterpolation;

    cout << "\n===== Pilihan Metode Searching =====\n";
    cout << "1. Interpolation Search (Ascending)\n";
    cout << "2. Binary Search (Descending)\n";
    cout << "3. Exit\n";
    cin >> pilihanSearch;

    // Membersihkan buffer sebelum melakukan operasi cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validasi input
    while (cin.fail() || pilihanSearch < 1 || pilihanSearch > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3 : ";
        cin >> pilihanSearch;
    }

    switch (pilihanSearch) {
        case 1:
            cout << "Masukkan ID barang yang ingin dicari : ";
            cin >> targetInterpolation;

            hasilPencarianInterpolation = interpolationSearchAscending(daftarInventaris, 0, totalBarang - 1, targetInterpolation);
            if (hasilPencarianInterpolation != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianInterpolation << endl;
                cout << "ID Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.id_barang << "| Nama Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.kondisi << endl;
            } else {
                cout << "Data tidak ditemukan. Data harus terurut secara Ascending dahulu" << endl;
            }
            break;

        case 2:
            cout << "Masukkan ID barang yang ingin dicari : ";
            cin >> targetBinary;

            hasilPencarianBinary = binarySearchDescending(daftarInventaris, 0, totalBarang - 1, targetBinary);
            if (hasilPencarianBinary != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianBinary << endl;
                cout << "ID Barang : " << daftarInventaris[hasilPencarianBinary]->barang.id_barang << "| Nama Barang : " << daftarInventaris[hasilPencarianBinary]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[hasilPencarianBinary]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[hasilPencarianBinary]->barang.kondisi << endl;
            } else {
                cout << "Data tidak ditemukan. Data harus terurut secara Descending dahulu" << endl;
            }
            break;

        case 3:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }
    return 0;
}

// Prosedur untuk menampilkan semua daftar barang
void lihatBarang(Inventaris** daftarInventaris, int totalBarang) {
    string pilihanSort, pilihanSearch;
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            // Disini juga terdapat penggunaan Operator Arrow (->) untuk menampilkan informasi dari setiap barang
            cout << "ID Barang : " << daftarInventaris[i]->barang.id_barang << "| Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << endl;
        }

        // Pilihan untuk user menampilkan data dengan metode sort Bubble, Quick, atau Insertion
        cout << "\nApakah anda ingin mengurutkan data menggunakan metode sorting ? [y/n]";
        cin >> pilihanSort;
        if (pilihanSort == "y" || pilihanSort == "Y") {
            // Pemanggilan fungsi menuSorting untuk memilih metode sorting
            menuSorting();

            // Setelah selesai sorting, tampilkan kembali data yang sudah diurutkan
            cout << "\n===== DATA BARANG SETELAH DIURUTKAN ===== \n";
            for (int i = 0; i < totalBarang; i++) {
                cout << "ID Barang : " << daftarInventaris[i]->barang.id_barang << "| Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << endl;
            }
        }

        cout << "\nApakah anda ingin mencari data ? [y/n]";
        cin >> pilihanSearch;

        if (pilihanSearch == "y" || pilihanSearch == "Y") {
            // Pemanggilan fungsi menuSearch untuk mencari barang
            menuSearch();
        }

    } else {
        cout << "\nBelum ada barang di inventory\n";
    }
}

// Prosedur untuk menambahkan barang baru
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang) {
    // Ini adalah penggunaan Operator Dereference (*) pada *totalBarang untuk mengakses nilai yang di simpan di alamat memori yang di tunjuk oleh pointer totalBarang
    if (*totalBarang < maxArray) {
        cout << "Masukkan ID barang : ";
        while (!(cin >> daftarInventaris[*totalBarang]->barang.id_barang)) {
            cout << "Input tidak valid. Masukkan ID barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

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
void updateBarang(Inventaris** daftarInventaris, int* totalBarang) {
    int update;
    cout << "Masukkan ID barang yang akan diubah datanya : ";
    cin >> update;

    int index = cariIndexBarang(update);
    if (index != -1) {
        cout << "Masukkan ID barang yang baru : ";
        while (!(cin >> daftarInventaris[index]->barang.id_barang)) {
            cout << "Input tidak valid. Masukkan ID barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Masukkan nama barang yang baru : ";
        cin.ignore(); // tambahkan ini untuk membersihkan newline dari buffer
        getline(cin, daftarInventaris[index]->barang.namaBarang);
        
        cout << "Masukkan jumlah barang yang baru : ";
        while (!(cin >> daftarInventaris[index]->barang.jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Kondisi barang yang baru : ";
        cin.ignore(); // tambahkan ini untuk membersihkan newline dari buffer
        getline(cin, daftarInventaris[index]->barang.kondisi);
        cout << "Data barang berhasil diupdate.\n";
    } else {
        cout << "ID barang tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus data barang
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang) {
    int hapus;
    cout << "Masukkan ID barang yang akan dihapus datanya : ";
    cin >> hapus;

    int index = cariIndexBarang(hapus);
    if (index != -1) {
        for (int i = index; i < *totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        (*totalBarang)--;
        cout << "Data barang berhasil dihapus.\n";
    } else {
        cout << "ID barang tidak ditemukan.\n";
    }
}


// Prosedur untuk Bubble Sort (Descending) berdasarkan ID Barang
void bubbleSortById(Inventaris** daftarInventaris, int totalBarang) {
    cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
    for (int i = 0; i < totalBarang; i++) {
        // Disini juga terdapat penggunaan Operator Arrow (->) untuk menampilkan informasi dari setiap barang
        cout << "ID Barang : " << daftarInventaris[i]->barang.id_barang << "| Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << endl;
    }

    for (int i = 0; i < totalBarang - 1; ++i) {
        for (int j = 0; j < totalBarang - i - 1; ++j) {
            if (daftarInventaris[j]->barang.id_barang > daftarInventaris[j + 1]->barang.id_barang) {
                Inventaris* swap = daftarInventaris[j];
                daftarInventaris[j] = daftarInventaris[j + 1];
                daftarInventaris[j + 1] = swap;
            }
        }
    }
}

// Prosedur untuk Quick Sort (Descending) berdasarkan Jumlah Barang
void quickSortByQuantity(Inventaris** daftarInventaris, int low, int high) {
    if (low < high) {
        int pivot = partisi(daftarInventaris, low, high);
        quickSortByQuantity(daftarInventaris, low, pivot - 1);
        quickSortByQuantity(daftarInventaris, pivot + 1, high);
    }
}

// Fungsi partisi untuk mendapatkan pivot
int partisi(Inventaris** daftarInventaris, int low, int high) {
    int pivot = daftarInventaris[high]->barang.jumlah;
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (daftarInventaris[j]->barang.jumlah > pivot) {
            ++i;
            swap(daftarInventaris[i], daftarInventaris[j]);
        }
    }
    swap(daftarInventaris[i + 1], daftarInventaris[high]);
    return i + 1;
}

// Prosedur untuk Insertion Sort (Ascending) berdasarkan Nama Barang
void insertionSortByName(Inventaris** daftarInventaris, int totalBarang) {
    cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
    for (int i = 0; i < totalBarang; i++) {
        // Disini juga terdapat penggunaan Operator Arrow (->) untuk menampilkan informasi dari setiap barang
        cout << "ID Barang : " << daftarInventaris[i]->barang.id_barang << "| Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << endl;
    }

    for (int i = 1; i < totalBarang; ++i) {
        Inventaris* key = daftarInventaris[i];
        int j = i - 1;
        while (j >= 0 && daftarInventaris[j]->barang.namaBarang > key->barang.namaBarang) {
            daftarInventaris[j + 1] = daftarInventaris[j];
            --j;
        }
        daftarInventaris[j + 1] = key;
    }
}

// Fungsi Binary Search untuk Data Terurut secara Descending
int binarySearchDescending(Inventaris** daftarInventaris, int kiri, int kanan, int target) {
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        // Cek apakah target berada di tengah
        if (daftarInventaris[tengah]->barang.id_barang == target)
            return tengah;

        // Jika target lebih kecil, abaikan setengah kanan
        if (daftarInventaris[tengah]->barang.id_barang < target)
            kanan = tengah - 1;
        // Jika target lebih besar, abaikan setengah kiri
        else
            kiri = tengah + 1;
    }
    // Jika tidak ditemukan
    return -1;
}


// Fungsi Interpolation Search untuk Data Terurut secara Ascending
int interpolationSearchAscending(Inventaris** daftarInventaris, int kiri, int kanan, int target) {
    while (kiri <= kanan && target >= daftarInventaris[kiri]->barang.id_barang && target <= daftarInventaris[kanan]->barang.id_barang) {
        // Hitung posisi perkiraan menggunakan rumus interpolasi yang benar untuk data terurut secara naik
        int posisi = kiri + ((float)(target - daftarInventaris[kiri]->barang.id_barang) / (daftarInventaris[kanan]->barang.id_barang - daftarInventaris[kiri]->barang.id_barang)) * (kanan - kiri);

        // Jika target ditemukan di posisi yang diprediksi
        if (daftarInventaris[posisi]->barang.id_barang == target)
            return posisi;
        // Jika target lebih kecil, cari di sebelah kiri
        else if (daftarInventaris[posisi]->barang.id_barang < target)
            kiri = posisi + 1;
        // Jika target lebih besar, cari di sebelah kanan
        else
            kanan = posisi - 1;
    }
    // Jika tidak ditemukan
    return -1;
}