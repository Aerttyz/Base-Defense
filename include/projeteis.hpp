#ifndef PROJETEIS_HPP
#define PROJETEIS_HPP

#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

using namespace sf;
class Inimigo;

class Projetil{
    public:
        Projetil(const Vector2f& posicaoInicial,const Vector2f& direcao, const Sprite& spriteProjetil, Inimigo* owner);
        void mover(float deltaTime);
        void moverInimigo(float deltaTime);
        void setPosicao(const sf::Vector2f& posicao);
        void setDirecao(const sf::Vector2f& direcao);
        void renderizar(RenderWindow& window);
        FloatRect getGlobalBounds() const;  
        Sprite getSprite() const;
        Vector2f getPosicao() const;
        bool verificarColisaoJanela(const RenderWindow& window);
        bool verificarColisao(const Sprite& sprite);
        bool isTextureLoaded() const;

        Inimigo* getOwner() const;
    private:
        Sprite backgroundSprite_projetil;
        Texture background_projetil;
        float velocidade;
        float velocidadeInimigo;
        Vector2f direcao;
        bool textureLoaded;

        Inimigo* owner;
        
};
#endif // PROJETEIS_HPP