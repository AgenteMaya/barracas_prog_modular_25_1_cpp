// cliente.cpp
#include "cliente.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

struct Cliente {
    std::string nome;
    long long cpf;
    std::string senha;
};

static std::map<long long, Cliente> lClientes;

int criaCliente(AuxCliente infoCliente) {
    if (infoCliente.nome.empty() || infoCliente.senha.length() > 10 || infoCliente.cpf <= 0)
        return infoCliente.nome.empty() ? 1 : (infoCliente.senha.length() > 10 ? 1 : 2);

    Cliente novoCliente{};
    novoCliente.nome = infoCliente.nome;
    novoCliente.cpf = infoCliente.cpf;
    novoCliente.senha = infoCliente.senha;

    auto resultado = lClientes.emplace(novoCliente.cpf, novoCliente);
    if (!resultado.second) return 1;
    return 0;
}

int atualizaCliente(auxCliente cliente) {
    if (cliente.cpf <= 0) return 2;

    auto it = lClientes.find(cliente.cpf);
    if (it == lClientes.end()) return 1;

    it->second.nome = cliente.nome;
    it->second.senha = cliente.senha;
    return 0;
}

int excluiCliente(long long cpf) {
    if (cpf <= 0) return 2;

    auto resultado = lClientes.erase(cpf);
    return resultado ? 0 : 1;
}

int buscaCliente(AuxCliente& cliente) {
    if (cliente.cpf <= 0) return 2;

    auto it = lClientes.find(cliente.cpf);
    if (it == lClientes.end()) return 1;

    cliente.nome = it->second.nome;
    cliente.senha = it->second.senha;
    return 0;
}

int buscaConfirmCliente(long long cpf)
{
    auto it = lClientes.find(cpf);
    if (it == lClientes.end()) {
        return 1;
    } 
    return 0;
}

int fazerLoginCliente(AuxCliente clienteLogin)
{
    auto it = lClientes.find(clienteLogin.cpf);
    if (it == lClientes.end() || it->second.senha != clienteLogin.senha) {
        return 1;
    } 
    return 0;
}

bool salvaClienteCSV(std::ofstream& arquivo) {

    if (!arquivo.is_open()) {
        return false;
    }

    for(auto& cliente : lClientes)
    {
        arquivo << cliente.second.nome << "," << cliente.second.cpf << "," << cliente.second.senha << "\n";
    }
    return arquivo.good();
}

bool carregaClienteCSV(std::ifstream& arquivo) {
    std::string linha;
    bool carregouAlgum = false;

    while (std::getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string campo;
        Cliente cliente;

        // Nome
        if (!std::getline(ss, campo, ','))
            continue;
        cliente.nome = campo;

        // CPF
        if (!std::getline(ss, campo, ','))
            continue;
        try {
            cliente.cpf = std::stoll(campo);
        } catch (...) {
            continue;
        }

        // Senha
        if (!std::getline(ss, campo))
            continue;
        cliente.senha = campo;

        lClientes[cliente.cpf] = cliente;
        carregouAlgum = true;
    }

    return carregouAlgum;
}

#ifdef TESTE_ON
void excluirTodosClientes() {
    lClientes.clear();
}
#endif
