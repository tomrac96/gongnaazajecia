#ifndef LEGALNA
#define LEGALNA
#include "definicje.h"
#include "toolsy.h"

legal ko(plansza teatr_wojenny,plansza *backup){
    legal mozna2;
    if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
      for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            if(backup->plain[i][j]==backup->prev->prev->plain[i][j])  //chyba ma jakis problem z backp->prev->prev (adresu nie ma)
                mozna2.czy_legalne=NL;
            else
                mozna2.czy_legalne=L;
             
    if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
      for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            if(backup->next->plain[i][j]==backup->prev->plain[i][j])
                mozna2.czy_legalne=NL;
            else
                mozna2.czy_legalne=L;
            
    return mozna2;
}

legal samobuj(plansza teatr_wojenny,ruch gruch,plansza zbadane,plansza niby_zbite,plansza do_zbicia){
    legal mozna;
    int bity,bijacy;                                    
    int i=gruch.kolumnyk;
    int j=gruch.wierszyk;
    int pusteczka=0,sojuz=0;

     if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY){
        bity=CZARNA;
        bijacy=BIALA; 
        }
     if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY){
        bity=BIALA; 
        bijacy=CZARNA; 
        }

     if(i-1>=0 && teatr_wojenny.plain[i-1][j]==PUSTE)
        pusteczka++;
     if(j-1>=0 && teatr_wojenny.plain[i][j-1]==PUSTE)
        pusteczka++;
     if(i+1<SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==PUSTE)
        pusteczka++;
     if(j+1<WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==PUSTE)
        pusteczka++;

    if(pusteczka==0){
          
            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity && teatr_wojenny.plain[i-1][j]!=niby_zbite.plain[i-1][j]){ //sprawdza czy ma sasiadow przyjaciol
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i-1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity && teatr_wojenny.plain[i][j-1]!=niby_zbite.plain[i][j-1]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i,j-1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(i+1<SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite.plain[i+1][j]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(j+1<WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite.plain[i][j+1]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i,j+1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
                 
             if(sojuz==0)
                mozna.czy_legalne=NL;
            else
                mozna.czy_legalne=L;
            
    }
    else
    {
       mozna.czy_legalne=L;
    }
    return mozna;
}


legal czy_legal(plansza teatr_wojenny,ruch gruch,plansza zbadane,plansza niby_zbite,plansza do_zbicia,plansza *backup){
    legal czy_mozna;
    
    czy_mozna=samobuj(teatr_wojenny,gruch,zbadane,niby_zbite,do_zbicia);
    if(czy_mozna.czy_legalne==L)
        czy_mozna=ko(teatr_wojenny,backup);
    
    return czy_mozna;
}



#endif
