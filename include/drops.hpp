#ifndef DROP_HPP
#define DROP_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Drop{
    public:
        Drop(const Sprite& dropSprite, const Vector2f& posicao);
        void renderizar(RenderWindow& window);
        void setPosicao(const Vector2f& posicao);
        Vector2f getPosicao() const;
        Sprite getSprite() const;
        
    private:
        Vector2f posicao;
        bool textureLoaded;
        Sprite backgroundSprite_drop;
};


#endif // DROP_HPP