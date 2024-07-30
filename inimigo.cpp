#include <iostream>
#include "inimigo.hpp"

using namespace std;
using namespace sf;

Inimigo::Inimigo(const string& inimigoFile){
    if (!background_inimigo.loadFromFile(inimigoFile)) {
        cerr << "Erro ao carregar a imagem do inimigo" << endl;
        exit(1);
    }
    backgroundSprite_inimigo.setTexture(background_inimigo);
    
}

