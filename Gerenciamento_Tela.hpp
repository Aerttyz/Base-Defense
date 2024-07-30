#ifndef GERENCIAMENTO_TELA_HPP
#define GERENCIAMENTO_TELA_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "heroi.hpp"
#include "base.hpp"

using namespace sf;
using namespace std;

class gerenciamentoTela {
    public:
        gerenciamentoTela(const string& backgroundFile,const string& musicFile, Heroi *heroi, Base *base);
        void eventos(RenderWindow& window);
        void renderizar(RenderWindow& window);
        void atualizar();
        
    private:
        RectangleShape shape;
        Texture background;
        Sprite backgroundSprite;
        Music music;
        Heroi *heroi;
        Base *base;

        void setBackgroundScale(RenderWindow& window);
        void setHeroiPosition(RenderWindow& window);

};
#endif // GERENCIAMENTO_TELA_HPP