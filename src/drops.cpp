#include "../include/drops.hpp"
#include "../include/heroi.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/**
 * @brief Construtor da classe Drop
 * 
 * Este construtor inicializa o drop com uma certa posição, um sprite e um tipo.
 * Inicializa também a textura do sprite e verifica se a textura foi carregada.
 * 
 * @param dropSprite sprite do drop
 * @param posicao posição do drop
 * @param heroi herói do jogo
 * @param tipo tipo do drop
 */
Drop::Drop(const Sprite& dropSprite, const Vector2f& posicao, Heroi *heroi, int tipo) : textureLoaded(false), posicao(posicao) {
    
    backgroundSprite_drop = dropSprite;
    backgroundSprite_drop.setPosition(posicao);
    textureLoaded = backgroundSprite_drop.getTexture() != nullptr;
    tipoDrop = tipo;
    tempoDeCriacao = clockDrop.getElapsedTime();
}

/**
 * @brief Retorna o tipo do drop
 * 
 * @return int 
 */
int Drop::getTipo() const {
    return tipoDrop;
}

/**
 * @brief Verifica se houve colisão com o drop
 * 
 * @param sprite sprite a ser verificado a colisão
 * @return true se houve colisão
 * @return false se não houve colisão
 */
bool Drop::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_drop.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
       
        return true;
    }
    return false;
}

/**
 * @brief Verifica se o drop já passou do tempo de desaparecer
 * 
 * @return true se já passou do tempo de desaparecer
 * @return false se ainda não passou do tempo de desaparecer
 */
bool Drop::verificarTempoDeDesaparecer() {
    Time tempoDecorrido = clockDrop.getElapsedTime() - tempoDeCriacao;
    return tempoDecorrido >= seconds(5);
}

/**
 * @brief Retorna a posição do drop
 * 
 * @return Vector2f: posição do drop
 */
Vector2f Drop::getPosicao() const {
    return backgroundSprite_drop.getPosition();
}

/**
 * @brief Retorna o sprite do drop
 * 
 * @return Sprite: sprite do drop
 */
Sprite Drop::getSprite() const {
    return backgroundSprite_drop;
}

/**
 * @brief Define a posição do drop
 * 
 * @param posicao posição do drop
 */
void Drop::setPosicao(const Vector2f& posicao) {
    backgroundSprite_drop.setPosition(posicao);
}

/**
 * @brief Renderiza o drop
 * 
 * @param window janela onde o drop será renderizado
 */
void Drop::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_drop);
}