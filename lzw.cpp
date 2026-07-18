#include "lzw.h"
#include "Bytes.h"
#include "Utils.h" 
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
  
  const int MAX_DICT_SIZE = 65535;

  for (size_t i = 0; i < descomprimido.length(); i++) {
    char c = static_cast<char>(descomprimido[i].get_valor());
    std::string pc = prefixo + c;

    if (dict.find(pc) != dict.end()) {
      prefixo = pc;
    } else {
      Utils::inserir_codigo_lzw(saida, dict[prefixo]);
      
      if (dictSize < MAX_DICT_SIZE) {
        dict[pc] = dictSize++;
      }
      prefixo = std::string(1, c);
    }
  }

  if (!prefixo.empty()) {
    Utils::inserir_codigo_lzw(saida, dict[prefixo]);
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
  size_t i = 0;
  int cod;
  
  while (Utils::extrair_codigo_lzw(comprimido, i, cod)) {
    codigos.push_back(cod);
  }

  if (codigos.empty()) return Bytes();

  std::unordered_map<int, std::string> dict;
  for (int j = 0; j < 256; j++) {
    dict[j] = std::string(1, static_cast<char>(j));
  }
  
  int dictSize = 256;
  const int MAX_DICT_SIZE = 65535;

  std::string anterior = dict[codigos[0]];
  std::string saida_str = anterior;

  for (size_t k = 1; k < codigos.size(); k++) {
    int p = codigos[k];
    std::string atual;

    if (dict.find(p) != dict.end()) {
      atual = dict[p];
    } else if (p == dictSize) {
      atual = anterior + anterior[0];
    } else {
      break; 
    }

    saida_str += atual;
    
    if (dictSize < MAX_DICT_SIZE) {
      dict[dictSize++] = anterior + atual[0];
    }
    
    anterior = atual;
  }

  return Bytes(saida_str);
}