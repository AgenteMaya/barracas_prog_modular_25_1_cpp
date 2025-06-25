#include <string>

struct AuxEstoque
{
    std::string nomeBarraca;
    std::string nomeProduto;
    int qtd;
    float preco;
};

int confereNoEstoque(AuxEstoque& infoEstoque);
bool buscaConfirmCliente(int cpf);
int editarQuantidadeProduto(AuxEstoque infoEstoque);
int buscaConfirmBarraca(std::string nomeBarraca);
