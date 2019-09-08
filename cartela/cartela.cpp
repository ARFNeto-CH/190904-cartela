
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"

using namespace std;


class Cartela
{
public:
	int		tamanho;
	int		limite;
	int*	valores;
	string	nome;

public:

	Cartela(string n, int t, int l)
	{
		/*
		Construtor com parâmetros

		Cria cartela para o jogador de nome n, com n numeros e 
		limite l, e preenche com numeros aleatorios em ordem crescente

		*/
		nome = n;
		tamanho = t;
		limite = l;
		cout << "Criando cartela '" <<
			nome <<
			"' com " << tamanho << " valores entre 1 e " << limite << endl;
		valores = new int[tamanho];
		int v;
		// pra vida ficar mais fácil inicia todos os valores
		// com um valor maior que o limite
		for (int i = 0; i < tamanho; i++) valores[i] = limite + 1;
		srand((int)time(NULL));
		// aqui vamos preencher a cartela
		// um loop simples: a cada vez retorna um
		// numero aleatorio. Como na cartela do bingo
		// os valores ficam em ordem crescente
		for (int i = 0; i < tamanho;)
		{	// total de valores = tamanho
			v = rand() % limite + 1; // um valor entre 1 e o limite
			for (int n = 0; n < tamanho; n++)
			{
				if (valores[n] > v)
				{	// achou o lugar: desloca todos pra abrir posicao
					for (int j = tamanho - 1; j >= n; j--)
					{
						if (valores[j] < limite + 1)
						{
							valores[j + 1] = valores[j];
						}	// end if
					}	// end for
					valores[n] = v;
					i++;
					break;
				}
				if (valores[n] == v) break;
			}	// end for n
		}	// end for i
	}	// end Cartela()


	Cartela()
	{
		nome = "CARTELA";	// nome padrao
		tamanho = 25;
		limite = 75;
		int base = 0;
		int faixa = 15;
		//cout << "Criando cartela padrao '" <<
		//	nome <<
		//	"' com " << tamanho << " valores entre 1 e " << limite << endl;
		valores = new int[tamanho];
		int v;
		for (int i = 0; i < tamanho; i++) valores[i] = limite + 1;
		// aqui vamos preencher a cartela
		// um loop simples: a cada vez retorna um
		// numero aleatorio. Como na cartela do bingo
		// os valores ficam em ordem crescente
		for (int i = 0; i < tamanho;)
		{	// total de valores = tamanho
			v = rand() % faixa + 1; // um valor entre 1 e o limite da faixa
			for (int n = 0; n < tamanho; n++)
			{
				if (valores[n] > (base + v))
				{	// achou o lugar: desloca todos pra abrir posicao
					for (int j = tamanho - 1; j >= n; j--)
					{
						if (valores[j] < limite + 1)
						{
							valores[j + 1] = valores[j];
						}	// end if
					}	// end for
					valores[n] = base + v;
					// achei o número n. se completou a faixa avanca
					if (i % 5 == 4) base += faixa;
					i++;
					break;
				}
				if (valores[n] == (base +v )) break;
			}	// end for n
		}	// end for i

	}	// end Cartela()


	~Cartela()
	{ 
		cout << 
			"Cartela: Destruindo cartela '" << 
			nome <<
			"' com " << tamanho <<
			" valores entre 1 e " << limite
			<< endl;
		delete [] valores;
	};


	int existe(unsigned int valor)
	{
		for (int i = 0; i < tamanho; i++)
		{
			if (valores[i] == valor)
				return valor;
		}	// end for
		return -1;
	}	// end existe()


	static int init()
	{
		srand((int)time(NULL));
		return 0;
	}	// end init()


	int mostra()
	{
		cout <<
			"\n    Cartela '" << nome <<
			"' com " << tamanho << 
			" valores. Limite: " <<	limite 
			<< endl;
		for (int i=0; i<tamanho; i++)
		{
			cout << valores[i] << "\t";
			if (i%5 == 4) cout << endl;
		}	// end for
		cout << endl;
		return 0;
	}	// end mostra()

	void muda_nome(string n) { nome = n; }

};	// end class Cartela

