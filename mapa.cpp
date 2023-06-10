#include "mapa.h"

using namespace std;


//Função responsável pelo menu, onde cria ao usuário uma forma de interação com o código
int menu(){
    void limparTela();
    int opcao = -1;
    
    cout << "|==============================|" << endl;
    cout << "|          GPS JOPERA          |" << endl;
    cout << "| O SEU MAPA PARA TODO MOMENTO |" << endl;
    cout << "|==============================|" << endl;
    while(opcao > 4 || opcao < 1) {
        cout << "|==============================|" << endl;
        cout << "|  SELECIONE UMA OPCAO ABAIXO  |" << endl;
        cout << "| 1 - VERIFICAR CIDADES        |" << endl;
        cout << "| 2 - VERIFICAR ROTA           |" << endl;
        cout << "| 3 - VERIFICAR ROTA PLUS      |" << endl;
        cout << "| 4 - SAIR                     |" << endl;
        cout << "|==============================|" << endl;
        cout << "| DIGITE SUA OPCAO: ";
        cin  >> opcao;
        cin.ignore();
    }

    return opcao;
}

//Essa função tem como principal objetivo separar o arquivo recebido onde contém duas cidades e a distancia
void separa_rotas(string arg,unordered_map<string,vector<mapa>>& rota,vector<string>& city) {
    mapa valor;
    ifstream arq(arg); //Abre o arquivo
    if (! arq.is_open()) { //Se o arquivo não abrir, retornar arquivo inválido
        cerr << "Arquivo ivalido";
    }
    string mapa;
    string cidade;
    string destino_I;
    string num;
    int qtde_I;

    //Através de um getline é feito a leitura do arquivo e a separação do conteúdo em strings.
    while (getline(arq, mapa)) {
        // A cada virgula, o conteudo é separado em uma string diferente, criadas acima.
        istringstream s(mapa);
        getline(s, cidade, ',');
        getline(s, destino_I, ',');
        getline(s, num, ',');
        qtde_I = stoi(num);

        city.push_back(cidade);
        // É pego o que foi separado a cima e armazenado na struct mapa, que foi nomeada de aux
        valor.destino = destino_I;
        valor.distancia = qtde_I;

        rota[cidade].push_back(valor);
    }
    unique(city.begin(),city.end());
}

//Função responsável por mostrar as cidades, quando clicado na opção 1, já organizadas por ordem alfabetica. 
void mostrar_cidades(vector<string>& cidade) {
    sort(cidade.begin(), cidade.end());  //Ordena o vector em ordem crescente
    auto it = unique(cidade.begin(), cidade.end()); //Reorganiza as cidades
    cidade.erase(it, cidade.end()); // Remove as duplicadas a partir do interador it

    string escolha = "";
    bool continua = true;

    //Loop responsável por receber os caracteres digitados pelo usuario e mostrar palavras
    //que começam com esses caracteres
    while (continua) {
        cout << "|==============================|" << endl;
        cout << "|   DIGITE A PRIMEIRA LETRA    |" << endl;
        cout << "|   DA CIDADE DE SUA ESCOLHA   |" << endl;
        cout << "|      OU ZERO PARA SAIR       |" << endl;
        cout << "|==============================|" << endl;
        cout << "|>";
        cin >> escolha;
        cin.ignore();
            
        if (escolha.size() != 1){
            cout << "|  DIGITE SOMENTE UM CARACTERE |" << endl;
            continue;
        }else if (escolha == "0") {
            continua = false;
        } else {
            escolha[0] = toupper(escolha[0]);

            bool encontrou = false;

            cout << "| Cidades com a letra '" << escolha << "':" << endl;
            for (auto i : cidade) {
                if (i[0] == escolha[0]) {
                    cout << "| " << i << endl;
                    encontrou = true;
                }
            }

            if (!encontrou) {
                cout << "| Nenhuma cidade com a letra '" << escolha << "'." << endl;
            }
        }
    }
}