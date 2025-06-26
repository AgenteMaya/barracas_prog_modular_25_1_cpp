/**
 * @author Mayara Ramos Damazio
 * @date 2025-06-15
 */

#include <string>
#include <ctime>

/* struct auxProduto
{
    std::string nome;
    size_t qtd;
    float preco;
};
 */
struct AuxBarraca{
    std::string nome;
    int horaInicial;
    int MinutoInicial;
    int horaFinal;
    int MinutoFinal;
    size_t senha;
};

/*
Objetivo: Cadastrar uma nova barraca no sistema com os dados fornecidos.

Descrição:
1. Recebe uma struct contendo nome, horário de funcionamento e senha da barraca.
2. Valida os dados e insere a barraca no sistema se ainda não existir.

Acoplamentos:

--> Parâmetros:
    AuxBarraca infoBarraca: estrutura com os dados da nova barraca.

--> Retornos:
    - 0: Barraca criada com sucesso.
    - 1: Barraca já existe.
    - 2: Dados inválidos (ex: horário incoerente).

Condições de acoplamento:

--> Assertivas de entrada:
    - `infoBarraca.nome` deve ser não vazio.
    - Horário de início deve ser anterior ao horário final.
    - A senha deve ser positiva.

--> Assertivas de saída:
    - A nova barraca é registrada no sistema com suas configurações.
*/
int criaBarraca(AuxBarraca infoBarraca);

/*
Objetivo: Atualizar os dados de uma barraca já cadastrada.

Descrição:
1. Recebe os novos dados via struct.
2. Verifica se a barraca existe.
3. Atualiza horário de funcionamento e senha.

Acoplamentos:

--> Parâmetros:
    AuxBarraca infoBarraca: estrutura contendo os dados atualizados da barraca.

--> Retornos:
    - 0: Atualização realizada com sucesso.
    - 1: Barraca não encontrada.
    - 2: Dados inválidos.

Condições de acoplamento:

--> Assertivas de entrada:
    - `infoBarraca.nome` deve ser de uma barraca já registrada.
    - Horários e senha devem estar em um formato válido.

--> Assertivas de saída:
    - A barraca tem seus dados atualizados corretamente no sistema.
*/
int atualizaBarraca (AuxBarraca infoBarraca);

/*
Objetivo: Excluir uma barraca do sistema com base no seu identificador.

Descrição:
1. Recebe o nome ou id da barraca.
2. Verifica se a barraca existe.
3. Remove a barraca e seus dados do sistema.

Acoplamentos:

--> Parâmetros:
    std::string id: identificador da barraca a ser removida.

--> Retornos:
    - 0: Barraca excluída com sucesso.
    - 1: Barraca não encontrada.

Condições de acoplamento:

--> Assertivas de entrada:
    - `id` deve corresponder a uma barraca existente.

--> Assertivas de saída:
    - A barraca é removida permanentemente do sistema.
*/
int excluiBarraca (std::string id);

/*
Objetivo: Buscar os dados de uma barraca específica.

Descrição:
1. Recebe uma struct com o nome da barraca.
2. Preenche a struct com as informações completas (horários e senha), se encontrada.

Acoplamentos:

--> Parâmetros:
    AuxBarraca& barraca: estrutura que contém o nome da barraca e será preenchida com os dados encontrados.

--> Retornos:
    - 0: Barraca encontrada com sucesso.
    - 1: Barraca não encontrada.

Condições de acoplamento:

--> Assertivas de entrada:
    - `barraca.nome` deve estar preenchido.

--> Assertivas de saída:
    - A struct `barraca` recebe as informações completas da barraca encontrada.
*/
int buscaBarraca (AuxBarraca& barraca);

/*
Objetivo: Exibir no console todas as barracas cadastradas e seus produtos disponíveis.

Descrição:
1. Percorre todas as barracas existentes no sistema.
2. Para cada barraca, imprime seu nome e a lista de produtos com quantidades e preços.

Acoplamentos:

--> Parâmetros:
    (nenhum)

--> Retornos:
    - 0: Sucesso na exibição dos dados.
    - 1: Nenhuma barraca cadastrada.

Condições de acoplamento:

--> Assertivas de entrada:
    - Nenhuma.

--> Assertivas de saída:
    - Todas as barracas e seus produtos são exibidos no console.
*/
int mostrarTodasBarracasEProdutos();

/*
Objetivo: Exibir os dados de uma barraca específica.

Descrição:
1. Recebe o nome/id da barraca.
2. Imprime no console as informações da barraca e seus produtos, se existir.

Acoplamentos:

--> Parâmetros:
    std::string id: nome ou identificador da barraca.

--> Retornos:
    - 0: Barraca encontrada e exibida.
    - 1: Barraca não encontrada.

Condições de acoplamento:

--> Assertivas de entrada:
    - `id` deve corresponder a uma barraca existente.

--> Assertivas de saída:
    - Os dados da barraca e seus produtos são impressos no console.
*/
int mostrarUmaBarraca(std::string id);

/*
Objetivo: Remover todas as barracas cadastradas no sistema.

Descrição:
1. Limpa todas as estruturas que armazenam os dados das barracas.
2. Apaga também seus produtos relacionados, se necessário.

Acoplamentos:

--> Parâmetros:
    (nenhum)

--> Retornos:
    (void)

Condições de acoplamento:

--> Assertivas de entrada:
    - Nenhuma.

--> Assertivas de saída:
    - Todas as barracas são removidas da memória do sistema.
*/
void excluirTodasBarracas ();

/*
Objetivo: Verificar se uma barraca está cadastrada no sistema.

Descrição:
1. Recebe o id da barraca e verifica sua existência.
2. Utilizada como função auxiliar em validações.

Acoplamentos:

--> Parâmetros:
    std::string id: nome ou identificador da barraca.

--> Retornos:
    - 0: Barraca confirmada (existe).
    - 1: Barraca não encontrada.


Condições de acoplamento:
--> Assertivas de entrada:
    - `id` não deve estar vazio.

--> Assertivas de saída:
    - Confirma a existência da barraca no sistema.
*/

int buscaConfirmaBarraca(std::string id);

int fazerLoginBarraca(AuxBarraca loginBarraca);

bool carregaBarracasCSV(std::ifstream& arquivo);

bool salvaBarracaCSV(std::ofstream& arquivo);