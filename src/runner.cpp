#include "../include/runner.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

using namespace std;
using namespace sf;

Runner::Runner(const string& runnerFile) : Inimigo(runnerFile) {
    this->velocidade = 400.0f;

    if(!background_runner.loadFromFile(runnerFile)){
        cout << "Erro ao carregar a textura do Runner" << endl;
    }else{
        backgroundSprite_runner.setTexture(background_runner);
    }
}