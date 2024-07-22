//
// Created by Daniel Rouxinol - 2018016929 on 4/29/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <synchapi.h>
#include "Jogo.h"

void initMatriz_secundaria(char matriz[3][3]){

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) {
            matriz[i][j] = ' ';
        }
    }
}
void Mostra_Linha(char matriz[3][3],int linha){
    for (int i = 0; i < 3; i++) {
        printf(" %c ",matriz[linha][i]);
        if(i != 2){
            printf("|");
        }

    }
}
void MostrarJogo(Jogo **p){

    int k = 0;
    int cont = 0;
    if(p != NULL) {

        printf("\n");
        for (int i = 0; i < 3; i++) {
            k = 0;
            if(cont == 3){
                break;
            }
            for(int o = 0;o<3;o++){
                for (int j = 0; j < 3; j++) {
                    Mostra_Linha(p[i][j].Matriz, k);

                }
                k++;
                if(k != 3){
                    printf("\n---+---+---");
                    printf("---+---+---");
                    printf("---+---+---\n");
                }
                else {
                    printf("\n");
                }

            }
                cont++;
            printf("\n\n");
        }
    }
    else {
        printf("[ERRO] Matriz esta a NULL\n\n");
    }
}
int PrimeiroJogar(){
    /* Define o primeiro jogador (aleatório) */
    return rand() % 2;
}
int Verifica_vitoria(char letra, char matriz[3][3]){ //Se houver vitoria retorna 1
    if((matriz[0][0] == letra && matriz[0][1] == letra && matriz[0][2] == letra) || //1ª linha
       (matriz[1][0] == letra && matriz[1][1] == letra && matriz[1][2] == letra) || //2ª linha
       (matriz[2][0] == letra && matriz[2][1] == letra && matriz[2][2] == letra)){ // 3ª linha
        return 1;
    }else if((matriz[0][0] == letra && matriz[1][0] == letra && matriz[2][0] == letra) || //1ª coluna
             (matriz[0][1] == letra && matriz[1][1] == letra && matriz[2][1] == letra) || //2ª coluna
             (matriz[0][2] == letra && matriz[1][2] == letra && matriz[2][2] == letra)){ // 3ª coluna
        return 1;
    }else if((matriz[0][0] == letra && matriz[1][1] == letra && matriz[2][2] == letra) || //diagonal 1
             (matriz[0][2] == letra && matriz[1][1] == letra && matriz[2][0] == letra)){ //diagonal 2
        return 1;
    }else{
        return 0;
    }
}
char troca(char c){
    if(c == 'O'){
        c = 'X';
    }
    else if(c == 'X'){
        c = 'O';
    }
    return c;
}
bool check_tabuleiro(int continua){
    if(continua == 0){
        return true;
    }
    return false;
}
void calcula_tabuleiro(int numero, int *l, int *c){

    switch (numero) {
        case 1: *l = 0; *c = 0;
            break;
        case 2: *l = 0; *c = 1;
            break;
        case 3: *l = 0; *c = 2;
            break;
        case 4: *l = 1; *c = 0;
            break;
        case 5: *l = 1; *c = 1;
            break;
        case 6: *l = 1; *c = 2;
            break;
        case 7: *l = 2; *c = 0;
            break;
        case 8: *l = 2; *c = 1;
            break;
        case 9: *l = 2; *c = 2;
            break;
        default:
            break;
    }
}
void Mostrajogadores(int jogador_1, int jogador_2){
    printf("\nJogador 1 - '%c'\nJogador 2 - '%c'\n\n",jogador_1,jogador_2);
}
bool Insere_peca(char letra,int l, int c, char m[3][3]){

    if(m[l][c] == 'X' || m[l][c] == 'O'){
        return false;
    }

    m[l][c] = letra;
    return true;

}
void Get_Posicoes(Jogo **p, char letra, const int * const x, const int * const y, int *l, int *c){
    int flag = 0;
    int linhas,colunas;

    //invalido no que diz respeito a nao caber nas dimensoes
        printf("\nInsira a as posicoes que pretende inserir a peca:",letra);
        fflush(stdin);
        scanf("(%d,%d)",&linhas,&colunas);
    do {
        if(linhas > 2 || colunas > 2 || linhas < 0 || colunas < 0){
            printf("\nNumero invalido\nInsira outro valor:");
            fflush(stdin);
            scanf("(%d,%d)",&linhas,&colunas);
        }
    }while(linhas > 2 || colunas > 2 || linhas < 0 || colunas < 0);

    do{ //invalido no que diz respeito a uma celula ja estar cheia
        flag = 0;
        if(!Insere_peca(letra,linhas,colunas,p[*x][*y].Matriz)){

            printf("Essa posicao ja se econtra cheia\nInsira novamente: ");
            fflush(stdin);
            scanf("(%d,%d)",&linhas,&colunas);

            do {
                if(linhas > 2 || colunas > 2 || linhas < 0 || colunas < 0){
                    printf("\nNumero invalido\nInsira outro valor:");
                    fflush(stdin);
                    scanf("(%d,%d)",&linhas,&colunas);
                }
            }while(linhas > 2 || colunas > 2 || linhas < 0 || colunas < 0);
            flag = 1;
        }
    }while(flag);

    if(p[linhas][colunas].continua != 0){
        printf("O tabuleiro [%d] ja se encontra terminado...Escolhendo outro\n",translate(linhas,colunas));
        for(int i=0;i<3;i++){
            Sleep(1000);
            printf(".");
        }
       linhas = rand() % 3;
       colunas = rand() % 3;
        printf("Escolheu-se o tabuleiro [%d]", translate(linhas,colunas));
    }

   *l = linhas;
   *c = colunas;
}
void verifica_disp_tabuleiro(Jogo **p, int *x, int *y){ //NAO PODE SER CONST PQ NAO CONSEGUES MANDAR PARA OUTRAS FUNCOES
    int flag_tabuleiro = 0;
    int n;

    if(p[*x][*y].continua != 0){
        do {
            flag_tabuleiro = 0;
            do {
                printf("Qual o tabuleiro que pretende jogar?\nOpcao:");
                fflush(stdin);
                scanf("%d", &n);
                if(n < 0 || n > 9){
                    printf("\nNumero invalido\nInsira outro valor:");
                }
            }while(n <= 0 || n > 9);

            calcula_tabuleiro(n, x, y); //retorna linha e coluna do tabuleiro que se escolheu
            if(!check_tabuleiro(p[*x][*y].continua)){ //verifica se tabuleiro esta disponivel
                printf("O tabuleiro que escolheu ja se encontra comlpeto!\n");
                flag_tabuleiro = 1;
            }
        }while(flag_tabuleiro);

        printf("\n\nTabuleiro [%d] escolhido!\n",n);
        return;
    }
}
bool Verifica_Empate(char matriz[3][3]){ //Se estiver empatado retorna 0

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(matriz[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}
void AI(Jogo **p, int *x, int *y){
    int flag_tabuleiro = 0;
    int n;
    do {
        flag_tabuleiro = 0;
        printf("\nEscolhendo o tabuleiro");
        for(int i=0;i<3;i++){
            Sleep(1000);
            printf(".");
        }
        n = rand() % 1 + 9;
        printf("Escolhi o tabuleiro numero %d\n\n",n);
        calcula_tabuleiro(n, x, y);
        if(!check_tabuleiro(p[*x][*y].continua)){
            flag_tabuleiro = 1;
        }
    }while(flag_tabuleiro);
}
void Vitoria(Jogo **p, int x, int y, bool *jog_vencedor, char letra){
    *jog_vencedor = true;
    MostrarJogo(p);
    printf("O jogador '%c' ganhou o jogo no tabuleiro [%d]!!\n",letra, translate(x,y));
    p[x][y].continua = 1;
    p[x][y].letra_venc = letra;
}
void Empate(Jogo **p, int *x, int *y){
    int n;
    MostrarJogo(p);

    do{
        n = rand() % 9 + 1;
        calcula_tabuleiro(n,x,y);
    }while(!check_tabuleiro(p[*x][*y].continua));
    printf("Jogo empatado!!!\nEscolhendo proximo tabuleiro");
    for(int i=0;i<3;i++){
        Sleep(1000);
        printf(".");
    }
    printf("\n\nTabuleiro [%d] escolhido!\n",n);
    p[*x][*y].letra_venc = 'E';
    p[*x][*y].continua = 1;
}
BOOL Verifica_MP(Jogo **p,char *vencedor, char *jog1, char *jog2){

   char matriz_auxiliar[3][3]; //matriz que contem as letras vencedoras de cada tabuleiro

   for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           matriz_auxiliar[i][j] = p[i][j].letra_venc;
       }
   }

    if(Verifica_vitoria(*jog1,matriz_auxiliar)){
        *vencedor = *jog1;
        return true;
    }
    else if(Verifica_vitoria(*jog2,matriz_auxiliar)){
        *vencedor = *jog2;
        return true;
    }
    if(Verifica_Empate(matriz_auxiliar)){
        *vencedor = 'E';
        return true;
    }

return false;
}
void Mostra_vencedor(char letra){
    printf("\nO jogador '%c' venceu o jogo. O perdedor paga dois finos.\n\n",letra);
}
void GetNome(char nome[]){

    printf("Nome do ficheiro de texto: ");
    scanf("%s",nome);
}
BOOL Guarda_fich_texto(Lista *p){
    FILE *fp;
    char nome[50];
    char str[1024];
    Lista *aux = p;

    GetNome(nome);

    strcat(nome,".txt");

    fp = fopen(nome, "w");

    if(fp == NULL){
        printf("\nErro ao guardar no ficheiro de texto...\n\n");
        return FALSE;
    }
    else {
        while(aux != NULL){
            show_all(aux,str);
            fputs(str,fp);
            aux = aux->next;
        }
    }
    fclose(fp);
    return TRUE;
}
void menu_inicial(const int *n){
    printf("\nBem vindo ao jogo do galo ultimate!\n");
    printf("[1] - SinglePlayer\n[2] - Multiplayer\nOpcao:");
    do{
        scanf("%d",&(*n));
        fflush(stdin);
        if((*n) > 2 || (*n) < 1){
            printf("Numero invalido!Tente outro valor.\nOpcao:");
        }
    }while((*n) > 2 || (*n) < 1 && isdigit(*n) == 0);
}
int menu(){
    int n;
    printf("[1] - Jogar\n[2] - Mostrar Jogada\n[3] - Sair\nOpcao:");
    do{
        fflush(stdin);
        scanf("%d",&n);
        fflush(stdin);
        if(n > 3 || n < 1){
            printf("Numero invalido!Tente outro valor.\nOpcao:");
        }
    }while(n > 3 || n < 1 && isdigit(n) == 0);

    return n;
}
int Get_K(){
    int k;
    printf("Digite o numero de jogadadas que quer visualizar: ");
    do{
        scanf("%d",&k);
        if(k > 10 || k < 1){
            printf("Numero invalido...\n");
        }
    }while(k > 10 || k < 1);

    return k;
}