//
// Created by Daniel Rouxinol - 2018016929 on 5/14/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <synchapi.h>
#include "Jogo.h"

bool Jogar_Single_player(Jogo **p,Lista **head, int n){
    char vez = 'X';
    char vez_comp, vez_jog; //vez do jogador e vez do computador
    bool comp_vencedor = false;
    bool jog_vencedor = false;
    int l = 0,c = 0; //para meter a peça na matriz secundaria
    int x,y; // linhas e colunas da metriz principal
    int flag = 0; //flag para ver se o espaço ja esta ocupado
    char vencedor_jogo = ' ';
    Lista *aux = *head;
    int op;
    int cont = 1;

    if(aux != NULL){
        while(aux->next != NULL){
            aux = aux->next;
        }
        cont = aux->id + 1;
    }

    if(aux != NULL){
        if(aux->jogador == 'X'){
            vez = 'O';
        }
    }

    //O 'X' começa sempre primeiro
    if(PrimeiroJogar()){ //Se for 1
        vez_jog = 'O';
        vez_comp = 'X';
    }else{
        vez_jog = 'X';
        vez_comp = 'O';
    }
    Mostrajogadores(vez_jog,vez_comp);

    if(n == -1){
        n = rand() % 9 + 1;
        calcula_tabuleiro(n,&x,&y);
    }else {
        calcula_tabuleiro(n,&x,&y);
    }

    if(p[x][y].continua == 1){
        do{
            n = rand() % 9 + 1;
            calcula_tabuleiro(n,&x,&y);
        }while(p[x][y].continua == 1);
    }

    while(!Verifica_MP(p, &vencedor_jogo,&vez_jog,&vez_comp)){
        MostrarJogo(p);
        if(vez_jog == vez){ //Se for a vez do jogador
            if(jog_vencedor){
                verifica_disp_tabuleiro(p,&x,&y); //Pergunta ao jogador qual o tabuleiro que quer jogar a seguir
                MostrarJogo(p);
                jog_vencedor = false;
            }
            do {
                printf("\nVez do jogador '%c'\nTabuleiro [%d]\n",vez_jog, translate(x,y));
                op = menu();
                if (op == 1) {
                    Get_Posicoes(p, vez_jog, &x, &y, &l, &c); //Para inserir a peça na matriz
                } else if(op == 2){
                    int k = Get_K();
                    show_list(head,k);
                    MostrarJogo(p);
                }
                else {
                    return false;
                }
            }while(op != 1);
            if(Verifica_vitoria(vez_jog,p[x][y].Matriz)){ //Funcao retorna 1 se ganhar
                Vitoria(p,x,y,&jog_vencedor,vez_jog);
                add_to_list(head,&aux,vez_jog,l,c,x,y,&cont,vez_jog);
                x = l;
                y = c;
                continue;
            }
            if(Verifica_Empate(p[x][y].Matriz)){ //Ser estiver empatado ninguem escolhe, e um numero aleatorio
                Empate(p,&x,&y);
                add_to_list(head,&aux,vez_jog,l,c,x,y,&cont,'E');
                x = l;
                y = c;
                continue;
            }
            add_to_list(head,&aux,vez_jog,l,c,x,y,&cont,' ');
            vez = troca(vez_jog);
            x = l;
            y = c;
        }
        else{
            if(comp_vencedor){
                AI(p,&x,&y);
                MostrarJogo(p);
                comp_vencedor = false;
            }
            printf("\nVez do jogador '%c'\nTabuleiro [%d]\n",vez_comp,translate(x,y));
            l = rand() % 3;
            c = rand() % 3;
            do{
                flag = 0;
                if(!Insere_peca(vez_comp,l,c,p[x][y].Matriz)){
                    flag = 1;
                    l = rand() % 3;
                    c = rand() % 3;
                }
            }while(flag);
            if(Verifica_vitoria(vez_comp,p[x][y].Matriz)){
                Vitoria(p,x,y,&comp_vencedor,vez_comp);
                add_to_list(head,&aux,vez_comp,l,c,x,y,&cont,vez_comp);
                x = l;
                y = c;
                continue;
            }
            else if(Verifica_Empate(p[x][y].Matriz)){ //Ser estiver empatado ninguem escolhe, e um numero aleatorio
                Empate(p,&x,&y);
                add_to_list(head,&aux,vez_comp,l,c,x,y,&cont,'E');
                x = l;
                y = c;
                continue;
            }
            add_to_list(head,&aux,vez_comp,l,c,x,y,&cont,' ');
            vez = troca(vez_comp);
            x = l;
            y = c;
        }
    }
    Mostra_vencedor(vencedor_jogo);
    return true;

}
bool Jogar_Multi_player(Jogo **p,Lista **head, int n){
    char vez = 'X'; // O X COMECA SEMPRE PRIMEIRO
    char vez_jog_1, vez_jog_2; //vez do jogador x e do jogador o
    bool Jog_1_vencedor = false;
    bool Jog_2_vencedor = false;
    int x,y; // linhas e colunas da metriz principal
    int l,c;
    char vencedor_jogo = ' ';
    int op;
    Lista *aux = *head;
    int cont = 1;

    if(aux != NULL){
        while(aux->next != NULL){
            aux = aux->next;
        }
        cont = aux->id + 1;
    }

    //O AUXILIAR ESTA NA ULTIMA CELULA, LOGO SE O O JOGADOR LA FOR O X ENTAO O PROXIMO A JOGAR VAI SER O 'O'
    if(aux != NULL){
        if(aux->jogador == 'X'){
            vez = 'O';
        }
    }


    if(PrimeiroJogar()){ //Se for 1
        vez_jog_1 = 'O';
        vez_jog_2 = 'X';
    }else{
        vez_jog_1 = 'X';
        vez_jog_2 = 'O';
    }

    Mostrajogadores(vez_jog_1,vez_jog_2);

    if(n == -1){
        n = rand() % 9 + 1;
        calcula_tabuleiro(n,&x,&y);
    }else {
        calcula_tabuleiro(n,&x,&y);
    }

    if(p[x][y].continua == 1){
        do{
            n = rand() % 9 + 1;
            calcula_tabuleiro(n,&x,&y);
        }while(p[x][y].continua == 1);
    }

    while(!Verifica_MP(p, &vencedor_jogo,&vez_jog_1,&vez_jog_2)){
        MostrarJogo(p);
        if(vez_jog_1 == vez){ //Se for a vez do jogador 1
            if(Jog_1_vencedor){
                verifica_disp_tabuleiro(p,&x,&y);
                Jog_1_vencedor = false;
            }
            do {
                printf("\nVez do jogador '%c'\nTabuleiro [%d]\n",vez_jog_1,translate(x,y));
                op = menu();
                if (op == 1) {
                    Get_Posicoes(p, vez_jog_1, &x, &y, &l, &c); //Para inserir a peça na matriz

                } else if(op == 2){
                    int k = Get_K();
                    show_list(head,k);
                    MostrarJogo(p);
                }
                else {
                    return false;
                }
            }while(op != 1);
            if(Verifica_vitoria(vez_jog_1,p[x][y].Matriz)){ //Funcao retorna 1 se ganhar
                Vitoria(p,x,y,&Jog_1_vencedor,vez_jog_1);
                add_to_list(head,&aux,vez_jog_1,l,c,x,y,&cont,vez_jog_1);
                x = l;
                y = c;
                continue;
            }
            else if(Verifica_Empate(p[x][y].Matriz)){ //Ser estiver empatado ninguem escolhe, e um numero aleatorio
                Empate(p,&x,&y);
                add_to_list(head,&aux,vez_jog_1,l,c,x,y,&cont,'E');
                x = l;
                y = c;
                continue;
            }
            add_to_list(head,&aux,vez_jog_1,l,c,x,y,&cont,' ');
            vez = troca(vez_jog_1);
            x = l;
            y = c;
        }
        else{
            if(Jog_2_vencedor){//Se for a vez do jogador 2
                verifica_disp_tabuleiro(p,&x,&y);
                Jog_2_vencedor = false;
            }
            do {
                printf("\nVez do jogador '%c'\nTabuleiro [%d]\n",vez_jog_2,translate(x,y));
                op = menu();
                if (op == 1) {
                    Get_Posicoes(p, vez_jog_2, &x, &y, &l, &c); //Para inserir a peça na matriz
                }
                else if(op == 2){
                    int k = Get_K();
                    show_list(head,k);
                    MostrarJogo(p);
                }
                else {
                    return false;
                }
            }while(op != 1);
            if(Verifica_vitoria(vez_jog_2,p[x][y].Matriz)){ //Funcao retorna 1 se ganhar
                Vitoria(p,x,y,&Jog_2_vencedor,vez_jog_2);
                add_to_list(head,&aux,vez_jog_2,l,c,x,y,&cont,vez_jog_2);
                x = l;
                y = c;
                continue;
            }
            else if(Verifica_Empate(p[x][y].Matriz)){ //Ser estiver empatado ninguem escolhe, e um numero aleatorio
                Empate(p,&x,&y);
                add_to_list(head,&aux,vez_jog_2,l,c,x,y,&cont,'E');
                x = l;
                y = c;
                continue;
            }
            add_to_list(head,&aux,vez_jog_2,l,c,x,y,&cont,' ');
            vez = troca(vez_jog_2);
            x = l;
            y = c;
        }
    }
    Mostra_vencedor(vencedor_jogo);
    return true;
}
Jogo **matrix(){
    Jogo **p = (Jogo **)malloc(3 * sizeof(Jogo *));
    for (int i = 0; i < 3; i++) {
        p[i] = (Jogo *)malloc(3 * sizeof(Jogo));
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) {
            initMatriz_secundaria(p[i][j].Matriz);
            p[i][j].letra_venc = ' ';
            p[i][j].continua = 0;
        }
    }
    return p;
}
bool Clean_Linked_List(Lista *head){

    Lista *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
int main() {

    time_t t;
    Jogo **p = matrix();
    int n_jogadores = -1;
    srand((unsigned) time(&t));
    Lista *head = NULL;
    FILE *ptr = NULL;
    int n = -1;
    bool vencedor;

    ptr = check_save_bin();
    if(ptr != NULL){
        head = open_bin_file();
        n = import(head,p);
    }

    menu_inicial(&n_jogadores);

    switch (n_jogadores) {

        case 1:
            vencedor = Jogar_Single_player(p,&head,n);
            if(!vencedor){
                if(save_bin(head)){
                    printf("Jogo guardado com sucesso...\n");
                }
            }
            if(Guarda_fich_texto(head)){
                printf("Jogo exportado com sucesso...\n");
            }
            break;
        case 2:
            vencedor = Jogar_Multi_player(p,&head,n);
            if(!vencedor){
                if(save_bin(head)){
                    printf("Jogo guardado com sucesso...\n");
                }
            }
            if(Guarda_fich_texto(head)){
                printf("Jogo exportado com sucesso...\n");
            }
            break;
        default:
            break;
    }

    //dealocar memoria do ponteiro para o file, lista ligada e matriz
    fclose(ptr);
    Clean_Linked_List(head);
    for (int i = 0; i < 3; i++) {
        free(p[i]);
    }
    free(p);
    return 0;
}
