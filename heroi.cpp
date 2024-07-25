#include <iostream>
#include "heroi.hpp"

using namespace std;
using namespace sf; 

Heroi::Heroi(const string& heroiFile) {
    if(!background_heroi.loadFromFile(heroiFile)) {
        cout << "Erro ao carregar imagem do herói" << endl;
    }
    backgroundSprite_heroi.setTexture(background_heroi);
}

void Heroi::mover() {
    //TODO
}

void Heroi::atirar() {
    //TODO
}

void Heroi::tomarDano() {
    //TODO
}

void Heroi::curar() {
    //TODO
}

void Heroi::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_heroi);
}


