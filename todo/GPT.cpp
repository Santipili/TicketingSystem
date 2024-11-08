#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include "../include/entidades.h"
#include "../include/database.h"

using namespace std;

#define Node pair< string, int > 
#define INF 1<<30  
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};

priority_queue< Node , vector<Node> , cmp > Q; 
map<string, int> distancia;     
map< string , int> visitado;      
map< string , string> previo;         
std::map< std::pair<std::string, std::string>, int > matrizPesos;
list<Cliente> clientes;

void init(){

    for (const auto& item : matrizPesos) {
        const std::pair<std::string, std::string>& key = item.first;
        int _peso = item.second;

        if (!distancia [key.first] && !visitado[ key.first ] ){
            distancia[ key.first ] = INF;     
            visitado[ key.first ] = false; 
            previo[ key.first  ] = "";   
        } 
    }
}

void relajacion( string actual , string adyacente , int peso ){

    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

void dijkstra( string inicial ){
    init();
    Q.push( { inicial , 0 } ); 
    distancia[ inicial ] = 0;      
    int  peso;
    string actual , adyacente;
    while( !Q.empty() ){                   
        actual = Q.top().first;             
        Q.pop();                           
        if( visitado[ actual ] ) continue; 
        visitado[ actual ] = true;  
        
        for (const auto& item : matrizPesos) {
            const std::pair<std::string, std::string>& key = item.first;
            int _peso = item.second;
            
            if (key.first == actual) {
                adyacente = key.second;   
                peso = _peso;  
                if( !visitado[ adyacente ] ){   
                    relajacion( actual , adyacente , peso );        
                }
            }      
        }
    }

        printf( "Distancias mas cortas iniciando en vertice " , inicial );

        vector<pair<string, int>> caminos;
        
        for (const auto& item : distancia) {
            const std::string& key = item.first;
            int _peso = item.second;
            caminos.push_back({key, _peso});
        }
        sort(caminos.begin(), caminos.end(),
                [](const auto& a, const auto& b) {
                    return a.second < b.second; 
                });
        for (const auto& item : caminos) {
            cout << "Vertice: " << item.first << ", Distancia mas corta: " << item.second << endl;
        }

        // puts("\n**************Impresion de camino mas corto**************");
        // printf("Ingrese vertice destino: ");
        // int destino;
        // scanf("%d" , &destino );
        // print( destino );
        // printf("\n");
   
}

int calcularPeso(const std::string& str1, const std::string& str2) {
    cout << "Calcular Peso" << endl;
    int peso = 0;
    for (size_t i = 0; i < str1.size() && i < str2.size(); ++i) {
        peso += std::abs(str1[i] - str2[i]);
    }
    return peso;
}

int main() {
    clientes.push_back(PoolClientes::cliente1);
    clientes.push_back(PoolClientes::cliente2);
    clientes.push_back(PoolClientes::cliente3);

    for (auto it = clientes.begin(); it != clientes.end(); ++it) {
        cout <<"Entre al primer for"    << endl;
        for (auto it2 = next(it); it2 != clientes.end(); ++it2){
            int peso = calcularPeso(it->direccion, it2->direccion);
            matrizPesos[{it->direccion, it2->direccion}] = peso;
            matrizPesos[{it2->direccion, it->direccion}] = peso; 
        }

        matrizPesos[{it->direccion, it->direccion}] = 0;
    }

    // Nuestra Matriz de Adyacencia
    for (const auto& Nodo : matrizPesos) {
        std::cout << "Peso de " << Nodo.first.first << " a " << Nodo.first.second << " es " << Nodo.second << std::endl;
    }
    

    // cout <<" ingrese la direccion inicial: " << endl;
    // getline(cin, direccion);
    dijkstra( PoolClientes::cliente1.direccion );


    return 0;
}
