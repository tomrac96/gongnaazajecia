#ifndef TOOLSY
#define TOOLSY
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include "definicje.h"

plansza sory_memory(plansza *teatr_wojenny){
    return (plansza) { .ruch_gracza_X=RUCH_CZARNY };
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
            if(teart_wojenny.plain[i][j]==BIALA || teart_wojenny.plain[i][j]==CZARNA)
                pelnosc++;

    return pelnosc;
}

#endif
