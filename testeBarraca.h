/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>

#define TESTE_ON

struct auxProduto 
{
    std::string nome;
    size_t id;
};

typedef struct auxProduto AuxProduto;

int buscaProduto(size_t id, AuxProduto auxProduto);

int buscaConfirmProduto(size_t id);