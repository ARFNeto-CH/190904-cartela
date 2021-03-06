#pragma once
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class Cartela
{
private:
	short		numeros_sorteados;
	short		hits;

public:
	int		tamanho;
	int		limite;
	int*	valores;
	string	nome;

public:
	Cartela();
	Cartela(string n, int t, int l);
	~Cartela();

	short	get_hits();
	int		set_numero();
	int		mostra();
	int		mostraXY(short X, short Y, short* sorteio);
	void	muda_nome(string n);

};	// end class Cartela
