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

int __negamax(plansza* p, int glebokosc, int alfa, int beta)
{
    if (!glebokosc)
        return ocen_pozycje(p);
    rozkaz *ruchy = czy_legal(p), *ptr = ruchy;//do dopisania w programie
    if (!ruchy)
        return ocen_pozycje(p);
    int ocena_wezla = -10, ocena_czymtasowa;
    do
    {
        plansza potomne = wykonaj_ruch(p, ruchy->move);//do dopisania w programie
        ocena_czymtasowa = -__negamax(&potomne, glebokosc - 1, -beta, -alfa);
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
    zgub_rozkaz(ptr);//do dopisania w programie
    return ocena_wezla;
}

int negamax(plansza* p, int glebokosc)
{
    return __negamax(p, glebokosc, -10, 10);
}
#endif
