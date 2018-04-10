#ifndef JOUEUR_HPP
#define JOUEUR_HPP


class joueur
{
    public:
        couleur c;
        tuile* tuile_act;
        int position;
        Plateau* plat_jeu;

        joueur();
        joueur(int i, tuile* depart, Plateau* plateau);
        virtual ~joueur();

        // gère le déplacement d'un joueur
        mouvement();

    protected:

    private:
};

#endif // JOUEUR_HPP
