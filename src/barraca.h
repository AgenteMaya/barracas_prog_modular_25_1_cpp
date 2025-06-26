/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>
#include <ctime>

/* struct auxProduto
{
    std::string nome;
    size_t qtd;
    float preco;
};
 */
struct AuxBarraca{
    std::string nome;
    int horaInicial;
    int MinutoInicial;
    int horaFinal;
    int MinutoFinal;
    size_t senha;
};

int criaBarraca(AuxBarraca infoBarraca);

int atualizaBarraca (AuxBarraca infoBarraca);

int excluiBarraca (std::string id);

int buscaBarraca (AuxBarraca& barraca);

int mostrarTodasBarracasEProdutos();

int mostrarUmaBarraca(std::string id);

int editarQuantidadeProduto(std::string idProduto, std::string idBarraca, int alteracao);

int adicionaProdutoNoEstoque(std::string idProduto, int qtd, std::string idBarraca);

void excluirTodasBarracas ();

int buscaConfirmaBarraca(std::string id);