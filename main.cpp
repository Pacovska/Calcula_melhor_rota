#include <iostream>
#include "mapa.h"

using namespace std;

int main(int argc, char **argv)
{
    setlocale(LC_ALL,"Portuguese");
    unordered_map<string, vector<mapa>> rota; //Cria uma tabela de nome rota
    vector<string> city; //Cria um vector chamado city

    separa_rotas(argv[1],rota, city);

    while (true){
        int valor = menu();

        if (valor ==  1){
            mostrar_cidades(city);
        }else if (valor == 2){
            mostra_distancia(rota, city);
        }else if (valor == 3){
            mostra_distancia_cidades(rota, city);
        }else{
            return 0;
        }
    }
    
    return 0;
}