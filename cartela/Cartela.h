#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class Cartela
{
public:
	int		tamanho;
	int		limite;
	int* valores;
	string	nome;

public:
	Cartela();
	Cartela(string n, int t, int l);
	~Cartela();

	int			existe(unsigned int valor);

	static int init()
	{
		srand((int)time(NULL));
		return 0;
	}	// end init()

	int			mostra();
	void		muda_nome(string n);
};	// end class Cartela
