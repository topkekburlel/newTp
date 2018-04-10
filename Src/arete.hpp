#ifndef ARETE_HPP
#define ARETE_HPP



class arete
{
    public:
        int direction;
        int taille;
        int tuile;
        int position;

        arete();
        arete(int direction_, int taille_, int tuile_, int pos_);
        ~arete();

    protected:

    private:
};

#endif // ARETE_HPP
