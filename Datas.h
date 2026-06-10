/**
 * @file Datas.h
 * @author ist1109947
 * @brief Declaracao de estruturas e funcoes para manipulacao de datas.
 */

 #include "Main.h"

typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;

Data iniciarData();
void printData(Data data);
Data leData();
int validaFormatoData(Data data);
int comparaData(Data data1, Data data2);
void avancaTempo(Data *dataGlobal, int idioma_pt);
