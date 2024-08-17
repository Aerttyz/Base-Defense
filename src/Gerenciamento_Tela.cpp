#include "../include/Gerenciamento_Tela.hpp"
#include <iostream>
#include <cmath>
#include "../include/heroi.hpp"
#include "../include/base.hpp"
#include "../include/projeteis.hpp"
#include "../include/inimigo.hpp"
#include "../include/drops.hpp"
#include "../include/tank.hpp"
#include "../include/runner.hpp"
#include "../include/inimigoTank.hpp"

using namespace sf;
using namespace std;

/**
 * @brief Construtor da classe gerenciamentoTela.
 * 
 * Este construtor inicializa a tela do jogo, carregando imagens e fontes, configurando texturas e sprites, e
 * configurando a música de fundo. Também configura os elementos do menu e outras variáveis necessárias para
 * o gerenciamento da tela do jogo.
 * 
 * @param backgroundFile O caminho para o arquivo de imagem do fundo da tela.
 * @param backgroundMenuFile O caminho para o arquivo de imagem do fundo do menu.
 * @param musicaTemaFile O caminho para o arquivo de música de fundo.
 * @param heroi Ponteiro para o objeto do tipo Heroi, representando o herói no jogo.
 * @param base Ponteiro para o objeto do tipo Base, representando a base no jogo.
 * @param windowSize Tamanho da janela do jogo (largura e altura).
 */
gerenciamentoTela::gerenciamentoTela(const string& backgroundFile, const string& backgroundMenuFile,const string& musicaTemaFile, Heroi *heroi, Base *base, const Vector2f& windowSize) 
: heroi(heroi), base(base){

    iniciarArquivos(backgroundFile, backgroundMenuFile, musicaTemaFile);
    setaArquivos(windowSize);
    
}

/**
 * @brief Inicializa os arquivos de imagem, fonte e música do jogo.
 * 
 * Esta função carrega os arquivos de imagem, fonte e música do jogo, exibindo mensagens de erro caso ocorra algum problema
 * durante o carregamento dos arquivos.
 * 
 * @param backgroundFile O caminho para o arquivo de imagem do fundo da tela.
 * @param backgroundMenuFile O caminho para o arquivo de imagem do fundo do menu.
 * @param musicaTemaFile O caminho para o arquivo de música de fundo.
 */
void gerenciamentoTela::iniciarArquivos(const string& backgroundFile, const string& backgroundMenuFile,const string& musicaTemaFile){
    if(!background.loadFromFile(backgroundFile)) {
        cout << "Erro ao carregar imagem de fundo" << endl;
    }
    if(!font.loadFromFile("assets/fonts/DotGothic16-Regular.ttf")) {
        cout << "Erro ao carregar fonte" << endl;
    }
    if(!fontGame.loadFromFile("assets/fonts/LilitaOne-Regular.ttf")) {
        cout << "Erro ao carregar fonte" << endl;
    }
    if(!background_menu.loadFromFile(backgroundMenuFile)) {
        cout << "Erro ao carregar imagem de fundo do menu" << endl;
    }
    if(!texturaProjetil.loadFromFile("assets/images/background/bullet1.png")) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    if(!texturaDrop.loadFromFile("assets/images/background/energy_bullet.png")) {
        cout << "Erro ao carregar textura do drop" << endl;
    }
    if(!texturaDrop1.loadFromFile("assets/images/background/drop_life.png")) {
        cout << "Erro ao carregar textura do drop" << endl;
    }
    if(!texturaDrop2.loadFromFile("assets/images/background/upgrade.png")) {
        cout << "Erro ao carregar textura do drop" << endl;
    }
    if(!musicaTema.openFromFile(musicaTemaFile)) {
        cout << "Erro ao carregar música" << endl;
    }
    if(!musicaGameOver.openFromFile("assets/music/game_over.ogg")) {
        cout << "Erro ao carregar música de game over" << endl;
    }
    if(!bufferEscolhaMenu.loadFromFile("assets/music/Menu-Choice.ogg")) {
        cout << "Erro ao carregar música de escolha do menu" << endl;
    }
}

/**
 * @brief Configura os arquivos de imagem, fonte e música do jogo.
 * 
 * Esta função configura os arquivos de imagem, fonte e música do jogo, definindo texturas e sprites para o fundo da tela,
 * o fundo do menu, os botões do menu, a música de fundo e o texto do menu.
 * 
 * @param windowSize O tamanho da janela do jogo (largura e altura).
 */
void gerenciamentoTela::setaArquivos(const Vector2f& windowSize){
    musicaTema.setLoop(true);
    musicaTema.play();
    escolhaMenu.setBuffer(bufferEscolhaMenu);

    spriteDrop.setTexture(texturaDrop);
    spriteDrop1.setTexture(texturaDrop1);
    spriteDrop2.setTexture(texturaDrop2);

    backgroundSprite_projetil.setTexture(texturaProjetil);

   
    backgroundSprite.setTexture(background);
    backgroundSprite_menu.setTexture(background_menu);

    spawRelogio.restart();

    
    textoKills.setFont(fontGame);
    textoKills.setCharacterSize(20);
    textoKills.setFillColor(Color::White);
    textoKills.setString("ABATES:" + to_string(Kills));
    FloatRect textRectKill = textoKills.getLocalBounds();
    textoKills.setOrigin(textRectKill.left + textRectKill.width/2.0f, textRectKill.top  + textRectKill.height/2.0f);
    textoKills.setPosition(windowSize.x / 2.0f, 20);

    vector<string> opcoes = {"Solo", "Dupla", "Dificuldade"};
    for (size_t i = 0; i < opcoes.size(); ++i) {
        Text botao;
        botao.setFont(font);
        botao.setString(opcoes[i]);
        botao.setCharacterSize(50);
        botao.setFillColor(Color::White); 
        botao.setOrigin(botao.getLocalBounds().width / 2, botao.getLocalBounds().height / 2);
        //setPosition para o meio da tela
        botao.setPosition((windowSize.x / 2.0f), (windowSize.y / 2.0f) - 100 + i * 100);
        botoesMenu.push_back(botao);
    }
    vector<string> opcoesDificuldade = {"Facil", "Normal", "Dificil"};
    for (size_t i = 0; i < opcoesDificuldade.size(); ++i) {
        Text botaoDificuldade;
        botaoDificuldade.setFont(font);
        botaoDificuldade.setString(opcoesDificuldade[i]);
        botaoDificuldade.setCharacterSize(50);
        botaoDificuldade.setFillColor(Color::White);
        botaoDificuldade.setOrigin(botaoDificuldade.getLocalBounds().width / 2, botaoDificuldade.getLocalBounds().height / 2);
        botaoDificuldade.setPosition(windowSize.x / 2.0f, (windowSize.y / 2.0f) - 100 + i * 100);
        botoesDificuldade.push_back(botaoDificuldade);
    }
}

void gerenciamentoTela::setarTextoGameOver(RenderWindow& window, const Font& font){
    textoGameOver.setFont(font);
    textoGameOver.setCharacterSize(50);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setFillColor(Color::Red);
    textoGameOver.setOrigin(textoGameOver.getLocalBounds().width / 2, textoGameOver.getLocalBounds().height / 2);
    textoGameOver.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    textoKills.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);
    textoKills.setFillColor(Color::Red);
    textoKills.setCharacterSize(30);
}

/**
 * @brief Gerencia os eventos de entrada do usuário para a tela atual do jogo.
 * 
 * Esta função lida com os eventos do mouse e teclado, alterando o estado do jogo e executando ações específicas
 * com base no estado atual da tela e nas interações do usuário. Dependendo do estado, pode lidar com eventos de 
 * clique do mouse para mudar o estado do jogo, posicionar o herói, disparar projéteis ou alterar a dificuldade do jogo.
 * 
 * @param window A janela do jogo onde os eventos estão sendo processados.
 * 
 * @details
 * - No estado `MENU`, a função verifica se o usuário está sobre um botão do menu e altera sua cor. 
 *   Quando um botão é clicado, o estado do jogo é alterado conforme o botão clicado:
 *   - Botão 0: Muda para o estado `JOGO`.
 *   - Botão 1: Muda para o estado `COOP` e cria um novo tanque.
 *   - Botão 2: Muda para o estado `DIFICULDADE`.
 * 
 * - No estado `JOGO`, a função permite que o usuário:
 *   - Posicione o herói com o botão direito do mouse.
 *   - Dispare projéteis com o botão Q.
 * 
 * - No estado `COOP`, além das ações do estado `JOGO`, o usuário pode:
 *   - Disparar projéteis com o botão esquerdo do mouse.
 *   - Trocar munição por vida base com a tecla R.
 * 
 * - No estado `DIFICULDADE`, a função verifica a posição do mouse sobre os botões de dificuldade e altera
 *   a dificuldade do jogo com base no botão clicado. Após selecionar a dificuldade, retorna ao estado `MENU`.
 */
void gerenciamentoTela::eventos(RenderWindow& window, const Vector2f& windowSize) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            musicaTema.stop();
            window.close();
        }
        if (estado == Estado::MENU) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            for (size_t i = 0; i < botoesMenu.size(); ++i) {
                if (botoesMenu[i].getGlobalBounds().contains(mousePos)) {
                    botoesMenu[i].setFillColor(Color::Yellow);  
                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        if (i == 0) {
                            estado = Estado::JOGO;  
                            escolhaMenu.play();
                        } else if (i == 1) {
                            escolhaMenu.play();
                            estado = Estado::COOP;  
                            tank = new Tank(100, "assets/images/characters/TankSup.png", fontGame, heroi, base);
                        } else if (i == 2) {
                            escolhaMenu.play();
                            estado = Estado::DIFICULDADE;
                        }
                    }
                } else {
                    botoesMenu[i].setFillColor(Color::White);  
                }
            }
        }else if(estado == Estado::JOGO) {
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                setHeroiPosition(window);
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
                if(heroi) {
                    Vector2i posicaoMouse = Mouse::getPosition(window);
                    Vector2f direcao(static_cast<float>(posicaoMouse.x) - heroi->getSprite().getPosition().x, static_cast<float>(posicaoMouse.y) - heroi->getSprite().getPosition().y);
                    heroi->atirar(direcao);
                    cout << "Atirou" << endl;
                }
            }
        }else if(estado == Estado::COOP){
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                setHeroiPosition(window);
            }
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if(heroi) {
                    Vector2i posicaoMouse = Mouse::getPosition(window);
                    Vector2f direcao(static_cast<float>(posicaoMouse.x) - heroi->getSprite().getPosition().x, static_cast<float>(posicaoMouse.y) - heroi->getSprite().getPosition().y);
                    heroi->atirar(direcao);
                    cout << "Atirou" << endl;
                }
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::R){
                    tank->trocarMunicaoPorVidaBase();
                
            }
        }else if(estado == Estado::DIFICULDADE){
             Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            for (size_t i = 0; i < botoesDificuldade.size(); ++i) {
                if (botoesDificuldade[i].getGlobalBounds().contains(mousePos)) {
                    botoesDificuldade[i].setFillColor(Color::Yellow);
                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        if (i == 0) {
                            escolhaMenu.play();
                            waveInimigo = SPAWN_FACIL;
                        } else if (i == 1) {
                            escolhaMenu.play();
                            waveInimigo = SPAWN_NORMAL;
                        } else if (i == 2) {
                            escolhaMenu.play();
                            waveInimigo = SPAWN_DIFICIL;
                        }
                        
                        estado = Estado::MENU; 
                    }
                } else {
                    botoesDificuldade[i].setFillColor(Color::White);
                }
            }
        }else if(estado == Estado::GAMEOVER || estado == Estado::VITORIA){
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                estado = Estado::MENU;
                resetarJogo(windowSize);
                musicaGameOver.stop();
                musicaTema.play();
            }
        }
    }
}

/**
 * @brief Reseta os valores do jogo para o estado inicial.
 * 
 * Esta função reseta os valores do jogo para o estado inicial, zerando a vida do herói, a vida da base, a quantidade de inimigos
 * 
 */
void gerenciamentoTela::resetarJogo(const Vector2f& windowSize){
    heroi->setVida(100);
    heroi->setMunicao();
    heroi->getSprite().setPosition(400, 300);
    inimigos.clear();
    runners.clear();
    tanks.clear();
    projeteisInimigos.clear();
    drops.clear();
    projeteis.clear();
    regenerarVidaBase = false;
    upLimite = 0;
    base->setVidaBase(100);
    Kills = 0;
    setKills();
    textoKills.setPosition(windowSize.x / 2.0f, 20);
    textoKills.setFillColor(Color::White);
    textoKills.setCharacterSize(20);
    
}

/**
 * @brief Gerencia a renderização das kills na tela.
 * 
 * Esta função renderiza o texto das kills na tela, exibindo a quantidade de inimigos eliminados pelo jogador.
 * 
 */
void gerenciamentoTela::setKills(){
    textoKills.setString("kills:" + to_string(Kills));
}

/**
 * @brief Gerencia o fim do jogo.
 * 
 * Esta função verifica se o jogo chegou ao fim, alterando o estado do jogo para GAMEOVER caso o herói ou a base
 * tenham sido destruídos ou o tempo de jogo tenha se esgotado.
 * 
 */
void gerenciamentoTela::setFimDeJogo(){
    if((heroi->getVida() <= 0) || (base->getVidaBase() <= 0 || spawRelogio.getElapsedTime() > seconds(60))){
        if(estado == Estado::COOP){
            if(tank){
                tank->setVida(100);
                tank->getSprite().setPosition(350, 300);
            }
        }
        estado = Estado::GAMEOVER;
        
        if (musicaTema.getStatus() == Music::Playing) {
                musicaTema.stop();
            }

        if (musicaGameOver.getStatus() != Music::Playing) {
            musicaGameOver.play();
        }
    }
    if(estado == Estado::COOP && tank && tank->getVida() <= 0){
        estado = Estado::GAMEOVER;
        tank->setVida(100);
        tank->getSprite().setPosition(350, 300);
        if (musicaTema.getStatus() == Music::Playing) {
                musicaTema.stop();
            }

        if (musicaGameOver.getStatus() != Music::Playing) {
            musicaGameOver.play();
        }
    }

    
}

/**
 * @brief Ajuda a ajustar a escala do fundo da tela.
 * 
 * Esta função ajusta a escala do fundo da tela com base no tamanho da janela do jogo.
 * 
 * @param window A janela do jogo.
 * @param sprite O sprite do fundo da tela.
 *
 */
void gerenciamentoTela::setBackgroundScale(RenderWindow& window, Sprite& sprite) {
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
}

/**
 * @brief Define a posição do herói na tela.
 * 
 * Esta função define a posição do herói na tela com base na posição do mouse.
 * 
 * @param window A janela do jogo.
 *
 */
void gerenciamentoTela::setHeroiPosition(RenderWindow& window) {
   Vector2i mousePosition = Mouse::getPosition(window);
   Vector2f novaPosicao(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
   if(heroi){
         heroi->definirPosicao(novaPosicao);
   }
}

/**
 * @brief Retorna uma posição aleatória na tela.
 * 
 * Esta função retorna uma posição aleatória na tela com base no tamanho da janela.
 * 
 * @param windowSize O tamanho da janela do jogo.
 * 
 * @return A posição aleatória na tela.
 *
 */
Vector2f gerenciamentoTela::getPosicaoRandom(const Vector2u& windowSize) {
    //Offset para evitar que o inimigo apareça fora da tela
    const int offset = 0;
    int direcao = rand() % (2);
    int sentido = rand() % (2);
    if(direcao == 0) {
        int x = rand() % (windowSize.x + offset);
        int y;
        if(sentido == 0) {
            y = -offset;
        }else{
            y = windowSize.y + offset;
        }
        return Vector2f(x, y);
    }
    else{
        int y = rand() % (windowSize.y + offset);
        int x;
        if(sentido == 0) {
            x = -offset;
        }else{
            x = windowSize.x + offset;
        }
        return Vector2f(x, y);
    }
}

/**
 * @brief Retorna um valor aleatório para a chance de drop.
 */
int gerenciamentoTela::getRandomChanceDrop(){
    int chance = rand() % 3;
    return chance;
}

/**
 * @brief Retorna um valor aleatório para o tipo de inimigo.
 */
int gerenciamentoTela::getRandomInimigo(){
    int inimigo = rand() % 3;
    return inimigo;
}

/**
 * @brief calcula a distância entre duas posições.
 * 
 * Esta função calcula a distância entre duas posições no plano cartesiano.
 * 
 * @param posicao1  
 * @param posicao2 
 * @return float 
 */
float calcularDistancia(const Vector2f& posicao1, const Vector2f& posicao2) {
    return sqrt(pow(posicao1.x - posicao2.x, 2) + pow(posicao1.y - posicao2.y, 2));
}

/**
 * @brief Atualiza os drops e remove os que já passaram do tempo de desaparecer
 * 
 * @param drops vetor de drops
 */
bool gerenciamentoTela::atualizarDrops(RenderWindow& window){
    for (auto it = drops.begin(); it != drops.end();) {
        if (it->verificarTempoDeDesaparecer()) {
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

/**
 * @brief Atualiza o estado do jogo e os objetos presentes na tela.
 * 
 * Esta função é responsável por atualizar a posição dos personagens e inimigos, verificar colisões, 
 * processar a lógica dos projéteis e gerar novos inimigos com base no tempo decorrido. Ela lida com 
 * diferentes estados do jogo, como `JOGO` e `COOP`, e realiza ações específicas dependendo do estado atual.
 * 
 * @param window A janela do jogo onde as atualizações são aplicadas.
 * 
 * @details
 * - No estado `JOGO` e `COOP`, a função realiza as seguintes ações:
 *   - Atualiza o tempo decorrido e verifica a regeneração da vida da base.
 *   - Atualiza o herói e seus projéteis.
 *   - Atualiza os inimigos e seus projéteis, verificando colisões com o herói, o tanque aliado (se aplicável) e a base.
 *   - Dependendo do estado, os inimigos podem atirar no herói ou no tanque aliado.
 *   - Atualiza e remove os drops, recuperando munição e vida conforme o tipo de drop.
 *   - Atualiza a lista de projéteis inimigos e verifica colisões com a janela e com outros objetos, removendo projéteis e inimigos quando necessário.
 *   - Verifica a colisão do projétil com inimigos, tanques e corredores, gerando drops conforme o tipo de inimigo atingido.
 *   - Verifica a colisão dos inimigos com a base e remove-os se necessário.
 *   - Atualiza a posição dos inimigos e verifica se colidem com a base, removendo-os se a colisão ocorrer.
 *   - Realiza o spawn de novos inimigos com base em intervalos de tempo definidos e em condições específicas.
 * 
 * - No estado `COOP`, além das ações descritas acima, o tanque aliado também é atualizado e verifica colisões com drops e projéteis.
 * 
 * - A função também realiza a lógica de spawn de novos inimigos, garantindo que a posição dos inimigos seja válida e não se sobreponha a outras entidades.
 * 
 * - Os inimigos são spawnados de forma aleatória com base em uma chance definida e em um tempo específico.
 */
void gerenciamentoTela::atualizar(RenderWindow& window) {
      
    

    if (estado == Estado::JOGO || estado == Estado::COOP) {
        setFimDeJogo();
        float deltaTime = relogio.restart().asSeconds();
        Time tempoDecorrido = spawRelogio.getElapsedTime();
        if(regenerarVidaBase){
            base->baseUpRegenerarVida();
        }
        
        if (heroi) {
            heroi->mover();
            heroi->atualizarProjeteis(deltaTime);
            
            
            for (auto& inimigo : inimigos) {
                
                inimigo->atualizarProjeteis(deltaTime, window);
                if(estado == Estado::COOP && tank){
                    tank->verificarColisao(inimigo->getSprite());
                    
                }
                base->verificarColisao(inimigo->getSprite());
                

                //Verifica em quem o inimigo vai atirar
                Vector2f direcaoHeroiInimigo = heroi->getSprite().getPosition() - inimigo->getSprite().getPosition();

                
                if(estado == Estado::COOP && tank){
                    Vector2f direcaoTankAliadoInimigo = tank->getSprite().getPosition() - inimigo->getSprite().getPosition();
                    float distanciaTankAliadoInimigo = calcularDistancia(inimigo->getSprite().getPosition(), tank->getSprite().getPosition());
                    float distanciaHeroiInimigo = calcularDistancia(inimigo->getSprite().getPosition(), heroi->getSprite().getPosition());
                    inimigo->atirarCOOP(direcaoHeroiInimigo, direcaoTankAliadoInimigo, distanciaHeroiInimigo, distanciaTankAliadoInimigo);
                }else{
                    inimigo->atirar(direcaoHeroiInimigo);
                    
                }
                

                for(auto& projetil : inimigo->getProjeteis()){
                    projeteisInimigos.push_back(projetil);
                }
                inimigo->getProjeteis().clear();
            }

            for (auto& inimigoTank : tanks) {
                inimigoTank->atualizarProjeteis(deltaTime, window);
                if(estado == Estado::COOP && tank){
                    tank->verificarColisao(inimigoTank->getSprite());
                }
                base->verificarColisao(inimigoTank->getSprite());

                //Verifica em quem o inimigo vai atirar
                Vector2f direcao = heroi->getSprite().getPosition() - inimigoTank->getSprite().getPosition();
                if(estado == Estado::COOP && tank){
                    Vector2f direcaoTank = tank->getSprite().getPosition() - inimigoTank->getSprite().getPosition();
                    float distanciaTank = calcularDistancia(inimigoTank->getSprite().getPosition(), tank->getSprite().getPosition());
                    float distanciaHeroi = calcularDistancia(inimigoTank->getSprite().getPosition(), heroi->getSprite().getPosition());
                    inimigoTank->atirarCOOP(direcao, direcaoTank, distanciaHeroi, distanciaTank);
                }else{
                    inimigoTank->atirar(direcao);                    
                }
                for(auto& projetil : inimigoTank->getProjeteis()){
                        projeteisInimigos.push_back(projetil);
                    }
                    inimigoTank->getProjeteis().clear();
            }
        }
        if (estado == Estado::COOP && tank) {
            tank->mover();  
            
        }


        for(auto dropIt = drops.begin(); dropIt != drops.end();) {
            bool dropRemovido = false;
            if(atualizarDrops(window)){
                dropIt = drops.erase(dropIt);
                dropRemovido = true;
            }
            if (!dropRemovido && heroi->verificarColisaoDrop(dropIt->getSprite())) {
                if (dropIt->getTipo() == 1) {
                    heroi->RecuperarMunicao();
                } else if (dropIt->getTipo() == 0) {
                    heroi->RecuperarVida();
                    if (estado == Estado::COOP && tank) {
                        tank->RecuperarVida();
                    }
                } else if (dropIt->getTipo() == 2) {
                    if (upLimite < 2) {
                        if (upLimite == 0) {
                            base->aumentarVidaBase();
                        } else if (upLimite == 1) {
                            regenerarVidaBase = true;
                        }
                        upLimite++;
                    }
                }
                dropIt = drops.erase(dropIt);
                dropRemovido = true;
            }

            if (!dropRemovido && estado == Estado::COOP && tank && tank->verificarColisaoDrop(dropIt->getSprite())) {
                if (dropIt->getTipo() == 1) {
                    heroi->RecuperarMunicao();
                } else if (dropIt->getTipo() == 0) {
                    tank->RecuperarVida();
                    heroi->RecuperarVida();
                } else if (dropIt->getTipo() == 2) {
                    if (upLimite < 2) {
                        if (upLimite == 0) {
                            base->aumentarVidaBase();
                        } else if (upLimite == 1) {
                            regenerarVidaBase = true;
                        }
                        upLimite++;
                    }
                }
                dropIt = drops.erase(dropIt);
                dropRemovido = true;
            }

            if (!dropRemovido) {
                ++dropIt;
            }
        }
        atualizarProjeteisInimigos(deltaTime, window);

        for(auto inimigoIt = inimigos.begin(); inimigoIt != inimigos.end();) {
            if(heroi->verificarColisao((*inimigoIt)->getSprite())) {
                inimigoIt = inimigos.erase(inimigoIt);
            }else if(estado == Estado::COOP && tank && tank->verificarColisao((*inimigoIt)->getSprite())){
                inimigoIt = inimigos.erase(inimigoIt);
            }else{
                ++inimigoIt;
            }
        }

        for(auto tankIt = tanks.begin(); tankIt != tanks.end();) {
            if(heroi->verificarColisao((*tankIt)->getSprite())) {
                heroi->TomarDano();
                tankIt = tanks.erase(tankIt);
            }else if(estado == Estado::COOP && tank && tank->verificarColisao((*tankIt)->getSprite())){
                tankIt = tanks.erase(tankIt);
                tank->TomarDano();
            }else {
                ++tankIt;
            }
        }

        for(auto runnerIt = runners.begin(); runnerIt != runners.end();) {
            if(heroi->verificarColisao((*runnerIt)->getSprite())) {
                runnerIt = runners.erase(runnerIt);
            }else if(estado == Estado::COOP && tank && tank->verificarColisao((*runnerIt)->getSprite())){
                runnerIt = runners.erase(runnerIt);
            }else {
                ++runnerIt;
            }
        }

        //Verifica colisão do projétil com a janela e com o inimigo
        auto& projeteis = heroi->getProjeteis();
        
        for (auto it = projeteis.begin(); it != projeteis.end();) {
            bool projetilRemovido = false;

            if (it->verificarColisaoJanela(window)) {
                it = projeteis.erase(it);
                projetilRemovido = true;
            }
            if (!projetilRemovido){
                
                for(auto tankIt = tanks.begin(); tankIt != tanks.end();) {
                    if ((*tankIt)->verificarColisao((it)->getSprite())) {
                        cout << "Tank atingido" << endl;
                        (*tankIt)->tomarDano();
                        if((*tankIt)->getVidaInimigo() <= 0){
                            tankIt = tanks.erase(tankIt);
                            Kills++;
                            setKills();
                            if(int chance = rand() % 3 == 0){
                                if(getRandomChanceDrop() == 2){
                                    if(upLimite < 2){
                                        Drop drop(spriteDrop2, (*tankIt)->getPosicao(), heroi, 2);
                                        drop.setPosicao((*tankIt)->getPosicao());
                                        drops.push_back(drop);
                                    }
                                }    
                            }
                        }
                        it = projeteis.erase(it);
                        projetilRemovido = true;
                        break;
                    } else {
                        ++tankIt;
                    }
                }
                for (auto runnerIt = runners.begin(); runnerIt != runners.end();) {
                    if ((*runnerIt)->verificarColisao((it)->getSprite())) {
                        cout << "Runner atingido" << endl;                       
                        if(getRandomChanceDrop() == 1){
                            Drop drop(spriteDrop, (*runnerIt)->getPosicao(), heroi, 1);
                            drop.setPosicao((*runnerIt)->getPosicao());
                            drops.push_back(drop);                          
                        }
                        runnerIt = runners.erase(runnerIt);                       
                        it = projeteis.erase(it);
                        Kills++;
                        setKills();
                        projetilRemovido = true;
                        break;
                    } else {
                        ++runnerIt;
                    }
                }
                for (auto inimigoIt = inimigos.begin(); inimigoIt != inimigos.end();) {
                    if ((*inimigoIt)->verificarColisao(it->getSprite())) {
                        if(getRandomChanceDrop() == 1){
                            Drop drop(spriteDrop, (*inimigoIt)->getPosicao(), heroi, 1);
                            drop.setPosicao((*inimigoIt)->getPosicao());
                            drops.push_back(drop);                          
                        }else if(getRandomChanceDrop() == 0){
                            Drop drop(spriteDrop1, (*inimigoIt)->getPosicao(), heroi, 0);
                            drop.setPosicao((*inimigoIt)->getPosicao());
                            drops.push_back(drop);                          
                        }
                        inimigoIt = inimigos.erase(inimigoIt);
                        it = projeteis.erase(it);
                        Kills++;
                        cout << "Kills: " << Kills << endl; 
                        setKills();
                        projetilRemovido = true;
                        break;
                    } else {
                        ++inimigoIt;
                    }
                }
            }
            if (!projetilRemovido) {
                ++it;
            }
        }

        //Verifica colisão do inimigo com a base
        if (base) {
            for (auto it = inimigos.begin(); it != inimigos.end();) {
                base->verificarColisao((*it)->getSprite());
                if(base->verificarColisao((*it)->getSprite())){ 
                    it = inimigos.erase(it);
                }else{
                    ++it;
                }
            }
        }

        for (auto it = inimigos.begin(); it != inimigos.end();) {
            (*it)->mover();
            base->verificarColisao((*it)->getSprite());
            if (base && (*it)->verificarColisao(base->getSprite())) {
                it = inimigos.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = runners.begin(); it != runners.end();) {
            (*it)->mover();
            base->verificarColisao((*it)->getSprite());
            if (base && (*it)->verificarColisao(base->getSprite())) {
                it = runners.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = tanks.begin(); it != tanks.end();) {
            (*it)->mover();
            if(base->verificarColisao((*it)->getSprite())){
                base->tomarDanoTank();
            }
            
            if (base && (*it)->verificarColisao(base->getSprite())) {
                it = tanks.erase(it);
            } else {
                ++it;
            }
        }

        //TODO: Implementar a lógica de spawn de inimigos em waves
        if(waveRelogio.getElapsedTime() >= waveInimigo) { 

            if (spawRelogio.getElapsedTime() >= spawnInimigo) {
                Vector2f posicao;
                bool posicaoValida = false;
                const float distanciaMinima = 50.0f;

                while (!posicaoValida) {
                    posicao = getPosicaoRandom(Vector2u(800, 600));
                    posicaoValida = true;

                    for (const auto& inimigo : inimigos) {
                        if (calcularDistancia(posicao, (*inimigo).getPosicao()) < distanciaMinima) {
                            posicaoValida = false;
                            break;
                        }
                    }
                }        
                if(getRandomInimigo() == 1){
                    Runner* runner = new Runner("assets/images/characters/runner.png");
                    if(runner->isTextureLoaded()){
                        runner->setPosicao(posicao);
                        runners.push_back(runner);
                        cout  << "Runner spawnado" << endl;
                    }else {
                        delete runner;
                    }
                    spawRelogio.restart();
                }else if(getRandomInimigo() == 0){
                    Inimigo* inimigo = new Inimigo("assets/images/characters/enemy.png");
                    if (inimigo->isTextureLoaded()) {
                        inimigo->setPosicao(posicao);
                        inimigos.push_back(inimigo);
                        cout  << "Inimigo spawnado" << endl;

                    } else {
                        delete inimigo;
                    }
                    spawRelogio.restart();
                }else if(getRandomInimigo() == 2){
                    if(rand() % 2 == 0){
                        InimigoTank* inimigoTank = new InimigoTank("assets/images/characters/enemy_tank.png");
                        if (inimigoTank->isTextureLoaded()) {
                            inimigoTank->setPosicao(posicao);
                            tanks.push_back(inimigoTank);
                            cout << tanks.size() << endl;
                            cout  << "Inimigo Tank spawnado" << endl;

                        } else {
                            delete inimigoTank;
                        }
                        spawRelogio.restart();
                    }
                }
            }
            waveInimigos();
            waveRelogio.restart();
        }
    }
}

/**
 * @brief Gerencia o spawn de inimigos em waves.
 * 
 * Esta função gerencia o spawn de inimigos em waves, ajustando o tempo de spawn de inimigos com base no tempo decorrido.
 * 
 */
void gerenciamentoTela::waveInimigos(){
    waveInimigo -= seconds(0.5);
    if(waveInimigo <= seconds(1)){
        waveInimigo = seconds(1);
    }
}

/**
 * @brief Atualiza a posição dos projéteis inimigos na tela.
 * 
 * Esta função atualiza a posição dos projéteis inimigos na tela, verificando colisões com a janela e com outros objetos.
 * 
 * @param deltaTime O tempo decorrido desde a última atualização.
 * @param window A janela do jogo onde as atualizações são aplicadas.
 * 
 * @details
 * - A função atualiza a posição dos projéteis inimigos e verifica colisões com a janela, removendo os projéteis se necessário.
 * - Verifica colisões dos projéteis inimigos com o herói, a base e os inimigos, removendo os projéteis e os inimigos atingidos.
 * - Verifica colisões dos projéteis inimigos com o tanque aliado (se aplicável), removendo os projéteis e o tanque se atingidos.
 * 
 */
void gerenciamentoTela::atualizarProjeteisInimigos(float deltaTime, RenderWindow& window) {
    for (auto it = projeteisInimigos.begin(); it != projeteisInimigos.end();) {
        it->moverInimigo(deltaTime);
        bool projetilRemovido = false;
        if (it->verificarColisaoJanela(window)) {
            it = projeteisInimigos.erase(it);
            projetilRemovido = true;
        } else {
            if (heroi->verificarColisao(it->getSprite())) {
                it = projeteisInimigos.erase(it);
                projetilRemovido = true;
            } else if (base && base->verificarColisao(it->getSprite())) {
                it = projeteisInimigos.erase(it);
                projetilRemovido = true;
            }else if(estado == Estado::COOP && tank && tank->verificarColisao(it->getSprite())){
                it = projeteisInimigos.erase(it);
                projetilRemovido = true;

            } 
            
            else {
                for (auto inimigoIt = inimigos.begin(); inimigoIt != inimigos.end();) {
                    if ((*inimigoIt)->verificarColisao(it->getSprite()) && it->getOwner() != *inimigoIt) {
                        inimigoIt = inimigos.erase(inimigoIt);
                        it = projeteisInimigos.erase(it);
                        projetilRemovido = true;
                        break;
                    } else {
                        ++inimigoIt;
                    }
                }
                for (auto tankIt = tanks.begin(); tankIt != tanks.end();) {
                    if ((*tankIt)->verificarColisao(it->getSprite()) && it->getOwner() != *tankIt) {
                        tankIt = tanks.erase(tankIt);
                        it = projeteisInimigos.erase(it);
                        projetilRemovido = true;
                        break;
                    } else {
                        ++tankIt;
                    }
                }
            }
        }
        if (!projetilRemovido) {
            ++it;
        }
    }
}

/**
 * @brief Atualiza a posição dos drops na tela.
 * 
 * @param window A janela do jogo onde as atualizações são aplicadas.
 * 
 */
void gerenciamentoTela::atualizarDrop(RenderWindow& window) {
    for(auto& drop : drops) {
        drop.renderizar(window);
    }
}

/**
 * @brief Renderiza os objetos na tela.
 * 
 * Esta função renderiza os objetos na tela, como o fundo, os botões do menu, os inimigos, os projéteis e os drops.
 * 
 * @param window A janela do jogo onde os objetos são renderizados.
 * 
 * @details
 * - No estado `MENU`, a função renderiza o fundo e os botões do menu.
 * - No estado `DIFICULDADE`, a função renderiza o fundo e os botões de dificuldade.
 * - No estado `JOGO` e `COOP`, a função renderiza o fundo, o herói, a base, os inimigos, os projéteis e os drops.
 * - No estado `GAMEOVER`, a função renderiza um círculo vermelho na tela.
 * - No estado `COOP`, a função renderiza o tanque aliado.
 */
void gerenciamentoTela::renderizar(RenderWindow& window) {
    window.clear();

    if(estado == Estado::MENU) { 
        setBackgroundScale(window, backgroundSprite_menu);
        window.draw(backgroundSprite_menu);
        for (const auto& botao : botoesMenu) {
            window.draw(botao);
        }
    }else if (estado == Estado::DIFICULDADE) {
        setBackgroundScale(window, backgroundSprite_menu);
        window.draw(backgroundSprite_menu);
        for (const auto& botao : botoesDificuldade) {
            window.draw(botao);
        }
    } else if(estado == Estado::JOGO || estado == Estado::COOP) {
        setBackgroundScale(window, backgroundSprite);
        window.draw(backgroundSprite);
        if(base) {
            base->renderizar(window);
        }
        window.draw(textoKills);   
        if(heroi != nullptr) {
            heroi->renderizar(window);
        }
        if(estado == Estado::COOP && tank){
            tank->renderizar(window);
        }
        for (auto& inimigo : inimigos) {
            (*inimigo).renderizar(window);
        }
        for (auto& runner : runners) {
            (*runner).renderizar(window);
        }
        for (auto& tank : tanks) {
            (*tank).renderizar(window);
        }
        renderizarProjeteisInimigos(window);
        atualizarDrop(window);
    }else if(estado == Estado::GAMEOVER) {
        setarTextoGameOver(window, font);
        window.draw(backgroundSprite_menu);
        window.draw(textoGameOver);     
        window.draw(textoKills);
    }else if(estado == Estado::COOP){
        tank->renderizar(window);
    }
    window.display();
}

/**
 * @brief Renderiza os projéteis inimigos na tela.
 * 
 * Esta função renderiza os projéteis inimigos na tela, exibindo os projéteis disparados pelos inimigos.
 * 
 * @param window A janela do jogo onde os projéteis são renderizados.
 * 
 */
void gerenciamentoTela::renderizarProjeteisInimigos(RenderWindow& window) {
    for (auto& projetil : projeteisInimigos) {
        projetil.renderizar(window);
    }
}