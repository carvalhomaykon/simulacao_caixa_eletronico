// ********** Banco da UFRA **********

// Importar bibliotecas que serão utilizadas durante a aplicação
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char numero_conta[6];
    char senha[20];
    char banco[20];
    int numero_agencia;
    float saldo;
} cliente;

void menu(){
    system("color 07");
    printf("|1| Adicionar Fundos\n");
    printf("|2| Consultar Saldo\n");
    printf("|3| Fazer Saque\n");
    printf("|4| Emitir Extrato\n");
    printf("|5| Sair\n");
    printf("\nDigite a sua opção: ");
}

void adicionar_fundo(float *saldo, FILE *extrato){
    float fundo;
    printf("--- Adicionar Fundo ---\n");
    printf("Digite a quantidade: R$ ");
    scanf("%f", &fundo);
    *saldo += fundo;
    system("cls");
    system("color A0");
    printf("\n\nFundo de R$ %.2f adicionado com sucesso.\n", fundo);
    printf("Seu saldo é de: R$ %.2f\n\n", *saldo);
    
    if (fprintf(extrato, "Fundo de R$ %.2f adicionado.\n", fundo) < 0) {
        printf("Erro ao escrever no arquivo de extrato.\n");
    }
    if (fprintf(extrato, "Saldo de R$ %.2f\n\n", *saldo) < 0) {
        printf("Erro ao escrever no arquivo de extrato.\n");
    }
    if (fprintf(extrato, "-----------------------\n\n") < 0) {
        printf("Erro ao escrever no arquivo de extrato.\n");
    }
}

void fazer_saque(float *saldo, FILE *extrato){
    float saque;
    printf("--- Fazer Saque --- \n");
    printf("Digite o valor do saque: R$ ");
    scanf("%f", &saque);
    if (saque <= *saldo) {
        system("color A0");
        system("cls");
        printf("\n\nOperação realizada com sucesso. Retire o seu dinheiro.\n");
        *saldo -= saque;
        printf("Seu saldo é de: R$ %.2f\n\n", *saldo);
        
        if (fprintf(extrato, "Saque de R$ %.2f realizado\n", saque) < 0) {
            printf("Erro ao escrever no arquivo de extrato.\n");
        }
        if (fprintf(extrato, "Saldo de R$ %.2f\n\n", *saldo) < 0) {
            printf("Erro ao escrever no arquivo de extrato.\n");
        }
        if (fprintf(extrato, "-----------------------\n\n") < 0) {
            printf("Erro ao escrever no arquivo de extrato.\n");
        }
    } else {
        system("cls");
        system("color 40");
        printf("\n\nValor acima do seu saldo. Tente novamente!\n\n\n");
        
        if (fprintf(extrato, "Tentativa de retirada de saldo. No entanto, saldo abaixo do valor do saque.\n\n") < 0) {
            printf("Erro ao escrever no arquivo de extrato.\n");
        }
        if (fprintf(extrato, "-----------------------\n\n") < 0) {
            printf("Erro ao escrever no arquivo de extrato.\n");
        }
    }   
}

void consultar_saldo(float saldo, FILE *extrato){
    printf("--- Consultar Saldo ---\n");
    printf("Seu saldo é de: R$ %.2f\n\n\n", saldo);
}

void emitir_extrato(FILE *extrato){
    fclose(extrato);
    printf("--- Emitir Extrato ---\n");
    printf("Extrato emitido com sucesso.\n\n");
    system("color A0");
}

int verificar_senha(char *senha){
    char senha_correta[20];
    int i = 0;
    char ch;

    printf("Digite sua senha: ");
    
    while (1) {
        ch = getch();
        
        if (ch == '\r') 
            break;
        else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } 
        else {
            printf("*");
            senha_correta[i] = ch;
            i++;
        }
    }
    
    senha_correta[i] = '\0';
    
    printf("\n");
    
    return strcmp(senha, senha_correta) == 0;
}

int main(void){
    setlocale(LC_ALL, "");
    
    cliente clientes[3];
    
    strcpy(clientes[0].numero_conta, "12345");
    strcpy(clientes[0].senha, "senha123");
    strcpy(clientes[0].banco, "Banco Açai");
    clientes[0].numero_agencia = 101;
    clientes[0].saldo = 100;
    
    strcpy(clientes[1].numero_conta, "67890");
    strcpy(clientes[1].senha, "senha456");
    strcpy(clientes[1].banco, "Banco Miriti");
    clientes[1].numero_agencia = 202;
    clientes[1].saldo = 150;
    
    strcpy(clientes[2].numero_conta, "13579");
    strcpy(clientes[2].senha, "senha789");
    strcpy(clientes[2].banco, "Banco Bacuri");
    clientes[2].numero_agencia = 303;
    clientes[2].saldo = 200;
    
    int opcao1, opcao2, i;
    FILE *extrato;
    
    do {
    	system ("cls");
        system("color 07");
        printf("--- CAIXA ELETRÔNICO UFRA ---\n");
        printf("|1| Iniciar\n");
        printf("|2| Encerrar\n\n");
        printf("Digite a sua opção: ");
        scanf("%d", &opcao1);
        system("cls");
        getchar(); 
        
        extrato = fopen("Extrato.txt", "w");
        
        if (extrato == NULL) {
            printf("Erro ao abrir o arquivo de extrato.\n");
            exit(1);
        }
        
        switch (opcao1) {
            case 1:
                printf("Escolha o banco:\n");
                printf("|1| Banco Açai\n");
                printf("|2| Banco Miriti\n");
                printf("|3| Banco Bacuri\n\n");
                printf("Digite sua escolha: ");
                int banco_escolhido;
                scanf("%d", &banco_escolhido);
                system("cls");
                
                switch (banco_escolhido) {
                    case 1:
                        printf("Bem-vindo ao Banco Açai!\n\n");
                        break;
                    case 2:
                        printf("Bem-vindo ao Banco Miriti!\n\n");
                        break;
                    case 3:
                        printf("Bem-vindo ao Banco Bacuri!\n\n");
                        break;
                    default:
                        printf("Opção inválida!\n\n");
                        continue; // Volta ao início do loop
                }
                
                printf("Digite o número da sua agência: "); 
                int numero_agencia;
                scanf("%d", &numero_agencia);
                
                printf("Digite o número da sua conta: ");
                char numero_conta[6];
                scanf("%s", numero_conta);
                
                int cliente_encontrado = 0;
                for (i = 0; i < 3; i++) {
                    if (strcmp(clientes[i].numero_conta, numero_conta) == 0 && clientes[i].numero_agencia == numero_agencia) {
                        cliente_encontrado = 1;
                        if (strcmp(clientes[i].banco, "Banco Açai") != 0 && banco_escolhido == 1) {
                            printf("Essa conta não pertence ao Banco Açai.\n\n");
                            cliente_encontrado = 0;
                            system("pause");
                            system("cls");
                            break;
                        } else if (strcmp(clientes[i].banco, "Banco Miriti") != 0 && banco_escolhido == 2) {
                            printf("Essa conta não pertence ao Banco Miriti.\n\n");
                            cliente_encontrado = 0;
                            system("pause");
                            system("cls");
                            break;
                        } else if (strcmp(clientes[i].banco, "Banco Bacuri") != 0 && banco_escolhido == 3) {
                            printf("Essa conta não pertence ao Banco Bacuri.\n\n");
                            cliente_encontrado = 0;
                            system("pause");
                            system("cls");
                            break;
                        } else {
                            if (verificar_senha(clientes[i].senha)) {
                                system("cls");
                                system("color A0");
                                printf("Acesso realizado com sucesso.\n\n");
                                system("pause");
                                system("cls");
                                
                                fprintf(extrato, "--- Banco %s ---\n\n", clientes[i].banco);
                                fprintf(extrato, "Número Conta: %s\n", clientes[i].numero_conta);
                                fprintf(extrato, "Número da Agência: %d\n\n", clientes[i].numero_agencia);
                                fprintf(extrato, "-----------------------\n\n");
                                
                                printf("Bem-Vindo ao %s\n\n", clientes[i].banco);
                                do {
                                    menu();
                                    scanf("%d", &opcao2);
                                    system("cls");
                                    switch (opcao2) {
                                        case 1:
                                            adicionar_fundo(&clientes[i].saldo, extrato);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 2:
                                            consultar_saldo(clientes[i].saldo, extrato);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 3:
                                            fazer_saque(&clientes[i].saldo, extrato);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 4:
                                            emitir_extrato(extrato);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 5:
                                            printf("Encerrando acesso!\n\n");
                                            system("pause");
                                            system("cls");
                                            break;
                                        default:
                                            printf("Opção inválida.\n\n");
                                            system("pause");
                                            system("cls");
                                    }
                                } while (opcao2 != 5);
                                break;
                            } else {
                                printf("\nSenha incorreta.\n\n");  
                                system("pause"); 
                                system("cls");   
                                break;                     
                            }
                        }
                    }
                }
                if (!cliente_encontrado) {
                    printf("Conta não encontrada!\n\n\n");
                }
                break;
            
            case 2:
                break;
            
            default:
                printf("Opção inválida.\n\n");
        }
        
        fclose(extrato);
    } while (opcao1 != 2);
    
    printf("Programa encerrado!\n\n");

    return 0;
}
