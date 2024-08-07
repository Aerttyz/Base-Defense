#include "../include/drops.hpp"
#include "../include/heroi.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


//Construtor
Drop::Drop(const Sprite& dropSprite, const Vector2f& posicao, Heroi *heroi) : textureLoaded(false), posicao(posicao) {
    
    backgroundSprite_drop = dropSprite;
    backgroundSprite_drop.setPosition(posicao);
    textureLoaded = backgroundSprite_drop.getTexture() != nullptr;

}

int Drop::getRandomTipoDrop(){
    return rand() % 2;
}
bool Drop::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_drop.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
       
        return true;
    }
    return false;
}


Vector2f Drop::getPosicao() const {
    return backgroundSprite_drop.getPosition();
}

Sprite Drop::getSprite() const {
    return backgroundSprite_drop;
}

void Drop::setPosicao(const Vector2f& posicao) {
    backgroundSprite_drop.setPosition(posicao);
}


void Drop::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_drop);
}