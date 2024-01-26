#ifndef TOOLSY
#define TOOLSY
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include "definicje.h"

void przepisz_plansze(plansza *z, plansza *d0){
    for(int i=0;i<SZEROKOSC_PLANSZY;i++)
        for(int j=0;j<WYSOKOSC_PLANSZY;j++)
            d0->plain[j][i]=z->plain[j][i];
}


void przepisz(plansza *z,ikea *d0){
     for(int i=0;i<SZEROKOSC_PLANSZY;i++)
        for(int j=0;j<WYSOKOSC_PLANSZY;j++)
            d0->plain[j][i]=z->plain[j][i];
}

plansza sory_memory(plansza *teatr_wojenny){
    return (plansza) { .ruch_gracza_X=RUCH_CZARNY };
}

void vanish(plansza *poletko){
    for(int i=0;i<SZEROKOSC_PLANSZY;i++)
        for(int j=0;j<WYSOKOSC_PLANSZY;j++)
        poletko->plain[i][j]=PUSTE;
        int kolumna = SZEROKOSC_PLANSZY >> 1, wiersz = WYSOKOSC_PLANSZY >> 1;
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
                    printf(" ⚈ ");
                    break;
                case CZARNA:
                    printf(" ⚆ ");
                    break;
            }
        printf("|\n");
    }
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_PLANSZY; printf("="), i++);
    printf("+\n   ");
    for(int i = 0; i < SZEROKOSC_PLANSZY; printf(" %c ", 'A' + i++));
    printf("\nRuch przypada na %s\n", teatr_wojenny->ruch_gracza_X == RUCH_CZARNY ? "Gracza BIALEGO" : "Gracza CZARNEGO");
    
}

plansza postaw_sie(plansza teatr_wojenny,ruch r0){
    if(teatr_wojenny.ruch_gracza_X=RUCH_BIALY)
        teatr_wojenny.plain[r0.kolumnyk][r0.wierszyk]=BIALA;
    else if(teatr_wojenny.ruch_gracza_X=RUCH_CZARNY)
        teatr_wojenny.plain[r0.kolumnyk][r0.wierszyk]=CZARNA;

    return teatr_wojenny;
}


plansza bicie_po_sznurku(plansza teatr_wojenny,plansza *niby_zbite,plansza *zbadane,plansza *do_zbicia, int bity,int bijacy,int i,int j){ // to funkcja sprawdzajaca kolezkow pierwotnie badanego kamucha
    int sojuz=0,pusteczka=0;

            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity && teatr_wojenny.plain[i-1][j]!=niby_zbite->plain[i-1][j]){ //sprawdza czy ma sasiadow przyjaciol
               
                if(teatr_wojenny.plain[i-1][j]!=zbadane->plain[i-1][j]){ 
                    zbadane->plain[i][j]=teatr_wojenny.plain[i][j];
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,do_zbicia,bity,bijacy,i-1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    } }
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity && teatr_wojenny.plain[i][j-1]!=niby_zbite->plain[i][j-1]){
                
                if(teatr_wojenny.plain[i][j-1]!=zbadane->plain[i][j-1]){ 
                 zbadane->plain[i][j]=teatr_wojenny.plain[i][j];
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,do_zbicia,bity,bijacy,i,j-1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }  }
             if(i+1<SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite->plain[i+1][j]){
                
                if(teatr_wojenny.plain[i+1][j]!=zbadane->plain[i+1][j]){
                    zbadane->plain[i][j]=teatr_wojenny.plain[i][j]; 
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,do_zbicia,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }  }
             if(j+1<WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite->plain[i][j+1]){
                
                if(teatr_wojenny.plain[i][j+1]!=zbadane->plain[i][j+1]){
                 zbadane->plain[i][j]=teatr_wojenny.plain[i][j]; 
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,do_zbicia,bity,bijacy,i,j+1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }  }

            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==PUSTE)
                pusteczka++;
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==PUSTE)
                pusteczka++;
             if(i+1>=0 && teatr_wojenny.plain[i+1][j]==PUSTE)
                pusteczka++;
             if(j+1>=0 && teatr_wojenny.plain[i][j+1]==PUSTE)
                pusteczka++;
            
            if(pusteczka==0 && sojuz==0){
                 do_zbicia->plain[i][j]=teatr_wojenny.plain[i][j];
                 teatr_wojenny.bezpieczenstwo=ZAGR;
                 zbadane->plain[i][j]=teatr_wojenny.plain[i][j];
                 return teatr_wojenny;
                }
            if(pusteczka!=0 || sojuz!=0){
                 teatr_wojenny.bezpieczenstwo=BEZP;
                 zbadane->plain[i][j]=teatr_wojenny.plain[i][j];
                 
                 return teatr_wojenny;
            }
}

int czy_pelna(plansza teart_wojenny){
    int pelnosc;
    for(int i=0;i<SZEROKOSC_PLANSZY;i++)
        for(int j=0;j<WYSOKOSC_PLANSZY;j++)
            if(teart_wojenny.plain[j][i]==BIALA || teart_wojenny.plain[j][i]==CZARNA)
                pelnosc++;

    return pelnosc+1;
}

int ocena_go(plansza* teatr_wojenny) 
    {
    int punkty_biale = 0;
    int punkty_czarne = 0;

    // Iteruj przez planszę i zliczaj punkty
    for (int j = 0; j < SZEROKOSC_PLANSZY; j++) {

        for (int i = 0; i < WYSOKOSC_PLANSZY; i++) 
        {
            if (teatr_wojenny->plain[i][j] == BIALA) 
            {
                punkty_biale++;
            } 
            else if (teatr_wojenny->plain[i][j] == CZARNA) 
            {
                punkty_czarne++;
            }
        }
    }

    // Zakładamy, że czarne zaczynają, więc białe dostają komi
    //punkty_biale += 6;

    // Zwracamy różnicę punktów
    return punkty_czarne - punkty_biale;
}
/*
plansza wykonaj_ruch(plansza teatr_wojenny,plansza zbadane,plansza niby_zbite,plansza do_zbicia){
    legal gal;
    ruch hcur;
    for (int j = 0; j < SZEROKOSC_PLANSZY; j++) 
        for (int i = 0; i < WYSOKOSC_PLANSZY; i++) 
        {
            hcur.kolumnyk=i;
            hcur.wierszyk=j;
            gal=czy_legal(teatr_wojenny,hcur,zbadane,niby_zbite,do_zbicia);
            if(teatr_wojenny.plain[i][j]==PUSTE && czy_legal){
                if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
                    teatr_wojenny.plain[i][j]=CZARNA;
                 if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
                    teatr_wojenny.plain[i][j]=BIALA;
            }
        }
}*/

void endgame(plansza *teatr_wojenny,int *punkciorBIALY,int *punkciorCZARNY){
    plansza policzone;
    vanish(&policzone);
    //czy_zakladnik(teatr_wojenny,&policzone,punkciorBIALY,punkciorCZARNY);
    for (int j = 0; j < SZEROKOSC_PLANSZY; j++) {

        for (int i = 0; i < WYSOKOSC_PLANSZY; i++) 
        {
            if (teatr_wojenny->plain[i][j] == BIALA && policzone.plain[i][j]!=BIALA) 
            {
                (*punkciorBIALY)++;
            } 
            else if (teatr_wojenny->plain[i][j] == CZARNA && policzone.plain[i][j]!=CZARNA) 
            {
                (*punkciorCZARNY)++;
            }
        }
    }
}


void zwyciezca(int *pcza, int *pbia){
    if(*pcza>*pbia)
    {
        printf("\nWygral gracz CZARNY!!!");
        printf("\nCzarnych punktow: %d",*pcza);  
        printf("\nBialych punktow: %d",*pbia);   
    }
    else if(*pbia>*pcza)
    {
        printf("\nWygral gracz BIALY!!!");
        printf("\nBialych punktow: %d",*pbia);  
        printf("\nCzarnych punktow: %d",*pcza);  
    }
    else if(*pbia==*pcza)
        printf("No to remis");
}

rozkaz* Lista_Schindlera(plansza teatr_wojenny, plansza zbadane,plansza niby_zbite,plansza do_zbicia,castorama *historia,rozkaz *ptr,int i,int j){
    legal moznaa;

            ptr->move.kolumnyk=j;
            ptr->move.wierszyk=i;
            moznaa=czy_legal(teatr_wojenny,ptr->move,zbadane,niby_zbite,do_zbicia,historia);
            if( i!=(WYSOKOSC_PLANSZY) && j!=(SZEROKOSC_PLANSZY) ){
                if(teatr_wojenny.plain[j][i]==PUSTE && moznaa.czy_legalne==L)
                {
                    
                    ptr->nastepny=(struct element *)malloc(sizeof(struct element));
                    ptr->loco=SPOKO;
                    j++;
                    if(j==SZEROKOSC_PLANSZY)
                    {
                        i++;j=0;
                    }
                    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbite,do_zbicia,historia,ptr->nastepny,i,j);  
                }
                else
                {
                    
                    ptr->nastepny=(struct element *)malloc(sizeof(struct element));
                    ptr->loco=NIE_SPOKO;
                    j++;
                    if(j==SZEROKOSC_PLANSZY){
                        i++;j=0; }
                    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbite,do_zbicia,historia,ptr->nastepny,i++,j++);
                }
            }
}

void zabij_ruchy_na_liscie(rozkaz* glowa)
{
    assert(glowa);
    if (glowa->nastepny)
        zabij_ruchy_na_liscie(glowa->nastepny);
    free(glowa);
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

plansza postaw_sie(plansza teatr_wojenny,ruch r0){
    
    if(teatr_wojenny.ruch_gracza_X=RUCH_BIALY)
        teatr_wojenny.plain[r0.kolumnyk][r0.wierszyk]=BIALA;
    else if(teatr_wojenny.ruch_gracza_X=RUCH_CZARNY)
        teatr_wojenny.plain[r0.kolumnyk][r0.wierszyk]=CZARNA;

    return teatr_wojenny;
}

#endif
