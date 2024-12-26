#include "graf.h"

void tampilkanMenu() {
    cout << "\nMenu Pilihan:\n";
    cout << "1. Tambahkan Tempat\n";
    cout << "2. Tambahkan Jalan\n";
    cout << "3. Print Graf\n";
    cout << "4. Cari Rute Terpendek\n";
    cout << "5. Hapus Lokasi yang bermasalah\n";
    cout << "0. Keluar\n";
    cout << "Pilih opsi: ";
}

int main() {
    graf G;
    initialGraf(G);

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string idSimpul;
                cout << "Masukkan nama tempat: ";
                cin >> idSimpul;
                tambahSimpul(G, idSimpul);
                cout << "Tempat \"" << idSimpul << "\" berhasil ditambahkan ke graf.\n";
                break;
            }

            case 2: {
                string idSumber, idTujuan;
                int bobot;
                cout << "Masukkan tempat asal: ";
                cin >> idSumber;
                cout << "Masukkan tempat tujuan: ";
                cin >> idTujuan;
                cout << "Masukkan bobot/jarak jalan: ";
                cin >> bobot;
                tambahSisi(G, idSumber, idTujuan, bobot);
                cout << "Jalan berhasil ditambahkan antara " << idSumber << " dan " << idTujuan << ".\n";
                break;
            }

            case 3:
                tampilkanGraf(G);
                break;

            case 4: {
                string asal, tujuan, b, a;
                cout << "Masukkan tempat asal: ";
                cin >> asal;
                cout << "Masukkan tempat tujuan: ";
                cin >> tujuan;
                cout << "Apakah ada tempat yang bermasalah? Y/N" << endl;
                cin >> a;
                if (a == "Y"){
                    cout << "Masukkan nama tempat yang ingin dihapus: ";
                    cin >> b;
                    hapusLokasi(G, b);
                    ruteTerpendek(G, asal, tujuan);
                } else if (a == "N"){
                    ruteTerpendek(G, asal, tujuan);
                }

                break;
            }

            case 5: {
                string namaTempat;
                cout << "Masukkan nama tempat yang ingin dihapus: ";
                cin >> namaTempat;
                hapusLokasi(G, namaTempat);
                break;
            }

            case 0:
                cout << "Terima kasih, program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}
