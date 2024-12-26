#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <string>

#define INT_MAX 2147483647
using namespace std;


#define info(P) P->info
#define next(P) P->next
#define simpulBerikut(P) P->simpulBerikut
#define sisiPertama(P) P->sisiPertama
#define simpulTujuan(P) P->simpulTujuan
#define first(G) G.first

// Deklarasi tipe data
typedef struct Simpul* adrSimpul;
typedef struct Sisi* adrSisi;

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


void initialGraf(graf &G);
adrSimpul alokasiSimpul(string id);
void tambahSimpul(graf& G, string id);
adrSisi alokasiSisi(int bobot, adrSimpul tujuan);
void tambahSisi(graf& G, string idSumber, string idTujuan, int bobot);
adrSimpul cariLokasi(graf G, string tempat);
void ruteTerpendek(graf G, string awal, string akhir);
void tampilkanGraf(const graf& G);
void hapusLokasi(graf &G, string simpul);

#endif
