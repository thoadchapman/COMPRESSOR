#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "Node.h"
#include "Node.cpp"
#define MAX 256

void preencherDict(Node* atual, std::string caminho, std::unordered_map<char,std::string>& dict){
    if (atual == nullptr)
        return;
    if (atual->ehFolha()) {
        dict[atual->getChar()] = caminho;
        return;
    }
    preencherDict(atual->getEsq(), caminho + "0", dict);
    preencherDict(atual->getDir(), caminho + "1", dict);
}
std::unordered_map<char, std::string> criarDict(Node* raiz){
    std::unordered_map<char,std::string> dict;
    preencherDict(raiz,"",dict);
    return dict;
}
int* criarArrayFreq(std::string str){
    int* array = new int[MAX]();
    for(char c : str) { 
        array[c]++;
    }
    return array;
}
std::priority_queue<Node*> criarHeap(int* array){
    std::priority_queue<Node*> heap;
    for (int i = 0; i < MAX; i++){
        if (array[i] <= 0) continue;
            Node* novo = new Node(array[i], (char) i);
            heap.push(novo);
        }
    return heap;
}
Node* criarArvHuffman(int len, std::priority_queue<Node*> heap){
    Node* atual = heap.top();;
    while (atual->getFreq() < len){
        Node* no1 = heap.top();
        heap.pop();
        Node* no2 = heap.top();
        heap.pop();
        Node* novo = new Node((no1->getFreq() + no2->getFreq()), no1, no2);
        heap.push(novo);
        atual = novo;
    }
    return atual;
}
std::string criarComp(std::string str, std::unordered_map<char, std::string> dict){
    std::string comp = "";
    for (char c : str){
        if (dict.contains(c)){
            comp += dict[c];
        }
    }
    return comp;
}


// TRATAMENTO DE ERRO PRA STRING VAZIA
std::string comprimir(std::string str){
    int* freq = criarArrayFreq(str);
    // ok, ele coloca todas as frequencias no array
    // a gente passa de 1 por 1 anotando o caractere e a frequencia dele
    // precisa colocar essas informações no node, e o node na min_heap
    std::priority_queue<Node*> heap = criarHeap(freq);
    // agora que o heap tá cheio, a gente monta a árvore
    // eu imagino que a condição de parada seja tipo:
    //      while no.freq < str.length()
    Node* raiz = criarArvHuffman(str.length(), heap);
    // ok, ai na teoria, depois disso, a árvore ta montada... na teoria
    // agora o que a gente precisa pra produzir a string comprimida...
    // puts, agora fodeu ne
    // pq a gente vai ter que montar o dicionario com o endereço de cada caractere
    // eu vou ter que instanciar a classe pra arvore binaria se pa
    std::unordered_map<char,std::string> dict = criarDict(raiz);
    // mentira, acho que eu consegui achar um jeito de fazer isso sem instanciar a classe
    // agora é criar a string comprimida, usando o dicionario pra ditar o caminho
    // na verdade, vou trocar de map pra unordered_map pra ficar com complexidade O(1)
    return criarComp(str, dict);
}

int main(){
    std::string exemplo1 = "FEEDBACKER";
    std::string exemplo2 = "BORIS";
    std::cout << "/ === TESTES === /" << std::endl;
    std::cout << "STRING 1: " << comprimir(exemplo1) << std::endl;
    return 0;
}