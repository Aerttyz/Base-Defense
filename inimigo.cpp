#include <iostream>
#include "inimigo.hpp"

using namespace std;
using namespace sf;

Inimigo::Inimigo(const string& inimigoFile) : textureLoaded(false) {
        if (!background_inimigo.loadFromFile(inimigoFile)) {
            cerr << "Erro ao carregar a imagem do inimigo" << endl;
            exit(1);
        }else{
            backgroundSprite_inimigo.setTexture(background_inimigo);
            textureLoaded = true;
        }
        
    }

void Inimigo::setPosicao(const Vector2f& posicao) {
        backgroundSprite_inimigo.setPosition(posicao);
    }

Vector2f Inimigo::getPosicao() const {
        return backgroundSprite_inimigo.getPosition();
    }

void Inimigo::renderizar(RenderWindow& window) {
        if(textureLoaded){
            window.draw(backgroundSprite_inimigo);
        } else {
            cerr << "Erro ao renderizar inimigo" << endl;
        }     
    }
bool Inimigo::isTextureLoaded() const {
        return textureLoaded;
    }
    
