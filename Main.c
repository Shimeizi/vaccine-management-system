/* iaed25 - ist1109947 - project */

/**
 * @file Main.c
 * @author ist1109947 Shimeizi Jin
 * @brief Projeto IAED 24/25
 */

#include "Utentes.h"

/**
    @brief Le os comandos inseridos pelo utilizador e executa a operacao 
    pretendida.
*/
void leInput(Data *data_global, int* lotes_no_sistema, int idioma_pt) {
    int run = 1, input;

    while (run) {
        input = getchar();
        
        // Limpar buffer de entrada para evitar chamadas duplicadas
        //while (getchar() != '\n');  

        switch (input) {
            case 'q':
                run = 0;
                break;
            
            case 'c':
                executa_C(data_global, lotes_no_sistema, idioma_pt);
                break;

            case 'l':
                executa_L(idioma_pt);
                break;

            case 'a':
                executa_A(data_global, idioma_pt);
                break;

            case 'r':
                executa_R(idioma_pt);
                break;
            
            case 'd':
                executa_D(data_global, idioma_pt);
                break;

            case 'u':
                executa_U(idioma_pt);
                break;
            
            case 't':
                avancaTempo(data_global, idioma_pt);
                break;

        }
    }
}

/**
 * @brief Liberta toda a memoria alocada durante a execucao do programa.  
 */
void apagaSistema(){
    freeLotes();
    freeUtentes();
}

/**
 * @brief Funcao main.
 * @return sempre 0.
 */
int main(int argc, char *argv[]) {

    int idioma_pt = 0; 

    if (argc > 1 && strcmp(argv[1], "pt") == 0) {
        idioma_pt = 1;
    }
    int LOTES_NO_SISTEMA = 0;

    // Inicia a data
    Data data_global = iniciarData();

    // Executa os comandos
    leInput(&data_global, &LOTES_NO_SISTEMA, idioma_pt);

    apagaSistema();

    return 0;
}
