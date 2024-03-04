#include <iostream>

using namespace std;

float CelciusToReamur(float celcius) {
    return 4.0 / 5.0 * celcius;
}

float CelciusToFahrenheit(float celcius) {
    return 9.0 / 5.0 * celcius + 32;
}

float CelciusToKelvin(float celcius) {
    return celcius + 273.15;
}

float ReamurToCelcius(float reamur) {
    return 5.0 / 4.0 * reamur;
}

float ReamurToFahrenheit(float reamur) {
    return 9.0 / 4.0 * reamur + 32;
}

float ReamurToKelvin(float reamur) {
    return 5.0 / 4.0 * reamur + 273.15;
}

float FahrenheitToCelcius(float farenheit) {
    return 5.0 / 9.0 * (farenheit - 32);
}

float FahrenheitToReamur(float farenheit) {
    return 4.0 / 9.0 * (farenheit - 32);
}

float FahrenheitToKelvin(float farenheit) {
    return 5.0 / 9.0 * (farenheit - 32) + 273.15;
}

float KelvinToCelcius(float kelvin) {
    return kelvin - 273.15;
}

float KelvinToReamur(float kelvin) {
    return 4.0 / 5.0 * (kelvin - 273.15);
}

float KelvinToFahrenheit(float kelvin) {
    return 9.0 / 5.0 * (kelvin - 273.15) + 32;
}

int main() {
    string nama, nim;
    int hitungLogin = 0;

    while (hitungLogin < 3) {
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
            hitungLogin++;
        }
    }

    if (hitungLogin == 3) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti.";
        return 0;
    }

    while (true) {
        int pilihan;
        float suhu;

        cout << "\nMenu Konversi Suhu:" << endl;
        cout << "1. Konversi Celcius" << endl;
        cout << "2. Konversi Reamur" << endl;
        cout << "3. Konversi Farenheit" << endl;
        cout << "4. Konversi Kelvin" << endl;
        cout << "5. Keluar" << endl;

        cout << "Pilih menu : ";
        cin >> pilihan;

        if (pilihan == 5) {
            cout << "Terima kasih telah menggunakan program. Sampai jumpa!\n";
            break;
        }

        cout << "Masukkan suhu: ";
        cin >> suhu;

        switch (pilihan) {
            case 1:
                cout << "\nHasil konversi :\n";
                cout << "Reamur: " << CelciusToReamur(suhu) << endl;
                cout << "Farenheit: " << CelciusToFahrenheit(suhu) << endl;
                cout << "Kelvin: " << CelciusToKelvin(suhu) << endl;
                break;
            case 2:
                cout << "\nHasil konversi :\n";
                cout << "Celcius: " << ReamurToCelcius(suhu) << endl;
                cout << "Farenheit: " << ReamurToFahrenheit(suhu) << endl;
                cout << "Kelvin: " << ReamurToKelvin(suhu) << endl;
                break;
            case 3:
                cout << "\nHasil konversi :\n";
                cout << "Celcius: " << FahrenheitToCelcius(suhu) << endl;
                cout << "Reamur: " << FahrenheitToReamur(suhu) << endl;
                cout << "Kelvin: " << FahrenheitToKelvin(suhu) << endl;
                break;
            case 4:
                cout << "\nHasil konversi :\n";
                cout << "Celcius: " << KelvinToCelcius(suhu) << endl;
                cout << "Reamur: " << KelvinToReamur(suhu) << endl;
                cout << "Farenheit: " << KelvinToFahrenheit(suhu) << endl;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    }

    return 0;
}
