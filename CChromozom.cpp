//
// Created by Jaroslav Hrách on 26.12.16.
//


#include "CChromozom.h"

CChromozom::CChromozom(int delkaChromozomu) {
    this->delkaChromozomu = delkaChromozomu;
    geny = new bool[delkaChromozomu];
};

CChromozom::~CChromozom() {
    delete geny;
};

void CChromozom::nahodnyChromozom() {
    for (int i = 0; i < delkaChromozomu; ++i) {
        int nahodnyStav = rand() % 2;
        geny[i] = nahodnyStav;
    }
}

void CChromozom::kopie(CChromozom *chromozom) {
    for (int i = 0; i < delkaChromozomu; ++i) {
        geny[i] = chromozom->getGen(i);
    }
}

bool CChromozom::getGen(int poradi) {
    return geny[poradi];
}

void CChromozom::setGen(int poradi, bool novaHodnota) {
    geny[poradi] = novaHodnota;
}

void CChromozom::fitness(CVec veci[], int kapacitaBatohu) {
    int tmpCena = 0;
    int tmpVaha = 0;
    for (int i = 0; i < delkaChromozomu; ++i){
        tmpCena += geny[i] ? veci[i].cena : 0;
        tmpVaha += geny[i] ? veci[i].vaha : 0;
    }
    fitnessHodnota = tmpVaha < kapacitaBatohu ? tmpCena : 0;
}

int CChromozom::getFitness() {
    return fitnessHodnota;
}

void CChromozom::vypsatGeny() {
    for (int i = 0; i < delkaChromozomu; ++i) {
        cout << geny[i] << " ";
    }
}
