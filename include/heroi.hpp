#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/projeteis.hpp" 
#include <vector>
using namespace sf;
using namespace std;
class Projetil;

class Heroi {
    public:
        Heroi(int vida, const string& heroiFile, const Font& fonte);
        Sprite getSprite() const;
        void definirPosicao(const Vector2f& posicao);
        virtual void mover();
        void atirar(const Vector2f& direcao);
        void atualizarProjeteis(float deltaTime);
        void setVida(int novaVida);
        int getVida();
        virtual void RecuperarVida();
        void RecuperarMunicao();
        void TomarDano();
        void darMunicao();
        Vector2f getPosicao();
        virtual bool verificarColisao(const Sprite& sprite);
        void verificarColisao(const RectangleShape& shape);
        virtual bool verificarColisaoDrop(const Sprite& sprite);
        virtual void renderizar(RenderWindow& window);
        vector<Projetil>& getProjeteis();

        int getRandomQuantidadeProjetil();
    
    private:
        
        
        string bulletSongFile;
        Sound bulletSong;
        SoundBuffer bufferBulletSong;
        Texture texturaProjetil;
        string projetilFile;
        vector<Projetil> projeteis;
        Texture background_heroi;
        Sprite backgroundSprite_heroi;
        Vector2f posicao;
        
        Clock relogio;
        Time dps;


        Sprite backgroundSprite_projetil;
        Texture background_projetil;

        int quantidadeProjetil;
        Text textoMunicao;
    protected:
        int vida;
        float velocidade;
        Text  textoVida;
};


#endif // HEROI_HPP