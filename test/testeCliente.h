/**
 * @author Maria Isabel Nicolau
 * @date 2025-06-21
 */

#ifndef TESTE_CLIENTE_H
#define TESTE_CLIENTE_H

#include <string>
#include "cliente.h"  // ✅ Inclui a struct corretamente, sem duplicar

#define TESTE_ON

// Protótipos de funções auxiliares que podem ser mockadas ou testadas
int loginCliente(long long cpf, const std::string& senha);
void excluirTodosClientes();

#endif // TESTE_CLIENTE_H
