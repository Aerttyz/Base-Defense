# Base-Defense :space_invader: :space_invader:

## Projeto de um jogo desenvolvido em C++/SFML da disciplina de Linguagem de Programação
O jogo consiste em um soldado que tem a missão de defender sua base em um mapa 2D. Inimigos surgem de forma aleatória e avançam em direção a base, disparando projéteis enquanto tentam dominar o campo de batalha.


## Referência

 - [Base Defense - Allegro 5 C++ test game](https://www.youtube.com/watch?v=5NH7W2XgdwE)



## Funcionalidades

- Modos de jogo Single Player e COOP
- Tank com habilidade de recuperação de vida para Base (COOP)
- Diferentes Niveis de Dificuldade
- Dificuldade escalável
- Diferentes tipos de Inimigos
- Drops inimigos
- Upgrades para base

## Documentação

[Documentação Base-Defense](https://aerttyz.github.io/Base-Defense/annotated.html)

## Stack utilizada

**Game Developer:** C++/ SFML

**Designe:** [Pixelart](https://Pixelart.com) e Photoshop

## Gameplay de exibição:
https://www.youtube.com/watch?v=_91ANe7mYfc

[**Base-Defense Preview**](/)

## Instalação

Configuração e execução no Linux

**Instale as ferramentas essenciais para C++:**

Primeiramente, atualize os repositórios de pacotes:
```bash
  sudo apt update
```
Em seguida, instale o pacote `build-essential` que inclui o compilador `g++` e outras ferramentas:
```bash
  sudo apt install build-essential
```
Por fim, instale a biblioteca SFML (Simple and Fast Multimedia Library) para execução do jogo:
```bash
  sudo apt-get install libsfml-dev
```

**Compilação e execução do Jogo:**

O projeto é compilado com ajuda de um ```makefile``` então para compilar apenas:

```bash 
make
```

Para execução siga o comando e divirta-se:
```bash
./base-defense
```
