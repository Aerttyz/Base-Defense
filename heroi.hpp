#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Heroi {
    public:
        Heroi(const string& heroiFile);
        void mover();
        void atirar();
        void tomarDano();
        void curar();
        void renderizar(RenderWindow& window);
    
    private:
        Texture background_heroi;
        Sprite backgroundSprite_heroi;
        int vida;
        const int max_vida = 100;
        int projeteis;
        const int max_projeteis = 10;
};


#endif // HEROI_HPP