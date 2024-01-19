#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"
#include "legalna.h"

void wypisz();
void vanish(plansza*);
plansza sory_memory(plansza*);
plansza ruszek(plansza,ruch);
ruch dokad_przybyszu(plansza,int);
void no_to_gramy(plansza,plansza,plansza,plansza,legal);
plansza czy_bicie(plansza,plansza,plansza,plansza);
plansza bicie_po_sznurku(plansza,plansza*,plansza*,plansza*,int bity,int bijacy,int i,int j);

legal wyjatek(plansza,ruch,plansza,plansza,plansza);
legal czy_legal(plansza,ruch,plansza,plansza,plansza,ikea*);
legal superko(plansza,castorama*);
legal samobuj(plansza,ruch,plansza,plansza,plansza);


int czy_pelna(plansza);
void przepisz(plansza*,ikea*);

void main(){
    
    legal zgoda;

    plansza teatr_wojenny;
    vanish(&teatr_wojenny);
    plansza zbadane;
    vanish(&zbadane);
    plansza niby_zbite;
    vanish(&niby_zbite);
    plansza do_zbicia;
    vanish(&do_zbicia);

    no_to_gramy(teatr_wojenny,niby_zbite,zbadane,do_zbicia,zgoda);

}

void no_to_gramy(plansza teatr_wojenny,plansza niby_zbity,plansza zbadane,plansza do_zbicia,legal zgoda){
    castorama historia;
  
    int qniec=0;
    int numerek=0;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
    plansza plac_boju;
    
    do{
//======================================================================================================================
    teatr_wojenny.ruch_gracza_X=RUCH_CZARNY; //Gracz zaczynajacy
     numerek++;

        do{
            ruch staruszek1=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek1);
            /*++++++++++*/ przepisz(&plac_boju,&historia.zero); /*++++++++++*/
            if(numerek>=3)
                zgoda=czy_legal(teatr_wojenny,staruszek1,zbadane,niby_zbity,do_zbicia,&historia);
            else
                zgoda.czy_legalne=L;

        }while(zgoda.czy_legalne==NL);

    przepisz(&plac_boju,&historia.minus2);
   
    teatr_wojenny=plac_boju;
      if(plac_boju.qn==1 || czy_pelna==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
        qniec++;
      else
        plac_boju=czy_bicie(teatr_wojenny,niby_zbity,zbadane,do_zbicia);
    
    teatr_wojenny=plac_boju;
    wypisz(&plac_boju);  

//=========================================================================================================================
    teatr_wojenny.ruch_gracza_X=RUCH_BIALY; ///KOLEJ NA DRUGIEGO GRACZA
    numerek++;

     do{
            ruch staruszek2=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek2);
            /*++++++++++*/przepisz(&plac_boju,&historia.zero); /*++++++++++*/
            if(numerek>=3)
                zgoda=czy_legal(teatr_wojenny,staruszek2,zbadane,niby_zbity,do_zbicia,&historia);
            else
                zgoda.czy_legalne=L;

        }while(zgoda.czy_legalne==NL);
        
    przepisz(&plac_boju,&historia.minus1);
    

     teatr_wojenny=plac_boju;
      if(plac_boju.qn==1 || czy_pelna==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
        qniec++;
      else
        plac_boju=czy_bicie(teatr_wojenny,niby_zbity,zbadane,do_zbicia);

    teatr_wojenny=plac_boju;
    wypisz(&plac_boju);
//===========================================================================================================================
    
    

    }while(qniec!=2);

    printf("\nobydwaj gracze spasowali");
    printf("\nende tu sprawdzanie stanu posaidania pul (tak wiem u XD).");
}

ruch dokad_przybyszu(plansza teatr_wojenny,int numerek){
    int w,k;
    char where[3];
    printf("\n\nRuch numer %d.",numerek);
    printf(" Gdzie chcesz sie postawic? -->");
    scanf("%s", &where);
    ruch staruch={.pas=TAK};
    if(where[0]=='p' && where[1]=='a' && where[2]=='s'){ //SPRAWDZA CZY PAS
        
        return staruch;
    }

    if(where[0]>='A' && where[0] < ('A' + SZEROKOSC_PLANSZY) && where[1] < ('0' //SPRAWDZA I INTERPRETUJE WARTOSC WPISANA PRZEZ UZYTK (wielkie lit.) I PRZETWARZA NA KOORDYNATY
    + WYSOKOSC_PLANSZY) && teatr_wojenny.plain[where[0] - 'A'][where[1] - '0'] == PUSTE){
        
        ruch staruch = { .wierszyk=where[1]-'0',.kolumnyk=where[0]-'A'};
        printf("\nRozkaz!\n");
        staruch.pas=NIE;
        return staruch;
    }
    if(where[0]>='a' && where[0] < ('a' + SZEROKOSC_PLANSZY) && where[1] < ('0' //SPRAWDZA I INTERPRETUJE WARTOSC WPISANA PRZEZ UZYTK (male lit.) I PRZETWARZA NA KOORDYNATY
    + WYSOKOSC_PLANSZY) && teatr_wojenny.plain[where[0] - 'a'][where[1] - '0'] == PUSTE){
        
        ruch staruch = { .wierszyk=where[1]-'0',.kolumnyk=where[0]-'a'};
        printf("\nRozkaz!\n");
        staruch.pas=NIE;
        return staruch;
    }
    else{
        printf("\nPanie Majorze, nie da sie D:");
        printf("\nPowtorz rozkaz...\n");
        staruch=dokad_przybyszu(teatr_wojenny,numerek);
        return staruch;
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

