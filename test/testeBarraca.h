/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>

#define TESTE_ON

struct auxProduto 
{
    std::string nome;
    std::string id;
};

typedef struct auxProduto AuxProduto;

int buscaProduto(std::string id, AuxProduto& auxProduto);

int buscaConfirmProduto(std::string id);