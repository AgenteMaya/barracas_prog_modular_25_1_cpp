/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>
#include <ctime>

struct auxProduto
{
    std::string nome;
    size_t qtd;
    float preco;
};

struct auxBarraca{
    std::string nome;
    int horaInicial;
    int MinutoInicial;
    int horaFinal;
    int MinutoFinal;
    size_t senha;
};

typedef struct auxProduto AuxProduto;
typedef struct auxBarraca AuxBarraca;

int criaBarraca(auxBarraca infoBarraca);

int atualizaBarraca (auxBarraca infoBarraca, std::string id);

int excluiBarraca (std::string id);

int buscaBarraca (std::string id, auxBarraca& barraca);

int mostrarTodasBarracasEProdutos();

int mostrarUmaBarraca(std::string id);

int editarQuantidadeProduto(std::string idProduto, std::string idBarraca, int alteracao);

int adicionaProdutoNoEstoque(std::string idProduto, int qtd, std::string idBarraca);

void excluirTodasBarracas ();