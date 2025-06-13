#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "barraca.h"

TESTE_CASE("Testando função cria barraca")
{
    auxBarraca barracaNova{"a", 8, 30, 19, 30, 1234};

    SUBCASE("Cria barraca nova")
    {
        CHECK(criaBarraca(barracaNova) == 0);
    }

    SUBCASE("Tentar inserir barraca com id já existente")
    {
        CHECK(criaBarraca(barracaNova) == 1);
    }
}

TEST_CASE
