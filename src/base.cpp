#include <iostream>
#include "../include/base.hpp"

using namespace std;
using namespace sf;

/**
 * @brief Construtor da classe Base    
 * 
 * Este construtor inicializa a base com uma certa quantidade de vida, uma imagem, e uma fonte para o texto.
 * 
 * @param vidaBase 
 * @param baseFile caminho da imagem da base
 * @param font fonte do texto
 * @param windowSize janela do jogo
 */
Base::Base(int vidaBase, const string& baseFile, const Font& font, const Vector2f& windowSize) : vida(vidaBase), dps(seconds(1)) {
    if(!background_base.loadFromFile(baseFile)) {
        cout << "Erro ao carregar imagem da base" << endl;
    }
    backgroundSprite_base.setTexture(background_base);
    FloatRect spriteBounds = backgroundSprite_base.getLocalBounds();
    backgroundSprite_base.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
    backgroundSprite_base.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    textoVidaBase.setFont(font);
    textoVidaBase.setCharacterSize(20);
    textoVidaBase.setFillColor(Color::White);
    textoVidaBase.setString("Base: " + to_string(vidaBase));
}

/**
 * @brief retorna o sprite da base
 * 
 * @return Sprite 
 */
Sprite Base::getSprite() const {
    return backgroundSprite_base;
}

/**
 * @brief Altera a vida da base
 * 
 * @param novaVidaBase nova vida da base
 */
void Base::setVidaBase(int novaVidaBase) {
    cout << "Vida Base: " << novaVidaBase << endl;
    vida = novaVidaBase;
    textoVidaBase.setString("Base: " + to_string(vida));
}

/**
 * @brief Retorna a vida da base
 * 
 * @return int 
 */
int Base::getVidaBase() {
    return vida;
}

/**
 * @brief Recupera a vida da base
 * 
 * Aumenta a vida da base em 10, mas não pode ultrapassar 200
 * 
 */
void Base::recuperarVida() {
    
        vida += 10;
        if(vida > 200) {
            vida = 200;
        }
        textoVidaBase.setString("Base: " + to_string(vida));
    
}

/**
 * @brief Regenera a vida da base
 * 
 * Regenera a vida da base em 1 a cada segundo
 * 
 */
void Base::baseUpRegenerarVida() {
    if(relogio.getElapsedTime() > dps) {
        vida += 1;
        if(vida > 200) {
            vida = 200;
        }
        textoVidaBase.setString("Base: " + to_string(vida));
        relogio.restart();
    }
}

/**
 * @brief Aumenta a vida da base
 * 
 * Aumenta a vida da base em 50, mas não pode ultrapassar 200
 * 
 */
void Base::aumentarVidaBase() {
    vida += 50;
    if(vida > 200) {
        vida = 200;
    }
    textoVidaBase.setString("Base: " + to_string(vida));
}

/**
 * @brief Verifica colisão com um sprite
 * 
 * Diminui a vida da base em 10 se houver colisão com um sprite
 * Atualiza o texto da vida da base
 * 
 * @param sprite sprite a ser verificado
 * @return true se houve colisão, false caso contrário
 */
bool Base::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_base.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            vida -= 10;
            cout << "Colisão detectada com a base" << endl;
            if(vida <= 0) {
                vida = 0;
            }
            textoVidaBase.setString("Base: " + to_string(vida));
            return true;
            relogio.restart();
        
    }
    return false;
}

/**
 * @brief Renderiza a base e o texto da vida da base
 * 
 * 
 * @param window janela do jogo
 */
void Base::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_base);
    FloatRect textRect = textoVidaBase.getLocalBounds();
    textoVidaBase.setPosition(window.getSize().x - textRect.width - 10, 70);
    window.draw(textoVidaBase);
}