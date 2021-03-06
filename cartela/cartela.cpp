#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "windows.h"
#include "Cartela.h"

using namespace std;


	Cartela::Cartela(string n, int t, int l)
	{
		/*
		Construtor com par�metros

		Cria cartela para o jogador de nome n, com n numeros e 
		limite l, e preenche com numeros aleatorios em ordem crescente

		*/
		nome = n;
		hits = 0;
		tamanho = t;
		limite = l;
		cout << "Criando cartela '" <<
			nome <<
			"' com " << tamanho << " valores entre 1 e " << limite << endl;
		valores = new int[tamanho];
		int v;
		// pra vida ficar mais f�cil inicia todos os valores
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


	Cartela::Cartela()
	{
		nome = "CARTELA";	// nome padrao
		tamanho = 25;
		limite = 75;
		int base = 0;
		int faixa = 15;
		hits = 0;
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
					// achei o n�mero n. se completou a faixa avanca
					if (i % 5 == 4) base += faixa;
					i++;
					break;
				}
				if (valores[n] == (base +v )) break;
			}	// end for n
		}	// end for i
	}	// end Cartela()


	Cartela::~Cartela()
	{ 
		//cout << 
		//	"Cartela: Destruindo cartela '" << 
		//	nome <<
		//	"' com " << tamanho <<
		//	" valores entre 1 e " << limite
		//	<< endl;
		delete [] valores;
	};


	short	Cartela::get_hits()
	{
		return hits;
	};


	int		Cartela::set_numero()
	{
		hits += 1;
		return hits;
	}	// end marca_numero()


	int		Cartela::mostra()
	{
		cout <<
			"\n    Cartela '" << nome <<
			"' com " << tamanho <<
			" valores. Limite: " << limite <<
			" marcados: " << hits <<
			endl;
		for (int i = 0; i < tamanho; i++)
		{
			cout << valores[i] << "\t";
			if (i % 5 == 4) cout << endl;
		}	// end for
		cout << endl;
		return 0;
	}	// end mostra()


	int		Cartela::mostraXY(short X, short Y, short* cor)
	{	// mostra a cartela a partir da posi��o (x,y) na tela
		// em principio igual a anterior mostra(), apenas posiciona o 
		// cursor antes de imprimir cada linha
		// usa as cores como marcadas no vetor 'cor'
		int		 i;
		HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD	 coord;
		coord.X = X;
		coord.Y = Y;
 		SetConsoleCursorPosition(H, coord);
		SetConsoleTextAttribute(H, cor[0]);
		cout <<
			"'" << nome << "' [" <<
			setfill('0') << setw(3) << hits << "]";
		coord.X = X;
		coord.Y++;
		SetConsoleCursorPosition(H, coord);
		// mostra valores[]
		for (i=0; i<tamanho; i++)
		{
			SetConsoleTextAttribute (H, cor[valores[i]]);
			cout << setfill('0') << setw(2) << valores[i] << "  ";
			SetConsoleTextAttribute(H, cor[0]);
			if (i % 5 == 4)
			{
				coord.X = X;
				coord.Y++;
				SetConsoleCursorPosition(H, coord);
			}	// end if
		}	// end for
		coord.X = X;
		coord.Y++;
		SetConsoleCursorPosition(H, coord);
		return 0;
	}	// end mostraXY()


	void	Cartela::muda_nome(string n) { nome = n; }
