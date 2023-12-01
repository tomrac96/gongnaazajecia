#ifndef DEFINICJE

#define DEFINICJE

#define SZEROKOSC_POLA 6
#define WYSOKOSC_POLA 6

typedef enum { PUSTE, BIALY, CZARNY } wielkosc_planszy;
//https://pl.wikibooks.org/wiki/C/Typy_z%C5%82o%C5%BCone    opis jak działa enum   na tym mozna tez ruchy robic

typedef struct
{
    wielkosc_planszy pole[SZEROKOSC_POLA][WYSOKOSC_POLA];
} plansza;

#endif
