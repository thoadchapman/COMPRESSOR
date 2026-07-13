#include "huffman.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::string caminhoDados;

std::string comprime(std::string str, int metodo) {
  switch (metodo) {
  case 0:
    return comprimir(str);
  case 1:
    std::cerr << "LZ77 ainda nao implementado\n";
    return "";
  case 2:
    std::cerr << "LZW ainda nao implementado\n";
    return "";
  default:
    std::cerr << "Metodo invalido\n";
    return "";
  }
}
std::string descomprime(std::string str, int metodo) {
  switch (metodo) {
  case 0:
    return descomprimir(str);
  case 1:
    std::cerr << "LZ77 ainda nao implementado\n";
    return "";
  case 2:
    std::cerr << "LZW ainda nao implementado\n";
    return "";
  default:
    std::cerr << "Metodo invalido\n";
    return "";
  }
}
std::string lerArquivo(const std::string &caminho) {
  std::ifstream arquivo(caminho, std::ios::binary);
  std::string conteudo((std::istreambuf_iterator<char>(arquivo)),
                       std::istreambuf_iterator<char>());
  return conteudo;
}
void escreverArquivo(const std::string &caminho, const std::string &conteudo) {
  std::ofstream saida(caminho, std::ios::binary);
  saida.write(conteudo.c_str(), conteudo.size());
}
fs::path caminhoEntradaSpotify() {
  fs::path csv = fs::path(caminhoDados) / "artists.csv";
  if (fs::exists(csv))
    return csv;
  return fs::path();
}
void comprime(int metodo) {
  fs::path entrada = caminhoEntradaSpotify();
  if (entrada.empty()) {
    std::cerr << "spotify.txt ou artists.csv nao encontrado em " << caminhoDados
              << "\n";
    return;
  }
  std::string conteudo = lerArquivo(entrada.string());
  std::string comprimido = comprime(conteudo, metodo);
  fs::path saida = fs::path(caminhoDados) / "spotifyComp.bin";
  escreverArquivo(saida.string(), comprimido);
  std::cout << "Comprimido salvo em " << saida.string() << "\n";
}
void descomprime(int metodo) {
  fs::path entrada = fs::path(caminhoDados) / "spotifyComp.bin";
  if (!fs::exists(entrada)) {
    std::cerr << "spotifyComp.bin nao encontrado em " << caminhoDados << "\n";
    return;
  }
  std::string conteudo = lerArquivo(entrada.string());
  std::string descomprimido = descomprime(conteudo, metodo);
  fs::path saida = fs::path(caminhoDados) / "spotifyDesc.txt";
  escreverArquivo(saida.string(), descomprimido);
  std::cout << "Descomprimido salvo em " << saida.string() << "\n";
}
void exibirMenu() {
  std::cout << "\n=== Compressor de dados Spotify ===\n";
  std::cout << "1 - Comprimir (Huffman)\n";
  std::cout << "2 - Comprimir (LZ77)\n";
  std::cout << "3 - Comprimir (LZW)\n";
  std::cout << "4 - Descomprimir (Huffman)\n";
  std::cout << "5 - Descomprimir (LZ77)\n";
  std::cout << "6 - Descomprimir (LZW)\n";
  std::cout << "0 - Sair\n";
  std::cout << "Escolha: ";
}
void rodarMenu() {
  int opcao = -1;
  while (opcao != 0) {
    exibirMenu();
    std::cin >> opcao;
    switch (opcao) {
    case 1:
      comprime(0);
      break;
    case 2:
      comprime(1);
      break;
    case 3:
      comprime(2);
      break;
    case 4:
      descomprime(0);
      break;
    case 5:
      descomprime(1);
      break;
    case 6:
      descomprime(2);
      break;
    case 0:
      std::cout << "Saindo...\n";
      break;
    default:
      std::cout << "Opcao invalida.\n";
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "sem argumentos o suficiente" << std::endl;
    return 0;
  }
  caminhoDados = argv[1];
  if (caminhoDados.size() >= 2 && caminhoDados.front() == '"' &&
      caminhoDados.back() == '"') {
    caminhoDados = caminhoDados.substr(1, caminhoDados.size() - 2);
  }

  rodarMenu();
  return 0;
}