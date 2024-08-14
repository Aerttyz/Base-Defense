#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"
#include "../include/projeteis.hpp" 
#include "../include/drops.hpp"
#include "cmath"
using namespace std;
using namespace sf;

/**
 * @brief Construtor da classe Inimigo
 * 
 *  
 * Este construtor inicializa o inimigo com uma certa imagem.
 * 
 * @param inimigoFile Arquivo de imagem do inimigo
 * 
 */
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

/**
 * @brief Move o inimigo em direção ao centro do mapa
 * 
 *  
 * Este método move o inimigo com uma certa velocidade em direção ao centro do mapa.
 * 
 */
void Inimigo::mover() {
    Vector2f posicaoAtual = backgroundSprite_inimigo.getPosition();
    Vector2f direcao = posicao - posicaoAtual;
    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if(distancia > 1.0f) {
        direcao /= distancia;
        backgroundSprite_inimigo.move(direcao * velocidade * 0.01f);
    }
}

/**
 * @brief Realiza o disparo de projéteis em direção ao herói ou ao tanque aliado no modo cooperativo.
 * 
 * Esta função é responsável por decidir para qual alvo (herói ou tanque aliado) o inimigo deve atirar 
 * no modo COOP, com base na distância entre o inimigo e os dois alvos. O inimigo dispara o projétil 
 * na direção do alvo mais próximo.
 * 
 * @param direcaoHeroi Vetor direção do inimigo em relação ao herói.
 * @param direcaoTank Vetor direção do inimigo em relação ao tanque aliado.
 * @param distanciaHeroi A distância entre o inimigo e o herói.
 * @param distanciaTank A distância entre o inimigo e o tanque aliado.
 * 
 * @details
 * - A função verifica se o tempo decorrido desde o último disparo é maior que o intervalo de disparo.
 * - Se a distância até o tanque aliado (`distanciaTank`) for menor que a distância até o herói (`distanciaHeroi`), 
 *   o inimigo dispara um projétil na direção do tanque aliado.
 * - Se a distância até o herói for menor ou igual à distância até o tanque aliado, o inimigo dispara um projétil na direção do herói.
 * - A direção de disparo é normalizada (vetor de comprimento 1) antes de criar o projétil.
 * - O projétil é criado na posição atual do inimigo e é adicionado à lista de projéteis (`projeteis`).
 * - O relógio de disparo (`relogio`) é reiniciado após o disparo para controlar o intervalo entre disparos.
 */
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

/**
 * @brief Realiza o disparo de um projétil em direção ao herói.
 * 
 * Esta função é responsável por fazer com que o inimigo dispare um projétil na direção do herói. O projétil é lançado
 * na direção fornecida, após a normalização do vetor de direção.
 * 
 * @param direcao Vetor direção do inimigo em relação ao herói.
 * 
 * @details
 * - A função verifica se o tempo decorrido desde o último disparo é maior que o intervalo de disparo (`intervaloDisparo`).
 * - O vetor direção (`direcao`) é normalizado, ou seja, convertido em um vetor de comprimento 1.
 * - Um novo projétil é criado na posição atual do inimigo (`backgroundSprite_inimigo.getPosition()`) e é direcionado na direção normalizada.
 * - O projétil é adicionado à lista de projéteis (`projeteis`) do inimigo.
 * - O relógio de disparo (`relogio`) é reiniciado após o disparo para controlar o intervalo entre disparos.
 */
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

/**
 * @brief Atualiza a posição dos projéteis do inimigo.
 * 
 * Este método é responsável por atualizar a posição de todos os projéteis do inimigo. Para cada projétil, 
 * a função `moverInimigo` é chamada para atualizar a posição do projétil. Se o projétil sair da janela, ele é removido.
 * 
 * @param deltaTime O tempo decorrido desde a última atualização.
 * @param window Referência para a janela de renderização.
 * 
 * @details
 * - Para cada projétil na lista de projéteis (`projeteis`), a função `moverInimigo` é chamada para atualizar a posição do projétil.
 * - Se o projétil sair da janela de renderização, ele é removido da lista de projéteis.
 */
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

/**
 * @brief Verifica se houve colisão entre o inimigo e um objeto Sprite.
 * 
 * Esta função verifica se houve colisão entre o inimigo e um objeto Sprite. A função `getGlobalBounds` é utilizada
 * para obter o retângulo delimitador do inimigo e do objeto Sprite. Se os retângulos se sobrepõem, a função retorna `true`.
 * 
 * @param sprite Objeto Sprite a ser verificado.
 * 
 * @return true Se houve colisão entre o inimigo e o objeto Sprite.
 * @return false Se não houve colisão entre o inimigo e o objeto Sprite.
 */
bool Inimigo::verificarColisao(const Sprite& sprite) {
    if(backgroundSprite_inimigo.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        return true;
    }
    return false;
}

/**
 * @brief Define a posição do inimigo.
 * 
 * Este método define a posição do inimigo na tela.
 * 
 * @param posicao Vetor posição a ser definido.
 */
void Inimigo::setPosicao(const Vector2f& posicao) {
    backgroundSprite_inimigo.setPosition(posicao);
}

/**
 * @brief Retorna a posição do inimigo.
 * 
 * @return Vector2f Vetor posição do inimigo.
 */
Vector2f Inimigo::getPosicao() const {
    return backgroundSprite_inimigo.getPosition();
}

/**
 * @brief Retorna o Sprite do inimigo.
 * 
 * @return Sprite Sprite do inimigo.
 */
Sprite Inimigo::getSprite() const {
    return backgroundSprite_inimigo;
}

/**
 * @brief Retorna a lista de projéteis do inimigo.
 * 
 * @return vector<Projetil>& Referência para a lista de projéteis do inimigo.
 */
vector<Projetil>& Inimigo::getProjeteis() {
    return projeteis;
}

/**
 * @brief Renderiza o inimigo na janela de renderização.
 * 
 * Este método é responsável por renderizar o inimigo. Para cada projétil na lista de projéteis,
 * a função `renderizar` é chamada para renderizar o projétil.
 * 
 * @param window Referência para a janela de renderização.
 * 
 * @details
 * - Se a textura do inimigo foi carregada com sucesso, o inimigo é renderizado na janela de renderização.
 * - Para cada projétil na lista de projéteis, a função `renderizar` é chamada para renderizar o projétil.
 * - Se ocorrer um erro ao renderizar o inimigo, uma mensagem de erro é exibida.
 */
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

/**
 * @brief Verifica se a textura do inimigo foi carregada com sucesso.
 * 
 * @return true Se a textura do inimigo foi carregada com sucesso.
 * @return false Se a textura do inimigo não foi carregada com sucesso.
 */
bool Inimigo::isTextureLoaded() const {
        return textureLoaded;
}