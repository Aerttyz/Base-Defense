#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"
#include "cmath"
using namespace std;
using namespace sf;

//Construtor
Inimigo::Inimigo(const string& inimigoFile) : textureLoaded(false), velocidade(100.0f), posicao(Vector2f(400, 300)), dps(seconds(1.0f)) { 
        if (!background_inimigo.loadFromFile(inimigoFile)) {
            cerr << "Erro ao carregar a imagem do inimigo" << endl;
            exit(1);
        }else{
            backgroundSprite_inimigo.setTexture(background_inimigo);
            textureLoaded = true;
        }
    }

//Move o inimigo
void Inimigo::mover() {
    Vector2f posicaoAtual = backgroundSprite_inimigo.getPosition();
    Vector2f direcao = posicao - posicaoAtual;
    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if(distancia > 1.0f) {
        direcao /= distancia;
        backgroundSprite_inimigo.move(direcao * velocidade * 0.01f);
    }
}

//Verifica colisão com um sprite
bool Inimigo::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_inimigo.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        if(relogio.getElapsedTime() > dps) {
            cout << "Colisão detectada" << endl;
            return true;
            relogio.restart();
        }
    }
    return false;
}

//Define a posição do inimigo
void Inimigo::setPosicao(const Vector2f& posicao) {
        backgroundSprite_inimigo.setPosition(posicao);
    }

//Retorna a posição do inimigo
Vector2f Inimigo::getPosicao() const {
        return backgroundSprite_inimigo.getPosition();
    }

//Retorna o sprite do inimigo
Sprite Inimigo::getSprite() const {
    return backgroundSprite_inimigo;
}

//Renderiza o inimigo
void Inimigo::renderizar(RenderWindow& window) {
        if(textureLoaded){
            window.draw(backgroundSprite_inimigo);
        } else {
            cerr << "Erro ao renderizar inimigo" << endl;
        }     
    }

//Retorna se a textura foi carregada
bool Inimigo::isTextureLoaded() const {
        return textureLoaded;
    }
    
