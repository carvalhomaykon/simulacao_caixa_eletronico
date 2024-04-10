// ********** Banco da UFRA **********

// Importar bibliotecas que ser�o utilizadas durante a aplica��o
#include <stdio.h>
#include <locale.h> // Usada para adicionar caracteres da l�ngua portuguesa
#include <stdlib.h>
#include <string.h> // Utilizada para manipular strings, que no caso dessa aplica��o � o N�mero da Conta
#include <conio.h> // Utilizado para colocar * no c�digo

// Declarar as vari�veis a respeito do n�mero dos clientes do banco
typedef struct{
    char numero_conta[6]; // Qtd de caracteres do n�mero da conta
    char senha[20]; //Qtd de caracteres da senha do cliente
    char banco[20]; //Qtd de caracteres do nome do banco
    int numero_agencia; // Declarar o n�mero da ag�ncia
    float saldo; // Saldo do cliente
} cliente;

//Encapsular os c�digos, para que n�o seja repetido os c�digos
void menu(){
    system ("color 07");
    printf("|1| Adicionar Fundos\n");
    printf("|2| Consultar Saldo\n");
    printf("|3| Fazer Saque\n");
    printf("|4| Emitir Extrato\n");
    printf("|5| Sair\n");
    printf("\nDigite a sua op��o: ");
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
    printf ("Seu saldo � de: R$ %.2f\n\n", *saldo);
    
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
        printf ("\n\nOpera��o realizada com sucesso. Retire o seu dinheiro.\n");
        *saldo -= saque;
        printf ("Seu saldo � de: R$ %.2f\n\n", *saldo);
        
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
    printf("Seu saldo � de: R$ %.2f\n\n\n", saldo);
}

void emitir_extrato(FILE *extrato){
    fclose (extrato);
    printf ("--- Emitir Extrato ---\n");
    printf ("Extrato emitido com sucesso.\n\n");
    system ("color A0");
}

// Fun��o para verificar senha
int verificar_senha (char *senha){
    char senha_correta[20];
    int i = 0;
    char ch;

    printf("Digite sua senha: ");
    
    while (1) {
        ch = getch(); // L� o caractere digitado pelo usu�rio
        
        if (ch == '\r') // Se o usu�rio pressionar Enter, termina a leitura
            break;
        else if (ch == '\b') { // Se o usu�rio pressionar Backspace
            if (i > 0) {
                i--; // Retrocede para a posi��o anterior
                printf("\b \b"); // Apaga o caractere na tela
            }
        } 
        else {
            // Se n�o for Enter nem Backspace, trata como um caractere normal
            printf("*"); // Mostra um asterisco na tela
            senha_correta[i] = ch; // Armazena o caractere na senha tempor�ria
            i++; // Avan�a para a pr�xima posi��o
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
    strcpy (clientes[0].banco, "Banco A�ai");
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
    
    do { // Fa�a o loop enquanto a op��o do cliente for diferente de 2
        system ("color 07");
        printf("--- CAIXA ELETR�NICO UFRA ---\n");
        printf("|1| Iniciar\n");
        printf("|2| Encerrar\n\n");
        printf("Digite a sua op��o: ");
        scanf("%d", &opcao1);
        system ("cls");
        getchar(); // Limpar o buffer de entrada
        
        extrato = fopen ("Extrato.txt", "w");
        
        switch (opcao1) {
            case 1:
                printf("Escolha o banco:\n");
                printf("|1| Banco A�ai\n");
                printf("|2| Banco Miriti\n");
                printf("|3| Banco Bacuri\n\n");
                printf("Digite sua escolha: ");
                int banco_escolhido;
                scanf("%d", &banco_escolhido);
                system("cls");
                
                switch (banco_escolhido) {
                    case 1:
                        printf("Bem-vindo ao Banco A�ai!\n\n");
                        break;
                    case 2:
                        printf("Bem-vindo ao Banco Miriti!\n\n");
                        break;
                    case 3:
                        printf("Bem-vindo ao Banco Bacuri!\n\n");
                        break;
                    default:
                        printf("Op��o inv�lida!\n\n");
                        break;
                }
                
                printf ("Digite o n�mero da sua ag�ncia: "); 
                int numero_agencia; // Cria uma vari�vel do n�mero da ag�ncia
                scanf ("%d", &numero_agencia); // Recebe o n�mero da ag�ncia
                
                printf ("Digite o n�mero da sua conta: ");
                char numero_conta[6]; // Testar e verificar posteriormente se est� se encaixa na fun��o fgets aprendida na aula de tc
                scanf ("%s", numero_conta); // Recebe o n�mero da conta | Vari�vel criada no c�digo acima
                
                // Procurar o cliente pelo n�mero da conta e ag�ncia
                for (i = 0; i < 3; i++) {
                    if (strcmp(clientes[i].numero_conta, numero_conta) == 0 && clientes[i].numero_agencia == numero_agencia) {
                        // Se o n�mero da conta e o n�mero da ag�ncia estiverem de acordo, ir� verificar a senha
                        if (verificar_senha(clientes[i].senha)) { // Se senha estiver tudo certo. Ir� entrar na conta do usu�rio
                            system ("cls");
                            system ("color A0");
                            printf ("Acesso realizado com sucesso.\n\n");
                            system ("pause");
                            system ("cls");
                            
                            fprintf (extrato, "--- Banco %s ---\n\n", clientes[i].banco);
                            fprintf (extrato, "N�mero Conta: %s\n", clientes[i].numero_conta);
                            fprintf (extrato, "N�mero da Ag�ncia: %d\n\n", clientes[i].numero_agencia);
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
                                        printf("Op��o inv�lida.\n\n");
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
                    printf ("Conta n�o encontrada!\n\n\n");
                    system ("\npause"); 
                    system ("cls");  
                } 
            break;
            
            case 2:
                break;
            
            default:
                printf("Op��o inv�lida.\n\n");
        }
    } while (opcao1 != 2);
    fclose (extrato);
    
    printf("Programa encerrado!\n\n");

    return 0;
}