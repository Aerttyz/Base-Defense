#ifndef PROJETEIS_HPP
#define PROJETEIS_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Projetil{
    public:
        Projetil(const Vector2f& posicaoInicial,const Vector2f& direcao, const Sprite& spriteProjetil);
        void mover();
        void renderizar(RenderWindow& window);
        FloatRect getGlobalBounds() const;  
        Sprite getSprite() const;
        Vector2f getPosicao() const;
        bool verificarColisao(const Sprite& sprite);
        bool isTextureLoaded() const;
    private:
        Sprite backgroundSprite_projetil;
        Texture background_projetil;
        float velocidade;
        Vector2f direcao;
        bool textureLoaded;
};
#endif // PROJETEIS_HPP