# 🎵📦 Compressor — Huffman, LZ77 & LZW

> Trabalho Prático de **DCC012 – Estruturas de Dados II** (UFJF), aplicado à base de dados [550K Spotify Songs: Audio, Lyrics & Genres](https://www.kaggle.com/datasets/serkantysz/550k-spotify-songs-audio-lyrics-and-genres/data) 🎧✨

Um compressorzinho de dados feito do zero em **C++17**, sem bibliotecas externas, que implementa três algoritmos clássicos de compressão sem perdas e compara o desempenho de cada um deles. Bora comprimir umas músicas? 🚀

---

## 💡 O que esse projeto faz?

O programa lê registros de músicas (letras, gêneros, metadados) de um dataset em CSV, sorteia uma amostra aleatória de `N` registros, concatena tudo em uma única cadeia de texto e comprime essa cadeia usando três algoritmos diferentes:

| Algoritmo | Ideia central | Arquivo |
|---|---|---|
| 🌳 **Huffman** | Códigos de tamanho variável baseados na frequência de cada caractere | `huffman.cpp` / `huffman.h` |
| 🪟 **LZ77** | Janela deslizante que substitui trechos repetidos por referências (offset, tamanho, próximo caractere) | `lz77.cpp` / `lz77.h` |
| 📖 **LZW** | Dicionário dinâmico que aprende e reutiliza sequências já vistas | `lzw.cpp` / `lzw.h` |

Além disso, o projeto conta com um **benchmarker** 📊 que roda múltiplas compressões e gera estatísticas (taxa de compressão e tempo de execução) automaticamente.

---

## 📁 Estrutura do projeto

```
COMPRESSOR/
├── main.cpp            # Menu principal e ponto de entrada (função main)
├── huffman.cpp / .h     # Algoritmo de Huffman
├── lz77.cpp / .h         # Algoritmo LZ77
├── lzw.cpp / .h           # Algoritmo LZW
├── benchmarker.cpp        # Geração de estatísticas de desempenho
├── Benchmarker.h
├── Header.h              # Cabeçalho dos arquivos comprimidos (Huffman)
├── Node.h                # Nó da árvore de Huffman
├── MinHeap.h             # Heap de mínimo usado na construção da árvore
├── Utils.h               # Serialização de tríplices (LZ77) e códigos (LZW)
├── Byte.h                # Representação de um byte, bit a bit
├── Bytes.h               # Contêiner de bytes (sequência de Byte)
├── Makefile               # Script de compilação (Linux/Windows com MinGW)
└── README.md               # Esse arquivo aqui 👋
```

---

## ⚙️ Requisitos

- Compilador **C++17** (recomendado: `g++`, versão 9+)
- **Nenhuma** biblioteca externa é necessária — é tudo feito na unha 💪
- Um diretório com os arquivos de dados (`songs.csv`, baixado do Kaggle — **não incluído no repositório**, veja a seção [📚 Sobre o dataset](#-sobre-o-dataset))

---

## 🛠️ Como compilar

Você pode compilar de **três jeitinhos diferentes** — escolha o que preferir:

### 1️⃣ Compilando na mão (um comando só)

Direto no terminal, sem Makefile:

```bash
g++ -std=c++17 main.cpp huffman.cpp lzw.cpp lz77.cpp benchmarker.cpp -o main.exe
```

Isso gera o executável `main.exe` (funciona tanto no Linux quanto no Windows, apesar do nome 😄).

### 2️⃣ Usando `make` (Linux / macOS)

Se você tem o `make` instalado, é só rodar:

```bash
make
```

Isso vai compilar tudo automaticamente seguindo as regras do `Makefile`, gerando o executável `main`. Para limpar os arquivos objeto (`.o`) e o executável gerado:

```bash
make clean
```

### 3️⃣ Usando `mingw32-make` (Windows)

No Windows, com o [MinGW-w64](https://www.mingw-w64.org/) instalado (ex: via [MSYS2](https://www.msys2.org/)), use:

```bash
mingw32-make
```

E, para limpar:

```bash
mingw32-make clean
```

> 💡 **Dica:** se estiver usando o MSYS2/UCRT64, lembre de rodar os comandos dentro do terminal certo (ex: `MSYS2 UCRT64`), senão o `g++` pode não ser encontrado.

---

## ▶️ Como rodar

O programa recebe o caminho da pasta com os arquivos de dados como argumento na linha de comando. Opcionalmente, também é possível passar a quantidade `N` de registros a serem sorteados:

```bash
./main /caminho/para/pasta/com/dados        # só carrega e abre o menu
./main /caminho/para/pasta/com/dados 500    # sorteia 500 registros aleatórios
```

No Windows (se compilou com o comando manual):

```bash
main.exe C:\caminho\para\dados 500
```

### 📋 O que acontece na primeira execução?

Se a pasta ainda não tiver o arquivo `songs.bin`, o programa faz o **pré-processamento** automaticamente (Etapa 0), convertendo `songs.csv` para um formato binário mais rápido de ler. Isso só acontece uma vez! ✨

### 🧭 Menu interativo

Depois de carregado, o programa mostra um menu assim:

```
=== Compressor de dados Spotify ===
1 - Comprimir (Huffman)
2 - Comprimir (LZ77)
3 - Comprimir (LZW)
4 - Descomprimir (Huffman)
5 - Descomprimir (LZ77)
6 - Descomprimir (LZW)
7 - Gerar Estatisticas de Desempenho
0 - Sair
Escolha:
```

| Opção | O que faz |
|---|---|
| `1`–`3` | Comprime `spotify.csv` com o método escolhido → gera `spotifyComp.bin` |
| `4`–`6` | Descomprime `spotifyComp.bin` com o método escolhido → gera `spotifyDesc.txt` |
| `7` | Roda o benchmark completo (M execuções) e salva os resultados em `saida.txt` 📊 *(exige que `N` tenha sido passado por linha de comando)* |
| `0` | Sai do programa 👋 |

---

## 📊 Sobre o benchmark

A opção `7` do menu executa a função `gerarEstatisticas()`, que:

1. Sorteia uma nova amostra aleatória de `N` registros a cada execução;
2. Comprime essa amostra com os três métodos (Huffman, LZ77 e LZW);
3. Mede o tamanho comprimido, a taxa de compressão e o tempo gasto em cada método;
4. Repete o processo `M` vezes (por padrão, 5) e calcula as médias finais;
5. Salva tudo, execução por execução, em `saida.txt`.

---

## 📚 Sobre o dataset

Este projeto usa o dataset **[550K Spotify Songs: Audio, Lyrics & Genres](https://www.kaggle.com/datasets/serkantysz/550k-spotify-songs-audio-lyrics-and-genres/data)**, disponível no Kaggle.

> ⚠️ Por orientação do enunciado do trabalho, **os arquivos de dados (`.csv` e `.bin`) não são incluídos neste repositório**. Baixe o dataset separadamente e coloque o `songs.csv` na pasta que você vai passar como argumento na linha de comando.

---

## 👥 Equipe

| Integrante | Matrícula |
|---|---|
| Gabriel Haddad Cyrino Gadioli | 202435026 |
| Rafael Magno Campos da Silva | 202435012 |
| Thomas Adam Chapman | 202476030 |

---

## 🧠 Uso de IA

Durante o desenvolvimento, o grupo utilizou o **Google Gemini** como apoio para entender o funcionamento dos algoritmos e discutir decisões de arquitetura. Todo o código foi revisado, testado e é de autoria do grupo.

---

<p align="center">Feito com 💙, muito café ☕ e uns bytes perdidos por aí. 🎶</p>
