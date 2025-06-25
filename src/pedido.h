#include <string>

struct auxPedido{
    std::string nomeBarraca;
    int cpfCliente;
    std::string nomeProduto;
    int qtd;
    std::string id; //vem vazio para ser preenchido. Se não vier vazio, é por algum motivo e esse será o id usado 
};

struct editaPedido{
    std::string id;
    std::string nomeProduto;
    int qtd;
};

struct auxPedidoPronto{
    std::string nomeBarraca;
    int cpfCliente;
};

typedef struct auxPedido AuxPedido;
typedef struct editaPedido EditaPedido;
typedef struct auxPedidoPronto auxPedidoPronto;


int criaPedido(auxPedido infoPedido);
int buscaPedidoClienteFinalizado(int cpf);
int buscaPedidoClienteNFinalizado(int cpf);
int edicaoPedido(auxPedido edicao);
int finalizarPedido(std::string idPedido);
int buscaPedidoClienteFinalizado(int cpf);
int buscaPedidosBarraca(std::string id);


