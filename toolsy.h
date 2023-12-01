#ifndef TOOLSY
#define TOOLSY

#include<stdio.h>
#include "definicje.h"

void wypisz(plansza* teatr_wojenny){
for(int i=0;i<SZEROKOSC_PLANSZY;i++) //bedzie wypisywal cale wiersze po kolei od gory
    printf("%d",i);
}

#endif
