#include <SFML/Graphics.hpp>
#include "../include/Gerenciamento_Tela.hpp"
#include "../include/heroi.hpp"
#include "../include/base.hpp"
#include "../include/inimigo.hpp"
#include <iostream>
using namespace sf;
using namespace std;

int main() {
    
    RenderWindow window(VideoMode(800, 600), "Base-Defense");
    //Ajusta a taxa de atualização da janela
    window.setFramerateLimit(60);
    

    Font font;
    if (!font.loadFromFile("assets/fonts/LilitaOne-Regular.ttf")) {
        cerr << "Erro ao carregar a fonte" << endl;
        return -1;
    }


    //Carrega imagem da base
    Base base(100, "assets/images/background/baseFinal1.png", font, Vector2f(window.getSize()));

    //Carrega imagem do herói
    Heroi heroi(100, "assets/images/characters/hero.png", font);

    //Carrega tela
    gerenciamentoTela gerenciamentoTela("assets/images/background/background1.png", "assets/images/background/testeInicial--.jpg", "assets/music/dark_forest.ogg", &heroi, &base, Vector2f(window.getSize()));    
    
    
    
    //Loop principal
    while (window.isOpen()) {
            
            gerenciamentoTela.eventos(window);
            
            gerenciamentoTela.atualizar(window);
            
            gerenciamentoTela.renderizar(window);

            
            
        }
        return 0;
    }
