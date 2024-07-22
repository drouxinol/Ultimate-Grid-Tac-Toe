//
// Created by Daniel Rouxinol - 2018016929 on 4/29/2022.
//

#ifndef TP_P_JOGO_H
#define TP_P_JOGO_H
#include <stdbool.h>

typedef struct {

    char letra_venc;
    int continua; //0 - continua \ 1 - nao continua
    char Matriz[3][3];

}Jogo;

typedef struct Lista{

    int id;
    char jogador;
    int linha;
    int coluna;
    int x;
    int y;
    char letra_vencedora;
    struct Lista *next;
}Lista;

/*--------------------------------------------Lógica------------------------------------------------*/
void initMatriz_secundaria(char matriz[3][3]);
void menu_inicial(const int *n);
int menu();
int Get_K();
void MostrarJogo(Jogo **p);
int Verifica_vitoria(char letra, char matriz[3][3]);
int PrimeiroJogar();
char troca(char c);
bool check_tabuleiro(int continua);
void calcula_tabuleiro(int numero, int *l, int *c);
void Mostrajogadores(int jogador_1, int jogador_2);
void Get_Posicoes(Jogo **p, char letra, const int * const x, const int * const y, int *l,int *c);
bool Insere_peca(char letra,int l, int c, char m[3][3]);
void verifica_disp_tabuleiro(Jogo **p, int *x, int *y);
bool Verifica_Empate(char matriz[3][3]);
void AI(Jogo **p, int *x, int *y);
void Vitoria(Jogo **p, int x, int y, bool *jog_vencedor, char letra);
void Empate(Jogo **p, int *x, int *y);
BOOL Verifica_MP(Jogo **p,char *vencedor, char *jog1, char *jog2);
void Mostra_vencedor(char letra);

/*-----------------------------------------Lista-Ligada----------------------------------------------*/

void add_to_list(Lista **head,Lista **aux, char letra_jog,int l, int c, int x, int y, int *cont, char letra_vencedora);
void add_to_list_version2(Lista **head,Lista **aux,Lista *temp);
void show_list(Lista **head, int k);
int translate(int l, int c);
void show_all(Lista *head, char *str);

/*------------------------------------------Ficheiros------------------------------------------------*/

BOOL Guarda_fich_texto(Lista *p);
void GetNome(char nome[]);
FILE* check_save_bin();
Lista* open_bin_file();
BOOL save_bin(Lista *head);
int import(Lista *head,Jogo **p);


#endif //TP_P_JOGO_H
