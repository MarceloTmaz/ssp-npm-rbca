#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <chrono>

#include <random> 


using namespace std;
using namespace std::chrono;

int maquinas, tarefas = 0, ferramentas = 0;
vector<int>magazine;
vector<int>tempoTroca;
vector<vector<int>>tempoProcessamento;
vector<vector<int>>matrizFerramentas;//matriz de ferramenta necessaria
vector<vector<int>>solucao;
vector<vector<int>>magazineMaquinas;

//variaveis complemeto
vector < vector<int>>trocasMagazine;
int menorTempoTotal = 0;
int valorMenor = 999999;
int maquinaCritica = -1;
int interacao = 0;
vector<int>tempoCompletude(maquinas, 0);
double melhoriaInserir = 0;
double melhoriaRelocate = 0;
double melhoriaSwap = 0;
double interacaoFinal = 0;
double melhoriaswaprealoca = 0;
double melhoriaMaiorArep = 0;
double melhoriaAleatoria = 0;
double pioraPertubacao = 0;
vector<int>tempoFinalmaquinas;
int melhorInteracao = -1;
double melhoria3opt = 0;
double nivelPertubacao = 0.02;
high_resolution_clock::time_point tempoinicial = high_resolution_clock::now();

vector<int>interacaoqueMelhora;
/*
2 10 10
5 7
2 4
2 7 2 5 10 8 10 8 8 9
8 10 2 1 2 7 5 3 10 8
0 0 1 0 1 0 0 1 0 1
1 1 0 0 1 0 1 1 0 0
0 0 1 1 0 1 1 1 1 0
1 0 0 1 0 0 0 0 1 1
0 1 1 0 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
0 1 1 0 1 1 0 1 0 0
1 0 0 1 0 0 0 0 0 0
0 0 1 1 0 1 1 0 0 1
0 1 0 0 0 1 0 0 1 0
*/

/*101

3 20 15
7 10 13
2 3 4
1 3 4 5 9 4 1 2 1 1 3 8 4 2 2 3 7 6 2 2
7 3 5 9 6 2 1 9 2 5 7 10 10 3 10 8 9 6 10 8
6 9 10 9 3 4 1 5 10 4 10 7 3 6 7 9 2 7 9 6
1 0 0 1 1 0 0 1 0 0 1 1 1 0 0 0 1 0 0 1
0 0 0 1 0 1 0 0 0 0 1 1 0 1 0 0 0 0 0 0
0 0 0 0 0 1 0 1 0 0 1 0 0 0 1 1 1 0 1 1
1 1 0 0 1 1 0 0 0 0 0 0 0 1 1 1 0 0 0 0
1 1 1 1 0 0 1 1 0 1 0 0 0 1 0 0 1 0 1 1
0 1 0 0 0 1 0 0 1 0 1 0 1 0 0 0 0 1 1 1
0 0 1 0 1 0 0 0 1 0 0 0 1 0 1 0 0 1 0 0
1 1 1 1 0 1 1 1 0 0 1 1 0 0 0 1 0 0 1 0
1 0 1 1 0 0 1 1 1 1 0 1 0 0 0 1 0 0 0 0
0 1 1 0 0 0 0 0 0 0 1 0 1 1 1 0 0 0 0 1
0 0 0 0 0 1 0 0 0 1 0 1 1 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0 0 0 1 1 0 1 0 1 0 0
1 0 0 0 1 0 1 0 1 1 0 0 0 0 1 0 0 1 0 0
0 0 0 0 1 1 0 0 1 1 0 1 0 0 0 0 1 1 1 0
0 1 1 1 0 0 0 0 0 1 0 0 0 1 0 0 0 1 1 0
*/

/* 82
3 15 15
7 10 13
2 3 4
9 3 3 10 3 9 6 6 2 1 6 1 2 4 9
6 5 10 3 9 9 5 2 2 8 6 8 1 4 2
2 9 10 5 6 6 3 6 5 10 3 8 6 1 5
1 1 0 0 0 0 0 1 0 0 0 1 0 1 0
1 0 0 0 0 1 1 1 0 1 0 1 0 0 1
0 0 1 0 1 1 0 0 1 1 0 1 1 0 1
1 1 0 0 1 0 0 1 1 0 0 1 0 0 1
0 1 0 1 0 1 1 0 0 0 1 1 0 1 0
1 1 0 1 0 0 0 0 0 0 0 0 0 0 0
0 1 1 0 1 0 1 0 0 1 1 0 0 1 0
0 1 0 0 0 0 1 1 1 0 0 0 1 0 0
0 0 1 0 0 1 1 1 0 1 1 0 1 0 0
1 0 0 1 1 1 0 1 0 0 0 0 1 0 1
1 0 0 0 1 0 1 1 1 0 1 1 0 1 1
0 0 1 1 1 1 0 0 1 1 1 0 1 1 1
0 0 1 0 0 0 0 0 0 0 1 0 0 1 0
0 0 1 1 0 0 0 0 1 1 0 0 0 1 0
1 0 0 1 1 1 0 0 0 0 1 0 0 0 0

*/
/* 85
3 15 15
7 10 13
2 3 4
9 2 4 6 6 5 8 6 9 3 3 3 10 3 9
4 4 2 3 3 3 2 8 5 3 9 3 4 8 4
5 2 6 2 1 2 2 6 4 4 10 1 2 8 10
0 1 1 1 0 0 0 1 0 0 1 1 0 0 1
1 0 0 0 1 0 0 1 0 0 1 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 0 1 0 1
0 1 0 0 0 0 0 0 0 1 0 0 0 1 0
1 0 1 0 0 0 1 0 1 1 0 1 1 0 0
0 1 0 0 1 1 0 0 0 0 0 0 1 1 1
1 0 1 1 0 1 0 1 0 0 0 1 0 1 0
0 0 0 1 0 0 0 0 0 0 0 1 1 1 0
0 0 0 0 0 0 0 0 1 0 0 1 0 0 1
0 0 0 0 0 1 0 0 1 1 1 0 0 0 0
1 0 1 0 1 1 1 0 0 0 1 0 0 0 0
1 0 0 0 0 0 0 1 0 1 1 0 0 1 0
0 0 1 1 1 0 1 0 1 0 1 0 1 0 1
1 1 0 1 1 1 1 1 0 1 0 0 0 1 1
0 1 0 0 1 0 1 0 1 0 1 1 0 1 0


*/
/*146
* 
* 
3 20 20
7 10 13
2 3 4
6 5 7 4 6 8 3 6 7 4 4 8 3 8 8 5 9 10 10 6
10 6 4 5 9 7 9 4 6 4 4 9 6 3 4 9 5 3 10 5
4 8 1 7 5 6 4 3 4 9 8 4 3 9 10 6 5 2 2 7
0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 1 1 0 0
1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 1 0 1 0 1 0 0 1 0 0 1 1 0 1 0
1 0 0 0 0 0 1 0 1 0 0 1 0 1 0 1 0 0 0 1
0 0 1 0 0 0 1 0 1 0 0 0 0 0 0 0 0 1 0 0
1 1 0 1 0 0 0 1 0 1 1 0 1 0 1 1 1 1 1 0
0 0 0 1 1 0 0 0 1 0 0 1 0 0 0 0 1 0 0 1
0 0 0 0 1 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 1 1 0 1 0 1 1 1 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1
0 1 1 1 0 0 1 1 0 0 1 0 0 0 1 0 0 0 1 0
0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0
0 0 1 1 1 1 0 0 1 0 0 0 1 0 1 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 1 0
0 0 1 0 1 1 0 1 0 0 1 0 1 0 1 1 0 0 0 0
0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 0 0 1 0 0
1 0 0 0 0 0 1 0 1 1 0 1 1 1 0 0 0 0 0 1
0 0 0 0 0 0 1 0 1 0 0 0 0 1 0 0 1 0 0 1
0 0 1 0 0 0 0 0 1 0 1 0 0 1 0 0 0 0 0 1
1 1 1 1 0 1 0 1 0 1 0 0 0 0 1 0 1 0 1 0

*/
/* 193
4 40 60
25 30 35 40
3 3 4 4
6 4 7 5 1 8 10 1 6 5 9 3 2 2 10 8 4 2 5 8 5 3 7 4 10 8 6 4 5 6 6 4 2 5 2 8 2 4 9 6
4 8 9 4 1 3 6 5 4 1 4 4 5 8 7 1 9 7 4 3 2 7 2 3 1 7 2 7 8 1 8 10 8 5 6 1 6 7 8 3
9 6 5 4 7 4 1 6 6 5 8 5 2 10 3 10 5 6 4 7 3 9 7 10 3 9 9 10 4 2 6 10 7 8 10 2 3 2 6 5
5 9 2 4 9 5 6 10 7 1 2 10 3 9 2 4 5 9 3 2 8 4 8 8 6 5 8 4 4 1 8 7 8 2 10 7 6 3 8 5
1 1 0 1 0 0 1 1 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 1 1 0 1 0 0 1 0 0 0 1 1 1 0 1 0 1
1 0 1 0 1 0 0 1 1 1 1 1 0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 0 1 1 1 0 1 0 0 1 0 0 0 0
1 0 1 0 0 0 0 0 1 0 1 0 0 1 0 1 1 0 0 1 1 0 0 1 0 1 1 0 1 0 1 1 0 1 0 1 0 0 0 1
0 0 1 0 0 1 1 0 1 1 1 0 1 1 0 0 0 1 1 1 0 1 0 1 0 0 1 0 0 0 0 0 0 1 0 1 1 0 1 0
0 1 0 0 1 1 1 1 0 1 0 0 1 1 1 0 0 1 0 1 1 0 1 1 0 1 1 0 1 1 0 0 0 1 1 0 0 0 1 0
1 0 1 1 0 0 0 1 1 1 1 0 0 0 1 0 0 1 0 0 1 1 1 1 1 0 1 0 1 0 1 1 0 1 0 0 1 0 1 1
0 0 0 0 1 0 1 1 0 1 1 1 1 1 0 1 0 0 1 1 1 0 0 1 1 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0
0 1 1 1 0 1 1 1 0 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 0 1 0 1 0 1 0 0 0 0 0 1 1 1 1
1 0 0 0 1 1 0 1 0 0 0 1 1 0 0 0 0 1 1 0 1 1 0 1 0 0 1 0 1 1 0 0 0 0 0 0 1 1 0 1
0 1 1 0 0 0 1 1 0 0 0 1 0 1 1 1 0 1 1 0 0 1 1 0 0 0 1 1 0 1 0 0 1 1 0 1 0 1 1 0
1 1 1 1 0 0 0 1 1 1 0 0 1 1 1 0 0 0 0 1 0 0 0 1 1 0 0 0 0 1 0 0 0 1 1 0 1 1 0 0
1 0 1 0 1 0 0 0 0 0 1 0 0 1 0 1 1 0 1 0 0 0 1 1 1 1 1 0 1 1 0 0 0 1 1 1 1 1 0 0
0 0 1 0 0 0 0 1 1 1 1 0 1 1 1 0 1 1 0 1 0 0 1 1 0 0 1 1 1 0 0 1 0 0 1 0 1 0 1 1
1 1 1 0 0 0 1 0 1 0 1 1 0 1 1 1 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 1 1 1 0 1 1 1 0
1 1 1 0 1 0 1 0 1 0 0 0 0 1 0 1 0 1 0 1 0 0 1 1 1 1 0 0 1 1 1 1 0 1 0 0 0 1 1 1
0 0 1 0 0 1 1 0 1 1 0 1 1 0 1 1 0 1 1 0 1 0 1 0 1 0 0 1 1 1 0 0 0 0 0 0 1 1 1 1
1 0 1 0 0 0 1 0 0 0 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 1 1 0 1 1 0 1 0 1 0 1 1 1 0 0
0 0 0 1 1 0 1 1 1 0 1 0 1 1 1 1 0 1 1 1 1 1 1 0 0 1 1 0 0 0 0 1 1 1 0 0 0 1 1 1
1 0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 1 1 1 0 0 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1 0 1 0 1
0 0 1 0 0 0 0 1 1 0 1 1 0 0 0 1 0 1 0 1 1 1 0 0 0 1 1 1 1 0 0 0 0 1 1 0 1 1 0 1
1 1 0 0 0 1 0 0 0 0 1 0 1 1 0 1 0 1 1 1 0 0 0 0 1 1 1 0 0 0 1 0 0 1 0 1 0 1 1 1
0 0 0 1 0 0 0 1 0 0 1 1 1 0 0 0 0 1 0 0 1 0 0 0 1 1 0 1 1 0 1 1 0 1 0 1 1 1 0 0
1 1 0 0 1 0 0 0 1 0 0 0 1 0 1 0 0 1 1 1 0 1 0 1 1 0 1 0 1 1 1 1 1 1 0 0 1 0 0 0
1 1 0 0 0 1 1 1 0 1 0 1 1 0 1 1 1 1 1 1 0 1 0 0 1 1 0 0 1 0 1 0 1 0 1 0 0 1 0 0
1 0 1 1 0 0 0 1 1 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 1 0 1 0 0 1 0 1 1 1 1 0 1 0 0 0
1 1 0 1 1 0 0 1 0 1 1 0 1 0 1 1 0 0 1 1 1 0 0 1 1 0 1 1 1 1 0 0 1 1 1 1 1 0 0 1
0 0 1 0 0 0 0 0 1 1 1 0 0 1 1 0 1 1 1 0 1 0 0 1 1 0 0 1 0 1 0 0 0 0 1 1 0 1 1 1
1 1 1 0 0 0 0 1 1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 1 1 0 1 1 1 0 1 0 0 1 1 1 0 0 0
1 1 1 1 1 0 1 0 1 1 0 1 1 0 0 0 1 1 1 1 0 1 0 1 0 0 1 1 0 1 0 0 0 0 1 1 1 1 1 0
1 1 1 0 1 0 1 0 1 1 0 1 1 1 0 0 0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 0 1 0 0 0 0 1 0 0
1 0 0 0 0 1 0 1 0 0 1 1 0 1 0 1 0 1 1 0 1 0 0 0 1 1 0 1 0 1 1 0 0 1 0 1 0 0 1 0
1 0 0 0 1 0 1 1 0 1 1 1 1 0 0 0 1 1 0 0 0 0 0 1 0 1 0 1 1 0 0 1 0 1 0 1 0 0 1 0
0 0 1 1 1 0 1 1 1 0 1 1 1 1 0 1 0 1 1 0 0 0 0 1 1 0 0 1 0 1 0 1 1 0 1 0 1 0 0 1
0 1 1 1 1 1 0 0 1 0 1 1 1 1 0 0 0 0 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 0 0 1 1 1 0
0 1 0 0 1 1 0 1 0 0 0 0 1 0 1 1 1 0 0 0 0 1 1 1 0 1 0 1 1 0 0 0 1 1 1 0 1 1 1 0
1 1 0 0 1 0 0 1 1 1 0 0 0 1 0 1 0 1 0 0 1 0 1 0 0 1 1 1 1 1 0 0 1 1 0 0 0 1 0 1
0 1 1 1 1 1 0 0 0 1 0 1 1 1 0 0 0 0 1 0 0 1 1 0 1 1 1 1 1 1 1 1 0 1 1 1 0 1 1 0
1 1 1 0 0 1 0 0 0 1 0 0 0 0 1 0 1 0 1 1 0 1 0 1 1 0 1 0 1 1 0 0 1 0 0 1 1 1 0 0
1 1 1 1 0 1 0 1 1 0 0 1 1 1 0 0 1 0 1 0 0 1 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0
0 1 1 0 1 0 1 1 1 1 1 0 0 0 0 1 1 0 0 1 1 1 0 0 0 1 1 0 0 1 1 1 1 1 1 1 0 0 0 1
1 1 1 0 0 0 0 1 0 0 0 1 1 1 1 1 0 1 0 0 0 1 0 0 1 0 0 0 1 0 1 0 0 1 1 0 1 1 0 0
1 1 1 1 1 0 1 1 0 0 1 0 1 1 0 0 1 1 0 1 1 1 0 0 1 0 1 1 1 1 1 1 0 0 1 1 0 1 0 0
1 0 1 1 0 0 1 1 1 1 1 0 0 1 0 1 1 0 1 0 0 0 1 1 0 0 0 0 1 1 0 0 1 1 0 1 0 0 1 0
1 0 0 1 0 0 0 0 0 0 1 0 1 1 1 0 0 1 1 0 1 0 0 1 0 0 1 0 1 0 0 1 0 0 0 0 0 0 1 1
1 0 0 1 1 1 1 1 0 0 1 0 0 1 0 1 1 1 0 1 1 1 0 1 1 0 0 0 0 1 0 1 1 1 0 0 1 1 0 1
0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 1 0 0 0 0 1 1 0 1 0 1 0 1 0 0 0 1 0 0 0 1 0 0
0 0 0 0 0 1 1 1 1 1 1 0 0 0 1 1 1 0 0 0 1 0 1 0 1 0 0 0 1 0 1 0 0 1 1 0 0 0 1 0
1 0 0 1 1 0 1 1 1 0 1 0 0 0 1 0 0 1 0 0 1 0 0 0 0 1 1 0 0 0 1 1 1 0 0 0 1 1 0 0
0 1 0 1 1 1 1 0 0 0 0 1 0 1 1 0 1 1 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 1 1 0 0 0
1 1 0 0 1 1 1 1 1 0 1 0 0 1 1 0 1 0 1 0 0 0 0 0 1 0 1 1 1 1 0 1 0 0 0 1 0 1 1 1
1 0 1 0 1 0 0 1 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 0 1 0 1 1 0 0 0 1 1
1 0 1 1 1 1 0 0 1 1 1 0 0 0 1 1 1 1 0 0 1 0 0 1 0 1 0 1 0 0 0 0 1 0 0 1 0 0 1 1
1 0 1 0 0 0 0 0 1 0 1 0 1 1 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 1 0 0 1 0 0 0 1 0 0
1 1 1 0 1 1 0 0 0 0 0 0 0 0 1 1 0 1 0 0 1 0 0 0 0 1 1 1 1 1 1 1 0 1 0 0 1 1 0 1
0 0 1 0 1 0 0 0 1 1 0 1 0 1 1 0 0 1 0 0 1 1 0 1 1 0 0 0 0 0 1 0 1 0 0 0 0 1 1 1
0 0 0 0 1 0 0 0 0 1 1 0 1 1 1 0 0 1 1 0 0 1 1 1 0 1 0 1 1 0 1 0 0 1 1 1 1 0 1 1
0 1 1 1 0 0 1 0 1 0 1 0 0 1 0 0 0 1 1 0 1 1 0 0 1 0 1 0 0 1 0 0 1 1 0 1 0 1 0 0
1 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 1 0 0 1 0 0 1 0 1 0 1 1 0 1 1 1 1 0 0 0 0
1 0 0 1 1 1 1 1 0 0 0 0 1 1 1 0 1 1 1 0 0 1 0 1 1 0 1 1 0 1 1 1 0 1 0 1 0 0 0 0
1 0 1 1 1 0 0 1 0 0 0 1 1 1 0 1 1 1 0 1 1 0 0 1 0 0 1 1 1 0 1 0 1 1 1 1 1 1 0 0


*/
int ktns(vector<int>processos, int maquinaAtual, vector<vector<int>>solucao) {


    if (processos.size() > 1) {
        vector < vector<int>>matrixFerramenas = matrizFerramentas;//matriz para o ktns
        vector<int> carregadas(ferramentas, 0);
        int trocaPorEstagio[200];
        int ferramentasMagazine = 0;
        vector<vector <int >> prioridade(ferramentas);
        for (int i = 0; i < ferramentas; i++)
        {
            vector<int>temp(processos.size(), 0);
            prioridade[i] = temp;
        }
        vector<vector <int >> magazineAtual(ferramentas);
        for (int i = 0; i < ferramentas; i++)
        {
            vector<int>temp(processos.size(), 0);
            magazineAtual[i] = temp;
        }

        trocaPorEstagio[0] = magazine[maquinaAtual];
        for (int i = 1; i < processos.size(); ++i) {
            trocaPorEstagio[i] = 0;
        }

        /*
        for (int i = 0; i < prioridade.size(); i++)
        {
            for (int j = 0; j < prioridade[i].size(); j++)
            {
                cout << prioridade[i][j] << " ";
            }
            cout << endl;
        }*/

        for (int j = 0; j < ferramentas; j++)
        {
            carregadas[j] = matrixFerramenas[j][processos[0]];
            if (matrixFerramenas[j][processos[0]] == 1)
                ferramentasMagazine++;
            for (int i = 0; i < processos.size(); i++)
            {
                magazineAtual[j][i] = matrixFerramenas[j][processos[i]];
            }

        }

        //preencher matriz de prioridade

        for (int i = 0; i < ferramentas; i++)
        {
            for (int j = 0; j < processos.size(); j++)
            {
                if (magazineAtual[i][j] == 1) {
                    prioridade[i][j] = 0;
                }
                else {
                    int proxima = 0;
                    bool usa = false;
                    for (int k = j + 1; k < processos.size(); k++)
                    {
                        ++proxima;
                        if (magazineAtual[i][k] == 1) {
                            usa = true;
                            break;
                        }
                    }
                    if (usa == true) {
                        prioridade[i][j] = proxima;
                    }
                    else {
                        prioridade[i][j] = -1;
                    }
                }
            }
        }
        /* matriz prioriedade
        for (int i = 0; i < ferramentas; i++)
        {
            for (int k = 0;  k < processos.size();  k++)
            {
                cout << prioridade[i][k] << " ";
            }
            cout << endl;
        }*/

        //calcular trocas
        int trocas = 0;
        for (int i = 1; i < processos.size(); ++i) {
            for (int j = 0; j < ferramentas; ++j) {
                if ((magazineAtual[j][i] == 1) && (carregadas[j] == 0)) {
                    carregadas[j] = 1;
                    ++ferramentasMagazine;
                }

                while (ferramentasMagazine > magazine[maquinaAtual]) {
                    int maior = -1;
                    int pMaior = -1;
                    for (int j = 0; j < ferramentas; j++)
                    {
                        if (magazineAtual[j][i] != 1)//ferramenta nã otutilizada pelo processo arual
                        {
                            //cout << "entrou";
                            if ((carregadas[j] == 1) && (prioridade[j][i] == -1)) {//Essa ferramenta não será mais utilizada e é um excelente candidato a remoção
                                pMaior = j;
                                break;
                            }
                            else {
                                // cout << "entro" << endl;
                                if ((prioridade[j][i] > maior) && carregadas[j] == 1) {
                                    maior = prioridade[j][i];
                                    //  cout << "desito\n";
                                    pMaior = j;
                                }
                            }
                        }
                    }
                    //if (pMaior != -1) {
                      //  cout << pMaior<<endl;

                //    trocasMagazine[maquinaAtual][i] += 1;
                    carregadas[pMaior] = 0;
                    ferramentasMagazine--;
                    //  cout << ferramentasMagazine << " " << magazine[maquinaAtual]<<endl;
                    trocaPorEstagio[i]++;
                    ++trocas;
                    //   }
                }
            }
        }

        return trocas;
    }
    return 0;
}

int ktnsTFT(vector<int>processos, int maquinaAtual) {

    vector < vector<int>>matrixFerramenas = matrizFerramentas;//matriz para o ktns
    vector<int> carregadas(ferramentas, 0);
    int trocaPorEstagio[200];
    int ferramentasMagazine = 0;
    vector<vector <int >> prioridade(ferramentas);
    for (int i = 0; i < ferramentas; i++)
    {
        vector<int>temp(processos.size(), 0);
        prioridade[i] = temp;
    }
    vector<vector <int >> magazineAtual(ferramentas);
    for (int i = 0; i < ferramentas; i++)
    {
        vector<int>temp(processos.size(), 0);
        magazineAtual[i] = temp;
    }

    trocaPorEstagio[0] = magazine[maquinaAtual];
    for (int i = 1; i < processos.size(); ++i) {
        trocaPorEstagio[i] = 0;
    }

    /*
    for (int i = 0; i < prioridade.size(); i++)
    {
        for (int j = 0; j < prioridade[i].size(); j++)
        {
            cout << prioridade[i][j] << " ";
        }
        cout << endl;
    }*/

    for (int j = 0; j < ferramentas; j++)
    {
        carregadas[j] = matrixFerramenas[j][processos[0]];
        if (matrixFerramenas[j][processos[0]] == 1)
            ferramentasMagazine++;
        for (int i = 0; i < processos.size(); i++)
        {
            magazineAtual[j][i] = matrixFerramenas[j][processos[i]];
        }

    }

    //preencher matriz de prioridade

    for (int i = 0; i < ferramentas; i++)
    {
        for (int j = 0; j < processos.size(); j++)
        {
            if (magazineAtual[i][j] == 1) {
                prioridade[i][j] = 0;
            }
            else {
                int proxima = 0;
                bool usa = false;
                for (int k = j + 1; k < processos.size(); k++)
                {
                    ++proxima;
                    if (magazineAtual[i][k] == 1) {
                        usa = true;
                        break;
                    }
                }
                if (usa == true) {
                    prioridade[i][j] = proxima;
                }
                else {
                    prioridade[i][j] = -1;
                }
            }
        }
    }
    //calcular trocas
    int trocas = 0;
    for (int i = 1; i < processos.size(); ++i) {
        for (int j = 0; j < ferramentas; ++j) {
            if ((magazineAtual[j][i] == 1) && (carregadas[j] == 0)) {
                carregadas[j] = 1;
                ++ferramentasMagazine;
            }

            while (ferramentasMagazine > magazine[maquinaAtual]) {
                int maior = 0;
                int pMaior = -1;
                for (int j = 0; j < ferramentas; j++)
                {
                    if (magazineAtual[j][i] != 1)//ferramenta nã otutilizada pelo processo arual
                    {
                        //cout << "entrou";
                        if ((carregadas[j] == 1) && (prioridade[j][i] == -1)) {//Essa ferramenta não será mais utilizada e é um excelente candidato a remoção
                            pMaior = j;
                            break;
                        }
                        else {
                            if ((prioridade[j][i] > maior) && carregadas[j] == 1) {
                                maior = prioridade[j][i];
                                pMaior = j;
                            }
                        }
                    }
                }
                //if (pMaior != -1) {
                  //  cout << pMaior<<endl;
                trocasMagazine[maquinaAtual][i] += 1;
                carregadas[pMaior] = 0;
                ferramentasMagazine--;
                //  cout << ferramentasMagazine << " " << magazine[maquinaAtual]<<endl;
                trocaPorEstagio[i]++;
                ++trocas;
                //   }
            }
        }
    }
    return trocas;
}

int makespan(vector<vector<int>>solucao)
{
    trocasMagazine = solucao;
    vector<int>tempocomple(maquinas, 0);
    tempoCompletude = tempocomple;
    valorMenor = 99999;
    vector<int>tempo;
    for (int i = 0; i < maquinas; i++)
    {
        int trocas = ktns(solucao[i], i, solucao);
        trocas *= tempoTroca[i];
        int soma = 0;
        for (int j = 0; j < solucao[i].size(); j++)
        {
            soma += tempoProcessamento[i][solucao[i][j]];
        }
        tempo.push_back((trocas + soma));
    }
    int cmax = -1;
    for (int i = 0; i < tempo.size(); i++)
    {
        tempoCompletude[i] = tempo[i];
        if (tempo[i] > cmax) {
            cmax = tempo[i];
            maquinaCritica = i;
        }
        if (tempo[i] < valorMenor) {
            valorMenor = tempo[i];
            menorTempoTotal = i;
        }

    }
    tempoFinalmaquinas = tempo;
    return cmax;
}

int flowTimeTotal(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    trocasMagazine = solucao;
    int tempo = 0;
    for (int i = 0; i < trocasMagazine.size(); i++)
    {
        for (int j = 0; j < trocasMagazine[i].size(); j++)
        {
            trocasMagazine[i][j] = 0;
        }
        ktnsTFT(solucao[i], i);
    }
    /*
    for (int i = 0; i < trocasMagazine.size(); i++)
    {
        for (int j = 0; j < trocasMagazine[i].size(); j++)
        {
            cout << trocasMagazine[i][j];
        }
        cout << endl;
    }*/

    for (int i = 0; i < solucao.size(); i++)
    {
        int tempoMaquina = 0;
        for (int j = 0; j < solucao[i].size(); j++)
        {
            if (trocasMagazine[i][j] != 0) {
                tempoMaquina += trocasMagazine[i][j] * tempoTroca[i];
                tempo += trocasMagazine[i][j] * tempoTroca[i];
            }
            tempo += tempoMaquina + tempoProcessamento[i][solucao[i][j]];
            tempoMaquina += tempoProcessamento[i][solucao[i][j]];
        }
    }
    return tempo;
}

void Hrandom() {
    srand(std::time(nullptr));
    for (int i = 0; i < maquinas; i++) {
        vector<int>temp;
        solucao.push_back(temp);
    }
    for (int i = 0; i < tarefas; i++) {
        int ferramentaTarefas = 0;
        for (int j = 0; j < ferramentas; j++) {
            if (matrizFerramentas[j][i] == 1) {
                ferramentaTarefas++;
            }
        }

        int te = (rand() % maquinas);
        //  cout << te << endl;

        for (int j = 0; j < magazine.size(); j++) {
            if (ferramentaTarefas <= magazine[te]) {
                solucao[te].push_back(i);
                break;
            }
            else if (ferramentaTarefas <= magazine[j]) {
                solucao[j].push_back(i);
                break;
            }
        }
    }
}

int completionTime(int i, vector<vector<int>>solucao) {
    //cout << "teste" << endl;
    int trocas = ktns(solucao[i], i, solucao);
    trocas *= tempoTroca[i];
    int soma = 0;
    for (int j = 0; j < solucao[i].size(); j++)
    {
        soma += tempoProcessamento[i][solucao[i][j]];
    }

    return soma;
}

vector<vector<int>> heuriticaSimilaridade() {
    vector<vector<int>>solucao;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    //decobrir inicial
    vector<int>jausando;
    for (int i = 0; i < maquinas; i++)
    {
        int maiorFer = -1;
        int menorTempo = -1;
        vector<int>temp;
        for (int j = 0; j < tarefas; j++)
        {
            if (magazine[i] >= ferramentaTarefas[j]) {
                if (maiorFer == -1 && menorTempo == -1) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
                else if (ferramentaTarefas[maiorFer] < ferramentaTarefas[j] && tempoProcessamento[i][menorTempo] < tempoProcessamento[i][j]) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
            }
        }
        if (menorTempo != -1) {
            temp.push_back(menorTempo);
            jausando.push_back(maiorFer);
            solucao.push_back(temp);
        }
        else {
            solucao.push_back(temp);
        }

    }
    /*for (int u = 0; u < maquinas; u++) {
            for (int j = 0; j < solucao[u].size(); j++) {
                cout << solucao[u][j] << " ";

            }
            cout << endl;
        }*/
        //descobrir demais tarefas
    while (jausando.size() != tarefas)
    {
        //  cout << "heristica";
        makespan(solucao);
        int menor = 99999;
        int index = -1;
        int qtsTarefas = 0;
        bool usouTarefa = false;
        for (int i = 0; i < tarefas; i++)
        {
            bool usado = false;
            if (magazine[menorTempoTotal] >= ferramentaTarefas[i]) {
                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);

                    int saida = ktns(temp[menorTempoTotal], menorTempoTotal, temp);
                    int ref = ktns(solucao[menorTempoTotal], menorTempoTotal, solucao);
                    if (saida == ref) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                        usouTarefa = true;
                    }
                }
            }
            else {
                //   cout << "entrei tarefa " << i;
                int maiorTempo = 99999;

                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    for (int k = 0; k < maquinas; k++)
                    {
                        if (tempoCompletude[k] < maiorTempo && magazine[k] >= ferramentaTarefas[i]) {
                            menorTempoTotal = k;
                            maiorTempo = tempoCompletude[k];
                            //  index = i;
                        }
                    }
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);

                    int saida = ktns(temp[menorTempoTotal], menorTempoTotal, temp);
                    int ref = ktns(solucao[menorTempoTotal], menorTempoTotal, solucao);
                    if (saida == ref) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                        usouTarefa = true;
                    }
                }
            }
        }
        if (usouTarefa == false) {
            for (int i = 0; i < tarefas; i++)
            {
                bool usado = false;
                if (magazine[menorTempoTotal] >= ferramentaTarefas[i]) {
                    for (int j = 0; j < jausando.size(); j++)
                    {
                        if (i == jausando[j]) {
                            usado = true;
                            break;
                        }

                    }

                    if (usado == false) {
                        vector<vector<int>>temp = solucao;
                        temp[menorTempoTotal].push_back(i);
                        int saida = completionTime(menorTempoTotal, temp);
                        if (saida < menor) {
                            menor = saida;
                            index = i;
                        }
                    }
                }
                else {
                    //   cout << "entrei tarefa " << i;
                    int maiorTempo = 99999;

                    for (int j = 0; j < jausando.size(); j++)
                    {
                        if (i == jausando[j]) {
                            usado = true;
                            break;
                        }

                    }

                    if (usado == false) {
                        for (int k = 0; k < maquinas; k++)
                        {
                            if (tempoCompletude[k] < maiorTempo && magazine[k] >= ferramentaTarefas[i]) {
                                menorTempoTotal = k;
                                maiorTempo = tempoCompletude[k];
                                //  index = i;
                            }
                        }
                        vector<vector<int>>temp = solucao;
                        temp[menorTempoTotal].push_back(i);
                        int saida = completionTime(menorTempoTotal, temp);
                        if (saida < menor) {
                            menor = saida;
                            index = i;
                        }
                    }
                }
            }
        }

        solucao[menorTempoTotal].push_back(index);
        jausando.push_back(index);
    }
    return solucao;
}


vector<vector<int>> heuritica() {
    vector<vector<int>>solucao;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    //decobrir inicial
    vector<int>jausando;
    for (int i = 0; i < maquinas; i++)
    {
        int maiorFer = -1;
        int menorTempo = -1;
        vector<int>temp;
        for (int j = 0; j < tarefas; j++)
        {
            if (magazine[i] >= ferramentaTarefas[j]) {
                if (maiorFer == -1 && menorTempo == -1) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
                else if (ferramentaTarefas[maiorFer] < ferramentaTarefas[j] && tempoProcessamento[i][menorTempo] < tempoProcessamento[i][j]) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
            }
        }
        if (menorTempo != -1) {
            temp.push_back(menorTempo);
            jausando.push_back(maiorFer);
            solucao.push_back(temp);
        }
        else {
            solucao.push_back(temp);
        }

    }
    /*for (int u = 0; u < maquinas; u++) {
            for (int j = 0; j < solucao[u].size(); j++) {
                cout << solucao[u][j] << " ";

            }
            cout << endl;
        }*/
        //descobrir demais tarefas
    while (jausando.size() != tarefas)
    {
        //  cout << "heristica";
        makespan(solucao);
        int menor = 99999;
        int index = -1;
        for (int i = 0; i < tarefas; i++)
        {
            bool usado = false;
            if (magazine[menorTempoTotal] >= ferramentaTarefas[i]) {
                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);
                    int saida = completionTime(menorTempoTotal, temp);
                    if (saida < menor) {
                        menor = saida;
                        index = i;
                    }
                }
            }
            else {
                //   cout << "entrei tarefa " << i;
                int maiorTempo = 99999;

                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    for (int k = 0; k < maquinas; k++)
                    {
                        if (tempoCompletude[k] < maiorTempo && magazine[k] >= ferramentaTarefas[i]) {
                            menorTempoTotal = k;
                            maiorTempo = tempoCompletude[k];
                            //  index = i;
                        }
                    }
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);
                    int saida = completionTime(menorTempoTotal, temp);
                    if (saida < menor) {
                        menor = saida;
                        index = i;
                    }
                }
            }
        }
        solucao[menorTempoTotal].push_back(index);
        jausando.push_back(index);
    }
    return solucao;
}

void heuristicaAleatoria() {
    vector<int>stmp;
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    for (int i = 0; i < tarefas; i++)
    {
        stmp.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(stmp.begin(), stmp.end(), std::default_random_engine(seed));
    vector<int>jausando;
    for (int i = 0; i < maquinas; i++)
    {
        for (int l = 0; l < tarefas; l++)
        {
            if (magazine[i] >= ferramentaTarefas[stmp[l]]) {
                bool usado = false;
                for (int k = 0; k < jausando.size(); k++)
                {
                    if (stmp[l] == jausando[k]) {
                        usado = true;
                        break;
                    }
                }
                if (usado == false) {
                    vector<int> temp;
                    temp.push_back(stmp[l]);
                    jausando.push_back(stmp[l]);
                    solucao.push_back(temp);
                    break;
                }
            }
        }
    }

    while (jausando.size() != tarefas)
    {
        //  cout << "heristica";
        makespan(solucao);
        int index = -1;
        for (int i = 0; i < stmp.size(); i++)
        {
            bool usado = false;
            if (magazine[menorTempoTotal] >= ferramentaTarefas[i]) {
                for (int j = 0; j < jausando.size(); j++)
                {
                    if (stmp[i] == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    index = stmp[i];
                }
            }
            else {
                //   cout << "entrei tarefa " << i;
                int maiorTempo = 999999;

                for (int j = 0; j < jausando.size(); j++)
                {
                    if (stmp[i] == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    for (int k = 0; k < maquinas; k++)
                    {
                        if ((tempoCompletude[k] < maiorTempo) && magazine[k] >= ferramentaTarefas[i]) {
                            menorTempoTotal = k;
                            maiorTempo = tempoCompletude[k];
                            //  index = i;
                            index = stmp[i];
                        }
                    }

                    ;

                }
            }
        }
        solucao[menorTempoTotal].push_back(index);
        jausando.push_back(index);
    }

}

vector<vector<int>> heuriticaSimilaridade2() {
    vector<vector<int>>solucao;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    //decobrir inicial
    vector<int>jausando;
    for (int i = 0; i < maquinas; i++)
    {
        int maiorFer = -1;
        int menorTempo = -1;
        vector<int>temp;
        for (int j = 0; j < tarefas; j++)
        {
            if (magazine[i] >= ferramentaTarefas[j]) {
                if (maiorFer == -1 && menorTempo == -1) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
                else if (ferramentaTarefas[maiorFer] < ferramentaTarefas[j] && tempoProcessamento[i][menorTempo] < tempoProcessamento[i][j]) {
                    bool usado = false;
                    for (int k = 0; k < jausando.size(); k++)
                    {
                        if (jausando[k] == j) {
                            usado = true;
                        }
                    }
                    if (usado == false) {
                        menorTempo = j;
                        maiorFer = j;
                    }
                }
            }
        }
        if (menorTempo != -1) {
            temp.push_back(menorTempo);
            jausando.push_back(maiorFer);
            solucao.push_back(temp);
        }
        else {
            solucao.push_back(temp);
        }

    }
    /*for (int u = 0; u < maquinas; u++) {
            for (int j = 0; j < solucao[u].size(); j++) {
                cout << solucao[u][j] << " ";

            }
            cout << endl;
        }*/
        //descobrir demais tarefas
    while (jausando.size() != tarefas)
    {
        //  cout << "heristica";
        makespan(solucao);
        int menor = 99999;
        int index = -1;
        int qtsTarefas = 0;
        for (int i = 0; i < tarefas; i++)
        {
            bool usado = false;
            if (magazine[menorTempoTotal] >= ferramentaTarefas[i]) {
                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);

                    int saida = ktns(temp[menorTempoTotal], menorTempoTotal, temp);
                    if (saida < menor) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                    }
                    else if (saida == menor && qtsTarefas < ferramentaTarefas[i]) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                    }
                }
            }
            else {
                //   cout << "entrei tarefa " << i;
                int maiorTempo = 99999;

                for (int j = 0; j < jausando.size(); j++)
                {
                    if (i == jausando[j]) {
                        usado = true;
                        break;
                    }

                }

                if (usado == false) {
                    for (int k = 0; k < maquinas; k++)
                    {
                        if (tempoCompletude[k] < maiorTempo && magazine[k] >= ferramentaTarefas[i]) {
                            menorTempoTotal = k;
                            maiorTempo = tempoCompletude[k];
                            //  index = i;
                        }
                    }
                    vector<vector<int>>temp = solucao;
                    temp[menorTempoTotal].push_back(i);

                    int saida = ktns(temp[menorTempoTotal], menorTempoTotal, temp);
                    if (saida < menor) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                    }
                    else if (saida == menor && qtsTarefas < ferramentaTarefas[i]) {
                        menor = saida;
                        index = i;
                        qtsTarefas = ferramentaTarefas[i];
                    }
                }
            }
        }
        solucao[menorTempoTotal].push_back(index);
        jausando.push_back(index);
    }
    return solucao;
}

void refinamento() {

    ktns(solucao[maquinaCritica], maquinaCritica, solucao);
    int inicio = 0;
    int fim = 0;
    int i = 0;
    for (i = 0; i < trocasMagazine[maquinaCritica].size(); i++)
    {
        if (trocasMagazine[maquinaCritica][i] > 0 && trocasMagazine[maquinaCritica][i] > trocasMagazine[maquinaCritica][inicio]) {
            inicio = i;
            for (i = i + 1; i < trocasMagazine[maquinaCritica].size(); i++)
            {
                if (trocasMagazine[maquinaCritica][i] != 0) {
                    fim = i;
                }
            }
        }
    }
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    int tamanho = fim - inicio;
    vector<vector<int>>verificar = solucao;
    for (int i = 0; i < tamanho; i++)
    {
        if (ferramentaTarefas[solucao[maquinaCritica][inicio + i]] <= magazine[menorTempoTotal]) {
            vector<int>temp = verificar[maquinaCritica];
            temp.erase(temp.begin() + (inicio + 1));
            verificar[menorTempoTotal].push_back(solucao[maquinaCritica][inicio + i]);
            verificar[maquinaCritica] = temp;
            //cout << "tentou" << endl;
        }
    }
    bool valido = true;
    vector<int>verificarTarefas(tarefas, 0);
    for (int j = 0; j < verificar.size(); j++)
    {
        for (int k = 0; k < verificar[j].size(); k++)
        {
            verificarTarefas[verificar[j][k]] += 1;
        }
    }
    /*
    for (int i = 0; i < verificarTarefas.size(); i++)
    {
        cout<<verificarTarefas[i];
    }
    cout<<"\n";
    */
    for (int i = 0; i < tarefas; i++)
    {
        if (verificarTarefas[i] != 1) {
            valido = false;
        }
    }
    int s1 = 0, s2 = 0;
    if (valido) {
        //cout<<"tentou2\n";
        s1 = makespan(solucao);
        s2 = makespan(verificar);
    }
    interacao++;
    if (s2 < s1) {
        solucao = verificar;
        interacao += 1;
        refinamento();
    }
}

vector<vector<int>> refinamentoInsertion(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;

    int makespanInicial = makespan(solucao);
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    bool para = false;
    while (para == false) {
        //cout << "entrou"<<endl;
        vector<int>tarefasTrocaa;
        int diferenca = 0;
        int index = -1;
        for (int i = 0; i < solucao[maquinaCritica].size(); i++)
        {
            if (magazine[menorTempoTotal] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                if (tempoProcessamento[menorTempoTotal][solucao[maquinaCritica][i]] < tempoProcessamento[maquinaCritica][solucao[maquinaCritica][i]]) {

                    tarefasTrocaa.push_back(solucao[maquinaCritica][i]);
                }
            }
        }
        //escolher quak tarefas vai ser trocada
        for (int i = 0; i < tarefasTrocaa.size(); i++)
        {
            if ((tempoProcessamento[maquinaCritica][tarefasTrocaa[i]] - tempoProcessamento[menorTempoTotal][tarefasTrocaa[i]]) > diferenca) {
                diferenca = (tempoProcessamento[menorTempoTotal][tarefasTrocaa[i]] - tempoProcessamento[maquinaCritica][tarefasTrocaa[i]]);
                index = tarefasTrocaa[i];
            }
        }
        // cout << index << endl;
        if (index == -1) {
            return solucao;
        }
        vector<vector<int>>final1 = solucao;
        vector < vector<int>>teste = solucao;
        for (int i = 0; i < teste[maquinaCritica].size(); i++)
        {
            if (index == teste[maquinaCritica][i]) {
                teste[maquinaCritica].erase(teste[maquinaCritica].begin() + i);
                break;
            }
        }
        vector < vector<int>>inserir = teste;
        int trocasref = 9999;
        for (int i = 0; i < teste[menorTempoTotal].size(); i++)
        {
            inserir = teste;
            inserir[menorTempoTotal].insert(inserir[menorTempoTotal].begin(), index);
            int  trocas = ktns(inserir[menorTempoTotal], menorTempoTotal, inserir);
            if (trocasref > trocas) {
                trocasref = trocas;
                final1 = inserir;
            }
        }
        int makespanFinal = makespan(final1);
        ;
        if (makespanInicial > makespanFinal) {

            bool valido = true;
            vector<int>verificarTarefas(tarefas, 0);
            for (int j = 0; j < final1.size(); j++)
            {
                for (int k = 0; k < final1[j].size(); k++)
                {
                    verificarTarefas[final1[j][k]] += 1;
                }
            }

            for (int i = 0; i < tarefas; i++)
            {
                if (verificarTarefas[i] != 1) {
                    valido = false;
                }
            }
            if (valido) {
                solucao = final1;
                interacao++;
            }
            else {
                para = true;
            }
        }
        else {
            para = true;
        }
    }
    return solucao;
}

vector<vector<int>>inserir(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<int>tarefasAvaliadas;
    vector<int>maquinaProcessar;
    vector<vector<int>>final1 = solucao;
    vector < vector<int>>inserir;
    bool para = false;
    int diferenca = -1;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }

    while (para == false)
    {
        int makespanSolucao = makespan(solucao);
        diferenca = -1;
        vector<int>copiar;
        tarefasAvaliadas = copiar;
        maquinaProcessar = copiar;
        for (int i = 0; i < solucao[maquinaCritica].size(); i++)
        {
            for (int k = 0; k < tempoProcessamento.size(); k++)
            {
                if (k != maquinaCritica) {
                    int tmp = tempoProcessamento[maquinaCritica][solucao[maquinaCritica][i]] - tempoProcessamento[k][solucao[maquinaCritica][i]];
                    if (tmp > diferenca) {
                        if (magazine[k] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                            diferenca = tmp;
                            vector<int>copiar;
                            tarefasAvaliadas = copiar;
                            tarefasAvaliadas.push_back(solucao[maquinaCritica][i]);
                            maquinaProcessar = copiar;
                            maquinaProcessar.push_back(k);
                        }
                    }
                    else if (tmp == diferenca) {
                        if (magazine[k] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                            tarefasAvaliadas.push_back(solucao[maquinaCritica][i]);
                            maquinaProcessar.push_back(k);
                        }
                    }
                }
            }

        }
        if (diferenca == -1) {
            for (int i = 0; i < solucao[maquinaCritica].size(); i++)
            {
                int verificarMaquinas = 0;
                for (int k = 0; k < tempoProcessamento.size(); k++)
                {
                    if (magazine[k] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                        if (tempoProcessamento[k][solucao[maquinaCritica][i]] > tempoProcessamento[maquinaCritica][solucao[maquinaCritica][i]]) {

                        }
                        else {
                            verificarMaquinas++;
                        }
                    }
                    else {
                        verificarMaquinas++;
                    }
                }
                if (verificarMaquinas == tempoProcessamento.size()) {
                    vector < vector<int>>teste = solucao;
                    if (magazine[menorTempoTotal] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {

                        inserir = teste;
                        int trocasref = 9999;
                        for (int i = 0; i < teste[maquinaProcessar[0]].size(); i++)
                        {
                            inserir = teste;


                            inserir[maquinaProcessar[0]].insert(inserir[maquinaProcessar[0]].begin(), tarefasAvaliadas[0]);
                            int  trocas = ktns(inserir[menorTempoTotal], menorTempoTotal, inserir);
                            if (trocasref > trocas) {
                                trocasref = trocas;
                                final1 = inserir;
                            }
                        }
                        for (int i = 0; i < teste[maquinaCritica].size(); i++)
                        {
                            if (teste[maquinaCritica][i] == tarefasAvaliadas[0]) {
                                final1[maquinaCritica].erase(final1[maquinaCritica].begin() + i);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
        else {
            if (tarefasAvaliadas.size() > 1) {
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

                shuffle(tarefasAvaliadas.begin(), tarefasAvaliadas.end(), std::default_random_engine(seed));

                int ref = tarefasAvaliadas[0];
                /*
                cout << endl;
                for (int o = 0; o < solucao[maquinaCritica].size(); o++)
                {
                    cout << solucao[maquinaCritica][o];
                }
                cout << endl;*/
                int maquinaRecebe = -1;
                for (int k = 0; k < tempoProcessamento.size(); k++)
                {
                    if (k != maquinaCritica) {

                        int tmp = tempoProcessamento[maquinaCritica][ref] - tempoProcessamento[k][ref];
                        if (tmp == diferenca) {
                            maquinaRecebe = k;
                            break;
                        }
                    }
                }
                vector < vector<int>>teste = solucao;

                inserir = teste;
                int trocasref = 9999;
                for (int i = 0; i < teste[maquinaRecebe].size(); i++)
                {
                    inserir = teste;
                    inserir[maquinaRecebe].insert(inserir[maquinaRecebe].begin(), tarefasAvaliadas[0]);
                    int  trocas = ktns(inserir[menorTempoTotal], menorTempoTotal, inserir);
                    if (trocasref > trocas) {
                        trocasref = trocas;
                        final1 = inserir;
                    }
                }
                for (int i = 0; i < teste[maquinaCritica].size(); i++)
                {
                    if (teste[maquinaCritica][i] == tarefasAvaliadas[0]) {
                        final1[maquinaCritica].erase(final1[maquinaCritica].begin() + i);
                        break;
                    }
                }
            }
            else {
                vector < vector<int>>teste = solucao;

                inserir = teste;
                int trocasref = 9999;
                for (int i = 0; i < teste[maquinaProcessar[0]].size(); i++)
                {
                    inserir = teste;
                    inserir[maquinaProcessar[0]].insert(inserir[maquinaProcessar[0]].begin(), tarefasAvaliadas[0]);
                    int  trocas = ktns(inserir[menorTempoTotal], menorTempoTotal, inserir);
                    if (trocasref > trocas) {
                        trocasref = trocas;
                        final1 = inserir;
                    }
                }
                for (int i = 0; i < teste[maquinaCritica].size(); i++)
                {
                    if (teste[maquinaCritica][i] == tarefasAvaliadas[0]) {
                        final1[maquinaCritica].erase(final1[maquinaCritica].begin() + i);
                        break;
                    }
                }
            }
        }

        int markspamteste = makespan(final1);

        if (makespanSolucao > markspamteste) {
            bool valido = true;
            vector<int>verificarTarefas(tarefas, 0);
            for (int j = 0; j < inserir.size(); j++)
            {
                for (int k = 0; k < inserir[j].size(); k++)
                {
                    verificarTarefas[inserir[j][k]] += 1;
                }
            }

            for (int i = 0; i < tarefas; i++)
            {
                if (verificarTarefas[i] != 1) {
                    valido = false;
                }
            }
            if (valido) {
                solucao = inserir;
                // interacao++;
            }
            else {
                para = true;
            }
        }
        else {
            para = true;
        }
    }

    int makespanInicio = makespan(entrada);
    int makespanFim = makespan(solucao);
    int diferenca2 = makespanInicio - makespanFim;
    if (diferenca2 > 0) {
        melhoriaInserir += diferenca2;
    }
    return solucao;
}

vector<vector<int>>insertion(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<int>tarefasAvaliadas;
    vector<int>diferenca;
    vector<int>maquinaProcessar;
    vector<vector<int>>final1 = solucao;
    vector < vector<int>>inserir;
    bool para = false;
    // int diferenca = -1;
     //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }

    int makespanFinal = 0;
    int makespanInicial = 0;

    int makespanSolucao = makespan(solucao);
    //  diferenca = -1;
    vector<int>copiar;
    tarefasAvaliadas = copiar;
    maquinaProcessar = copiar;
    diferenca = copiar;
    for (int i = 0; i < solucao[maquinaCritica].size(); i++)
    {
        int tmp = -9999;
        int maquinadestino = -1;
        for (int k = 0; k < tempoProcessamento.size(); k++)
        {

            if (k != maquinaCritica) {
                int tmp2 = tempoProcessamento[maquinaCritica][solucao[maquinaCritica][i]] - tempoProcessamento[k][solucao[maquinaCritica][i]];

                if (magazine[k] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                    if (tmp2 > tmp) {
                        tmp = tmp2;
                        maquinadestino = k;
                    }
                }
            }
        }
        //achar posição de inserção
        for (int l = 0; l < tarefasAvaliadas.size(); l++)
        {
            if (tmp > tarefasAvaliadas[l]) {
                if (maquinadestino > -1) {
                    diferenca.insert(diferenca.begin() + l, tmp);
                    //  cout << tarefasAvaliadas.size() << "tarefas" << maquinaProcessar.size();
                    maquinaProcessar.insert(maquinaProcessar.begin() + l, maquinadestino);
                    tarefasAvaliadas.insert(tarefasAvaliadas.begin(), i);
                    break;
                }
            }
        }
        if (tarefasAvaliadas.size() == 0) {
            if (maquinadestino > -1) {
                diferenca.insert(diferenca.begin(), tmp);
                maquinaProcessar.insert(maquinaProcessar.begin(), maquinadestino);
                tarefasAvaliadas.insert(tarefasAvaliadas.begin(), i);
            }
        }
        //cout << i;
    }
    bool melhorou = false;
    //fazer a inserção
    for (int i = 0; i < tarefasAvaliadas.size(); i++)
    {

        if (melhorou == true) {
            break;
        }
        inserir = solucao;
        if (diferenca[i] <= -1) {

            if (magazine[menorTempoTotal] >= ferramentaTarefas[tarefasAvaliadas[i]]) {


                inserir[menorTempoTotal].push_back(tarefasAvaliadas[i]);
                for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                {
                    if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                        inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                        break;
                    }
                }
                cout << "morri" << endl;
                makespanFinal = makespan(inserir);
                makespanInicial = makespan(solucao);
                cout << "nao" << endl;
                if (makespanInicial > makespanFinal) {

                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < inserir.size(); j++)
                    {
                        for (int k = 0; k < inserir[j].size(); k++)
                        {
                            verificarTarefas[inserir[j][k]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido) {
                        solucao = inserir;
                        melhorou = true;
                        //interacao++;
                    }
                }
            }/*
            else {
                inserir[maquinaProcessar[i]].push_back(tarefasAvaliadas[i]);
                for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                {
                    if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                        inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                        break;
                    }
                }
                cout << "aqui23" << endl;
                makespanFinal = makespan(inserir);
                makespanInicial = makespan(solucao);
                if (makespanInicial > makespanFinal) {

                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < inserir.size(); j++)
                    {
                        for (int k = 0; k < inserir[j].size(); k++)
                        {
                            verificarTarefas[inserir[j][k]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido) {
                        solucao = inserir;
                        melhorou = true;
                        //interacao++;
                    }
                }
            }*/
        }
        else {
            //    cout << "esyo oreo\n";
             //   cout << maquinaProcessar[i];
             //   cout << tarefasAvaliadas[i];
            //    cout << inserir[maquinaProcessar[0]].size();
            if (magazine[maquinaProcessar[i]] >= ferramentaTarefas[tarefasAvaliadas[i]])
            {
                inserir[maquinaProcessar[i]].push_back(tarefasAvaliadas[i]);
                for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                {
                    if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                        inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                        break;
                    }
                }/*
                for (int p = 0; p < solucao.size(); p++)
                {
                    for (int u = 0; u < solucao[p].size(); u++)
                    {
                        cout << solucao[p][u];
                    }
                    cout << endl;
                }*/
                cout << "morru" << endl;
                makespanFinal = makespan(inserir);
                makespanInicial = makespan(solucao);
                cout << "nop" << endl;
                if (makespanInicial > makespanFinal) {

                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < inserir.size(); j++)
                    {
                        for (int k = 0; k < inserir[j].size(); k++)
                        {
                            verificarTarefas[inserir[j][k]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido) {
                        solucao = inserir;
                        melhorou = true;
                        //interacao++;
                    }
                }
            }
        }
    }

    //cout << "aqui" << endl;
    int makesparef = makespan(entrada);
    int final3 = makespan(solucao);
    // cout << "porra" << endl;
    int diferenca2 = makesparef - final3;
    if (diferenca2 > 0) {
        melhoriaInserir += diferenca2;
    }
    return solucao;
}

//em uso essa
vector<vector<int>>insertion2(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<int>tarefasAvaliadas;
    vector<int>diferenca;
    vector<int>maquinaProcessar;
    vector<vector<int>>final1 = solucao;
    vector < vector<int>>inserir;
    bool para = false;

    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }

    int makespanFinal = 0;
    int makespanInicial = 0;
    bool melhorou = true;
    while (para == false) {
        if (melhorou == true) {
            int makespanSolucao = makespan(solucao);
            //  diferenca = -1;
            for (int i = 0; i < solucao[maquinaCritica].size(); i++)
            {
                int tmp = -9999;
                int maquinadestino = -1;
                for (int k = 0; k < tempoProcessamento.size(); k++)
                {

                    if (k != maquinaCritica) {
                        if (magazine[k] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                            int diferenca = tempoProcessamento[maquinaCritica][solucao[maquinaCritica][i]] - tempoProcessamento[k][solucao[maquinaCritica][i]];
                            if (diferenca > tmp) {
                                tmp = diferenca;
                                maquinadestino = k;
                            }
                        }

                    }
                }
                //achar posição de inserção
                for (int l = 0; l < tarefasAvaliadas.size(); l++)
                {
                    if (tmp > diferenca[l]) {
                        if (maquinadestino > -1) {
                            diferenca.insert(diferenca.begin() + l, tmp);
                            //  cout << tarefasAvaliadas.size() << "tarefas" << maquinaProcessar.size();
                            maquinaProcessar.insert(maquinaProcessar.begin() + l, maquinadestino);
                            tarefasAvaliadas.insert(tarefasAvaliadas.begin() + l, i);
                            break;
                        }
                    }
                }
                if (tarefasAvaliadas.size() == 0) {
                    if (maquinadestino > -1) {
                        diferenca.insert(diferenca.begin(), tmp);
                        maquinaProcessar.insert(maquinaProcessar.begin(), maquinadestino);
                        tarefasAvaliadas.insert(tarefasAvaliadas.begin(), i);
                    }
                }
            }
            melhorou = false;
        }

        //fazer a inserção

        for (int i = 0; i < tarefasAvaliadas.size(); i++)
        {

            if (melhorou == true) {
                break;
            }
            inserir = solucao;
            if (diferenca[i] <= 0) {

                if (magazine[menorTempoTotal] >= ferramentaTarefas[tarefasAvaliadas[i]]) {
                    inserir[menorTempoTotal].push_back(tarefasAvaliadas[i]);
                    for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                    {
                        if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                            inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                            break;
                        }
                    }
                    //   cout << "a1" << endl;
                    makespanFinal = makespan(inserir);
                    makespanInicial = makespan(solucao);
                    //  cout << "nota1" << endl;
                    if (makespanInicial > makespanFinal) {

                        bool valido = true;
                        vector<int>verificarTarefas(tarefas, 0);
                        for (int j = 0; j < inserir.size(); j++)
                        {
                            for (int k = 0; k < inserir[j].size(); k++)
                            {
                                verificarTarefas[inserir[j][k]] += 1;
                            }
                        }

                        for (int i = 0; i < tarefas; i++)
                        {
                            if (verificarTarefas[i] != 1) {
                                valido = false;
                            }
                        }
                        if (valido) {
                            solucao = inserir;
                            melhorou = true;
                            //interacao++;
                        }
                    }
                }
                else {
                    int tempoAtual = 99999;
                    int receber = -1;
                    for (int h = 0; h < solucao.size(); h++)
                    {
                        if (h != maquinaCritica) {
                            if (magazine[h] >= ferramentaTarefas[tarefasAvaliadas[i]]) {
                                if (tempoFinalmaquinas[h] < tempoAtual) {
                                    tempoAtual = tempoFinalmaquinas[h];
                                    receber = h;
                                }
                            }
                        }
                    }

                    if (receber > -1) {
                        inserir[receber].push_back(tarefasAvaliadas[i]);
                        for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                        {
                            if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                                inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                                break;
                            }
                        }
                        //   cout << "a1" << endl;
                        makespanFinal = makespan(inserir);
                        makespanInicial = makespan(solucao);
                        //  cout << "nota1" << endl;
                        if (makespanInicial > makespanFinal) {

                            bool valido = true;
                            vector<int>verificarTarefas(tarefas, 0);
                            for (int j = 0; j < inserir.size(); j++)
                            {
                                for (int k = 0; k < inserir[j].size(); k++)
                                {
                                    verificarTarefas[inserir[j][k]] += 1;
                                }
                            }

                            for (int i = 0; i < tarefas; i++)
                            {
                                if (verificarTarefas[i] != 1) {
                                    valido = false;
                                }
                            }
                            if (valido) {
                                solucao = inserir;
                                melhorou = true;
                                //interacao++;
                            }
                        }
                    }
                }
            }
            else {
                if (magazine[maquinaProcessar[i]] >= ferramentaTarefas[tarefasAvaliadas[i]])
                {
                    inserir[maquinaProcessar[i]].push_back(tarefasAvaliadas[i]);
                    for (int j = 0; j < inserir[maquinaCritica].size(); j++)
                    {
                        if (inserir[maquinaCritica][j] == tarefasAvaliadas[i]) {
                            inserir[maquinaCritica].erase(inserir[maquinaCritica].begin() + j);
                            break;
                        }
                    }/*
                    for (int p = 0; p < solucao.size(); p++)
                    {
                        for (int u = 0; u < solucao[p].size(); u++)
                        {
                            cout << solucao[p][u];
                        }
                        cout << endl;
                    }*/
                    //    cout << "a3" << endl;
                    makespanFinal = makespan(inserir);
                    makespanInicial = makespan(solucao);
                    //    cout <<  "nota3" << endl;
                    if (makespanInicial > makespanFinal) {

                        bool valido = true;
                        vector<int>verificarTarefas(tarefas, 0);
                        for (int j = 0; j < inserir.size(); j++)
                        {
                            for (int k = 0; k < inserir[j].size(); k++)
                            {
                                verificarTarefas[inserir[j][k]] += 1;
                            }
                        }

                        for (int i = 0; i < tarefas; i++)
                        {
                            if (verificarTarefas[i] != 1) {
                                valido = false;
                            }
                        }
                        if (valido) {
                            solucao = inserir;
                            melhorou = true;
                            //interacao++;
                        }
                    }
                }
            }
        }
        if (melhorou == false) {
            para = true;
            break;
        }
    }
    // cout << "final" << endl;
    int makesparef = makespan(entrada);
    int final3 = makespan(solucao);
    //  cout << "tambem nao" << endl;
    int diferenca2 = makesparef - final3;
    if (diferenca2 > 0) {
        melhoriaInserir += diferenca2;
    }
    return solucao;

}
vector < vector<int>>swapdireita(vector<vector<int>>entrada) {
    vector<vector<int>> solucao = entrada;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    bool para = false;
    while (para == false) {
        int makespaninicial = makespan(solucao);
        bool melhorou = false;
        for (int i = solucao[maquinaCritica].size() - 1; i >= 0; i--)
        {

            for (int l = solucao[menorTempoTotal].size() - 1; l >= 0; l--)
            {

                vector<vector<int>>troca = solucao;
                if (magazine[menorTempoTotal] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                    if (magazine[maquinaCritica] >= ferramentaTarefas[solucao[menorTempoTotal][l]]) {

                        if (l >= troca[menorTempoTotal].size()) {
                            troca[menorTempoTotal].pop_back();
                        }
                        else
                        {
                            troca[menorTempoTotal].erase(troca[menorTempoTotal].begin() + l);
                        }

                        for (int u = 0; u < troca[maquinaCritica].size(); u++)
                        {
                            cout << troca[maquinaCritica][u];
                        }
                        cout << endl;
                        if (i >= troca[maquinaCritica].size()) {
                            troca[maquinaCritica].pop_back();
                        }
                        else
                        {
                            troca[maquinaCritica].erase(troca[maquinaCritica].begin() + i);
                        }

                        if (troca[maquinaCritica].size() - 1 < i) {
                            troca[maquinaCritica].push_back(solucao[menorTempoTotal][l]);
                        }
                        else {
                            troca[maquinaCritica].insert(troca[maquinaCritica].begin() + i, solucao[menorTempoTotal][l]);
                        }

                        if (troca[menorTempoTotal].size() - 1 < l) {
                            troca[menorTempoTotal].push_back(solucao[maquinaCritica][i]);
                        }
                        else {
                            troca[menorTempoTotal].insert(troca[menorTempoTotal].begin() + l, solucao[maquinaCritica][i]);
                        }
                        int makespanFinal = makespan(troca);
                        if (makespaninicial > makespanFinal) {
                            bool valido = true;
                            vector<int>verificarTarefas(tarefas, 0);
                            for (int j = 0; j < troca.size(); j++)
                            {
                                for (int k = 0; k < troca[j].size(); k++)
                                {
                                    verificarTarefas[troca[j][k]] += 1;
                                }
                            }

                            for (int i = 0; i < tarefas; i++)
                            {
                                if (verificarTarefas[i] != 1) {
                                    valido = false;
                                }
                            }
                            if (valido) {
                                solucao = troca;
                                melhorou = true;
                            }
                        }
                    }
                }
                else {
                    break;
                }
                if (melhorou == true) {
                    break;
                }
            }
            if (melhorou == true) {
                break;
            }
        }
        if (melhorou == false) {
            para = true;
        }
    }
    int makepanINico = makespan(entrada);
    int makespanFim = makespan(solucao);
    int dife = makepanINico - makespanFim;
    if (dife > 0) {
        melhoriaSwap += dife;
    }
    return solucao;
}
//usa essse
vector < vector<int>>swapesrqueda(vector<vector<int>>entrada) {
    vector<vector<int>> solucao = entrada;
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    bool para = false;  
    while (para == false) {
        int makespaninicial = makespan(solucao);
        bool melhorou = false;
    
        for (int i = 0; i < solucao[maquinaCritica].size(); i++)
        {

            for (int l = 0; l < solucao[menorTempoTotal].size(); l++)
            {

                vector<vector<int>>troca = solucao;
                if (i < solucao[maquinaCritica].size()) {
                    if (magazine[menorTempoTotal] >= ferramentaTarefas[solucao[maquinaCritica][i]]) {
                        if (l < solucao[menorTempoTotal].size()) {
                            if (magazine[maquinaCritica] >= ferramentaTarefas[solucao[menorTempoTotal][l]]) {
                                /*
                                for (int u = 0; u < troca[menorTempoTotal].size(); u++)
                                {
                                    cout << troca[menorTempoTotal][u];
                                }
                                cout << endl;*/
                                if (l >= troca[menorTempoTotal].size()) {
                                    troca[menorTempoTotal].pop_back();
                                }
                                else
                                {
                                    troca[menorTempoTotal].erase(troca[menorTempoTotal].begin() + l);
                                }
                                if (i >= troca[maquinaCritica].size()) {
                                    troca[maquinaCritica].pop_back();
                                }
                                else
                                {
                                    troca[maquinaCritica].erase(troca[maquinaCritica].begin() + i);
                                }
                                /*

                                cout << endl;
                                cout << i << endl;
                                cout << troca[maquinaCritica][i];*/
                                if (i > troca[maquinaCritica].size() - 1) {
                                    troca[maquinaCritica].push_back(solucao[menorTempoTotal][l]);
                                }
                                else
                                {
                                    troca[maquinaCritica].insert(troca[maquinaCritica].begin() + i, solucao[menorTempoTotal][l]);
                                }
                                if (troca[menorTempoTotal].size() - 1 < l) {
                                    troca[menorTempoTotal].push_back(solucao[maquinaCritica][i]);
                                }
                                else
                                {
                                    troca[menorTempoTotal].insert(troca[menorTempoTotal].begin() + l, solucao[maquinaCritica][i]);
                                }
                                int makespanFinal = makespan(troca);
                                // cout <<"\n"+ makespanFinal << endl;
                                if (makespaninicial > makespanFinal) {
                                    bool valido = true;
                                    vector<int>verificarTarefas(tarefas, 0);
                                    for (int j = 0; j < troca.size(); j++)
                                    {
                                        for (int k = 0; k < troca[j].size(); k++)
                                        {
                                            verificarTarefas[troca[j][k]] += 1;
                                        }
                                    }

                                    for (int i = 0; i < tarefas; i++)
                                    {
                                        if (verificarTarefas[i] != 1) {
                                            valido = false;
                                        }
                                    }
                                    if (valido) {
                                        solucao = troca;
                                        melhorou = true;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        break;
                    }
                }
                if (melhorou == true) {
                    break;
                }
            }
            if (melhorou == true) {
                break;
            }
        }
        if (melhorou == false) {
            para == true;
            break;
        }
    }



    int makepanINico = makespan(entrada);
    int makespanFim = makespan(solucao);
    int dife = makepanINico - makespanFim;
    if (dife > 0) {
        melhoriaSwap += dife;
    }
    return solucao;
}

vector<vector<int>>swaprealocar(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<vector<int>>mover = entrada;

    bool para = false;

    while (para == false) {
        bool melhorou = false;
        for (int i = 0; i < solucao[maquinaCritica].size(); i++)
        {
            mover = solucao;

            int inicio = makespan(solucao);
            int ref = solucao[maquinaCritica].size();
            for (int l = i + 1; l < solucao[maquinaCritica].size(); l++)
            {
                if (l >= ref) {
                    break;
                }
                //cout << i<<" " << l << endl;
                inicio = makespan(solucao);
                // cout <<ref<<"l"<<l << endl;
               //  cout << solucao[maquinaCritica][l] << endl;
                mover[maquinaCritica].insert(mover[maquinaCritica].begin() + i, solucao[maquinaCritica][l]);
                mover[maquinaCritica].erase(mover[maquinaCritica].begin() + i + 1);
                mover[maquinaCritica].insert(mover[maquinaCritica].begin() + l, solucao[maquinaCritica][i]);
                mover[maquinaCritica].erase(mover[maquinaCritica].begin() + l + 1);

                int fim = makespan(mover);
                if (inicio > fim) {
                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < mover.size(); j++)
                    {
                        for (int k = 0; k < mover[j].size(); k++)
                        {
                            verificarTarefas[mover[j][k]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido == true) {
                        melhorou = true;
                        solucao = mover;
                        int diferenca = inicio - fim;
                        melhoriaswaprealoca += diferenca;
                        break;
                    }
                }
            }
            if (melhorou==true) {
                break;
            }
        }
        if (melhorou == false) {
            para = true;
            break;
        }
    }
    return solucao;
}

vector<vector<int>>rellocate(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    bool para = false;
    vector<vector<int>>final1 = solucao;


    //cout << para;
    int makespanInicial = makespan(solucao);
    vector<int>maquinaCriticaVetor = solucao[maquinaCritica];
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(maquinaCriticaVetor.begin(), maquinaCriticaVetor.end(), std::default_random_engine(seed));
    for (int i = 0; i < maquinaCriticaVetor.size(); i++)
    {
        if (para == true) {
            break;
        }
        vector < vector<int>>teste = solucao;
        int valronserir;
        for (int j = 0; j < teste[maquinaCritica].size(); j++)
        {
            if (maquinaCriticaVetor[i] == teste[maquinaCritica][j]) {

                teste[maquinaCritica].erase(teste[maquinaCritica].begin() + j);
                break;
            }
        }
        vector < vector<int>>inserir = teste;
        int trocasref = 9999;
        for (int j = 0; j < teste[maquinaCritica].size(); j++)
        {
            inserir = teste;
            inserir[maquinaCritica].insert(inserir[maquinaCritica].begin() + j, maquinaCriticaVetor[i]);
            int  trocas = ktns(inserir[maquinaCritica], maquinaCritica, inserir);
            if (trocasref > trocas) {
                trocasref = trocas;
                final1 = inserir;
                int makespanFinal = makespan(final1);
                if (makespanInicial > makespanFinal) {

                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < final1.size(); j++)
                    {
                        for (int k = 0; k < final1[j].size(); k++)
                        {
                            verificarTarefas[final1[j][k]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido) {
                        solucao = final1;
                        //interacao++;
                    }
                    else {
                        para = true;
                    }
                }
            }
        }
    }
    /*
    else {

        para = true;
    }*/

    int makespanInicio = makespan(entrada);
    int makespanFim = makespan(solucao);
    int diferenca2 = makespanInicio - makespanFim;
    if (diferenca2 > 0) {
        melhoriaRelocate += diferenca2;
    }

    return solucao;
}

vector<vector<int>> realocar(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<vector<int>>final1 = solucao;
    bool para = false;
    while (para == false) {
        int makespanInicial = makespan(solucao);
        vector<int>maquinaCriticaVetor = solucao[maquinaCritica];
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(maquinaCriticaVetor.begin(), maquinaCriticaVetor.end(), std::default_random_engine(seed));
        bool melhorou = false;
        for (int i = 0; i < maquinaCriticaVetor.size(); i++)
        {
            final1 = solucao;

            for (int k = 0; k < solucao[maquinaCritica].size(); k++)
            {
                if (final1[maquinaCritica][k] == maquinaCriticaVetor[i]) {
                    final1[maquinaCritica].erase(final1[maquinaCritica].begin() + k);
                    break;
                }
            }
            for (int k = 0; k < final1[maquinaCritica].size(); k++)
            {
                vector<vector<int>>teste = final1;
                teste[maquinaCritica].insert(teste[maquinaCritica].begin() + k, maquinaCriticaVetor[i]);
                int makespanFim = makespan(teste);
                int makespaInicio = makespan(solucao);
                if (makespanFim < makespaInicio) {
                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < teste.size(); j++)
                    {
                        for (int k2 = 0; k2 < teste[j].size(); k2++)
                        {
                            verificarTarefas[teste[j][k2]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido == true) {
                        solucao = teste;
                        melhorou = true;
                        int diferenca = makespaInicio - makespanFim;
                        melhoriaRelocate += diferenca;
                        break;
                    }

                }
            }
            if (melhorou == true) {
                break;
            }
        }
        if (melhorou == false) {
            para = true;
            break;
        }
        
    }
    return solucao;
}

vector<vector<int>>maiorArreptimento(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;

    bool para = false;

    while (para == false) {
        int ini = makespan(solucao);  
        vector<int>ordem;
        vector<int>ref;
       // cout << "aqui;" << endl;
        int ktnsMaquinaCritica = ktns(solucao[maquinaCritica], maquinaCritica, solucao);

        bool melhorou = false;
        for (int i = 0; i < solucao[maquinaCritica].size(); i++)
        {
            vector<vector<int>>tmp = solucao;
            tmp[maquinaCritica].erase(tmp[maquinaCritica].begin() + i);
           // cout << "ali" << endl;
            int kenTemp = ktns(tmp[maquinaCritica], maquinaCritica, tmp);
          //  cout << "não sei" << endl;
            if (ref.size() == 0) {
                ordem.push_back(solucao[maquinaCritica][i]);
                ref.push_back(kenTemp);
            }
            else {
                for (int k = 0; k < ref.size(); k++)
                {   // cout << "aqui"<<solucao[maquinaCritica].size();
                    if (ref[k] > kenTemp) {
                        ordem.insert(ordem.begin() + k, solucao[maquinaCritica][i]);
                        ref.insert(ref.begin() + k, kenTemp);
                        break;
                    }
                    else if (k == ref.size() - 1) {
                        ordem.push_back(solucao[maquinaCritica][i]);
                        ref.push_back(kenTemp);
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < ordem.size(); i++)
        {
            if (melhorou == true) {
                break;
            }
            vector<vector<int>>remover = solucao;
            for (int j = 0; j < remover[maquinaCritica].size(); j++)
            {
                if (ordem[i] == remover[maquinaCritica][j]) {
                    remover[maquinaCritica].erase(remover[maquinaCritica].begin() + j);
                    break;
                }
            }
            for (int k = 0; k < remover[maquinaCritica].size(); k++)
            {

                if (melhorou == true) {
                    break;
                }
                vector<vector<int>>final1 = remover;
                final1[maquinaCritica].insert(final1[maquinaCritica].begin() + k, ordem[i]);
              //  cout << "talvez" << endl;
                int fim = makespan(final1);
                int inicio = makespan(solucao);
                if (inicio > fim) {
                    bool valido = true;
                    vector<int>verificarTarefas(tarefas, 0);
                    for (int j = 0; j < final1.size(); j++)
                    {
                        for (int l = 0; l < final1[j].size(); l++)
                        {
                            verificarTarefas[final1[j][l]] += 1;
                        }
                    }

                    for (int i = 0; i < tarefas; i++)
                    {
                        if (verificarTarefas[i] != 1) {
                            valido = false;
                        }
                    }
                    if (valido == true) {
                        solucao = final1;
                        melhorou = true;
                        int diferenca = inicio - fim;
                        melhoriaMaiorArep += diferenca;
                        break;
                    }
                }
            }
        }
        if (melhorou == false) {
            para = true;
            break;
        }
    }

    return solucao;
}

//tre opt inicio
vector<int>temp;
void movimento1(vector<int>solucao, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solucao[j]);
    }
    // Pega do ponto 2 até ponto 1 +1
    for (int j = p2; j > p1; --j) {
        temp.push_back(solucao[j]);
    }
    // Pega do ponto 3 até o ponto 2 +1
    for (int j = p3; j > p2; --j) {
        temp.push_back(solucao[j]);
    }
    // Pega do ponto 3 + 1 até o final
    for (int j = p3 + 1; j < solucao.size(); ++j) {
        temp.push_back(solucao[j]);
    }
}
void movimento2(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 1 segue para Ponto 2+1 até Ponto 3
    for (int j = p2 + 1; j <= p3; ++j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 1+1 até o ponto 2
    for (int j = p1 + 1; j <= p2; ++j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 3 + 1 até o final
    for (int j = p3 + 1; j < solution.size(); ++j) {
        temp.push_back(solution[j]);
    }
}

void movimento3(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 1 segue para Ponto 3, inverte até Ponto 2 +1
    for (int j = p3; j > p2; --j) {
        temp.push_back(solution[j]);
    }
    // Pega do Ponto 1+1 até Ponto 2
    for (int j = p1 + 1; j <= p2; ++j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 3 + 1 até o final
    for (int j = p3 + 1; j < solution.size(); ++j) {
        temp.push_back(solution[j]);
    }
}

void movimento4(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 1 segue para Ponto 3, inverte até Ponto 1 +1
    for (int j = p3; j > p1; --j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 3 + 1 até o final
    for (int j = p3 + 1; j < solution.size(); ++j) {
        temp.push_back(solution[j]);
    }
}

void movimento5(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 1 segue para último, inverte até Ponto 3 + 1
    for (int j = solution.size() - 1; j > p3; --j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 2 + 1 até o Ponto 3
    for (int j = p2 + 1; j <= p3; ++j) {
        temp.push_back(solution[j]);
    }
    // Pega do ponto 2, inverte até Ponto 1-1
    for (int j = p2; j > p1; --j) {
        temp.push_back(solution[j]);
    }
}

void movimento6(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 2, inverte até Ponto 2+1
    for (int j = p2; j >= p1 + 1; --j) {
        temp.push_back(solution[j]);
    }
    // Pega do Ponto 2+1 até o final
    for (int j = p2 + 1; j < solution.size(); ++j) {
        temp.push_back(solution[j]);
    }
}

void movimento7(std::vector<int> solution, int p1, int p2, int p3) {
    temp.clear();
    // Em ordem até o ponto 1
    for (int j = 0; j <= p1; ++j) {
        temp.push_back(solution[j]);
    }
    // Ponto 2+1, segue até Ponto 3
    for (int j = p2 + 1; j <= p3; ++j) {
        temp.push_back(solution[j]);
    }
    // Pega do Ponto 2, inverte até P1+1
    for (int j = p2; j > p1; --j) {
        temp.push_back(solution[j]);
    }
    // Pega do Ponto 3+1, segue até o final
    for (int j = p3 + 1; j < solution.size(); ++j) {
        temp.push_back(solution[j]);
    }
}
vector<vector<int>> three_opt(vector<vector<int>>solution) {
    bool melhorou = false;
    vector<vector<int>>retorno = solution;
    vector<vector<int>>m1 = solution;
    vector<vector<int>>m2 = solution;
    vector<vector<int>>m3 = solution;
    vector<vector<int>>m4 = solution;
    vector<vector<int>>m5 = solution;
    vector<vector<int>>m6 = solution;
    vector<vector<int>>m7 = solution;
    int makespanInicio=makespan(solution);
    int maquinaCriticaAtual = maquinaCritica;
    vector<int>v1 = solution[maquinaCritica];
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(v1.begin(), v1.end(), std::default_random_engine(seed1));

    vector<int>v2 = solution[maquinaCritica];
    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(v2.begin(), v2.end(), std::default_random_engine(seed2));

    vector<int>v3 = solution[maquinaCritica];
    unsigned seed3 = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(v3.begin(), v3.end(), std::default_random_engine(seed3));

    for (int i = 0; i < v1.size(); ++i) {
        if (melhorou == true) {
            break;
        }
        for (int j = 0; j < v2.size(); ++j) {
            if (melhorou == true) {
                break;
            }
            if (v2[j] == v1[i]) {

            }
            else {
                for (int k = 0; k < v3.size(); ++k) {
                    if (melhorou == true) {
                        break;
                    }
                    if (v3[k] == v2[j] || v3[k] == v1[i]) {

                    }
                    else {
                        // cout << "inicio" << endl;
                        vector<int>ordenados;
                        for (int jk = 0; jk < solution[maquinaCriticaAtual].size(); jk++)
                        {
                            if (solution[maquinaCriticaAtual][jk] == v1[i] || solution[maquinaCriticaAtual][jk] == v2[j] || solution[maquinaCriticaAtual][jk] == v3[k]) {
                                ordenados.push_back(jk);
                            }
                        }
                        sort(ordenados.begin(), ordenados.end());
                        movimento1(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m1[maquinaCriticaAtual] = temp;
                        int m1MAkespan = makespan(m1);
                        // cout << m1MAkespan << endl;
                        if (makespanInicio > m1MAkespan) {
                            retorno = m1;
                            melhorou = true;
                            makespanInicio = m1MAkespan;
                        }
                        movimento2(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m2[maquinaCriticaAtual] = temp;
                        int m2MAkespan = makespan(m2);
                        // cout << m2MAkespan << endl;
                        if (makespanInicio > m2MAkespan) {
                            retorno = m2;
                            melhorou = true;
                            makespanInicio = m2MAkespan;

                        }
                        movimento3(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m3[maquinaCriticaAtual] = temp;
                        int m3MAkespan = makespan(m3);
                        //   cout << m3MAkespan << endl;
                        if (makespanInicio > m3MAkespan) {
                            retorno = m3;
                            melhorou = true;
                            makespanInicio = m3MAkespan;

                        }
                        movimento4(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m4[maquinaCriticaAtual] = temp;
                        int m4MAkespan = makespan(m4);
                        // cout << m4MAkespan << endl;
                        if (makespanInicio > m4MAkespan) {
                            retorno = m4;
                            melhorou = true;
                            makespanInicio = m4MAkespan;

                        }
                        movimento5(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m5[maquinaCriticaAtual] = temp;
                        int m5MAkespan = makespan(m5);
                        // cout << m5MAkespan << endl;
                        if (makespanInicio > m5MAkespan) {
                            retorno = m5;
                            melhorou = true;
                            makespanInicio = m5MAkespan;

                        }

                        movimento6(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m6[maquinaCriticaAtual] = temp;
                        int m6MAkespan = makespan(m6);
                        //   cout << m6MAkespan << endl;
                        if (makespanInicio > m6MAkespan) {
                            retorno = m6;
                            melhorou = true;
                            makespanInicio = m6MAkespan;

                        }

                        movimento7(solution[maquinaCriticaAtual], ordenados[0], ordenados[1], ordenados[2]);
                        m7[maquinaCriticaAtual] = temp;
                        int m7MAkespan = makespan(m7);
                        //  cout << m7MAkespan << endl;
                        if (makespanInicio > m7MAkespan) {
                            retorno = m7;
                            melhorou = true;
                            makespanInicio = m7MAkespan;

                        }
                    }
                }
            

                
            }
        }
    }

   // cout << makespanInicio << " " << makespan(retorno)<<endl;
    int inicio = makespan(solution);
    int diferenca = inicio - makespan(retorno);
   // cout << diferenca << endl;
    melhoria3opt += diferenca;

    return retorno;
}

vector<vector<int>>insercaoAleatoria(vector<vector<int>>solucao) {
    vector<vector<int>>solucion = solucao;
    int inicio = makespan(solucao);
    int maquinaDestino = maquinaCritica;
    bool melhorou = true;
    while (melhorou == true) {
        int itemMover = rand() % solucao[maquinaDestino].size();
        int posicao = rand() % solucao[maquinaDestino].size();
        vector<int>vetor;
        vector<vector<int>>verficar = solucion;
        verficar[maquinaDestino].insert(verficar[maquinaDestino].begin() + posicao, verficar[maquinaDestino][itemMover]);
        
        if (posicao > itemMover) {
            verficar[maquinaDestino].erase(verficar[maquinaDestino].begin() + itemMover);
        }
        else {
            int tmp = itemMover + 1;
            verficar[maquinaDestino].erase(verficar[maquinaDestino].begin() + tmp);
        }
        int makespanF = makespan(verficar);
        if (makespanF < inicio) {
            melhorou = true;
            solucion = verficar;
        }
        else {
            melhorou = false;
        }
    }
    
    int makesfim = makespan(solucion);
    melhoriaAleatoria += inicio - makesfim;
    return solucion;
}



vector<vector<int>>doubleBrind(vector<vector<int>>entrada) {
    return entrada;
}

vector<vector<int>> dbi(vector <vector<int>>ref) {
    //saber quantas ferramntas gasta cada tarefa
    vector<int>ferramentaTarefas;
    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }

    int t = ref.size();
    vector<vector<int>>saida;
    vector<int>tarefaMa;
    vector<int>tarefa;
    vector<int> newTarefa;
    vector<int>pos;
    for (int i = 0; i < t; i++)
    {
        tarefaMa.push_back(ref[i].size());
        for (int k = 0; k < ref[i].size(); k++)
        {
            tarefa.push_back(ref[i][k]);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int v1 = rand() % tarefa.size();
        pos.push_back(v1);
    }

    sort(pos.begin(), pos.end());

    for (int i = 0; i < pos[0] + 1; i++)
    {
        newTarefa.push_back(tarefa[i]);
    }

    for (int i = pos[2] + 1; i < pos[3] + 1; i++)
    {
        newTarefa.push_back(tarefa[i]);
    }

    for (int i = pos[1] + 1; i < pos[2] + 1; i++)
    {
        newTarefa.push_back(tarefa[i]);
    }
    for (int i = pos[0] + 1; i < pos[1] + 1; i++)
    {
        newTarefa.push_back(tarefa[i]);
    }
    for (int i = pos[3] + 1; i < tarefa.size(); i++)
    {
        newTarefa.push_back(tarefa[i]);
    }

    vector<int>tmp;
    vector<int>tmaq;
    int atual = -1;
    vector<int>jausando;
    bool para = false;
    vector<vector<int>>teste;
    for (int i = 0; i < maquinas; i++)
    {
        vector<int>t;
        teste.push_back(t);
    }
    int incio = newTarefa.size();
    int fim = 0;
    while (!newTarefa.empty()) {
        if (incio == fim) {
            break;
        }
        incio = newTarefa.size();
        // cout << newTarefa.size();
        int k = 0;
        for (int i = 0; i < maquinas; i++)
        {

            if (teste[i].size() < tarefaMa[i])
            {
                if (magazine[i] >= ferramentaTarefas[newTarefa[k]]) {
                    teste[i].push_back(newTarefa[k]);
                    newTarefa.erase(newTarefa.begin() + k);
                }
            }
            else {
                break;
            }

        }
        fim = newTarefa.size();
    }

    while (!newTarefa.empty()) {
        for (int i = 0; i < maquinas; i++)
        {
            if (magazine[i] >= ferramentaTarefas[newTarefa[0]]) {
                teste[i].push_back(newTarefa[0]);
                newTarefa.erase(newTarefa.begin() + 0);
            }
            if (newTarefa.size() == 0) {
                break;
            }
        }

    }
    /*
    while (para == false)
    {

        for (int i = 0; i < teste.size(); i++)
        {
            for (int k= 0; k < teste[i].size(); k++)
            {
                cout << teste[i][k]<<" ";
            }
            cout << endl;
        }
        cout << endl;
        cout << jausando.size()<<" ";




        for (int i = 0; i < maquinas; i++)
        {
            for (int k = 0; k < newTarefa.size(); k++)
            {
                if (teste[i].size() < tarefaMa[i])
                {
                    if (magazine[i] >= ferramentaTarefas[newTarefa[k]]) {
                        bool usado = false;
                        for (int j = 0; j < jausando.size(); j++)
                        {
                            if (jausando[j] == newTarefa[k]) {
                                usado = true;
                                break;
                            }
                        }
                        if (usado == false) {
                            teste[i].push_back(newTarefa[k]);
                            jausando.push_back(newTarefa[k]);
                        }
                    }
                }
                else {
                    break;
                }
            }
        }

        /*

      for (int i = 0; i < maquinas; i++)
      {
            tmp.clear();
            for (int k = 0; k < newTarefa.size(); k++)
            {
                if (magazine[i] >= ferramentaTarefas[newTarefa[k]]) {
                    if (tmp.size() < tarefaMa[i]) {
                        bool usado = false;
                        for (int l = 0; l < jausando.size(); l++)
                        {
                            if (jausando[l] == newTarefa[l]) {
                                usado = true;
                            }
                        }
                        if (usado == false) {
                            tmp.push_back(newTarefa[k]);
                            jausando.push_back(newTarefa[k]);
                        }

                    }
                }
            }
            saida.push_back(tmp);
      }*//*
        if (jausando.size() == newTarefa.size()) {
            cout <<  "aqui" << endl;
            para = true;
        }
    }
    */
    bool valido = true;
    vector<int>verificarTarefas(tarefas, 0);
    for (int j = 0; j < teste.size(); j++)
    {
        for (int k = 0; k < teste[j].size(); k++)
        {
            verificarTarefas[teste[j][k]] += 1;
            //cout << teste[j][k] << " ";
        }
        //   cout << endl;
    }

    for (int i = 0; i < tarefas; i++)
    {
        if (verificarTarefas[i] != 1) {
            valido = false;
        }
    }
    if (valido) {   // cout << valido <<" aqui" << endl;
        int mkinicio = makespan(ref);
        int mkfim = makespan(teste);
        double diferenca = mkfim-mkinicio;
        pioraPertubacao += diferenca;
        return teste;
    }
    /*
    for (int i = 0; i < ref.size(); i++)
    {
        for (int k = 0; k < ref[i].size(); k++)
        {
            cout << ref[i][k] << " ";
        }
        cout << endl;
    }*/
    return ref;
}
   
vector<int>tarefasUsadas;
vector<int>ferramanetasPorTarefa;
void prePertubacao() {
    vector<int>ferramentaTarefas;

    for (int i = 0; i < tarefas; i++)
    {
        int temp = 0;
        for (int j = 0; j < ferramentas; j++)
        {
            if (matrizFerramentas[j][i] == 1) {
                temp++;
            }
        }
        ferramentaTarefas.push_back(temp);
    }
    ferramanetasPorTarefa = ferramentaTarefas;
    for (int i = 0; i < ferramentaTarefas.size(); i++)
    {
        int ref = 0;
        for (int j = 0; j < magazine.size(); j++)
        {
            if (magazine[j] >= ferramentaTarefas[i]) {
                ref++;
            }
        }
        if (ref > 1) {
            tarefasUsadas.push_back(i);
        }
    }
}
double valorMAximo = 0.01;
vector<vector<int>>novaPertubacao(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<int>tarefasShuff = tarefasUsadas;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(tarefasShuff.begin(), tarefasShuff.end(), std::default_random_engine(seed));
    double vintePorcenro = tarefas * nivelPertubacao;
    int numero_int = static_cast<int>(std::ceil(vintePorcenro));
    if (numero_int == 0) {
        numero_int++;
    }
    if (nivelPertubacao > valorMAximo) {
        valorMAximo = nivelPertubacao;
    }
    vintePorcenro = numero_int;
   // cout << vintePorcenro << endl;
    for (int i = 0; i < vintePorcenro; i++)
    {
        //sotear maquiana
        int novaMAquina = rand() % magazine.size();
        int contador = -1;
        int maquinaDestino = -1;

        while (contador <= novaMAquina) {
      //  cout << contador <<" " << maquinaDestino << endl;
            for (int j = 0; j < magazine.size(); j++)
            { 
                if (magazine[j] >= ferramanetasPorTarefa[tarefasShuff[i]]) {
                    contador++;
                   
                        if (contador == novaMAquina) {
                            maquinaDestino = j;
                            break;
                        }
                }
            }
            if (contador == novaMAquina) {
                break;
            }
        }
        //sotear posicao
      
        for (int k = 0; k < solucao.size(); k++)
        {
            bool para = false;
            for (int l = 0; l < solucao[k].size(); l++)
            {
                if (solucao[k][l] == tarefasShuff[i]) {
                    solucao[k].erase(solucao[k].begin() + l);
                    para = true;
                    break;
                }
            }
            if (para == true) {
                break;
            }
        }
        //cout << "maquinadestino <<" << maquinaDestino << endl;
        if (solucao[maquinaDestino].size() > 0) {
            int posicao = rand() % solucao[maquinaDestino].size();
            solucao[maquinaDestino].insert(solucao[maquinaDestino].begin() + posicao, tarefasShuff[i]);
        }
    }
    bool valido = true;
    vector<int>verificarTarefas(tarefas, 0);
    for (int j = 0; j < solucao.size(); j++)
    {
        for (int k = 0; k < solucao[j].size(); k++)
        {
            verificarTarefas[solucao[j][k]] += 1;
            //cout << teste[j][k] << " ";
        }
        //   cout << endl;
    }

    for (int i = 0; i < tarefas; i++)
    {
        if (verificarTarefas[i] != 1) {
            valido = false;
        }
    }
    if (valido) {   // cout << valido <<" aqui" << endl;
        int makespanInicio = makespan(entrada);
        int mkfim = makespan(solucao);
        double difer = mkfim - makespanInicio;
        pioraPertubacao += difer;
        return solucao;
    }
    return entrada;
}


vector < vector<int>>vns(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector< vector<int>>dbisolucao = entrada;
    for (int i = 0; i < 1000; i++)
    {/*
        cout << "aqui" << endl;for (int l = 0; l < solucao.size(); l++)
        {
            for (int k = 0; k < solucao[l].size(); k++)
            {
                cout << solucao[l][k] << " ";
            }
            cout << endl;
        }*/

        interacaoFinal++;
        // cout << i << endl;
        high_resolution_clock::time_point tempoatual = high_resolution_clock::now();
        duration <double> time;
        time = duration_cast<duration<double>>(tempoatual - tempoinicial);
        if (time.count() > 3600) {
            break;
        }
        vector<vector<int>>tmp = insertion(dbisolucao);
        //swapesrqueda(solucao
     //   cout << "ali" << endl; 
        tmp = swapesrqueda(tmp);
        // cout << "la" << endl;

        tmp = rellocate(tmp);

        int solucaoMakespan = makespan(solucao);
        int tmpMakespan = makespan(tmp);
        // cout << tmpMakespan << endl;
        if (solucaoMakespan > tmpMakespan) {
            solucao = tmp;

            dbisolucao = solucao;
        }
        //  cout << "talvez";
        dbisolucao = dbi(dbisolucao);
        /*
        for (int k = 0; k < maquinas; k++) {
            for (int j = 0; j < dbisolucao[k].size(); j++) {
                cout << dbisolucao[k][j] << " ";

            }
            cout << endl;
        }*/
    }
    return solucao;
}

vector<vector<int>>vnd(vector<vector<int>>entrada) {
    vector<vector<int>>solucao = entrada;
    vector<vector<int>> dbisolucao = entrada;
    bool melhorou = false;
    int i = 0;
    int interacaoSemMelhoria = 0;//deve ser reniciado a cada 100
    prePertubacao();
    while (i < 1000)
    {
        if (melhorou == false) {
            interacaoFinal++;
            interacaoSemMelhoria++;
        }
        //cout << i << endl;
        //cout << nivelPertubacao << "intreracao sem melhoria" << endl;
        if (interacaoSemMelhoria == 100) {
            nivelPertubacao += 0.01;
            interacaoSemMelhoria = 0;
        }
        melhorou = false;
        duration <double> time;
        high_resolution_clock::time_point tempoatual = high_resolution_clock::now();
        time = duration_cast<duration<double>>(tempoatual - tempoinicial);
        if (time.count() > 3600) {
            break;
        }

        int makespanSolucao = makespan(solucao);

        int makespanInicial = makespan(dbisolucao);
       // cout << "inserir" << endl;
        vector<vector<int>>tmp = insertion2(dbisolucao);
        
        int makespanInseir = makespan(tmp);
        //    cout << "sair insetion" << endl;
        if (makespanInicial > makespanInseir) {
            melhorou = true;
            dbisolucao = tmp;
            if (makespanSolucao > makespanInseir) {
                solucao = tmp;
                melhorInteracao = interacaoFinal;
                interacaoSemMelhoria = 0;
                nivelPertubacao = 0.02;

                bool achou = false;
                for (int k = 0; k < interacaoqueMelhora.size(); k++)
                {
                    if (interacaoqueMelhora[k] == i) {
                        achou = true;
                    }
                }
                if (achou == false) {
                    interacaoqueMelhora.push_back(i);
                }
            }
        }
        if (melhorou == false) {
           // cout << "swap" << endl;
            tmp = swapesrqueda(tmp);
            int makespanswap = makespan(tmp);

            if (makespanInicial > makespanswap) {
                melhorou = true;
                if (makespanSolucao > makespanswap) {
                    solucao = tmp;
                    melhorInteracao = interacaoFinal;
                    interacaoSemMelhoria = 0;
                    nivelPertubacao = 0.02;

                    bool achou = false;
                    for (int k = 0; k < interacaoqueMelhora.size(); k++)
                    {
                        if (interacaoqueMelhora[k] == i) {
                            achou = true;
                        }
                    }
                    if (achou == false) {
                        interacaoqueMelhora.push_back(i);
                    }
                }
                dbisolucao = tmp;

            }
        }

        if (melhorou == false) {// cout << "morri" << endl;
          //  cout << "maior" << endl;
            //tmp = maiorArreptimento(tmp);
            tmp = realocar(tmp);
           // tmp = insercaoAleatoria(tmp);
     // cout << "no morri" << endl;
            int solucaoMakespan = makespan(solucao);
            int tmpMakespan = makespan(tmp);
            // cout << tmpMakespan << endl;
            if (solucaoMakespan > tmpMakespan) {
                melhorou = true;
                if (makespanSolucao > tmpMakespan) {
                    solucao = tmp;
                    melhorInteracao = interacaoFinal;
                    interacaoSemMelhoria = 0;
                    nivelPertubacao = 0.02;

                        bool achou = false;
                        for (int k = 0; k < interacaoqueMelhora.size(); k++)
                        {
                            if (interacaoqueMelhora[k] == i) {
                                achou = true;
                            }
                        }
                        if (achou == false) {
                            interacaoqueMelhora.push_back(i);
                        }

                }
                dbisolucao = tmp;

            }
        }      
        /*
        if (melhorou == false) {
           // cout << "rodou" << endl;
            tmp = three_opt(tmp);
            int makespanopt = makespan(tmp);

            if (makespanInicial > makespanopt) {
                melhorou = true;
                if (makespanSolucao > makespanopt) {
                    solucao = tmp;
                    melhorInteracao = interacaoFinal;
                }
                dbisolucao = tmp;

            }
        }*/
        
      
        if (melhorou == false) {
            dbisolucao = solucao;
            dbisolucao = novaPertubacao(dbisolucao);
            i++;
        }

    }
    return solucao;
}

int main() {
    // int maquinas,tarefas,ferramentas;
    cin >> maquinas >> tarefas >> ferramentas;
    //vector<int>magazine;
    for (int i = 0; i < maquinas; i++) {
        int temp;
        cin >> temp;
        magazine.push_back(temp);
    }
    // vector<int>tempoTroca;
    for (int i = 0; i < maquinas; i++) {
        int temp;
        cin >> temp;
        tempoTroca.push_back(temp);
    }

    for (int i = 0; i < maquinas; i++) {
        vector<int>temp;
        for (int j = 0; j < tarefas; j++) {
            int temp1;
            cin >> temp1;
            temp.push_back(temp1);
        }
        tempoProcessamento.push_back(temp);
    }

    for (int i = 0; i < ferramentas; i++) {
        vector<int>temp;
        for (int j = 0; j < tarefas; j++) {
            int temp1;
            cin >> temp1;
            temp.push_back(temp1);
        }
        matrizFerramentas.push_back(temp);
    }
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    high_resolution_clock::time_point total1 = high_resolution_clock::now();
    vector<vector<int>>completudeFiltro = heuriticaSimilaridade();
    completudeFiltro = refinamentoInsertion(completudeFiltro);
    vector<vector<int>>completude = heuritica();
    completude = refinamentoInsertion(completude);
    vector<vector<int>>similaridade = heuriticaSimilaridade2();
    similaridade = refinamentoInsertion(similaridade);

    int makespanFitro = makespan(completudeFiltro);
    int makespanCompletide = makespan(completude);
    int makespanSimilaridade = makespan(similaridade);

    if (makespanFitro <= makespanCompletide && makespanFitro < makespanSimilaridade) {
        solucao = completudeFiltro;
    }
    else if (makespanCompletide < makespanFitro && makespanCompletide < makespanSimilaridade) {
        solucao = completude;
    }
    else
    {
        solucao = similaridade;
    }
    ofstream makeFiltrp;
    makeFiltrp.open("makespanFiltro.txt", ios::app);
    makeFiltrp << makespanFitro << "\n";
    makeFiltrp.close();
    ofstream ftfFitro;
    ftfFitro.open("ftfFitroo.txt", ios::app);
    ftfFitro << flowTimeTotal(completudeFiltro) << "\n";
    ftfFitro.close();

    ofstream makeCompletudade;
    makeCompletudade.open("makespanComplerude.txt", ios::app);
    makeCompletudade << makespanCompletide << "\n";
    makeCompletudade.close();
    ofstream ftfCompletude;
    ftfCompletude.open("ftfnCompletude.txt", ios::app);
    ftfCompletude << flowTimeTotal(completude) << "\n";
    ftfCompletude.close();

    ofstream makeSimilaridade;
    makeSimilaridade.open("makespanSimilaridade.txt", ios::app);
    makeSimilaridade << makespanSimilaridade << "\n";
    makeSimilaridade.close();
    ofstream ftfSimilaridade;
    ftfSimilaridade.open("ftfnSimilaridade.txt", ios::app);
    ftfSimilaridade << flowTimeTotal(similaridade) << "\n";
    ftfSimilaridade.close();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration <double> time;
    time = duration_cast<duration<double>>(t2 - t1);
    // ofstream inicio;
     //inicio.open("tempoHC.txt", ios::app);
   //  inicio << time.count() << "\n";
   //  inicio.close();
    for (int i = 0; i < maquinas; i++) {
        for (int j = 0; j < solucao[i].size(); j++) {
            cout << solucao[i][j] << " ";

        }
        cout << endl;
    }
    ofstream make1;
    make1.open("makespanInicio.txt", ios::app);
    make1 << makespan(solucao) << "\n";
    make1.close();
    ofstream ftf;
    ftf.open("ftfnInicio.txt", ios::app);
    ftf << flowTimeTotal(solucao) << "\n";
    ftf.close();
    cout << makespan(solucao) << " " << flowTimeTotal(solucao) << endl;
    t1 = high_resolution_clock::now();
    /*
    vector<int>tmp;
    tmp.push_back(0);
    solucao[0] = tmp;
    vector<int>tm;
    tm.push_back(1);
    tm.push_back(2);
    tm.push_back(3);
    tm.push_back(4);
    tm.push_back(5);
    tm.push_back(6);
    tm.push_back(7);
    tm.push_back(8);
    tm.push_back(9);
    solucao[1] = tm;*/
    solucao = vnd(solucao);
    //solucao = swapesrqueda(solucao);// 36 40
   // solucao = swapdireita(solucao);//36
   /*
    32 13 15 39 10 3 12 7 0
        36 17 20 11 6 25 35 19 31 14 21 4
        37 24 34 16 27 30 26 38
        33 22 5 28 23 9 2 8 18 29 1*/

    t2 = high_resolution_clock::now();
    time = duration_cast<duration<double>>(t2 - t1);
    ofstream fim;
    fim.open("vns.txt", ios::app);
    fim << time.count() << "\n";
    fim.close();
    for (int i = 0; i < maquinas; i++) {
        for (int j = 0; j < solucao[i].size(); j++) {
            cout << solucao[i][j] << " ";

        }
        cout << endl;
    }
    ofstream make2;
    make2.open("makespanFim.txt", ios::app);
    make2 << makespan(solucao) << "\n";
    make2.close();
    ofstream ftf2;
    ftf2.open("ftfFim.txt", ios::app);
    ftf2 << flowTimeTotal(solucao) << "\n";
    ftf2.close();
    /*
    for (int i = 0; i < maquinas; i++) {
        for (int j = 0; j < trocasMagazine[i].size(); j++) {
            cout << trocasMagazine[i][j] << " ";

        }
        cout << endl;
    }*/
    high_resolution_clock::time_point total2 = high_resolution_clock::now();
    time = duration_cast<duration<double>>(total2 - total1);
    ofstream total;
    total.open("total.txt", ios::app);
    total << time.count() << "\n";
    total.close();
    cout << makespan(solucao) << " " << flowTimeTotal(solucao);
    std::cout << "Hello World!\n";
    cout << interacao;
    ofstream interacao2;
    interacao2.open("interacao2.txt", ios::app);
    interacao2 << interacao << "\n";
    interacao2.close();
    int trocas = 0;
    for (int i = 0; i < maquinas; i++)
    {
        trocas += ktns(solucao[i], i, solucao);
    }
    cout << "trocas" << trocas << endl;
    ofstream trocas2;
    trocas2.open("trocas.txt", ios::app);
    trocas2 << trocas << "\n";
    trocas2.close();

    ofstream meloriaInseirTXT;
    meloriaInseirTXT.open("meloriaInseirTXT.txt", ios::app);
    meloriaInseirTXT << (melhoriaInserir / interacaoFinal) << "\n";
    meloriaInseirTXT.close();

    ofstream meloriaRelocateTXT;
    meloriaRelocateTXT.open("meloriaRelocateTXT.txt", ios::app);
    meloriaRelocateTXT << (melhoriaRelocate / interacaoFinal) << "\n";
    meloriaRelocateTXT.close();

    ofstream meloriaSwapTXT;
    meloriaSwapTXT.open("meloriaSwapTXT.txt", ios::app);
    meloriaSwapTXT << (melhoriaSwap / interacaoFinal) << "\n";
    meloriaSwapTXT.close();

    ofstream interacaoFinal2;
    interacaoFinal2.open("interacaoFinal.txt", ios::app);
    interacaoFinal2 << interacaoFinal << "\n";
    interacaoFinal2.close();

    ofstream melhoriaRealocar;
    melhoriaRealocar.open("melhoriaSwapRealocar.txt", ios::app);
    melhoriaRealocar << (melhoriaswaprealoca / interacaoFinal) << "\n";
    melhoriaRealocar.close();

    ofstream melhoriaMAior;
    melhoriaMAior.open("melhoriaMAior.txt", ios::app);
    melhoriaMAior << (melhoriaMaiorArep / interacaoFinal) << "\n";
    melhoriaMAior.close();

    ofstream melhoriaopt;
    melhoriaopt.open("melhoria3opt.txt", ios::app);
    melhoriaopt << (melhoria3opt / interacaoFinal) << "\n";
    melhoriaopt.close();

    ofstream piora;
    piora.open("pertubvacao.txt", ios::app);
    piora << (pioraPertubacao / interacaoFinal) << "\n";
    piora.close();

    ofstream interacaoMelhor;
    interacaoMelhor.open("interacaoMelhor.txt", ios::app);
    interacaoMelhor << melhorInteracao << "\n";
    interacaoMelhor.close();



    ofstream interacaoMelhoria;
    interacaoMelhoria.open("interacaoMelhoria.txt", ios::app);
    cout << interacaoqueMelhora.size();
    for (int i = 0; i < interacaoqueMelhora.size(); i++)
    {
        int temp = interacaoqueMelhora[i];
        interacaoMelhoria << temp << " ";
    }
    interacaoMelhoria << "\n";
    interacaoMelhoria.close();


    ofstream valorMAx;
    valorMAx.open("valorMaximo.txt", ios::app);
    valorMAx <<valorMAximo<< "\n";
    valorMAx.close();

    ofstream melhoraiaALe;
    melhoraiaALe.open("melhoraiaALe.txt", ios::app);
    melhoraiaALe << (melhoriaAleatoria/interacaoFinal)<<"\n";
    melhoraiaALe.close();
    return 0;
}