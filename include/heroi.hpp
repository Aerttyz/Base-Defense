#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/projeteis.hpp" 
#include <vector>
using namespace sf;
using namespace std;


class Heroi {
    public:
        Heroi(int vida, const string& heroiFile, const Font& fonte);
        Sprite getSprite() const;
        void definirPosicao(const Vector2f& posicao);
        void mover();
        void atirar(const Vector2f& direcao);
        void atualizarProjeteis();
        void setVida(int novaVida);
        int getVida();
        Vector2f getPosicao();
        void verificarColisao(const Sprite& sprite);
        void verificarColisao(const RectangleShape& shape);
        void renderizar(RenderWindow& window);
        vector<Projetil>& getProjeteis();
    
    private:
        float velocidade;
        int vida;
        string bulletSongFile;
        Sound bulletSong;
        SoundBuffer bufferBulletSong;
        Texture texturaProjetil;
        string projetilFile;
        vector<Projetil> projeteis;
        Texture background_heroi;
        Sprite backgroundSprite_heroi;
        Vector2f posicao;
        Text  textoVida;
        Clock relogio;
        Time dps;


        Sprite backgroundSprite_projetil;
        Texture background_projetil;
};


#endif // HEROI_HPP