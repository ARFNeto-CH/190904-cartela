#pragma once
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include "Cartela.h"

class Bingo
{
private:

	short		cor_dos_numeros[102];		// vai acompanhar as rodadas
	short		cor_nao_sorteados_ainda;	// cor inicial
	short		cor_sorteados;				// cor dos marcados
	int			maior_numero = 75;			// bingo 75
	string		nome;						// nome da mesa
	Cartela*	pCartelas;					// as cartelas
	short		sorteio[102];				// o sorteio pronto com todas as rodadas possiveis
	int			tamanho_cartelas = 25;		// cartela de 25
	int			tamanho_faixas = 15;		// em faixas de 15 por linha
	int			total_cartelas = 5;			// 5 cartelas por jogo
	short		total_cartelas_completas;	// pode ter mais de um vencedor, claro
	int			ultima_rodada;				// ultima rodada: usado para navegar no sorteio[]
	int			ultimo_numero;				// ultimo numero que 'saiu'

public:

	Bingo();
	Bingo(int n_cartelas);
	~Bingo();

	Cartela*	get_cartela(short n);	// traz o endereco da cartela n
	short*		get_cores(); 				// devolve o endereco do vetor de cores
	int			faz_o_jogo(short* valores);
	int			fim_da_rodadaXY(short X, short Y);
	short		get_vencedores();
	int			inicia(int t);
	void		mostra();
	void		mostra_detalhes();
	void		mostra_rodadasXY(short X, short Y);
	void		muda_nome(string n);
	int			nova_rodada();

};	// end class Bingo

