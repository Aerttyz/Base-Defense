#ifndef TANK_HPP
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include "../include/heroi.hpp" 
#include "../include/base.hpp"

using namespace std;
using namespace sf;
//tank herda de heroi
class Tank : public Heroi {
    public:
        Tank(int vida, const string& tankFile, const Font& font, Heroi *heroi, Base *base);
        void mover();
        void RecuperarVida() override;
        bool verificarColisao(const Sprite& sprite) override;
        void renderizar(RenderWindow& window) override;
        void trocarMunicaoPorVidaBase();
        bool verificarColisaoDrop(const Sprite& sprite) override;
        Sprite getSprite() const override;
    private:  
        Sprite backgroundSprite_tank;
        Texture background_tank;
        Vector2f posicao;
        Clock relogio;

        Heroi *heroi;
        Base *base;

        Text textoVidaTank;
        int barraIndex = 0;
};


#endif // TANK_HPP