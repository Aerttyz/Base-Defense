#include <SFML/Graphics.hpp>
#include "Gerenciamento_Tela.hpp"
#include "heroi.hpp"
using namespace sf;

int main() {
    //Cria janela de 800x600 pixels
    RenderWindow window(VideoMode(800, 600), "Base-Defense");
    
    Heroi heroi("imagens/Cactus Man.png");
    GerenciametoTela gerenciamentoTela("imagens/background.png", &heroi);    
    

    
    //Loop principal
    while (window.isOpen()) {
            gerenciamentoTela.eventos(window);
            
            
            gerenciamentoTela.renderizar(window);
            heroi.renderizar(window);

            window.display();
        }
        //Desenha o background e o herói
        
        
        return 0;
    }
