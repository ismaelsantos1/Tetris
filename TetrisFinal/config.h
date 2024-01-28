//Sistema de pontuação para os jogadores
#define SCORE (100*cleared+75*(cleared/2)+125*(cleared/3)+150*(cleared/4))* level
/*
Formula para calcular o intervalo de queda de cada peça, foi feito propositalmente feito para a peça depender do atraso. Assim, quanto maior o nível menos movimentos o jogador poderá fazer nas quedas. Isso torna o jogo mais difícil a cada nível e força o player a pensar no que fazer a seguir
*/
#define INTERVALODROP (DELAY/1000) * ((300-level*13/5))
//delay é o intervalo entre dois comandos, isso evita forçar demais o processador
#define DELAY 7777
#define MAXLEVEL 30
//numero de linhas que vão ser limpas para cada nível acima
#define LINESPLVLUP 10