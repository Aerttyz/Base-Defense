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
        void atualizar(RenderWindow& window);
        void setBackgroundScale(RenderWindow& window, Sprite& sprite);
        void setHeroiPosition(RenderWindow& window);
        Vector2f getPosicaoRandom(const Vector2u& windowSize);

        void atualizarProjeteisInimigos(float deltaTime, RenderWindow& window);
        bool verificarColisaoProjeteisInimigos(Projetil& projetil, Inimigo& inimigo);
        void renderizarProjeteisInimigos(RenderWindow& window);

        void atualizarDrop(RenderWindow& window);  
        
        int getRandomChanceDrop();
        int getRandomTipoDrop();

        //void atirarInimigo(const Vector2f& direcao,const Sprite& backgroundSprite_inimigo);
        void setKills();
        
    private:
        RectangleShape shape;
        Texture background;
        Texture background_menu;
        Texture texturaProjetil;
        Sprite backgroundSprite;
        Sprite backgroundSprite_menu;
        Text textoMenu;
        Music music;
        Heroi *heroi;
        Base *base;
        vector<Inimigo> inimigos;
        vector<Projetil> projeteis;

        vector<Projetil> projeteisInimigos;
        
        Font font;
        Clock spawRelogio;
        Time spawInimigo;
        Clock relogio;
        enum class Estado {MENU, JOGO, GAMEOVER};
        Estado estado;

        Time intervaloDisparo;
        string projetilFile;
        Sprite backgroundSprite_projetil;

        Texture texturaDrop;
        Sprite spriteDrop;
        vector<Drop> drops; 

        int Kills;
        Text textoKills;
              

};
#endif // GERENCIAMENTO_TELA_HPP