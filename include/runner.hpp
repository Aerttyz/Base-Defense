#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <SFML/Graphics.hpp>
#include "../include/inimigo.hpp"

class Runner : public Inimigo {
    public:
        Runner(const string& inimigoFile);
    private:
        Sprite backgroundSprite_runner;
        Texture background_runner;

};   

#endif // RUNNER_HPP