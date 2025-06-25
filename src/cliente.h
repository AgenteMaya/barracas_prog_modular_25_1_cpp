// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct auxCliente {
    std::string nome;
    long long cpf;
    std::string senha;
};
typedef struct auxCliente AuxCliente;

/**
 * Cria um cliente com os dados fornecidos.
 * @return 0 se criado com sucesso, 1 se nome/senha inválido ou já existe, 2 se CPF inválido.
 */
int criaCliente(AuxCliente infoCliente);

/**
 * Atualiza o nome do cliente com o CPF fornecido.
 * @return 0 se atualizado com sucesso, 1 se cliente não encontrado, 2 se CPF inválido.
 */
int atualizaCliente(AuxCliente infoCliente);

/**
 * Exclui o cliente com o CPF fornecido.
 * @return 0 se excluído com sucesso, 1 se não encontrado, 2 se CPF inválido.
 */
int excluiCliente(long long cpf);

/**
 * Busca um cliente pelo CPF e preenche a estrutura fornecida.
 * @return 0 se encontrado, 1 se não encontrado, 2 se CPF inválido.
 */
int buscaCliente(AuxCliente& cliente);

/**
 * Apaga todos os clientes da memória (apenas com TESTE_ON definido).
 */
void excluirTodosClientes();

#endif // CLIENTE_H
