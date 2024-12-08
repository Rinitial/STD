#include <iostream>
#include <string>
using namespace std;

#define info(P) P->info
#define next(P) P->next
#define simpulBerikut(P) P->simpulBerikut
#define sisiPertama(P) P->sisiPertama
#define simpulTujuan(P) P->simpulTujuan
#define first(G) G.first

typedef struct Simpul* adrSimpul;
typedef struct Sisi* adrSisi;
//s
struct Simpul {
    string info;
    adrSimpul simpulBerikut;
    adrSisi sisiPertama;
};

struct Sisi {
    adrSimpul simpulTujuan;
    int info;
    adrSisi next;
};

struct graf {
    adrSimpul first;
};

void initialGraf(graf &G) {
    first(G) = NULL;
}

adrSimpul alokasiSimpul(string id) {
    adrSimpul simpulBaru = new Simpul;
    info(simpulBaru) = id;
    simpulBerikut(simpulBaru) = NULL;
    sisiPertama(simpulBaru) = NULL;
    return simpulBaru;
}

void tambahSimpul(graf& G, string id) {
    adrSimpul simpulBaru = alokasiSimpul(id);
    if (first(G) == NULL) {
        first(G) = simpulBaru;
    } else {
        adrSimpul temp = first(G);
        while (simpulBerikut(temp) != NULL) {
            temp = simpulBerikut(temp);
        }
        simpulBerikut(temp) = simpulBaru;
    }
}

adrSisi alokasiSisi(int bobot, adrSimpul tujuan) {
    adrSisi sisiBaru = new Sisi;
    info(sisiBaru) = bobot;
    simpulTujuan(sisiBaru) = tujuan;
    next(sisiBaru) = NULL;
    return sisiBaru;
}

void tambahSisi(graf& G, string idSumber, string idTujuan, int bobot) {
    adrSimpul sumber = G.first;
    while (sumber != NULL && info(sumber) != idSumber) {
        sumber = simpulBerikut(sumber);
    }

    adrSimpul tujuan = G.first;
    while (tujuan != NULL && info(tujuan) != idTujuan) {
        tujuan = simpulBerikut(tujuan);
    }

    if (sumber != NULL && tujuan != NULL) {
        adrSisi sisiBaru = alokasiSisi(bobot, tujuan);
        next(sisiBaru) = sisiPertama(sumber);
        sisiPertama(sumber) = sisiBaru;

        adrSisi sisiBaru2 = alokasiSisi(bobot, sumber);
        next(sisiBaru2) = sisiPertama(tujuan);
        sisiPertama(tujuan) = sisiBaru2;
    } else {
        cout << "Error: Simpul sumber atau tujuan tidak ditemukan!" << endl;
    }
}

adrSimpul cariLokasi(graf G, string tempat) {
    adrSimpul current = first(G);
    while (current != NULL && info(current) != tempat) {
        current = simpulBerikut(current);
    }
    if (current != NULL) {
        return current;
    } else {
        return NULL;
    }
}

void ruteTerpendek(graf G, string awal, string akhir) {
    // Array untuk menyimpan jarak ke simpul
    int jarak[100];  // Asumsi jumlah simpul tidak lebih dari 100
    // Array untuk menyimpan simpul sebelumnya dalam rute terpendek
    string prev[100];  
    // Array untuk menandakan apakah simpul sudah diproses
    bool processed[100] = {false}; 

    // Inisialisasi jarak untuk semua simpul
    adrSimpul temp = G.first;
    int idx = 0;
    while (temp != NULL) {
        jarak[idx] = 999999;  // Set jarak semua simpul ke nilai besar (tak terhingga)
        prev[idx] = "";  // Set simpul sebelumnya ke NULL
        temp = simpulBerikut(temp);
        idx++;
    }

    // Set jarak simpul awal ke 0
    idx = 0;
    temp = G.first;
    while (temp != NULL) {
        if (info(temp) == awal) {
            jarak[idx] = 0;
            break;
        }
        temp = simpulBerikut(temp);
        idx++;
    }

    // Algoritma Dijkstra (dengan pendekatan array)
    while (true) {
        // Cari simpul dengan jarak terpendek yang belum diproses
        int minJarak = 999999;
        int minIdx = -1;
        temp = G.first;
        idx = 0;
        while (temp != NULL) {
            if (!processed[idx] && jarak[idx] < minJarak) {
                minJarak = jarak[idx];
                minIdx = idx;
            }
            temp = simpulBerikut(temp);
            idx++;
        }

        if (minIdx == -1) break; // Jika tidak ada simpul lagi yang perlu diproses

        // Tandai simpul tersebut sudah diproses
        processed[minIdx] = true;

        // Ambil simpul yang dipilih
        temp = G.first;
        idx = 0;
        while (temp != NULL && idx != minIdx) {
            temp = simpulBerikut(temp);
            idx++;
        }

        // Perbarui jarak untuk tetangga simpul
        adrSisi sisi = sisiPertama(temp);
        while (sisi != NULL) {
            int tetanggaIdx = -1;
            adrSimpul tetangga = simpulTujuan(sisi);
            idx = 0;
            adrSimpul temp2 = G.first;
            while (temp2 != NULL) {
                if (info(temp2) == info(tetangga)) {
                    tetanggaIdx = idx;
                    break;
                }
                temp2 = simpulBerikut(temp2);
                idx++;
            }

            if (tetanggaIdx != -1) {
                int jarakBaru = jarak[minIdx] + info(sisi);
                if (jarakBaru < jarak[tetanggaIdx]) {
                    jarak[tetanggaIdx] = jarakBaru;
                    prev[tetanggaIdx] = info(temp);
                }
            }

            sisi = next(sisi);
        }
    }

    // Rekonstruksi rute terpendek
    idx = 0;
    temp = G.first;
    while (temp != NULL) {
        if (info(temp) == akhir) {
            break;
        }
        temp = simpulBerikut(temp);
        idx++;
    }

    if (jarak[idx] == 999999) {
        cout << "Tidak ada rute terpendek dari " << awal << " ke " << akhir << endl;
    } else {
        cout << "Rute terpendek dari " << awal << " ke " << akhir << ": ";
        string path = akhir;
        while (prev[idx] != "") {
            path = prev[idx] + " -> " + path;
            // Mencari simpul sebelumnya
            temp = G.first;
            while (temp != NULL) {
                if (info(temp) == prev[idx]) {
                    break;
                }
                temp = simpulBerikut(temp);
            }
            idx = 0;
            while (temp != NULL) {
                temp = simpulBerikut(temp);
                idx++;
            }
        }
        cout << path << endl;
    }
}


void tampilkanGraf(const graf& G) {
    adrSimpul temp = G.first;
    while (temp != NULL) {
        cout << "Tempat: " << info(temp) << ":";
        adrSisi sisi = sisiPertama(temp);
        while (sisi != NULL) {
            cout << " -> " << info(simpulTujuan(sisi)) << "(" << info(sisi) << ")";
            sisi = next(sisi);
        }
        cout << endl;
        temp = simpulBerikut(temp);
    }
}

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

void hapusLokasi(graf &G, string simpul) {
    adrSimpul s = cariLokasi(G, simpul);

    if (s == NULL) {
        cout << "Error: Tempat yang ingin dihapus tidak ditemukan.\n";
        return;
    }

   //hapus semua sisi dari loksi
    adrSisi sisiTemp = sisiPertama(s);
    while (sisiTemp != NULL) {
        adrSisi sisiHapus = sisiTemp;
        sisiTemp = next(sisiTemp);
        delete sisiHapus;
    }
    sisiPertama(s) = NULL;

    // Hapus semua sisi dari seluruh simpul yang mengarah ke lokasi yang ingin dihpus
    adrSimpul curSimpul = first(G);
    while (curSimpul != NULL) {
        adrSisi prevSisi = NULL;
        adrSisi curSisi = sisiPertama(curSimpul);

        while (curSisi != NULL) {
            if (simpulTujuan(curSisi) == s) {
                if (prevSisi == NULL) { 
                    sisiPertama(curSimpul) = next(curSisi);
                } else {
                    next(prevSisi) = next(curSisi);
                }
                adrSisi sisiHapus = curSisi;
                curSisi = next(curSisi);
                delete sisiHapus;
            } else {
                prevSisi = curSisi;
                curSisi = next(curSisi);
            }
        }
        curSimpul = simpulBerikut(curSimpul);
    }

    // Hapus simpul dari graf
    if (first(G) == s) { 
        first(G) = simpulBerikut(s);
    } else {
        adrSimpul prevSimpul = first(G);
        while (simpulBerikut(prevSimpul) != s) {
            prevSimpul = simpulBerikut(prevSimpul);
        }
        simpulBerikut(prevSimpul) = simpulBerikut(s);
    }

    delete s;
    cout << "Tempat \"" << simpul << "\" berhasil dihapus dari graf.\n";
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
                int jumlah;
                cout << "Masukkan jumlah tempat yang ingin ditambahkan: ";
                cin >> jumlah;

                for (int i = 0; i < jumlah; ++i) {
                    string idSimpul;
                    cout << "Masukkan nama tempat (ID) ke-" << (i+1) << ": ";
                    cin >> idSimpul;
                    tambahSimpul(G, idSimpul);
                    cout << "Tempat \"" << idSimpul << "\" berhasil ditambahkan ke graf.\n";
                }
                break;
            }

            case 2: {
                cout << "\nDaftar Tempat:\n";
                adrSimpul temp = G.first;
                int no = 1;
                while (temp != NULL) {
                    cout << no++ << ". " << info(temp) << endl;
                    temp = simpulBerikut(temp);
                }  
                int pilihanAsal, pilihanTujuan;
                cout << "Masukkan nomor tempat asal: ";
                cin >> pilihanAsal;
                cout << "Masukkan nomor tempat tujuan: ";
                cin >> pilihanTujuan;
                adrSimpul asal = G.first;
                adrSimpul tujuan = G.first;
                int i = 1;
                while (asal != NULL && i < pilihanAsal) {
                    asal = simpulBerikut(asal);
                    i++;
                }
                i = 1;
                while (tujuan != NULL && i < pilihanTujuan) {
                    tujuan = simpulBerikut(tujuan);
                    i++;
                }
                if (asal != NULL && tujuan != NULL) {
                    int bobot;
                    cout << "Masukkan bobot/jarak jalan: ";
                    cin >> bobot;
                    tambahSisi(G, info(asal), info(tujuan), bobot);
                    cout << "Jalan berhasil ditambahkan antara " << info(asal) << " dan " << info(tujuan) << ".\n";
                }
                break;
            }

            case 3:
                tampilkanGraf(G);
                break;

            case 4: {
                string asal, tujuan;
                cout << "Masukkan tempat asal: ";
                cin >> asal;
                cout << "Masukkan tempat tujuan: ";
                cin >> tujuan;
                ruteTerpendek(G, asal, tujuan);
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
