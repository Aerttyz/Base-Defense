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
        virtual Sprite getSprite() const;
        void definirPosicao(const Vector2f& posicao);
        virtual void mover();
        void atirar(const Vector2f& direcao);
        void atualizarProjeteis(float deltaTime);
        int getVida();
        void setVida(int novaVida);
        virtual void RecuperarVida();
        void RecuperarMunicao();
        void TomarDano();
        void darMunicao();
        Vector2f getPosicao();
        virtual bool verificarColisao(const Sprite& sprite);
        virtual bool verificarColisaoDrop(const Sprite& sprite);
        virtual void renderizar(RenderWindow& window);
        vector<Projetil>& getProjeteis();

        int getRandomQuantidadeProjetil();
    
    private:
        
        
        string bulletSongFile = "assets/music/bulletsong.ogg";
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

        int barraIndex = 0;
        IntRect barra1 = IntRect(0, 0, 28, 8);    // Primeira barra (verde)
        IntRect barra2 = IntRect(0, 8, 28, 8);    // Segunda barra (verde)
        IntRect barra3 = IntRect(0, 16, 28, 8);   // Terceira barra (verde)
        IntRect barra4 = IntRect(0, 24, 28, 8);   // Quarta barra (verde)
        IntRect barra5 = IntRect(0, 32, 28, 8);   // Quinta barra (amarela)
        IntRect barra6 = IntRect(0, 40, 28, 8);   // Sexta barra (amarela)
        IntRect barra7 = IntRect(0, 48, 28, 8);   // Sétima barra (vermelha)
        IntRect barra8 = IntRect(0, 56, 28, 8);   // Oitava barra (vermelha)
        vector<IntRect> barrasVida = {barra1, barra2, barra3, barra4, barra5, barra6, barra7, barra8};
        Texture barraVida;
        Sprite barraSprite;
};


#endif // HEROI_HPP