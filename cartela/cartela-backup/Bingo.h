#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"

class Bingo
{
public:
	string		nome;
	int			total_cartelas;
	Cartela* pCartelas;

	Bingo();
	Bingo(int n_cartelas);
	~Bingo();
	void mostra();
	void mostra_detalhes();
	void muda_nome(string n);
};	// end class Bingo

