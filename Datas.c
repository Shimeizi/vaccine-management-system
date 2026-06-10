/**
 * @file Datas.c
 * @author ist1109947
 * @brief Funcoes para manipulacao de datas.
 */

#include "Datas.h"

/**
 * @brief Inicializa e retorna uma estrutura Data com o valor 01-01-2025.
 * @return Estrutura Data inicializada com dia=1, mes=1, ano=2025
 */
Data iniciarData(){
    Data dataGlobal;

    dataGlobal.dia = 1;
    dataGlobal.mes = 1;
    dataGlobal.ano = 2025;

    return dataGlobal;
}

/**
 * @brief Imprime a data no formato DD-MM-AAAA.
 * @param data Estrutura Data a ser imprimida
 * @example Para dia=5, mes=3, ano=2023 → "05-03-2023"
 */
void printData(Data data){
    printf("%02d-%02d-%d\n", data.dia, data.mes, data.ano);
}

/**
 * @brief Lê uma data do input.
 * @return Estrutura Data contendo os valores lidos
 * @note Não valida o formato da data durante a leitura
 */
Data leData() {
    Data data;
    int dia, mes, ano;

    scanf("%d-%d-%d", &dia, &mes, &ano);

    data.dia = dia;
    data.mes = mes;
    data.ano = ano;
    
    return data;
}

/**
 * @brief Valida se uma data é cronologicamente correta (ignorando anos bissextos).
 * @param data Estrutura Data a validar
 * @return TRUE (1) se válida, FALSE (0) se inválida
 * @note Considera fevereiro sempre com 28 dias
 * @note Valida ano positivo, mês entre 1-12 e dias conforme o mês
 */
int validaFormatoData(Data data){

    if(data.ano < 0 || (data.mes < 1 || data.mes > 12)){
        return FALSE;
    }

    if(data.mes == 2 && (data.dia < 1 || data.dia > 28)){
        return FALSE;
    }

    else if(data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11){
        if(data.dia < 1 || data.dia > 30){
            return FALSE;
        }
    }
    else{
        if(data.dia < 1 || data.dia > 31){
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * @brief Compara duas datas cronologicamente.
 * @param data1 Primeira data para comparação
 * @param data2 Segunda data para comparação
 * @return Diferença entre datas (>0 se data1 > data2, <0 se data1 < data2, 0 se iguais)
 * @example comparaData({15,1,2025}, {10,1,2025}) retorna 5 (15-10)
 */
int comparaData(Data data1, Data data2) {
    if (data1.ano != data2.ano) {
        return data1.ano - data2.ano;
    } 
    else if (data1.mes != data2.mes) {
        return data1.mes - data2.mes;
    } 
    else if (data1.dia != data2.dia) {
        return data1.dia - data2.dia;
    }
    return 0;
}

/**
 * @brief Atualiza a data do sistema se a nova data for válida e posterior.
 * @param[in,out] dataGlobal Ponteiro para a data atual do sistema (será atualizada)
 * @param idioma_pt Flag de idioma (1 = português, 0 = inglês) para mensagens de erro
 * @note Imprime a nova data se válida, ou mensagem de erro no idioma selecionado
 * @note A validação inclui formato correto e verificação de posterioridade temporal
 */
void avancaTempo(Data *dataGlobal, int idioma_pt){
    Data nova_data;

    nova_data = leData();

    if(validaFormatoData(nova_data) && (comparaData(nova_data, *dataGlobal) >= 0)){
        dataGlobal->dia = nova_data.dia;
        dataGlobal->mes = nova_data.mes;
        dataGlobal->ano = nova_data.ano;
        
        printData(*dataGlobal);
        }
    else{
        printf("%s\n", idioma_pt ? DATA_INVALIDA_PT : DATA_INVALIDA);
    }
}
