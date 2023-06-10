#ifndef MAPA_H
#define MAPA_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <locale>
#include <unistd.h>
#include <cstdlib>
#include <cctype>


using namespace std;

struct mapa {
    string destino;
    int distancia;
};

struct tipo_grafo {
    string cidade;
    int distancia;
};

//Função responsável pelo menu, onde cria ao usuário uma forma de interação com o código
int menu();

//Essa função tem como principal objetivo separar o arquivo recebido onde contém duas cidades e a distancia
void separa_rotas(string arg,unordered_map<string,vector<mapa>>& rota,vector<string>& city);

//Função responsável por mostrar as cidades, quando clicado na opção 1, já organizadas por ordem alfabetica. 
void mostrar_cidades(vector<string> & cidade);

//Função responsável por fazer o cálculo da menor rota entre as cidades informadas.
void calculo(unordered_map<string, vector<mapa>>& rota, vector<string>& city,string& final, unordered_map<string, tipo_grafo>& grafo_distancia);

//Função responsável por mostrar as cidades, quando clicado na opção 1, já organizadas por ordem alfabetica. 
void mostra_distancia(unordered_map<string, vector<mapa>> rota, vector<string> city);

// Função responsável por mostrar a melhor rota das cidades informadas, tendo como base cidades >= 2.
void mostra_distancia_cidades(unordered_map<string, vector<mapa>>& rota, vector<string>& city);

#endif
