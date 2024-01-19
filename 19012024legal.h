#ifndef LEGALNA
#define LEGALNA
#include "definicje.h"
#include "toolsy.h"

plansza czy_bicie(plansza teatr_wojenny,plansza niby_zbite,plansza zbadane,plansza do_zbicia){
    
    int sojuz=0,pusteczka=0;
    int bity,bijacy;                                     //kogo badamy
    
     if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY){
        bity=BIALA;
        bijacy=CZARNA;  
        }
     if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY){
        bity=CZARNA;
        bijacy=BIALA;   
        }
        for(int j=0;j<SZEROKOSC_PLANSZY;j++)
         for(int i=0;i<WYSOKOSC_PLANSZY ;i++){
          if(teatr_wojenny.plain[i][j]==bity && teatr_wojenny.plain[i][j]!=zbadane.plain[i][j]){

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
             if(i+1<=SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite.plain[i+1][j]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(j+1<=WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite.plain[i][j+1]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i,j+1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }

            
            if(sojuz==0){
                for(int a=0;a<SZEROKOSC_PLANSZY;a++)
                    for(int b=0;b<WYSOKOSC_PLANSZY ;b++)
                        niby_zbite.plain[b][a]=do_zbicia.plain[b][a];
    
                niby_zbite.plain[i][j]=teatr_wojenny.plain[i][j];  }
            else
                zbadane.plain[i][j]=teatr_wojenny.plain[i][j];

            }

        else{
                zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
            }
            
            pusteczka=0;
            sojuz=0;
            
        }
        
    }
    
    for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
          if(teatr_wojenny.plain[i][j]==bity)
            if(teatr_wojenny.plain[i][j]==niby_zbite.plain[i][j])
                teatr_wojenny.plain[i][j]=PUSTE;
                
    vanish(&niby_zbite);
    vanish(&zbadane);
    vanish(&do_zbicia);
     return teatr_wojenny;
}

legal superko(plansza teatr_wojenny,castorama *spr){
    legal mozna2;
    int kloppppsiikkkk=0;
    if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
      for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            if(spr->zero.plain[i][j]==spr->minus2.plain[i][j]) {
                kloppppsiikkkk++;
                if(kloppppsiikkkk==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
                    mozna2.czy_legalne=NL;
                else
                    mozna2.czy_legalne=L;       }
            else
                mozna2.czy_legalne=L;
             
    if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
      for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            if(spr->zero.plain[i][j]==spr->minus2.plain[i][j]) {
                kloppppsiikkkk++;
                if(kloppppsiikkkk==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
                    mozna2.czy_legalne=NL; 
                else 
                    mozna2.czy_legalne=L; 
                }
            else
                mozna2.czy_legalne=L;
            
    return mozna2;
}

legal wyjatek(plansza teatr_wojenny,ruch gruch,plansza zbadane,plansza niby_zbite,plansza do_zbicia){
    plansza franca;
    plansza tymczas; 

    for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
            tymczas.plain[i][j]=teatr_wojenny.plain[i][j];
    
    if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
        tymczas.plain[gruch.kolumnyk][gruch.wierszyk]=CZARNA;
    if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
        tymczas.plain[gruch.kolumnyk][gruch.wierszyk]=BIALA;
    legal lagel;
    int lbkwpd=0;
    franca=czy_bicie(tymczas,niby_zbite,zbadane,do_zbicia);
    for(int j=0;j<SZEROKOSC_PLANSZY;j++)
        for(int i=0;i<WYSOKOSC_PLANSZY ;i++){
            if(franca.plain[i][j]==teatr_wojenny.plain[i][j])
                lbkwpd++;
            if(lbkwpd==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY){
                lagel.czy_legalne=L;
                return lagel;
            }
            else
            {
                if( i==(SZEROKOSC_PLANSZY-1) && j==(WYSOKOSC_PLANSZY-1) ){
                    lagel.czy_legalne=NL;
                    return lagel; 
                }
            }
        }
}

legal samobuj(plansza teatr_wojenny,ruch gruch,plansza zbadane,plansza niby_zbite,plansza do_zbicia){
    legal mozna;
    int bity,bijacy;                                    
    int i=gruch.kolumnyk;
    int j=gruch.wierszyk;
    int pusteczka=0,sojuz=0;

    mozna=wyjatek(teatr_wojenny,gruch,zbadane,niby_zbite,do_zbicia);
    if(mozna.czy_legalne==NL){
        

     if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY){
        bity=CZARNA;
        bijacy=BIALA; 
        teatr_wojenny.plain[i][j]=CZARNA;
        }
     if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY){
        bity=BIALA; 
        bijacy=CZARNA; 
         teatr_wojenny.plain[i][j]=BIALA;
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
    else{
        return mozna;
    }
}


legal czy_legal(plansza teatr_wojenny,ruch gruch,plansza zbadane,plansza niby_zbite,plansza do_zbicia,ikea *sprawdzam){
    legal czy_mozna;
    
    czy_mozna=samobuj(teatr_wojenny,gruch,zbadane,niby_zbite,do_zbicia);
    if(czy_mozna.czy_legalne==L)
        czy_mozna=superko(teatr_wojenny,sprawdzam);
    
    return czy_mozna;
}

#endif
