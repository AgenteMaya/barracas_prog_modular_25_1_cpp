#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "pedido.h"
#include "testePedido.h"


bool mockBarraca;
int buscaConfirmBarraca(std::string nomeBarraca)
{
    return mockBarraca;
} 

bool mockCliente;
bool buscaConfirmCliente(int cpf)
{
    return mockCliente;
}

int mockConfereReturn;
int mockConfereQtd;
int confereNoEstoque(AuxEstoque& infoEstoque)
{
    infoEstoque.qtd = mockConfereQtd;
    return mockConfereReturn;
}

int editarQuantidadeProduto(AuxEstoque infoEstoque)
{
    return 0;
}


TEST_CASE("Testando funcao criaPedido")
{
    mockConfereReturn = 0;

    AuxPedido pedidoNovo{"c", 123, "coca", 2, "" };
    SUBCASE("Cria barraca nova")
    {
        CHECK(criaPedido(pedidoNovo) == 0);
    }

    AuxPedido pedidoNovo2{"d", 123, "coca", 2, "1" };
    criaPedido(pedidoNovo2);
    SUBCASE("Tenta inserir pedido com id já existente")
    {
        CHECK(criaPedido(pedidoNovo2) == 1);
    }

    mockConfereReturn = 1;
    AuxPedido pedidoNovo3{"a", 123, "coca", 2, "" };

    SUBCASE("Tenta inserir pedido com barraca não existente")
    {
        CHECK(criaPedido(pedidoNovo3) == 2);
    }

    mockConfereReturn = 2;
    AuxPedido pedidoNovo4{"c", 123, "pepsi", 2, "" };
    SUBCASE("Tenta inserir pedido com produto fora de estoque")
    {
        CHECK(criaPedido(pedidoNovo4) == 3);
    }
}

TEST_CASE("Testando função buscaPedidoClienteNFinalizado")
{
    mockCliente = false;
    mockConfereReturn = 0;
    AuxPedido pedidoNovo2{"a", 123, "pepsi", 2, "2" };
    criaPedido(pedidoNovo2);
    std::cout << "print dos testes" << std::endl;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de um cliente")
    {
        CHECK(buscaPedidoClienteNFinalizado(123) == 0);
    }

    mockCliente = 1;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de um cliente nao existente")
    {
        CHECK(buscaPedidoClienteNFinalizado(124) == 1);
    }
}

TEST_CASE("Testando função finalizarPedido")
{
    mockCliente = false;
    mockConfereReturn = 0;
    mockConfereQtd = 5;
    std::cout << "printar testes finalizar" << std::endl;
    SUBCASE("Tentar finalizar pedido existente")
    {
        CHECK(finalizarPedido("2") == 0);
    }

    SUBCASE("Tentar finalizar pedido inexistente")
    {
        CHECK(finalizarPedido("5") == 1);
    }

    SUBCASE("Tentar finalizar pedido já finalizado")
    {
        CHECK(finalizarPedido("2") == 2);
    }

    mockConfereQtd = 1;
    SUBCASE("Tentar finalizar pedido com algum produto fora de estoque de uma barraca")
    {
        CHECK(finalizarPedido("1") == 3);
    }
}

TEST_CASE("Testando função edicaoPedido")
{
    mockCliente = false;
    mockConfereReturn = 0;
    AuxPedido pedidoInexistente{"a", 123, "pepsi", 2, "3" };
    AuxPedido pedidoFinalizado{"a", 123, "pepsi", 2, "2" };
    AuxPedido pedidoExistenteAltera{"a", 123, "coca", 4, "1" };
    AuxPedido pedidoExistenteInsere{"a", 123, "fanta", 2, "1" };
    buscaPedidoClienteNFinalizado(123);
    SUBCASE("Tentar editar pedido inexistente")
    {
        CHECK(edicaoPedido(pedidoInexistente) == 1);
    }

    SUBCASE("Tentar editar pedido existente inserindo item")
    {
        CHECK(edicaoPedido(pedidoExistenteInsere) == 2);
    }

    SUBCASE("Tentar editar pedido existente alterando item")
    {
        CHECK(edicaoPedido(pedidoExistenteAltera) == 3);
    }

    SUBCASE("Tentar editar pedido existente ja finalizado")
    {
        CHECK(edicaoPedido(pedidoFinalizado) == 4);
    }
}

TEST_CASE("Testando função buscaPedidoClienteFinalizado")
{
    mockCliente = false;
    std::cout << "print dos testes" << std::endl;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de um cliente")
    {
        CHECK(buscaPedidoClienteFinalizado(123) == 0);
    }

    mockCliente = 1;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de um cliente nao existente")
    {
        CHECK(buscaPedidoClienteFinalizado(124) == 1);
    }
}

TEST_CASE("Testando função buscaPedidoClienteFinalizado")
{
    mockBarraca = 0;
    std::cout << "print dos testes" << std::endl;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de um cliente")
    {
        CHECK(buscaPedidosBarraca("d") == 0);
    }

    mockBarraca = 1;
    SUBCASE("Tentar imprimir lista de pedidos nao confirmados de uma barraca inexistente")
    {
        CHECK(buscaPedidosBarraca("h") == 1);
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