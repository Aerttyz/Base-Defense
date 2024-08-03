#include "../include/projeteis.hpp"

Projetil::Projetil(const Vector2f& posicaoInicial, const Vector2f& direcao, const Texture& textura) : direcao(direcao), velocidade(400.0f) {
    backgroundSprite_projetil.setTexture(textura);
    backgroundSprite_projetil.setPosition(posicaoInicial);
}

Sprite Projetil::getSprite() const {
    return backgroundSprite_projetil;
}   


Vector2f Projetil::getPosicao() const{
    return backgroundSprite_projetil.getPosition();
}

void Projetil::mover() {
    backgroundSprite_projetil.move(direcao * velocidade * 0.01f);
}

void Projetil::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_projetil);
}

FloatRect Projetil::getGlobalBounds() const {
    return backgroundSprite_projetil.getGlobalBounds();
}   