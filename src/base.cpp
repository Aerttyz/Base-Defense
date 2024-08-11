#include <iostream>
#include "../include/base.hpp"

using namespace std;
using namespace sf;

Base::Base(int vidaBase, const string& baseFile, const Font& font, const Vector2f& windowSize) : vida(vidaBase), dps(seconds(0.01f)) {
    if(!background_base.loadFromFile(baseFile)) {
        cout << "Erro ao carregar imagem da base" << endl;
    }
    backgroundSprite_base.setTexture(background_base);
    FloatRect spriteBounds = backgroundSprite_base.getLocalBounds();
    backgroundSprite_base.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
    backgroundSprite_base.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    textoVidaBase.setFont(font);
    textoVidaBase.setCharacterSize(20);
    textoVidaBase.setFillColor(Color::White);
    textoVidaBase.setString("Base: " + to_string(vidaBase));
}

//Retorna o sprite da base
Sprite Base::getSprite() const {
    return backgroundSprite_base;
}

//Define a vida da base
void Base::setVidaBase(int novaVidaBase) {
    cout << "Vida Base: " << novaVidaBase << endl;
    vida = novaVidaBase;
    textoVidaBase.setString("Base: " + to_string(vida));
}


int Base::getVidaBase() {
    return vida;
}

void Base::recuperarVida() {
    
        vida += 10;
        if(vida > 200) {
            vida = 200;
        }
        textoVidaBase.setString("Base: " + to_string(vida));
    
}

//Verifica colisão com um sprite e diminui a vida da base
bool Base::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_base.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            vida -= 10;
            cout << "Colisão detectada com a base" << endl;
            if(vida <= 0) {
                vida = 0;
            }
            textoVidaBase.setString("Base: " + to_string(vida));
            return true;
            relogio.restart();
        
    }
    return false;
}

void Base::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_base);
    FloatRect textRect = textoVidaBase.getLocalBounds();
    textoVidaBase.setPosition(window.getSize().x - textRect.width - 10, 40);
    window.draw(textoVidaBase);
}