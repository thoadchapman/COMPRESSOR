#ifndef LZW_H
#define LZW_H

#include "Bytes.h"
#include <string>

Bytes comprimir_lzw(const Bytes &descomprimido);
std::string comprimir_lzw(const std::string &descomprimido);

Bytes descomprimir_lzw(const Bytes &comprimido);
std::string descomprimir_lzw(const std::string &comprimido);

#endif