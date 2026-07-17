#include "lzw.h"
#include "Bytes.h"
#include <unordered_map>
#include <vector>

std::string comprimir_lzw(const std::string &str) {
  Bytes descomprimido = Bytes(str);
  return comprimir_lzw(descomprimido).to_string();
}

Bytes comprimir_lzw(const Bytes &descomprimido) {
  std::unordered_map<std::string, int> dict;
  for (int i = 0; i < 256; i++) {
    dict[std::string(1, static_cast<char>(i))] = i;
  }

  std::string prefixo = "";
  Bytes saida;
  int dictSize = 256;

  for (size_t i = 0; i < descomprimido.length(); i++) {
    char c = static_cast<char>(descomprimido[i].get_valor());
    std::string pc = prefixo + c;

    if (dict.find(pc) != dict.end()) {
      prefixo = pc;
    } else {
      saida.insert_int(dict[prefixo]);
      dict[pc] = dictSize++;
      prefixo = std::string(1, c);
    }
  }

  if (!prefixo.empty()) {
    saida.insert_int(dict[prefixo]);
  }

  return saida;
}

std::string descomprimir_lzw(const std::string &str) {
  Bytes comprimido = Bytes(str);
  return descomprimir_lzw(comprimido).to_string();
}

Bytes descomprimir_lzw(const Bytes &comprimido) {
  if (comprimido.length() == 0) return Bytes();

  std::vector<int> codigos;
  for (size_t i = 0; i < comprimido.length(); i += sizeof(int)) {
    codigos.push_back(comprimido.sub(i, i + sizeof(int)).to_int());
  }

  std::unordered_map<int, std::string> dict;
  for (int i = 0; i < 256; i++) {
    dict[i] = std::string(1, static_cast<char>(i));
  }
  int dictSize = 256;

  std::string anterior = dict[codigos[0]];
  std::string saida_str = anterior;

  for (size_t i = 1; i < codigos.size(); i++) {
    int p = codigos[i];
    std::string atual;

    if (dict.find(p) != dict.end()) {
      atual = dict[p];
    } else if (p == dictSize) {
      atual = anterior + anterior[0];
    }

    saida_str += atual;
    dict[dictSize++] = anterior + atual[0];
    anterior = atual;
  }

  return Bytes(saida_str);
}