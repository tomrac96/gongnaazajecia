#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"

void wypisz();
void vanish(plansza*);
plansza sory_memory(plansza*);
plansza ruszek(plansza,ruch);
ruch dokad_przybyszu(plansza);
void no_to_gramy(plansza);
plansza czy_bicie(plansza);

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
      else
        plac_boju=czy_bicie(teatr_wojenny);
    
    wypisz(&plac_boju);

    teatr_wojenny.ruch_gracza_X=RUCH_BIALY; ///KOLEJ NA DRUGIEGO GRACZA

    ruch staruszek2=dokad_przybyszu(teatr_wojenny);

     plac_boju=ruszek(teatr_wojenny,staruszek2);
     teatr_wojenny=plac_boju;
      if(plac_boju.qn==1)
        qniec++;
      else
        plac_boju=czy_bicie(teatr_wojenny);

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

    if(where[0]=='p' && where[1]=='a' && where[2]=='s'){ //SPRAWDZA CZY PAS
        ruch staruch={.pas=TAK};
        return staruch;
    }

    if(where[0]>='A' && where[0] < ('A' + SZEROKOSC_PLANSZY) && where[1] < ('0' //SPRAWDZA I INTERPRETUJE WARTOSC WPISANA PRZEZ UZYTK I PRZETWARZA NA KOORDYNATY
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
    int i=staruszek.kolumnyk;
    int j=staruszek.wierszyk;
    
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

plansza czy_bicie(plansza teatr_wojenny){
    plansza zbadane;
    plansza niby_zbite;
    int sus=0;

    int bity;                                     //kogo badamy
    int bijacy;
     if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
        bity=BIALA;
        bijacy=CZARNA;
     if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
        bity=CZARNA;
        bijacy=BIALA;

    for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++){
        if(teatr_wojenny.plain[i][j]==bity){
            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity ) //sprawdza czy ma sasiadow przyjaciol
                sus++;
            if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity )
                sus++;
            if(i+1<=SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity )
                sus++;
            if(j+1<=WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity )
                sus++;

            if(sus==0)
                niby_zbite.plain[i][j]=teatr_wojenny.plain[i][j];
        }
        
    }
    for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            if(teatr_wojenny.plain[i][j]==niby_zbite.plain[i][j])
                teatr_wojenny.plain[i][j]==PUSTE;

    return teatr_wojenny;
}
