#pragma once
#include "Bytes.h"

namespace Utils{
    inline void inserir_tripla(Bytes &saida, int p, int l, unsigned char c) {

        saida.append(Byte((p >> 8) & 0xFF));
        saida.append(Byte(p & 0xFF));
        saida.append(Byte(l & 0xFF));
        saida.append(Byte(c));
    }


    inline bool extrair_tripla(const Bytes &comprimido, size_t &i, int &p, int &l, unsigned char &c) {
        if (i + 4 > comprimido.length()) {
            return false;
        }
        

        p = (comprimido[i].get_valor() << 8) | comprimido[i + 1].get_valor();
        l = comprimido[i + 2].get_valor();
        c = comprimido[i + 3].get_valor();

        i += 4; 
        return true;
    }
}