#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "cliente.h"
#include "testeCliente.h"



TEST_CASE("Testando função criaCliente") {
    AuxCliente cliente1{"Carlos", 12345678900, "senha123"};

    SUBCASE("Criação bem-sucedida") {
        CHECK(criaCliente(cliente1) == 0);
    }

    SUBCASE("Nome vazio") {
        AuxCliente cliente2{"", 12345678901, "senha123"};
        CHECK(criaCliente(cliente2) == 1);
    }

    SUBCASE("Senha com mais de 10 caracteres") {
        AuxCliente cliente3{"Ana", 12345678902, "senhamuitogrande"};
        CHECK(criaCliente(cliente3) == 1);
    }

    SUBCASE("CPF inválido") {
        AuxCliente cliente4{"João", -1, "senha123"};
        CHECK(criaCliente(cliente4) == 2);
    }

    SUBCASE("CPF já existente") {
        CHECK(criaCliente(cliente1) == 1);
    }
}

TEST_CASE("Testando função atualizaCliente") {

    auxCliente clienteExiste{"Carlos Silva", 12345678900, "senha123"};
    auxCliente clienteCpfNexiste{"Novo Nome", 99999999999, "senha123"};
    auxCliente clienteCpfInv{"Teste", -10, "senha123"};

    SUBCASE("Atualiza cliente com sucesso") {
        CHECK(atualizaCliente(clienteExiste) == 0);
    }

    SUBCASE("CPF não existente") {
        CHECK(atualizaCliente(clienteCpfNexiste) == 1);
    }

    SUBCASE("CPF inválido") {
        CHECK(atualizaCliente(clienteCpfInv) == 2);
    }
}

TEST_CASE("Testando função excluiCliente") {
    SUBCASE("Exclui cliente com sucesso") {
        CHECK(excluiCliente(12345678900) == 0);
    }

    SUBCASE("Cliente não encontrado") {
        CHECK(excluiCliente(99999999999) == 1);
    }

    SUBCASE("CPF inválido") {
        CHECK(excluiCliente(-1) == 2);
    }
}

TEST_CASE("Testando função buscaCliente") {
    AuxCliente clienteBuscado;

    SUBCASE("Busca cliente com sucesso") {
        AuxCliente cliente{"Maria", 11111111111, "abc123"};
        criaCliente(cliente);
        clienteBuscado.cpf = cliente.cpf;
        CHECK(buscaCliente(clienteBuscado) == 0);
        CHECK(clienteBuscado.nome == "Maria");
    }

    SUBCASE("Cliente não encontrado") {
        clienteBuscado.cpf = 99999999999;
        CHECK(buscaCliente(clienteBuscado) == 1);
    }

    SUBCASE("CPF inválido") {
        clienteBuscado.cpf = -1;
        CHECK(buscaCliente(clienteBuscado) == 2);
    }
}

TEST_CASE("Testando função buscaConfirmCliente") {
    AuxCliente clienteBuscado;

    SUBCASE("Busca cliente com sucesso") {
        CHECK(buscaConfirmCliente(11111111111) == 0);
    }

    SUBCASE("Cliente inexistente") {
        CHECK(buscaConfirmCliente(99999999999) == 1);
    }
}

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("success", true);
    context.setOption("reporters", "console");

    context.applyCommandLine(argc, argv);
    return context.run();
}
