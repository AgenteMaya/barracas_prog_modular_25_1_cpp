#include <string>

struct AuxEstoque
{
    std::string nomeBarraca;
    std::string nomeProduto;
    int qtd;
    float preco;
};

int confereNoEstoque(AuxEstoque& infoEstoque);
int editarQuantidadeProduto(AuxEstoque infoEstoque);

