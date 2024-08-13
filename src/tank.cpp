#include "../include/tank.hpp"
#include <iostream>
#include <cmath>

Tank::Tank(int vida, const string& tankFile, const Font& font, Heroi *heroi, Base *base)
    : Heroi(vida, tankFile, font), heroi(heroi), base(base) {
    setVida(vida);  
    this->velocidade = 150.0f; 
    if (!background_tank.loadFromFile(tankFile)) {
        cout << "Erro ao carregar imagem do tanque" << endl;
    }
    backgroundSprite_tank.setTexture(background_tank);
    backgroundSprite_tank.setPosition(350, 300);
    posicao = backgroundSprite_tank.getPosition();

    textoVidaTank.setFont(font);
    textoVidaTank.setCharacterSize(20);
    textoVidaTank.setFillColor(Color::White);
    textoVidaTank.setString("Tank");

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
    textoVida.setString("Tank: ");
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
            int totalBarras = barrasVida.size();
            barraIndex = ((300 - vida) * (totalBarras - 1)) / 300;
            barraSprite.setTextureRect(barrasVida[barraIndex]);
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
    FloatRect textRect = textoVidaTank.getLocalBounds();
    textoVidaTank.setPosition(window.getSize().x - textRect.width - 20, 20);
    window.draw(textoVidaTank);
    barraSprite.setPosition(window.getSize().x - textRect.width - 20, 50);
    window.draw(barraSprite);
}