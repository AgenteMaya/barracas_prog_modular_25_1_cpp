#include <string>

struct auxProduto 
{
    std::string nome;
    size_t id;
};

typedef struct auxProduto AuxProduto;

int buscaProduto(size_t id, AuxProduto auxProduto);