#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"
#include "../include/projeteis.hpp" 
#include "../include/drops.hpp"
#include "cmath"
using namespace std;
using namespace sf;

Inimigo::Inimigo(const string& inimigoFile) : textureLoaded(false), velocidade(50.0f), posicao(Vector2f(400, 300)), dps(seconds(1.0f)), intervaloDisparo(seconds(2)) { 
        if (!background_inimigo.loadFromFile(inimigoFile)) {
            cerr << "Erro ao carregar a imagem do inimigo" << endl;
            exit(1);
        }else{
            backgroundSprite_inimigo.setTexture(background_inimigo);
            textureLoaded = true;
        }
        
        
        if(!texturaProjetil.loadFromFile(projetilFile)) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    backgroundSprite_projetil.setTexture(texturaProjetil);
   
}

void Inimigo::mover() {
    Vector2f posicaoAtual = backgroundSprite_inimigo.getPosition();
    Vector2f direcao = posicao - posicaoAtual;
    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if(distancia > 1.0f) {
        direcao /= distancia;
        backgroundSprite_inimigo.move(direcao * velocidade * 0.01f);
    }
}

void Inimigo::atirarCOOP(const Vector2f& direcaoHeroi, const Vector2f& direcaoTank, const float distanciaHeroi, const float distanciaTank) {
    if(relogio.getElapsedTime() > intervaloDisparo) {
        if(distanciaTank < distanciaHeroi) {
            Vector2f direcaoNormalizada = direcaoTank;
            float magnitude = sqrt(direcaoNormalizada.x * direcaoNormalizada.x + direcaoNormalizada.y * direcaoNormalizada.y);
            if (magnitude != 0) {
                direcaoNormalizada /= magnitude;
            }
            Projetil projetil(backgroundSprite_inimigo.getPosition(), direcaoNormalizada, backgroundSprite_projetil, this);
            projetil.setPosicao(backgroundSprite_inimigo.getPosition());
            projeteis.push_back(projetil);
            relogio.restart();
        } else {
            Vector2f direcaoNormalizada = direcaoHeroi;
            float magnitude = sqrt(direcaoNormalizada.x * direcaoNormalizada.x + direcaoNormalizada.y * direcaoNormalizada.y);
            if (magnitude != 0) {
                direcaoNormalizada /= magnitude;
            }
            Projetil projetil(backgroundSprite_inimigo.getPosition(), direcaoNormalizada, backgroundSprite_projetil, this);
            projetil.setPosicao(backgroundSprite_inimigo.getPosition());
            projeteis.push_back(projetil);
            relogio.restart();
        }
    }
}

void Inimigo::atirar(const Vector2f& direcao) {
    if(relogio.getElapsedTime() > intervaloDisparo) {

        Vector2f direcaoNormalizada = direcao;
        float magnitude = sqrt(direcaoNormalizada.x * direcaoNormalizada.x + direcaoNormalizada.y * direcaoNormalizada.y);
         if (magnitude != 0) {
            direcaoNormalizada /= magnitude;
        }
        
        Projetil projetil(backgroundSprite_inimigo.getPosition(), direcaoNormalizada, backgroundSprite_projetil, this);
        projetil.setPosicao(backgroundSprite_inimigo.getPosition());
        projeteis.push_back(projetil);
        relogio.restart();
    }
}

void Inimigo::atualizarProjeteis(float deltaTime, RenderWindow& window) {
    for (auto it = projeteis.begin(); it != projeteis.end();) {
        it->moverInimigo(deltaTime); 
        if (it->verificarColisaoJanela(window)) {
            it = projeteis.erase(it); 
        } else {
            ++it;
        }
    }
}

bool Inimigo::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_inimigo.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        return true;
    }
    return false;
}

void Inimigo::setPosicao(const Vector2f& posicao) {
    backgroundSprite_inimigo.setPosition(posicao);
}

Vector2f Inimigo::getPosicao() const {
    return backgroundSprite_inimigo.getPosition();
}

Sprite Inimigo::getSprite() const {
    return backgroundSprite_inimigo;
}

vector<Projetil>& Inimigo::getProjeteis() {
    return projeteis;
}

void Inimigo::renderizar(RenderWindow& window) {
    if(textureLoaded){
        window.draw(backgroundSprite_inimigo);
        for(auto& projetil : projeteis){
            projetil.renderizar(window);
        }
    } else {
        cerr << "Erro ao renderizar inimigo" << endl;
    }
}

bool Inimigo::isTextureLoaded() const {
        return textureLoaded;
}