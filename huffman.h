#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Bytes.h"
#include <string>

Bytes comprimir_huffman(const Bytes &descomprimido);
std::string comprimir_huffman(const std::string &descomprimido);

Bytes descomprimir_huffman(const Bytes &comprimido);
std::string descomprimir_huffman(const std::string &comprimido);
#endif