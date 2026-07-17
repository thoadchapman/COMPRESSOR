#include "lz77.h"
#include "Bytes.h"
#include <algorithm>

const int Nd = 4096; 
const int Nb = 255;  

std::string comprimir_lz77(const std::string &str) {
  Bytes descomprimido = Bytes(str);
  return comprimir_lz77(descomprimido).to_string();
}

Bytes comprimir_lz77(const Bytes &descomprimido) {
  Bytes saida;
  int n = descomprimido.length();

  for (int cursor = 0; cursor < n; ) {
    int best_p = 0;
    int best_l = 0;
    unsigned char next_c = descomprimido[cursor].get_valor();

    int dict_start = std::max(0, cursor - Nd);

    for (int p_idx = dict_start; p_idx < cursor; ++p_idx) {
      int l = 0;
      while (l < Nb && cursor + l < n &&
             descomprimido[p_idx + l].get_valor() == descomprimido[cursor + l].get_valor()) {
        l++;
      }
      if (l > best_l) {
        best_l = l;
        best_p = cursor - p_idx;
        
        if (cursor + l < n) {
          next_c = descomprimido[cursor + l].get_valor();
        } else {
          next_c = 0; 
        }
      }
    }

    saida.insert_int(best_p);
    saida.insert_int(best_l);
    saida.append(Byte(next_c));

    cursor += best_l + 1;
  }
  return saida;
}

std::string descomprimir_lz77(const std::string &str) {
  Bytes comprimido = Bytes(str);
  return descomprimir_lz77(comprimido).to_string();
}

Bytes descomprimir_lz77(const Bytes &comprimido) {
  Bytes saida;
  size_t i = 0;
  int size = comprimido.length();

  while (i < size) {
    if (i + sizeof(int) * 2 + 1 > size) break;

    int p = comprimido.sub(i, i + sizeof(int)).to_int();
    i += sizeof(int);
    
    int l = comprimido.sub(i, i + sizeof(int)).to_int();
    i += sizeof(int);
    
    unsigned char c = comprimido[i].get_valor();
    i++;

    if (l > 0) {
      int start = saida.length() - p;
      for (int j = 0; j < l; ++j) {
        saida.append(saida[start + j]);
      }
    }

    if (c != 0 || i < size) {
      saida.append(Byte(c));
    }
  }
  return saida;
}