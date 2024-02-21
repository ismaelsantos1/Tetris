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

`//////////////////////////////////////////////////////////////////////////////////////////////////////////////`
`updatescrn()`: O updatescrn() é usado para atualizar a exibição da tela do jogo Tetris no. Parece estar definido em outra parte do código. Explicarei sua provável funcionalidade com base em seu nome e no código que o chama.

function provavelmente faz o seguinte:

. Atualiza a tela para garantir que as alterações mais recentes sejam exibidas. Isso normalmente é feito usando a função refrescante() na biblioteca de maldições, que está sendo usada neste código. 2. Com base no estado atual do jogo, ele atualiza o conteúdo das matrizes esquerda, central e direita, que representam as partes esquerda, central e direita da tela, respectivamente. Essas matrizes contêm strings que definem o texto e os gráficos a serem exibidos nessas partes da tela. 3. Em seguida, ele copia o conteúdo atualizado das matrizes esquerda, central e direita para os locais correspondentes na tela do console usando as funções wmove(), wprintw() e wrefresh() da biblioteca de Curses. 4. Se a variável showext estiver definida como true, ela também exibe a próxima peça que aparecerá no jogo, na parte direita da tela. 5. Se a variável showtext estiver definida como verdadeira, ela exibirá vários textos informativos na parte esquerda da tela, como nome do jogador, nível, pontuação e linhas limpas.

No geral, a função updatescrn() é responsável por garantir que a tela do console reflita com precisão o estado atual do jogo, atualizando o conteúdo dos arrays left, center e right e copiando-os para a tela do console.

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

`toplist()`: A função toplist() no código fornecido parece ter sido projetada para exibir uma lista de pontuações mais altas, mas a implementação não é fornecida no trecho de código.

Com base no nome e no contexto em que é chamada (após o término do jogo), podemos inferir que a função provavelmente faz o seguinte:

. Lê o arquivo de pontuação mais alta (que não é mostrado no trecho de código) e armazena as pontuações mais altas em uma matriz ou estrutura de dados. 2. Classifica as pontuações mais altas em ordem decrescente. 3. Exibe as pontuações mais altas na tela usando printw() ou uma função semelhante. 4. Atualiza a tela usando update() para garantir que as pontuações mais altas sejam exibidas.

`////////////////////////////////////////////////////////////////////////////////`
`addscore()`: A função addscore() é responsável por adicionar pontos à pontuação atual do jogo, de acordo com o número de linhas removidas do tabuleiro. Ela recebe um parâmetro lines, que representa o número de linhas removidas.

A função começa definindo o valor de points como zero. Em seguida, ela utiliza um switch statement para calcular o número de pontos a serem adicionados à pontuação, com base no número de linhas removidas.

Se uma linha for removida, o jogador recebe 100 pontos.
Se duas linhas forem removidas simultaneamente, o jogador recebe 300 pontos.
Se três linhas forem removidas simultaneamente, o jogador recebe 500 pontos.
Se quatro linhas forem removidas simultaneamente (um Tetris), o jogador recebe 800 pontos.
Após calcular o número de pontos a serem adicionados, a função atualiza a pontuação atual adicionando o valor de points a ela. Em seguida, a função chama a função updatescore() para atualizar a tela com a nova pontuação.

Por fim, a função retorna o valor de points, que pode ser utilizado para outros fins, como atualizar a velocidade do jogo ou outros cálculos relacionados à pontuação.
`////////////////////////////////////////////////////////////////////////////////`

`gameover()`: A função gameover() é usada para lidar com a condição de fim de jogo no jogo Tetris. É chamado quando o jogador perde o jogo, por exemplo, quando um novo tetrominó não pode mais ser colocado no tabuleiro de jogo sem se sobrepor aos blocos existentes.

Com base no nome e no contexto, podemos assumir que a função gameover() pode exibir uma mensagem de fim de jogo para o usuário, interromper o jogo e possivelmente fornecer opções para reiniciar ou encerrar o jogo. Os detalhes específicos da implementação dependeriam de como a função é definida na base de código.
`///////////////////////////////////////////////////////////////////////////////`

`checkclr()`: A função checkclr é usada para verificar se há alguma linha completa no tabuleiro do jogo Tetris. Veja um passo a passo da função:

1 A função inicializa uma variável clear com zero, que será usada para contar o número de linhas completadas. 2 A função então percorre cada linha do tabuleiro de jogo (de baixo para cima) usando um loop for. 3. Dentro do loop for, a função inicializa uma variável numfull com zero, que será usada para contar o número de quadrados preenchidos na linha atual. 4. A função então percorre cada coluna da linha atual usando outro loop for. 5. Dentro do loop for interno, a função verifica se o quadrado atual no tabuleiro do jogo está preenchido (ou seja, tem o valor #). Se o quadrado for preenchido, a função incrementa a variável numfull. 6. Após verificar todos os quadrados da linha atual, a função verifica se o número de quadrados preenchidos (numfull) é igual à largura do tabuleiro de jogo (COLS). Se numfull for igual a COLS, significa que a linha atual está completamente preenchida e pode ser limpa. 7. Se a linha atual estiver completamente preenchida, a função incrementa a variável numclear e desloca todas as linhas acima da linha atual para baixo em uma linha usando uma função memmove(). 8. Após verificar todas as linhas, a função retorna o número de linhas completadas (numclear).

A função checkclr() é responsável por detectar linhas completas no tabuleiro de jogo e limpá-las para abrir espaço para novos blocos. Isso é feito percorrendo cada linha do tabuleiro de jogo e verificando se ela está completamente preenchida. Se uma linha for completamente preenchida, a função desloca todas as linhas acima dela em uma linha e incrementa a variável numclear. A função então retorna o número de linhas concluídas.

`///////////////////////////////////////////////////////////////////////////////`

`initpiece()`: A função initpiece() é responsável por gerar uma nova peça aleatória e posicioná-la no topo do tabuleiro de jogo em uma posição válida.

Primeiro, é gerado um número aleatório entre 0 e 6, que será usado como índice para selecionar uma das sete formas de peças possíveis (I, J, L, O, S, T, Z). Em seguida, é definido o ponto fixo da peça, que é a posição inicial da mesma no tabuleiro. O ponto fixo é definido como um array de dois inteiros, onde o primeiro elemento é a linha e o segundo é a coluna.

Em seguida, é verificado se a posição inicial da peça está livre, ou seja, se não há nenhum obstáculo ou outra peça ocupando essa posição. Se a posição estiver livre, a peça é copiada para o tabuleiro a partir da posição fixa. Caso contrário, a função é chamada recursivamente até que uma posição válida seja encontrada.

Por fim, é atualizado o valor da variável global peca com o caractere correspondente à forma da peça gerada.
`//////////////////////////////////////////////////////////////////////////////`

`moveleft()`:
A função moveleft() responsável por mover a peça atual uma unidade para a esquerda, se isso for possível. Ela faz isso verificando se a posição de destino está livre ou não, e se estiver, copia a parte relevante da peça para a posição de destino.

A função usa um switch statement para selecionar o comportamento adequado com base no tipo da peça atual, que é armazenado na variável global peca. Cada caso corresponde a um tipo de peça diferente, e contém as instruções específicas para mover essa peça para a esquerda.

Por exemplo, no caso da peça 'I', a função verifica se a posição à esquerda da peça está livre ou não, e se estiver, move a peça para a esquerda, copiando os 8 bytes relevantes da peça para a posição de destino. Isso é feito usando a função memcpy(), que copia uma região de memória para outra.

Se a posição de destino não estiver livre, a função retorna sem fazer nada, pois a peça não pode ser movida para a esquerda neste caso.

No final, a função atualiza a variável global fixedpoint, que armazena a posição atual da peça, para refletir o novo local da peça.
`/////////////////////////////////////////////////////////////////////////////`

`moveright()`: A função moveright() é responsável por mover a peça atual uma unidade para a direita no jogo de Tetris, desde que isso seja possível. Ela faz isso verificando as condições de colisão e copiando os valores dos blocos da peça atual para as posições correspondentes na matriz de jogo.

A função começa verificando se a peça atual pode ser movida para a direita sem colidir com outras peças ou os limites do jogo. Isso é feito verificando as condições de colisão específicas para cada tipo de peça. Se a peça não pode ser movida para a direita, a função retorna imediatamente sem fazer nenhuma alteração no jogo.

Se a peça pode ser movida para a direita, a função copia os valores dos blocos da peça atual para as posições correspondentes na matriz de jogo, uma unidade à direita. Isso é feito usando a função memcpy() para copiar os valores dos blocos da peça atual para as posições correspondentes na matriz de jogo, uma unidade à direita.

Em seguida, a função atualiza a posição fixa da peça atual, incrementando o valor de fixedpoint[1] em uma unidade. Isso é feito para refletir o fato de que a peça foi movida para a direita.

Por fim, a função retorna 0, indicando que a operação de mover a peça para a direita foi concluída com sucesso.
`/////////////////////////////////////////////////////////////////////////////`

`movedown()`: A função movedown() responsável por mover a peça atual para baixo no jogo de Tetris. Ela faz isso verificando se a próxima posição da peça está livre ou não. Se estiver livre, a peça é movida para baixo e a função retorna 0. Caso contrário, se a próxima posição estiver ocupada por um bloco sólido ou se a peça atingir o topo do tabuleiro, a função retorna 1, indicando que o jogo deve ser encerrado.

A função começa verificando se a próxima linha abaixo da peça está livre ou não. Se a próxima linha estiver ocupada por um bloco sólido ou se a peça atingir o topo do tabuleiro, a função retorna 1. Caso contrário, a peça é movida para baixo e a função retorna 0.

A função também verifica se a peça está se sobrepondo a outras peças fixas no tabuleiro. Se isso acontecer, a função retorna 1, indicando que o jogo deve ser encerrado.

Além disso, a função verifica se a peça está se sobrepondo à parte inferior do tabuleiro. Se isso acontecer, a função retorna 1, indicando que o jogo deve ser encerrado.

Em resumo, a função movedown() é responsável por mover a peça atual para baixo no tabuleiro de Tetris, verificando se a próxima posição está livre ou não, e se a peça está se sobrepondo a outras peças fixas ou à parte inferior do tabuleiro. Se a próxima posição estiver livre, a peça é movida para baixo e a função retorna 0. Caso contrário, a função retorna 1, indicando que o jogo deve ser encerrado.

`/////////////////////////////////////////////////////////////////////////////`

`init()`: A função init() é responsável por inicializar a tela do jogo de Tetris. Ela é chamada no início do jogo e é responsável por definir a aparência inicial da tela, incluindo a pontuação, o nível e as instruções do jogo.

A função utiliza a função memcpy() para copiar strings de texto em três matrizes bidimensionais, left, center e right, que representam as diferentes partes da tela do jogo. Cada matriz tem dimensões HEIGHT x WIDTH, onde HEIGHT e WIDTH são constantes definidas no início do código.

A matriz left é usada para exibir a pontuação, o nível e o nome do jogador na parte esquerda da tela. A matriz center é usada para exibir a grade de jogo no centro da tela. A matriz right é usada para exibir as instruções do jogo e as opções de controle na parte direita da tela.

A função init() é chamada uma única vez no início do jogo e define a aparência inicial da tela. A partir daqui, outras funções do jogo irão atualizar a tela com as informações relevantes, como a posição da peça atual, a pontuação e o nível atual.

`/////////////////////////////////////////////////////////////////////////////`

`updatelevel()`: A função update() atualiza o nível do jogo exibido na tela, no canto superior esquerdo do tabuleiro de jogo. Ela faz isso criando uma string temporária tmp usando a funçãosprintf(), que converte o valor atual da variável levelem uma string e armazena-a emtmp. Em seguida, a string tmpé copiada para a posição adequada no arrayleft`, que é exibido na tela.

Em resumo, a função updatelevel() atualiza a string exibida na tela para mostrar o novo nível atual do jogo.

`/////////////////////////////////////////////////////////////////////////////`

`setkeybind()`: A função setkey() é responsável por definir as associações de teclas para o jogo de Tetris. Ela é chamada no início do j e lê as configurações de tecl definidas em um arquivo de configuração (não mostrado no código fornecido).

A função define as seguintes associações de teclas:

right[3][3] é associado à tecla de seta para a esquerda (MOVE), que move a peça atual para a esquerda.
right[3][14] é associado à tecla de seta para a direita (MOVD), que move a peça atual para a direita.
right[4][8] é associado à tecla 'z' (ROTA), que rotaciona a peça atual em sentido anti-horário.
right[5][3] é associado à tecla de barra de espaço (DROP), que faz a peça atual cair rapidamente até o fundo do tabuleiro ou colidir com outras peças.
right[5][14] é associado à tecla 'x' (RSET), que reinicia o jogo.
right[6][3] é associado à tecla 'c' (SNXT), que exibe a próxima peça que será desbloqueada.
right[7][3] é associado à tecla 'v' (STXT), que exibe um texto sobre as regras do jogo.
right[8][3] é associado à tecla 'b' (EXT), que exibe a lista de melhores pontuações.
A função utiliza a matriz right para armazenar as associações de teclas e a função toupper() para converter as teclas em letras maiúsculas antes de armazená-las. Isso é feito para facilitar a comparação com as teclas pressionadas posteriormente no jogo.

`/////////////////////////////////////////////////////////////////////////////`

`game()`: A função game() é a função principal que simula o jogo de Tetris. Ela é responsável por gerenciar a tela de jogo, atualizar a pontuação e o nível, controlar as peças e detectar colisões, entre outras coisas.

A função começa definindo algumas variáveis globais e chamando a função init() para inicializar a tela de jogo. Em seguida, ela lê as configurações de teclas definidas no arquivo de configuração e desativa o modo de espera do terminal com nodelay(stdscr, FALSE).

A variável end é usada para controlar o fim do jogo. Se ela for definida como verdadeira, o jogo será encerrado. A variável score armazena a pontuação atual do jogador, level armazena o nível atual do jogo e clrlines conta as linhas limpas pelo jogador.

A função updatescore() é chamada para atualizar a pontuação na tela e a função updatelevel() é chamada para atualizar o nível atual do jogo. A função initpiece() é chamada para inicializar uma nova peça e a função updatescrn() é chamada para atualizar a tela de jogo.

A função gettimeofday() é usada para medir o tempo entre as iterações do loop principal do jogo. O loop principal do jogo é executado enquanto a variável end for falsa. Dentro do loop, a função getch() é usada para ler as teclas pressionadas pelo jogador e a função movedown() é chamada para mover a peça atual para baixo na tela. Se a peça atingir o fundo da tela ou colidir com outras peças, a função gameover() é chamada para encerrar o jogo.

Se o jogador pressionar a tecla "DROP", a peça atual é movida para baixo imediatamente e a função updatescrn() é chamada para atualizar a tela de jogo. Se o jogador pressionar a tecla "RSET", o jogo é reiniciado. Se o jogador pressionar a tecla "STXT", a função showtext é alternada entre mostrar e esconder o texto de ajuda na tela. Se o jogador pressionar a tecla "SNXT", a função shownext é alternada entre mostrar e esconder a próxima peça na tela. Se o jogador pressionar a tecla "MOVE", a peça atual é movida para a esquerda e a função updatescrn() é chamada para atualizar a tela de jogo. Se o jogador pressionar a tecla "MOVD", a peça atual é movida para a direita e a função updatescrn() é chamada para atualizar a tela de jogo. Se o jogador pressionar a tecla "ROTA", a peça atual é rotacionada e a função updatescrn() é chamada para atualizar a tela de jogo.

Se o jogador pressionar a tecla "EXT", o jogo é encerrado. Se a variável end for verdadeira, a função gameover() é chamada para exibir a tela de game over e encerrar o jogo. Se o jogador limpar um número suficiente de linhas, a variável clrlines é incrementada e a função updatelevel() é chamada para atualizar o nível do jogo.

A função retorna 1 se o jogo for encerrado com sucesso e 0 se o jogo for encerrado devido a um erro ou a uma interrupção do usuário.

`////////////////////////////////////////////////////////////////////////////`
`main()`: A função main é o ponto de entrada do programa em C e C++. Ela é responsável por inicializar o ambiente de execução, chamar as funções necessárias e gerenciar a execução do programa. No código fornecido, a função main() é responsável por:

Alocar memória para a variável name usando malloc().
Inicializar o gerador de números aleatórios usando srand() com a hora atual como semente.
Inicializar a tela do terminal usando initscr().
Inicializar a biblioteca de cores usando start_color().
Configurar o modo de leitura de teclado bruta usando cbreak().
Inicializar as cores usando init_pair().
Ativar as cores usando attron(COLOR_PAIR(1)).
Solicitar o nível inicial ao usuário e verificar sua validade.
Solicitar o nome do usuário e armazená-lo na variável name.
Desativar a exibição de caracteres digitados usando noecho().
Ocultar o cursor usando curs_set(0).
Gerar um número aleatório entre 0 e 6 para determinar a peça inicial.
Chamar a função game() em um loop infinito até que o usuário escolha sair.
Liberar a memória alocada para a variável name usando free().
Finalizar a tela do terminal usando endwin().
Em resumo, a função main() é responsável por inicializar o ambiente de execução, solicitar informações ao usuário, chamar a função game() e finalizar o ambiente de execução.

`////////////////////////////////////////////////////////////////////////////`

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

© Ismael dos Santos & Mateus Garcia - UERN (Universidade Do Rio Grande do Norte), 2024