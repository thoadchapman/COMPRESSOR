#include "huffman.h"
#include "Node.h"
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#define MAX 256
#define SEPARADOR_PRIMARIO "|"
#define SEPARADOR_SECUNDARIO ","
#define SEPARADOR_TERCIARIO ":"

struct Comparador {
  bool operator()(Node *esq, Node *dir) {
    if (esq->getFreq() != dir->getFreq())
      return esq->getFreq() > dir->getFreq();
    return esq->getChar() > dir->getChar();
  }
};
void preencherDict(Node *atual, std::string caminho,
                   std::unordered_map<char, std::string> &dict) {
  if (atual == nullptr)
    return;
  if (atual->ehFolha()) {
    dict[atual->getChar()] = caminho;
    return;
  }
  preencherDict(atual->getEsq(), caminho + "0", dict);
  preencherDict(atual->getDir(), caminho + "1", dict);
}
std::unordered_map<char, std::string> criarDict(Node *raiz) {
  std::unordered_map<char, std::string> dict;
  preencherDict(raiz, "", dict);
  return dict;
}
void inserirNaHeap(
    std::string buffer,
    std::priority_queue<Node *, std::vector<Node *>, Comparador> &heap) {
  int idx_terciario = buffer.find(SEPARADOR_TERCIARIO[0]);
  char c = buffer.substr(0, idx_terciario)[0];
  int freq = std::stoi(buffer.substr(idx_terciario + 1));
  heap.push(new Node(freq, c));
}
std::priority_queue<Node *, std::vector<Node *>, Comparador>
headerToHeap(std::string header) {
  std::string buffer = "";
  std::priority_queue<Node *, std::vector<Node *>, Comparador> heap;
  for (int i = 0; i < header.length(); i++) {
    if (header[i] == SEPARADOR_SECUNDARIO[0]) {
      inserirNaHeap(buffer, heap);
      buffer = "";
      continue;
    }
    buffer += header[i];
  }
  inserirNaHeap(buffer, heap);
  return heap;
}
int *criarArrayFreq(std::string str) {
  int *array = new int[MAX]();
  for (char c : str) {
    array[c]++;
  }
  return array;
}
std::priority_queue<Node *, std::vector<Node *>, Comparador>
criarHeap(int *array) {
  std::priority_queue<Node *, std::vector<Node *>, Comparador> heap;
  for (int i = 0; i < MAX; i++) {
    if (array[i] <= 0)
      continue;
    Node *novo = new Node(array[i], (char)i);
    heap.push(novo);
  }
  return heap;
}

Node *criarArvHuffman(
    int len,
    std::priority_queue<Node *, std::vector<Node *>, Comparador> heap) {
  while (heap.size() > 1) {
    Node *no1 = heap.top();
    heap.pop();
    Node *no2 = heap.top();
    heap.pop();
    Node *novo = new Node((no1->getFreq() + no2->getFreq()), no1, no2);
    heap.push(novo);
  }
  return heap.top();
}
std::string criarComp(std::string str,
                      std::unordered_map<char, std::string> dict) {
  std::string comp = "";
  for (char c : str) {
    if (dict.find(c) != dict.end())
      comp += dict[c];
  }
  return comp;
}
std::string decodificarComp(std::string str, Node *raiz) {
  std::string decomp = "";
  std::string caminho = "";
  Node *atual = raiz;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '0')
      atual = atual->getEsq();
    else if (str[i] == '1')
      atual = atual->getDir();
    caminho += str[i];
    if (atual->getChar() != '\0') {
      decomp += atual->getChar();
      caminho = "";
      atual = raiz;
      continue;
    }
  }
  return decomp;
}
std::string
criarHeader(std::priority_queue<Node *, std::vector<Node *>, Comparador> heap) {
  std::string header = "";
  while (!heap.empty()) {
    Node *node = heap.top();
    heap.pop();
    header += std::string(1, node->getChar()) + SEPARADOR_TERCIARIO +
              std::to_string(node->getFreq());
    if (heap.size() >= 1) {
      header += SEPARADOR_SECUNDARIO;
    }
  }
  header += SEPARADOR_PRIMARIO;
  return header;
}
std::string comprimir(std::string str) {
  int *freq = criarArrayFreq(str);
  std::priority_queue<Node *, std::vector<Node *>, Comparador> heap =
      criarHeap(freq);
  std::priority_queue<Node *, std::vector<Node *>, Comparador> copia = heap;
  std::string header = criarHeader(copia);
  Node *raiz = criarArvHuffman(str.length(), heap);
  std::unordered_map<char, std::string> dict = criarDict(raiz);
  std::string comprimida = criarComp(str, dict);
  return header + comprimida;
}
std::string descomprimir(std::string comprimida) {
  int separador_idx = comprimida.find(SEPARADOR_PRIMARIO);
  std::string header = comprimida.substr(0, separador_idx);
  std::string bits =
      comprimida.substr(separador_idx + 1, comprimida.length() - 1);
  std::priority_queue<Node *, std::vector<Node *>, Comparador> heap =
      headerToHeap(header);
  Node *raiz = criarArvHuffman(bits.length(), heap);
  return decodificarComp(bits, raiz);
}