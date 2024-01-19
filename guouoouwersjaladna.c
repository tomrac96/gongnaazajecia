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


legal czy_legal(plansza,ruch,plansza,plansza,plansza,ikea*);
legal ko(plansza,castorama*);
legal samobuj(plansza,ruch,plansza,plansza,plansza);


int czy_pelna(plansza);
void przepisz(plansza*,ikea*);

void main()
{
    
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

void no_to_gramy(plansza teatr_wojenny,plansza niby_zbity,plansza zbadane,plansza do_zbicia,legal zgoda)
{
    castorama historia;
  
    int qniec=0;
    int numerek=0;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
    plansza plac_boju;
    
    do
    {
//======================================================================================================================
    teatr_wojenny.ruch_gracza_X=RUCH_CZARNY; //Gracz zaczynajacy
     numerek++;

        do
        {
            ruch staruszek1=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek1);
            /*++++++++++*/przepisz(&plac_boju,&historia.zero); /*++++++++++*/
            if(numerek>=3)
                zgoda=czy_legal(teatr_wojenny,staruszek1,zbadane,niby_zbity,do_zbicia,&historia.zero);
            else
                zgoda.czy_legalne=L;

        }
        while(zgoda.czy_legalne==NL);

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

        do
        {
            ruch staruszek2=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek2);
            /*++++++++++*/przepisz(&plac_boju,&historia.zero); /*++++++++++*/
            if(numerek>=3)
                zgoda=czy_legal(teatr_wojenny,staruszek2,zbadane,niby_zbity,do_zbicia,&historia.zero);
            else
                zgoda.czy_legalne=L;

        }
        while(zgoda.czy_legalne==NL);
        
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

ruch dokad_przybyszu(plansza teatr_wojenny,int numerek)
{
    int w,k;
    char where[3];
    printf("\n\nRuch numer %d.",numerek);
    printf(" Gdzie chcesz sie postawic? -->");
    scanf("%s", &where);
    ruch staruch={.pas=TAK};

    if(where[0]=='p' && where[1]=='a' && where[2]=='s') //SPRAWDZA CZY PAS
    {
        return staruch;
    }

    if(where[0]>='A' && where[0] < ('A' + SZEROKOSC_PLANSZY) && where[1] < ('0' //SPRAWDZA I INTERPRETUJE WARTOSC WPISANA PRZEZ UZYTK (wielkie lit.) I PRZETWARZA NA KOORDYNATY
    + WYSOKOSC_PLANSZY) && teatr_wojenny.plain[where[0] - 'A'][where[1] - '0'] == PUSTE)
    {
        
        ruch staruch = { .wierszyk=where[1]-'0',.kolumnyk=where[0]-'A'};
        printf("\nRozkaz!\n");
        staruch.pas=NIE;
        return staruch;
    }

    if(where[0]>='a' && where[0] < ('a' + SZEROKOSC_PLANSZY) && where[1] < ('0' //SPRAWDZA I INTERPRETUJE WARTOSC WPISANA PRZEZ UZYTK (male lit.) I PRZETWARZA NA KOORDYNATY
    + WYSOKOSC_PLANSZY) && teatr_wojenny.plain[where[0] - 'a'][where[1] - '0'] == PUSTE)
    {
        
        ruch staruch = { .wierszyk=where[1]-'0',.kolumnyk=where[0]-'a'};
        printf("\nRozkaz!\n");
        staruch.pas=NIE;
        return staruch;
    }
    
    else
    {
        printf("\nPanie Majorze, nie da sie D:");
        printf("\nPowtorz rozkaz...\n");
        staruch=dokad_przybyszu(teatr_wojenny,numerek);
        return staruch;
    }
}

plansza ruszek(plansza teatr_wojenny,ruch staruszek)
{
    int i=staruszek.kolumnyk;
    int j=staruszek.wierszyk;
    
    if(staruszek.pas==TAK)
    {
        teatr_wojenny.qn=1;
        teatr_wojenny.blad=NO;
        return teatr_wojenny;
    }

    if(teatr_wojenny.plain[i][j]==PUSTE)
    {
        if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
         teatr_wojenny.plain[i][j]=CZARNA;
        if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
         teatr_wojenny.plain[i][j]=BIALA;

        teatr_wojenny.blad=NO;
    return teatr_wojenny;
    }

    if(teatr_wojenny.plain[i][j]!=PUSTE)
    {
        ruszek(teatr_wojenny,staruszek);
    }
}

plansza czy_bicie(plansza teatr_wojenny,plansza niby_zbite,plansza zbadane,plansza do_zbicia)
{
    
    int sojuz=0,pusteczka=0;
    int bity,bijacy;                                     //kogo badamy
    
     if(teatr_wojenny.ruch_gracza_X==RUCH_CZARNY)
        {
        bity=BIALA;
        bijacy=CZARNA;  
        }

     if(teatr_wojenny.ruch_gracza_X==RUCH_BIALY)
        {
        bity=CZARNA;
        bijacy=BIALA;   
        }

        for(int j=0;j<SZEROKOSC_PLANSZY;j++)
         for(int i=0;i<WYSOKOSC_PLANSZY ;i++)
         {
          if(teatr_wojenny.plain[i][j]==bity && teatr_wojenny.plain[i][j]!=zbadane.plain[i][j])
          {

             if(i-1>=0 && teatr_wojenny.plain[i-1][j]==PUSTE)
                pusteczka++;
             if(j-1>=0 && teatr_wojenny.plain[i][j-1]==PUSTE)
                pusteczka++;
             if(i+1<SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==PUSTE)
                pusteczka++;
             if(j+1<WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==PUSTE)
                pusteczka++;

            if(pusteczka==0)
            {
          
            if(i-1>=0 && teatr_wojenny.plain[i-1][j]==bity && teatr_wojenny.plain[i-1][j]!=niby_zbite.plain[i-1][j])//sprawdza czy ma sasiadow przyjaciol
            { 
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i-1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    
            }
            
            if(j-1>=0 && teatr_wojenny.plain[i][j-1]==bity && teatr_wojenny.plain[i][j-1]!=niby_zbite.plain[i][j-1])
            {
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i,j-1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;    
            }

            if(i+1<=SZEROKOSC_PLANSZY && teatr_wojenny.plain[i+1][j]==bity && teatr_wojenny.plain[i+1][j]!=niby_zbite.plain[i+1][j])
            {
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i+1,j);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;
            }

            if(j+1<=WYSOKOSC_PLANSZY && teatr_wojenny.plain[i][j+1]==bity && teatr_wojenny.plain[i][j+1]!=niby_zbite.plain[i][j+1])
            {
                 zbadane.plain[i][j]=teatr_wojenny.plain[i][j];
                teatr_wojenny=bicie_po_sznurku(teatr_wojenny,&niby_zbite,&zbadane,&do_zbicia,bity,bijacy,i,j+1);
                if(teatr_wojenny.bezpieczenstwo==BEZP)
                 sojuz++;
            }

            
            if(sojuz==0)
            {
                for(int a=0;a<SZEROKOSC_PLANSZY;a++)
                    for(int b=0;b<WYSOKOSC_PLANSZY ;b++)
                        niby_zbite.plain[b][a]=do_zbicia.plain[b][a];
    
                niby_zbite.plain[i][j]=teatr_wojenny.plain[i][j];  
            }

            else
                zbadane.plain[i][j]=teatr_wojenny.plain[i][j];

            }

        else
        {
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
