#include <string>


struct auxBarraca{
    std::string nome;
    size_t horarioInicial;
    size_t horarioFinal;
    size_t senha;
};

int criaBarraca(auxBarraca infoBarraca);

int atualizaBarraca (auxBarraca infoBarraca, size_t id);

int excluiBarraca (size_t id);

int buscaBarraca (size_t id);

int mostrarTodasBarracasEProdutos();

int mostrarUmaBarraca(size_t id);

int editarQuantidadeProduto(size_t idProduto, size_t idBarraca, int alteracao);

int adicionaProdutoNoEstoque(size_t idProduto, size_t qtd, size_t idBarraca);
