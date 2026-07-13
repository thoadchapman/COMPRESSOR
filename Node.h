#ifndef NODE_HPP
#define NODE_HPP

class Node {
private:
  int freq;
  unsigned char c;
  Node *esq;
  Node *dir;

public:
  Node(unsigned char c, int freq) {
    this->c = c;
    this->freq = freq;
    this->esq = nullptr;
    this->dir = nullptr;
  }

  Node(int freq, Node *esq, Node *dir) {
    this->freq = freq;
    this->c = 0;
    this->esq = esq;
    this->dir = dir;
  }

  bool operator<(const Node &outro) const {
    if (this->freq != outro.getFreq()) {
      return this->freq < outro.getFreq();
    }
    return this->c < outro.getChar();
  }

  bool operator>(const Node &outro) const {
    if (this->freq != outro.getFreq()) {
      return this->freq > outro.getFreq();
    }
    return this->c > outro.getChar();
  }

  int getFreq() const { return freq; }
  unsigned char getChar() const { return c; }
  Node *getEsq() const { return esq; }
  Node *getDir() const { return dir; }

  void setFreq(int freq) { this->freq = freq; }
  void setChar(unsigned char c) { this->c = c; }
  void setEsq(Node *esq) { this->esq = esq; }
  void setDir(Node *dir) { this->dir = dir; }

  bool ehFolha() { return (this->esq == nullptr && this->dir == nullptr); }
};

#endif