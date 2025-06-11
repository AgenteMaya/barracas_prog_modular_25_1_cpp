#include "testeBarraca.h"
#include "barraca.h"
#include <map>
#include <iostream>

struct produto{
    std::string nome;
    size_t id;
};


int main()
{
    std::map<size_t, std::string> lProdutos;
    lProdutos.emplace(1, "Pão de Queijo");
    lProdutos.emplace(2, "Mate");

    std::cout << "TESTE 1: ler todas as barracas com a lista vazia - Correto 1" << std::endl;
    auto resultado1 = mostrarTodasBarracasEProdutos();
    if (resultado1)
        std::cout << "Passou no teste 1" << std::endl;
    else
        std::cout << "Não passou no teste 1" << std::endl;

    auxBarraca barraca1{"b1", 8, 30, 19, 30, 1234};

    std::cout << "TESTE 2: Adicionar uma barraca no map - Correto 0" << std::endl;

    auto resultado2 = criaBarraca(barraca1);
    if (!resultado1)
        std::cout << "Passou no teste 2" << std::endl;
    else
        std::cout << "Não passou no teste 2" << std::endl;

     std::cout << "TESTE 3: Adicionar uma barraca no map - Correto 0" << std::endl;

    auto resultado2 = criaBarraca(barraca1);
    if (!resultado1)
        std::cout << "Passou no teste 2" << std::endl;
    else
        std::cout << "Não passou no teste 2" << std::endl;

    








    
}




int buscaProduto(size_t id, AuxProduto auxProduto){

}