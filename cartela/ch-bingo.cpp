
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"
#include "Bingo.h"

using namespace std;


int main(int argc, char** argv)
{
	cout << "\nCriando uma classe Bingo...\n" << endl;
	Bingo	bingo(3);
	cout << "\nMostra resumo...\n" << endl;
	bingo.mostra();
	cout << "\nMostra as cartelas todas...\n" << endl;
	bingo.mostra_detalhes();
	cout << "\nMostra a terceira cartela...\n" << endl;
	(bingo.pCartelas+2)->mostra();
	return 0;
}	// end main()
