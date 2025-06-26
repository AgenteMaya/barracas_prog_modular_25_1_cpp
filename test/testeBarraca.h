/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>

#define TESTE_ON

struct AuxProduto 
{
    std::string nome;
    std::string id;
};

int buscaProduto(std::string id, AuxProduto& auxProduto);

int buscaConfirmProduto(std::string id);

int mostrarItensNoEstoqueUmaBarraca(std::string barraca);
