/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "barraca.h"
#include "testeBarraca.h"

int buscaProduto(std::string id, AuxProduto& auxProduto){
    auxProduto.id = 9;
    auxProduto.nome = "coca";
    return 0;
}

bool mock;

int buscaConfirmProduto(std::string id)
{
    return mock;
}

int mostrarItensNoEstoqueUmaBarraca(std::string barraca){
    return 0;
}


TEST_CASE("Testando função criaBarraca")
{
    auxBarraca barracaNova{"a", 8, 30, 19, 30, 1234};
    SUBCASE("Cria barraca nova")
    {
        CHECK(criaBarraca(barracaNova) == 0);
    }

    SUBCASE("Tentar inserir barraca com nome já existente")
    {
        CHECK(criaBarraca(barracaNova) == 1);
    }


}

TEST_CASE("Testando função atualizaBarraca")
{

    auxBarraca barracaNovaB{"b", 9, 30, 20, 30, 1234};
    auxBarraca barracaNovaA{"a", 10, 30, 21, 30, 1234};

    SUBCASE("Atualizar barraca já existente")
    {
        CHECK(atualizaBarraca(barracaNovaA) == 0);
    }

    SUBCASE("Tentar editar barraca inexistente")
    {
        CHECK(atualizaBarraca(barracaNovaB) == 1);
    }
}



TEST_CASE("Testando função excluiBarraca")
{
    auxBarraca barracaNovaB{"b", 9, 30, 20, 30, 1234};
    criaBarraca(barracaNovaB);
    SUBCASE("Exclui uma barraca existente")
    {
        CHECK(excluiBarraca("b") == 0);
    }

    SUBCASE("Tentar excluir barraca inexistente")
    {
        CHECK(excluiBarraca("c") == 1);
    }
}

TEST_CASE("Testando função buscaBarraca")
{
    auxBarraca barracaTesteExistente;
    barracaTesteExistente.nome = "a";
    SUBCASE("Encontrar barraca existente")
    {
        CHECK(buscaBarraca(barracaTesteExistente) == 0);
    }

    auxBarraca barracaTesteNExistente;
    barracaTesteNExistente.nome = "h";

    SUBCASE("Tentar encontra barraca não existente")
    {
        CHECK(buscaBarraca(barracaTesteNExistente) == 1);
    }
}

TEST_CASE("Testando mostrarUmaBarraca")
{
    SUBCASE("Mostra uma barraca existente")
    {
        CHECK(mostrarUmaBarraca("a") == 0);
    }

    SUBCASE("Tentar mostrar barraca inexistente")
    {
        CHECK(mostrarUmaBarraca("h") == 1);
    }
}

TEST_CASE("Testando função mostrarTodasBarracasEProdutos")
{
    SUBCASE("Mostrar todas as barracas")
    {
        CHECK(mostrarTodasBarracasEProdutos() == 0);
    }

    SUBCASE("Tentar Mostrar lista de barraca vazia")
    {
        excluirTodasBarracas();
        CHECK(mostrarTodasBarracasEProdutos() == 1);
    }
}

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("success", true);      // mostra testes que passaram
    context.setOption("reporters", "console"); // saída padrão
    // context.setOption("no-breaks", true); // não para no primeiro erro

    context.applyCommandLine(argc, argv);    // aceita também flags via terminal
    int res = context.run();                 // roda os testes

    return res;
}


