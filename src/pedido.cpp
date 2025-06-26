#include "pedido.h"
#include "testePedido.h"
#include "uuid.h"
#include <map>
#include <ctime>
#include <iostream>


struct Pedido{
    int cpfCliente;
    std::string nomeBarraca;
    bool verificaFinalizado;
    tm horarioPedido;
    std::string id;
    int preco;
    std::map<std::string, size_t> lItens; //<nome_item, qtd_item>
};

static std::map<std::string, Pedido> lPedidos;

std::string criaId()
{
    int valor{1};
    if (!lPedidos.empty()) 
        valor = std::stoi(lPedidos.rbegin()->first) + 1;
    return std::to_string(valor);
}

int criaPedido(auxPedido infoPedido)
{
    Pedido pedidoNovo{};
    pedidoNovo.cpfCliente = infoPedido.cpfCliente;

    if (infoPedido.id != "")
        pedidoNovo.id = infoPedido.id;
    else
    {
        pedidoNovo.id = UUID::generate();
        //pedidoNovo.id = criaId();        
    }
        
    pedidoNovo.verificaFinalizado = false;

    AuxEstoque item;
    item.nomeBarraca = infoPedido.nomeBarraca;
    item.nomeProduto = infoPedido.nomeProduto;
    auto verifica = confereNoEstoque(item);
    if (verifica)
        return verifica + 1; //retorna 2 se a barraca não existe e 3 se o produto está fora de estoque

    pedidoNovo.nomeBarraca = infoPedido.nomeBarraca;

    pedidoNovo.lItens.emplace( infoPedido.nomeProduto, infoPedido.qtd);

    pedidoNovo.preco = item.preco;

    //TODO caso em que verifica o horário da porra da criação do pedido (qm pensou nesta merda mesmo)? Não fui eu, óbvio
    //Não há verificação agora por que o horário só é necessário quando se vai fechar um pedido.

    auto resultado = lPedidos.emplace(pedidoNovo.id, pedidoNovo);
    if (!resultado.second)
        return 1;

    return 0;
}

 int buscaPedidoClienteNFinalizado(int cpf)
{
    auto verifica = buscaConfirmCliente(cpf);
    if (verifica)
        return 1;
    for(auto& pedido : lPedidos)
    {
        if (!pedido.second.verificaFinalizado && pedido.second.cpfCliente == cpf)
        {
            std::cout << "Pedido " << pedido.first << std::endl;
            std::cout << "Barraca escolhida: " << pedido.second.nomeBarraca << std::endl;
            std::cout << "Produtos: " << std::endl;
            for (auto& produto : pedido.second.lItens)
                std::cout << "           " <<  produto.first << " - " << produto.second << " qtd" << std::endl;

            std::cout << std::endl;
        }
    }
    return 0;
}

int edicaoPedido(auxPedido edicao)
{
    auto pedido = lPedidos.find(edicao.id);
    if (pedido == lPedidos.end())
        return 1;

    if (pedido->second.verificaFinalizado)
    {
        std::cout << "Pedido já finalizado. Não pode ser editado." << std::endl;
        return 4;
    } 

    AuxEstoque infoEstoque{};
    infoEstoque.nomeBarraca = edicao.nomeBarraca;
    infoEstoque.nomeProduto = edicao.nomeProduto;
    auto verifica = confereNoEstoque(infoEstoque);
    if (verifica)
        return verifica + 3; //retorna 2 se a barraca não existe e 3 se o produto está fora de estoque


    auto produto = pedido->second.lItens.find(edicao.nomeProduto);
    if (produto == pedido->second.lItens.end())
    {
        pedido->second.lItens.emplace(edicao.nomeProduto, edicao.qtd);
        return 2;
    }
    else
    {
        pedido->second.lItens[edicao.nomeProduto] = edicao.qtd;
        return 3;
    }
}

int finalizarPedido(std::string idPedido)
{
    auto pedido = lPedidos.find(idPedido);
    if (pedido == lPedidos.end())
        return 1;

    if (pedido->second.verificaFinalizado)
    {
        std::cout << "Pedido já finalizado. Não pode ser editado." << std::endl;
        return 2;
    }

    AuxEstoque infoEstoque;
    infoEstoque.nomeBarraca = pedido->second.nomeBarraca;
    for (auto& item : pedido->second.lItens)
    {
        infoEstoque.nomeProduto = item.first;
        confereNoEstoque(infoEstoque);
        if (static_cast<size_t>(infoEstoque.qtd) < item.second)
        {
            std::cout << "Barraca " << infoEstoque.nomeBarraca << " não tem quantidade de produto " << item.first << " suficiente. Olhe o estoque da barraca" << std::endl;
            return 3;
        }
    }

    pedido->second.verificaFinalizado = true;

    for (auto& item : pedido->second.lItens)
    {
        infoEstoque.nomeProduto = item.first;
        infoEstoque.qtd = item.second * -1;
        editarQuantidadeProduto(infoEstoque);        
    }

    return 0;
}


int buscaPedidoClienteFinalizado(int cpf)
{
    auto verifica = buscaConfirmCliente(cpf);
    if (verifica)
        return 1;
    for(auto& pedido : lPedidos)
    {
        if (pedido.second.verificaFinalizado && pedido.second.cpfCliente == cpf)
        {
            std::cout << "Pedido " << pedido.first << "feito no dia " << pedido.second.horarioPedido.tm_mday  << "/" << pedido.second.horarioPedido.tm_mon << "/" << pedido.second.horarioPedido.tm_year << std::endl;
            std::cout << "Barraca escolhida: " << pedido.second.nomeBarraca << std::endl;
            std::cout << "Produtos: ";
            for (auto& produto : pedido.second.lItens)
                std::cout << "           " <<  produto.first << " - " << produto.second << " qtd" << std::endl;

            std::cout << std::endl;
        }
    }
    return 0;
}

int buscaPedidosBarraca(std::string barraca)
{
    auto verifica = buscaConfirmBarraca(barraca);
    if (verifica)
        return 1;
    for(auto& pedido : lPedidos)
    {
        if (pedido.second.verificaFinalizado && pedido.second.nomeBarraca == barraca)
        {
            std::cout << "Pedido " << pedido.first << "feito no dia " << pedido.second.horarioPedido.tm_mday  << "/" << pedido.second.horarioPedido.tm_mon << "/" << pedido.second.horarioPedido.tm_year << std::endl;
            std::cout << "Produtos: ";
            for (auto& produto : pedido.second.lItens)
                std::cout << "           " <<  produto.first << " - " << produto.second << " qtd" << std::endl;

            std::cout << std::endl;
        }
    }
    return 0;
}

