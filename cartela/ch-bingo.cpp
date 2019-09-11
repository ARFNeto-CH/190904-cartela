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
	(bingo.get_cartela(2))->mostra();
	return 0;
}


int mostra_o_jogo(Bingo* bingo)
{
	Cartela* p = bingo->get_cartela(0);
	short* cores = bingo->get_cores();

	      p->mostraXY(27, 0, cores);
	(p + 1)->mostraXY(53, 0, cores);
	(p + 2)->mostraXY( 0, 8, cores);
	(p + 3)->mostraXY(27, 8, cores);
	(p + 4)->mostraXY(53, 8, cores);

	bingo->mostra_rodadasXY(0, 15);
	return 0;

}

int cinXY(short X, short Y)
{
	char a;
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD	 coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(H, coord);
	cin >> a;
	return 0;
}

int main(int argc, char** argv)
{
	Bingo	bingo(5);
	do
	{
		bingo.nova_rodada();
		mostra_o_jogo(&bingo);
		Sleep(150);
	} while (bingo.get_vencedores() <= 0);
	mostra_o_jogo(&bingo);
	bingo.fim_da_rodadaXY(0, 21);

	return 0;
}	// end main()
