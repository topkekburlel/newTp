#ifndef ARETE_HPP
#define ARETE_HPP


namespace MMaze {
class Arete
{
    public:
        int direction;
        int taille;
        int tuile;
        int position;

        Arete();
        Arete(int direction_, int taille_, int tuile_, int pos_);

    protected:

    private:
};
}
#endif // ARETE_HPP
