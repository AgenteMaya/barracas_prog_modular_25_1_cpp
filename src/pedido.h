#include <string>

struct AuxPedido{
    std::string nomeBarraca;
    int cpfCliente;
    std::string nomeProduto;
    int qtd;
    std::string id; //vem vazio para ser preenchido. Se não vier vazio, é por algum motivo e esse será o id usado 
};

/*
Objetivo: Criar e registrar um novo pedido com base nas informações fornecidas.

Descrição:
1. Recebe os dados do pedido via struct `auxPedido`.
2. Gera um id automaticamente caso não seja fornecido.
3. Verifica se a barraca e o produto estão disponíveis no estoque.
4. Armazena o pedido na estrutura global `lPedidos`.

Acoplamentos:

--> Parâmetros:
    auxPedido infoPedido: estrutura com nome da barraca, produto, CPF do cliente, quantidade e id opcional.

--> Retornos:
    - 0: Pedido criado com sucesso.
    - 1: Falha ao inserir pedido (id duplicado).
    - 2: Barraca não existe (erro vindo de `confereNoEstoque`).
    - 3: Produto fora de estoque.

Condições de acoplamento:

--> Assertivas de entrada:
    - `infoPedido.nomeBarraca` não deve ser vazio.
    - `infoPedido.nomeProduto` não deve ser vazio.
    - `infoPedido.qtd` deve ser maior que 0.
    - `infoPedido.cpfCliente` deve ser positivo.
    - `infoPedido.id` pode ser vazio (caso em que será gerado).

--> Assertivas de saída:
    - O pedido é registrado na estrutura `lPedidos` com um id único.
    - Os dados inseridos correspondem ao cliente e produto informados.
*/
int criaPedido(AuxPedido infoPedido);

/*
Objetivo: Listar os pedidos finalizados de um cliente específico.

Descrição:
1. Verifica se o cliente está confirmado.
2. Percorre os pedidos e imprime no console os que estão finalizados.

Acoplamentos:

--> Parâmetros:
    int cpf: CPF do cliente.

--> Retornos:
    - 0: Busca realizada com sucesso.
    - 1: Cliente não está confirmado (`buscaConfirmCliente` retorna erro).

Condições de acoplamento:

--> Assertivas de entrada:
    - `cpf` deve ser um número válido e existente no sistema.

--> Assertivas de saída:
    - Os pedidos finalizados do cliente são exibidos no console.
*/
int buscaPedidoClienteFinalizado(int cpf);

/*
Objetivo: Listar os pedidos finalizados de um cliente específico.

Descrição:
1. Verifica se o cliente está confirmado.
2. Percorre os pedidos e imprime no console os que estão finalizados.

Acoplamentos:

--> Parâmetros:
    int cpf: CPF do cliente.

--> Retornos:
    - 0: Busca realizada com sucesso.
    - 1: Cliente não está confirmado (`buscaConfirmCliente` retorna erro).

Condições de acoplamento:

--> Assertivas de entrada:
    - `cpf` deve ser um número válido e existente no sistema.

--> Assertivas de saída:
    - Os pedidos finalizados do cliente são exibidos no console.
*/
int buscaPedidoClienteNFinalizado(int cpf);

/*
Objetivo: Editar um pedido existente, alterando a quantidade de um item ou adicionando um novo.

Descrição:
1. Localiza o pedido pelo id.
2. Verifica se ele já foi finalizado.
3. Atualiza a quantidade do item se já existir, ou adiciona o novo item.

Acoplamentos:

--> Parâmetros:
    auxPedido edicao: estrutura com id do pedido, nome do produto e nova quantidade.

--> Retornos:
    - 1: Pedido não encontrado.
    - 2: Produto não existia no pedido e foi adicionado.
    - 3: Produto já existia e teve a quantidade atualizada.
    - 4: Pedido já está finalizado e não pode ser editado.

Condições de acoplamento:

--> Assertivas de entrada:
    - `edicao.id` deve estar preenchido e corresponder a um pedido existente.
    - `edicao.qtd` deve ser maior que 0.

--> Assertivas de saída:
    - O conteúdo do pedido é alterado, mantendo a consistência da estrutura.
*/
int edicaoPedido(AuxPedido edicao);

/*
Objetivo: Finalizar um pedido existente e atualizar o estoque.

Descrição:
1. Localiza o pedido pelo id.
2. Verifica se já foi finalizado.
3. Confirma disponibilidade dos itens no estoque.
4. Atualiza o estoque com base na quantidade dos itens.
5. Marca o pedido como finalizado.

Acoplamentos:

--> Parâmetros:
    std::string idPedido: identificador do pedido a ser finalizado.

--> Retornos:
    - 0: Pedido finalizado com sucesso.
    - 1: Pedido não encontrado.
    - 2: Pedido já está finalizado.
    - 3: Estoque insuficiente para algum item.

Condições de acoplamento:

--> Assertivas de entrada:
    - `idPedido` deve ser um id válido existente em `lPedidos`.

--> Assertivas de saída:
    - O pedido é marcado como finalizado.
    - O estoque da barraca é reduzido conforme os itens do pedido.
*/
int finalizarPedido(std::string idPedido);

/*
Objetivo: Listar todos os pedidos finalizados de uma barraca específica.

Descrição:
1. Verifica se a barraca existe e está confirmada.
2. Percorre todos os pedidos e imprime os que estão associados à barraca e finalizados.

Acoplamentos:

--> Parâmetros:
    std::string barraca: nome ou identificador da barraca.

--> Retornos:
    - 0: Busca realizada com sucesso.
    - 1: Barraca não está confirmada (`buscaConfirmBarraca` retorna erro).

Condições de acoplamento:

--> Assertivas de entrada:
    - `barraca` deve ser uma string não vazia e válida.

--> Assertivas de saída:
    - Os pedidos finalizados da barraca são exibidos no console.
*/
int buscaPedidosBarraca(std::string id);
bool salvaPedidoCSV(std::ofstream& arquivo);
bool carregaPedidosCSV(std::ifstream& arquivo);
int buscaBarracaPedido(AuxPedido& pedidoProcurado);


