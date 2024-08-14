#include "../include/projeteis.hpp"
#include "../include/inimigo.hpp"
#include <iostream>
using namespace std;

/**
 * @brief Construtor da classe Projetil
 * 
 *  
 * Este construtor inicializa o projétil com uma certa posição, direção, sprite e dono.
 * 
 * @param posicaoInicial Posição inicial do projétil
 * @param direcao Direção do projétil
 * @param spriteProjetil Sprite do projétil
 * @param owner Dono do projétil
 * 
 */
Projetil::Projetil(const Vector2f& posicaoInicial, const Vector2f& direcao, const Sprite& spriteProjetil, Inimigo* owner) 
: direcao(direcao), velocidade(400.0f), velocidadeInimigo(100.0f), owner(owner) {
    backgroundSprite_projetil = spriteProjetil;
    textureLoaded = backgroundSprite_projetil.getTexture() != nullptr;
    backgroundSprite_projetil.setPosition(posicaoInicial);

}

/**
 * @brief Retorna a sprite do projétil
 * 
 * @return Sprite 
 */
Sprite Projetil::getSprite() const {
    return backgroundSprite_projetil;
}   

/**
 * @brief Verifica se houve colisão com um sprite
 * 
 * @param sprite Sprite a ser verificada a colisão
 * @return true 
 * @return false 
 */
bool Projetil::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_projetil.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
      cout << "Colisão detectada proje" << endl;  
      return true;
    }
    return false;
}

/**
 * @brief Verifica se houve colisão com a janela
 * 
 * @param window Janela a ser verificada a colisão
 * @return true 
 * @return false 
 */
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

/**
 * @brief Retorna a posição do projétil
 * 
 * @return Vector2f: Posição do projétil
 */
Vector2f Projetil::getPosicao() const{
    return backgroundSprite_projetil.getPosition();
}

/**
 * @brief Define a posição do projétil
 * 
 * @param posicao Posição a ser definida
 */
void Projetil::setPosicao(const sf::Vector2f& posicao) {
    backgroundSprite_projetil.setPosition(posicao);
}

/**
 * @brief Define a direção do projétil
 * 
 * @param direcao Direção a ser definida
 */
void Projetil::setDirecao(const sf::Vector2f& direcao) {
    this->direcao = direcao;
}

/**
 * @brief Move o projétil
 * 
 * Move o projétil de acordo com a direção e a velocidade
 * 
 * @param deltaTime 
 */
void Projetil::mover(float deltaTime) {
    backgroundSprite_projetil.move(direcao * velocidade * deltaTime);
}

/**
 * @brief Move o projétil do inimigo
 * 
 * Move o projétil do inimigo de acordo com a direção e a velocidade
 * 
 * @param deltaTime 
 */
void Projetil::moverInimigo(float deltaTime) {
    backgroundSprite_projetil.move(direcao * velocidadeInimigo * deltaTime);
}

/**
 * @brief Retorna o dono do projétil
 * 
 * @return Inimigo* 
 */
Inimigo* Projetil::getOwner() const {
    return owner;
}


/**
 * @brief Renderiza o projétil
 * 
 * @param window Janela a ser renderizada
 */
void Projetil::renderizar(RenderWindow& window) {
    if (backgroundSprite_projetil.getTexture() == nullptr) {
        cout << "Sprite do projétil não tem textura." << endl;
    }
    window.draw(backgroundSprite_projetil);

}

/**
 * @brief Retorna o retângulo de colisão do projétil
 * 
 * @return FloatRect 
 */
FloatRect Projetil::getGlobalBounds() const {
    return backgroundSprite_projetil.getGlobalBounds();
}   

/**
 * @brief Verifica se a textura do projétil foi carregada
 * 
 * @return true 
 * @return false 
 */
bool Projetil::isTextureLoaded() const {
        return textureLoaded;
    }
    