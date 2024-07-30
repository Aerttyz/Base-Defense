#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Heroi {
    public:
        Heroi(int vida, const string& heroiFile, const Font& fonte);
        void definirPosicao(const Vector2f& posicao);
        void mover();
        void renderizar(RenderWindow& window);
        void setVida(int novaVida);
        int getVida();
        void verificarColisao(const Sprite& sprite);
        void verificarColisao(const RectangleShape& shape);
        Sprite getSprite() const;
    
    private:
        float velocidade;
        int vida;
        Texture background_heroi;
        Sprite backgroundSprite_heroi;
        Vector2f posicao;
        Text  textoVida;
        Clock relogio;
        Time dps;
};


#endif // HEROI_HPP