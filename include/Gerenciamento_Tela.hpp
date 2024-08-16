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
        gerenciamentoTela(const string& backgroundFile,const string& backgroundMenuFile, const string& musicaTemaFile, Heroi *heroi, Base *base, const Vector2f& windowSize);  
        void iniciarArquivos(const string& backgroundFile, const string& backgroundMenuFile,const string& musicaTemaFile);
        void setaArquivos(const Vector2f& windowSize);
        void eventos(RenderWindow& window, const Vector2f& windowSize);
        void renderizar(RenderWindow& window);
        void atualizar(RenderWindow& window);
        void setBackgroundScale(RenderWindow& window, Sprite& sprite);
        void setHeroiPosition(RenderWindow& window);
        Vector2f getPosicaoRandom(const Vector2u& windowSize);

        void atualizarProjeteisInimigos(float deltaTime, RenderWindow& window);
        void renderizarProjeteisInimigos(RenderWindow& window);

        void atualizarDrop(RenderWindow& window);  
        bool atualizarDrops(RenderWindow& window);
        
        int getRandomChanceDrop();
        int getRandomInimigo();

        void setFimDeJogo();
        void setKills();

        void waveInimigos();

        void resetarJogo(const Vector2f& windowSize);

    private:
        Texture background;
        Texture background_menu;
        Texture texturaProjetil;
        Sprite backgroundSprite;
        Sprite backgroundSprite_menu;
        Text textoMenu;
        Music musicaTema;
        Music musicaGameOver;
        Sound escolhaMenu;
        SoundBuffer bufferEscolhaMenu;
        Heroi *heroi;
        Base *base;
        Tank *tank;
        Inimigo *inimigo;
        Inimigo *runner;
        InimigoTank *inimigoTank;
        vector<Inimigo *> inimigos;
        vector<Runner *> runners;
        vector<InimigoTank *> tanks;
        int inimigoTankVida = 2;
        vector<Projetil *> projeteis;
        vector<sf::Text> botoesMenu;  
        vector<sf::Text> botoesDificuldade;  
        vector<Projetil> projeteisInimigos;

        
        Font font;
        Font fontGame;
        Clock spawRelogio;
        const Time SPAWN_FACIL = seconds(3);  
        const Time SPAWN_NORMAL = seconds(2); 
        const Time SPAWN_DIFICIL = seconds(1);  
        Time spawnInimigo = seconds(0.2f);
        Time waveInimigo = SPAWN_NORMAL;
        Clock waveRelogio;
        Clock relogio;
        enum class Estado {MENU, DIFICULDADE, JOGO, COOP, GAMEOVER, PAUSE};
        Estado estado = Estado::MENU;

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

        int Kills=0;
        Text textoKills;

        bool regenerarVidaBase = false;
        bool aumentarVidaBase = false;
        int upLimite = 0;
              

};
#endif // GERENCIAMENTO_TELA_HPP