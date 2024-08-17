#ifndef INIMIGO_TANK_HPP
#define INIMIGO_TANK_HPP

#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

class InimigoTank : public Inimigo {
    public:
        InimigoTank(const string& inimigoFile);
        int getVidaInimigo();
        void tomarDano();
        
    private:
        Sprite backgroundSprite_inimigoTank;
        Texture background_inimigoTank;
        int vidaInimigo = 3;

};   

#endif // INIMIGO_TANK_HPP