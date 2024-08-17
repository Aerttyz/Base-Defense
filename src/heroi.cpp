#include <iostream>
#include "../include/heroi.hpp"
#include "cmath"


using namespace std;
using namespace sf; 

/**
 * @brief Construtor da classe Heroi
 * 
 * Este construtor inicializa o herói com uma certa quantidade de vida, uma imagem, e uma fonte para o texto.
 * 
 * @param vida Vida do herói
 * @param heroiFile Arquivo de imagem do herói
 * @param font Fonte do texto
 * 
 */
Heroi::Heroi(int vida, const string& heroiFile, const Font& font) : vida(vida) {
    if(!background_heroi.loadFromFile(heroiFile)) {
        cout << "Erro ao carregar imagem do herói" << endl;
    }
    backgroundSprite_heroi.setTexture(background_heroi);
    backgroundSprite_heroi.setPosition(450, 300);
    posicao = backgroundSprite_heroi.getPosition();

    textoVida.setFont(font);
    textoVida.setCharacterSize(20);
    textoVida.setFillColor(Color::White);
    textoVida.setString("Heroi");

    textoMunicao.setFont(font);
    textoMunicao.setCharacterSize(20);
    textoMunicao.setFillColor(Color::White);
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));

    projetilFile = "assets/images/background/hero_bullet.png";   
    if(!texturaProjetil.loadFromFile(projetilFile)) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    
    
    if(!bufferBulletSong.loadFromFile(bulletSongFile)) {
        cout << "Erro ao carregar música do projetil" << endl;
    }else {
        bulletSong.setBuffer(bufferBulletSong);
    }
    if(!barraVida.loadFromFile("assets/images/background/lifebar.png")) {
        cout << "Erro ao carregar barra de vida" << endl;
    }
    barraSprite.setTexture(barraVida);
    barraSprite.setTextureRect(barra1);


    backgroundSprite_projetil.setTexture(texturaProjetil);
    backgroundSprite_projetil.setPosition(posicao);
}

/**
 * @brief Retorna o sprite do herói
 * 
 * @return Sprite do herói 
 */
Sprite Heroi::getSprite() const {
    return backgroundSprite_heroi;
}

/**
 * @brief retorna a posição do herói
 * 
 * @return  Vector2f: Posição do herói
 */
Vector2f Heroi::getPosicao() {
    return backgroundSprite_heroi.getPosition();
}

/**
 * @brief Define a posição do herói
 * 
 * Define a posição do herói para a nova posição passada como parâmetro.
 * 
 * @param novaPosicao 
 * 
 */
void Heroi::definirPosicao(const Vector2f& novaPosicao) {
    posicao = novaPosicao;
}

/**
 * @brief Move o herói
 * 
 * Move o herói para a posição definida se a distância entre a posição atual e a nova posição for maior que 1.0f.
 * 
 */
void Heroi::mover() {
    Vector2f posicaoAtual = backgroundSprite_heroi.getPosition();
    Vector2f direcao = posicao - posicaoAtual;
    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if(distancia > 1.0f) {
        direcao /= distancia;
        backgroundSprite_heroi.move(direcao * velocidade * 0.01f);
    }
}

/**
 * @brief Atira um projetil na direção passada como parâmetro
 * 
 * Este método verifica se a quantidade de projeteis é maior que 0. 
 * Se for, decrementa a quantidade de projeteis e cria um novo projetil na direção passada como parâmetro.
 * 
 * 
 * 
 * @param direcao Direção do projetil de acordo com a posição do mouse
 */
void Heroi::atirar(const Vector2f& direcao) {
        if(quantidadeProjetil>0){
            Vector2f direcaoNormalizada = direcao / sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
            Projetil projetil(backgroundSprite_heroi.getPosition(), direcaoNormalizada, backgroundSprite_projetil, nullptr);
            projeteis.push_back(projetil);
            bulletSong.play();
            quantidadeProjetil--;
            textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
        }else{
            cout << "Sem munição" << endl;
        }
}

/**
 * @brief Atualiza a posição dos projeteis
 * 
 * Este método atualiza a posição de todos os projeteis do vetor de projeteis.
 * 
 * @param deltaTime 
 */
void Heroi::atualizarProjeteis(float deltaTime) {
    for (auto& projetil : projeteis) {
        projetil.mover(deltaTime);
    }
    projeteis.erase(remove_if(projeteis.begin(), projeteis.end(), [](const Projetil& p) {
        return p.getGlobalBounds().top + p.getGlobalBounds().height < 0;
    }), projeteis.end());
}

/**
 * @brief Retorna a vida do herói
 * 
 * @return int Vida do herói
 */
int Heroi::getVida() {
    return vida;
}

/**
 * @brief Define a vida do herói
 * 
 * Define a vida do herói para a nova vida passada como parâmetro.
 * 
 * @param novaVida Nova vida do herói
 */
void Heroi::setVida(int novaVida) {
    vida = novaVida;
    barraSprite.setTextureRect(barrasVida[1]);
    
}


void Heroi::TomarDano() {
   vida -= 100;
   int index = (100 - vida) / 10;
    if (index > 0 && index < 10) {
        barraSprite.setTextureRect(barrasVida[index]);
    }
    
}

/**
 * @brief Diminui a quantidade de projeteis
 * 
 * Diminui a quantidade de projeteis em 5.
 * 
 */
void Heroi::darMunicao() {
    quantidadeProjetil -= 5;
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
}

/**
 * @brief Recupera a vida do herói
 * 
 * Recupera 10 de vida do herói.
 * Atualiza a barra de vida de acordo com a vida atual.
 * 
 */
void Heroi::RecuperarVida() {
    vida += 10;
    if(vida > 100){
        vida = 100;
    }
    int index = (100 - vida) / 10;
    if (index > 0 && index < 10) {
        barraSprite.setTextureRect(barrasVida[index]);
    }
}

/**
 * @brief Retorna um número aleatório de projeteis 
 * 
 * @return int Número aleatório de projeteis entre 0 e 10
 */
int Heroi::getRandomQuantidadeProjetil() {
    int quantidade = rand() % 10;
    return quantidade;
}

/**
 * @brief Recupera a quantidade de projeteis
 * 
 * Recupera uma quantidade aleatória de projeteis com base no método getRandomQuantidadeProjetil().
 * Atualiza a quantidade de projeteis no texto.
 * 
 */
void Heroi::RecuperarMunicao() {
    quantidadeProjetil += getRandomQuantidadeProjetil();
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
}

void Heroi::setMunicao() {
    quantidadeProjetil = 100;
    textoMunicao.setString("Municao: " + to_string(quantidadeProjetil));
}

/**
 * @brief Verifica colisão com um sprite
 * 
 * Verifica se houve colisão com um sprite passado como parâmetro.
 * Se houver colisão, decrementa a vida do herói em 10.
 * Atualiza a barra de vida de acordo com a vida atual.
 * 
 * @param sprite Sprite a ser verificado a colisão
 * @return true Se houve colisão
 * @return false Se não houve colisão
 */
bool Heroi::verificarColisao(const Sprite& sprite) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        vida -= 10;
        if(vida < 0 ){
            vida = 0;
            
        }
        switch (vida)
        {
            case 90:
                barraSprite.setTextureRect(barrasVida[1]);
                break;
            case 80:
                barraSprite.setTextureRect(barrasVida[2]);
                break;
            case 70:
                barraSprite.setTextureRect(barrasVida[3]);
                break;
            case 60:
                barraSprite.setTextureRect(barrasVida[4]);
                break;
            case 50:
                barraSprite.setTextureRect(barrasVida[5]);
                break;
            case 40:
                barraSprite.setTextureRect(barrasVida[6]);
                break;
            case 30:
                barraSprite.setTextureRect(barrasVida[7]);
                break;
            case 20:
                barraSprite.setTextureRect(barrasVida[8]);
                break;
            case 10:
                barraSprite.setTextureRect(barrasVida[9]);
                break;
            default:
                break;
        }
        return true;      
    }
    return false;
}

/**
 * @brief Verifica colisão com um drop
 * 
 * Verifica se houve colisão com um drop passado como parâmetro.
 * 
 * @param sprite Sprite a ser verificado a colisão
 * @return true Se houve colisão
 * @return false Se não houve colisão
 */
bool Heroi::verificarColisaoDrop(const Sprite& sprite) {
    if (backgroundSprite_heroi.getGlobalBounds().intersects(sprite.getGlobalBounds())) {    
        return true;  
    }
    return false;
}


/**
 * @brief Retorna o vetor de projeteis
 * 
 * @return vector<Projetil>& Vetor de projeteis
 */
vector<Projetil>& Heroi::getProjeteis() {
    return projeteis;
}

/**
 * @brief Renderiza o herói
 * 
 * Renderiza o herói na janela passada como parâmetro.
 * Renderiza os projeteis na janela.
 * Renderiza o texto de vida e a barra de vida.
 * 
 * @param window Janela onde o herói será renderizado
 */
void Heroi::renderizar(RenderWindow& window) {
    window.draw(backgroundSprite_heroi);
    for (auto& projetil : projeteis) {
        projetil.renderizar(window);
    }

    textoVida.setPosition(20, 20);
    barraSprite.setPosition(20, 50);
    window.draw(textoVida);
    window.draw(barraSprite);
    
    
    textoMunicao.setPosition(20, 70);
    window.draw(textoMunicao);
 
    
}


