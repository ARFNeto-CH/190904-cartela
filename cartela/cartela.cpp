#pragma once
#include <iomanip>
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


	Cartela::Cartela()
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


	int Cartela::existe(unsigned int valor)
	{
		for (int i = 0; i < tamanho; i++)
		{
			if (valores[i] == valor)
				return valor;
		}	// end for
		return -1;
	}	// end existe()


	int Cartela::mostra()
	{
		cout <<
			"\n    Cartela '" << nome <<
			"' com " << tamanho <<
			" valores. Limite: " << limite
			<< endl;
		for (int i = 0; i < tamanho; i++)
		{
			cout << valores[i] << "\t";
			if (i % 5 == 4) cout << endl;
		}	// end for
		cout << endl;
		return 0;
	}	// end mostra()


	int Cartela::mostraXY(short X, short Y)
	{	// mostra a cartela a partir da posição (x,y) na tela
		// em principio igual a anterior, apenas posiciona o 
		// cursor antes de imprimir cada linha
		int		 i;
		HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		COORD	 coord;
		coord.X = X;
		coord.Y = Y;
		// precisamos saber a cor orginal para restaurar a tela
		GetConsoleScreenBufferInfo(H, &info);
		SetConsoleCursorPosition(H, coord);
		cout <<	"'" << nome << "'";
		coord.X = X;
		coord.Y++;
		SetConsoleCursorPosition(H, coord);
		for (i = 0; i < tamanho; i++)
		{
			// so pra testar vamos usar VERDE para os valores pares
			// o que a gente quer e usar VERDE para os que ja sairam
			// no bingo
			if (i % 2 == 0)
			{
				SetConsoleTextAttribute(H, (FOREGROUND_GREEN));
				cout << setfill('0') << setw(2) << valores[i] << "  ";
				SetConsoleTextAttribute(H, (WORD)info.wAttributes);
			}else
			{
				cout << setfill('0') << setw(2) << valores[i] << "  ";
			}	// end if
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
	}	// end mostra()

	void Cartela::muda_nome(string n) { nome = n; }
