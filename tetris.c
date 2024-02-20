#include <ctype.h> //estudar lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> //estudar lib
#include <time.h> //estudar lib
#include <unistd.h> //estudar lib
#include <curses.h> //estudar a lib

#include "comandos.h"
#include "configs.h"


//NÃO MUDA
#define WIDTH 25
#define HEIGHT 24
#define TOPLSITMAXLINELENGTH 34

//init variáveis
char peca;
char *name;
//set flags de valores padrão
int level, score, showtext = 1, next, shownext = 1, end, clrlines = 0;
int startlevel, dropped = 0;
int fixedpoint[2] = {0};
//tela é dividida em 3 seções - left, right and center
char left[HEIGHT][WIDTH] = {0};
char center[HEIGHT][WIDTH] = {0};
char right[HEIGHT][WIDTH] = {0};

//Todos os tetrominos
char TetrominoI[2][WIDTH] = {"<! . . . . . . . . . .!>",
                            "<! . . .[][][][] . . .!>"};

char TetrominoJ[2][WIDTH] = {"<! . . .[] . . . . . .!>",
                            "<! . . .[][][] . . . .!>"};

char TetrominoL[2][WIDTH] = {"<! . . . . .[] . . . .!>",
                            "<! . . .[][][] . . . .!>"};

char TetrominoO[2][WIDTH] = {"<! . . . .[][] . . . .!>",
                            "<! . . . .[][] . . . .!>"};

char TetrominoS[2][WIDTH] = {"<! . . . .[][] . . . .!>",
                            "<! . . .[][] . . . . .!>"};

char TetrominoT[2][WIDTH] = {"<! . . . .[] . . . . .!>",
                            "<! . . .[][][] . . . .!>"};

char TetrominoZ[2][WIDTH] = {"<! . . .[][] . . . . .!>",
                            "<! . . . .[][] . . . .!>"};
struct timeval t1, t2;

void show_next(){
  //function mostra o próximo tetromino
  switch(next){
    case 0:
      memcpy(left[11]+WIDTH-10, TetrominoI[1]+8, 8);
      return;
    case 1:
      memcpy(left[10]+WIDTH-8, TetrominoJ[0]+8, 2);
      memcpy(left[11]+WIDTH-8, TetrominoJ[1]+8, 6);
      return;
    case 2:
      memcpy(left[10]+WIDTH-4, TetrominoL[0]+12, 2);
      memcpy(left[11]+WIDTH-8, TetrominoL[1]+8, 6);
      return;
    case 3:
      memcpy(left[10]+WIDTH-6, TetrominoO[0]+10, 4);
      memcpy(left[11]+WIDTH-6, TetrominoO[1]+10, 4);
      return;
    case 4:
      memcpy(left[10]+WIDTH-6, TetrominoS[0]+10, 4);
      memcpy(left[11]+WIDTH-8, TetrominoS[1]+8, 4);
      return;
    case 5:
      memcpy(left[10]+WIDTH-6, TetrominoT[0]+10, 2);
      memcpy(left[11]+WIDTH-8, TetrominoT[1]+8, 6);
      return;
    case 6:
      memcpy(left[10]+WIDTH-8, TetrominoZ[0]+8, 4);
      memcpy(left[11]+WIDTH-6, TetrominoZ[1]+10, 4);
      return;
  }
}

void updatescrn(){
  //vai atualizar a tela
  clear();
  printw("\n");
  for(int i=2; i<HEIGHT; ++i){
    if(shownext) show_next();
    printw("%s", left[i]);
    printw("%s", center[i]);
    if(showtext) printw("%s", right[i]);
    printw("\n");
  }
  refresh();
  if(shownext){
    memcpy(left[10]+WIDTH-10, "        ", 8);
    memcpy(left[11]+WIDTH-10, "        ", 8);
  }
}

void updatescore(){
  //atualiza a pontuação
  char *tmp=malloc(sizeof *tmp * 15);
  sprintf(tmp, "%-14d", score);
  memcpy(left[7]+9, tmp, 14);
  free(tmp);
}

void toplist(){
  //mostra toplist
  char *buffer=malloc(sizeof *buffer * TOPLSITMAXLINELENGTH);
  FILE *f;
  clear();
  if(!(f=fopen("toplist", "r")))
    printw("\n\n\n    NÃO HÁ UMA LISTA COM OS MELHORES JOGADORES. SUA PONTUAÇÃO PRECISA SER MAIOR DO QUE 0" " PARA SER INCLUÍDO\n");
  else{
    printw("\n");
    while(fgets(buffer, TOPLSITMAXLINELENGTH, f) != NULL)
      printw("                        %s", buffer);
    fclose(f);
  }
  refresh();
  free(buffer);
  getch();
}

void addscore(){
  //add pontos no arquivo de tops se necessário
  if(!score) return;
  FILE *f;
  if(!(f=fopen("toplist", "r"))){
    if(!(f=fopen("toplist", "w")))
      exit(1);
    fprintf(f, "NOME          LVL PONTOS        \n%-13s %2d  %-14d\n", name, level, score);
    fclose(f);
    return;
  }
  f=fopen("toplist", "r");
  int num, added = 0;
  char *buffer=malloc(sizeof *buffer * TOPLSITMAXLINELENGTH);
  FILE *tmp;
  if(!(tmp=fopen("tmp", "a+")))
    exit(1);
  int cntr = 21;
  while(fgets(buffer, TOPLSITMAXLINELENGTH, f) != NULL && --cntr){
    num = strtol(buffer+18, NULL, 10); //ler sobre strtol
    if(!added && score>num && num!=0){
      fprintf(tmp, "%-13s %2d  %-14d\n", name, level, score);
      score=0;
    }
    fputs(buffer, tmp);
  }
  if(cntr && score) fprintf(tmp, "%-13s %2d  %-14d\n", name, level, score);
  fclose(f);
  fclose(tmp);
  remove("toplist");
  rename("tmp", "toplist");
  free(buffer);
}

int gameover(){
  //prints game over na tela
  nodelay(stdscr, FALSE);
  if(!end) addscore();
  end = 1;
  memcpy(left[9], "    __      __      ___ \0"
                  "  /'_ `\\  /'__`\\  /' __`\0"
                  " /\\ \\L\\ \\/\\ \\L\\.\\_/\\ \\/\\\0"
                  " \\ \\____ \\ \\__/.\\_\\ \\_\\ \0"
                  "  \\/___L\\ \\/__/\\/_/\\/_/\\\0"
                  "    /\\____/             \0"
                  "    \\_/__/              \0", WIDTH*7);
  memcpy(center[9], "___      __         ___ \0"
                    " __`\\  /'__`\\      / __`\0"
                    " \\/\\ \\/\\  __/     /\\ \\L\\\0"
                    "\\_\\ \\_\\ \\____\\    \\ \\___\0"
                    "/_/\\/_/\\/____/     \\/___\0", WIDTH*5);
  memcpy(right[9], "  __  __    __  _ __    \0"
                   "\\/\\ \\/\\ \\ /'__`/\\`'__\\  \0"
                   " \\ \\ \\_/ /\\  __\\ \\ \\/   \0"
                   "_/\\ \\___/\\ \\____\\ \\_\\   \0"
                   "/  \\/__/  \\/____/\\/_/   \0", WIDTH*5);
  memcpy(center[16], "    : QUIT    : RESET   \0"
                     "        : TOPLIST       \0", WIDTH*2);
  center[16][3] = toupper(EXT);
  center[16][13] = toupper(RSET);
  center[17][7] = toupper(TPLS);
  clear();
  printw("\n");
  for(int i=2; i<HEIGHT; ++i){
    if(i == 9 || i == 15 || i == 16) attron(COLOR_PAIR(2));
    else if( i == 18) attron(COLOR_PAIR(1));
    printw("%s", left[i]);
    if(i == 14 || i == 15) attron(COLOR_PAIR(1));
    printw("%s", center[i]);
    printw("%s\n", right[i]);
  }
  refresh();
  return 1;
}

void checkclr(){
  //confere se a linha deverá ser limpa
  int cleared = 0;
  if(fixedpoint[0]>2){
    for(int i=-2; i<2; ++i){
      if(!strncmp(center[fixedpoint[0]+i]+3,"][][][][][][][][][", 18)){
        ++cleared;
        for(int j=fixedpoint[0]+i; j>0; --j)
          memcpy(center[j]+2, center[j-1]+2, 20);
      }
    }
    if(cleared){
      score+=SCORE;
      score+=dropped;
      dropped = 0;
      updatescore();
      updatescrn();
    }
  }
  clrlines+=cleared;
}

void initpiece(){
  //inicializar uma nova peça
  checkclr();
  int current;
  current = next;
  next = rand() % 7;
  switch(current){
    case 0:
      memcpy(center[0], TetrominoI[0], WIDTH*2);
      fixedpoint[0] = 1;
      fixedpoint[1] = 12;
      peca = 'I';
      return;
    case 1:
      memcpy(center[0], TetrominoJ[0], WIDTH*2);
      fixedpoint[0] = 1;
      fixedpoint[1] = 10;
      peca = 'J';
      return;
    case 2:
      memcpy(center[0], TetrominoL[0], WIDTH*2);
      fixedpoint[0] = 1;
      fixedpoint[1] = 10;
      peca = 'L';
      return;
    case 3:
      memcpy(center[0], TetrominoO[0], WIDTH*2);
      fixedpoint[0] = 1;
      fixedpoint[1] = 10;
      peca = 'O';
      return;
    case 4:
      memcpy(center[0], TetrominoS[0], WIDTH*2);
      fixedpoint[0] = 0;
      fixedpoint[1] = 10;
      peca = 'S';
      return;
    case 5:
      memcpy(center[0], TetrominoT[0], WIDTH*2);
      fixedpoint[0] = 1;
      fixedpoint[1] = 10;
      peca = 'T';
      return;
    case 6:
      memcpy(center[0], TetrominoZ[0], WIDTH*2);
      fixedpoint[0] = 0;
      fixedpoint[1] = 10;
      peca = 'Z';
      return;
  }
}

void rotate(){
  //girar a peça atual (no sentido horário)
  switch(peca){
    case 'I':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='='
         || center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]-2][fixedpoint[1]]=='[') return;
      
      memcpy(center[fixedpoint[0]-2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             TetrominoI[0]+fixedpoint[1]-4, 4);
      
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='i';
      return;
    case 'i':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<') return;
      
      memcpy(center[fixedpoint[0]-2]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             TetrominoI[1]+8, 4);
      
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[1]+12, 2);
      
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      peca ='I';
      return;
    case 'J':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='='
         || center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='K';
      return;
    case 'K':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      peca ='j';
      return;
    case 'j':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      peca ='k';
      return;
    case 'k':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 4);
      peca ='J';
      return;
    case 'L':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='='
         || center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoO[0]+10, 4);
      peca ='M';
      return;
    case 'M':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 6);
      peca ='l';
      return;
    case 'l':
      if(center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoO[0]+10, 4);
      peca ='m';
      return;
    case 'm':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+6, 6);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      peca ='L';
      return;
    case 'S':
      if(center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+6, 6);
      peca = 's';
      return;
    case 's':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      peca = 'S';
      return;
    case 'T':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='=') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='U';
      return;
    case 'U':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='t';
      return;
    case 't':
      if(center[fixedpoint[0]-1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='u';
      return;
    case 'u':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!') return;
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca ='T';
      return;
    case 'Z':
      if(center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      peca = 'z';
      return;
    case 'z':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      peca = 'Z';
      return;
  }
}

void moveleft(){
  //move a atual peça para a esquerda
  switch(peca){
    case 'I':
      if(center[fixedpoint[0]][fixedpoint[1]+-6]=='['
         || center[fixedpoint[0]][fixedpoint[1]-6]=='<') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-6,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      fixedpoint[1]-=2;
      return;
    case 'i':
    if(center[fixedpoint[0]][fixedpoint[1]-2]=='<') return;
      for(int i=-2; i<2; ++i){
        if(center[fixedpoint[0]+i][fixedpoint[1]-2]=='[') return;
      }
      for(int i=-2; i<2; ++i){
        memcpy(center[fixedpoint[0]+i]+fixedpoint[1]-2,
               TetrominoT[0]+10, 4);
      }
      fixedpoint[1]-=2;
      return;
    case 'J':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-4]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      fixedpoint[1]-=2;
      return;
    case 'K':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'j':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'k':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-4]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]-=2;
      return;
    case 'L':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      fixedpoint[1]-=2;
      return;
    case 'M':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 2);
      fixedpoint[1]-=2;
      return;
    case 'l':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]-4]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-4,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'm':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]-4]=='[') return;
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]-=2;
      return;
    case 'O':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             center[fixedpoint[0]-1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      fixedpoint[1]-=2;
      return;
    case 'S':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-4]=='<') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-4,
             center[fixedpoint[0]+1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]-=2;
      return;
    case 's':
      if(center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'T':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]-=2;
      return;
    case 'U':
      if(center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 't':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             TetrominoT[0]+10, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'u':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]-1][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             TetrominoO[0]+10, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
    case 'Z':
      if(center[fixedpoint[0]][fixedpoint[1]-4]=='['
         || center[fixedpoint[0]][fixedpoint[1]-4]=='<'
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]+1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      fixedpoint[1]-=2;
      return;
    case 'z':
      if(center[fixedpoint[0]-1][fixedpoint[1]]=='['
         || center[fixedpoint[0]][fixedpoint[1]-2]=='<'
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+10, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+10, 4);
      fixedpoint[1]-=2;
      return;
  }
}

void moveright(){
  //move a atual peça para a direita
  switch(peca){
    case 'I':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-4,
             TetrominoI[0]+fixedpoint[1]-4, 2);
      fixedpoint[1]+=2;
      return;
    case 'i':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='!') return;
      for(int i=-2; i<2; ++i){
        if(center[fixedpoint[0]+i][fixedpoint[1]+2]=='[') return;
      }
      for(int i=-2; i<2; ++i){
        memcpy(center[fixedpoint[0]+i]+fixedpoint[1],
               TetrominoT[0]+8, 4);
      }
      fixedpoint[1]+=2;
      return;
    case 'J':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      fixedpoint[1]+=2;
      return;
    case 'K':
      if(center[fixedpoint[0]-1][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]-1][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'j':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'k':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1]+2, 2);
      fixedpoint[1]+=2;
      return;
    case 'L':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+4]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1]+4, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      fixedpoint[1]+=2;
      return;
    case 'M':
      if(center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='[') return;
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'l':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]+1][fixedpoint[1]]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'm':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1]+2, 2);
      fixedpoint[1]+=2;
      return;
    case 'O':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+4]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+4,
             center[fixedpoint[0]-1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]+=2;
      return;
    case 'S':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             center[fixedpoint[0]+1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      fixedpoint[1]+=2;
      return;
    case 's':
      if(center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'T':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]+=2;
      return;
    case 'U':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 't':
      if(center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+4,
             TetrominoT[0]+10, 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'u':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]][fixedpoint[1]+2]=='!'
         || center[fixedpoint[0]-1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
    case 'Z':
      if(center[fixedpoint[0]][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+4]=='!') return;
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+4,
             center[fixedpoint[0]+1]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      fixedpoint[1]+=2;
      return;
    case 'z':
      if(center[fixedpoint[0]-1][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]][fixedpoint[1]+4]=='!'
         || center[fixedpoint[0]][fixedpoint[1]+4]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='[') return;
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoO[0]+8, 6);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      fixedpoint[1]+=2;
      return;
  }
}
int movedown(){
  //move atual peça para baixo
  switch(peca){
    case 'I':
      if(center[fixedpoint[0]+1][fixedpoint[1]-4]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<4; ++i){
        if(center[fixedpoint[0]+1][fixedpoint[1]-4+i*2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-4,
             center[fixedpoint[0]]+fixedpoint[1]-4, 8);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1]-4,
             TetrominoI[0]+fixedpoint[1]-4, 8);
      return 0;
    case 'i':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]++ -2]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      return 0;
    case 'J':
      if(center[fixedpoint[0]+1][fixedpoint[1]-2]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<3; ++i){
        if(center[fixedpoint[0]+1][fixedpoint[1]-2+i*2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1]-2, 6);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 4);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      return 0;
    case 'K':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]][fixedpoint[1]+2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 4);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1]+2,
             TetrominoT[0]+10, 2);
      return 0;
    case 'j':
      if(center[fixedpoint[0]+2][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]+2]=='='
         || center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 6);
      memcpy(center[fixedpoint[0]++ +1]+fixedpoint[1]-2,
             TetrominoO[0]+10, 4);
      return 0;
    case 'k':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+2][fixedpoint[1]-2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1]-2,
             TetrominoO[0]+10, 4);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]++ +1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      return 0;
    case 'L':
      if(center[fixedpoint[0]+1][fixedpoint[1]-2]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<3; ++i){
        if(center[fixedpoint[0]+1][fixedpoint[1]-2+i*2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1]-2, 6);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 4);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      return 0;
    case 'M':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+2][fixedpoint[1]+2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             TetrominoO[0]+10, 4);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]++ +1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      return 0;
    case 'l':
      if(center[fixedpoint[0]+2][fixedpoint[1]-2]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]-2]=='='
         || center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 6);
      memcpy(center[fixedpoint[0]++ +1]+fixedpoint[1],
             TetrominoO[0]+10, 4);
      return 0;
    case 'm':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]][fixedpoint[1]-2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             TetrominoT[0]+10, 2);
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 4);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1]-2,
             TetrominoT[0]+10, 2);
      return 0;
    case 'O':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<2; ++i){
        if(center[fixedpoint[0]+1][fixedpoint[1]+i*2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 4);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 4);
      return 0;
    case 'S':
      if(center[fixedpoint[0]+2][fixedpoint[1]-2]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<2; ++i){
        if(center[fixedpoint[0]+2][fixedpoint[1]-2+i*2]=='['
           || center[fixedpoint[0]+1][fixedpoint[1]+2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1]-2,
             center[fixedpoint[0]+1]+fixedpoint[1]-2, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoS[0]+8, 6);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 4);
      return 0;
    case 's':
      if(center[fixedpoint[0]+1][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+2][fixedpoint[1]+2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+10, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoO[0]+10, 4);
      memcpy(center[fixedpoint[0]++ +2]+fixedpoint[1]+2,
             TetrominoT[0]+10, 2);
      return 0;
    case 'T':
      if(center[fixedpoint[0]+1][fixedpoint[1]-2]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<3; ++i){
        if(center[fixedpoint[0]+1][fixedpoint[1]-2+i*2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1]-2, 6);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoT[0]+8, 6);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      return 0;
    case 'U':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1]+2, 2);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      return 0;
    case 't':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]+2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 6);
      return 0;
    case 'u':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             center[fixedpoint[0]]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 2);
      memcpy(center[fixedpoint[0]++ -1]+fixedpoint[1],
             TetrominoI[0]+fixedpoint[1], 2);
      return 0;
    case 'Z':
      if(center[fixedpoint[0]+2][fixedpoint[1]]=='='){
        initpiece();
        return 0;
      }
      for(int i=0; i<2; ++i){
        if(center[fixedpoint[0]+2][fixedpoint[1]+i*2]=='['
           || center[fixedpoint[0]+1][fixedpoint[1]-2]=='['){
          if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
          initpiece();
          return 0;
        }
      }
      memcpy(center[fixedpoint[0]+2]+fixedpoint[1],
             center[fixedpoint[0]+1]+fixedpoint[1], 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1]-2,
             TetrominoZ[0]+8, 6);
      memcpy(center[fixedpoint[0]++]+fixedpoint[1]-2,
             TetrominoI[0]+fixedpoint[1]-2, 4);
      return 0;
    case 'z':
      if(center[fixedpoint[0]+1][fixedpoint[1]+2]=='['
         || center[fixedpoint[0]+2][fixedpoint[1]]=='='
         || center[fixedpoint[0]+2][fixedpoint[1]]=='['){
        if(fixedpoint[0]==1 || fixedpoint[0]==2) return gameover();
        initpiece();
        return 0;
      }
      memcpy(center[fixedpoint[0]-1]+fixedpoint[1]+2,
             TetrominoI[0]+fixedpoint[1], 2);
      memcpy(center[fixedpoint[0]]+fixedpoint[1],
             TetrominoT[0]+8, 4);
      memcpy(center[fixedpoint[0]+1]+fixedpoint[1],
             TetrominoO[0]+10, 4);
      memcpy(center[fixedpoint[0]++ +2]+fixedpoint[1],
             TetrominoT[0]+10, 2);
      return 0;
  }
  return 0;
}

void init(){
  //inicializa a tela do jogo
  memcpy(left[0], "                        \0"
                  "                        \0"
                  "                        \0"
                  "  PLAYER:               \0"
                  "                        \0"
                  "  NÍVEL:                \0"
                  "                        \0"
                  "  PONTOS:               \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0"
                  "                        \0", (HEIGHT)*(WIDTH));
  memcpy(center[0], "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<! . . . . . . . . . .!>\0"
                    "<!====================!>\0"
                    "  \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\0", (HEIGHT)*(WIDTH));
  memcpy(right[0], "                              \0"
                   "                              \0"
                   "                              \0"
                   "    : ESQUERDA     :DIREITA   \0"
                   "         :GIRAR               \0"
                   "    : DROP     :RESET         \0"
                   "    : MOSTRAR/ESCND NEXT      \0"
                   "    : ESCND ESSE TEXTO        \0"
                   "    : SAIR                    \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0"
                   "                              \0", (HEIGHT)*(WIDTH));
}

void updatelevel(){
  //atualiza a o nível
  char *tmp=malloc(sizeof *tmp * 15);
  sprintf(tmp, "%-14d", level);
  memcpy(left[5]+9, tmp, 14);
  free(tmp);
}

void setkeybind(){
  //reads key bindings from config
    right[3][3]=toupper(MOVE);
    right[3][14]=toupper(MOVD);
    right[4][8]=toupper(ROTA);
    right[5][3]=toupper(DROP);
    right[5][14]=toupper(RSET);
    right[6][3]=toupper(SNXT);
    right[7][3]=toupper(STXT);
    right[8][3]=toupper(EXT);
}

int game(){
  //simula o jogo de tetris
  nodelay(stdscr, FALSE);
  init();
  setkeybind();
  clear();
  end = 0;
  score = 0;
  level = startlevel;
  clrlines = 0;
  memcpy(left[3]+10, name, strlen(name));
  printw("\n\n\n       Pressione qualquer tecla para inciar\n");
  refresh();
  getch();
  updatescore();
  updatelevel();
  initpiece();
  updatescrn();
  nodelay(stdscr, TRUE);
  gettimeofday(&t1, NULL);
  while(!usleep(DELAY)){
    switch(getch()){
      case DROP:
        if(movedown()) continue;
        ++dropped;
        updatescrn();
        continue;
      case EXT:
        return 1;
      case RSET:
        return 0;
      case STXT:
        if(end) continue;
        showtext=!showtext;
        updatescrn();
        continue;
      case SNXT:
        if(end) continue;
        shownext=!shownext;
        updatescrn();
        continue;
      case MOVD:
        if(end) continue;
        moveright();
        updatescrn();
        continue;
      case MOVE:
        if(end) continue;
        moveleft();
        updatescrn();
        continue;
      case ROTA:
        if(end || fixedpoint[0]<2) continue;
        rotate();
        updatescrn();
        continue;
      case TPLS:
        if(!end) continue;
        toplist();
    }
    if(end){
      gameover();
      continue;
    }
    if(clrlines == LINESPLVLUP){
      if(level<MAXLEVEL){
        ++level;
        updatelevel();
        clrlines = 0;
      }
    }
    gettimeofday(&t2, NULL);
    if((((t2.tv_sec-t1.tv_sec) * 1000) + ((t2.tv_usec-t1.tv_usec)/1000)) 
       > DROPINTERVAL){
      if(movedown()) continue;
      updatescrn();
      gettimeofday(&t1, NULL);
    }
  }
  return 1;
}

int main(void){
  //função principal
  name=malloc(sizeof *name * 14);
  srand(time(NULL));
  initscr();
  start_color();
  cbreak();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  do{
    clear();
    printw("\n\n\n       Insira o nível inicial(1-%d): ", MAXLEVEL);
    refresh();
    scanw("%d ", &startlevel);
  }while(startlevel<1 || startlevel>MAXLEVEL);
  clear();
  printw("\n\n\n       Insira seu nome: ");
  refresh();
  scanw("%13s ", name);
  noecho();
  curs_set(0);
  next=rand()%7;
  while(!game());
  free(name);
  endwin();
  return 0;
}
