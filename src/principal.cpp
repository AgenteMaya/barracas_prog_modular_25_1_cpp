#include "cliente.h"
#include "pedido.h"
#include "estoque.h"
#include "barraca.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Funções de leitura/escrita de CSV (você deve implementá-las nos módulos correspondentes)
/* std::vector<Cliente> carregarClientesCSV(const std::string& caminho);
void salvarClientesCSV(const std::vector<Cliente>& clientes, const std::string& caminho);

std::vector<Pedido> carregarPedidosCSV(const std::string& caminho);
void salvarPedidosCSV(const std::vector<Pedido>& pedidos, const std::string& caminho);

Estoque carregarEstoqueCSV(const std::string& caminho);
void salvarEstoqueCSV(const Estoque& estoque, const std::string& caminho);

std::vector<Barraca> carregarBarracasCSV(const std::string& caminho);
void salvarBarracasCSV(const std::vector<Barraca>& barracas, const std::string& caminho);
 */


void iniciarSistema() {
    std::ifstream f1("clientes.csv");
    std::ifstream f2("pedidos.csv");
    std::ifstream f3("estoque.csv");
    std::ifstream f4("barracas.csv");

    carregaClienteCSV(f1);
    carregaPedidosCSV(f2);
    carregaEstoqueCSV(f3);
    carregaBarracasCSV(f4);
}
// Salva os dados em arquivos CSV ao encerrar o sistema
void encerrarSistema() {
    std::ofstream f1("clientes.csv");
    std::ofstream f2("pedidos.csv");
    std::ofstream f3("estoque.csv");
    std::ofstream f4("barracas.csv");

    salvaClienteCSV(f1);
    salvaPedidoCSV(f2);
    salvaEstoqueCSV(f3);
    salvaBarracaCSV(f4);
}

// Função principal
int main() {
    iniciarSistema();
    exibirMenu();
    encerrarSistema();
    return 0;
}