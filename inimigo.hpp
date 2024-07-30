#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Inimigo{
    public:
        Inimigo(const string& inimigoFile);
        //void mover();
        void renderizar(RenderWindow& window);
        void verificarColisao(const Sprite& sprite);
    private:
        float velocidade;
        Texture background_inimigo;
        Sprite backgroundSprite_inimigo;
        Vector2f posicao;
};

#endif // INIMIGO_HPP