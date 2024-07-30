#ifndef GERENCIAMENTO_TELA_HPP
#define GERENCIAMENTO_TELA_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "heroi.hpp"
#include "base.hpp"
#include "inimigo.hpp"

using namespace sf;
using namespace std;



class gerenciamentoTela {
    public:
        gerenciamentoTela(const string& backgroundFile,const string& backgroundMenuFile, const string& musicFile, Heroi *heroi, Base *base);  
        void eventos(RenderWindow& window);
        void renderizar(RenderWindow& window);
        void atualizar();
        void setBackgroundScale(RenderWindow& window, Sprite& sprite);
        void setHeroiPosition(RenderWindow& window);
        
    private:
        RectangleShape shape;
        Texture background;
        Texture background_menu;
        Sprite backgroundSprite;
        Sprite backgroundSprite_menu;
        Text textoMenu;
        Music music;
        Heroi *heroi;
        Base *base;
        vector<Inimigo> inimigos;
        Font font;
        enum class Estado {MENU, JOGO, GAMEOVER};
        Estado estado;
        Clock spawRelogio;
        Time spawInimigo;
        Vector2f getPosicaoRandom(const Vector2u& windowSize);


};
#endif // GERENCIAMENTO_TELA_HPP