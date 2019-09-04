
#include <iostream>
#include <stdlib.h>
#include < time.h>

using namespace std;

class Cartela
{
public:
	int		tamanho;
	int		limite;
	int*	valores;
	string	nome;

public:

	Cartela(string n, int t, int l)
	{
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
		for (int i=0; i<tamanho; i++) valores[i] = limite+1;
		srand(time(NULL));
		// aqui vamos preencher a cartela
		// um loop simples: a cada vez retorna um
		// numero aleatorio. Como na cartela do bingo
		// os valores ficam em ordem crescente
		for (int i = 0; i < tamanho;)
		{	// total de valores = tamanho
			v = rand() % limite + 1; // um valor entre 1 e o limite
			for (int n=0; n<tamanho; n++)
			{
				if (valores[n] > v)
				{	// achou o lugar: desloca todos pra abrir posicao
					for (int j=tamanho-1; j>=n; j--)
					{
						if(valores[j]<limite+1)
						{
							valores[j+1] = valores[j];
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


	~Cartela()
	{ 
		cout << 
			"Destruindo cartela '" << 
			nome <<
			"' com " << tamanho <<
			" valores entre 1 e " << limite
			<< endl;
		delete [] valores;
	};


	int mostra()
	{
		cout <<
			"\n    Cartela '" << nome <<
			"' com " << tamanho << 
			" valores. Limite: " <<	limite 
			<< endl;
		for (int i=0; i<tamanho; i++)
		{
			cout << valores[i] << "\t";
			if (i%5 == 4) cout << endl;
		}	// end for
		cout << endl;
		return 0;
	}	// end mostra()


	int existe(unsigned int valor)
	{
		for (int i=0; i<tamanho; i++)
		{
			if (valores[i] == valor)
				return valor;
		}	// end for
		return -1;
	}	// end existe()

};	// end class Cartela

int main(int argc, char** argv)
{
	Cartela c("Cartela A", 20, 100);
	c.mostra();

	Cartela d("Bingo", 10, 50);
	d.mostra();

	return 0;
}
