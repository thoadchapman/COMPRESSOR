#pragma once
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "Byte.h"

class Bytes {
private:
  std::vector<Byte> vetor;
  Byte last_byte;

public:
  Bytes() = default;
  Bytes(std::vector<Byte> vetor) { this->vetor = vetor; }
  Bytes(const std::string &str) {
    vetor.insert(vetor.end(), str.begin(), str.end());
  }
  auto begin() const { return this->vetor.begin(); }
  auto end() const { return this->vetor.end(); }
  Bytes operator+(const Bytes &outro) const {
    Bytes resultado;
    resultado.vetor = this->vetor;
    resultado.vetor.insert(resultado.vetor.end(), outro.vetor.begin(),
                           outro.vetor.end());
    return resultado;
  }
  Bytes &operator+=(const Byte &outro) {
    if (last_byte.get_pos() + outro.get_pos() < 8) {
      last_byte += outro;
      return *this;
    }
    unsigned char valor = outro.get_valor();
    for (int i = outro.length() - 1; i >= 0; i--)
      this->insert_bit((valor >> i) & 1);
    return *this;
  }

  Bytes &operator+=(const Bytes &outro) {
    this->vetor.insert(this->vetor.end(), outro.begin(), outro.end());
    return *this;
  }
  Byte &operator[](size_t index) {
    if (index >= vetor.size()) {
      throw std::out_of_range("Índice inválido: " + std::to_string(index));
    }
    return vetor[index];
  }
  const Byte &operator[](size_t index) const {
    if (index >= vetor.size()) {
      throw std::out_of_range("Índice inválido: " + std::to_string(index));
    }
    return vetor[index];
  }
  size_t length() const { return this->vetor.size(); }
  void clear() { this->vetor.clear(); }

  Bytes sub(size_t inicio, size_t fim) const {
    return Bytes(std::vector<Byte>(this->vetor.begin() + inicio,
                                   this->vetor.begin() + fim));
  }
  void add_padding() {
    this->last_byte.add_padding();
    vetor.push_back(last_byte);
    last_byte.clear();
  }
  std::string to_string() const {
    return std::string(this->vetor.begin(), this->vetor.end());
  }
  std::vector<unsigned char> valores() const {
    std::vector<unsigned char> v;
    v.reserve(this->vetor.size());
    for (const auto &a : this->vetor)
      v.push_back(a.get_valor());
    return v;
  }
  int to_int() {
    int i = 0;
    auto v = this->valores();
    if (v.size() >= sizeof(int)) {
      std::memcpy(&i, &v[0], sizeof(int));
    }
    return i;
  }
  void insert_int(int v) {
    const unsigned char *bytes_inicio =
        reinterpret_cast<const unsigned char *>(&v);

    const unsigned char *bytes_fim = bytes_inicio + sizeof(int);

    this->vetor.insert(this->vetor.end(), bytes_inicio, bytes_fim);
  }
  void append(const Byte b) { this->vetor.push_back(b); }
  void dump() {
    this->append(last_byte);
    this->last_byte.clear();
  }
  void insert_bit(unsigned char b) {
    this->last_byte.insert_bit(b);
    if (this->last_byte.full()) {
      this->dump();
    }
  }
};