#ifndef DROP_HPP
#define DROP_HPP

#include <SFML/Graphics.hpp>
#include "../include/heroi.hpp"

using namespace std;
using namespace sf;

class Heroi;

class Drop{
    public:
        Drop(const Sprite& dropSprite, const Vector2f& posicao, Heroi *heroi);
        void renderizar(RenderWindow& window);
        void setPosicao(const Vector2f& posicao);
        Vector2f getPosicao() const;
        Sprite getSprite() const;
        int getRandomTipoDrop();

        bool verificarColisao(const Sprite& sprite);
    private:
        Vector2f posicao;
        bool textureLoaded;
        Sprite backgroundSprite_drop;
        Heroi *heroi;
};


#endif // DROP_HPP