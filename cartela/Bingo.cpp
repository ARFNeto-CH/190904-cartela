#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Cartela.h"
#include "Bingo.h"


Bingo::Bingo()
{	// construtor padrao assume cinco cartelas
	inicia(5);
}	// end constructor


Bingo::Bingo(int n_cartelas)
{	// construtor comum para n cartelas
	inicia(n_cartelas);
}	// end constructor


Bingo::~Bingo()
{	// ao final libera a memoria
	//cout << "Bingo: Destruindo " << total_cartelas << " cartelas" << endl;
	delete[] pCartelas;
}	// end destructor


Cartela*	Bingo::get_cartela(short n)
{
	// apenas devolve o endereco da cartela n
	return (pCartelas + n);	// so isso
};	// end acessa_cartela()


short*		Bingo::get_cores()
{ 
	return cor_dos_numeros;
}	// devolve o endereco do vetor de cores


int			Bingo::faz_o_jogo(short* valores)
{
	/*
	 fazendo o sorteio aqui e colocando os números no vetor sorteio[]
	 a partir da posicao 1 para a rodada 1 simplifica tudo

	 Como e o sorteio do bingo? Como o da loto:
	 - inicialmente tiramos uma bola
	   a partir do conjunto todo, que tem 'maior_numero' bolas
	   e trocamos pela primeira
	 - depois tiramos uma bola a partir do conjunto restante e
	   colocamos no lugar da segunda
	 - E prosseguimos ate escolhermos uma entre as duas ultimas
	   'bolas' e colocamos no lugar da penultima
	 */
	if (valores == NULL) return -1;
	int bola_da_vez = 0;
	int restantes = maior_numero - 1;
	int guarda_bola = 0;
	for (int i = 0; i <= maior_numero; i++) { valores[i] = i; }
	for (int inicial = 1; inicial < (maior_numero - 1); inicial++)
	{
		bola_da_vez = (rand() % restantes) + 1;
		guarda_bola = valores[inicial];
		valores[inicial] = valores[bola_da_vez];
		valores[bola_da_vez] = guarda_bola;
		restantes -= 1;
	}	// end for
	return 0;
}	// end faz_o_jogo()


int			Bingo::fim_da_rodadaXY(short X, short Y)
{
	if (total_cartelas_completas == 0) return -1;

	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD	 coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(H, coord);
	if (total_cartelas_completas == 1)
	{
		cout << "Depois de " << ultima_rodada << " rodadas, BINGO '" <<
			nome << "' encerrado com um unico vencedor";
	}
	else
	{
		cout << "Depois de " << ultima_rodada << " rodadas, BINGO '" <<
			nome << "' encerrado com " << total_cartelas_completas <<
			" vencedores";
	}	// end if
	coord.X = X;
	coord.Y += 2;
	SetConsoleCursorPosition(H, coord);
	cout << "Numeros que nao sairam:" << endl;
	for (int i = ultima_rodada + 1; i <= maior_numero; i++)
	{
		cout << setfill('0') << setw(2) << sorteio[i] << " ";
		if (i % 25 == 0) cout << endl;
	}	// end for
	cout << endl;
	mostra();
	return 0;

};	// end fim_da_rodada()


short		Bingo::get_vencedores()
{
	return	total_cartelas_completas;
};	// end get_vencedores()


int			Bingo::inicia(int t)
{	// prepara um bingo com 't' cartelas
	/*
	 - inicia o gerador de numeros
	 - nomeia e cria as cartelas preenchidas 'Cartela 1' ate 'Cartela n'
	 - acerta a cor para os sorteados e nao sorteados
	 - inicia contadores
	 */
	srand((int)time(NULL));
	nome = "Clube do Bingo";
	total_cartelas = t;
	// agora cria as cartelas todas
	pCartelas = new (Cartela[total_cartelas]);
	string		prefixo = "Cartela ";
	string		nome = "";
	// agora a cor: precisamos saber a cor que esta em uso
	// para definir nas cartelas a cor certa
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(H, &info);
	// define as cores
	cor_nao_sorteados_ainda = (WORD)info.wAttributes;
	cor_sorteados = FOREGROUND_GREEN;
	total_cartelas_completas = 0;

	for (int i = 1; i <= total_cartelas; i++)
	{
		nome = prefixo;
		nome.append(to_string(i));	// monta o nome
		pCartelas[i - 1].muda_nome(nome);
	}	// end for

	for (int i = 0; i <= maior_numero+1; i++) { cor_dos_numeros[i] = cor_nao_sorteados_ainda; }

	ultima_rodada = 0;
	ultimo_numero = 0;
	faz_o_jogo(sorteio);	// mais fácil preencher as rodadas uma vez só
	return 0;
}	// end inicio()


void		Bingo::mostra()
{
	cout <<
		"\nBingo: jogo '" <<
		nome <<
		"' com '" << total_cartelas << "' cartelas" << endl;
	for (int i = 1; i <= total_cartelas; i++)
	{
		cout << i << ": '" <<
			(pCartelas + i - 1)->nome <<
			"' marcados: " << (pCartelas+i-1)->get_hits() << 
			endl;
	}	// end for
}	// end mostra()


void		Bingo::mostra_detalhes()
{	// mostra todas as cartelas do bingo
	cout <<
		"\nBingo: jogo '" <<
		nome <<
		"' com '" << total_cartelas << "' cartelas" << endl;
	for (int i = 1; i <= total_cartelas; i++)
	{
		(pCartelas + i - 1)->mostra();
	}	// end for
}	// end mostra_detalhes()


void		Bingo::mostra_rodadasXY(short X, short Y)
{
	// mostra no rodape os numeros ja sorteados
	// legenda
	string linha1 =
		"Numeros      0              1              1              2              2";
	string linha2 =
		".............5..............0..............5..............0..............5";
	int		 i;
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD	 coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(H, coord);	// cursor na posicao
	SetConsoleTextAttribute(H, cor_nao_sorteados_ainda );
	cout << linha1;						// legenda linha 1

	coord.X = X;
	coord.Y++;
	SetConsoleCursorPosition(H, coord);
	cout << linha2;						// legenda linha 2
	coord.X = X;
	coord.Y++;

	SetConsoleCursorPosition(H, coord);	// numeros que ja sairam
	for (i = 1; i <= ultima_rodada; i++)
	{
		cout << setfill('0') << setw(2) << sorteio[i] << " ";
		if (i % 25 == 0)
		{
			coord.X = X;
			coord.Y++;
			SetConsoleCursorPosition(H, coord);
		}	// end if
	}	// end for
	coord.X = X;
	coord.Y++;
	SetConsoleCursorPosition(H, coord);
	return;

}	 // end mostra_rodadasXY()


void Bingo::muda_nome(string n) { nome = n; }


int Bingo::nova_rodada()
{
	// 'sorteia' novo numero, atualiza as cartelas
	// como o sorteio já foi feito no início basta
	// adiantar o indice
	// e avisa sobre eventual vitoria ou vitorias
	ultima_rodada += 1;
	ultimo_numero = sorteio[ultima_rodada];
	cor_dos_numeros[ultimo_numero] = cor_sorteados;
	// agora marca as cartelas que tem o novo numero
		// ve todas as cartelas
		// endereco da cartela: (pCartelas+i)
		// numero que saiu: ultimo_numero
		// valores da cartela em (pCartelas+1)->valores
		// os numeros na cartela estao em ordem ascendente
	for (int i = 0; i < total_cartelas; i++)
	{	// varre as cartelas a a partir de pCartelas
		for (int indice = 0; indice < tamanho_cartelas; indice++)
		{	// varre os numeros todos
			if ((pCartelas+i)->valores[indice] > ultimo_numero) break;
			if ((pCartelas+i)->valores[indice] < ultimo_numero) continue;
			(pCartelas + i)->set_numero();	// marca o numero
		}	// end for
		// marcado o novo numero, esa cartela pode ter vencido
		if ((pCartelas + i)->get_hits() >= tamanho_cartelas) total_cartelas_completas += 1;
	}	// end for

	return(0);

}	// end nova_rodada()
