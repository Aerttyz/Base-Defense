#ifndef GERENCIAMENTO_TELA_HPP
#define GERENCIAMENTO_TELA_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../include/heroi.hpp"
#include "../include/base.hpp"
#include "../include/inimigo.hpp"
#include "../include/tank.hpp"
#include "../include/inimigoTank.hpp"
#include "../include/runner.hpp"
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
        void renderizarProjeteisInimigos(RenderWindow& window);

        void atualizarDrop(RenderWindow& window);  
        
        int getRandomChanceDrop();
        int getRandomInimigo();

        void setFimDeJogo();
        void setKills();

        void waveInimigos();
        
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
        Tank *tank;
        Inimigo *inimigo;
        Inimigo *runner;
        InimigoTank *inimigoTank;
        vector<Inimigo *> inimigos;
        vector<Inimigo *> runners;
        vector<InimigoTank *> tanks;
        int inimigoTankVida = 2;
        vector<Projetil *> projeteis;
          
        vector<sf::Text> botoesMenu;  
        
        vector<sf::Text> botoesDificuldade;  

        vector<Projetil> projeteisInimigos;

        
        Font font;
        Clock spawRelogio;
        Time spawnInimigo;
        Time waveInimigo;
        const Time SPAWN_FACIL = seconds(3);  
        const Time SPAWN_NORMAL = seconds(2); 
        const Time SPAWN_DIFICIL = seconds(1);  
        Clock waveRelogio;
        Clock relogio;
        enum class Estado {MENU, DIFICULDADE, JOGO, COOP, GAMEOVER, PAUSE};
        Estado estado;

        Time intervaloDisparo;
        string projetilFile;
        Sprite backgroundSprite_projetil;

        Texture texturaDrop;
        Texture texturaDrop1;
        Texture texturaDrop2;
        Sprite spriteDrop;
        Sprite spriteDrop1;
        Sprite spriteDrop2;
        vector<Drop> drops; 
        Clock dropRelogio;

        int Kills=0;
        Text textoKills;

        bool regenerarVidaBase = false;
        bool aumentarVidaBase = false;
        int upLimite = 0;
              

};
#endif // GERENCIAMENTO_TELA_HPP