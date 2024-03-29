#ifndef DEFINICJE
#define DEFINICJE

#define SZEROKOSC_PLANSZY 6
#define WYSOKOSC_PLANSZY 6
//const int DEFEAT=-(SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY+100);
//const int VICTORY=-DEFEAT;
typedef enum { BEZP, ZAGR } save;
typedef enum {YES,NO} error;
typedef enum { TAK,NIE } koniec;
typedef enum { PUSTE, BIALA, CZARNA } wielkosc_planszy;
typedef enum { RUCH_CZARNY, RUCH_BIALY } kto_sie_rusza;
typedef enum {L,NL} konfident;
//https://pl.wikibooks.org/wiki/C/Typy_z%C5%82o%C5%BCone    opis jak działa enum   na tym mozna tez ruchy robic

typedef struct element2
{ 
    save bezpieczenstwo;
    error blad;
    int qn;
    kto_sie_rusza ruch_gracza_X;
    wielkosc_planszy plain[SZEROKOSC_PLANSZY][WYSOKOSC_PLANSZY];
} plansza;

typedef struct jysk{
    wielkosc_planszy plain[SZEROKOSC_PLANSZY][WYSOKOSC_PLANSZY];
} ikea;

typedef struct{
    struct jysk minus2;
    struct jysk minus1;
    struct jysk zero;
} castorama;

typedef struct
{   
   
    int wierszyk;
    int kolumnyk;
    koniec pas;
} ruch;

typedef struct element
{
    ruch move;
    struct element* nastepny;
} rozkaz;

typedef struct 
{
    konfident czy_legalne;
} legal;

#endif
