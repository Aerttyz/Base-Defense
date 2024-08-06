#include "../include/drops.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//Construtor
Drop::Drop(const Sprite& dropSprite, const Vector2f& posicao) : textureLoaded(false), posicao(posicao) {
    
    backgroundSprite_drop = dropSprite;
    backgroundSprite_drop.setPosition(posicao);
    textureLoaded = backgroundSprite_drop.getTexture() != nullptr;

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