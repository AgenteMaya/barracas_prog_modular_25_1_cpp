#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("success", true);      // mostra testes que passaram
    context.setOption("reporters", "console"); // saída padrão
    // context.setOption("no-breaks", true); // não para no primeiro erro

    context.applyCommandLine(argc, argv);    // aceita também flags via terminal
    int res = context.run();                 // roda os testes

    return res;
}