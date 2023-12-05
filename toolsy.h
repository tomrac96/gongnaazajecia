#ifndef TOOLSY
#define TOOLSY

#include<stdio.h>
#include "definicje.h"

void wypisz(plansza* teatr_wojenny){
for(int i=0;i<SZEROKOSC_PLANSZY;i++) //bedzie wypisywal cale wiersze po kolei od gory
    printf("%d",i);
}




void wypisz(plansza *teatr_wojenny)
{
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_PLANSZY; printf("-"), i++);
    printf("+\n");
    for(int i = 0; i < WYSOKOSC_PLANSZY; i++)
    {
        printf("%2d|", i);
        for(int j = 0; j < SZEROKOSC_PLANSZY; j++)
            switch(plansza->teatr_wojenny[j][i])
            {
                case PUSTE:
                    printf(" . ");
                    break;
                case BIALA:
                    printf(" B ");
                    break;
                case CZARNA:
                    printf(" C ");
                    break;
            }
        printf("|\n");
    }
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_PLANSZY; printf("-"), i++);
    printf("+\n   ");
    for(int i = 0; i < SZEROKOSC_PLANSZY; printf(" %c ", 'A' + i++));
    printf("\nRuch przypada na %c\n", teatr_wojenny->ruch_gracza_X == RUCH_GRACZ1 ? 'O' : 'X');
#endif
