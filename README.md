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
- 🚀 **Desempenho (tempo de execução para diferentes tamanhos de matriz)**  

## 📂 Estrutura do Repositório

📄 README.md # Documentação do projeto
📄 LICENSE # licença do projeto
📦 gauss_implementation ├── 📁 c/ # code in c │ ├── gauss.c 
                        ├── 📁 golang/ # code in go│ ├── gauss.go 
                        ├── 📁 rust/ # code in rust │ ├── teste
                                                    │ ├── gauss/ │ ├── 📄 gitgnore
                                                                 │ ├── 📄 Cargo.lock
                                                                 │ ├── 📄 Cargo.toml
                                                                 │ ├── src/ | ├── main.rs

 


---

## ⚙️ Como Executar as Implementações

### 💻 **Linux**
Abra um terminal e execute:
```bash
git clone https://github.com/usuario/gauss_implementation.git

🖥 Windows
Baixe e instale o Git para Windows caso ainda não tenha.
Abra o Git Bash e execute:

git clone https://github.com/usuario/gauss_implementation.git

🔷 C
Pré-requisitos

🐧 Linux
Instalar o compilador GCC (caso não tenha)
sudo apt install build-essential
Compilar e executar o código
cd c/
gcc -o gauss_c gauss.c -O2 -lm
./gauss_c

🖥 Windows
Instalar o MinGW (caso não tenha)

Baixe e instale o MinGW-w64: Download MinGW
Adicione o caminho do gcc.exe ao PATH do Windows.
Compilar e executar o código

cd c/
gcc -o gauss_c.exe gauss.c -O2 -lm
./gauss_c.exe

🦀 Rust
🐧 Linux
Instalar o Rust

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

Compilar e executar o código
cd rust/gauss
cargo run --release

🖥 Windows
Instalar o Rust

Baixe e instale pelo site oficial: Rust Lang
Reinicie o terminal após a instalação.
Compilar e executar o código

cd rust/gauss
cargo run --release

🏎 Golang
🐧 Linux
Instalar o Go
sudo apt install golang-go

Executar o código
cd golang/
go run gauss.go

🖥 Windows
Instalar o Go

Baixe e instale pelo site oficial: Download Go
Reinicie o terminal após a instalação.
Executar o código
cd golang/
go run gauss.go

📌 Conclusão
Com essa comparação, buscamos entender as vantagens e desvantagens de cada linguagem no contexto da computação numérica e eficiência. Esperamos que esta análise contribua para a escolha da linguagem mais adequada para problemas de computação de alto desempenho.
