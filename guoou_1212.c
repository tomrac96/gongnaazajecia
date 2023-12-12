#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"

void wypisz();
void vanish(teatr_wojenny);
plansza sory_memory(teatr_wojenny);
int ruszek(teatr_wojenny);
ruch dokad_przybyszu(teatr_wojenny);
void no_to_gramy(teatr_wojenny);
void main(){
    
    plansza teatr_wojenny;
    no_to_gramy(teatr_wojenny);
}

void no_to_gramy(plansza teatr_wojenny){
    int qniec=0;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
    do{

    ruszek(teatr_wojenny);
    if(ruszek(teatr_wojenny)==1)
        qniec++;
    teatr_wojenny.ruch_gracza_X=RUCH_BIALY;

    ruszek(teatr_wojenny);
    if(ruszek(teatr_wojenny)==1)
        qniec++;

    }while(qniec!=2);
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
        //teatr_wojenny=ruszek();         // tu uzuplenij jak powstanie f. ruszaj_sie()
        printf("\nRozkaz!");
        //printf("\nPanie Majorze, melduje ze ruch wykonano!!!");
        return staruch;
    }
    else{
        printf("\nPanie Majorze, nie da sie D:");
        printf("\nPowtorz rozkaz...\n");
        dokad_przybyszu(teatr_wojenny);
    }
}

int ruszek(plansza teatr_wojenny){
    ruch staruszek=dokad_przybyszu(teatr_wojenny);
    int i=staruszek.wierszyk;
    int j=staruszek.kolumnyk;
    int qn;
    if(staruszek.pas==TAK){
        if(RUCH_CZARNY)
         printf("\nGracz czarny pasuje");
        if(RUCH_BIALY)
         printf("\nGracz bialy pasuje");

        qn=1;
        return qn;
    }
    if(teatr_wojenny.plain[i][j]==PUSTE){
        printf("\nStawiam na puste");
        if(RUCH_CZARNY)
         teatr_wojenny.plain[i][j]=CZARNA;
        if(RUCH_BIALY)
         teatr_wojenny.plain[i][j]=BIALA;
    }
    else{
        printf("\nMajorze to zasadzka, ktos tu stoi!!!");
    }

}

