//formula para calcular pontos
/*
vai calcular a pontuação com base no número de linhas que são limpas (no caso, cleared)e no atual nível (marcado pelo level)

100 pontos por linha
75 por metade da linha limpa
125 por um terço da linha limpa
150 pontos por um quarto da linha limpa
*/
#define SCORE (100*cleared+75*(cleared/2)+125*(cleared/3)+150*(cleared/4))* level 

/*
Calcula o intervalo de queda do do próximo bloco, em segundos, tendo como base o atraso entre dois comandos 'Delay' e no nível atual do jogador. Quanto maior o nível, menor o intervalo de queda entre blocos, o que torna o jogo mais difícil
*/
#define DROPINTERVAL (DELAY/1000) * ((300 - level*13)/5)
#define DELAY 7777 //define o atraso entre dois comandos, em milissegundos, para não sobrecarregar o processador

#define MAXLEVEL 20 //nível máximo que o jogador pode alcançar
#define LINESPLVLUP 10 //número de linhas que o jogador pode alcançar