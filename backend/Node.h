#ifndef NODE_HPP
#define NODE_HPP

class Node {
private:
  int freq;
  unsigned char c;
  Node *esq;
  Node *dir;

public:
  Node(int freq, unsigned char c);
  Node(int freq, Node *esq, Node *dir);
  bool operator<(const Node &outro) const;
  int getFreq() const;
  unsigned char getChar() const;
  Node *getEsq() const;
  Node *getDir() const;
  void setFreq(int freq);
  void setChar(unsigned char c);
  void setEsq(Node *esq);
  void setDir(Node *dir);
  bool ehFolha();
};

#endif