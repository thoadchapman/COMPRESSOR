#include "Node.h"

Node::Node(int freq, unsigned char c) {
  this->freq = freq;
  this->c = c;
  this->esq = nullptr;
  this->dir = nullptr;
}

Node::Node(int freq, Node *esq, Node *dir) {
  this->freq = freq;
  this->c = 0;
  this->esq = esq;
  this->dir = dir;
}

bool Node::operator<(const Node &outro) const {
  return this->freq > outro.getFreq();
}

int Node::getFreq() const { return freq; }

unsigned char Node::getChar() const { return c; }

Node *Node::getEsq() const { return esq; }

Node *Node::getDir() const { return dir; }

void Node::setFreq(int freq) { this->freq = freq; }

void Node::setChar(unsigned char c) { this->c = c; }

void Node::setEsq(Node *esq) { this->esq = esq; }

void Node::setDir(Node *dir) { this->dir = dir; }

bool Node::ehFolha() { return (this->esq == nullptr && this->dir == nullptr); }