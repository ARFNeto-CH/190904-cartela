#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"
#include "Bingo.h"

using namespace std;

int umTeste()
{
	// esse era pra testar a funcao mostra()
	cout << "\nCriando uma classe Bingo...\n" << endl;
	Bingo	bingo(5);
	cout << "\nMostra resumo...\n" << endl;
	bingo.mostra();
	cout << "\nMostra as cartelas todas...\n" << endl;
	bingo.mostra_detalhes();
	cout << "\nMostra a terceira cartela...\n" << endl;
	(bingo.pCartelas + 2)->mostra();
	return 0;
}

int main(int argc, char** argv)
{
	Bingo	bingo(5);
	(bingo.pCartelas + 0)->mostraXY(27, 0);
	(bingo.pCartelas + 1)->mostraXY(53, 0);
	(bingo.pCartelas + 2)->mostraXY(0, 8);
	(bingo.pCartelas + 3)->mostraXY(27, 8);
	(bingo.pCartelas + 4)->mostraXY(53, 8);
	return 0;
}	// end main()
