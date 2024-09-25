#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Grafo {
private:
    int numVertices;
    vector<vector<int>> matrizAdj;
    unordered_map<int, vector<int>> listaAdj;

public:
    // Construtor
    Grafo(int numVertices) {
        this->numVertices = numVertices;
        matrizAdj.resize(numVertices, vector<int>(numVertices, 0));
    }

    // Função para adicionar aresta (usada para ambas as representações)
    void adicionarAresta(int origem, int destino) {
        matrizAdj[origem][destino] = 1;
        matrizAdj[destino][origem] = 1; // Para grafos não direcionados
        listaAdj[origem].push_back(destino);
        listaAdj[destino].push_back(origem); // Para grafos não direcionados
    }

    // Função para carregar o grafo a partir de um arquivo
    void carregarGrafo(string nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        string linha;
        while (getline(arquivo, linha)) {
            istringstream iss(linha);
            int origem, destino;
            if (!(iss >> origem >> destino)) { break; }
            adicionarAresta(origem, destino);
        }
        arquivo.close();
    }

    // Função de BFS que imprime o caminho entre dois vértices
    void BFS(int s, int t) {
        vector<bool> visitado(numVertices, false);
        vector<int> caminho(numVertices, -1); // Para armazenar o caminho
        queue<int> fila;
        
        visitado[s] = true;
        fila.push(s);

        while (!fila.empty()) {
            int v = fila.front();
            fila.pop();

            if (v == t) {
                break;
            }

            for (int adj : listaAdj[v]) {
                if (!visitado[adj]) {
                    visitado[adj] = true;
                    caminho[adj] = v; // Rastrear o caminho
                    fila.push(adj);
                }
            }
        }

        // Verifica se há caminho entre s e t
        if (caminho[t] == -1) {
            cout << "Não há caminho entre os vértices " << s << " e " << t << endl;
        } else {
            // Imprimir o caminho
            stack<int> caminhoFinal;
            for (int v = t; v != -1; v = caminho[v]) {
                caminhoFinal.push(v);
            }

            cout << "Caminho entre " << s << " e " << t << ": ";
            while (!caminhoFinal.empty()) {
                cout << caminhoFinal.top() << " ";
                caminhoFinal.pop();
            }
            cout << endl;
        }
    }

    // Função de DFS não-recursivo utilizando pilha
    void DFS(int inicio) {
        vector<bool> visitado(numVertices, false);
        stack<int> pilha;

        pilha.push(inicio);

        while (!pilha.empty()) {
            int v = pilha.top();
            pilha.pop();

            if (!visitado[v]) {
                visitado[v] = true;
                cout << v << " "; // Processar vértice

                for (int adj : listaAdj[v]) {
                    if (!visitado[adj]) {
                        pilha.push(adj);
                    }
                }
            }
        }
        cout << endl;
    }

    // Função para exibir a matriz de adjacência
    void exibirMatrizAdj() {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << matrizAdj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Função para exibir a lista de adjacência
    void exibirListaAdj() {
        for (const auto& par : listaAdj) {
            cout << par.first << ": ";
            for (int adj : par.second) {
                cout << adj << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Teste para cada instância de grafo
    vector<pair<string, int>> instancias = {
        {"instancia_grafo/pcv4.txt", 4},
        {"instancia_grafo/pcv10.txt", 10},
        {"instancia_grafo/pcv50.txt", 50},
        {"instancia_grafo/pcv177.txt", 177}
    };

    for (auto& instancia : instancias) {
        string arquivo = instancia.first;
        int numVertices = instancia.second;

        cout << "\nCarregando e testando a instância: " << arquivo << " com " << numVertices << " vértices." << endl;
        
        // Criar o grafo de acordo com o número de vértices
        Grafo grafo(numVertices);

        // Carregar o grafo
        grafo.carregarGrafo(arquivo);

        // Exibir representações da instância
        cout << "\nMatriz de Adjacência da instância " << arquivo << ":" << endl;
        grafo.exibirMatrizAdj();

        cout << "\nLista de Adjacência da instância " << arquivo << ":" << endl;
        grafo.exibirListaAdj();

        // Executar BFS e DFS para alguns vértices de teste
        if (numVertices >= 5) {
            cout << "\nBusca em Largura (BFS) do vértice 0 para o vértice 4:" << endl;
            grafo.BFS(0, 4);

            cout << "\nBusca em Profundidade (DFS) a partir do vértice 0:" << endl;
            grafo.DFS(0);
        }
    }

    return 0;
}
