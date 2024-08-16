#include "../include/inimigoTank.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

using namespace std;
using namespace sf;

/**
 * @brief Construtor da classe InimigoTank que herda de Inimigo
 * 
 *  
 * Este construtor herda de Inimigo e inicializa o tanque inimigo com uma certa quantidade de vida, uma imagem.
 * 
 * @param inimigoTankFile Arquivo de imagem do inimigoTank
 * 
 */
InimigoTank::InimigoTank(const string& inimigoTankFile) : Inimigo(inimigoTankFile) {
    this->velocidade = 20.0f;
    this->intervaloDisparo = seconds(5);
    if(!background_inimigoTank.loadFromFile(inimigoTankFile)){
        cout << "Erro ao carregar a textura do Runner" << endl;
    }else{
        backgroundSprite_inimigoTank.setTexture(background_inimigoTank);
    }
}

/**
 * @brief Retorna a vida do tank inimigo
 * 
 * @return int 
 */
int InimigoTank::getVidaInimigo(){
    return vidaInimigo;
}

/**
 * @brief Diminui a vida do tank inimigo
 * 
 */
void InimigoTank::tomarDano(){
    vidaInimigo--;
}