#include "huffman.h"
#include "Node.h"
#include <queue>
#include <string>
#include <unordered_map>

#define MAX 256
#define SEPARADOR_PRIMARIO "|"
#define SEPARADOR_SECUNDARIO ","
#define SEPARADOR_TERCIARIO ":"

void preencherDict(Node *atual, std::string caminho,
                   std::unordered_map<unsigned char, std::string> &dict) {
  if (atual == nullptr)
    return;
  if (atual->ehFolha()) {
    dict[atual->getChar()] = caminho;
    return;
  }
  preencherDict(atual->getEsq(), caminho + "0", dict);
  preencherDict(atual->getDir(), caminho + "1", dict);
}
std::unordered_map<unsigned char, std::string> criarDict(Node *raiz) {
  std::unordered_map<unsigned char, std::string> dict;
  preencherDict(raiz, "", dict);
  return dict;
}
void inserirNaHeap(std::string buffer, std::priority_queue<Node *> &heap) {
  int idx_terciario = buffer.find(SEPARADOR_TERCIARIO[0]);
  unsigned char c = buffer.substr(0, idx_terciario)[0];
  int freq = std::stoi(buffer.substr(idx_terciario + 1));
  heap.push(new Node(freq, c));
}
std::priority_queue<Node *> headerToHeap(std::string header) {
  std::string buffer = "";
  std::priority_queue<Node *> heap;
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
int *criarArrayFreq(const std::string &str) {
  int *array = new int[MAX]();
  for (unsigned char c : str) {
    array[c]++;
  }
  return array;
}
std::priority_queue<Node *> criarHeap(int *array) {
  std::priority_queue<Node *> heap;
  for (int i = 0; i < MAX; i++) {
    if (array[i] <= 0)
      continue;
    Node *novo = new Node(array[i], (unsigned char)i);
    heap.push(novo);
  }
  return heap;
}

Node *criarArvHuffman(int len, std::priority_queue<Node *> heap) {
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
std::string criarComp(const std::string &str,
                      std::unordered_map<unsigned char, std::string> &dict) {
  std::string comp = "";
  for (unsigned char c : str) {
    if (dict.find(c) != dict.end())
      comp += dict[c];
  }
  return comp;
}
std::string decodificarComp(const std::string &str, Node *raiz) {
  std::string decomp = "";
  std::string caminho = "";
  Node *atual = raiz;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '0')
      atual = atual->getEsq();
    else if (str[i] == '1')
      atual = atual->getDir();
    caminho += str[i];
    if (atual->getChar()) {
      decomp += atual->getChar();
      caminho = "";
      atual = raiz;
      continue;
    }
  }
  return decomp;
}
std::string criarHeader(std::priority_queue<Node *> heap) {
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
std::string comprimir(const std::string &descomprimida) {
  int *freq = criarArrayFreq(descomprimida);
  std::priority_queue<Node *> heap = criarHeap(freq);
  std::priority_queue<Node *> copia = heap;
  std::string header = criarHeader(copia);
  Node *raiz = criarArvHuffman(descomprimida.length(), heap);
  std::unordered_map<unsigned char, std::string> dict = criarDict(raiz);
  std::string comprimida = criarComp(descomprimida, dict);
  return header + comprimida;
}
std::string descomprimir(const std::string &comprimida) {
  int separador_idx = comprimida.find(SEPARADOR_PRIMARIO);
  std::string header = comprimida.substr(0, separador_idx);
  std::string bits =
      comprimida.substr(separador_idx + 1, comprimida.length() - 1);
  std::priority_queue<Node *> heap = headerToHeap(header);
  Node *raiz = criarArvHuffman(bits.length(), heap);
  return decodificarComp(bits, raiz);
}