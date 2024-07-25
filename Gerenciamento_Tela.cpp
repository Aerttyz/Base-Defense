#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
#include <iostream>

using namespace std;
using namespace sf;
class heroi;
GerenciametoTela::GerenciametoTela(const string& backgroundFile, Heroi *heroi) : heroi(heroi) {
    if(!background.loadFromFile(backgroundFile)) {
        cout << "Erro ao carregar imagem de fundo" << endl;
    }
    backgroundSprite.setTexture(background);
    
}

void GerenciametoTela::eventos(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }
}

void GerenciametoTela::setBackgroundScale(RenderWindow& window) {
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
}

void GerenciametoTela::renderizar(RenderWindow& window) {
    setBackgroundScale(window);
    window.clear();
    window.draw(backgroundSprite);
    if(heroi != nullptr) {
        heroi->renderizar(window);
    }
    window.display();
}