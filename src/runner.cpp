#include "../include/runner.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

using namespace std;
using namespace sf;

/**
 * @brief Construtor da classe Runner que herda de Inimigo
 * 
 *  
 * Este construtor herda de Inimigo e inicializa o Runner com uma certa quantidade de vida, uma imagem.
 * Ajuda a definir a velocidade do Runner.
 * 
 * @param runnerFile Arquivo de imagem do Runner
 * 
 */
Runner::Runner(const string& runnerFile) : Inimigo(runnerFile) {
    this->velocidade = 200.0f;

    if(!background_runner.loadFromFile(runnerFile)){
        cout << "Erro ao carregar a textura do Runner" << endl;
    }else{
        backgroundSprite_runner.setTexture(background_runner);
    }
}