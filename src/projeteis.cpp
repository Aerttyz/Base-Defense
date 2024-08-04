#include "../include/projeteis.hpp"
#include <iostream>
using namespace std;

Projetil::Projetil(const Vector2f& posicaoInicial, const Vector2f& direcao, const Sprite& spriteProjetil) : direcao(direcao), velocidade(400.0f){
    backgroundSprite_projetil = spriteProjetil;
    textureLoaded = backgroundSprite_projetil.getTexture() != nullptr;
    backgroundSprite_projetil.setPosition(posicaoInicial);

}

Sprite Projetil::getSprite() const {
    return backgroundSprite_projetil;
}   

bool Projetil::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_projetil.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
      cout << "Colisão detectada proje" << endl;  
      return true;
    }
    return false;
}

bool Projetil::verificarColisaoJanela(const RenderWindow& window) {
        FloatRect spriteBounds = backgroundSprite_projetil.getGlobalBounds();
        Vector2u windowSize = window.getSize();
        
        if (spriteBounds.left < 0 || spriteBounds.left + spriteBounds.width > windowSize.x ||
            spriteBounds.top < 0 || spriteBounds.top + spriteBounds.height > windowSize.y) {
            cout << "Colisão com a borda da janela detectada" << endl;
            return true;
        }
        return false;
    }

Vector2f Projetil::getPosicao() const{
    return backgroundSprite_projetil.getPosition();
}

void Projetil::mover() {
    backgroundSprite_projetil.move(direcao * velocidade * 0.01f);
}

void Projetil::renderizar(RenderWindow& window) {
    if (backgroundSprite_projetil.getTexture() == nullptr) {
        cout << "Sprite do projétil não tem textura." << endl;
    }
    window.draw(backgroundSprite_projetil);

}

FloatRect Projetil::getGlobalBounds() const {
    return backgroundSprite_projetil.getGlobalBounds();
}   

bool Projetil::isTextureLoaded() const {
        return textureLoaded;
    }
    