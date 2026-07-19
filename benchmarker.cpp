#include "Benchmarker.h"
#include "huffman.h"
#include "lz77.h"
#include "lzw.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

extern void sortearRegistros(int n);
extern std::string lerArquivo(const std::string &caminho);
extern int qtdRegistros;
extern std::filesystem::path caminhoEntradaSpotifyComp();

void gerarEstatisticas() {
    int M = 5; 
    std::ofstream arquivoSaida("saida.txt");
    
    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar o arquivo saida.txt\n";
        return;
    }

    arquivoSaida << "=== RELATORIO DE ESTATISTICAS DE COMPRESSAO ===\n\n";

    double somaTaxaHuffman = 0, somaTaxaLZ77 = 0, somaTaxaLZW = 0;
    double somaTempoHuffman = 0, somaTempoLZ77 = 0, somaTempoLZW = 0;

    for (int i = 1; i <= M; i++) {
        std::cout << "\n--- Rodando bateria de testes " << i << " de " << M << " ---\n";
        arquivoSaida << "--- Execucao " << i << " ---\n";


        std::cout << "Sorteando nova amostra de " << qtdRegistros << " registros...\n";
        sortearRegistros(qtdRegistros);
        

        std::string conteudoOriginal = lerArquivo(caminhoEntradaSpotifyComp().string());
        size_t tamanhoOriginal = conteudoOriginal.size();
        
        arquivoSaida << "Tamanho Original da Amostra: " << tamanhoOriginal << " bytes\n";

        // --- HUFFMAN ---
        auto inicio = std::chrono::high_resolution_clock::now();
        std::string compHuffman = comprimir_huffman(conteudoOriginal);
        auto fim = std::chrono::high_resolution_clock::now();
        
        double tempoHuffman = std::chrono::duration<double, std::milli>(fim - inicio).count();
        double taxaHuffman = ((double)compHuffman.size() / tamanhoOriginal) * 100.0;
        
        somaTaxaHuffman += taxaHuffman;
        somaTempoHuffman += tempoHuffman;

        arquivoSaida << "Huffman - Tamanho: " << compHuffman.size() << " bytes | Taxa: " 
                     << std::fixed << std::setprecision(2) << taxaHuffman << "% | Tempo: " 
                     << tempoHuffman << " ms\n";

        // --- LZ77 ---
        inicio = std::chrono::high_resolution_clock::now();
        std::string compLZ77 = comprimir_lz77(conteudoOriginal);
        fim = std::chrono::high_resolution_clock::now();
        
        double tempoLZ77 = std::chrono::duration<double, std::milli>(fim - inicio).count();
        double taxaLZ77 = ((double)compLZ77.size() / tamanhoOriginal) * 100.0;
        
        somaTaxaLZ77 += taxaLZ77;
        somaTempoLZ77 += tempoLZ77;

        arquivoSaida << "LZ77    - Tamanho: " << compLZ77.size() << " bytes | Taxa: " 
                     << std::fixed << std::setprecision(2) << taxaLZ77 << "% | Tempo: " 
                     << tempoLZ77 << " ms\n";

        // --- LZW ---
        inicio = std::chrono::high_resolution_clock::now();
        std::string compLZW = comprimir_lzw(conteudoOriginal);
        fim = std::chrono::high_resolution_clock::now();
        
        double tempoLZW = std::chrono::duration<double, std::milli>(fim - inicio).count();
        double taxaLZW = ((double)compLZW.size() / tamanhoOriginal) * 100.0;
        
        somaTaxaLZW += taxaLZW;
        somaTempoLZW += tempoLZW;

        arquivoSaida << "LZW     - Tamanho: " << compLZW.size() << " bytes | Taxa: " 
                     << std::fixed << std::setprecision(2) << taxaLZW << "% | Tempo: " 
                     << tempoLZW << " ms\n\n";
    }

    arquivoSaida << "=== MEDIAS FINAIS (M = " << M << ") ===\n";
    arquivoSaida << "HUFFMAN -> Taxa Media: " << std::fixed << std::setprecision(2) << (somaTaxaHuffman / M) 
                 << "% | Tempo Medio: " << (somaTempoHuffman / M) << " ms\n";
    arquivoSaida << "LZ77    -> Taxa Media: " << std::fixed << std::setprecision(2) << (somaTaxaLZ77 / M) 
                 << "% | Tempo Medio: " << (somaTempoLZ77 / M) << " ms\n";
    arquivoSaida << "LZW     -> Taxa Media: " << std::fixed << std::setprecision(2) << (somaTaxaLZW / M) 
                 << "% | Tempo Medio: " << (somaTempoLZW / M) << " ms\n";

    arquivoSaida.close();
    std::cout << "\n[Sucesso] Estatisticas geradas e salvas no arquivo 'saida.txt'!\n";
}