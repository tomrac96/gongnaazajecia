#ifndef TOOLSY
#define TOOLSY
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include "definicje.h"

plansza sory_memory(plansza *teatr_wojenny){
    return (plansza) { .ruch_gracza_X=RUCH_CZARNY};
}

void vanish(plansza *teatr_wojenny){
    for(int i=0;i<SZEROKOSC_PLANSZY;i++)
        for(int j=0;j<WYSOKOSC_PLANSZY;j++)
        teatr_wojenny->plain[i][j]=PUSTE;
        int kolumna = SZEROKOSC_PLANSZY >> 1, wiersz = WYSOKOSC_PLANSZY >> 1;
    /*teatr_wojenny->plain[kolumna][wiersz] = teatr_wojenny->plain[kolumna - 1][wiersz - 1] = BIALA;
    teatr_wojenny->plain[kolumna - 1][wiersz] = teatr_wojenny->plain[kolumna][wiersz - 1] = CZARNA;*/

   //return *teatr_wojenny;
}

void wypisz(plansza *teatr_wojenny)
{
    //話
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_PLANSZY; printf("="), i++);
    printf("+\n");
    
    for(int i = 0; i < WYSOKOSC_PLANSZY; i++)
    {
        printf("%2d|", i);
        for(int j = 0; j < SZEROKOSC_PLANSZY; j++)
            switch(teatr_wojenny->plain[j][i])
            {
                case PUSTE:
                    printf(" + ");
                    break;
                case BIALA:
                    printf(" O ");
                    break;
                case CZARNA:
                    printf(" か ");
                    break;
            }
        printf("|\n");
    }
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_PLANSZY; printf("="), i++);
    printf("+\n   ");
    for(int i = 0; i < SZEROKOSC_PLANSZY; printf(" %c ", 'A' + i++));
    printf("\nRuch przypada na %s\n", teatr_wojenny->ruch_gracza_X == RUCH_CZARNY ? "Gracz 2" : "Gracz 1");
    
}


#endif
