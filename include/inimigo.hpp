#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class Inimigo{
    public:
        Inimigo(const string& inimigoFile);
        void mover();
        void renderizar(RenderWindow& window);
        //void verificarColisao(const Sprite& sprite);
        void setPosicao(const Vector2f& posicao);
        sf::Vector2f getPosicao() const;
        Sprite getSprite() const;
        
        bool isTextureLoaded() const;   
        
    private:
        float velocidade;
        Texture background_inimigo;
        Sprite backgroundSprite_inimigo;
        Vector2f posicao;
        Clock relogio;
        Time dps;

        bool textureLoaded;

};

#endif // INIMIGO_HPP