#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../include/projeteis.hpp"
#include "../include/drops.hpp"
using namespace std;
using namespace sf;
class Projetil;

class Inimigo{
    public:
        Inimigo(const string& inimigoFile);
        void mover();
        void atualizarProjeteis(float deltaTime, RenderWindow& window);
        virtual bool verificarColisao(const Sprite& sprite);
        void atirar(const Vector2f& direcao);
        void atirarCOOP(const Vector2f& direcaoHeroi, const Vector2f& direcaoTank, const float distanciaHeroi, const float distanciaTank);
        void setPosicao(const Vector2f& posicao);
        Vector2f getPosicao() const;
        Sprite getSprite() const;
        bool isTextureLoaded() const; 
        vector<Projetil>& getProjeteis();
        
         
        
        void renderizar(RenderWindow& window);


        
    private:
        
        Texture background_inimigo;
        Sprite backgroundSprite_inimigo;
        Vector2f posicao;
        Clock relogio;
        Time dps;
        

        bool textureLoaded;
        string projetilFile = "../assets/images/background/bullet2.png";

        vector<Projetil> projeteis; 
        
        Texture texturaProjetil;
        Sprite backgroundSprite_projetil;
    protected:
        float velocidade;   
        Time intervaloDisparo = seconds(3); 
        

};

#endif // INIMIGO_HPP