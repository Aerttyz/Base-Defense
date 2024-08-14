#ifndef DROP_HPP
#define DROP_HPP

#include <SFML/Graphics.hpp>
#include "../include/heroi.hpp"

using namespace std;
using namespace sf;

class Heroi;

class Drop{
    public:
        Drop(const Sprite& dropSprite, const Vector2f& posicao, Heroi *heroi, int tipo);
        void renderizar(RenderWindow& window);
        void setPosicao(const Vector2f& posicao);
        Vector2f getPosicao() const;
        Sprite getSprite() const;
        bool verificarColisao(const Sprite& sprite);
        bool verificarTempoDeDesaparecer();
        int getTipo() const;
    private:
        Vector2f posicao;
        bool textureLoaded;
        Sprite backgroundSprite_drop;
        Heroi *heroi;
        int tipoDrop;    

        Time tempoDeCriacao;    
        Clock clockDrop; 
};


#endif // DROP_HPP