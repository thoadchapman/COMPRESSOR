#ifndef LZ77_H
#define LZ77_H

#include "Bytes.h"
#include <string>

Bytes comprimir_lz77(const Bytes &descomprimido);
std::string comprimir_lz77(const std::string &descomprimido);

Bytes descomprimir_lz77(const Bytes &comprimido);
std::string descomprimir_lz77(const std::string &comprimido);

#endif