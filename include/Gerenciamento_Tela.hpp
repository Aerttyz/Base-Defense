#ifndef GERENCIAMENTO_TELA_HPP
#define GERENCIAMENTO_TELA_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../include/heroi.hpp"
#include "../include/base.hpp"
#include "../include/inimigo.hpp"
#include <vector>

using namespace sf;
using namespace std;



class gerenciamentoTela {
    public:
        gerenciamentoTela(const string& backgroundFile,const string& backgroundMenuFile, const string& musicFile, Heroi *heroi, Base *base, const Vector2f& windowSize);  
        void eventos(RenderWindow& window);
        void renderizar(RenderWindow& window);
        void atualizar();
        void setBackgroundScale(RenderWindow& window, Sprite& sprite);
        void setHeroiPosition(RenderWindow& window);
        Vector2f getPosicaoRandom(const Vector2u& windowSize);
        
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
        Clock spawRelogio;
        Time spawInimigo;
        enum class Estado {MENU, JOGO, GAMEOVER};
        Estado estado;


};
#endif // GERENCIAMENTO_TELA_HPP