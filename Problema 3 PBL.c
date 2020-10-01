/******************************************************************************************
Autor: Roberto Maia Rodrigues Junior
Componente Curricular: MI - Algoritmos
Concluido em: 19/07/2018
Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct celula{
	char nome[30], time[30], posicao[15];
	int camisa,nascimento,sorteio; // Vari�vel para saber em que sorteio foi feito;
	struct celula *prox;	
};
typedef struct celula dados;
dados* cadastrar_jogador(dados *); 
dados* editar_camisa(dados*);
dados* remover_jogador( dados*);
dados* sortear_jogador(dados*,int,int*);
void filtrar_posicao(dados*);
void exibir_tudo(dados *);
void exibir_sorteados(dados*,int);
int main(){
	dados *p; 
	int *numeros_sorteados;
	int comando_arquivo,numero_do_sorteio=0;
	FILE *entrada,*saida;
	p = (dados*)malloc(sizeof (dados)); // Alocando mem�ria para a lista encadeada
    p->prox = NULL; // Criando o inicio da lista
	entrada=freopen("entrada.txt","r",stdin); // Redirecionando a entrada padr�o do programa para o arquivo entrada.txt
	saida=freopen("saida.txt","w",stdout); // Redirecionando a saida padr�o do programa para o arquivo saida.txt
	srand(time(NULL));
	printf("--------------------------------------------------------------------------------------------\n");
	printf("SISTEMA ANTIDOPING | COPA DO MUNDO 2018\n");
	printf("--------------------------------------------------------------------------------------------\n");
	do{
		fscanf(stdin,"%d\n",&comando_arquivo);
 		switch(comando_arquivo){
			case 1: 
				p=cadastrar_jogador(p); // Comando 1 � respons�vel por realizar o cadastro de jogadores, o ponteiro 'p' foi utilizado como par�metro para a fun��o.
				break;
			case 2:
				p=editar_camisa(p); // Comando 2 � respons�vel por editar o n�mero da camisa de um jogador, o ponteiro 'p' foi utilizado como par�metro para a fun��o.
				break;
			case 3:
				p=remover_jogador(p); //  Comando 3 � respons�vel por remover um jogador da lista, o ponteiro 'p' foi utilizado como par�metro para a fun��o.
				break;
			case 4: 
				numero_do_sorteio++;
				p=sortear_jogador(p,numero_do_sorteio,numeros_sorteados); // Comando 4 � respons�vel por sortear um n�mero espec�fico de jogadores, foi utilizado como um dos par�metros a vari�vel numerodosorteio(respons�vel por indicar qual o n�mero do sorteio que est� sendo realizado).
				break;
			case 5:
				filtrar_posicao(p); // Comando 5 � respons�vel por fazer a filtragem dos jogadores sorteados a partir de uma posi��o espec�fica.
				break;
			case 6:
				exibir_tudo(p); // Comando 6 � respons�vel por exibir todos os jogadores pertecentes a lista encadeada.
				break;
			case 7:
				exibir_sorteados(p,numero_do_sorteio); //  Comando 7 � respons�vel por exibir os jogadores que foram sorteados na fun��o sorteio
				break;
		}
	}while(comando_arquivo!=8); // O comando 8 � respons�vel por finalizar o programa e por conta disso � a condi��o de parada do la�o de repeti��o.
	fclose(stdin);
    fclose(stdout);
    return 0;
}
dados* cadastrar_jogador(dados *p){ /*Fun��o baseada na fun��o disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *nova, *aux; // Ponteiro nova � respons�vel por alocar a nova c�lula da lista encadeada // O ponteiro aux � respons�vel por checar se o jogador a ser cadastrado n�o tinha sido previamente inserido.
	nova = (dados *)malloc(sizeof(dados)); // Alocando mem�ria para a nova c�lula da lista.
	fgets(nova->nome,30,stdin); 
	fscanf(stdin,"%d\n",&nova->nascimento);
	fgets(nova->time,30,stdin); 
	fscanf(stdin,"%d\n",&nova->camisa);
	fgets(nova->posicao,15,stdin);
	nova->nome[strcspn(nova->nome, "\n")] = 0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
	nova->time[strcspn(nova->time,"\n")]=0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
	nova->posicao[strcspn(nova->posicao, "\n")] = 0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
	nova->sorteio=0; // Esse valor ser� importante futuramente para controle do sorteio.
	/* Inser��o da nova c�lula no in�cio da lista. */
	nova->prox = p->prox; 
	p->prox = nova;
	return p; // Retornando o in�cio da lista para que as modifica��es sejam salvas.
}
dados* editar_camisa(dados *p){ /*Fun��o baseada na fun��o disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
   dados *aux;
   aux = p->prox; // Aux recebe p->prox por conta de que 'p' � a primeira parte da lista e est� vazia.
   char nome_busca[100]; // Vari�vel que recebe o nome a ser pesquisado para altera��o do n�mero da camisa.
   int novo_numero; // Vari�vel que recebe o novo n�mero da camisa.
   fgets(nome_busca,100,stdin);
   nome_busca[strcspn(nome_busca, "\n")] = 0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
   fscanf(stdin,"%d",&novo_numero);
   while (aux != NULL && strcmp (aux->nome,nome_busca)!=0) // A pesquisa gira em torno de um la�o de repeti��o que consiste em percorrer toda a lista, caso alguma c�lula tenha o nome pesquisado a altera��o ser� realizada, caso contr�rio o ponteiro estar� como NULL e exibir� a mensagem de que n�o foi encontrado jogador com tal nome.
   aux = aux->prox; 
   if(aux != NULL) {
   printf("|O n�mero da camisa do jogador %s foi alterado para %d.\n",aux->nome,novo_numero);  
   aux->camisa = novo_numero;
	}
   else{
   printf("|N�o existem jogadores cadastrados com o nome %s.\n",nome_busca);
   }
   return p; // Retornando o in�cio da lista para que as modifica��es sejam salvas.
}
dados* remover_jogador(dados *p){ /*Fun��o baseada na fun��o disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *aux1, *aux2;
	aux1= p; //  Aux1 aponta para in�cio da lista.
	aux2=p->prox; // Aux2 aponta para o elemento ap�s o in�cio da lista.
	char nome_busca[100];
	fgets(nome_busca,100,stdin);
	nome_busca[strcspn(nome_busca, "\n")] = 0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
	while (aux2 != NULL && strcmp (aux2->nome,nome_busca)!=0){ // O la�o percorre a lista at� o final, se o nome escolhido for encontrado o jogador � removido da lista, caso contr�rio o ponteiro estar� NULL e exibir� a mensagem de que n�o existe jogador com o nome desejado.
   		aux1 = aux2;
		aux2 = aux2->prox;
	}
	if(aux2 != NULL){
		aux1->prox = aux2->prox;
		free(aux2);
		printf("|Dados do jogador %s foram removidos.\n",nome_busca);
   	}
   	else{
	   printf("|N�o foi poss�vel remover o jogador %s. Cadastro n�o encontrado.\n",nome_busca);
   	}
   	return p; // Retornando o in�cio da lista para que as modifica��es sejam salvas.
}
dados* sortear_jogador(dados *p,int numero_do_sorteio,int* numeros_sorteados){ // FALTA COMENTAR E FINALIZAR A FUN��O.
	dados *aux;
	aux=p->prox;
	int i,j,quantidade_sortear,valor_rand,tamanho_lista=0,contador_posicao=0,condicao_repeticao,condicao_repeticao2=0,jogadores_nao_sorteados=0,novo_valor_rand=999;
	while(aux!=NULL){ //  La�o de repeti��o respons�vel por contabilizar quantas celulas a lista tem ao total;
		tamanho_lista++;
		if(aux->sorteio==0) //  Dados sorteio, � uma vari�vel para ter controle sobre o sorteio, jogadores sorteados tem um valor diferente de 0 na vari�vel pertencente a sua celula.
		jogadores_nao_sorteados++;
		aux=aux->prox;
	}
	fscanf(stdin,"%d\n",&quantidade_sortear);
	numeros_sorteados=(int*)malloc(quantidade_sortear*sizeof(int)); // Alocando mem�ria para um vetor que receber� os n�meros que j� foram sorteados.
	if(jogadores_nao_sorteados<quantidade_sortear) //  Caso n�o existam jogadores suficientes para sortear o programa avisar�.
	printf("N�o existem jogadores suficientes para o sorteio.\n");
	else{
		for(i=0;i<quantidade_sortear;i++){ // La�o respons�vel por executar o sorteio.
			do{
				valor_rand=1+(rand()%tamanho_lista); 
				numeros_sorteados[i]=valor_rand; // Salva o valor sorteado em um vetor, para que futuramente seja checado e evite a repeti��o de jogadores anteriormente sorteados.
				condicao_repeticao=0;
				for(j=0;j<i;j++){ // La�o para descobrir se o n�mero sorteado j� tinha sido sorteado anteriormente.
					if(numeros_sorteados[j]==numeros_sorteados[i]){
						condicao_repeticao=1; // Caso a condi��o de repeti��o seja verdadeira a vari�vel recebe o n�1 e assim entra no la�o de repeti��o.
					}
				}
			}while(condicao_repeticao==1); 
			contador_posicao=1; // O rand tem um intervalo de 1 ao n�mero m�ximo de c�lulas da lista, por conta disso a vari�vel contador_posicao � inicializada com o valor 1.
			aux=p->prox;
			while(aux!=NULL){ 
				if(contador_posicao==valor_rand){ // O la�o se repetir� at� que o n�mero da c�lula seja equivalente ao n�mero sorteado, assim "selecionando" a c�lula equivalente ao n�mero sorteado.
					if(aux->sorteio>0){ // A vari�vel sorteio que pertence a estrutura principal tem uma fun��o de controle do sorteio, pois � inicializada com valor 0 , valor que s� ser� alterado ap�s o jogador ter sido sorteado, sendo assim, caso o valor seja maior que 0 significa que o jogador j� foi sorteado.
						do{
						novo_valor_rand=1+(rand()%tamanho_lista); // J� que o n�mero foi sorteado anteriormente � gerado um novo n�mero de sorteio.
						//printf("\nnovo valor rand %d",novo_valor_rand);
						condicao_repeticao2=0;
							for(j=0;j<=i;j++){ // La�o para descobrir se o novo n�mero sorteado j� tinha sido sorteado anteriormente.
								if(numeros_sorteados[j]==novo_valor_rand)
									condicao_repeticao2=1;
							}		
						} while(condicao_repeticao2==1);
					}
					else if(aux->sorteio==0){ // Caso o jogador n�o tenha sido sorteado a vari�vel sorteio recebe o n�mero equivalente ao do sorteio realizado.
						aux->sorteio=numero_do_sorteio;
						//printf("entrou");
					}	
				}
				if(contador_posicao==novo_valor_rand && aux->sorteio==0) // Caso o novo n�mero sorteado n�o seja repetido o jogador equivalente a esse n�mero receber� o n�mero equivalente ao do sorteio realizado.
					aux->sorteio = numero_do_sorteio;
				aux=aux->prox;
				contador_posicao++; // Incrementa a vari�vel contador_posicao durante o percorrer da lista.
			}
		}
	}
	return p; // Retornando o in�cio da lista para que as modifica��es sejam salvas.
}
void filtrar_posicao( dados *p){ 
   dados *aux;
   aux = p->prox; // Aux2 aponta para o elemento ap�s o in�cio da lista.
   char posicao_busca[15],possiveis_posicoes[4][15]={"Goleiro","Zagueiro","Volante","Atacante"}; // Vari�vel utilizada como "filtro" por posi��o.
   int contador=0; // Contador utilizado para saber se existem jogadores registrados na posi��o utilizada como filtro.
   fgets(posicao_busca,15,stdin);
   posicao_busca[strcspn(posicao_busca, "\n")] = 0; //  Remo��o do \n que a fun��o fgets salva na vari�vel.
   if(strcmp(posicao_busca, possiveis_posicoes[0]) == 0 || strcmp(posicao_busca,possiveis_posicoes[1]) == 0 || strcmp(posicao_busca,possiveis_posicoes[2]) == 0 || strcmp(posicao_busca,possiveis_posicoes[3]) == 0){
   printf("--------------------------------------------------------------------------------------------\n");
   printf("JOGADORES SORTEADOS E QUE OCUPAM A POSI��O: %s\n",posicao_busca);
	   while (aux != NULL){ // O la�o percorre a lista at� o final, somente ser�o printados jogadores que foram sorteados e pertencem a posi��o escolhida para a filtragem, caso nenhum jogador sorteado perten�a a posi��o escolhida o programa indicar� que n�o existem jogadores sorteados pertencentes a essa posi��o.
	   		if(strcmp (aux->posicao,posicao_busca)==0 && aux->sorteio>0){
			   printf ("%s\t", aux->nome);
			   printf ("%s\n", aux->time);
			   contador++;
			}
			aux = aux->prox; 
		}
	   	if(contador==0){
		   printf("N�o existem jogadores sorteados nessa posicao\n",posicao_busca); 
		}
	}
	else{
		printf("--------------------------------------------------------------------------------------------\n");
		printf("POSI��O %s N�O CADASTRADA\n",posicao_busca);
	}
	printf("--------------------------------------------------------------------------------------------\n");
}
void exibir_tudo(dados *p){ /*Fun��o baseada na fun��o disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *mostrar;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("EXIBI��O DE JOGADORES CADASTRADOS\n\n");                
	for(mostrar = p->prox; mostrar != NULL; mostrar = mostrar->prox){ // Fun��o percorre a lista toda e imprime os dados dos jogadores cadastrados.
		printf ("%s\t", mostrar->nome);
		printf ("%d\t", mostrar->nascimento);
		printf ("%s\t", mostrar->time);
		printf ("%d\t", mostrar->camisa);
		printf ("%s\n", mostrar->posicao);
	}
	printf("--------------------------------------------------------------------------------------------\n");
}
void exibir_sorteados(dados*p,int numero_do_sorteio){
	dados* aux;
	int i,contador_sorteados;
	
	for(i=0;i<numero_do_sorteio;i++){ //  Percorre a lista at� o final e imprime os jogadores sorteados por sorteio realizado, caso nenhum jogador tenha sido sorteado o programa indicar� que n�o foram sorteados jogadores.
		contador_sorteados=0; 
		printf("--------------------------------------------------------------------------------------------\n");
		printf("SORTEIO N� %d\n",i+1);
		aux=p->prox; // Aux aponta para o elemento ap�s o in�cio da lista.
		while(aux!=NULL){
			if(aux->sorteio==i+1){
				printf("%s\t%s\n",aux->nome,aux->time);
				contador_sorteados++;
			}
			aux=aux->prox;
		}
	}
	if(contador_sorteados==0){ 
		printf("N�o foram sorteados jogadores\n");
	}
	printf("--------------------------------------------------------------------------------------------\n");
}
