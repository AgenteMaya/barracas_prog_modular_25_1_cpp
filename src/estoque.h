#include <string>

struct AuxEstoque
{
    std::string nomeBarraca;
    std::string nomeProduto;
    int qtd;
    float preco;
};

/*
Objetivo: Criar um novo estoque associado a uma barraca.

Descrição:
1. Verifica se já existe um estoque para a barraca fornecida.
2. Se não existir, cria um novo objeto `Estoque` e o insere no mapa `lEstoque`.
3. Se já houver estoque com o mesmo nome, a função retorna erro.

Acoplamentos:

--> Parâmetros:
    std::string nomeBarraca: nome da barraca que terá um novo estoque associado.

--> Retornos:
    - 0 caso o estoque tenha sido criado corretamente
    - 1 caso já exista um estoque com esse nome
    - 2 caso a função de verificação indique erro na barraca

Condições de acoplamento:

--> Assertivas de entrada:
    - 'nomeBarraca' deve ser uma string válida e não vazia

--> Assertivas de saída:
    - Um novo estoque é adicionado a 'lEstoque' caso não exista um com esse nome
*/
int criaEstoque (std::string nomeBarraca);

/*
Objetivo: Adicionar um novo produto ao estoque de uma barraca.

Descrição:
1. Verifica se a barraca informada existe.
2. Tenta inserir um novo produto no mapa `lProdutos` da barraca.
3. Se o produto já existir, a função não altera o estoque e retorna erro.

Acoplamentos:

--> Parâmetros:
    AuxEstoque infoEstoque: estrutura contendo o nome da barraca, produto, quantidade e preço.

--> Retornos:
    - 0 caso o produto tenha sido adicionado corretamente
    - 1 caso o produto já exista no estoque
    - 2 caso a barraca não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca deve existir em `lEstoque`
    - O produto não deve estar presente no estoque da barraca

--> Assertivas de saída:
    - O produto é inserido no mapa de produtos da barraca correspondente
*/
int adicionaProdutoNoEstoque(AuxEstoque infoEstoque);

/*
Objetivo: Alterar a quantidade de um produto no estoque de uma barraca.

Descrição:
1. Verifica se a barraca e o produto existem.
2. Soma a quantidade informada à quantidade atual do produto.
3. Se a quantidade final for negativa, ela é ajustada para 0.

Acoplamentos:

--> Parâmetros:
    AuxEstoque infoEstoque: estrutura com nome da barraca, produto e quantidade a adicionar (ou remover, se negativa).

--> Retornos:
    - 0 caso a operação tenha sido bem-sucedida
    - 1 caso a barraca não exista
    - 2 caso o produto não exista no estoque da barraca

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca e o produto devem existir

--> Assertivas de saída:
    - A quantidade do produto é alterada (mantida ≥ 0)
*/
int editarQuantidadeProduto(AuxEstoque infoEstoque);

/*
Objetivo: Alterar o preço de um produto no estoque de uma barraca.

Descrição:
1. Verifica se a barraca e o produto existem.
2. Atualiza o preço do produto com o valor informado.

Acoplamentos:

--> Parâmetros:
    AuxEstoque infoEstoque: estrutura com nome da barraca, produto e novo preço.

--> Retornos:
    - 0 caso o preço tenha sido alterado corretamente
    - 1 caso a barraca não exista
    - 2 caso o produto não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca e o produto devem existir

--> Assertivas de saída:
    - O preço do produto é atualizado
*/
int editarPrecoProduto(AuxEstoque infoEstoque);

/*
Objetivo: Exibir todos os itens do estoque de uma barraca.

Descrição:
1. Verifica se a barraca existe.
2. Exibe todos os produtos, suas quantidades e preços no terminal.

Acoplamentos:

--> Parâmetros:
    std::string barraca: nome da barraca a ser exibida.

--> Retornos:
    - 0 caso os produtos tenham sido exibidos corretamente
    - 1 caso a barraca não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca deve existir

--> Assertivas de saída:
    - Os dados dos produtos da barraca são mostrados no `std::cout`
*/
int mostrarItensNoEstoqueUmaBarraca(std::string barraca);

/*
Objetivo: Remover um produto específico do estoque de uma barraca.

Descrição:
1. Verifica se a barraca existe.
2. Remove o produto indicado do estoque da barraca.

Acoplamentos:

--> Parâmetros:
    std::string nomeBarraca: nome da barraca
    std::string nomeProduto: nome do produto a ser removido

--> Retornos:
    - 0 caso o produto tenha sido removido
    - 1 caso o produto não exista
    - 2 caso a barraca não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca deve existir
    - O produto deve estar no estoque da barraca

--> Assertivas de saída:
    - O produto é removido do mapa de produtos da barraca
*/
int excluiItemDoEstoque (std::string nomeBarraca, std::string nomeItem);

/*
Objetivo: Excluir completamente o estoque de uma barraca.

Descrição:
1. Remove a barraca e todos os seus produtos do mapa `lEstoque`.

Acoplamentos:

--> Parâmetros:
    std::string nomeBarraca: nome da barraca a ser removida

--> Retornos:
    - 0 caso o estoque tenha sido removido com sucesso
    - 1 caso a barraca não exista

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca deve existir

--> Assertivas de saída:
    - A barraca e seus produtos são removidos do sistema
*/
int excluiEstoque (std::string nomeBarraca);

/*
Objetivo: Verificar se um produto está disponível em uma barraca e obter suas informações.

Descrição:
1. Verifica se a barraca existe.
2. Procura o produto informado.
3. Caso o produto exista e a quantidade seja maior que 0, atualiza a estrutura `infoEstoque` com a quantidade e o preço.

Acoplamentos:

--> Parâmetros:
    AuxEstoque& infoEstoque: estrutura com nome da barraca e produto; será preenchida com quantidade e preço, se encontrado.

--> Retornos:
    - 0 caso o produto esteja disponível e as informações foram preenchidas
    - 1 caso a barraca não exista
    - 2 caso o produto não exista ou esteja com quantidade 0

Condições de acoplamento:

--> Assertivas de entrada:
    - A barraca deve existir
    - O nome do produto deve ser válido

--> Assertivas de saída:
    - A estrutura `infoEstoque` é preenchida com dados do produto, caso encontrado
*/
int confereNoEstoque(AuxEstoque& infoEstoque);


bool carregaEstoqueCSV(std::ifstream& arquivo);
bool salvaEstoqueCSV(std::ofstream& arquivo);


