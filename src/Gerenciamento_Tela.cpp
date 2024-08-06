#include "../include/Gerenciamento_Tela.hpp"
#include <iostream>
#include <cmath>
#include "../include/heroi.hpp"
#include "../include/base.hpp"
#include "../include/projeteis.hpp"
#include "../include/inimigo.hpp"
#include "../include/drops.hpp"
using namespace std;
using namespace sf;


//Carrega a imagem de fundo e a música
gerenciamentoTela::gerenciamentoTela(const string& backgroundFile, const string& backgroundMenuFile,const string& musicFile, Heroi *heroi, Base *base, const Vector2f& windowSize) 
: heroi(heroi), base(base), estado(Estado::MENU), spawInimigo(seconds(2)), intervaloDisparo(seconds(1)) {

    if(!background.loadFromFile(backgroundFile)) {
        cout << "Erro ao carregar imagem de fundo" << endl;
    }
    if(!font.loadFromFile("assets/fonts/fonts.ttf")) {
        cerr << "Erro ao carregar a fonte" << endl;
        exit(1);
    }
    if(!background_menu.loadFromFile(backgroundMenuFile)) {
        cout << "Erro ao carregar imagem de fundo do menu" << endl;
    }
    if(!texturaProjetil.loadFromFile("assets/images/background/bullet1.png")) {
        cout << "Erro ao carregar textura do projetil" << endl;
    }
    if(!texturaDrop.loadFromFile("assets/images/background/drop.png")) {
        cout << "Erro ao carregar textura do drop" << endl;
    }
    if(!music.openFromFile(musicFile)) {
        cout << "Erro ao carregar música" << endl;
    }else {
        music.setLoop(true);
        music.play();
        
    }
    //Configuração do drop
    spriteDrop.setTexture(texturaDrop);

    //Configuração do projétil
    backgroundSprite_projetil.setTexture(texturaProjetil);

    //Seta a imagem de fundo
    backgroundSprite.setTexture(background);
    backgroundSprite_menu.setTexture(background_menu);

    //Configuração do texto do menu
    textoMenu.setFont(font);
    textoMenu.setCharacterSize(30);
    textoMenu.setFillColor(Color::White);
    textoMenu.setString("Pressione Enter para iniciar o jogo");
    FloatRect textRect = textoMenu.getLocalBounds();
    textoMenu.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    textoMenu.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    //Inicia o relógio
    spawRelogio.restart();
}

//Verifica eventos do mouse
void gerenciamentoTela::eventos(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if(estado == Estado::MENU) {
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                estado = Estado::JOGO;
            }
        }else if(estado == Estado::JOGO) {
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                setHeroiPosition(window);
            }
        }
        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
            if(heroi) {
                Vector2i posicaoMouse = Mouse::getPosition(window);
                Vector2f direcao(static_cast<float>(posicaoMouse.x) - heroi->getSprite().getPosition().x, static_cast<float>(posicaoMouse.y) - heroi->getSprite().getPosition().y);
                heroi->atirar(direcao);
                cout << "Atirou" << endl;
            }
        }
    }
}

//Ajusta o tamanho da imagem de fundo
void gerenciamentoTela::setBackgroundScale(RenderWindow& window, Sprite& sprite) {
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    //backgroundSprite_menu.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
}

//Ajusta a posição do herói
void gerenciamentoTela::setHeroiPosition(RenderWindow& window) {
   Vector2i mousePosition = Mouse::getPosition(window);
   Vector2f novaPosicao(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
   if(heroi){
         heroi->definirPosicao(novaPosicao);
   }
}

//Gera uma posição aleatória para o inimigo
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

int gerenciamentoTela::getRandomChanceDrop(){
    int chance = rand() % 2;
    return chance;
}

int gerenciamentoTela::getRandomTipoDrop(){
    int tipo = rand() % 2;
    return tipo;
}

//Calcula a distância entre duas posições
float calcularDistancia(const Vector2f& posicao1, const Vector2f& posicao2) {
    return sqrt(pow(posicao1.x - posicao2.x, 2) + pow(posicao1.y - posicao2.y, 2));
}

//Atualiza as informações do jogo
void gerenciamentoTela::atualizar(RenderWindow& window) {
    if (estado == Estado::JOGO) {
        float deltaTime = relogio.restart().asSeconds();
        Time tempoDecorrido = spawRelogio.getElapsedTime();
        
        
        
        if (heroi) {
            heroi->mover();
            heroi->atualizarProjeteis(deltaTime);

            
            
            for (auto& inimigo : inimigos) {
                inimigo.atualizarProjeteis(deltaTime, window);
                heroi->verificarColisao(inimigo.getSprite());
                
                base->verificarColisao(inimigo.getSprite());
                Vector2f direcao = heroi->getSprite().getPosition() - inimigo.getSprite().getPosition();
                inimigo.atirar(direcao); 
                /* atirarInimigo(direcao, inimigo.getSprite()); */

                for(auto& projetil : inimigo.getProjeteis()){
                    projeteisInimigos.push_back(projetil);
                }
                inimigo.getProjeteis().clear();
            }
        }

        for(auto& drop : drops) {
            if(heroi->verificarColisaoDrop(drop.getSprite())) {
                if(getRandomTipoDrop() == 1){
                    heroi->RecuperarMunicao();
                }else{
                heroi->RecuperarVida();
            }
                drop.setPosicao(Vector2f(-1000, -1000));
            }
        }

        atualizarProjeteisInimigos(deltaTime, window);
        
        for(auto& inimigo : inimigos) {
            auto& projeteisInimigo = inimigo.getProjeteis();
            for(auto it = projeteisInimigo.begin(); it != projeteisInimigo.end();) {
                if(it->verificarColisao(heroi->getSprite())) {
                    it = projeteisInimigo.erase(it);
                    heroi->TomarDano();
                }else {
                    ++it;
                }
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
                for (auto inimigoIt = inimigos.begin(); inimigoIt != inimigos.end();) {
                    if (inimigoIt->verificarColisao(it->getSprite())) {
                        if(getRandomChanceDrop() == 1){
                            Drop drop(spriteDrop, inimigoIt->getPosicao(), heroi);
                            drop.setPosicao(inimigoIt->getPosicao());
                            drops.push_back(drop);
                        }
                        inimigoIt = inimigos.erase(inimigoIt);
                        it = projeteis.erase(it);
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
                base->verificarColisao(it->getSprite());
                if(base->verificarColisao(it->getSprite())){ 
                    cout << "Inimigo colidiu com a base!" << endl;
                    it = inimigos.erase(it);
                }else{
                    ++it;
                }
            }
        }

        for (auto it = inimigos.begin(); it != inimigos.end();) {
            it->mover();
            base->verificarColisao(it->getSprite());
            if (base && it->verificarColisao(base->getSprite())) {
                it = inimigos.erase(it);
            } else {
                ++it;
            }
        }

        //TODO: Implementar a lógica de spawn de inimigos em waves
        if (spawRelogio.getElapsedTime() >= spawInimigo) {
            Vector2f posicao;
            bool posicaoValida = false;
            const float distanciaMinima = 50.0f;

            while (!posicaoValida) {
                posicao = getPosicaoRandom(Vector2u(800, 600));
                posicaoValida = true;

                for (const auto& inimigo : inimigos) {
                    if (calcularDistancia(posicao, inimigo.getPosicao()) < distanciaMinima) {
                        posicaoValida = false;
                        break;
                    }
                }
            }

            Inimigo* inimigo = new Inimigo("assets/images/characters/enemy.png");
            if (inimigo->isTextureLoaded()) {
                inimigo->setPosicao(posicao);
                inimigos.push_back(*inimigo);

            } else {
                delete inimigo;
            }
            spawRelogio.restart();
        }
    }
}

void gerenciamentoTela::atualizarProjeteisInimigos(float deltaTime, RenderWindow& window) {
    for (auto it = projeteisInimigos.begin(); it != projeteisInimigos.end();) {
        it->moverInimigo(deltaTime);
        if (it->verificarColisaoJanela(window)) {
            it = projeteisInimigos.erase(it);
        } else {
            if (heroi->verificarColisao(it->getSprite())) {
                heroi->TomarDano();
                it = projeteisInimigos.erase(it);
            }else if(base && base->verificarColisao(it->getSprite())){
                it = projeteisInimigos.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void gerenciamentoTela::atualizarDrop(RenderWindow& window) {
    for(auto& drop : drops) {
        drop.renderizar(window);
    }
}

//Renderiza a imagem de fundo e os sprites
void gerenciamentoTela::renderizar(RenderWindow& window) {
    window.clear();

    if(estado == Estado::MENU) {
        setBackgroundScale(window, backgroundSprite_menu);
        window.draw(backgroundSprite_menu);
        window.draw(textoMenu);
    }else if(estado == Estado::JOGO) {
        setBackgroundScale(window, backgroundSprite);
        window.draw(backgroundSprite);
        
        if(base) {
            base->renderizar(window);
        }
        if(heroi != nullptr) {
            heroi->renderizar(window);
        }
        for (auto& inimigo : inimigos) {
            inimigo.renderizar(window);
        }
        renderizarProjeteisInimigos(window);
        atualizarDrop(window);
        
        
    }
    window.display();
}

void gerenciamentoTela::renderizarProjeteisInimigos(RenderWindow& window) {
    for (auto& projetil : projeteisInimigos) {
        projetil.renderizar(window);
    }
}