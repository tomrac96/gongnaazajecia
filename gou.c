#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"

void wypisz();
void vanish(teatr_wojenny);
plansza sory_memory(teatr_wojenny);
plansza ruszek(teatr_wojenny);
ruch dokad_przybyszu(teatr_wojenny);
void no_to_gramy(teatr_wojenny);

void main(){
    
    plansza teatr_wojenny;
    no_to_gramy(teatr_wojenny);
}

void no_to_gramy(plansza teatr_wojenny){
    int pomocnik;
    int qniec=0;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
    plansza plac_boju;

    do{
    
    teatr_wojenny.ruch_gracza_X=RUCH_CZARNY;
    ruch staruszek1=dokad_przybyszu(teatr_wojenny);

    plac_boju=ruszek(teatr_wojenny,staruszek1);
    teatr_wojenny=plac_boju;
      if(plac_boju.qn==1)
        qniec++;
    
    wypisz(&plac_boju);

    teatr_wojenny.ruch_gracza_X=RUCH_BIALY; ///KOLEJ NA DRUGIEGO GRACZA

    ruch staruszek2=dokad_przybyszu(teatr_wojenny);

     plac_boju=ruszek(teatr_wojenny,staruszek2);
     teatr_wojenny=plac_boju;
      if(plac_boju.qn==1)
        qniec++;

    wypisz(&plac_boju);

    }while(qniec!=2);
    printf("\nobydwaj gracze spasowali");
    printf("\nende tu sprawdzanie stanu posaidania pul (tak wiem u XD).");
}

ruch dokad_przybyszu(plansza teatr_wojenny){
    int w,k;
    char where[3];

    printf("\n\ngdzie chcesz sie postawic?");
    scanf("%s", &where);

    if(where[0]=='p' && where[1]=='a' && where[2]=='s'){
        ruch staruch={.pas=TAK};
        return staruch;
    }

    if(where[0]>='A' && where[0] < ('A' + SZEROKOSC_PLANSZY) && where[1] < ('0' 
    + WYSOKOSC_PLANSZY) && teatr_wojenny.plain[where[0] - 'A'][where[1] - '0'] == PUSTE){
        
        ruch staruch = { .wierszyk=where[1]-'0',.kolumnyk=where[0]-'A'};
        printf("\nRozkaz!\n");
        staruch.pas=NIE;
        return staruch;
    }
    else{
        printf("\nPanie Majorze, nie da sie D:");
        printf("\nPowtorz rozkaz...\n");
        dokad_przybyszu(teatr_wojenny);
    }
}

plansza ruszek(plansza teatr_wojenny,ruch staruszek){
    
    int i=staruszek.wierszyk;
    int j=staruszek.kolumnyk;
    if(staruszek.pas==TAK){
        teatr_wojenny.qn=1;
        teatr_wojenny.blad=NO;
        return teatr_wojenny;
    }
    if(teatr_wojenny.plain[i][j]==PUSTE){
        if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
         teatr_wojenny.plain[i][j]=CZARNA;
        if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
         teatr_wojenny.plain[i][j]=BIALA;
         teatr_wojenny.blad=NO;
    return teatr_wojenny;
    }
    if(teatr_wojenny.plain[i][j]!=PUSTE){
        ruszek(teatr_wojenny,staruszek);
    }
}

