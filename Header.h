#include "Bytes.h"
#include <unordered_map>
class Header {
private:
  int original_length = 0;
  int num_chars = 0;
  int header_size = 0;
  Bytes freq_bytes;
  Bytes full_header;

public:
  Header() = default;
  Header(int original_length, int num_chars, Bytes freq) {
    this->original_length = original_length;
    this->num_chars = num_chars;
    this->header_size = 8 + (num_chars * 5);
    this->freq_bytes = freq;
    this->full_header = make_full_header();
  }
  Header(const Bytes &comprimido) {
    full_header = comprimido;
    original_length = comprimido.sub(0, 4).to_int();
    num_chars = comprimido.sub(4, 8).to_int();
    header_size = 8 + (num_chars * 5);
    freq_bytes = comprimido.sub(8, header_size);
  }
  std::unordered_map<unsigned char, int> to_freq_dict() {
    std::unordered_map<unsigned char, int> dict;
    for (int i = 8; i < header_size; i += 5) {
      auto c = this->full_header[i];
      int freq = this->full_header.sub(i + (5 - sizeof(int)), i + 5).to_int();
      dict[c] = freq;
    }
    return dict;
  }
  Bytes make_full_header() {
    if (header_size == 0)
      return Bytes();
    auto header_inteira = Bytes();
    header_inteira.insert_int(original_length);
    header_inteira.insert_int(num_chars);
    header_inteira += freq_bytes;
    return header_inteira;
  }
  int get_header_size() { return header_size; }
  int get_original_length() { return original_length; }
  Bytes get_full_header() { return full_header; }
  void set_original_length(int i) { original_length = i; }
  void set_freq_bytes(Bytes b) { freq_bytes = b; }
};