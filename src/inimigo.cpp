#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"
#include "../include/projeteis.hpp" 
#include "cmath"
using namespace std;
using namespace sf;

//Construtor
Inimigo::Inimigo(const string& inimigoFile) : textureLoaded(false), velocidade(100.0f), posicao(Vector2f(400, 300)), dps(seconds(1.0f)), intervaloDisparo(seconds(1.0f)) { 
        if (!background_inimigo.loadFromFile(inimigoFile)) {
            cerr << "Erro ao carregar a imagem do inimigo" << endl;
            exit(1);
        }else{
            backgroundSprite_inimigo.setTexture(background_inimigo);
            textureLoaded = true;
        }
        projetilFile = "assets/images/background/bullet1.png";   
        if(!texturaProjetil.loadFromFile(projetilFile)) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    backgroundSprite_projetil.setTexture(texturaProjetil);
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

void Inimigo::atirar(const Vector2f& direcao) {
    if(relogio.getElapsedTime() > intervaloDisparo) {

        Vector2f direcaoNormalizada = direcao;
        float magnitude = sqrt(direcaoNormalizada.x * direcaoNormalizada.x + direcaoNormalizada.y * direcaoNormalizada.y);
         if (magnitude != 0) {
            direcaoNormalizada /= magnitude;
        }
        
        Projetil projetil(backgroundSprite_inimigo.getPosition(), direcaoNormalizada, backgroundSprite_projetil);
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

//Verifica colisão com um sprite
bool Inimigo::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_inimigo.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        cout << "Colisão detectada" << endl;
        return true;
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
            for(auto& projetil : projeteis){
                projetil.renderizar(window);
            }
        } else {
            cerr << "Erro ao renderizar inimigo" << endl;
        }     
    }

//Retorna se a textura foi carregada
bool Inimigo::isTextureLoaded() const {
        return textureLoaded;
    }
    
