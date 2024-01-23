#ifndef OCENA //oceniam pozycje (kto by pomyslal)

#define OCENA

#include "toolsy.h"

int ocen_pozycje(plansza* teatr_wojenny)
{
    int bialka = 0, czarnka = 0, puste = 0;
    for(int kolumna = 0; kolumna < SZEROKOSC_PLANSZY; kolumna++)
        for(int wiersz = 0; wiersz < WYSOKOSC_PLANSZY; wiersz++)
            switch(teatr_wojenny->plain[kolumna][wiersz])
            {
                case BIALA:
                    bialka++; break;
                case CZARNA:
                    czarnka++; break;
                case PUSTE:
                    puste++; break;
            }
    if (!puste)
        return teatr_wojenny->ruch_gracza_X == RUCH_BIALY ? (bialka > czarnka ? 10 : (bialka < czarnka ? -10 : 0)) : (bialka < czarnka ? 10 : (bialka > czarnka ? -10 : 0));
    return (teatr_wojenny->ruch_gracza_X== RUCH_BIALY ? bialka - czarnka : czarnka - bialka);
}

#endif
