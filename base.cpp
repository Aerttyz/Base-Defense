#include <iostream>
#include "base.hpp"

using namespace std;
using namespace sf;

Base::Base(int vida, const string& baseFile, const Font& font) : vida(100) {
    if(!background_base.loadFromFile(baseFile)) {
        cout << "Erro ao carregar imagem da base" << endl;
    }
    backgroundSprite_base.setTexture(background_base);
    backgroundSprite_base.setPosition(Vector2f(0.0f, 400.0f));

    textoVidaBase.setFont(font);
    textoVidaBase.setCharacterSize(20);
    textoVidaBase.setFillColor(Color::White);
    textoVidaBase.setString("Base: " + to_string(vida));
}

Sprite Base::getSprite() const {
    return backgroundSprite_base;
}

void Base::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_base);
    window.draw(textoVidaBase);
}