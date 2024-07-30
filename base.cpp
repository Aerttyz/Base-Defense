#include <iostream>
#include "base.hpp"

using namespace std;
using namespace sf;

Base::Base(int vidaBase, const string& baseFile, const Font& font) : vida(vidaBase), dps(seconds(1.0f)) {
    cout << "Construtor Base com Vida" << endl;
    if(!background_base.loadFromFile(baseFile)) {
        cout << "Erro ao carregar imagem da base" << endl;
    }
    backgroundSprite_base.setTexture(background_base);
    //backgroundSprite_base.setOrigin(backgroundSprite_base.getLocalBounds().width / 2, backgroundSprite_base.getLocalBounds().height / 2);
    backgroundSprite_base.setPosition(400.0f, 300.0f);

    textoVidaBase.setFont(font);
    textoVidaBase.setCharacterSize(20);
    textoVidaBase.setFillColor(Color::White);
    textoVidaBase.setString("Base: " + to_string(vidaBase));
}

Sprite Base::getSprite() const {
    return backgroundSprite_base;
}

void Base::setVidaBase(int novaVidaBase) {
    cout << "Vida Base: " << novaVidaBase << endl;
    vida = novaVidaBase;
    textoVidaBase.setString("Base: " + to_string(vida));
}

int Base::getVidaBase() {
    return vida;
}

void Base::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_base.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        if(relogio.getElapsedTime() > dps) {
            vida -= 10;
            textoVidaBase.setString("Base: " + to_string(vida));
            relogio.restart();
        }
    }
}

void Base::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_base);
    FloatRect textRect = textoVidaBase.getLocalBounds();
    textoVidaBase.setPosition(window.getSize().x - textRect.width - 10, 40);
    window.draw(textoVidaBase);
}