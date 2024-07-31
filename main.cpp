#include <SFML/Graphics.hpp>
#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
#include "base.hpp"
#include "inimigo.hpp"
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

    Inimigo novoInimigo("imagens/Cactus Man.png");

    //Carrega imagem da base
    Base base(100, "imagens/safezone.png", font, Vector2f(window.getSize()));

    //Carrega imagem do herói
    Heroi heroi(100, "imagens/Cactus Man.png", font);

    //Carrega tela
    gerenciamentoTela gerenciamentoTela("imagens/background1.png", "imagens/backgroundInicio.png", "imagens/dark_forest.ogg", &heroi, &base, Vector2f(window.getSize()));    
    
    
    
    //Loop principal
    while (window.isOpen()) {
            
            gerenciamentoTela.eventos(window);
            
            gerenciamentoTela.atualizar();
            
            gerenciamentoTela.renderizar(window);

            
            
        }
        return 0;
    }
