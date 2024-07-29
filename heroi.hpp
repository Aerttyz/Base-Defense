#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Heroi {
    public:
        Heroi(int vida, const string& heroiFile);
        void definirPosicao(const Vector2f& posicao);
        void mover();
        void atirar();
        void tomarDano();
        void curar();
        void renderizar(RenderWindow& window);
        void setVida(int novaVida);
        int getVida();
        void verificarColisao(const Sprite& sprite);
    
    private:
        Texture background_heroi;
        Sprite backgroundSprite_heroi;
        Vector2f posicao;
        float velocidade;
        int vida;
        int projeteis;
        const int max_projeteis = 20;
};


#endif // HEROI_HPP