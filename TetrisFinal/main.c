/*
Vai poder ser notado muitos números 'mágicos' flutuando nesse código, também poderá ser notado que a maioria deles são limpos. A maioria deles são simplesmente compensações. Alguns do final da tela, alguns do ponto fixo, mas eram muitos para se livrar de todos. Alguns estão aqui apenas para garantir qque o número de adequado de bytes seja usado. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>//pesquisar sobre
#include <time.h>
#include <ncurses.h>
#include <unistd.h>//pesquisar sobre

//my libs
#include "config.h"
#include "comandos.h"
//#include "mapa.c" 

/*MAPA m;
PECA pecas[7];

int atingiuChao = 0;

int acabou(){
    return 0;

}


void limpaAnterior(PECA* p, MAPA* m, int anteriorx, int anteriory){
    for(int i = 0; i < p->linhas; i++)
        for(int j = 0; j < p->colunas; j++)

            m->matriz[anteriorx + i][anteriory+ j] = '.';

}
void atualizaMapa(PECA* p, MAPA* m){

    for(int i = 0; i < p->linhas; i++)
        for(int j = 0; j < p->colunas; j++)

            m->matriz[p->ponto.x + i][p->ponto.y + j] = p->bloco[i][j];

}

int verificaChao(PECA *p, MAPA *m){
    if(p->ponto.x >= m->linhas - p->linhas){
        atingiuChao = 1;
        return 0;
    }

    return 1;
}

int verificaColisaoPeca(PECA *p, MAPA *m){

    for(int j = 0; j < p->colunas; j++){
        if(m->matriz[p->ponto.x + p->linhas][p->ponto.y + j] == ']' || m->matriz[p->ponto.x + p->linhas][p->ponto.y + j] == '['){
            atingiuChao = 1;
            return 0;
        }
    }

    return 1;
}


void move(PECA* p, MAPA* m, char direcao) {

    int anteriorx = p->ponto.x;
    int anteriory = p->ponto.y;

    limpaAnterior(p, m, anteriorx, anteriory);
    switch(direcao){
        case 'a':
            if(p->ponto.y > 0 && verificaChao(p, m) && verificaColisaoPeca(p, m))
                p->ponto.y--;
            break;
        case 'd':
            if(p->ponto.y + 1 < m->colunas - p->colunas && verificaChao(p, m) && verificaColisaoPeca(p, m))
                p->ponto.y++;
            break;
        case 's':
            if(verificaChao(p, m) && verificaColisaoPeca(p, m))
                p->ponto.x++;
            break;
        default:
            break;
    }


    atualizaMapa(p, m);
}

int main() {
    lemapa(&m);
    lepecas(pecas);

    int aleatorio;

    do {
        srand(time(NULL));
        aleatorio = rand() % 7;
//        printf("aleatorio = %d\n", aleatorio);
        atingiuChao = 0;

        while (!atingiuChao) {
            system("cls");
            imprimemapa(&m);

            char comando;
            comando = getchar();

            move(&pecas[aleatorio], &m, comando);
            //sleep(60);
        }
        atingiuChao = 0;


    } while (!acabou());

    liberapeca(&pecas[aleatorio]);
    liberamapa(&m);
    return 0;
}
*/

//NÃO MUDA ESSA PORRA
//altura e largura de onde vai rolar a brincadeira
#define WIDTH 25
#define HEIGHT 24
#define TOPLSITMAXLINELENGTH 34

//inicia variáveis
char peca;
char *name;


//set flags para valores pré-definidos
int level, score, showtext = 1, next, shownext =1, end, clrlines=0;
int starlevel, dropped=0;

int pontofixado[2] = {0};

//A tela é dividida entre 3 seções: direita, esquerda e centro
char esquerda[HEIGHT][WIDTH] = {0};
char centro[HEIGHT][WIDTH] = {0};
char direita[HEIGHT][WIDTH] = {0};

//todas as possibilidades dos brinquedos

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

void mostra_prox(){
    //essa função vai mostrar os próximos objetos

    switch(next){
        case 0:
            memcpy(esquerda[11]+WIDTH-10, TetrominoI[1]+8, 8);
            return;
        
        case 1:
            memcpy(esquerda[10]+WIDTH-8, TetrominoJ[0]+12, 2);
            memcpy(esquerda[11]+WIDTH-8, TetrominoJ+8, 6);
            return;
        
        case 2:
            memcpy(esquerda[10]+WIDTH-4, TetrominoL[0]+12, 2);
            memcpy(esquerda[11]+WIDTH-8, TetrominoL[1]+8, 6);
            return;

        case 3:
            memcpy(esquerda[10]+WIDTH-6, TetrominoO[0]+10,4);
            memcpy(esquerda[11]+WIDTH-8, TetrominoO[1]+8, 4);
            return;
        
        case 4:
            memcpy(esquerda[10]+WIDTH-6, TetrominoS[0]+10, 4);
            memcpy(esquerda[11]+WIDTH-8, TetrominoS[1]+10, 4);
            return;
        
        case 5:
            memcpy(esquerda[10]+WIDTH-6, TetrominoT[0]+10, 2);
            memcpy(esquerda[11]+WIDTH-8, TetrominoT[1]+8, 6);
            return;
        
        case 6:
            memcpy(esquerda[10]+WIDTH-8, TetrominoZ[0]+8, 4);
            memcpy(esquerda[11]+WIDTH-6, TetrominoZ[1]+10, 4);
            return;
    }
}

void updatescrn(){
    //atualiza a tela
    system("clear");
    printf("\n"); //funciona igual ao printf

    for(int i=2; i<HEIGHT; i++){

        if(shownext) mostra_prox();
        printf("%s", esquerda[i]);
        printf("%s", centro[i]);
        
        if(shownext) printf("%s",  direita[i]);
        printf("\n");
    }
    refresh();
    /*
    atualiza a coleção Parameters para o objeto Command de um procedimento armazenado.
    */
    if(shownext){
        memcpy(esquerda[10]+WIDTH-10, "        ", 8);
        memcpy(esquerda[11]+WIDTH-10, "        ", 8);
    }
}

void updatescore(){
    //updates score
    char *tmp=malloc(sizeof *tmp * 15); //alocando memória
    sprintf(tmp, "%-14d", score);
    memcpy(esquerda[7]+9, tmp, 14);
    free(tmp);
}

void toplist(){
    //mostra os top jogadores

    char *buffer = malloc(sizeof *buffer * TOPLSITMAXLINELENGTH);

    FILE *f;
    clear();

    if(!(f=fopen("toplist", "r")))
        printf("\n\n\n   Lista dos Top jogadores não existe! Sua pontuação precisa ser maior do que 0 para ser adicionado");
    
    else{
        printf("\n");
        while(fgets(buffer, TOPLSITMAXLINELENGTH, f) != NULL)
        printf("                           %s\n", buffer);
        fclose(f);
    }

    refresh();
    free(buffer);
    getch();
}

void addscore(){
    //adiciona pontução à lista dos maiores pontos se necessário

    if(!score) return;
    FILE *f;
    if(!(f=fopen("toplist", "r"))){
        if(!(f=fopen("toplist", "w")))
            exit(1);
        fprintf(f, "NOME         LVL SCORE              \n%-13s %2d %-14d\n", name, level, score);
        fclose(f);
        return;
    }
    f=fopen("toplist", "r");
    int num, added = 0;
    char *buffer = malloc(sizeof *buffer *TOPLSITMAXLINELENGTH);
    FILE *tmp;
    if(!(tmp=fopen("tmp", "a+")))
        exit(1);
    int cntr = 21;
    while(fgets(buffer, TOPLSITMAXLINELENGTH, f) != NULL && --cntr){
        num = strtol(buffer+18, NULL, 10);
        //strtol converte string num inteiro longo
        if(!added && score>num && num !=0){
            fprintf(tmp, "%-13s  %2d %-14d\n", name, level, score);
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

int gamerover(){
    //printa na teela "game over"
    //nodelay(stdscr, FALSE);
    if(!end) addscore();
    end=1;
    memcpy(esquerda[9], "    __      __      ___ \0"
                "  /'_ `\\  /'__`\\  /' __`\0"
                " /\\ \\L\\ \\/\\ \\L\\.\\_/\\ \\/\\\0"
                " \\ \\____ \\ \\__/.\\_\\ \\_\\ \0"
                "  \\/___L\\ \\/__/\\/_/\\/_/\\\0"
                "    /\\____/             \0"
                "    \\_/__/              \0", WIDTH*7);
    memcpy(centro[9], "___      __         ___ \0"
                    " __`\\  /'__`\\      / __`\0"
                    " \\/\\ \\/\\  __/     /\\ \\L\\\0"
                    "\\_\\ \\_\\ \\____\\    \\ \\___\0"
                    "/_/\\/_/\\/____/     \\/___\0", WIDTH*5);
    memcpy(direita[9], "  __  __    __  _ __    \0"
                "\\/\\ \\/\\ \\ /'__`/\\`'__\\  \0"
                " \\ \\ \\_/ /\\  __\\ \\ \\/   \0"
                "_/\\ \\___/\\ \\____\\ \\_\\   \0"
                "/  \\/__/  \\/____/\\/_/   \0", WIDTH*5);
    memcpy(centro[16], "    : SAIR    : RESET   \0"
                    "        : TOPLIST       \0", WIDTH*2);
    
    centro [16][4]= EXIT;
    centro[16][3]= RSET;
    centro[17][7]= TPLS;
    clear();
    printf("\n");
    for (int i=2; i<HEIGHT; ++i){
        if(i ==9 || i == 15 || i == 16) attron(COLOR_PAIR(2));
        else if(i==18) attron(COLOR_PAIR(1));
        printf("%s", esquerda[i]);
        if(i==14 || i==15) attron(COLOR_PAIR(1));
        printf("%s", centro[i]);
        printf("%s\n", direita[i]);
    }
    refresh();
    return 1;
}

void checkclr(){
    //confere se a linha deverá ser limpa
    int cleared= 0;
    if(pontofixado[0]>2){
        for(int i=-2; i<2; ++i){
            if(!strncmp(centro[pontofixado[0]+i]+3, "][][][][][][][][][", 18)){
                ++cleared;
                for (int j=pontofixado[0]+i; j>0; --j)
                    memcpy(centro[j]+2, centro[j-1]+2, 20);
            }
        }
        if(cleared){
            score+=SCORE;
            score+=dropped;
            dropped=0;
            updatescore();
            updatescrn();
        }
    }
    clrlines+=cleared;
}

void initpiece(){
    //cria uma nova peca do jogo
    checkclr();
    int current;
    current = next;
    next = rand() % 7;
    switch(current){
        case 0:
            memcpy(centro[0], TetrominoI[0], WIDTH*2);
            pontofixado[0] = 1;
            pontofixado[1]= 12;
            peca = 'I';
            return;

        case 1:
            memcpy(centro[0], TetrominoJ[0], WIDTH*2);
            pontofixado[0] = 1;
            pontofixado[1]= 10;
            peca = 'J';
            return;
        
        case 2:
            memcpy(centro[0], TetrominoL[0], WIDTH*2);
            pontofixado[0] = 1;
            pontofixado[1]=10;
            peca= 'L';
            return;
        
        case 3:
            memcpy(centro[0], TetrominoO[0], WIDTH*2);
            pontofixado[0] = 1;
            pontofixado[1]= 10;
            peca = 'O';
            return;
        
        case 4:
            memcpy(centro[0], TetrominoS[0], WIDTH*2);
            pontofixado[0]= 0;
            pontofixado[1]=10;
            peca= 'S';
            return;

        case 5:
            memcpy(centro[0], TetrominoT[0], WIDTH*2);
            pontofixado[0] = 1;
            pontofixado[1]=10;
            peca='T';
            return;

        case 6:
            memcpy(centro[0], TetrominoZ[0], WIDTH*2);
            pontofixado[0] = 0;
            pontofixado[1]=10;
            peca='Z';
            return;
    }
}

void rotate(){
    //rotaciona a peça atual no jogo
    switch(peca){
        case 'I':
            if(centro[pontofixado[0]+1][pontofixado[1]]=='['||centro[pontofixado[0]+1][pontofixado[1]]=='='||centro[pontofixado[0]-1][pontofixado[1]]=='['||centro[pontofixado[0]-2][pontofixado[1]]=='[') return;
            
            memcpy(centro[pontofixado[0]-2]+pontofixado[1], centro[pontofixado[0]]+pontofixado[1], 2);

            memcpy(centro[pontofixado[0]-1]+pontofixado[1], centro[pontofixado[0]]+pontofixado[1], 2);

            memcpy(centro[pontofixado[0]]+pontofixado[1]-4, TetrominoI[0]+pontofixado[1]+2, 2);

            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2, TetrominoI[0]+pontofixado[1]+2, 2);

            memcpy(centro[pontofixado[0]+1]+pontofixado[1], centro[pontofixado[0]]+pontofixado[1], 2);
            peca = 'i';
            return;
        
        case 'i':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='['|| centro[pontofixado[0]][pontofixado[1]+2]=='!' || centro[pontofixado[0]][pontofixado[1]-2]=='[' || centro[pontofixado[0]][pontofixado[1]-4]=='[' || centro[pontofixado[0]][pontofixado[1]-4]=='<') return;

            memcpy(centro[pontofixado[0]-2]+pontofixado[1], TetrominoI[0]+pontofixado[1], 2);

            memcpy(centro[pontofixado[0]-1]+pontofixado[1], TetrominoI[0]+ pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4, TetrominoI[1]+8, 4);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2, TetrominoI[1]+12, 2);

            memcpy(centro[pontofixado[0]+1]+pontofixado[1], TetrominoI[0]+pontofixado[1], 2);
            peca ='I';
            return;

        case 'J':
            if(centro[pontofixado[0]+1][pontofixado[1]]=='[' || centro[pontofixado[0]+1][pontofixado[1]]=='=' || centro[pontofixado[0]-1][pontofixado[1]]=='['|| centro[pontofixado[0]-1][pontofixado[1]+2]=='[') return;

            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2, TetrominoO[0]+8, 6);

            memcpy(centro[pontofixado[0]]+pontofixado[1]-2, TetrominoI[0]+pontofixado[1]-2, 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2, TetrominoI[0]+pontofixado[1]+2, 2);
            
            memcpy(centro[pontofixado[0]+1]+pontofixado[1], centro[pontofixado[0]]+pontofixado[1], 2);
            peca ='K';
            return;
    
        case 'K':

            if(centro[pontofixado[0]][pontofixado[1]-2]=='[' || centro[pontofixado[0]][pontofixado[1]-2]=='<' || centro[pontofixado[0]][pontofixado[1]+2]=='[' || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            
            memcpy(centro[pontofixado[0]-1]+pontofixado[1], TetrominoI[0]+pontofixado[1], 4);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2, centro[pontofixado[0]]+pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2, centro[pontofixado[0]]+pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],TetrominoT[0]+8, 4);
            peca ='j';
            return;
            
        case 'j':
            if(centro[pontofixado[0]+1][pontofixado[1]]=='[' || centro[pontofixado[0]+1][pontofixado[1]-2]=='[' || centro[pontofixado[0]-1][pontofixado[1]]=='[') return;
            
            memcpy(centro[pontofixado[0]-1]+pontofixado[1], centro[pontofixado[0]]+pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2, TetrominoI[0]+pontofixado[1]-2, 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2, TetrominoI[0]+pontofixado[1]+2, 2);
            
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2, TetrominoO[0]+10, 6);
            peca ='k';
            return;
    
        case 'k':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='[' || centro[pontofixado[0]][pontofixado[1]+2]=='!' || centro[pontofixado[0]][pontofixado[1]-2]=='[' || centro[pontofixado[0]-1][pontofixado[1]-2]=='[') return;
            
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,TetrominoT[0]+10, 4);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2, centro[pontofixado[0]]+pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2, centro[pontofixado[0]]+pontofixado[1], 2);
            
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2, TetrominoI[0]+pontofixado[1]-2, 4);
            peca ='J';
            return;

    case 'L':
        if(centro[pontofixado[0]+1][pontofixado[1]]=='[' || centro[pontofixado[0]+1][pontofixado[1]]=='=' || centro[pontofixado[0]-1][pontofixado[1]]=='[' || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;

        memcpy(centro[pontofixado[0]-1]+pontofixado[1], TetrominoT[0]+10, 4);
        
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2, TetrominoI[0]+pontofixado[1]-2, 2);
        
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2, TetrominoI[0]+pontofixado[1]+2, 2);
        
        memcpy(centro[pontofixado[0]+1]+pontofixado[1], TetrominoO[0]+10, 4);
        peca ='M';
        return;

    case 'M':
        if(centro[pontofixado[0]][pontofixado[1]-2]=='[' || centro[pontofixado[0]][pontofixado[1]-2]=='<' || centro[pontofixado[0]][pontofixado[1]+2]=='[' || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
        
        memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                TetrominoI[0]+pontofixado[1], 2);
        
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                TetrominoT[0]+10, 6);
        peca ='l';
        return;
    
    case 'l':
        if(centro[pontofixado[0]-1][pontofixado[1]]=='['
            || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
            || centro[pontofixado[0]+1][pontofixado[1]]=='[') return;
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                TetrominoT[0]+8, 4);
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                TetrominoI[0]+pontofixado[1]-2, 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                TetrominoI[0]+pontofixado[1]+2, 2);
        memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                TetrominoO[0]+10, 4);
        peca ='m';
        return;
    
    case 'm':
        if(centro[pontofixado[0]][pontofixado[1]+2]=='['
            || centro[pontofixado[0]][pontofixado[1]+2]=='!'
            || centro[pontofixado[0]][pontofixado[1]-2]=='['
            || centro[pontofixado[0]-1][pontofixado[1]+2]=='[') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                TetrominoT[0]+6, 6);
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                TetrominoI[0]+pontofixado[1], 2);
        peca ='L';
        return;
    
    case 'S':
        if(centro[pontofixado[0]-1][pontofixado[1]]=='['
            || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                centro[pontofixado[0]]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                TetrominoT[0]+6, 6);
        peca = 's';
        return;
    
    case 's':
        if(centro[pontofixado[0]+1][pontofixado[1]]=='['
            || centro[pontofixado[0]+1][pontofixado[1]-2]=='<'
            || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                TetrominoI[0]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                TetrominoO[0]+10, 6);
        peca = 'S';
        return;
    
    case 'T':
        if(centro[pontofixado[0]+1][pontofixado[1]]=='['
            || centro[pontofixado[0]+1][pontofixado[1]]=='=') return;
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                TetrominoI[0]+pontofixado[1]-2, 2);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                centro[pontofixado[0]]+pontofixado[1], 2);
        peca ='U';
        return;
        
    case 'U':
        if(centro[pontofixado[0]][pontofixado[1]-2]=='['
            || centro[pontofixado[0]][pontofixado[1]-2]=='<') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                TetrominoI[0]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        peca ='t';
        return;
        
    case 't':
        if(centro[pontofixado[0]-1][pontofixado[1]]=='[') return;
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                TetrominoI[0]+pontofixado[1]+2, 2);
        memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                centro[pontofixado[0]]+pontofixado[1], 2);
        peca ='u';
        return;
        
    case 'u':
        if(centro[pontofixado[0]][pontofixado[1]+2]=='['
            || centro[pontofixado[0]][pontofixado[1]+2]=='!') return;
        memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                TetrominoI[0]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        peca ='T';
        return;
        
    case 'Z':
        if(centro[pontofixado[0]-1][pontofixado[1]+2]=='['
            || centro[pontofixado[0]][pontofixado[1]+2]=='[') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                TetrominoO[0]+8, 6);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                TetrominoI[0]+pontofixado[1]+2, 2);
        peca = 'z';
        return;
        
    case 'z':
        if(centro[pontofixado[0]][pontofixado[1]-2]=='['
            || centro[pontofixado[0]][pontofixado[1]-2]=='<'
            || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
        memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                TetrominoI[0]+pontofixado[1]+2, 2);
        memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                TetrominoO[0]+10, 6);
        memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                centro[pontofixado[0]]+pontofixado[1], 2);
        peca = 'Z';
        return;
    }
}

void moveleft(){
  //move a atual peça para a esquerda
    switch(peca){
        
        case 'I':
            if(centro[pontofixado[0]][pontofixado[1]+-6]=='['
                || centro[pontofixado[0]][pontofixado[1]-6]=='<') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-6,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            pontofixado[1]-=2;
            return;
            
        case 'i':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='<') return;
            for(int i=-2; i<2; ++i){
                if(centro[pontofixado[0]+i][pontofixado[1]-2]=='[') return;
            }
            for(int i=-2; i<2; ++i){
                memcpy(centro[pontofixado[0]+i]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            }
            pontofixado[1]-=2;
            return;

        case 'J':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-4]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            pontofixado[1]-=2;
            return;
        
        case 'K':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;
        
        case 'j':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]+1][pontofixado[1]]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;
        
        case 'k':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-4]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]-=2;
            return;
        
        case 'L':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            pontofixado[1]-=2;
            return;
        
        case 'M':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 2);
            pontofixado[1]-=2;
            return;
        
        case 'l':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]+1][pontofixado[1]-4]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-4,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;
        
        case 'm':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]-1][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]-1][pontofixado[1]-4]=='[') return;
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]-=2;
            return;
            
        case 'O':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    centro[pontofixado[0]-1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            pontofixado[1]-=2;
            return;

        case 'S':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-4]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-4]=='<') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-4,
                    centro[pontofixado[0]+1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]-=2;
            return;

        case 's':
            if(centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoO[0]+10, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;

        case 'T':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]-=2;
            return;

        case 'U':
            if(centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoO[0]+10, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;

        case 't':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    TetrominoT[0]+10, 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;

        case 'u':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]-1][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    TetrominoO[0]+10, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;
        
        case 'Z':
            if(centro[pontofixado[0]][pontofixado[1]-4]=='['
                || centro[pontofixado[0]][pontofixado[1]-4]=='<'
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]+1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            pontofixado[1]-=2;
            return;

        case 'z':
            if(centro[pontofixado[0]-1][pontofixado[1]]=='['
                || centro[pontofixado[0]][pontofixado[1]-2]=='<'
                || centro[pontofixado[0]][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoO[0]+10, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+10, 4);
            pontofixado[1]-=2;
            return;
    }
}

void moveright(){
  //move a atual peça para a direita
    switch(peca){
        case 'I':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-4,
                    TetrominoI[0]+pontofixado[1]-4, 2);
            pontofixado[1]+=2;
            return;

        case 'i':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='!') return;
            for(int i=-2; i<2; ++i){
                if(centro[pontofixado[0]+i][pontofixado[1]+2]=='[') return;
            }
            for(int i=-2; i<2; ++i){
                memcpy(centro[pontofixado[0]+i]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            }
            pontofixado[1]+=2;
            return;

        case 'J':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            pontofixado[1]+=2;
            return;

        case 'K':
            if(centro[pontofixado[0]-1][pontofixado[1]+4]=='['
                || centro[pontofixado[0]-1][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'j':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'k':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]][pontofixado[1]+2]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1]+2, 2);
            pontofixado[1]+=2;
            return;

        case 'L':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+4]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1]+4, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            pontofixado[1]+=2;
            return;

        case 'M':
            if(centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='[') return;
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'l':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]+1][pontofixado[1]]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'm':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]][pontofixado[1]+2]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1]+2, 2);
            pontofixado[1]+=2;
            return;

        case 'O':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+4]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+4,
                    centro[pontofixado[0]-1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]+=2;
            return;

        case 'S':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    centro[pontofixado[0]+1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            pontofixado[1]+=2;
            return;

        case 's':
            if(centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoO[0]+8, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'T':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]+=2;
            return;

        case 'U':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoO[0]+8, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 't':
            if(centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+4,
                    TetrominoT[0]+10, 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'u':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]][pontofixado[1]+2]=='!'
                || centro[pontofixado[0]-1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoO[0]+8, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;

        case 'Z':
            if(centro[pontofixado[0]][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+4]=='!') return;
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+4,
                    centro[pontofixado[0]+1]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            pontofixado[1]+=2;
            return;

        case 'z':
            if(centro[pontofixado[0]-1][pontofixado[1]+4]=='['
                || centro[pontofixado[0]][pontofixado[1]+4]=='!'
                || centro[pontofixado[0]][pontofixado[1]+4]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='[') return;
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoO[0]+8, 6);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            pontofixado[1]+=2;
            return;
    }
}

int movedown(){
  //move a peça atual para baixo
    switch(peca){
        case 'I':
            if(centro[pontofixado[0]+1][pontofixado[1]-4]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<4; ++i){
                if(centro[pontofixado[0]+1][pontofixado[1]-4+i*2]=='['){
                    if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                        initpiece();
                        return 0;
                }
            }
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-4,
                    centro[pontofixado[0]]+pontofixado[1]-4, 8);
            memcpy(centro[pontofixado[0]++]+pontofixado[1]-4,
                    TetrominoI[0]+pontofixado[1]-4, 8);
            return 0;
            
        case 'i':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]++ -2]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            return 0;
        
        case 'J':
            if(centro[pontofixado[0]+1][pontofixado[1]-2]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<3; ++i){
                if(centro[pontofixado[0]+1][pontofixado[1]-2+i*2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1]-2, 6);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 4);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            return 0;
        
        case 'K':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 4);
            memcpy(centro[pontofixado[0]++]+pontofixado[1]+2,
                    TetrominoT[0]+10, 2);
            return 0;

        case 'j':
            if(centro[pontofixado[0]+2][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+2][pontofixado[1]+2]=='='
                || centro[pontofixado[0]+1][pontofixado[1]]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 6);
            memcpy(centro[pontofixado[0]++ +1]+pontofixado[1]-2,
                    TetrominoO[0]+10, 4);
            return 0;

        case 'k':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+2][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1]-2,
                    TetrominoO[0]+10, 4);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]++ +1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            return 0;

        case 'L':
            if(centro[pontofixado[0]+1][pontofixado[1]-2]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<3; ++i){
                if(centro[pontofixado[0]+1][pontofixado[1]-2+i*2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1]-2, 6);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 4);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            return 0;

        case 'M':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+2][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    TetrominoO[0]+10, 4);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]++ +1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            return 0;

        case 'l':
            if(centro[pontofixado[0]+2][pontofixado[1]-2]=='['
                || centro[pontofixado[0]+2][pontofixado[1]-2]=='='
                || centro[pontofixado[0]+1][pontofixado[1]]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 6);
            memcpy(centro[pontofixado[0]++ +1]+pontofixado[1],
                    TetrominoO[0]+10, 4);
            return 0;

        case 'm':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    TetrominoT[0]+10, 2);
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 4);
            memcpy(centro[pontofixado[0]++]+pontofixado[1]-2,
                    TetrominoT[0]+10, 2);
            return 0;

        case 'O':
            if(centro[pontofixado[0]+1][pontofixado[1]]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<2; ++i){
                if(centro[pontofixado[0]+1][pontofixado[1]+i*2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 4);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 4);
            return 0;

        case 'S':
            if(centro[pontofixado[0]+2][pontofixado[1]-2]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<2; ++i){
                if(centro[pontofixado[0]+2][pontofixado[1]-2+i*2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1]-2,
                    centro[pontofixado[0]+1]+pontofixado[1]-2, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoS[0]+8, 6);
            memcpy(centro[pontofixado[0]++]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 4);
            return 0;

        case 's':
            if(centro[pontofixado[0]+1][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+2][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]-1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+10, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoO[0]+10, 4);
            memcpy(centro[pontofixado[0]++ +2]+pontofixado[1]+2,
                    TetrominoT[0]+10, 2);
            return 0;

        case 'T':
            if(centro[pontofixado[0]+1][pontofixado[1]-2]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<3; ++i){
                if(centro[pontofixado[0]+1][pontofixado[1]-2+i*2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1]-2, 6);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoT[0]+8, 6);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            return 0;

        case 'U':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1]+2, 2);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            return 0;

        case 't':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]+2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]++]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 6);
            return 0;

        case 'u':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    centro[pontofixado[0]]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 2);
            memcpy(centro[pontofixado[0]++ -1]+pontofixado[1],
                    TetrominoI[0]+pontofixado[1], 2);
            return 0;

        case 'Z':
            if(centro[pontofixado[0]+2][pontofixado[1]]=='='){
                initpiece();
                return 0;
            }
            for(int i=0; i<2; ++i){
                if(centro[pontofixado[0]+2][pontofixado[1]+i*2]=='['
                || centro[pontofixado[0]+1][pontofixado[1]-2]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
                }
            }
            memcpy(centro[pontofixado[0]+2]+pontofixado[1],
                    centro[pontofixado[0]+1]+pontofixado[1], 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1]-2,
                    TetrominoZ[0]+8, 6);
            memcpy(centro[pontofixado[0]++]+pontofixado[1]-2,
                    TetrominoI[0]+pontofixado[1]-2, 4);
            return 0;

        case 'z':
            if(centro[pontofixado[0]+1][pontofixado[1]+2]=='['
                || centro[pontofixado[0]+2][pontofixado[1]]=='='
                || centro[pontofixado[0]+2][pontofixado[1]]=='['){
                if(pontofixado[0]==1 || pontofixado[0]==2) return gamerover();
                initpiece();
                return 0;
            }
            memcpy(centro[pontofixado[0]-1]+pontofixado[1]+2,
                    TetrominoI[0]+pontofixado[1], 2);
            memcpy(centro[pontofixado[0]]+pontofixado[1],
                    TetrominoT[0]+8, 4);
            memcpy(centro[pontofixado[0]+1]+pontofixado[1],
                    TetrominoO[0]+10, 4);
            memcpy(centro[pontofixado[0]++ +2]+pontofixado[1],
                    TetrominoT[0]+10, 2);
            return 0;
    }
    return 0;
}

void init(){
  //vai inciar a tela do jogo

    memcpy(esquerda[0], "                        \0"
                    "                            \0"
                    "                            \0"
                    "  PLAYER:                   \0"
                    "                            \0"
                    "  LEVEL:                    \0"
                    "                            \0"
                    "  SCORE:                    \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0"
                    "                            \0", (HEIGHT)*(WIDTH));
    memcpy(centro[0], "<! . . . . . . . . . .!>\0"
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
    memcpy(direita[0], "                        \0"
                    "                        \0"
                    "                        \0"
                    "    : LEFT     :RIGHT   \0"
                    "         :ROTATE        \0"
                    "    : DROP     :RESET   \0"
                    "    : SHOW/HIDE NEXT    \0"
                    "    : HIDE THIS TEXT    \0"
                    "    : EXIT              \0"
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
    }

    void updatelevel(){
    //updates level
    char *tmp=malloc(sizeof *tmp * 15);
    sprintf(tmp, "%-14d", level);
    memcpy(esquerda[5]+9, tmp, 14);
    free(tmp);
    }

    void setkeybind(){
    //lê as combinações de teclas da configuração

        direita[3][3]= MOVE;
        direita[3][14]= MOVD;
        direita[4][8]= RTOA;
        direita[5][3]= DROP;
        direita[5][14]= RSET;
        direita[6][3]= SNXT;
        direita[7][3]= STXT;
        direita[8][3]= EXIT;
    }

int game(){
    //aqui a mágica acontece
    //nodelay(stdscr, FALSE);
    init();
    setkeybind();
    clear();
    end = 0;
    score = 0;
    level = starlevel;
    clrlines = 0;
    memcpy(esquerda[3]+10, name, strlen(name));
    printf("\n\n\n       Pressione qualquer tecla para iniciar!\n");
    refresh();
    getch();
    updatescore();
    updatelevel();
    initpiece();
    updatescrn();
    ////nodelay(stdscr, TRUE);
    gettimeofday(&t1, NULL);
    while(!usleep(DELAY)){
        
        switch(getch()){
            case DROP:
                if(movedown()) continue;
                ++dropped;
                updatescrn();
                continue;
            
            case EXIT:

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
            
            case RTOA:
                if(end || pontofixado[0]<2) continue;
                rotate();
                updatescrn();
                continue;
            
            case TPLS:
                if(!end) continue;
                toplist();
        }
        
        if(end){
            gamerover();
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
        > INTERVALODROP){
            if(movedown()) continue;
            updatescrn();
            gettimeofday(&t1, NULL);
        }
            
    }
    return 1;
}

int main(void){
    //PRINCIPAL

    name=malloc(sizeof *name * 14);
    srand(time(NULL));
    initscr();
    start_color();
    cbreak();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
    do{
//        clear();
        printf("\n\n\n       Enter starting level (1-%d): ", MAXLEVEL);
        refresh();
        scanf("%d ", &starlevel);
    }while(starlevel<1 || starlevel>MAXLEVEL);
    
        clear();
        printf("\n\n\n       Insira seu nome: ");
        refresh();
        scanf("%13s ", name);
        noecho();
        //curs_set(0);
        next=rand()%7;
        while(!game());
        free(name);
        //endwin();
    
    return 0;
}