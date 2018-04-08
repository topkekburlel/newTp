#ifndef NOEUD_HPP
#define NOEUD_HPP


class noeud
{
    public:

        arete* tab_access[14];
        tuile* localisation;
        int id;
        int nbArete;

        noeud();
        noeud(tuile* tuile, int case_id);
        virtual ~noeud();

    protected:

    private:
};

#endif // NOEUD_HPP
