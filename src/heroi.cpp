#include <iostream>
#include "../include/heroi.hpp"
#include "cmath"


using namespace std;
using namespace sf; 

//Construtor
Heroi::Heroi(int vida, const string& heroiFile, const Font& font) : velocidade(300.0f), quantidadeProjetil(10) ,vida(vida), dps(seconds(0.5f)) {
    if(!background_heroi.loadFromFile(heroiFile)) {
        cout << "Erro ao carregar imagem do herói" << endl;
    }
    backgroundSprite_heroi.setTexture(background_heroi);
    posicao = backgroundSprite_heroi.getPosition();

    textoVida.setFont(font);
    textoVida.setCharacterSize(20);
    textoVida.setFillColor(Color::White);
    textoVida.setString("Heroi: " + to_string(vida));

    textoMunicao.setFont(font);
    textoMunicao.setCharacterSize(20);
    textoMunicao.setFillColor(Color::White);
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));

    projetilFile = "assets/images/background/bullet1.png";   
    if(!texturaProjetil.loadFromFile(projetilFile)) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    
    bulletSongFile = "assets/music/bulletsong.ogg";
    if(!bufferBulletSong.loadFromFile(bulletSongFile)) {
        cout << "Erro ao carregar música do projetil" << endl;
    }else {
        bulletSong.setBuffer(bufferBulletSong);
    }


    backgroundSprite_projetil.setTexture(texturaProjetil);
    backgroundSprite_projetil.setPosition(posicao);
}

//Retorna o sprite do herói
Sprite Heroi::getSprite() const {
    return backgroundSprite_heroi;
}

//Retorna a posição do herói
Vector2f Heroi::getPosicao() {
    return backgroundSprite_heroi.getPosition();
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

void Heroi::atirar(const Vector2f& direcao) {
        if(quantidadeProjetil>0){
            Vector2f direcaoNormalizada = direcao / sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
            Projetil projetil(backgroundSprite_heroi.getPosition(), direcaoNormalizada, backgroundSprite_projetil);
            projeteis.push_back(projetil);
            bulletSong.play();
            quantidadeProjetil--;
            textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
        }else{
            cout << "Sem munição" << endl;
        }
}

void Heroi::atualizarProjeteis(float deltaTime) {
    for (auto& projetil : projeteis) {
        projetil.mover(deltaTime);
    }
    projeteis.erase(remove_if(projeteis.begin(), projeteis.end(), [](const Projetil& p) {
        return p.getGlobalBounds().top + p.getGlobalBounds().height < 0;
    }), projeteis.end());
}

void Heroi::setVida(int novaVida) {
    vida = novaVida;
    textoVida.setString("Heroi: " + to_string(vida));
}

int Heroi::getVida() {
    return vida;
}

void Heroi::TomarDano() {
   //TODO
}

void Heroi::RecuperarVida() {
    vida += 10;
    textoVida.setString("Heroi: " + to_string(vida));
}

void Heroi::RecuperarMunicao() {
    quantidadeProjetil += 10;
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
}


//Verifica colisão com um sprite

bool Heroi::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
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


bool Heroi::verificarColisaoDrop(const Sprite& sprite) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            textoVida.setString("Heroi: " + to_string(vida));
            relogio.restart(); 
            return true;  
        
    }
    return false;
}

//Verifica colisão com um retângulo de testes

void Heroi::verificarColisao(const RectangleShape& shape) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(shape.getGlobalBounds())) {
         if(relogio.getElapsedTime() > dps) {
            vida = vida - 10;
           
        textoVida.setString("Heroi: " + to_string(vida));   
        relogio.restart();
        }
    }
}

vector<Projetil>& Heroi::getProjeteis() {
    return projeteis;
}

//Renderiza o herói
void Heroi::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_heroi);
    for (auto& projetil : projeteis) {
        projetil.renderizar(window);
    }

    FloatRect textRect = textoVida.getLocalBounds();
    textoVida.setPosition(window.getSize().x - textRect.width - 10, 10);
    FloatRect textRectMunicao = textoMunicao.getLocalBounds();
    textoMunicao.setPosition(window.getSize().x - textRect.width - 10, 70);
    window.draw(textoVida);
    window.draw(textoMunicao);

    
}


