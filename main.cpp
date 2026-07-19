#include "huffman.h"
#include "lzw.h"
#include "lz77.h"
#include "Benchmarker.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

namespace fs = std::filesystem;
std::string caminhoDados;
int qtdRegistros = 0;

fs::path caminhoEntradaSpotify();
void escreverArquivo(const std::string &caminho, const std::string &conteudo);

void sortearRegistros(int n) {
  fs::path entrada = caminhoEntradaSpotify();
  if (entrada.empty()) {
    std::cerr << "artists.csv nao encontrado em " << caminhoDados << "\n";
    return;
  }

  std::ifstream arquivo(entrada.string());
  std::vector<std::string> linhas;
  std::string linha;
  while (std::getline(arquivo, linha)) {
    linhas.push_back(linha);
  }
  arquivo.close();

  if (linhas.empty()) {
    std::cerr << "Arquivo de entrada vazio.\n";
    return;
  }

  std::string cabecalho = linhas.front();
  std::vector<std::string> registros(linhas.begin() + 1, linhas.end());

  if ((size_t)n > registros.size()) {
    std::cerr << "N (" << n << ") maior que a quantidade de registros disponiveis ("
               << registros.size() << "). Usando todos os registros.\n";
    n = (int)registros.size();
  }

  std::vector<std::string> amostra;
  amostra.reserve(n);
  std::random_device rd;
  std::mt19937 gerador(rd());
  std::sample(registros.begin(), registros.end(), std::back_inserter(amostra),
              n, gerador);

  std::string conteudo = cabecalho + "\n";
  for (const auto &l : amostra) {
    conteudo += l + "\n";
  }

  fs::path saida = fs::path(caminhoDados) / "spotifyAmostra.csv";
  escreverArquivo(saida.string(), conteudo);
  std::cout << "Amostra de " << n << " registros salva em " << saida.string()
             << "\n";
}





std::string comprime(std::string str, int metodo) {
  switch (metodo) {
  case 0:
    return comprimir_huffman(str);
  case 1:
    return comprimir_lz77(str);
  case 2:
    return comprimir_lzw(str);
  default:
    std::cerr << "Metodo invalido\n";
    return "";
  }
}
std::string descomprime(std::string str, int metodo) {
  switch (metodo) {
  case 0:
    return descomprimir_huffman(str);
  case 1:
    return descomprimir_lz77(str);
  case 2:
    return descomprimir_lzw(str);
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
  fs::path csv = fs::path(caminhoDados) / "songs.csv";
  if (fs::exists(csv))
    return csv;
  return fs::path();
}

fs::path caminhoEntradaSpotifyComp() {
  fs::path csv = fs::path(caminhoDados) / "spotifyAmostra.csv";
  if (fs::exists(csv))
    return csv;
  return fs::path();
}

void comprime(int metodo) {
  fs::path entrada = caminhoEntradaSpotifyComp();
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
  std::cout << "7 - Gerar Estatisticas de Desempenho\n";
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
    case 7: 
      if (qtdRegistros == 0) {
        std::cerr << "Por favor, inicie o programa passando a quantidade de registros no terminal!\n";
      } else {
        gerarEstatisticas(); 
      }
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

   if (argc >= 3) {
    qtdRegistros = std::stoi(argv[2]);
    sortearRegistros(qtdRegistros);
  }

  rodarMenu();
  return 0;
}