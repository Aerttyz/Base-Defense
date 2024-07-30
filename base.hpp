#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Base{
    public:
        Base(int vida, const string& baseFile, const Font& font);
        void renderizar(RenderWindow& window);
        //void verificarColisao(const Sprite& sprite);
        Sprite getSprite() const;
    private:
        int vida;
        Text textoVidaBase;
        Texture background_base;
        Sprite backgroundSprite_base;
        Vector2f posicao;
};

#endif // BASE_HPP