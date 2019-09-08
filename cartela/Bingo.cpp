#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"
#include "Bingo.h"

class Bingo
{
public:
	string		nome;
	int			total_cartelas;
	Cartela* pCartelas;

	Bingo()
	{	// construtor padrao assume cinco cartelas
		Cartela::init();	// inicia o gerador srand()
		total_cartelas = 5;
		nome = "Um bingo";
		pCartelas = new (Cartela[total_cartelas]);
		string		prefixo = "cartela";
		string		nome = "";
		for (int i = 1; i <= total_cartelas; i++)
		{
			nome = prefixo;
			nome.append(to_string(i));
			pCartelas[i - 1].muda_nome(nome);
		}	// end for
	}

	Bingo(int n_cartelas)
	{	// construtor comum para n cartelas
		Cartela::init();	// inicia o gerador srand()
		nome = "Um bingo";
		total_cartelas = n_cartelas;
		pCartelas = new (Cartela[total_cartelas]);
		string		prefixo = "cartela";
		string		nome = "";
		for (int i = 1; i <= total_cartelas; i++)
		{
			nome = prefixo;
			nome.append(to_string(i));
			pCartelas[i - 1].muda_nome(nome);
		}	// end for
	}

	~Bingo()
	{	// ao final libera a memoria
		cout << "Bingo: Destruindo " << total_cartelas << " cartelas" << endl;
		delete[] pCartelas;
	}	// end destructor

	void mostra()
	{
		cout <<
			"\nBingo: jogo '" <<
			nome <<
			"' com '" << total_cartelas << "' cartelas" << endl;
		for (int i = 1; i <= total_cartelas; i++)
		{
			cout << i << ": '" <<
				(pCartelas + i - 1)->nome <<
				"'" <<
				endl;
			//cout << i << ": '" << (pCartelas + i)->nome << "'" << endl;
		}	// end for
	}

	void mostra_detalhes()
	{
		cout <<
			"\nBingo: jogo '" <<
			nome <<
			"' com '" << total_cartelas << "' cartelas" << endl;
		for (int i = 1; i <= total_cartelas; i++)
		{
			(pCartelas + i - 1)->mostra();
		}	// end for
	}

	void muda_nome(string n) { nome = n; }

};	// end class Bingo
