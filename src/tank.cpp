#include "../include/tank.hpp"
#include <iostream>
#include <cmath>

Tank::Tank(int vida, const string& tankFile, const Font& fonte, Heroi *heroi, Base *base)
    : Heroi(vida, tankFile, fonte), heroi(heroi), base(base) {
    setVida(vida);  
    this->velocidade = 150.0f; 
    if (!background_tank.loadFromFile(tankFile)) {
        cout << "Erro ao carregar imagem do tanque" << endl;
    }
    backgroundSprite_tank.setTexture(background_tank);
    posicao = backgroundSprite_tank.getPosition();
}


Sprite Tank::getSprite() const {
    return backgroundSprite_tank;
}


// Sobrescreve o método para recuperar vida
void Tank::RecuperarVida() {
    vida += 30;  
    if (vida > 300) {  
        vida = 300;
    }
    textoVida.setString("Tank: " + to_string(vida));
}

void Tank::trocarMunicaoPorVidaBase() {
    
    heroi->darMunicao();
    base->recuperarVida();
}

// Sobrescreve o método para verificar colisão
bool Tank::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_tank.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            vida -= 10;
           
            if(vida < 0 ){
                vida = 0;
                
            }
            textoVida.setString("Heroi: " + to_string(vida));
            relogio.restart(); 
            return true;  
        
    }
    return false;
}

bool Tank::verificarColisaoDrop(const Sprite& sprite) {
    if (backgroundSprite_tank.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        return true;
    }return false;   
}

// Sobrescreve o método para ajustar a velocidade do tanque
void Tank::mover() {
    float deltaTime = relogio.restart().asSeconds();
    Vector2f direcao;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        direcao.y -= velocidade * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        direcao.y += velocidade * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direcao.x -= velocidade * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direcao.x += velocidade * deltaTime;
    }
    backgroundSprite_tank.move(direcao);
}

void Tank::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_tank);
    

    FloatRect textRect = textoVida.getLocalBounds();
    textoVida.setPosition(window.getSize().x - textRect.width - 100, 100);
    window.draw(textoVida);
}