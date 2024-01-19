#ifndef OCENA //oceniam pozycje (kto by pomyslal)

#define OCENA

#include "toolsy.h"

int ocen_pozycje(plansza* teatr_wojenny)
{
    int kolka = 0, krzyzyki = 0, puste = 0;
    for(int kolumna = 0; kolumna < SZEROKOSC_PLANSZY; kolumna++)
        for(int wiersz = 0; wiersz < WYSOKOSC_PLANSZY; wiersz++)
            switch(teatr_wojenny->plain[kolumna][wiersz])
            {
                case BIALA:
                    kolka++; break;
                case CZARNA:
                    krzyzyki++; break;
                case PUSTE:
                    puste++; break;
            }
    if (!puste)
        return teatr_wojenny->ruch_gracza_X == RUCH_BIALY ? (kolka > krzyzyki ? 10 : (kolka < krzyzyki ? -10 : 0)) : (kolka < krzyzyki ? 10 : (kolka > krzyzyki ? -10 : 0));
    return (teatr_wojenny->ruch_gracza_X== RUCH_BIALY ? kolka - krzyzyki : krzyzyki - kolka);
}

#endif
