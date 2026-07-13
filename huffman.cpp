#include "huffman.h"
#include "Bytes.h"
#include "Minheap.h"
#include "Node.h"
#include <unordered_map>

#define MAX 256
Node *criar_arv_huffman(MinHeap *heap) {
  if (heap->empty() || heap->size() <= 1)
    return nullptr;
  while (heap->size() > 1) {
    Node *no1 = heap->pop();
    Node *no2 = heap->pop();
    Node *novo = new Node((no1->getFreq() + no2->getFreq()), no1, no2);
    heap->push(novo);
  }
  return heap->pop();
}
void preencher_dict(Node *atual, Byte caminho,
                    std::unordered_map<unsigned char, Byte> &dict) {
  if (atual == nullptr)
    return;
  if (atual->ehFolha()) {
    dict[atual->getChar()] = caminho;
    return;
  }
  Byte caminho_esq = caminho;
  caminho_esq.insert_bit(0);
  preencher_dict(atual->getEsq(), caminho_esq, dict);

  Byte caminho_dir = caminho;
  caminho_dir.insert_bit(1);
  preencher_dict(atual->getDir(), caminho_dir, dict);
}
std::unordered_map<unsigned char, Byte> criarDict(Node *raiz) {
  std::unordered_map<unsigned char, Byte> dict;
  Byte caminho;
  preencher_dict(raiz, caminho, dict);
  return dict;
}
int *criar_array_freq(const Bytes &dados) {
  int *array = new int[MAX]();
  for (size_t i = 0; i < dados.length(); i++) {
    Byte byte = dados[i];
    array[byte.get_valor()]++;
  }
  return array;
}
Bytes codificar(const Bytes &dados,
                std::unordered_map<unsigned char, Byte> &dict) {
  Bytes comp;
  for (unsigned char c : dados) {
    if (dict.find(c) != dict.end())
      comp += dict[c];
  }
  return comp;
}
Bytes decodificar(Bytes comprimido, Node *raiz, size_t qtd_char_original) {
  Bytes decodificada;
  Node *atual = raiz;
  for (size_t i = 0;
       i < comprimido.length() && decodificada.length() < qtd_char_original;
       i++) {
    Byte byte_atual = comprimido[i];
    for (int b = 7; b >= 0 && decodificada.length() < qtd_char_original; b--) {
      unsigned char bit = (byte_atual >> b) & 1;
      atual = bit ? atual->getDir() : atual->getEsq();
      if (atual->ehFolha()) {
        decodificada += Byte(atual->getChar());
        atual = raiz;
      }
    }
  }
  return decodificada;
}
std::string comprimir(const std::string &str) {
  Bytes descomprimido = Bytes(str);
  return comprimir(descomprimido).to_string();
}

Bytes comprimir(const Bytes &descomprimido) {
  int *freq = criar_array_freq(descomprimido);
  MinHeap *heap = new MinHeap(freq);
  Bytes freq_bytes = heap->to_freq_bytes();
  Header header = Header(descomprimido.length(), heap->size(), freq_bytes);
  Node *raiz = criar_arv_huffman(heap);
  auto dict = criarDict(raiz);
  Bytes body = codificar(descomprimido, dict);
  Bytes full_header = header.make_full_header();
  body.add_padding();
  return header.get_full_header() + body;
}
std::string descomprimir(const std::string &str) {
  Bytes comprimido = Bytes(str);
  return descomprimir(comprimido).to_string();
}
Bytes descomprimir(const Bytes &comprimido) {
  Header header(comprimido);
  auto freq_dict = header.to_freq_dict();
  MinHeap *heap = new MinHeap(freq_dict);
  Node *raiz = criar_arv_huffman(heap);
  Bytes body = comprimido.sub(header.get_header_size(), comprimido.length());
  Bytes decodificada = decodificar(body, raiz, header.get_original_length());
  return decodificada;
}
