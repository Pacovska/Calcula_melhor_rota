#include "mapa.h"

//Função responsável por fazer o cálculo da menor rota entre as cidades informadas.
void calculo(unordered_map<string, vector<mapa>>& rota, vector<string>& city, string& final,
             unordered_map<string, tipo_grafo>& grafo_distancia) {

    // Nessa primeira parte é criada uma tabela D, onde:
    // D[nodo] = (infinito, próximo_nodo)
    for (auto it : city) {
        grafo_distancia[it] = tipo_grafo{"", 99999999};
    }
    grafo_distancia[final] = tipo_grafo{"", 0};
    // Vale lembrar que o D[nodoA] = (0, nodoA), sendo nodoA o destino

    // Cria Q, lista contendo todos os nodos (incluindo nodoA)
    vector<string> Q = city;

    // Enquanto Q não estiver vazio:
    while (!Q.empty()) {
        // Retira de Q o nodo denominado u, que é o nodo com menor distância até nodoA
        string u;
        int m_distancia = 99999999;
        for (auto it : Q) {
            if (grafo_distancia[it].distancia < m_distancia) {
                u = it;
                m_distancia = grafo_distancia[it].distancia;
            }
        }

        // Para cada nodo vizinho (v) de u:
        for (auto vizinho : rota[u]) {
            string v = vizinho.destino;
            int dist_v = m_distancia + vizinho.distancia; // Calcular a distância do novo v: dist_v = dist_u + distancia(u,v)
            if (dist_v < grafo_distancia[v].distancia) { // Se dist_v for menor que a distância contida em D[v]
                grafo_distancia[v] = tipo_grafo{u, dist_v}; // Atualizar D[v] = (dist_v, u)
            }
        }

        Q.erase(std::find(Q.begin(), Q.end(), u)); // Remove u de Q até ficar vazio
    }
}


void mostra_distancia(unordered_map<string, vector<mapa>> rota, vector<string> city) {
    string final;
    string inicio, escolha;
    bool continua = true;

    while (continua) {
        cout << "|==============================|" << endl;
        cout << "|  INFORME A CIDADE DE ORIGEM  |" << endl;
        cout << "|      E CIDADE DE DESTINO     |" << endl;
        cout << "|  CASO DESEJE SAIR, DIGITE 0  |" << endl;
        cout << "|==============================|" << endl;
        cout << "| Digite a origem: ";
        getline(cin, inicio); // Faz a leitura do que for digitado pelo usuário como cidade de origem

        if (inicio == "0") {
            break; // Se o usuário digitar zero, sai do primeiro looping principal
        }

        auto it = rota.find(inicio);

        if (it == rota.end()) { // Caso a cidade digitada não esteja no arquivo
            cout << "| " << inicio << "Desconhecido" << endl; // Retorna mensagem de desconhecido
            cout << "| Certifique que o nome da cidade esteja correto e com letras maiusculas" << endl; // E pede ao usuario que verifique se digitou corretamente
        } else {
            cout << "| Digite o destino:";
            getline(cin, final); // Faz a leitura do que for digitado pelo usuário como cidade de destino

            if (final == "0") {
                break; // Se o usuário digitar zero, sai do primeiro looping principal
            }

            if (rota.find(final) == rota.end()) { // Caso a cidade digitada não esteja no arquivo
                cout << "| " << final << "Desconhecido" << endl; // Retorna mensagem de desconhecido
                cout << "| Certifique que o nome da cidade esteja correto e com letras maiusculas" << endl; // E pede ao usuario que verifique se digitou corretamente
            } else {
                unordered_map<string, tipo_grafo> grafo_distancia;
                calculo(rota, city, final, grafo_distancia);

                // Imprime o percurso completo da cidade de origem ate a de destino.
                vector<string> caminho;
                string atual = inicio;
                while (atual != final) {//Loop responsável por percorrer todo o caminho feito pelo algoritmo e armazenar as cidades no vector caminho
                    caminho.push_back(atual);
                    atual = grafo_distancia[atual].cidade;
                }
                caminho.push_back(final);

                cout << "| As cidades percorridas sao:" << endl << "| "; 

                for (size_t i = 0; i < caminho.size(); ++i) {
                    cout << caminho[i];
                    if (i < caminho.size() - 1) {
                        cout << " -> ";
                    }
                }
                cout << endl;

                cout << "| Distancia total: " << grafo_distancia[inicio].distancia << "km" << endl;
            }
        }
    }
}

void mostra_distancia_cidades(unordered_map<string, vector<mapa>>& rota, vector<string>& city) {
    cout << "|==============================|" << endl;
    cout << "|      INFORME AS CIDADES      |" << endl;
    cout << "|      NA ORDEM QUE DESEJA     |" << endl;
    cout << "|            VISITAR           |" << endl;
    cout << "|   (Digite 0 para encerrar)   |" << endl;
    cout << "|==============================|" << endl;

    vector<string> cidades;
    string cidade;
    while (true) {
        cout << "| Digite uma cidade: ";
        getline(cin, cidade);

        if (cidade == "0") {
            if (cidades.size() < 2) {
                cout << "| É necessário informar no mínimo 2 cidades." << endl;
                continue; // Reinicia o loop para que o operador insira pelo menos 2 cidades
            }
            break; // Sai do loop caso o operador digite 0 e haja pelo menos 2 cidades informadas
        }

        auto it = rota.find(cidade);
        if (it == rota.end()) {
            cout << "| " << cidade << " Desconhecido" << endl;
            cout << "| Certifique que o nome da cidade esteja correto e com letras maiúsculas" << endl;
        } else {
            cidades.push_back(cidade);
        }
    }

    cout << "|==============================|" << endl;
    cout << "|  Cidades Informadas:         |" << endl;
    cout << "|==============================|" << endl;
    cout << "|";
    for (const string& cidade : cidades) {
        cout << " -> " << cidade;
    }
    cout << endl;
    cout << "|==============================|" << endl;

    vector<string> caminho_total;
    int distancia_total = 0;

    for (size_t i = 0; i < cidades.size() - 1; ++i) {
        string inicio = cidades[i];
        string final = cidades[i + 1];

        unordered_map<string, tipo_grafo> grafo_distancia;
        calculo(rota, city, final, grafo_distancia);

        vector<string> caminho;
        string atual = inicio;
        while (atual != final) {
            caminho.push_back(atual);
            atual = grafo_distancia[atual].cidade;
        }

        // Verifica se a cidade final já está presente no caminho
        if (caminho.back() != final) {
            caminho.push_back(final);
        }

        caminho_total.insert(caminho_total.end(), caminho.begin(), caminho.end());
        distancia_total += grafo_distancia[inicio].distancia;
    }

    caminho_total.erase(unique(caminho_total.begin(), caminho_total.end()), caminho_total.end());

    cout << "| Distância total: " << distancia_total << " km" << endl;
}
