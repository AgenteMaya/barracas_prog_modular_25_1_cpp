#include "barraca.h"
#include <map>
#include <vector>
#include <utility>
#include <iostream>

struct barraca{
    std::string nome;
    size_t horarioInicial;
    size_t horarioFinal;
    size_t senha;
    size_t id;
    std::vector<std::pair<size_t, size_t>> lProdutos; //<qtd do Produto, id do produto>
};

typedef struct barraca Barraca;

static std::map<size_t, Barraca> lBarracas;

int criaBarraca (auxBarraca infoBarraca)
{
    Barraca novaBarraca{};
    novaBarraca.nome = infoBarraca.nome;
    novaBarraca.horarioInicial = novaBarraca.horarioInicial;
    novaBarraca.horarioFinal = novaBarraca.horarioFinal;
    novaBarraca.id = criaId();
    novaBarraca.senha = infoBarraca.senha;

    auto resultado = lBarracas.emplace(infoBarraca.senha, novaBarraca);

    if (!resultado.second) {
        return 1; 
    }   
    return 0;
}

int atualizaBarraca (auxBarraca infoBarraca, size_t id)
{
    auto resultado = lBarracas.find(id);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 

    resultado->second.nome = infoBarraca.nome;
    resultado->second.horarioInicial = infoBarraca.horarioInicial;
    resultado->second.horarioFinal = infoBarraca.horarioFinal;

    return 0;
}

int excluiBarraca (size_t id){
    auto resultado = lBarracas.erase(id);
    if (resultado)
        return 0;
    return 1;
}

int buscaBarraca (int id, auxBarraca& barraca)
{
    auto resultado = lBarracas.find(id);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 

    barraca.nome = resultado->second.nome;
    barraca.horarioInicial = resultado->second.horarioInicial;
    barraca.horarioFinal = resultado->second.horarioFinal;

    return 0;
}

int mostrarTodasBarracasEProdutos(){
    if (lBarracas.empty())
        return 1;

    for(auto it = lBarracas.begin(); it != lBarracas.end(); it++)
    {
        std::cout << "Barraca " << it->second.nome << std::endl;
        std::cout << "        Produtos: ";
        for(auto it2 = it->second.lProdutos.begin(); it2 != it->second.lProdutos.end(); it2++)
        {
            AuxProduto auxProduto;
            auto verifica = buscaProduto(it2->second, auxProduto);
            if (!verifica)
                std::cout << "                   " << auxProduto.nome << "  -  " << it2->first;
        }
    }

    return 0;
}

 int mostrarUmaBarraca(int id)
 {
    
 }



int main(){
    return 0;
}