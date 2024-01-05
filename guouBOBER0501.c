#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"

void wypisz();
void vanish(plansza*);
plansza sory_memory(plansza*);
plansza ruszek(plansza,ruch);
ruch dokad_przybyszu(plansza);
void no_to_gramy(plansza,plansza,plansza);
plansza czy_bicie(plansza,plansza,plansza);
plansza bicie_po_sznurku(plansza,plansza*,plansza*,int bity,int bijacy,int i,int j);

int czy_pelna(plansza);

void main(){

    plansza zbadane;
    vanish(&zbadane);
    plansza niby_zbite;
    vanish(&niby_zbite);

    plansza teatr_wojenny;
    no_to_gramy(teatr_wojenny,niby_zbite,zbadane);
}

void no_to_gramy(plansza teatr_wojenny,plansza niby_zbity,plansza zbadane){
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
      if(plac_boju.qn==1 || czy_pelna==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
        qniec++;
      else
        plac_boju=czy_bicie(teatr_wojenny,niby_zbity,zbadane);
    
    teatr_wojenny=plac_boju;
    wypisz(&plac_boju);

    teatr_wojenny.ruch_gracza_X=RUCH_BIALY; ///KOLEJ NA DRUGIEGO GRACZA

    ruch staruszek2=dokad_przybyszu(teatr_wojenny);

     plac_boju=ruszek(teatr_wojenny,staruszek2);
     teatr_wojenny=plac_boju;
      if(plac_boju.qn==1 || czy_pelna==SZEROKOSC_PLANSZY*WYSOKOSC_PLANSZY)
        qniec++;
      else
        plac_boju=czy_bicie(teatr_wojenny,niby_zbity,zbadane);

    teatr_wojenny=plac_boju;
    wypisz(&plac_boju);

    }while(qniec!=2);

    printf("\nobydwaj gracze spasowali");
    printf("\nende tu sprawdzanie stanu posaidania pul (tak wiem u XD).");
}

ruch dokad_przybyszu(plansza teatr_wojenny){
    int w,k;
    char where[3];

    printf("\n\ngdzie chcesz sie postawic? -->");
    scanf("%s", &where);
    ruch staruch={.pas=TAK};
    if(where[0]=='p' && where[1]=='a' && where[2]=='s'){ //SPRAWDZA CZY PAS
        
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
        staruch=dokad_przybyszu(teatr_wojenny);
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

plansza czy_bicie(plansza teatr_wojenny,plansza niby_zbite,plansza zbadane){
    
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
            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity && teatr_wojenny.plain[i-1][j]!=niby_zbite.plain[i-1][j]){ //sprawdza czy ma sasiadow przyjaciol
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,bity,bijacy,i-1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity && teatr_wojenny.plain[i][j-1]!=niby_zbite.plain[i][j-1]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,bity,bijacy,i,j-1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(i+1<=SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite.plain[i+1][j]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }
             if(j+1<=WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite.plain[i][j+1]){
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,bity,bijacy,i,j+1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }

            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==PUSTE)
                pusteczka++;
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==PUSTE)
                pusteczka++;
             if(i+1>=0 && teatr_wojenny.plain[i+1][j]==PUSTE)
                pusteczka++;
             if(j+1>=0 && teatr_wojenny.plain[i][j+1]==PUSTE)
                pusteczka++;

            if(pusteczka==0 && sojuz==0)
                    niby_zbite.plain[i][j]=teatr_wojenny.plain[i][j];   
            else
                zbadane.plain[i][j]=teatr_wojenny.plain[i][j];

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
     return teatr_wojenny;
}

plansza bicie_po_sznurku(plansza teatr_wojenny,plansza *niby_zbite,plansza *zbadane,int bity,int bijacy,int i,int j){ // to funkcja sprawdzajaca kolezkow pierwotnie badanego kamucha
    int sojuz=0,pusteczka=0;

            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity && teatr_wojenny.plain[i-1][j]!=niby_zbite->plain[i-1][j]){ //sprawdza czy ma sasiadow przyjaciol
               
                if(teatr_wojenny.plain[i-1][j]!=zbadane->plain[i-1][j]){ 
                    zbadane->plain[i-1][j]=teatr_wojenny.plain[i-1][j];
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,bity,bijacy,i-1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    } }
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity && teatr_wojenny.plain[i][j-1]!=niby_zbite->plain[i][j-1]){
                
                if(teatr_wojenny.plain[i][j-1]!=zbadane->plain[i][j-1]){ 
                 zbadane->plain[i][j-1]=teatr_wojenny.plain[i][j-1];
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,bity,bijacy,i,j-1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }  }
             if(i+1<=SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite->plain[i+1][j]){
                
                if(teatr_wojenny.plain[i+1][j]!=zbadane->plain[i+1][j]){
                    zbadane->plain[i+1][j]=teatr_wojenny.plain[i+1][j]; 
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    }  }
             if(j+1<=WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite->plain[i][j+1]){
                
                if(teatr_wojenny.plain[i][j+1]!=zbadane->plain[i][j+1]){
                 zbadane->plain[i][j+1]=teatr_wojenny.plain[i][j+1]; 
                 teatr_wojenny=bicie_po_sznurku(teatr_wojenny,niby_zbite,zbadane,bity,bijacy,i,j+1);
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
                 niby_zbite->plain[i][j]=teatr_wojenny.plain[i][j];
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
