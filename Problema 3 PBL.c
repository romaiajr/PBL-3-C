/******************************************************************************************
Autor: Roberto Maia Rodrigues Junior
Componente Curricular: MI - Algoritmos
Concluido em: 19/07/2018
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct celula{
	char nome[30], time[30], posicao[15];
	int camisa,nascimento,sorteio; // Variável para saber em que sorteio foi feito;
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
	p = (dados*)malloc(sizeof (dados)); // Alocando memória para a lista encadeada
    p->prox = NULL; // Criando o inicio da lista
	entrada=freopen("entrada.txt","r",stdin); // Redirecionando a entrada padrão do programa para o arquivo entrada.txt
	saida=freopen("saida.txt","w",stdout); // Redirecionando a saida padrão do programa para o arquivo saida.txt
	srand(time(NULL));
	printf("--------------------------------------------------------------------------------------------\n");
	printf("SISTEMA ANTIDOPING | COPA DO MUNDO 2018\n");
	printf("--------------------------------------------------------------------------------------------\n");
	do{
		fscanf(stdin,"%d\n",&comando_arquivo);
 		switch(comando_arquivo){
			case 1: 
				p=cadastrar_jogador(p); // Comando 1 é responsável por realizar o cadastro de jogadores, o ponteiro 'p' foi utilizado como parâmetro para a função.
				break;
			case 2:
				p=editar_camisa(p); // Comando 2 é responsável por editar o número da camisa de um jogador, o ponteiro 'p' foi utilizado como parâmetro para a função.
				break;
			case 3:
				p=remover_jogador(p); //  Comando 3 é responsável por remover um jogador da lista, o ponteiro 'p' foi utilizado como parâmetro para a função.
				break;
			case 4: 
				numero_do_sorteio++;
				p=sortear_jogador(p,numero_do_sorteio,numeros_sorteados); // Comando 4 é responsável por sortear um número específico de jogadores, foi utilizado como um dos parâmetros a variável numerodosorteio(responsável por indicar qual o número do sorteio que está sendo realizado).
				break;
			case 5:
				filtrar_posicao(p); // Comando 5 é responsável por fazer a filtragem dos jogadores sorteados a partir de uma posição específica.
				break;
			case 6:
				exibir_tudo(p); // Comando 6 é responsável por exibir todos os jogadores pertecentes a lista encadeada.
				break;
			case 7:
				exibir_sorteados(p,numero_do_sorteio); //  Comando 7 é responsável por exibir os jogadores que foram sorteados na função sorteio
				break;
		}
	}while(comando_arquivo!=8); // O comando 8 é responsável por finalizar o programa e por conta disso é a condição de parada do laço de repetição.
	fclose(stdin);
    fclose(stdout);
    return 0;
}
dados* cadastrar_jogador(dados *p){ /*Função baseada na função disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *nova, *aux; // Ponteiro nova é responsável por alocar a nova célula da lista encadeada // O ponteiro aux é responsável por checar se o jogador a ser cadastrado não tinha sido previamente inserido.
	nova = (dados *)malloc(sizeof(dados)); // Alocando memória para a nova célula da lista.
	fgets(nova->nome,30,stdin); 
	fscanf(stdin,"%d\n",&nova->nascimento);
	fgets(nova->time,30,stdin); 
	fscanf(stdin,"%d\n",&nova->camisa);
	fgets(nova->posicao,15,stdin);
	nova->nome[strcspn(nova->nome, "\n")] = 0; //  Remoção do \n que a função fgets salva na variável.
	nova->time[strcspn(nova->time,"\n")]=0; //  Remoção do \n que a função fgets salva na variável.
	nova->posicao[strcspn(nova->posicao, "\n")] = 0; //  Remoção do \n que a função fgets salva na variável.
	nova->sorteio=0; // Esse valor será importante futuramente para controle do sorteio.
	/* Inserção da nova célula no início da lista. */
	nova->prox = p->prox; 
	p->prox = nova;
	return p; // Retornando o início da lista para que as modificações sejam salvas.
}
dados* editar_camisa(dados *p){ /*Função baseada na função disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
   dados *aux;
   aux = p->prox; // Aux recebe p->prox por conta de que 'p' é a primeira parte da lista e está vazia.
   char nome_busca[100]; // Variável que recebe o nome a ser pesquisado para alteração do número da camisa.
   int novo_numero; // Variável que recebe o novo número da camisa.
   fgets(nome_busca,100,stdin);
   nome_busca[strcspn(nome_busca, "\n")] = 0; //  Remoção do \n que a função fgets salva na variável.
   fscanf(stdin,"%d",&novo_numero);
   while (aux != NULL && strcmp (aux->nome,nome_busca)!=0) // A pesquisa gira em torno de um laço de repetição que consiste em percorrer toda a lista, caso alguma célula tenha o nome pesquisado a alteração será realizada, caso contrário o ponteiro estará como NULL e exibirá a mensagem de que não foi encontrado jogador com tal nome.
   aux = aux->prox; 
   if(aux != NULL) {
   printf("|O número da camisa do jogador %s foi alterado para %d.\n",aux->nome,novo_numero);  
   aux->camisa = novo_numero;
	}
   else{
   printf("|Não existem jogadores cadastrados com o nome %s.\n",nome_busca);
   }
   return p; // Retornando o início da lista para que as modificações sejam salvas.
}
dados* remover_jogador(dados *p){ /*Função baseada na função disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *aux1, *aux2;
	aux1= p; //  Aux1 aponta para início da lista.
	aux2=p->prox; // Aux2 aponta para o elemento após o início da lista.
	char nome_busca[100];
	fgets(nome_busca,100,stdin);
	nome_busca[strcspn(nome_busca, "\n")] = 0; //  Remoção do \n que a função fgets salva na variável.
	while (aux2 != NULL && strcmp (aux2->nome,nome_busca)!=0){ // O laço percorre a lista até o final, se o nome escolhido for encontrado o jogador é removido da lista, caso contrário o ponteiro estará NULL e exibirá a mensagem de que não existe jogador com o nome desejado.
   		aux1 = aux2;
		aux2 = aux2->prox;
	}
	if(aux2 != NULL){
		aux1->prox = aux2->prox;
		free(aux2);
		printf("|Dados do jogador %s foram removidos.\n",nome_busca);
   	}
   	else{
	   printf("|Não foi possível remover o jogador %s. Cadastro não encontrado.\n",nome_busca);
   	}
   	return p; // Retornando o início da lista para que as modificações sejam salvas.
}
dados* sortear_jogador(dados *p,int numero_do_sorteio,int* numeros_sorteados){ // FALTA COMENTAR E FINALIZAR A FUNÇÃO.
	dados *aux;
	aux=p->prox;
	int i,j,quantidade_sortear,valor_rand,tamanho_lista=0,contador_posicao=0,condicao_repeticao,condicao_repeticao2=0,jogadores_nao_sorteados=0,novo_valor_rand=999;
	while(aux!=NULL){ //  Laço de repetição responsável por contabilizar quantas celulas a lista tem ao total;
		tamanho_lista++;
		if(aux->sorteio==0) //  Dados sorteio, é uma variável para ter controle sobre o sorteio, jogadores sorteados tem um valor diferente de 0 na variável pertencente a sua celula.
		jogadores_nao_sorteados++;
		aux=aux->prox;
	}
	fscanf(stdin,"%d\n",&quantidade_sortear);
	numeros_sorteados=(int*)malloc(quantidade_sortear*sizeof(int)); // Alocando memória para um vetor que receberá os números que já foram sorteados.
	if(jogadores_nao_sorteados<quantidade_sortear) //  Caso não existam jogadores suficientes para sortear o programa avisará.
	printf("Não existem jogadores suficientes para o sorteio.\n");
	else{
		for(i=0;i<quantidade_sortear;i++){ // Laço responsável por executar o sorteio.
			do{
				valor_rand=1+(rand()%tamanho_lista); 
				numeros_sorteados[i]=valor_rand; // Salva o valor sorteado em um vetor, para que futuramente seja checado e evite a repetição de jogadores anteriormente sorteados.
				condicao_repeticao=0;
				for(j=0;j<i;j++){ // Laço para descobrir se o número sorteado já tinha sido sorteado anteriormente.
					if(numeros_sorteados[j]==numeros_sorteados[i]){
						condicao_repeticao=1; // Caso a condição de repetição seja verdadeira a variável recebe o nº1 e assim entra no laço de repetição.
					}
				}
			}while(condicao_repeticao==1); 
			contador_posicao=1; // O rand tem um intervalo de 1 ao número máximo de células da lista, por conta disso a variável contador_posicao é inicializada com o valor 1.
			aux=p->prox;
			while(aux!=NULL){ 
				if(contador_posicao==valor_rand){ // O laço se repetirá até que o número da célula seja equivalente ao número sorteado, assim "selecionando" a célula equivalente ao número sorteado.
					if(aux->sorteio>0){ // A variável sorteio que pertence a estrutura principal tem uma função de controle do sorteio, pois é inicializada com valor 0 , valor que só será alterado após o jogador ter sido sorteado, sendo assim, caso o valor seja maior que 0 significa que o jogador já foi sorteado.
						do{
						novo_valor_rand=1+(rand()%tamanho_lista); // Já que o número foi sorteado anteriormente é gerado um novo número de sorteio.
						//printf("\nnovo valor rand %d",novo_valor_rand);
						condicao_repeticao2=0;
							for(j=0;j<=i;j++){ // Laço para descobrir se o novo número sorteado já tinha sido sorteado anteriormente.
								if(numeros_sorteados[j]==novo_valor_rand)
									condicao_repeticao2=1;
							}		
						} while(condicao_repeticao2==1);
					}
					else if(aux->sorteio==0){ // Caso o jogador não tenha sido sorteado a variável sorteio recebe o número equivalente ao do sorteio realizado.
						aux->sorteio=numero_do_sorteio;
						//printf("entrou");
					}	
				}
				if(contador_posicao==novo_valor_rand && aux->sorteio==0) // Caso o novo número sorteado não seja repetido o jogador equivalente a esse número receberá o número equivalente ao do sorteio realizado.
					aux->sorteio = numero_do_sorteio;
				aux=aux->prox;
				contador_posicao++; // Incrementa a variável contador_posicao durante o percorrer da lista.
			}
		}
	}
	return p; // Retornando o início da lista para que as modificações sejam salvas.
}
void filtrar_posicao( dados *p){ 
   dados *aux;
   aux = p->prox; // Aux2 aponta para o elemento após o início da lista.
   char posicao_busca[15],possiveis_posicoes[4][15]={"Goleiro","Zagueiro","Volante","Atacante"}; // Variável utilizada como "filtro" por posição.
   int contador=0; // Contador utilizado para saber se existem jogadores registrados na posição utilizada como filtro.
   fgets(posicao_busca,15,stdin);
   posicao_busca[strcspn(posicao_busca, "\n")] = 0; //  Remoção do \n que a função fgets salva na variável.
   if(strcmp(posicao_busca, possiveis_posicoes[0]) == 0 || strcmp(posicao_busca,possiveis_posicoes[1]) == 0 || strcmp(posicao_busca,possiveis_posicoes[2]) == 0 || strcmp(posicao_busca,possiveis_posicoes[3]) == 0){
   printf("--------------------------------------------------------------------------------------------\n");
   printf("JOGADORES SORTEADOS E QUE OCUPAM A POSIÇÃO: %s\n",posicao_busca);
	   while (aux != NULL){ // O laço percorre a lista até o final, somente serão printados jogadores que foram sorteados e pertencem a posição escolhida para a filtragem, caso nenhum jogador sorteado pertença a posição escolhida o programa indicará que não existem jogadores sorteados pertencentes a essa posição.
	   		if(strcmp (aux->posicao,posicao_busca)==0 && aux->sorteio>0){
			   printf ("%s\t", aux->nome);
			   printf ("%s\n", aux->time);
			   contador++;
			}
			aux = aux->prox; 
		}
	   	if(contador==0){
		   printf("Não existem jogadores sorteados nessa posicao\n",posicao_busca); 
		}
	}
	else{
		printf("--------------------------------------------------------------------------------------------\n");
		printf("POSIÇÃO %s NÃO CADASTRADA\n",posicao_busca);
	}
	printf("--------------------------------------------------------------------------------------------\n");
}
void exibir_tudo(dados *p){ /*Função baseada na função disponibilizada no site https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html*/
	dados *mostrar;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("EXIBIÇÃO DE JOGADORES CADASTRADOS\n\n");                
	for(mostrar = p->prox; mostrar != NULL; mostrar = mostrar->prox){ // Função percorre a lista toda e imprime os dados dos jogadores cadastrados.
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
	
	for(i=0;i<numero_do_sorteio;i++){ //  Percorre a lista até o final e imprime os jogadores sorteados por sorteio realizado, caso nenhum jogador tenha sido sorteado o programa indicará que não foram sorteados jogadores.
		contador_sorteados=0; 
		printf("--------------------------------------------------------------------------------------------\n");
		printf("SORTEIO Nº %d\n",i+1);
		aux=p->prox; // Aux aponta para o elemento após o início da lista.
		while(aux!=NULL){
			if(aux->sorteio==i+1){
				printf("%s\t%s\n",aux->nome,aux->time);
				contador_sorteados++;
			}
			aux=aux->prox;
		}
	}
	if(contador_sorteados==0){ 
		printf("Não foram sorteados jogadores\n");
	}
	printf("--------------------------------------------------------------------------------------------\n");
}
