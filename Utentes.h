/**
 * @file Lotes.c
 * @author ist1109947
 * @brief Declaracao de estruturas e funcoes para manipulacao de 
 *        registos de vacinas(utentes).
 */

#include "Lotes.h"

typedef struct Utente{
    char *nome;
    char *nome_vacina;
    char *lote_vacina;
    Data data;
}Utente;

typedef struct NodeUtente {
    Utente utente;
    struct NodeUtente* next;   // Ponteiro para o próximo nó
    struct NodeUtente* prev;   // Ponteiro para o nó anterior
} NodeUtente;


void executa_A(Data *data_global, int idioma_pt);
int JaAplicou(char* nome_utente, char* nome_vacina, Data data_global, int idioma_pt);
void aplicaVacinaAoUtente(char *nome, Lote *lote, Data data);
void pushUtente(Utente utente);

void executa_U(int idioma_pt);
void printUtente(NodeUtente *node_utente);

void executa_D(Data *data_global, int idioma_pt);
void apagaRegistoPorNome(char* nome_utente, int idioma_pt);
void apagaRegistoPorData(char* nome_utente, Data data, Data *data_global, int idioma_pt);
void apagaRegistoPorLote(char* nome_utente, Data data, Data *data_global, char *lote_vacina, int idioma_pt);

void freeUtentes();
