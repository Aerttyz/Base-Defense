#ifndef PROJETEIS_HPP
#define PROJETEIS_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Projetil{
    public:
        Projetil(const Vector2f& posicaoInicial, const Vector2f& direcao, const Texture& textura);
        void mover();
        void renderizar(RenderWindow& window);
        FloatRect getGlobalBounds() const;  
        Sprite getSprite() const;
        Vector2f getPosicao() const;
        bool verificarColisao(const Sprite& sprite);
    private:
        Sprite backgroundSprite_projetil;
        float velocidade;
        Vector2f direcao;
};
#endif // PROJETEIS_HPP