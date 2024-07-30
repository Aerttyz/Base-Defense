#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
#include <iostream>
#include "base.hpp"
using namespace std;
using namespace sf;


//Carrega a imagem de fundo e a música
gerenciamentoTela::gerenciamentoTela(const string& backgroundFile, const string& backgroundMenuFile,const string& musicFile, Heroi *heroi, Base *base) : heroi(heroi), base(base), estado(Estado::MENU) {
    
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
    backgroundSprite.setTexture(background);
    backgroundSprite_menu.setTexture(background_menu);

    shape.setSize(Vector2f(100.0f, 100.0f));
    shape.setFillColor(Color::Green);
    shape.setPosition(200.0f, 200.0f);
    
    textoMenu.setFont(font);
    textoMenu.setCharacterSize(30);
    textoMenu.setFillColor(Color::White);
    textoMenu.setString("Pressione Enter para iniciar o jogo");
    FloatRect textRect = textoMenu.getLocalBounds();
    textoMenu.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    textoMenu.setPosition(400.0f, 300.0f);
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
    backgroundSprite_menu.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
}

//Ajusta a posição do herói
void gerenciamentoTela::setHeroiPosition(RenderWindow& window) {
   Vector2i mousePosition = Mouse::getPosition(window);
   Vector2f novaPosicao(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
   if(heroi){
         heroi->definirPosicao(novaPosicao);
   }
}

//Atualiza a posição do herói
void gerenciamentoTela::atualizar() {
    if(estado == Estado::JOGO) {
        if(heroi){
            heroi->mover();
            heroi->verificarColisao(shape);
            heroi->verificarColisao(base->getSprite());
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
        
        window.draw(shape);
    }
    window.display();
}