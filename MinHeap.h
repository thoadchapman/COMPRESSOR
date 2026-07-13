#pragma once
#include "Bytes.h"
#include "Header.h"
#include "Node.h"
#include <queue>
#include <unordered_map>

#define MAX 256

class MinHeap {
private:
  struct ComparadorNode {
    bool operator()(Node *a, Node *b) const { return *a > *b; }
  };

  std::priority_queue<Node *, std::vector<Node *>, ComparadorNode> heap;

public:
  MinHeap() = default;
  MinHeap(int *freq_array) {
    for (int i = 0; i < MAX; i++) {
      if (freq_array[i] <= 0)
        continue;
      heap.push(new Node(i, freq_array[i]));
    }
  };
  MinHeap(const MinHeap &outro) { this->heap = outro.heap; }
  MinHeap(std::unordered_map<unsigned char, int> &dict) {
    for (int i = 0; i < MAX; i++) {
      auto it = dict.find((unsigned char)i);
      if (it != dict.end())
        heap.push(new Node((unsigned char)i, it->second));
    }
  }
  void push(Node *n) { heap.push(n); }
  size_t size() const { return heap.size(); }

  Node *pop() {
    Node *n = heap.top();
    heap.pop();
    return n;
  }

  bool empty() const { return heap.empty(); }
  Bytes to_freq_bytes() {
    Bytes freq_bytes;
    MinHeap copia = *this;
    while (!copia.empty()) {
      Node *node = copia.pop();
      Byte b = Byte(node->getChar());
      freq_bytes.append(b);
      freq_bytes.insert_int(node->getFreq());
    }
    return freq_bytes;
  }
};