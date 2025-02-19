#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
	char nome[50];
	int numConta, senhaNum;
	float saldo;
} conta;

void menu(conta banco[]);
void create(conta banco[]);
void acess(conta banco[]);
void menuConta(conta banco[], int count);
void deposit(conta banco[], int count);
void saldo(conta banco[], int count);
void transf(conta banco[], int count);
void transferindo(conta banco[], int count, int flag, float trans);
void cls();

int main(){
	setlocale(LC_ALL, "Portuguese");
	conta contas[MAX];
	
	menu(contas);
	
	return 0;
}

void menu(conta banco[]){
	int opc;
	
	do{
		printf("=== MENU ===\n");
		printf("1 - Criar conta.\n");
		printf("2 - Acessar conta.\n");
		printf("0 - Sair.\n");
		printf("Opção: ");
	
		scanf("%d", &opc);
		switch(opc)
		{
		case 1:
			create(banco);
			break;
		case 2:
			acess(banco);
			break;
		case 0:
			cls();
			printf("Saindo...\n");
			break;
		default:
			printf("Opção incorreta! Tente novamente: ");
			break;
		}
	}while(opc != 0);
}

void create(conta banco[]){
	static int count = 0;
	int opc;
	
	while(count < MAX){
		cls();
		printf("Vamos cadastrar sua conta: ");
		printf("\nDigite seu nome: ");
		getchar();
		fgets(banco[count].nome, sizeof(banco[count].nome), stdin);
        banco[count].nome[strcspn(banco[count].nome, "\n")] = '\0';
        
        printf("Digite o número da conta: ");
        scanf("%d", &banco[count].numConta);
        
        printf("Digite a senha: ");
        scanf("%d", &banco[count].senhaNum);
        
        deposit(banco, count);
		count++;
		
		if(count == MAX){
			cls();
            printf("Limite de contas atingido.\n\n");
            break;
		}
		
		printf("\nDeseja cadastrar outra conta? (0 - Não, 1 - Sim): ");
        scanf("%d", &opc);
        if(opc == 0){
        	cls();
        	break;
		}
	}
}

void acess(conta banco[]){
	int i, flag = -1, count = 0, auxConta, auxSenha; 
	cls();
	
	do{
		printf("Digite o numero da sua conta: ");
		scanf("%d", &auxConta);
		printf("Digite sua senha: ");
		scanf("%d", &auxSenha);
		
		for(i = 0; i < MAX; i++){
			if(auxConta == banco[i].numConta && auxSenha == banco[i].senhaNum){
				flag = i;
				break;
			}
		}
		
		if(flag != -1){
			cls();
			printf("Acesso Garantido! Bem-vindo(a) %s\n", banco[i].nome);
			menuConta(banco, flag);
			break;
		} else if(count == 3){
			cls();
			printf("Número de tentativas excedeu.");
			break;
		} else {
			printf("Conta e/ou senha estão incorretos! Tente novamente:\n");
			count++;
		}
	}while(count < 3);
}

void menuConta(conta banco[], int count){
	int opc;
	
	do{
		printf("\n=== Menu Conta ===\n");
		printf("1 - Fazer deposito.\n");
		printf("2 - Verificar saldo.\n");
		printf("3 - Transferir dinheiro.\n");
		printf("0 - Sair\n");
		printf("Opção: ");
		scanf("%d", &opc);
		cls();
		
		switch(opc){
            case 1:
                deposit(banco, count);
                break;
            case 2:
                saldo(banco, count);
                break;
            case 3:
            	if(banco[count].saldo == 0){
					printf("\nSua conta não possui saldo para fazer transferencia, primeiro faça um deposito.\n");
				} else{
					transf(banco, count);
				}
                break;
            case 0:
                printf("Redirecionado para o menu principal...\n\n");
                break;
            default:
                printf("Opção incorreta! Tente novamente.\n");
                break;
		}
	}while(opc != 0);
}

void deposit(conta banco[], int count){
	float auxSaldo;
	printf("Digite o saldo a ser depositado: ");
	scanf("%f", &auxSaldo);
	banco[count].saldo += auxSaldo;
	cls();
	printf("Deposito feito com sucesso!\n");
}

void saldo(conta banco[], int count){
	printf("O saldo é: %0.2f\n", banco[count].saldo);
}

void transf(conta banco[], int count){
	int i, auxConta, auxSenha, flag = -1, contador = 0;
	float trans;
	
	printf("Qual o numero da conta de qual deseja fazer a transferencia: ");
	scanf("%d", &auxConta);
	
	for(i = 0; i < MAX; i++){
		if(auxConta == banco[i].numConta){
			flag = i;
			break;
		}
	}
	
	if(flag == -1){
		printf("Conta inexistente, confirme o número da conta.");
	} else {
		printf("Você deseja fazer uma transferencia para %s, conta %d, de qual valor: ", banco[flag].nome, banco[flag].numConta);
		scanf("%f", &trans);

		do{
			printf("Digite sua senha: ");
			scanf("%d", &auxSenha);
		
			if(auxSenha == banco[count].senhaNum){
				printf("\nFazendo a transferencia!\n");
				transferindo(banco, count, flag, trans);
				break;
			} else if(contador == 3){
				printf("Número de tentativas excedido.");
				break;
			} else {
				printf("Conta e/ou senha estão incorretos! Tente novamente: ");
				contador++;
			}
		}while(contador < 3);
	}
}

void transferindo(conta banco[], int count, int flag, float trans){
	if(banco[count].saldo < trans){
		printf("Você não tem saldo suficiente para esta transação!\n");
	} else {
		banco[count].saldo -= trans;
		banco[flag].saldo += trans;
		printf("Transferencia concluida!\n");
	}
}

void cls(){
	system("cls");
}