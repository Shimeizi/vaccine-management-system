/**
 * @file Lotes.c
 * @author ist1109947
 * @brief Funcoes para manipulacao de vacinas(lotes).
 */

#include "Lotes.h"

/** 
 * @brief Lista encadeada de lotes de vacinas (variável global do módulo).
 * @details Armazena todos os lotes de vacinas registrados no sistema.
 */
static NodeLote *lista_lotes = NULL;


/**
 * @brief Executa o comando 'c' para introduzir um novo lote de vacina.
 * @param data_global Ponteiro para a data atual do sistema
 * @param lotes_no_sistema Ponteiro para o contador de lotes no sistema
 * @param idioma_pt Flag de idioma (1 = português, 0 = inglês) para mensagens
 * @details Lê os dados do lote (lote, data, doses, nome), valida e introduz se válido.
 * @note Libera memória alocada caso o lote seja inválido.
 */
void executa_C(Data* data_global, int* lotes_no_sistema, int idioma_pt){
    char lote_buffer[MAX_INPUT], nome_vacina_buffer[MAX_INPUT];
    int num_doses, valido;
    Data data;

    // Lote
    leString(lote_buffer);
    char *lote_vacina = criaString(lote_buffer);

    // Data
    data = leData();

    // Numero de doses
    scanf("%d", &num_doses);

    // Nome
    leString(nome_vacina_buffer);
    char *nome_vacina = criaString(nome_vacina_buffer);


    valido = validaLoteVacina(lotes_no_sistema, lote_vacina, nome_vacina, data, 
                            data_global, num_doses, idioma_pt);

    if(valido){
        criaLoteVacina(lote_vacina, nome_vacina, data, num_doses, lotes_no_sistema);
    }
    else{
        free(lote_vacina);
        free(nome_vacina);
    }
}

/**
 * @brief Lê uma string da entrada.
 * @param buffer Array de caracteres onde a string será armazenada
 * @return TRUE (1) se leitura bem-sucedida, FALSE (0) se entrada vazia
 * @details Suporta strings com espaços quando entre aspas.
 * @example "Vacina COVID" → lê como string única
 */
int leString(char buffer[]) {
    int iterador = -1, c;
    int fim = FALSE, valido = FALSE, aspas = FALSE;

    while (!fim) {
        c = getchar();

        if (c == EOF || c == '\n') {
            fim = TRUE;
            buffer[++iterador] = '\0';
        } 
        
        else if (c == '"') {
            aspas = !aspas;
            if (!aspas) {
                buffer[++iterador] = '\0';
                fim = TRUE;
            }
        }

        else if (isspace(c)){
            if (valido && !aspas) {
                buffer[++iterador] = '\0';
                fim = TRUE;
            }
            else if (valido && aspas) {
                buffer[++iterador] = c;
            }
        }

        else {
            valido = TRUE;
            buffer[++iterador] = c;
        }
    }

    return valido;
}

/**
 * @brief Aloca e copia uma string dinamicamente.
 * @param buffer String original a ser copiada
 * @return Ponteiro para a nova string alocada
 */
char* criaString(char buffer[]){

    char *string = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(string, buffer);

    return string;
}

/**
 * @brief Verifica capacidade do sistema para novos lotes.
 * @param lotes_no_sistema Ponteiro para contador atual de lotes
 * @return TRUE se sistema cheio (NUM_LOTES atingido), FALSE caso contrário
 */
int sistemaCheio(int* lotes_no_sistema){
    if(*lotes_no_sistema < NUM_LOTES){
        return FALSE;
    }
    
    return TRUE;
}

/**
 * @brief Verifica se um lote já existe no sistema.
 * @param novo_lote Lote a verificar
 * @return TRUE se lote já existe, FALSE caso contrário
 */
int loteExiste(const char *novo_lote) {
    if (lista_lotes == NULL) {
        return FALSE;
    }

    NodeLote *atual = lista_lotes;

    while (atual != NULL) {
        // Verifica se o número do lote já existe
        if (strcmp(atual->lote.lote, novo_lote) == 0) {
            return TRUE;  // Lote duplicado encontrado
        }
        
        atual = atual->next;
    }

    return FALSE;  // Lote não encontrado, pode ser inserido
}

/**
 * @brief Valida o formato do lote.
 * @param lote_buffer String contendo o lote
 * @return TRUE se válido (até 20 caracteres hexadecimais), FALSE se inválido
 * @details Um lote válido deve conter apenas dígitos 0-9 e letras A-F/a-f.
 */
int validaFormatoLote(char lote_buffer[]) {
    int i = 0;
    char c;

    // Verificar comprimento no início
    if (strlen(lote_buffer) > 20) {
        return FALSE;
    }

    // Validar caracteres
    while ((c = lote_buffer[i]) != '\0') {
        // Se encontrar um caractere inválido (não hexadecimal ou espaço)
        if (!isxdigit(c)) {
            return FALSE;
        }
        i++;
    }

    return TRUE;  // A string é válida
}

/**
 * @brief Valida o formato do nome da vacina.
 * @param nome_vacina_buffer String contendo o nome da vacina
 * @return TRUE se válido (até 50 caracteres sem espaços), FALSE se inválido
 */
int validaFormatoNomeVacina(char nome_vacina_buffer[]) {
    int i = 0;
    char c;

    // Verificar comprimento no início
    if (strlen(nome_vacina_buffer) > 50) {
        return FALSE;
    }

    // Validar caracteres
    while ((c = nome_vacina_buffer[i]) != '\0') {
        // Se encontrar um espaço ou caractere inválido
        if (isspace(c)) {
            return FALSE;
        }
        i++;
    }

    return TRUE;  // A string é válida
}


/**
 * @brief Valida o número de doses de um lote.
 * @param num_doses Quantidade de doses a validar
 * @return TRUE se positivo (>0), FALSE se inválido
 */
int validaDoses(int num_doses) {
    if (num_doses <= 0) {
        return FALSE;
    }
    return TRUE;
}

/**
 * @brief Valida todas as condições necessárias para introduzir um novo lote no sistema.
 * @param lotes_no_sistema Contador de lotes no sistema
 * @param lote_vacina Lote a validar
 * @param nome_vacina Nome da vacina a validar
 * @param data Data de validade a verificar
 * @param data_global Ponteiro para data atual do sistema
 * @param num_doses Quantidade de doses a validar
 * @param idioma_pt Idioma para mensagens de erro
 * @return TRUE se todas as condições são compridas, FALSE caso contrário
 */
int validaLoteVacina(int* lotes_no_sistema, char* lote_vacina, char* nome_vacina, 
    Data data, Data* data_global, int num_doses, int idioma_pt){

    if(sistemaCheio(lotes_no_sistema)){
        printf("%s\n", idioma_pt ? SISTEMA_CHEIO_PT : SISTEMA_CHEIO);
        return FALSE;
    }

    if(loteExiste(lote_vacina)){
        printf("%s\n", idioma_pt ? LOTE_JA_EXISTE_PT : LOTE_JA_EXISTE);
        return FALSE;
    }

    if(!validaFormatoLote(lote_vacina)){
        printf("%s\n", idioma_pt ? LOTE_INVALIDO : LOTE_INVALIDO);
        return FALSE;
    }

    if(!validaFormatoNomeVacina(nome_vacina)){
        printf("%s\n", idioma_pt ? NOME_INVALIDO_PT : NOME_INVALIDO);
        return FALSE;
    }

    if(!(validaFormatoData(data) && (comparaData(data, *data_global) >= 0))){
        printf("%s\n", idioma_pt ? DATA_INVALIDA_PT : DATA_INVALIDA);
        return FALSE;
    }

    if(!validaDoses(num_doses)){
        printf("%s\n", idioma_pt? QUANTIDADE_INVALIDA_PT : QUANTIDADE_INVALIDA);
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief Cria e registra um novo lote de vacina no sistema.
 * @param lote Lote da vacina
 * @param nome Nome da vacina 
 * @param data Data de validade 
 * @param num_doses Quantidade de doses 
 * @param lotes_no_sistema Ponteiro para contador de lotes 
 */
void criaLoteVacina(char *lote, char* nome, Data data, int num_doses, int* lotes_no_sistema){
    Lote novo_lote;

    novo_lote.lote = lote;
    novo_lote.nome = nome;
    novo_lote.data = data;
    novo_lote.num_doses = num_doses;
    novo_lote.num_aplic = 0;

    // Incrementa o ponteiro
    *lotes_no_sistema += 1;

    pushLote(&lista_lotes, novo_lote);
    printLote(novo_lote);
}

/**
 * @brief Insere um lote na lista mantendo ordenação por data e lote.
 * @param head Ponteiro para o início da lista de lotes
 * @param lote Dados do lote a ser inserido
 * @details Ordenação primária por data (cronológica), secundária por código (alfabética).
 */
void pushLote(NodeLote **head, Lote lote) {
    NodeLote* novo_Node = (NodeLote*) malloc(sizeof(NodeLote));
    novo_Node->lote = lote;
    NodeLote *current;

    // Caso especial: a lista está vazia ou o novo nó deve ser o primeiro
    if (*head == NULL) {
        novo_Node->next = NULL;
        *head = novo_Node;
        return;
    }

    // Comparações de data e lote feitas uma vez e armazenadas
    int data_comparacao = comparaData((*head)->lote.data, novo_Node->lote.data);
    int lote_comparacao = (data_comparacao == 0) ? strcmp((*head)->lote.lote, novo_Node->lote.lote) : -1;

    // Se o novo nó deve ser o primeiro
    if (data_comparacao > 0 || (data_comparacao == 0 && lote_comparacao > 0)) {
        novo_Node->next = *head;
        *head = novo_Node;
        return;
    }

    current = *head;

    // Percorre a lista até encontrar o local correto
    while (current->next != NULL) {
        // Comparações de data e lote feitas uma vez
        int next_data_comparacao = comparaData(novo_Node->lote.data, current->next->lote.data);
        int next_lote_comparacao = (next_data_comparacao == 0) ? strcmp(novo_Node->lote.lote, current->next->lote.lote) : -1;

        if (next_data_comparacao > 0 || (next_data_comparacao == 0 && next_lote_comparacao > 0)) {
            current = current->next;
        } else {
            break;
        }
    }

    // Insere o novo nó na posição correta
    novo_Node->next = current->next;
    current->next = novo_Node;
}


/**
 * @brief Imprime as informações completas de um lote de vacina.
 * @param lote Estrutura contendo os dados do lote
 * @details Formato: "nome lote DD-MM-AAAA doses_disponíveis doses_aplicadas"
 */
void printLote(Lote lote){
    printf("%s\n", lote.lote);
}


/**
 * @brief Executa o comando 'l' para listar lotes.
 * @param idioma_pt Idioma para mensagens (1 = PT, 0 = EN)
 * @details Sem parâmetros: lista todos os lotes. Com parâmetros: filtra por nome.
 */
void executa_L(int idioma_pt) {
    char input[MAX_INPUT];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return;
    }

    input[strcspn(input, "\n")] = 0; 

    if (input[0] == '\0') {
        if (lista_lotes == NULL) {
            return;
        }

        NodeLote* atual = lista_lotes;
        while (atual != NULL) {
            Lote lote = atual->lote;
            printLoteVacina(lote);
            atual = atual->next;
        }
        return;
    }

    char* token = strtok(input, " ");  
    while (token != NULL) {
        int encontrado = 0;
        NodeLote* atual = lista_lotes;

        while (atual != NULL) {
            Lote lote = atual->lote;
            if (strcmp(lote.nome, token) == 0) {
                printLoteVacina(lote);
                encontrado = 1;
            }
            atual = atual->next;
        }

        if (!encontrado) {
            printf("%s: %s\n", token, idioma_pt ? VACINA_INEXISTENTE_PT : VACINA_INEXISTENTE);
        }

        token = strtok(NULL, " "); 
    }
}

/**
    @brief Imprime informacao de uma vacina.
*/
void printLoteVacina(Lote lote){
    printf("%s %s %02d-%02d-%d %d %d\n", lote.nome, lote.lote, lote.data.dia, 
        lote.data.mes, lote.data.ano, lote.num_doses, lote.num_aplic);
}


/**
 * @brief Busca vacina disponível por nome e validade.
 * @param nome_vacina Nome da vacina a buscar
 * @param data_global Data atual para verificar validade
 * @param idioma_pt Idioma para mensagens de erro
 * @return Ponteiro para lote válido ou NULL se não encontrado
 * @details Um lote válido deve: existir, estar dentro do prazo e ter doses disponíveis.
 */
Lote* vacinaExisteDisponivel(char *nome_vacina, Data data_global, int idioma_pt){
    NodeLote* atual = lista_lotes;

    while (atual != NULL) {
        Lote lote = atual->lote;
        if (strcmp(lote.nome, nome_vacina) == 0) {
            if(comparaData(lote.data, data_global) >= 0){
                if(lote.num_doses > 0){
                    return &atual->lote;
                }  
            }
        }
        atual = atual->next;
    }
    printf("%s\n", idioma_pt ? ESGOTADO_PT : ESGOTADO);
    return NULL;
}

/**
 * @brief Executa o comando 'r' para remover disponibilidade de lote.
 * @param idioma_pt Idioma para mensagens (1 = PT, 0 = EN)
 * @details Lê o código do lote e remove (se não usado) ou zera doses (se parcialmente usado).
 */
void executa_R(int idioma_pt) {
    char lote_buffer[MAX_INPUT];

    leString(lote_buffer);
    char *lote_vacina = criaString(lote_buffer);

    if(!validaFormatoLote(lote_buffer)){
        printf("%s: %s\n", lote_vacina, idioma_pt ? LOTE_INEXISTENTE_PT : LOTE_INEXISTENTE);
        free(lote_vacina);  
        return;
    }

    retiraDisponibilidade(lote_vacina, idioma_pt);

    free(lote_vacina);
}


/**
 * @brief Remove/atualiza disponibilidade de um lote específico.
 * @param lote Lote a processar
 * @param idioma_pt Idioma para mensagens
 * @details Se não houve aplicações: remove o lote. Se houve: mantém registro com doses = 0.
 */
void retiraDisponibilidade(char *lote, int idioma_pt) {

    int encontrado = FALSE;
    int num_doses_aplics;

    if (lista_lotes == NULL) {
        printf("%s: %s\n", lote, idioma_pt ? LOTE_INEXISTENTE_PT : LOTE_INEXISTENTE);
        return;
    }

    NodeLote* anterior = lista_lotes;
    NodeLote* atual = anterior->next;

    if (strcmp(lista_lotes->lote.lote, lote) == 0) {
        encontrado = TRUE;
        num_doses_aplics = lista_lotes->lote.num_aplic;
        
        if (lista_lotes->lote.num_aplic == 0) {
            NodeLote* to_free = lista_lotes;
            lista_lotes = lista_lotes->next;
            free(to_free->lote.lote);  // free a string do lote
            free(to_free->lote.nome);  // free a string do nome
            free(to_free);
        }
        else {
            lista_lotes->lote.num_doses = 0;
        }
    }

    while (atual != NULL) {

        if (strcmp(atual->lote.lote, lote) == 0) {
            encontrado = TRUE;
            num_doses_aplics = atual->lote.num_aplic;

            if (atual->lote.num_aplic == 0) {
                anterior->next = atual->next;
                free(atual->lote.lote);  
                free(atual->lote.nome);   
                free(atual);
            }
            else {
                atual->lote.num_doses = 0;
            }
        }

        anterior = atual;
        atual = atual->next;
    }
    if(!encontrado){
        printf("%s: %s\n", lote, idioma_pt ? LOTE_INEXISTENTE_PT : LOTE_INEXISTENTE);
    }
    else {
        printf("%d\n", num_doses_aplics);
    }
}

/**
 * @brief Libera toda a memória alocada para a lista de lotes.
 * @details Remove todos os nós e strings alocadas, reiniciando a lista.
 */
void freeLotes() {
    NodeLote *current = lista_lotes;
    while (current != NULL) {
        NodeLote *next = current->next;
        free(current->lote.lote);  
        free(current->lote.nome); 
        free(current);           
        current = next;
    }
    lista_lotes = NULL;
}
