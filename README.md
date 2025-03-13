# Comparação de Implementações: C, Rust e Golang

## 📌 Integrantes do Grupo
- **Miguel Rodrigues Botelho**  
- **João Reis**  
- **Pedro Zanchin Baldissera**  

## 📖 Descrição do Projeto
Este projeto tem como objetivo comparar as características das linguagens de programação **C**, **Rust** e **Golang**, implementando o algoritmo de **Eliminação de Gauss** em cada uma delas. A análise considera os seguintes aspectos:

- 🏗 **Estrutura e organização do código**  
- 🛠 **Tipos de dados e gerenciamento de memória**  
- ⚡ **Acesso a variáveis e chamadas de função**  
- 🔁 **Comandos de controle de fluxo**  
- 📊 **Métricas do código (número de linhas, número de comandos, etc.)**  
- 🚀 **Desempenho (Tempo de execução)**
- 📊 **Escalabilidade (Diferentes tamanhos de matrizes, com possibilidade de diferentes seeds)**
- 💻💻 ** Processamento (Dois sistemas operacionais com sistemas distindos, com caracteristicas distintas, onde serao feitos todos os experimentos) **


---

## ⚙️ Como Executar as Implementações

### 💻 **Linux**
Abra um terminal e execute:
```bash
git clone https://github.com/Bot-e-lho/CLP.git
```

### 🖥 **Windows**
Baixe e instale o Git para Windows caso ainda não tenha.
Abra o Git Bash e execute:

```bash
git clone https://github.com/Bot-e-lho/CLP.git
```

🔷 C
Pré-requisitos

🐧 Linux
Instalar o compilador GCC (caso não tenha)
```bash
sudo apt install build-essential
```
🖥 Windows
Instalar o MinGW (caso não tenha)

Baixe e instale o MinGW-w64: Download MinGW
Adicione o caminho do gcc.exe ao PATH do Windows.
Compilar e executar o código


Compilar e executar o código sem flag

🐧 Linux
```bash
cd c/
gcc gauss_linux.c -o gauss_c
./gauss_c <N> (tamanho da matriz) <SEED> (valor SEED)
```


🖥 Windows
```bash
cd c/
gcc gauss.c -o gauss.c
./gauss_c.exe <N> (tamanho da matriz) <SEED> (valor SEED)
```
Compilar e executar o código com flag

🐧 Linux
```bash
cd c/
gcc -O3 gauss_linux.c -o gauss_c
./gauss_c <N> (tamanho da matriz) <SEED> (valor SEED)
```


🖥 Windows
```bash
cd c/
gcc -O3 gauss.c -o gauss.c
./gauss_c.exe <N> (tamanho da matriz) <SEED> (valor SEED)
```

🦀 Rust
🐧 Linux
Instalar o Rust

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```
🖥 Windows
Instalar o Rust

Baixe e instale pelo site oficial: Rust Lang
Reinicie o terminal após a instalação.
Compilar e executar o código

Compilar e executar o código

🐧 Linux
```bash
cd rust/gauss
cargo run --release
```

🖥 Windows
```bash
cd rust/gauss
cargo run --release
```

🏎 Golang
🐧 Linux
Instalar o Go
```bash
sudo apt install golang-go
```
🖥 Windows
Instalar o Go

Baixe e instale pelo site oficial: Download Go
Reinicie o terminal após a instalação.
Executar o código

Executar o código

🐧 Linux
```bash
cd golang/
go run gauss.go
```
🖥 Windows
```bash
cd golang/
go run gauss.go
```

