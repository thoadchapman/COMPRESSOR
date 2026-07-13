#pragma once

#include <cstddef>
class Byte {
private:
  unsigned char valor = 0;
  int pos_byte = 0;

public:
  Byte() = default;
  Byte(unsigned char valor) {
    this->valor = valor;
    this->pos_byte = 8;
  }
  Byte &operator+=(const Byte &outro) {
    this->valor = (this->valor << outro.pos_byte) | outro.valor;
    this->pos_byte += outro.pos_byte;
    return *this;
  }
  operator unsigned char() const { return valor; }
  void clear() {
    this->valor = 0;
    this->pos_byte = 0;
  }
  void insert_bit(unsigned char b) {
    this->valor = (this->valor << 1) | (b ? 1 : 0);
    pos_byte++;
  }
  size_t length() const { return pos_byte; }
  void deslocar_esq(int n) { this->valor = this->valor << n; }
  unsigned char get_valor() const { return this->valor; }
  int get_pos() const { return this->pos_byte; }
  void set_pos(int pos) {
    if (pos >= 8)
      return;
    this->pos_byte = pos;
  }
  bool full() const { return pos_byte == 8; }
  void add_padding() { this->deslocar_esq(8 - pos_byte); }
};