#include "Gerenciamento_Tela.hpp"
#include <iostream>
#include <cmath>
#include "heroi.hpp"
#include "base.hpp"
#include "inimigo.hpp"
using namespace std;
using namespace sf;


//Carrega a imagem de fundo e a música
gerenciamentoTela::gerenciamentoTela(const string& backgroundFile, const string& backgroundMenuFile,const string& musicFile, Heroi *heroi, Base *base, const Vector2f& windowSize) 
: heroi(heroi), base(base), estado(Estado::MENU), spawInimigo(seconds(2)) {
    
    if(!background.loadFromFile(backgroundFile)) {
        cout << "Erro ao carregar imagem de fundo" << endl;
    }
    if(!font.loadFromFile("imagens/fonts/fonts.ttf")) {
        cerr << "Erro ao carregar a fonte" << endl;
        exit(1);
    }
    if(!background_menu.loadFromFile(backgroundMenuFile)) {
        cout << "Erro ao carregar imagem de fundo do menu" << endl;
    }
    if(!music.openFromFile(musicFile)) {
        cout << "Erro ao carregar música" << endl;
    }else {
        music.setLoop(true);
        music.play();
        
    }
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
    int x = rand() % (windowSize.x + 200);
    int y = rand() % (windowSize.y + 200);
    return Vector2f(x, y);
}

float calcularDistancia(const Vector2f& posicao1, const Vector2f& posicao2) {
    return sqrt(pow(posicao1.x - posicao2.x, 2) + pow(posicao1.y - posicao2.y, 2));
}

//Atualiza a posição do herói e do inimigo
void gerenciamentoTela::atualizar() {
    if(estado == Estado::JOGO) {
        if(heroi){
            heroi->mover();
            for (auto& inimigo : inimigos) {
                heroi->verificarColisao(inimigo.getSprite());
            }
        }
        if(base) {
            //Aqui implemente a verificação de colisão do sprite com a base
            //heroi usado para testar, posteriormente substituir por progeteis
            base->verificarColisao(heroi->getSprite());
        }
        if(spawRelogio.getElapsedTime() >= spawInimigo) {
            Vector2f posicao;
            bool posicaoValida = false;
            const float distanciaMinima = 50.0f;

            while(!posicaoValida){
                posicao = getPosicaoRandom(Vector2u(800, 600));
                posicaoValida = true;

                for(const auto& inimigo : inimigos) {
                    if(calcularDistancia(posicao, inimigo.getPosicao()) < distanciaMinima) {
                        posicaoValida = false;
                        break;
                    }
                }

            }
            
            Inimigo* inimigo = new Inimigo("imagens/alien_0.png");
            if(inimigo->isTextureLoaded()) {
                inimigo->setPosicao(posicao);
                inimigos.push_back(*inimigo);
            }else{
                delete inimigo;
            }
            spawRelogio.restart();
        }
    }
}

//Renderiza a imagem de fundo e o herói
void gerenciamentoTela::renderizar(RenderWindow& window) {
    window.clear();

    if(estado == Estado::MENU) {
        setBackgroundScale(window, backgroundSprite_menu);
        window.draw(backgroundSprite_menu);
        window.draw(textoMenu);
    }else if(estado == Estado::JOGO) {
        setBackgroundScale(window, backgroundSprite);
        window.draw(backgroundSprite);
        if(heroi != nullptr) {
            heroi->renderizar(window);
        }
        
        if(base) {
            base->renderizar(window);
        }
        for (auto& inimigo : inimigos) {
            inimigo.renderizar(window);
        }
        
    }
    window.display();
}