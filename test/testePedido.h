#include <string>

struct AuxEstoque
{
    std::string nomeBarraca;
    std::string nomeProduto;
    int qtd;
    float preco;
};

int confereNoEstoque(AuxEstoque& infoEstoque);
bool buscaConfirmCliente(long long  cpf);
int editarQuantidadeProduto(AuxEstoque infoEstoque);
int buscaConfirmaBarraca(std::string nomeBarraca);
