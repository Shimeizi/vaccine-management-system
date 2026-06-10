/**
 * @file Lotes.h
 * @author ist1109947
 * @brief Declaracao de estruturas e funcoes para manipulacao de vacinas(lotes).
 */

#include "Datas.h"

typedef struct Lote{
    char *nome;
    char *lote;
    Data data;
    int num_doses;
    int num_aplic;
}Lote;

typedef struct NodeLote{
    Lote lote;
    struct NodeLote *next;
}NodeLote;

void executa_C(Data* data_global, int* lotes_no_sistema, int idioma_pt);
int leString(char buffer[]);
char* criaString(char buffer[]);
int sistemaCheio(int* lotes_no_sistema);
int loteExiste(const char *novo_lote);
int validaFormatoLote(char lote_buffer[]);
int validaFormatoNomeVacina(char nome_vacina_buffer[]);
int validaDoses(int num_doses);
int validaLoteVacina(int* lotes_no_sistema, char* lote_vacina, char* nome_vacina, 
    Data data, Data* data_global, int num_doses, int idioma_pt);
void criaLoteVacina(char *lote, char* nome, Data data, int num_doses, int* lotes_no_sistema);
void pushLote(NodeLote **head, Lote lote);
void printLote(Lote lote);

void executa_L(int idioma_pt);
void printLoteVacina(Lote lote);

Lote* vacinaExisteDisponivel(char *nome_vacina, Data data_global, int idioma_pt);

void executa_R(int idioma_pt);
void retiraDisponibilidade(char *lote, int idioma_pt);

void freeLotes();
