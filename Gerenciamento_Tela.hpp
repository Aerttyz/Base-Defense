#ifndef GERENCIAMENTO_TELA_HPP
#define GERENCIAMENTO_TELA_HPP

#include <SFML/Graphics.hpp>
#include "heroi.hpp"

using namespace sf;
using namespace std;

class GerenciametoTela {
    public:
        GerenciametoTela(const string& backgroundFile, Heroi *heroi);
        void eventos(RenderWindow& window);
        void renderizar(RenderWindow& window);
    private:
        Texture background;
        Sprite backgroundSprite;
        Heroi *heroi;
        void setBackgroundScale(RenderWindow& window);

};
#endif // GERENCIAMENTO_TELA_HPP