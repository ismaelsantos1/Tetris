# Tetris

O código é uma implementação do jogo Tetris. A linguagem usada para criar o jogo é a mesma  que foi usada na criação da versão original; o jogo foi desenvolvido pelo cientista russo Alexey Pajitnov no computador soviético chamado Electronika 60.  A biblioteca ncurses foi usada para a implementação da interface gráfica.

As funções mais importantes do código são:

`spawnnewpiece()`: gera uma nova peça aleatória e a posiciona no topo do tabuleiro.

`rotate()`: faz a peça atual girar em 90 graus no sentido horário, se isso for possível sem colidir com outras peças ou os limites do tabuleiro.
A função de rotação é usada para girar a peça de tetrominó atual no jogo Tetris. A função não aceita argumentos e não retorna nenhum valor. Modifica a variável peca, que representa a peça atual do tetrominó, para refletir a rotação.

A função primeiro verifica se a peça atual é uma das seguintes: 'I', 'J', 'K' ou 'L'. Se for, a função gira a peça atualizando a variável peca com a forma girada apropriada. Se a peça atual não for um dos tipos acima, a função não faz nada e retorna.

A rotação das peças é feita copiando os dados relevantes das matrizes TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para a matriz central, que representa o tabuleiro do jogo. A variável de ponto fixo, que armazena as coordenadas do ponto fixo da peça atual, também é atualizada de acordo para refletir a rotação.

Por exemplo, se a peça atual for do tipo 'I', a função a rotaciona copiando os dados do array TetrominoI para o array central, começando nas coordenadas do ponto fixo. As coordenadas do ponto fixo também são atualizadas para refletir a rotação.

A função memcpy é usada para copiar os dados dos arrays TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para o array central. A variável de ponto fixo é atualizada usando operações aritméticas simples para refletir a rotação.
No geral, a função de rotação é responsável por girar a peça de tetrominó atual no jogo Tetris.A função de rotação é usada para girar a peça de tetrominó atual no jogo Tetris. A função não aceita argumentos e não retorna nenhum valor. Modifica a variável peca, que representa a peça atual do tetrominó, para refletir a rotação.

A função primeiro verifica se a peça atual é uma das seguintes: 'I', 'J', 'K' ou 'L'. Se for, a função gira a peça atualizando a variável peca com a forma girada apropriada. Se a peça atual não for um dos tipos acima, a função não faz nada e retorna.

A rotação das peças é feita copiando os dados relevantes das matrizes TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para a matriz central, que representa o tabuleiro do jogo. A variável de ponto fixo, que armazena as coordenadas do ponto fixo da peça atual, também é atualizada de acordo para refletir a rotação.

Por exemplo, se a peça atual for do tipo 'I', a função a rotaciona copiando os dados do array TetrominoI para o array central, começando nas coordenadas do ponto fixo. As coordenadas do ponto fixo também são atualizadas para refletir a rotação.

A função memcpy é usada para copiar os dados dos arrays TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para o array central. A variável de ponto fixo é atualizada usando operações aritméticas simples para refletir a rotação.
No geral, a função de rotação é responsável por girar a peça de tetrominó atual no jogo Tetris.
A função de rotação é usada para girar a peça de tetrominó atual no jogo Tetris. A função não aceita argumentos e não retorna nenhum valor. Modifica a variável peca, que representa a peça atual do tetrominó, para refletir a rotação.

A função primeiro verifica se a peça atual é uma das seguintes: 'I', 'J', 'K' ou 'L'. Se for, a função gira a peça atualizando a variável peca com a forma girada apropriada. Se a peça atual não for um dos tipos acima, a função não faz nada e retorna.

A rotação das peças é feita copiando os dados relevantes das matrizes TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para a matriz central, que representa o tabuleiro do jogo. A variável de ponto fixo, que armazena as coordenadas do ponto fixo da peça atual, também é atualizada de acordo para refletir a rotação.

Por exemplo, se a peça atual for do tipo 'I', a função a rotaciona copiando os dados do array TetrominoI para o array central, começando nas coordenadas do ponto fixo. As coordenadas do ponto fixo também são atualizadas para refletir a rotação.

A função memcpy é usada para copiar os dados dos arrays TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para o array central. A variável de ponto fixo é atualizada usando operações aritméticas simples para refletir a rotação.
No geral, a função de rotação é responsável por girar a peça de tetrominó atual no jogo Tetris.A função de rotação é usada para girar a peça de tetrominó atual no jogo Tetris. A função não aceita argumentos e não retorna nenhum valor. Modifica a variável peca, que representa a peça atual do tetrominó, para refletir a rotação.

A função primeiro verifica se a peça atual é uma das seguintes: 'I', 'J', 'K' ou 'L'. Se for, a função gira a peça atualizando a variável peca com a forma girada apropriada. Se a peça atual não for um dos tipos acima, a função não faz nada e retorna.

A rotação das peças é feita copiando os dados relevantes das matrizes TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para a matriz central, que representa o tabuleiro do jogo. A variável de ponto fixo, que armazena as coordenadas do ponto fixo da peça atual, também é atualizada de acordo para refletir a rotação.

Por exemplo, se a peça atual for do tipo 'I', a função a rotaciona copiando os dados do array TetrominoI para o array central, começando nas coordenadas do ponto fixo. As coordenadas do ponto fixo também são atualizadas para refletir a rotação.

A função memcpy é usada para copiar os dados dos arrays TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para o array central. A variável de ponto fixo é atualizada usando operações aritméticas simples para refletir a rotação.
No geral, a função de rotação é responsável por girar a peça de tetrominó atual no jogo Tetris.
A função de rotação é usada para girar a peça de tetrominó atual no jogo Tetris. A função não aceita argumentos e não retorna nenhum valor. Modifica a variável peca, que representa a peça atual do tetrominó, para refletir a rotação.

A função primeiro verifica se a peça atual é uma das seguintes: 'I', 'J', 'K' ou 'L'. Se for, a função gira a peça atualizando a variável peca com a forma girada apropriada. Se a peça atual não for um dos tipos acima, a função não faz nada e retorna.

A rotação das peças é feita copiando os dados relevantes das matrizes TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para a matriz central, que representa o tabuleiro do jogo. A variável de ponto fixo, que armazena as coordenadas do ponto fixo da peça atual, também é atualizada de acordo para refletir a rotação.

Por exemplo, se a peça atual for do tipo 'I', a função a rotaciona copiando os dados do array TetrominoI para o array central, começando nas coordenadas do ponto fixo. As coordenadas do ponto fixo também são atualizadas para refletir a rotação.

A função memcpy é usada para copiar os dados dos arrays TetrominoI, TetrominoJ, TetrominoK ou TetrominoL para o array central. A variável de ponto fixo é atualizada usando operações aritméticas simples para refletir a rotação.
No geral, a função de rotação é responsável por girar a peça de tetrominó atual no jogo Tetris.

`////////////////////////////////////////////////////////////////////////////////`

`show_next()`: A função show_next() não está presente no código fornecido. No entanto, existem duas funções relacionadas a mostrar a próxima peça: shownext e shownextpiece(). Vou supor que você queria saber sobre a função shownextpiece().

A função shownextpiece() é responsável por exibir a próxima peça que virá na fila no canto inferior direito da tela. Ela é chamada na função updatescrn() sempre que uma nova peça é criada ou quando a tecla 'N' (ou equivalente definido em setkeybind()) é pressionada.

Aqui está uma descrição da função shownextpiece():

Limpa a tela de texto auxiliar right usando wclear().
Define a cor da fonte como vermelha usando wattron(right[HEIGHT-1], COLOR_PAIR(2)).
Imprime a mensagem "PRÓXIMA PEÇA:" seguida da próxima peça na posição (3, 3) da tela auxiliar right.
Atualiza a tela auxiliar right usando wrefresh(right[HEIGHT-1]).
Desativa a cor da fonte usando wattroff(right[HEIGHT-1], COLOR_PAIR(2)).
Em resumo, a função shownextpiece() limpa a tela auxiliar right, define a cor da fonte como vermelha, imprime a mensagem "PRÓXIMA PEÇA:" seguida da próxima peça e, em seguida, atualiza a tela auxiliar right. Por fim, desativa a cor da fonte.

`////////////////////////////////////////////////////////////////////////////////`

`moveleft()`: move a peça atual uma unidade para a esquerda, se isso for possível sem colidir com outras peças ou os limites do tabuleiro.

`moveright()`: move a peça atual uma unidade para a direita, se isso for possível sem colidir com outras peças ou os limites do tabuleiro.

`movedown()`: move a peça atual uma unidade para baixo, se isso for possível sem colidir com outras peças ou os limites do tabuleiro. Se a peça atingir o fundo do tabuleiro ou outra peça, ela é fixada no tabuleiro e uma nova peça é gerada.

`init()`: inicializa o tabuleiro com as peças iniciais.

`updatelevel()`: atualiza o nível do jogo com base no número de linhas removidas.

`setkeybind()`: define as teclas de controle do jogo com base em um arquivo de configuração.

`game()`: a função principal do jogo, que gera as peças, processa as entradas do usuário e atualiza o tabuleiro. Ela continua até que o jogo seja encerrado ou o usuário saia do jogo.

`main()`: a função principal do programa, que inicializa a interface gráfica, solicita as entradas do usuário e chama a função game().

## Função de cada biblioteca incluída

`stdio.h`: essa é a biblioteca padrão de entrada e saída. Vai ter as funções mais usadas, tipo scanf, printf, sprintf.

`stdlib.h`: biblioteca usada para alocar memória de forma dinâmica, usando `malloc`, evitando um uso excessivo de memória e, consequentemente, um estouro de memória. A função rand tbm pertence a essa biblioteca, e é responsável por gerar números aleatórios.

`string.h`:  fornece funções para manipulação de strings, como concatenar e comparar cadeias de caracteres. Contém as funções `strcpy`, `strlen` e `strcat`.

`time.h`:  fornece funções para medir tempo, como por exemplo `get_time()`. Isso é usado na função `waitforinput()`, que pausa o jogo até- `math`: fornece funções matemáticas, como arredondamento.

`unistd.h`: contém a função `usleep` para pausar a execução do programa por um determinado tempo em microsegundos.

`ncurses.h`: usada para criar a interface de linhas de comando. Contém as funções para criar janelas, manipular cores e ler input do usuário. As libs ncurses são utilizadas para a manipular as tela de jogo, além da criação da interface de linha de comando.


A função initpiece() inicializa uma nova peça do jogo Tetris. Aqui está um passo a passo da função:

O checkclr() é chamado para verificar se alguma linha foi apagada e atualizar o estado do jogo de acordo.
a peça atual (atual) é definida como o valor next e, em seguida, next é definida como um número inteiro aleatório entre 0 e 6 (inclusive) usando Rand()% 7.
Uma instrução switch é usada para determinar qual peça inicializar com base no valor da corrente.
Para cada caso, o Tetromino correspondente é copiado para o array central na posição [0] usando memcpy(). A matriz de ponto fixo também é atualizada para armazenar a posição do ponto fixo da peça.
A variável peca é definida como o caractere correspondente da peça.
A função retorna após inicializar a peça.

A função inicializa uma nova peça copiando o Tetromino correspondente no array central e definindo o array de ponto fixo para armazenar a posição do ponto fixo da peça. A variável peca também é definida como o caractere correspondente da peça. Isso permite que o jogo acompanhe a peça atual e sua posição no tabuleiro de jogo.

`rotate()`:













© Ismael dos Santos & Mateus Garcia - UERN (Universidade Do Rio Grande do Norte), 2024