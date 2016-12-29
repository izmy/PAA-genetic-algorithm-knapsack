//
// Created by Jaroslav Hrách on 26.12.16.
//

#ifndef GENETIKA_CCHROMOZOM_H
#define GENETIKA_CCHROMOZOM_H

#include <iostream>
#include "CVec.h"

using namespace std;

class CChromozom {
private:
    bool * geny;
    int delkaChromozomu;
    int fitnessHodnota;
public:
    CChromozom(int delkaChromozomu);
    ~CChromozom();
    void nahodnyChromozom();
    void kopie(CChromozom * chromozom);
    bool getGen(int poradi);
    void setGen(int poradi, bool novaHodnota);
    void fitness(CVec veci[], int kapacitaBatohu);
    int getFitness();
    void vypsatGeny();
};


#endif //GENETIKA_CCHROMOZOM_H
