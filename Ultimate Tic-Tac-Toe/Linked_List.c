//
// Created by Daniel Rouxinol - 2018016929 on 5/9/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <synchapi.h>
#include "Jogo.h"

void add_to_list(Lista **head,Lista **aux, char letra_jog,int l, int c, int x, int y, int*cont, char letra_vencedora){

    if(*head==NULL){

        *head=(Lista*)malloc (1*sizeof(Lista));

        (*head)->id = *cont;
        *cont +=1;

        (*head)->coluna = c;
        (*head)->jogador = letra_jog;
        (*head)->linha = l;
        (*head)->x = x;
        (*head)->y = y;
        (*head)->letra_vencedora = letra_vencedora;

        (*head)->next=NULL;

        (*aux) = *head;
    }
    else {
        (*aux)->next=(Lista*)malloc (1*sizeof(Lista));
        (*aux)=(*aux)->next;
        (*aux)->id = *cont;
        *cont +=1;

        (*aux)->coluna = c;
        (*aux)->jogador = letra_jog;
        (*aux)->linha = l;
        (*aux)->x = x;
        (*aux)->y = y;
        (*aux)->letra_vencedora = letra_vencedora;

        (*aux)->next=NULL;
    }
}
void add_to_list_version2(Lista **head,Lista **aux,Lista *temp){

    if(*head==NULL){

        *head=(Lista*)malloc (1*sizeof(Lista));

        (*head)->id = temp->id;
        (*head)->coluna = temp->coluna;
        (*head)->jogador = temp->jogador;
        (*head)->linha = temp->linha;
        (*head)->x = temp->x;
        (*head)->y = temp->y;
        (*head)->letra_vencedora = temp->letra_vencedora;

        (*head)->next=NULL;

        (*aux) = *head;
    }
    else {
        (*aux)->next=(Lista*)malloc (1*sizeof(Lista));
        (*aux)=(*aux)->next;

        (*aux)->id = temp->id;
        (*aux)->coluna = temp->coluna;
        (*aux)->jogador =temp->jogador;
        (*aux)->linha =  temp->linha;
        (*aux)->x = temp->x;
        (*aux)->y = temp->y;
        (*aux)->letra_vencedora = temp->letra_vencedora;

        (*aux)->next=NULL;
    }
}
int translate(int l, int c){
    if(l == 0 && c == 0){
        return 1;
    }
    else if(l == 0 && c == 1){
        return 2;
    }
    else if(l == 0 && c == 2){
        return 3;
    }
    else if(l == 1 && c == 0){
        return 4;
    }
    else if(l == 1 && c == 1){
        return 5;
    }
    else if(l == 1 && c == 2){
        return 6;
    }
    else if(l == 2 && c == 0){
        return 7;
    }
    else if(l == 2 && c == 1){
        return 8;
    }
    else if(l == 2 && c == 2){
        return 9;
    }
}
int get_jogadas(Lista *head){
    int c = 0;
    while(head != NULL){
        c++;
        head = head->next;
    }
    return c;
}
void show_list(Lista **head, int k){ //Mostrar ate um determinado numero o que esta dentro da lista ligada
    Lista *aux;
    aux = *head;
    int cont = 0;
    int jogadas = get_jogadas(aux);
    int comeco = jogadas - k;

    while(aux != NULL){
        if(cont >= comeco){
            printf("\nJogada: %d\nO jogador '%c' inseriu a peca na posicao (%d,%d) do tabuleiro %d.",aux->id,aux->jogador,aux->linha,aux->coluna,translate(aux->x,aux->y));
        }
        aux = aux->next;
        cont++;
    }
    printf("\n");
}
void show_all(Lista *head,char *str){ //Mostrar o que esta dentro de uma celula da lista ligada
    Lista *aux;
    aux = head;
    sprintf(str,"\nJogada: %d\nO jogador '%c' inseriu a peca na posicao (%d,%d) do tabuleiro %d.",aux->id,aux->jogador,aux->linha,aux->coluna,translate(aux->x,aux->y));
    str[strlen(str) - 1] = '\0';

}