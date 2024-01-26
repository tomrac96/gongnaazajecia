#ifndef NEGAMAX   //(i przy okazji je sprawdzam))

#define NEGAMAX

#include "definicje.h"
#include "ocena.h"
#include "toolsy.h"
#include "legalna.h"
#include <ctype.h>

/*
function negamax(node, depth, α, β, color) is
    if depth = 0 or node is a terminal node then
        return color × the heuristic value of node

    childNodes := generateMoves(node)
    childNodes := orderMoves(childNodes)
    value := −∞
    foreach child in childNodes do
        value := max(value, −negamax(child, depth − 1, −β, −α, −color))
        α := max(α, value)
        if α ≥ β then
            break (* cut-off *)
    return value
*/

int xamagen(plansza *teatr_wojenny, int glebokosc, int alfa, int beta, plansza zbadane,plansza niby_zbite,plansza do_zbicia,castorama *historia)
{
    rozkaz *ruchy;
    ruch skuch;
    if (!glebokosc)
        return ocen_pozycje(teatr_wojenny);
    Lista_Schindlera(*teatr_wojenny,zbadane,niby_zbite,do_zbicia,historia,ruchy,0,0);
    rozkaz *rtp = ruchy;
    if (!ruchy)
        return ocen_pozycje(teatr_wojenny);
    int ocena_wezla = DEFEAT, ocena_czymtasowa;
    do
    {
        plansza potomne = postaw_sie(*teatr_wojenny, ruchy->move);
        ocena_czymtasowa = -xamagen(&potomne, glebokosc - 1, -beta, -alfa,zbadane,niby_zbite,do_zbicia,historia);
        if (ocena_czymtasowa > ocena_wezla)
        {
            ocena_wezla = ocena_czymtasowa;
            if (ocena_wezla > alfa)
                alfa = ocena_wezla;
        }
        if (alfa >= beta)
        {
            ocena_wezla = beta;
            break;
        }
        ruchy = ruchy->nastepny;
    } while (ruchy);
    zabij_ruchy_na_liscie(rtp);
    return ocena_wezla;
}

int negamax(plansza* teatr_wojenny, int glebokosc, plansza zbadane,plansza niby_zbite,plansza do_zbicia,castorama *historia)
{
    return xamagen(teatr_wojenny, glebokosc, -10, 10,zbadane,niby_zbite,do_zbicia,historia);
}
#endif
