#include "../include/tank.hpp"
#include <iostream>
#include <cmath>

/**
 * @brief Construtor da classe Tank que herda de Heroi
 * 
 *  
 * Este construtor herda de heroi e inicializa o tanque com uma certa quantidade de vida, uma imagem, e uma 
 * fonte para o texto.
 * 
 * @param vida Vida do tanque
 * @param tankFile Arquivo de imagem do tanque
 * @param font Fonte do texto
 * @param heroi referência para o herói do jogo
 * @param base referência para a base do jogo
 * 
 */
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

/**
 * @brief Retorna o sprite do tanque
 * 
 * Sobrescreve o método da classe Heroi para retornar o sprite do tanque
 * 
 * @return Sprite 
 */
Sprite Tank::getSprite() const {
    return backgroundSprite_tank;
}


/**
 * @brief Recupera a vida do tanque
 * 
 * Sobrescreve o método da classe Heroi para recuperar a vida do tanque
 * 
 */
void Tank::RecuperarVida() {
    vida += 30;  
    if (vida > 300) {  
        vida = 300;
    }
    textoVida.setString("Tank: ");
}

/**
 * @brief Troca munição por vida da base
 * 
 * Este método troca a munição do herói por vida para base
 * 
 */
void Tank::trocarMunicaoPorVidaBase() {
    
    heroi->darMunicao();
    base->recuperarVida();
}

/**
 * @brief Verifica se houve colisão com o tanque
 * 
 * Sobrescreve o método da classe Heroi para verificar se houve colisão com o tanque
 * A vida do tanque é decrementada em 10 e a barra de vida é atualizada
 * 
 * @param sprite sprite a ser verificado a colisão
 * @return true se houve colisão
 * @return false se não houve colisão
 */
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

/**
 * @brief Verifica se houve colisão com o drop
 * 
 * Sobrescreve o método da classe Heroi para verificar se houve colisão com o drop
 * 
 * @param sprite sprite a ser verificado a colisão
 * @return true se houve colisão
 * @return false se não houve colisão
 */
bool Tank::verificarColisaoDrop(const Sprite& sprite) {
    if (backgroundSprite_tank.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        return true;
    }return false;   
}

/**
 * @brief Move o tanque
 * 
 * Sobrescreve o método da classe Heroi para mover o tanque
 * Move o tanque de acordo com as teclas pressionadas e uma velocidade
 * 
 */
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

/**
 * @brief Renderiza o tanque
 * 
 * Sobrescreve o método da classe Heroi para renderizar o tanque e a sua barra de vida
 * 
 * @param window Janela onde o tanque será renderizado
 */
void Tank::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_tank);
    FloatRect textRect = textoVidaTank.getLocalBounds();
    textoVidaTank.setPosition(window.getSize().x - textRect.width - 20, 20);
    window.draw(textoVidaTank);
    barraSprite.setPosition(window.getSize().x - textRect.width - 20, 50);
    window.draw(barraSprite);
}