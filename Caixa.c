#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu(void);

int senha(void){
    int x, i = 0;
    while(i<3){
        printf("Digite a senha: ");
        scanf("%d", &x);
        if(x == 2435) return 0;
        else{
            printf("Senha incorreta! \n");
            i++;
        }
    }
    printf("Retornando...\n");
    return 1;
}

int main(){
    int numeroPedido, opcao, variavelControle, i;
    double valor, somaPix = 0, somaRetirada = 0;
    char operador[9], linha[256], comando[100], confirmacao[2];
    char *token, aux[10][256];

    char dataFormatada[11];
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    sprintf(dataFormatada, "%d_%d_%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    FILE * controle;
    FILE * pix;
    FILE * retirada;
    char controlePath[256], pixPath[256], retiradaPath[256];
    sprintf(controlePath, "C:\\ControleDeCaixa\\controle.txt");
    sprintf(pixPath, "C:\\ControleDeCaixa\\Registros\\%s\\Pix (%s).csv", dataFormatada, dataFormatada);
    sprintf(retiradaPath, "C:\\ControleDeCaixa\\Registros\\%s\\Retirada (%s).csv", dataFormatada, dataFormatada);

    system("color 0f");

    controle = fopen(controlePath, "r");
    variavelControle = atoi(fgets(linha, 2, controle));
    fclose(controle);

    if(variavelControle == 0){
        controle = fopen(controlePath, "w");
        fputs("1", controle);
        fclose(controle);
        system("cd Registros");
        sprintf(comando, "mkdir Registros\\%s", dataFormatada);
        system(comando);
        sprintf(comando, "cd %s", dataFormatada);
        system(comando);
        pix = fopen(pixPath, "w");
        sprintf(linha, "Número do Pedido;Valor da Transferência\n");
        fputs(linha, pix);
        fclose(pix);
        retirada = fopen(retiradaPath, "w");
        sprintf(linha, "Autor da Retirada;Valor da Retirada\n");
        fputs(linha, retirada);
        fclose(retirada);
        }

        system("cls");

        do{
        menu();
        scanf("%d", &opcao);
        printf("\n");
        switch(opcao){
            case 1:
            printf("R$");
            scanf("%lf", &valor);
            printf("No. do pedido: ");
            scanf("%d", &numeroPedido);
            pix = fopen(pixPath, "a+");
            sprintf(linha, "%d;R$%.2lf\n", numeroPedido, valor);
            fputs(linha, pix);
            fclose(pix);
            system("cls");
            break;

            case 2:
            printf("R$");
            scanf("%lf", &valor);
            printf("Pessoa que retirou: ");
            scanf("%s", &operador);
            retirada = fopen(retiradaPath, "a+");
            sprintf(linha, "%s;R$%.2lf\n", operador, valor);
            fputs(linha, retirada);
            fclose(retirada);
            system("cls");
            break;

            case 3:
            system("cls");
            pix = fopen(pixPath, "r");
            fgets(linha, 256, pix);
            printf("No. do Pedido \t Valor da Transferencia\n");
            printf("\n");
            while(fgets(linha, 256, pix) != NULL){
                token = strtok(linha, ";");
                printf("%7s  \t \t", token);
                token = strtok(NULL, ";");
                printf("%7s\n", token);
            }
            fclose(pix);
            printf("\n");
            system("pause");
            system("cls");
            break;

            case 4:
            system("cls");
            retirada = fopen(retiradaPath, "r");
            fgets(linha, 256, retirada);
            printf("Autor da Retirada \t Valor da Retirada\n");
            printf("\n");
            while(fgets(linha, 256, retirada) != NULL){
                token = strtok(linha, ";");
                printf("%7s  \t \t", token);
                token = strtok(NULL, ";");
                printf("%7s\n", token);
            }
            fclose(retirada);
            printf("\n");
            system("pause");
            system("cls");
            break;

            case 5:
            printf("Tem certeza? [S/N]: ");
            scanf("%s", &confirmacao);
            if(strcasecmp(confirmacao, "n") == 0){
                system("cls");
                continue;
            }
            printf("Finalizando...\n");
            return 0;
            break;

            case 6:
            printf("Tem certeza? [S/N]: ");
            scanf("%s", &confirmacao);
            if(strcasecmp(confirmacao, "n") == 0){
                system("cls");
                continue;
            }
            else if(senha() == 0){
              pix = fopen(pixPath, "r");
              fgets(linha, 256, pix);
              while(fgets(linha, 256, pix) != NULL){
                token = strtok(linha, ";");
                token = strtok(NULL, ";");
                strcpy(aux[2], " ");
                for(i=2; i<strlen(token); i++){
                  sprintf(aux[1], "%c", token[i]);
                  strcat(aux[2], aux[1]);
                }
                somaPix+=atof(aux[2]);
              }
              fclose(pix);
              retirada = fopen(retiradaPath, "r");
              fgets(linha, 256, retirada);
              while(fgets(linha, 256, retirada) != NULL){
                token = strtok(linha, ";");
                token = strtok(NULL, ";");
                strcpy(aux[4], " ");
                for(i=2; i<strlen(token); i++){
                  sprintf(aux[3], "%c", token[i]);
                  strcat(aux[4], aux[3]);
                }
                somaRetirada+=atof(aux[4]);
              }
              fclose(retirada);
              printf("\n");
              printf("O total PIX: %.2lf\n", somaPix);
              printf("\n");
              printf("O total RETIRADA: %.2lf\n", somaRetirada);
              printf("\n");
              system("pause");
              printf("Salvando...");
              controle = fopen(controlePath, "w");
              fputs("0", controle);
              fclose(controle);
            }
            else {
                system("pause");
                system("cls");
                opcao = 5;
                continue;
            }
            break;

            default:
            printf("Opcao invalida!\n");
        }
    } while(opcao != 6);
    return 0;
}

void menu(){
    printf("==========================\n");
    printf("    Menu de Operacoes\n");
    printf("==========================\n");
    printf("\n");
    printf("1- Pix\n");
    printf("\n");
    printf("2- Retirada\n");
    printf("\n");
    printf("3- Listar Pix\n");
    printf("\n");
    printf("4- Listar Retiradas\n");
    printf("\n");
    printf("5- Sair\n");
    printf("\n");
    printf("6- Fechar o Caixa\n");
    printf("\n");
    printf("Digite a opcao desejada: ");
    }
