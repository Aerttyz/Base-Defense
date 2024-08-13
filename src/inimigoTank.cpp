#include "../include/inimigoTank.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

using namespace std;
using namespace sf;

InimigoTank::InimigoTank(const string& inimigoTankFile) : Inimigo(inimigoTankFile) {
    this->velocidade = 20.0f;

    if(!background_inimigoTank.loadFromFile(inimigoTankFile)){
        cout << "Erro ao carregar a textura do Runner" << endl;
    }else{
        backgroundSprite_inimigoTank.setTexture(background_inimigoTank);
    }
}

int InimigoTank::getVidaInimigo(){
    return vidaInimigo;
}

void InimigoTank::tomarDano(){
    vidaInimigo--;
}