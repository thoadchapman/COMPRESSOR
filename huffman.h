#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Bytes.h"
#include <string>

Bytes comprimir(const Bytes &descomprimido);
std::string comprimir(const std::string &descomprimido);

Bytes descomprimir(const Bytes &comprimido);
std::string descomprimir(const std::string &comprimido);
#endif