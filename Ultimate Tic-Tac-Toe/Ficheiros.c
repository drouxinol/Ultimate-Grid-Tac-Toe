//
// Created by Daniel Rouxinol - 2018016929 on 5/14/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <synchapi.h>
#include "Jogo.h"

FILE* check_save_bin(){
    FILE *ptr;
    int op;

    ptr = fopen("TP_P_save.bin","rb");
    if(ptr == NULL){
        printf("Nao foi encontrado nenhum ficheiro binario...\n");
        return NULL;
    }
    printf("Foi encontrado um save do jogo...Deseja carregar o ficheiro para o jogo atual?\n[1] - sim\n[2] - nao\nOpcao:");
    scanf("%d",&op);
    do{
        if(isdigit(op) || op > 2 || op < 1){
            fflush(stdin);
            printf("Numero invalido! Opcao:");
            scanf("%d",&op);
        }
    }while(isdigit(op)  || op > 2 || op < 1);

    if(op == 1){
        return ptr;
    }
    else {
        return NULL;
    }
}
Lista* open_bin_file(){
    Lista *head = NULL;
    Lista *aux = head;
    Lista *temp = (Lista*) malloc(sizeof(Lista));
    temp->next = NULL;

    FILE *fptr;

    if ((fptr = fopen("TP_P_save.bin","rb")) == NULL){
        printf("Error! opening file");

        return NULL;
    }

    do{
        if(fread(temp, sizeof(Lista), 1, fptr) > 0){
            add_to_list_version2(&head,&aux,temp);
            printf("\nJogada: %d\nO jogador '%c' inseriu a peca na posicao (%d,%d) do tabuleiro %d.",aux->id,aux->jogador,aux->linha,aux->coluna,translate(aux->x,aux->y));
        }
        else if(fread(temp, sizeof(Lista), 1, fptr) <= 0){
            break;
        }

    }while(1);

    fclose(fptr);
    return head;
}
BOOL save_bin(Lista *head){
    Lista *aux = head;
    FILE *fptr;

    if ((fptr = fopen("TP_P_save.bin","wb")) == NULL){
        printf("Erro ao abrir ficheiro binario!\n");
        return FALSE;
    }

    while(aux != NULL)
    {
        fwrite(aux, sizeof(Lista), 1, fptr);
        aux = aux->next;
    }
    fclose(fptr);
    return TRUE;

}
int import(Lista *head,Jogo **p){
    Lista *aux = head;
    int n = 0;
    while(aux != NULL){
        Insere_peca(aux->jogador,aux->linha,aux->coluna,p[aux->x][aux->y].Matriz);
        n = translate(aux->linha,aux->coluna);
        p[aux->x][aux->y].letra_venc = aux->letra_vencedora;
        if(p[aux->x][aux->y].letra_venc != ' '){
            p[aux->x][aux->y].continua = 1;
        }
        aux = aux->next;
    }
    return n;
}