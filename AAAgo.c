#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"
#include "legalna.h"
#include "xamagen.h"
#include "ocena.h"

void cr_byczq(char*);
void wypisz();
void vanish(plansza*);
plansza sory_memory(plansza*);
plansza ruszek(plansza,ruch);
ruch dokad_przybyszu(plansza,int);
void no_to_gramy(plansza,plansza,plansza,plansza,legal,rozkaz*,rozkaz);
plansza czy_bicie(plansza,plansza,plansza,plansza);
plansza bicie_po_sznurku(plansza,plansza*,plansza*,plansza*,int bity,int bijacy,int i,int j);

legal wyjatek(plansza,ruch,plansza,plansza,plansza);
legal czy_czy(plansza,ruch,plansza,plansza,plansza,castorama*);
legal superko(plansza,castorama*);
legal samobuj(plansza,ruch,plansza,plansza,plansza);

//dokad_przybyszu bedzie funkcja stawiania siedla bota, mus korzystac z listy_schindl, legalnosci i cos jeszcz?
//mozna zrobic nowa dokad_bociszu i podmienic ja w no to gramy?
void zabij_ruchy_na_liscie(rozkaz*);
rozkaz* Lista_Schindlera(plansza,plansza,plansza,plansza,castorama*,rozkaz*,int,int);
void przepisz(plansza*,ikea*);
void przepisz_plansze(plansza*,plansza*);

void czy_zakladnik(plansza*,plansza*,int*,int*);
int czy_pelna(plansza);
void endgame(plansza*,int*,int*);
void zwyciezca(int*,int*);


void arena(plansza* , plansza ,plansza ,plansza);

void main(){
    char tryb;
    rozkaz ptr;
    rozkaz do_boju_Polsko;
    legal zgoda;

    plansza teatr_wojenny;
    vanish(&teatr_wojenny);
    plansza zbadane;
    vanish(&zbadane);
    plansza niby_zbite;
    vanish(&niby_zbite);
    plansza do_zbicia;
    vanish(&do_zbicia);

    cr_byczq(&tryb);
    switch(tryb){
        case 'g':
          no_to_gramy(teatr_wojenny,niby_zbite,zbadane,do_zbicia,zgoda,&ptr,do_boju_Polsko); 
          break;
        case 'k' :
          arena(&teatr_wojenny,zbadane,niby_zbite,do_zbicia);
          break; 
    }
    

}
void cr_byczq(char *czar){
    printf("Kto gra?/n1.Gracz vs Gracz (wpisz g)/n2.Komp vs Komp (wpisz k)\n --> ");
    scanf("&c",czar);
}

void no_to_gramy(plansza teatr_wojenny,plansza niby_zbity,plansza zbadane,plansza do_zbicia,legal zgoda,rozkaz *ptr,rozkaz do_boju_Polsko){
    castorama historia;
    int punkciorBIALY=0,punkciorCZARNY=0;
    int qniec=0;
    int numerek=0;
    vanish(&teatr_wojenny);
    sory_memory(&teatr_wojenny);
    wypisz(&teatr_wojenny);
    plansza plac_boju;
    
    do{
//======================================================================================================================
    teatr_wojenny.ruch_gracza_X=RUCH_CZARNY; //Gracz zaczynajacy
    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbity,do_zbicia,&historia,ptr,0,0);
     numerek++;

        do{
            ruch staruszek1=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek1);
            /*++++++++++++++++++++++++++++*/ przepisz(&plac_boju,&historia.zero); /*++++++++++++++++++++++++++++++++++++*/
            if(numerek>=3 && staruszek1.pas!=TAK)
                zgoda=czy_czy(teatr_wojenny,staruszek1,zbadane,niby_zbity,do_zbicia,&historia);
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
    if(qniec==2)
        break;
//=========================================================================================================================
    teatr_wojenny.ruch_gracza_X=RUCH_BIALY; ///KOLEJ NA DRUGIEGO GRACZA
    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbity,do_zbicia,&historia,ptr,0,0);
    numerek++;

     do{
            ruch staruszek2=dokad_przybyszu(teatr_wojenny,numerek);
    
            plac_boju=ruszek(teatr_wojenny,staruszek2);
            /*+++++++++++++++++++++++++++*/przepisz(&plac_boju,&historia.zero); /*+++++++++++++++++++++++++++++++++++++++*/
            if(numerek>=3 && staruszek2.pas!=TAK)
                zgoda=czy_czy(teatr_wojenny,staruszek2,zbadane,niby_zbity,do_zbicia,&historia);
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
    endgame(&teatr_wojenny,&punkciorBIALY,&punkciorCZARNY);
    zwyciezca(&punkciorCZARNY,&punkciorBIALY);

}

void arena(plansza* teatr_wojenny, plansza zbadane,plansza niby_zbite,plansza do_zbicia)//rozpoczecie meczu
{
    castorama historia;
    int glebokosc_bialasa, glebokosc_czarnasa, ocena;
    printf("\nWpisz glebokosc --> ");
    scanf("%d %d", &glebokosc_bialasa, &glebokosc_czarnasa);
    printf("info glebokosc bialasa %d glebokosc czarnasa %d\n", glebokosc_bialasa, glebokosc_czarnasa);
    while((ocena = negamax(teatr_wojenny, 0,zbadane,niby_zbite,do_zbicia,&historia)) != -10 && ocena != 10 && czy_pelna ( *teatr_wojenny ) != ( SZEROKOSC_PLANSZY * WYSOKOSC_PLANSZY ) )
    {
        __graj(teatr_wojenny->ruch_gracza_X == RUCH_BIALY ? glebokosc_bialasa : glebokosc_czarnasa,teatr_wojenny,zbadane,niby_zbite,do_zbicia,&historia);
        wypisz(&teatr_wojenny);
    }
    printf("info arena sie skonczyla\n");
}

void __graj(int glebokosc,plansza *teatr_wojenny, plansza zbadane,plansza niby_zbite,plansza do_zbicia,castorama *historia)
{
    rozkaz *ruchy;
    Lista_Schindlera(*teatr_wojenny,zbadane,niby_zbite,do_zbicia,historia,ruchy,0,0);
    if (ruchy)
    {
        ruch *ruch_debesciak = NULL;
        int ocena_posuniecia, debesciak = DEFEAT;
        for(rozkaz *rukh = ruchy; rukh; rukh = rukh->nastepny)
        {
            printf("info oceniam ruch %c%d\r", 'A' + rukh->move.kolumnyk, rukh->move.wierszyk);
            plansza wariant = postaw_sie(*teatr_wojenny, rukh->move);
            ocena_posuniecia = -negamax(&wariant, glebokosc,zbadane,niby_zbite,do_zbicia,&historia);
            if (ocena_posuniecia > debesciak)
            {
                debesciak = ocena_posuniecia;
                ruch_debesciak = &ruchy->move;
                printf("%c%d (%s %d) jest debesciakiem\n", 'A' + rukh->move.kolumnyk, rukh->move.wierszyk, enum2txt(ocena_posuniecia), ocena_posuniecia);
            }   
        }
        if(!ruch_debesciak)
            ruch_debesciak = &ruchy->move;
        *teatr_wojenny = postaw_sie(*teatr_wojenny, *ruch_debesciak);
        printf("info debesciak wykonany (%s %d)\n", enum2txt(debesciak), debesciak);
        zabij_ruchy_na_liscie(ruchy);
    }
    else 
        printf("info nie ma legalnego posuniecia\n");
}
