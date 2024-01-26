#ifndef OCENA_POZYCJI_H
#define OCENA_POZYCJI_H

#include "definicje.h"

int ocen_pozycje(plansza* plansza) {
    int biale = 0, czarne = 0, puste = 0;

    for (int i = 0; i < SZEROKOSC_PLANSZY; i++) {
        for (int j = 0; j < WYSOKOSC_PLANSZY; j++) {
            switch (plansza->plain[i][j]) {
                case BIALA:
                    biale++;
                    break;
                case CZARNA:
                    czarne++;
                    break;
                case PUSTE:
                    puste++;
                    break;
            }
        }
    }

    if (puste == 0) {
        if (plansza->ruch_gracza_X == RUCH_BIALY) {
            if (biale > czarne)
                return 10;
            else if (biale < czarne)
                return -10;
            else
                return 0;
        } else {
            if (czarne > biale)
                return 10;
            else if (czarne < biale)
                return -10;
            else
                return 0;
        }
    } else {
        if (plansza->ruch_gracza_X == RUCH_BIALY)
            return biale - czarne;
        else
            return czarne - biale;
    }
}

#endif
