#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"

void wypisz();
void vanish(teatr_wojenny);
plansza sory_memory(teatr_wojenny);

void main(){
    
    plansza teatr_wojenny;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
}
