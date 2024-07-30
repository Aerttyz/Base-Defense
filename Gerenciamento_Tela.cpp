#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
#include <iostream>
#include "base.hpp"
using namespace std;
using namespace sf;


//Carrega a imagem de fundo e a música
gerenciamentoTela::gerenciamentoTela(const string& backgroundFile,const string& musicFile, Heroi *heroi, Base *base) : heroi(heroi), base(base) {
    
    if(!background.loadFromFile(backgroundFile)) {
        cout << "Erro ao carregar imagem de fundo" << endl;
    }
    if(!music.openFromFile(musicFile)) {
        cout << "Erro ao carregar música" << endl;
    }else {
        music.setLoop(true);
        music.play();
        
    }
    backgroundSprite.setTexture(background);

    shape.setSize(Vector2f(100.0f, 100.0f));
    shape.setFillColor(Color::Green);
    shape.setPosition(200.0f, 200.0f);
    
}

//Verifica eventos do mouse
void gerenciamentoTela::eventos(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
            setHeroiPosition(window);
        }
    }
}

//Ajusta o tamanho da imagem de fundo
void gerenciamentoTela::setBackgroundScale(RenderWindow& window) {
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
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
    if(heroi){
        heroi->mover();
        heroi->verificarColisao(shape);
        heroi->verificarColisao(base->getSprite());
    }
}

//Renderiza a imagem de fundo e o herói
void gerenciamentoTela::renderizar(RenderWindow& window) {
    window.clear();

    setBackgroundScale(window);
    window.draw(backgroundSprite);

    if(heroi != nullptr) {
        heroi->renderizar(window);
    }
    
    if(base) {
        base->renderizar(window);
    }
    
    window.draw(shape);

    window.display();
}