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

/*
Objetivo: Criar um novo cliente

Acoplamentos:

--> Parâmetros:
    AuxCliente infoCliente: estrutura contendo nome, CPF e senha do novo cliente.

--> Retornos:
    - 0 caso o cliente tenha sido criado com sucesso
    - 1 caso o nome/senha já exista
    - 2 caso o CPF seja inválido

Condições de acoplamento:

--> Assertivas de entrada:
    - O CPF deve ser positivo
    - O nome não pode estar vazio
    - A senha deve ter no máximo 10 caracteres
    - O CPF não pode já existir no mapa

--> Assertivas de saída:
    - Um novo cliente é adicionado ao mapa `lClientes`
*/
int criaCliente(AuxCliente infoCliente);

/*
Objetivo: Atualizar o nome de um cliente com CPF cadastrado.

Acoplamentos:

--> Parâmetros:
    AuxCliente cliente: estrutura com CPF já cadastrado e novos dados a serem atualizados.

--> Retornos:
    - 0 caso a atualização tenha sido realizada com sucesso
    - 1 caso o cliente não encontrado
    - 2 caso o CPF seja inválido

Condições de acoplamento:

--> Assertivas de entrada:
    - O CPF deve ser positivo e já existir em `lClientes`

--> Assertivas de saída:
    - O nome e a senha do cliente são atualizados no mapa
*/
int atualizaCliente(AuxCliente infoCliente);

/*
Objetivo: Excluir um cliente do sistema.

Acoplamentos:

--> Parâmetros:
    long long cpf: número do CPF do cliente a ser removido.

--> Retornos:
    - 0 caso o cliente tenha sido removido com sucesso
    - 1 caso o cliente não exista
    - 2 caso o CPF seja inválido

Condições de acoplamento:

--> Assertivas de entrada:
    - O CPF deve ser válido

--> Assertivas de saída:
    - O cliente correspondente é removido do mapa
*/
int excluiCliente(long long cpf);

/*
Objetivo: Consultar os dados de um cliente a partir do CPF e preenche a estrutura fornecida.

Acoplamentos:

--> Parâmetros:
    AuxCliente& cliente: estrutura com CPF preenchido e campos `nome` e `senha` a serem preenchidos na busca.

--> Retornos:
    - 0 caso o cliente seja encontrado
    - 1 caso o cliente não exista
    - 2 caso o CPF seja inválido

Condições de acoplamento:

--> Assertivas de entrada:
    - O CPF deve ser válido

--> Assertivas de saída:
    - A estrutura 'cliente' é preenchida com 'nome' e 'senha' correspondentes ao CPF
*/
int buscaCliente(AuxCliente& cliente);

/*
Objetivo: Verificar se um cliente com o CPF informado existe no sistema.

Acoplamentos:

--> Parâmetros:
    long long cpf: número do CPF a ser verificado.

--> Retornos:
    - 0 caso o cliente exista
    - 1 caso o cliente não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - O CPF deve ser válido

--> Assertivas de saída:
    - A função informa se há ou não um cliente com aquele CPF no sistema
*/

int buscaConfirmCliente(long long cpf);

/**
 * Apaga todos os clientes da memória (apenas com TESTE_ON definido).
 */
void excluirTodosClientes();

int fazerLoginCliente(AuxCliente clienteLogin);

bool carregaClienteCSV(std::ifstream& arquivo);

bool salvaClienteCSV(std::ofstream& arquivo);

#endif // CLIENTE_H
