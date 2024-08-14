
# Documentação Base-Defense

## Explicação dos Métodos
**Construtor Inimigo::Inimigo:** 

- Inicializa os atributos do objeto Inimigo.
- Carrega a textura do inimigo a partir do arquivo especificado.
- Define a textura do sprite do inimigo.
- Carrega a textura do projetil e define a textura do sprite do - projetil.
#
**Método Inimigo::mover:** 

- Calcula a direção e a distância até a posição alvo.
- Move o inimigo na direção da posição alvo se a distância for maior que 1.0f.
#
**Método Inimigo::atirarCOOP:** 

- Verifica se o intervalo de disparo foi atingido.
- Compara as distâncias até o herói e o tanque.
- Normaliza a direção e cria um projetil na direção do alvo mais próximo.
- Adiciona o projetil à lista de projéteis e reinicia o relógio.
#
**Método Inimigo::atirar:** 

- Verifica se o intervalo de disparo foi atingido.
- Normaliza a direção e cria um projetil na direção especificada.
- Adiciona o projetil à lista de projéteis e reinicia o relógio.
#
**Método Inimigo::atualizarProjeteis:**

- Move o projetil inimigo. 
- Verifica se o projetil colidiu com a janela usando do método ```verificarColisãoJanela```.
#
**Método Inimigo::verificarColisão:**

- Verifica se o inimigo colidiu com outro ```Sprite``` e retorna um booleano.
#
**Método Inimigo::renderizar:**

- Verifica se a textura foi carregada usando do método ```isTextureLoaded```.
- Desenha o inimigo e seus projéteis.