#ifndef NODE_HPP
#define NODE_HPP

class Node {
    private:
        int freq;
        char c;
        Node* esq;
        Node* dir;        
    public:
        Node(int freq, char c);
        Node(int freq, Node* esq, Node* dir);
        bool operator<(const Node& outro) const;
        int getFreq() const;
        char getChar() const;
        Node* getEsq() const;
        Node* getDir() const;
        void setFreq(int freq);
        void setChar(char c);
        void setEsq(Node* esq);
        void setDir(Node* dir);
        bool ehFolha();
};

#endif