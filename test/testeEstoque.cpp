#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "estoque.h"
#include "testeEstoque.h"

bool mockBarraca;

int buscaConfirmaBarraca(std::string id)
{
    return mockBarraca;
}

TEST_CASE("Testando função criaBarraca")
{
    mockBarraca = false;
    SUBCASE("Cria estoque novo")
    {
        CHECK(criaEstoque("a") == 0);
    }

    SUBCASE("Tentar inserir estoque de uma barraca já existente")
    {
        CHECK(criaEstoque("a") == 1);
    }

    mockBarraca = true;
    SUBCASE("Tentar criar estoque sem barraca existir")
    {
        CHECK(criaEstoque("b") == 2);
    }
}

TEST_CASE("Testando adicionaProdutoNoEstoque")
{   
    mockBarraca = false;

    AuxEstoque infoEstoque1 {"a", "coca", 2, 2.0};
    AuxEstoque infoEstoque2 {"c", "coca", 2, 2.0};

    SUBCASE("Adicionar um produto na lista de estoque")
    {
        CHECK(adicionaProdutoNoEstoque(infoEstoque1) == 0);
    }
    
    SUBCASE("tentar adicionar produto já existente")
    {
        CHECK(adicionaProdutoNoEstoque(infoEstoque1) == 1);
    }
    
    mockBarraca = true;
    SUBCASE("tentar adicionar produto em barraca inexistente")
    {
        CHECK(adicionaProdutoNoEstoque(infoEstoque2) == 2);
    }
}

TEST_CASE("Testando função editarQuantidadeProduto")
{

    AuxEstoque infoEstoque1 {"a", "coca", 4, 2.0};
    AuxEstoque infoEstoque2 {"b", "coca", 4, 2.0};
    AuxEstoque infoEstoque3 {"a", "pepsi", 4, 2.0};

    SUBCASE("Atualizar qtd de um produto de uma barraca existente")
    {
        CHECK(editarQuantidadeProduto(infoEstoque1) == 0);
    }

    SUBCASE("tentar atualizar qtd produto em barraca inexistente")
    {
        CHECK(editarQuantidadeProduto(infoEstoque2) == 1);
    }

    SUBCASE("Tentar editar qtd de um produto inexistente")
    {
        CHECK(editarQuantidadeProduto(infoEstoque3) == 2);
    }
}

TEST_CASE("Testando função editarPrecoProduto")
{

    AuxEstoque infoEstoque1 {"a", "coca", 4, 2.5};
    AuxEstoque infoEstoque2 {"b", "coca", 4, 2.5};
    AuxEstoque infoEstoque3 {"a", "pepsi", 4, 2.5};

    SUBCASE("Atualizar o preco de um produto de uma barraca existente")
    {
        CHECK(editarPrecoProduto(infoEstoque1) == 0);
    }

    SUBCASE("tentar atualizar o preco de um produto em barraca inexistente")
    {
        CHECK(editarPrecoProduto(infoEstoque2) == 1);
    }

    SUBCASE("Tentar editar preco de produto inexistente")
    {
        CHECK(editarPrecoProduto(infoEstoque3) == 2);
    }
}

TEST_CASE("Testando mostrarItensNoEstoqueUmaBarraca")
{
    std::cout << "entrei no teste da mostrar" << std::endl;
    SUBCASE("Mostra uma itens de barraca existente")
    {
        CHECK(mostrarItensNoEstoqueUmaBarraca("a") == 0);
    }

    SUBCASE("Tentar mostrar itens de uma barraca inexistente")
    {
        CHECK(mostrarItensNoEstoqueUmaBarraca("b") == 1);
    }
}

TEST_CASE("Testando função confereNoEstoque")
{
    AuxEstoque infoEstoque1 {"a", "coca", 4, 2.5};
    AuxEstoque infoEstoqueZerar {"a", "coca", -5, 2.5};
    AuxEstoque infoEstoque2 {"b", "coca", 4, 2.5};
    AuxEstoque infoEstoque3 {"a", "pepsi", 4, 2.5};
    
    SUBCASE("Conseguir conferir que o produto existe")
    {
        CHECK(confereNoEstoque(infoEstoque1) == 0);
    }

    SUBCASE("Tentar conferir produto em uma barraca inexistente")
    {
        CHECK(confereNoEstoque(infoEstoque2) == 1);
    }

    SUBCASE("Tentar conferir produto inexistente ou fora de estoque")
    {
        CHECK(confereNoEstoque(infoEstoque3) == 2);
        editarQuantidadeProduto(infoEstoqueZerar);
        CHECK(confereNoEstoque(infoEstoque1) == 2);
    }
}

TEST_CASE("Testando função excluiItemDoEstoque")
{
    SUBCASE("Exclui um item de uma barraca existente")
    {
        CHECK(excluiItemDoEstoque("a", "coca") == 0);
    }

    SUBCASE("Tentar excluir item inexistente em uma barraca")
    {
        CHECK(excluiItemDoEstoque("a", "coca") == 1);
    }

    SUBCASE("Tentar excluir barraca inexistente")
    {
        CHECK(excluiItemDoEstoque("b", "coca") == 2);
    }
}

TEST_CASE("Testando função excluiEstoque")
{
    SUBCASE("Exclui uma barraca existente")
    {
        CHECK(excluiEstoque("a") == 0);
    }

    SUBCASE("Tentar excluir barraca inexistente")
    {
        CHECK(excluiEstoque("b") == 1);
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