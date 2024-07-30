#include <SFML/Graphics.hpp>
#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
#include <iostream>
using namespace sf;
using namespace std;

int main() {
    //Cria janela de 800x600 pixels
    RenderWindow window(VideoMode(800, 600), "Base-Defense");
    

    Font font;
    if (!font.loadFromFile("imagens/fonts/fonts.ttf")) {
        cerr << "Erro ao carregar a fonte" << endl;
        return -1;
    }

    //Carrega imagem do herói
    Heroi heroi(100, "imagens/Cactus Man.png", font);

    //Carrega tela
    gerenciamentoTela gerenciamentoTela("imagens/background.png","imagens/dark_forest.ogg", &heroi);    
    
    
    
    //Loop principal
    while (window.isOpen()) {
            
            gerenciamentoTela.eventos(window);
            
            gerenciamentoTela.atualizar();
            
            gerenciamentoTela.renderizar(window);

            
            
        }
        return 0;
    }
