#include <SFML/Graphics.hpp>
#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
using namespace sf;

int main() {
    //Cria janela de 800x600 pixels
    RenderWindow window(VideoMode(800, 600), "Base-Defense");
    
    //Carrega imagem do herói
    Heroi heroi("imagens/Cactus Man.png");

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
