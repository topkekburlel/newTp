#ifndef JOUEUR_HPP
#define JOUEUR_HPP


class joueur
{
    public:
        couleur c;
        tuile* tuile_act;
        int position;

        joueur();
        joueur(int i, tuile* depart);
        virtual ~joueur();

        // g�re le d�placement d'un joueur
        mouvement();

    protected:

    private:
};

#endif // JOUEUR_HPP
