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

void endgame(plansza *teatr_wojenny,int *punkciorBIALY,int *punkciorCZARNY){
    plansza policzone;
    vanish(&policzone);
    czy_zakladnik(teatr_wojenny,&policzone,punkciorBIALY,punkciorCZARNY);
    for (int j = 0; j < SZEROKOSC_PLANSZY; j++) {

        for (int i = 0; i < WYSOKOSC_PLANSZY; i++) 
        {
            if (teatr_wojenny->plain[i][j] == BIALA && policzone.plain[i][j]!=BIALA) 
            {
                *punkciorBIALY++;
            } 
            else if (teatr_wojenny->plain[i][j] == CZARNA && policzone.plain[i][j]!=CZARNA) 
            {
                *punkciorCZARNY++;
            }
        }
    }
}


void zwyciezca(int *pcza, int *pbia){
    if(pcza>pbia)
    {
        printf("\nWygral gracz CZARNY!!!");
        printf("\nCzarnych punktow: %d",pcza);  
        printf("\nBialych punktow: %d",pbia);   
    }
    else if(pbia>pcza)
    {
        printf("\nWygral gracz BIALY!!!");
        printf("\nBialych punktow: %d",pbia);  
        printf("\nCzarnych punktow: %d",pcza);  
    }
    else if(pbia==pcza)
        printf("No to remis");
}

#endif
