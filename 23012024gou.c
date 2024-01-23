#include <stdio.h>
#include "toolsy.h"
#include "definicje.h"
#include "legalna.h"
//xamagen!!1!
void wypisz();
void vanish(plansza*);
plansza sory_memory(plansza*);
plansza ruszek(plansza,ruch);
ruch dokad_przybyszu(plansza,int);
void no_to_gramy(plansza,plansza,plansza,plansza,legal,rozkaz*,rozkaz);
plansza czy_bicie(plansza,plansza,plansza,plansza);
plansza bicie_po_sznurku(plansza,plansza*,plansza*,plansza*,int bity,int bijacy,int i,int j);

legal wyjatek(plansza,ruch,plansza,plansza,plansza);
legal czy_legal(plansza,ruch,plansza,plansza,plansza,ikea*);
legal superko(plansza,castorama*);
legal samobuj(plansza,ruch,plansza,plansza,plansza);



rozkaz Lista_Schindlera(plansza,plansza,plansza,plansza,castorama*,rozkaz*,int,int);
void przepisz(plansza*,ikea*);
void przepisz_plansze(plansza*,plansza*);

void czy_zakladnik(plansza*,plansza*,int*,int*);
int czy_pelna(plansza);
void endgame(plansza*,int*,int*);
void zwyciezca(int*,int*);

void main(){
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

    no_to_gramy(teatr_wojenny,niby_zbite,zbadane,do_zbicia,zgoda,&ptr,do_boju_Polsko);

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

    endgame(&teatr_wojenny,&punkciorBIALY,&punkciorCZARNY);
    zwyciezca(&punkciorCZARNY,&punkciorBIALY);
    
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

rozkaz Lista_Schindlera(plansza teatr_wojenny, plansza zbadane,plansza niby_zbite,plansza do_zbicia,castorama *historia,rozkaz *ptr,int i,int j){
    legal moznaa;

            ptr->move.kolumnyk=j;
            ptr->move.wierszyk=i;
            moznaa=czy_legal(teatr_wojenny,ptr->move,zbadane,niby_zbite,do_zbicia,&historia);
            if( i!=(WYSOKOSC_PLANSZY) && j!=(SZEROKOSC_PLANSZY) ){
                if(teatr_wojenny.plain[j][i]==PUSTE && moznaa.czy_legalne==L)
                {
                    
                    ptr->nastepny=malloc(sizeof(rozkaz));
                    ptr->loco=SPOKO;
                    j++;
                    if(j==SZEROKOSC_PLANSZY)
                    {
                        i++;j=0;
                    }
                    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbite,do_zbicia,&historia,ptr->nastepny,i,j);  
                }
                else
                {
                    
                    ptr->nastepny=malloc(sizeof(rozkaz));
                    ptr->loco=NIE_SPOKO;
                    j++;
                    if(j==SZEROKOSC_PLANSZY){
                        i++;j=0; }
                    Lista_Schindlera(teatr_wojenny,zbadane,niby_zbite,do_zbicia,&historia,ptr->nastepny,i++,j++);
                }
            }
}
