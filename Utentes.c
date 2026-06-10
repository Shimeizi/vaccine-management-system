/**
 * @file Utentes,c
 * @author ist1109947
 * @brief Funcoes para manipulacao de registos de vacinas(utentes).
 */

#include "Utentes.h"

/** Estrutura de dados para os utentes */
static NodeUtente *lista_utentes = NULL;
static NodeUtente *ultimo_no = NULL;


/**
 * @brief Executa o comando 'a' para aplicar vacina a um utente.
 * @param data_global Ponteiro para a data atual do sistema
 * @param idioma_pt Flag de idioma (1 = português, 0 = inglês) para mensagens
 * @details Lê nome do utente e vacina, verifica condições e aplica se válido.
 * @note Libera memória alocada caso a aplicação não seja possível.
 */
void executa_A(Data *data_global, int idioma_pt){
    char nome_buffer[MAX_INPUT], vacina_buffer[MAX_INPUT];
    Lote* lote;

    // Nome do utente
    leString(nome_buffer);  
    char *nome_utente = criaString(nome_buffer);

    // Nome da vacina
    leString(vacina_buffer);  
    char *nome_vacina = criaString(vacina_buffer);

    if(!validaFormatoNomeVacina(nome_vacina)){
        printf("%s\n", idioma_pt ? ESGOTADO_PT : ESGOTADO);
        free(nome_utente);
        free(nome_vacina);
        return;
    }

    lote = vacinaExisteDisponivel(nome_vacina, *data_global, idioma_pt);

    if(!JaAplicou(nome_utente, nome_vacina, *data_global, idioma_pt) && (lote != NULL)){
        aplicaVacinaAoUtente(nome_utente, lote, *data_global);
        free(nome_vacina);
    }
    else{
        free(nome_utente);
        free(nome_vacina);
    }
}

/**
 * @brief Verifica se utente já recebeu a mesma vacina no mesmo dia.
 * @param nome_utente Nome do utente a verificar
 * @param nome_vacina Nome da vacina a verificar
 * @param data_global Data atual para comparação
 * @param idioma_pt Idioma para mensagens de erro
 * @return TRUE se já vacinado, FALSE caso contrário
 * @details Verifica apenas registros do mesmo dia (não verifica dias anteriores).
 */
int JaAplicou(char* nome_utente, char* nome_vacina, Data data_global, int idioma_pt) {
    NodeUtente* atual = ultimo_no;

    while (atual != NULL) {
        // Se a data do registo for diferente da data do sistema, pare de verificar mais registros
        if (comparaData(atual->utente.data, data_global) != 0) {
            return FALSE;  // Não há registos no mesmo dia, logo, o utente não foi vacinado hoje
        }

        // Se a data for igual à data do sistema, verifica o nome do utente e o nome da vacina
        if (strcmp(atual->utente.nome, nome_utente) == 0 && strcmp(atual->utente.nome_vacina, nome_vacina) == 0) {
            printf("%s\n", idioma_pt ? JA_VACINADO_PT : JA_VACINADO);
            return TRUE;  // Retorna TRUE se encontrar a vacina aplicada no mesmo dia
        }

        // Avança para o nó anterior
        atual = atual->prev;
    }

    // Se nenhum registo for encontrado, retorna FALSE
    return FALSE;
}


/**
 * @brief Registra a aplicação de vacina para um utente no sistema.
 * @param nome Nome do utente vacinado
 * @param lote Ponteiro para o lote de vacina utilizado
 * @param data Data da aplicação
 * @details Atualiza contadores de doses e adiciona registro na lista de utentes.
 */
void aplicaVacinaAoUtente(char *nome, Lote *lote, Data data){
    Utente novo_utente;

    novo_utente.nome = nome;
    novo_utente.nome_vacina = lote->nome;
    novo_utente.lote_vacina = lote->lote;
    novo_utente.data = data;

    lote->num_aplic++;
    lote->num_doses--;

    pushUtente(novo_utente);

    printLote(*lote);
}

/**
 * @brief Adiciona um novo registro de utente vacinado à lista.
 * @param utente Estrutura com dados do utente a ser registrado
 * @details Mantém a lista duplamente encadeada atualizada com inserção no final.
 */
void pushUtente(Utente utente) {
    NodeUtente* novo_Node = (NodeUtente*) malloc(sizeof(NodeUtente));
    novo_Node->utente = utente;
    novo_Node->next = NULL;
    novo_Node->prev = ultimo_no; // O anterior será o último nó existente

    if (ultimo_no != NULL) {
        // Se a lista não está vazia, o último nó atual aponta para o novo nó
        ultimo_no->next = novo_Node;
    } else {
        // Se a lista está vazia, o novo nó será o primeiro e o último
        lista_utentes = novo_Node;
    }

    // Atualiza o último nó
    ultimo_no = novo_Node;
}


/**
 * @brief Executa o comando 'u' para listar aplicações de vacinas.
 * @param idioma_pt Idioma para mensagens (1 = PT, 0 = EN)
 * @details Sem parâmetro: lista todos os registros. Com nome: filtra por utente.
 */
void executa_U(int idioma_pt){
    NodeUtente* atual = lista_utentes;
    char nome_buffer[MAX_INPUT];
    int encontrado = 0;

    // Le nome de utente
    int nome = leString(nome_buffer);
    char* nome_utente = criaString(nome_buffer);

    if(nome){ // se existe nome atras do comando 'u'
        while(atual != NULL){
            if(strcmp(atual->utente.nome, nome_utente) == 0){
                printUtente(atual);
                encontrado = 1;
            }
            atual = atual->next;
        }
        if(!encontrado){
            printf("%s: %s\n", nome_utente, idioma_pt ? UTENTE_INEXISTENTE_PT : UTENTE_INEXISTENTE);
        }
    }

    else{
        while(atual != NULL){
            printUtente(atual);
            atual = atual->next;
        }
    }

    free(nome_utente);
}

/**
 * @brief Imprime informações de um registro de vacinação.
 * @param node_utente Ponteiro para o nó contendo os dados do utente
 * @details Formato: "nome lote DD-MM-AAAA"
 */
void printUtente(NodeUtente *node_utente){
    printf("%s %s %02d-%02d-%d\n", node_utente->utente.nome, node_utente->utente.lote_vacina, 
        node_utente->utente.data.dia, node_utente->utente.data.mes, node_utente->utente.data.ano);
}

/**
 * @brief Executa o comando 'd' para apagar registros de vacinação.
 * @param data_global Ponteiro para data atual do sistema
 * @param idioma_pt Idioma para mensagens (1 = PT, 0 = EN)
 * @details Aceita diferentes combinações de parâmetros (nome, data, lote).
 */
void executa_D(Data *data_global, int idioma_pt) {
    char *nome_utente, nome_buffer[MAX_INPUT], lote_vacina[MAX_INPUT], linha[MAX_INPUT], c;
    Data data_vacina;
    int num_args = 0;

    fgets(linha, sizeof(linha), stdin);

    num_args = sscanf(linha, "%c \"%[^\"]\" %d-%d-%d %s", &c, nome_buffer, 
                      &data_vacina.dia, &data_vacina.mes, &data_vacina.ano, lote_vacina);

    if (num_args < 2) {  
        num_args = sscanf(linha, "%c %s %d-%d-%d %s", &c, nome_buffer, 
                          &data_vacina.dia, &data_vacina.mes, &data_vacina.ano, lote_vacina);
    }

    // Caso tenha apenas o nome (com ou sem aspas)
    if (num_args == 2) { 
        nome_utente = strdup(nome_buffer);
        apagaRegistoPorNome(nome_buffer, idioma_pt);
        free(nome_utente);
        return;
    }

    nome_utente = strdup(nome_buffer);

    if (num_args == 5) {  // Apenas nome e data
        apagaRegistoPorData(nome_utente, data_vacina, data_global, idioma_pt);

    } else if (num_args == 6) {  // Nome, data e lote
        apagaRegistoPorLote(nome_utente, data_vacina, data_global, lote_vacina, idioma_pt);
    }

    free(nome_utente);
}

/**
 * @brief Remove todos os registros de vacinação de um utente específico.
 * @param nome_utente Nome do utente a ter registros removidos
 * @param idioma_pt Idioma para mensagens de feedback
 * @return Número de registros removidos
 * @note Remove todas as ocorrências independente de data ou lote.
 */
void apagaRegistoPorNome(char* nome_utente, int idioma_pt) {
    NodeUtente* atual = lista_utentes;
    NodeUtente* anterior = NULL;
    NodeUtente* delete;
    int num_apl_apagados = 0;
    int encontrado = FALSE;

    while (atual != NULL) {
        if (strcmp(atual->utente.nome, nome_utente) == 0) {
            encontrado = TRUE;
            num_apl_apagados++;

            delete = atual;

            if (anterior == NULL) { 
                lista_utentes = atual->next;
                atual = lista_utentes; 
            } else {
                anterior->next = atual->next;
                atual = anterior->next;
            }
            free(delete->utente.nome); 
            free(delete); 
            
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }

    if(encontrado){
        printf("%d\n", num_apl_apagados);
    }
    else{
        printf("%s: %s\n", nome_utente, idioma_pt ? UTENTE_INEXISTENTE_PT : UTENTE_INEXISTENTE);
    }
}

/**
 * @brief Remove registros de vacinação de um utente em data específica.
 * @param nome_utente Nome do utente a ter registros removidos
 * @param data Data dos registros a remover
 * @param data_global Ponteiro para data atual (validação)
 * @param idioma_pt Idioma para mensagens de feedback
 * @return Número de registros removidos
 * @note Valida se data é anterior ou igual à data atual.
 */
void apagaRegistoPorData(char* nome_utente, Data data, Data *data_global, int idioma_pt) {
    NodeUtente* atual = lista_utentes;
    NodeUtente* anterior = NULL;
    NodeUtente* delete;
    int num_apl_apagados = 0;
    int encontrado = FALSE;

    // Verifica se a data é válida antes de percorrer a lista
    if (!validaFormatoData(data) || (comparaData(data, *data_global) > 0)) {
        printf("%s\n", idioma_pt ? DATA_INVALIDA_PT : DATA_INVALIDA);
        return; // Sai da função se a data for inválida
    }

    // Percorre a lista de utentes
    while (atual != NULL) {
        if (strcmp(atual->utente.nome, nome_utente) == 0) {
            encontrado = TRUE;

            // Verifica se a data do nó atual corresponde à data fornecida
            if (comparaData(atual->utente.data, data) == 0) {
                // Remove o nó da lista
                delete = atual;
                if (anterior == NULL) { 
                    // Caso seja o primeiro nó
                    lista_utentes = atual->next;
                    atual = lista_utentes; 
                } else {
                    // Caso seja um nó intermediário ou final
                    anterior->next = atual->next;
                    atual = anterior->next;
                }

                // Libera a memória do nó removido
                free(delete);
                num_apl_apagados++;
                continue; // Evita que "anterior" avance incorretamente
            }
        }
        
        // Atualiza os ponteiros apenas se não apagou o nó
        anterior = atual;
        atual = atual->next;
    }

    // Exibe o resultado
    if (!encontrado) {
        printf("%s: %s\n", nome_utente, idioma_pt ? UTENTE_INEXISTENTE_PT : UTENTE_INEXISTENTE);
    } else {
        printf("%d\n", num_apl_apagados);
    }
}

/**
 * @brief Remove registro específico de vacinação (nome + data + lote).
 * @param nome_utente Nome do utente
 * @param data Data da aplicação
 * @param data_global Ponteiro para data atual (validação)
 * @param lote_vacina Código do lote a remover
 * @param idioma_pt Idioma para mensagens de feedback
 * @return Número de registros removidos
 * @note Faz validação completa de todos os parâmetros.
 */
void apagaRegistoPorLote(char* nome_utente, Data data, Data *data_global, char *lote_vacina, int idioma_pt) {
    NodeUtente* atual = lista_utentes;
    NodeUtente* anterior = NULL;
    NodeUtente* delete;
    int num_apl_apagados = 0;
    int encontrado = FALSE;

    // Verifica se o lote existe antes de percorrer a lista
    if (!loteExiste(lote_vacina)) {
        printf("%s: %s\n", lote_vacina, idioma_pt ? LOTE_INEXISTENTE_PT : LOTE_INEXISTENTE);
        return; // Sai da função se o lote não existir
    }

    // Verifica se a data é válida
    if (!validaFormatoData(data) || (comparaData(data, *data_global) > 0)) {
        printf("%s\n", idioma_pt ? DATA_INVALIDA_PT : DATA_INVALIDA);
        return; // Sai da função se a data for inválida
    }

    // Percorre a lista de utentes
    while (atual != NULL) {
        if (strcmp(atual->utente.nome, nome_utente) == 0) {
            encontrado = TRUE;

            // Verifica se a data do nó atual corresponde à data fornecida
            if (comparaData(atual->utente.data, data) == 0) {
                // Verifica se o lote do nó atual corresponde ao lote fornecido
                if (strcmp(atual->utente.lote_vacina, lote_vacina) == 0) {
                    // Remove o nó da lista
                    delete = atual;
                    if (anterior == NULL) { 
                        // Caso seja o primeiro nó
                        lista_utentes = atual->next;
                        atual = lista_utentes; 
                    } else {
                        // Caso seja um nó intermediário ou final
                        anterior->next = atual->next;
                        atual = anterior->next;
                    }

                    // Libera a memória do nó removido
                    free(delete);
                    num_apl_apagados++;
                    continue; // Evita que "anterior" avance incorretamente
                }
            }
        }
        
        // Atualiza os ponteiros apenas se não apagou o nó
        anterior = atual;
        atual = atual->next;
    }

    // Exibe o resultado
    if (!encontrado) {
        printf("%s: %s\n", nome_utente, idioma_pt ? UTENTE_INEXISTENTE_PT : UTENTE_INEXISTENTE);
    } else {
        printf("%d\n", num_apl_apagados);
    }
}

/**
 * @brief Libera toda a memória alocada para a lista de utentes.
 * @details Remove todos os nós e strings alocadas, reiniciando a lista.
 * @note Chamar ao finalizar o programa para evitar vazamentos de memória.
 */
void freeUtentes() {
    NodeUtente *current = lista_utentes;
    while (current != NULL) {
        NodeUtente *next = current->next;
        free(current->utente.nome);      // Libera o nome do utente
        free(current);                   // Libera o nó
        current = next;
    }
    lista_utentes = NULL;
    ultimo_no = NULL;
}
