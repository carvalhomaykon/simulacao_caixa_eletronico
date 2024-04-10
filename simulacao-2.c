// ********** Banco da UFRA **********

// Importar bibliotecas que serão utilizadas durante a aplicação
#include <stdio.h>
#include <locale.h> // Usada para adicionar caracteres da língua portuguesa
#include <stdlib.h>
#include <string.h> // Utilizada para manipular strings, que no caso dessa aplicação é o Número da Conta
#include <conio.h> // Utilizado para colocar * no código

// Declarar as variáveis a respeito do número dos clientes do banco
typedef struct{
    char numero_conta[6]; // Qtd de caracteres do número da conta
    char senha[20]; //Qtd de caracteres da senha do cliente
    char banco[20]; //Qtd de caracteres do nome do banco
    int numero_agencia; // Declarar o número da agência
    float saldo; // Saldo do cliente
} cliente;

//Encapsular os códigos, para que não seja repetido os códigos
void menu(){
    system ("color 07");
    printf("|1| Adicionar Fundos\n");
    printf("|2| Consultar Saldo\n");
    printf("|3| Fazer Saque\n");
    printf("|4| Emitir Extrato\n");
    printf("|5| Sair\n");
    printf("\nDigite a sua opção: ");
}

void adicionar_fundo(float *saldo, FILE *extrato){
    float fundo;
    printf ("--- Adicionar Fundo ---\n");
    printf ("Digite a quantidade: R$ ");
    scanf ("%f", &fundo);
    *saldo += fundo;
    system ("cls");
    system ("color A0");
    printf ("\n\nFundo de R$ %.2f adicionado com sucesso.\n", fundo);
    printf ("Seu saldo é de: R$ %.2f\n\n", *saldo);
    
    fprintf (extrato, "Fundo de R$ %.2f adicionado.\n", fundo);
    fprintf (extrato, "Saldo de R$ %.2f\n\n", *saldo);
    fprintf (extrato, "-----------------------\n\n");
}

void fazer_saque(float *saldo, FILE *extrato){
    float saque;
    printf ("--- Fazer Saque --- \n");
    printf("Digite o valor do saque: R$ ");
    scanf("%f", &saque);
    if (saque <= *saldo) {
        system ("color A0");
        system ("cls");
        printf ("\n\nOperação realizada com sucesso. Retire o seu dinheiro.\n");
        *saldo -= saque;
        printf ("Seu saldo é de: R$ %.2f\n\n", *saldo);
        
        fprintf (extrato, "Saque de R$ %.2f realizado\n", saque);
        fprintf (extrato, "Saldo de R$ %.2f\n\n", *saldo);
        fprintf (extrato, "-----------------------\n\n");
    } else {
        system ("cls");
        system ("color 40");
        printf ("\n\nValor acima do seu saldo. Tente novamente!\n\n\n");
        
        fprintf (extrato, "Tentativa de retirada de saldo. No entanto, saldo abaixo do valor do saque.\n\n");
        fprintf (extrato, "-----------------------\n\n");
    }   
}

void consultar_saldo(float saldo, FILE *extrato){
    printf ("--- Consultar Saldo ---\n");
    printf("Seu saldo é de: R$ %.2f\n\n\n", saldo);
}

void emitir_extrato(FILE *extrato){
    fclose (extrato);
    printf ("--- Emitir Extrato ---\n");
    printf ("Extrato emitido com sucesso.\n\n");
    system ("color A0");
}

// Função para verificar senha
int verificar_senha (char *senha){
    char senha_correta[20];
    int i = 0;
    char ch;

    printf("Digite sua senha: ");
    
    while (1) {
        ch = getch(); // Lê o caractere digitado pelo usuário
        
        if (ch == '\r') // Se o usuário pressionar Enter, termina a leitura
            break;
        else if (ch == '\b') { // Se o usuário pressionar Backspace
            if (i > 0) {
                i--; // Retrocede para a posição anterior
                printf("\b \b"); // Apaga o caractere na tela
            }
        } 
        else {
            // Se não for Enter nem Backspace, trata como um caractere normal
            printf("*"); // Mostra um asterisco na tela
            senha_correta[i] = ch; // Armazena o caractere na senha temporária
            i++; // Avança para a próxima posição
        }
    }
    
    senha_correta[i] = '\0'; // Adiciona o caractere nulo ao final da senha
    
    printf("\n");
    
    return strcmp(senha, senha_correta) == 0;
}

int main (void){
    setlocale (LC_ALL, "");
    
    cliente clientes[3]; // Definindo 3 clientes para o exemplo
    
    strcpy (clientes[0].numero_conta, "12345");
    strcpy (clientes[0].senha, "senha123");
    strcpy (clientes[0].banco, "Banco Açai");
    clientes[0].numero_agencia = 101;
    clientes[0].saldo = 100;
    
    strcpy (clientes[1].numero_conta, "67890");
    strcpy (clientes[1].senha, "senha456");
    strcpy (clientes[1].banco, "Banco Miriti");
    clientes[1].numero_agencia = 202;
    clientes[1].saldo = 150;
    
    strcpy (clientes[2].numero_conta, "13579");
    strcpy (clientes[2].senha, "senha789");
    strcpy (clientes[2].banco, "Banco Bacuri");
    clientes[2].numero_agencia = 303;
    clientes[2].saldo = 200;
    
    int opcao1, opcao2, i;
    FILE *extrato;
    
    do { // Faça o loop enquanto a opção do cliente for diferente de 2
        system ("color 07");
        printf("--- CAIXA ELETRÔNICO UFRA ---\n");
        printf("|1| Iniciar\n");
        printf("|2| Encerrar\n\n");
        printf("Digite a sua opção: ");
        scanf("%d", &opcao1);
        system ("cls");
        getchar(); // Limpar o buffer de entrada
        
        extrato = fopen ("Extrato.txt", "w");
        
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
                        break;
                }
                
                printf ("Digite o número da sua agência: "); 
                int numero_agencia; // Cria uma variável do número da agência
                scanf ("%d", &numero_agencia); // Recebe o número da agência
                
                printf ("Digite o número da sua conta: ");
                char numero_conta[6]; // Testar e verificar posteriormente se está se encaixa na função fgets aprendida na aula de tc
                scanf ("%s", numero_conta); // Recebe o número da conta | Variável criada no código acima
                
                // Procurar o cliente pelo número da conta e agência
                for (i = 0; i < 3; i++) {
                    if (strcmp(clientes[i].numero_conta, numero_conta) == 0 && clientes[i].numero_agencia == numero_agencia) {
                        // Se o número da conta e o número da agência estiverem de acordo, irá verificar a senha
                        if (verificar_senha(clientes[i].senha)) { // Se senha estiver tudo certo. Irá entrar na conta do usuário
                            system ("cls");
                            system ("color A0");
                            printf ("Acesso realizado com sucesso.\n\n");
                            system ("pause");
                            system ("cls");
                            
                            fprintf (extrato, "--- Banco %s ---\n\n", clientes[i].banco);
                            fprintf (extrato, "Número Conta: %s\n", clientes[i].numero_conta);
                            fprintf (extrato, "Número da Agência: %d\n\n", clientes[i].numero_agencia);
                            fprintf (extrato, "-----------------------\n\n");
                            
                            printf("Bem-Vindo ao %s\n\n", clientes[i].banco);
                            do {
                                //system ("cls");
                                menu();
                                scanf("%d", &opcao2);
                                system ("cls");
                                switch (opcao2) {
                                    case 1:
                                        adicionar_fundo(&clientes[i].saldo, extrato);
                                        system ("\n\npause");
                                        system ("cls");
                                        break;
                                    case 2:
                                        consultar_saldo(clientes[i].saldo, extrato);
                                        system ("\n\npause");
                                        system ("cls");
                                        break;
                                    case 3:
                                        fazer_saque(&clientes[i].saldo, extrato);
                                        system ("\n\npause");
                                        system ("cls");
                                        break;
                                    case 4:
                                        emitir_extrato(extrato);
                                        system ("\n\npause");
                                        system ("cls");
                                        break;
                                    case 5:
                                        printf ("Encerrando acesso!\n\n");
                                        system ("pause");
                                        system ("cls");
                                        break;
                                    default:
                                        printf("Opção inválida.\n\n");
                                        system ("\n\npause");
                                        system ("cls");
                                }
                            } while (opcao2 != 5);
                            break;
                        } 
                        else {
                            printf("\nSenha incorreta.\n\n");  
                            system ("\npause"); 
                            system ("cls");   
                            break;                     
                        }
                    }
                }
                if ((strcmp(clientes[i].numero_conta, numero_conta) != 0 && clientes[i].numero_agencia != numero_agencia)){
                    system ("cls");
                    system ("color 40");
                    printf ("Conta não encontrada!\n\n\n");
                    system ("\npause"); 
                    system ("cls");  
                } 
            break;
            
            case 2:
                break;
            
            default:
                printf("Opção inválida.\n\n");
        }
    } while (opcao1 != 2);
    fclose (extrato);
    
    printf("Programa encerrado!\n\n");

    return 0;
}