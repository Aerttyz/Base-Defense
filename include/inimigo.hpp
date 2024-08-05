#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../include/projeteis.hpp"
using namespace std;
using namespace sf;

class Inimigo{
    public:
        Inimigo(const string& inimigoFile);
        void mover();
        void atualizarProjeteis(float deltaTime, RenderWindow& window);
        void atirar(const Vector2f& direcao);
        void renderizar(RenderWindow& window);
        bool verificarColisao(const Sprite& sprite);
        void setPosicao(const Vector2f& posicao);
        Vector2f getPosicao() const;
        Sprite getSprite() const;
        bool isTextureLoaded() const; 

        vector<Projetil>& getProjeteis();  
        
    private:
        float velocidade;
        Texture background_inimigo;
        Sprite backgroundSprite_inimigo;
        Vector2f posicao;
        Clock relogio;
        Time dps;

        bool textureLoaded;

        vector<Projetil> projeteis; 
        Time intervaloDisparo;
        string projetilFile;
        Texture texturaProjetil;
        Sprite backgroundSprite_projetil;

};

#endif // INIMIGO_HPP