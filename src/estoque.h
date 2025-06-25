#include <string>

struct AuxEstoque
{
    std::string nomeBarraca;
    std::string nomeProduto;
    int qtd;
    float preco;
};

int criaEstoque (std::string nomeBarraca);
int adicionaProdutoNoEstoque(AuxEstoque infoEstoque);
int editarQuantidadeProduto(AuxEstoque infoEstoque);
int editarPrecoProduto(AuxEstoque infoEstoque);
int mostrarItensNoEstoqueUmaBarraca(std::string barraca);
int excluiItemDoEstoque (std::string nomeBarraca, std::string nomeItem);
int excluiEstoque (std::string nomeBarraca);
int confereNoEstoque(AuxEstoque& infoEstoque);



