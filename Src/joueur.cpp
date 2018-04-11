#include "joueur.hpp"
#include "tuile.hpp"

#include <queue>
#include <iostream>
#include <cstdlib>

namespace MMaze {
Joueur::Joueur()
{
    tuile_act = nullptr;
	position = -1;
	co = AUCUNE;
	status = ACCES;
}

Joueur::Joueur(int i, Tuile* depart, Plateau* plateau){
    plat_jeu = plateau;
	tuile_act = depart;
	position = 1 + 4*((i/2) + 1) + (i%2);
	co = tuile_act->tabCases[position]->color;
	status = ACCES;
}

Joueur::~Joueur()
{
    tuile_act = nullptr;
}

void Joueur::mouvement(int tuile, int pos)
{
    tuile_act = plat_jeu->tab_tuile[tuile];
    position = pos;
}

Case* Joueur::trouve_site(){
    Case* c = tuile_act->tabCases[position];
    std::cout << c->nbArete <<endl;
    Case* d;
    Arete* a;
    int niveau, iteration, taille_niveau, taille_niveau_suiv;
    std::queue<Arete*> f;
    std::queue<Arete*> g;
    std::cout << "toto 1" << endl;
    if(status != RIEN) {
        std::cout << "toto 2" << endl;
        c->visit = false;
        for(int i = 0; i < c->nbArete; i++){
            std::cout << "toto 2.5" << endl;
            f.push(c->tab_access[i]);
        }
        niveau = 1;
        iteration = 1;
        taille_niveau = c->nbArete;
        taille_niveau_suiv = 0;
        while(!(f.empty())){
            a = f.front();
            g.push(a);
            f.pop();
            c = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
            std::cout <<"toto 3 " << iteration << endl;
            for(int i = 0; i < c->nbArete; i++){
                a = c->tab_access[i];
                d = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
                std::cout <<"toto 4 " << iteration << endl;
                if(d->visit){
                    std::cout <<"toto 5 " << iteration << endl;
                    if(d->type == status && d->color == co && d->nouv){
                        std::cout <<"toto 6 " << iteration << endl;
                        while(!(g.empty())){
                            a = g.front();
                            d = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
                            d->visit = true;
                            g.pop();
                        }
                        return d;
                    }
                    f.push(a);
                    taille_niveau_suiv = taille_niveau_suiv + 1;
                    iteration = iteration + 1;
                }
            }
            if(iteration == taille_niveau){
                niveau = niveau + 1;
                taille_niveau = taille_niveau_suiv;
                iteration = 1;
                taille_niveau_suiv = 0;
            }
            c->visit = false;
        }
    }
	//std::cout<<"TROUVEE tuile_act->tabCases[position] == "<<tuile_act->tabCases[position]<<std::endl;
    return tuile_act->tabCases[position];
}


}
