#ifndef DEFINICJE

#define DEFINICJE

#define SZEROKOSC_PLANSZY 6
#define WYSOKOSC_PLANSZY 6

typedef enum { PUSTE, BIALA, CZARNA } wielkosc_planszy;
typedef enum { RUCH_GRACZ1, RUCH_GRACZ2 } kto_sie_rusza;
//https://pl.wikibooks.org/wiki/C/Typy_z%C5%82o%C5%BCone    opis jak działa enum   na tym mozna tez ruchy robic

typedef struct
{
    kto_sie_rusza ruch_gracza_X;
    wielkosc_planszy plansza[SZEROKOSC_PLANSZY][WYSOKOSC_PLANSZY];
} plansza;

klops
#endif
