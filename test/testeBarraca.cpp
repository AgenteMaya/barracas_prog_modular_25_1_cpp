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

    auxBarraca barracaNovaB1{"b", 9, 30, 20, 30, 1234};
    auxBarraca barracaNovaB2{"b", 11, 30, 21, 30, 1234};
    auxBarraca barracaNovaC{"c", 10, 30, 21, 30, 1234};

    SUBCASE("Atualizar barraca já existente")
    {
        CHECK(atualizaBarraca(barracaNovaC, "a") == 0);
    }

    SUBCASE("Atualizar nome da barraca com alguma que já tenha o nome")
    {
        criaBarraca(barracaNovaB1);
        CHECK(atualizaBarraca(barracaNovaB2, "c") == 2);
    }

    SUBCASE("Tentar editar barraca inexistente")
    {
        CHECK(atualizaBarraca(barracaNovaC, "e") == 1);
    }
}



TEST_CASE("Testando função excluiBarraca")
{
    SUBCASE("Exclui uma barraca existente")
    {
        CHECK(excluiBarraca("b") == 0);
    }

    SUBCASE("Tentar excluir barraca inexistente")
    {
        CHECK(excluiBarraca("b") == 1);
    }
}

TEST_CASE("Testando função buscaBarraca")
{
    auxBarraca barracaTeste;
    SUBCASE("Encontrar barraca existente")
    {
        CHECK(buscaBarraca("c", barracaTeste) == 0);
    }

    SUBCASE("Tentar encontra barraca não existente")
    {
        CHECK(buscaBarraca("h", barracaTeste) == 1);
    }
}

TEST_CASE("Testando mostrarUmaBarraca")
{
    SUBCASE("Mostra uma barraca existente")
    {
        CHECK(mostrarUmaBarraca("c") == 0);
    }

    SUBCASE("Tentar mostrar barraca inexistente")
    {
        CHECK(mostrarUmaBarraca("b") == 1);
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


