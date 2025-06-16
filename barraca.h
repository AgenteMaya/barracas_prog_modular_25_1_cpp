/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>
#include <ctime>

struct auxBarraca{
    std::string nome;
    int horaInicial;
    int MinutoInicial;
    int horaFinal;
    int MinutoFinal;
    size_t senha;
};
typedef struct auxBarraca AuxBarraca;

int criaBarraca(auxBarraca infoBarraca);

int atualizaBarraca (auxBarraca infoBarraca, std::string id);

int excluiBarraca (std::string id);

int buscaBarraca (std::string id, auxBarraca& barraca);

int mostrarTodasBarracasEProdutos();

int mostrarUmaBarraca(std::string id);

int editarQuantidadeProduto(size_t idProduto, std::string idBarraca, int alteracao);

int adicionaProdutoNoEstoque(size_t idProduto, int qtd, std::string idBarraca);

void excluirTodasBarracas ();