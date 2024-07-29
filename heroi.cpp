#include <iostream>
#include "heroi.hpp"
#include "cmath"


using namespace std;
using namespace sf; 

//Construtor
Heroi::Heroi(int vida, const string& heroiFile) : velocidade(0.5f), vida(vida){
    if(!background_heroi.loadFromFile(heroiFile)) {
        cout << "Erro ao carregar imagem do herói" << endl;
    }
    backgroundSprite_heroi.setTexture(background_heroi);
    posicao = backgroundSprite_heroi.getPosition();
}

//Define a posição do herói
void Heroi::definirPosicao(const Vector2f& novaPosicao) {
    posicao = novaPosicao;
}

//Move o herói
void Heroi::mover() {
    Vector2f posicaoAtual = backgroundSprite_heroi.getPosition();
    Vector2f direcao = posicao - posicaoAtual;
    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if(distancia > 1.0f) {
        direcao /= distancia;
        backgroundSprite_heroi.move(direcao * velocidade * 0.01f);
    }
}

void Heroi::setVida(int novaVida) {
    vida = novaVida;
}

int Heroi::getVida() {
    return vida;
}

void Heroi::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        vida -= 10;
        if (vida < 0) {
            vida = 0;
        }
    }
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

//Renderiza o herói
void Heroi::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_heroi);
    
}


