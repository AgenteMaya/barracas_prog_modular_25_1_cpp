#include "cliente.h"
#include "pedido.h"
#include "estoque.h"
#include "barraca.h"
#include <iostream>
#include <limits>

int verificaEntradaNum()
{
    if (std::cin.fail()) 
    {
        std::cout << "Dado inserido não é um número, preencha novamente os dados." << std::endl;
        std::cin.clear(); // limpa o estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta entrada inválida
        return 1;
    }
    return 0;
}

int verificaMinuto(int minuto)
{
    return(minuto >= 0 && minuto < 61);
}

int verificaHora(int hora)
{
    return(hora >= 0 && hora < 13);
}

int menuCliente(long long cpfCliente)
{
    int opcaoCliente = -1;
    while(opcaoCliente)
    {
        std::cout << " MENU CLIENTE" << std::endl;
        std::cout << "1. alterar informações" << std::endl;
        std::cout << "2. Criar Pedido" << std::endl;
        std::cout << "3. Olhar informações de todas as barracas" << std::endl;
        std::cout << "4. Olhar informacao de uma barraca específica" << std::endl;
        std::cout << "5. Olhar historico de pedidos finalizados" << std::endl;
        std::cout << "6. Olhar historico de pedidos não finalizados" << std::endl;
        std::cout << "7. Editar algum pedido não finalizado" << std::endl;
        std::cout << "8. Finalizar pedido" << std::endl;
        std::cout << "9. Excluir conta cliente" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcaoCliente;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcaoCliente) {
            case 1: {
                AuxCliente cliente;
                cliente.cpf = cpfCliente;
                std::cout << "Digite o novo nome: " << std::endl;
                std::getline(std::cin, cliente.nome);

                std::cout << "Digite a nova senha: " << std::endl;
                std::cin >> cliente.senha;
                if (verificaEntradaNum())
                    break;
                atualizaCliente(cliente);
                break;
            }
            case 2: {
                AuxPedido novoPedido;
                novoPedido.cpfCliente = cpfCliente;
                novoPedido.id = "";
                std::cout << "Digite o nome da barraca: " << std::endl;
                std::getline(std::cin, novoPedido.nomeBarraca);

                std::cout << "Digite o nome do produto: " << std::endl;
                std::getline(std::cin, novoPedido.nomeProduto);

                std::cout << "Digite a qtd do produto: " << std::endl;
                std::cin >> novoPedido.qtd;
                if (verificaEntradaNum())
                    break;

                auto verifica = criaPedido(novoPedido);

                if (verifica == 2)
                    std::cout << "Barraca informada não existe" << std::endl;
                
                else if (verifica == 3)
                    std::cout << "Produto fora de estoque" << std::endl;

                break;
            }
            case 3: {
                mostrarTodasBarracasEProdutos();
                break;
            }
            case 4: {
                std::string idBarraca;
                std::cout << "Digite o nome/id da barraca: ";
                std::cin >> idBarraca;
                mostrarUmaBarraca(idBarraca);
                break;
            }
            case 5: {
                buscaPedidoClienteFinalizado(cpfCliente);
                break;
            }
            case 6: {
                buscaPedidoClienteNFinalizado(cpfCliente);
                break;
            }
            case 7: {
                AuxPedido edicao;
                std::cout << "Digite o ID do pedido para editar: ";
                std::cin >> edicao.id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                buscaBarracaPedido(edicao);

                edicao.cpfCliente = cpfCliente;

                std::cout << "Digite o nome do item: " << std::endl;
                std::getline(std::cin, edicao.nomeProduto);

                std::cout << "Digite a qtd do produto: " << std::endl;
                std::cin >> edicao.qtd;
                if (verificaEntradaNum())
                    break;

                auto verifica = edicaoPedido(edicao);

                if (verifica == 5)
                std::cout << "Barraca informada não existe" << std::endl;
                
                else if (verifica == 6)
                    std::cout << "Produto fora de estoque" << std::endl;
                break;
            }
            case 8: {
                std::string id;
                std::cout << "Digite o ID do pedido para finalizar: ";
                std::cin >> id;
                finalizarPedido(id);
                break;
            }
            case 9:{
                excluiCliente(cpfCliente);
            }
            case 0:
                std::cout << "Saindo do menu cliente." << std::endl;
                break;
            default:
                std::cout << "Opção inválida." << std::endl;
                break;
        }
    }
    return 0;
    
}

int menuBarraca(std::string nomeBarraca)
{
    int opcaoBarraca = -1;
    while(opcaoBarraca)
    {
        std::cout << " MENU BARRACA" << std::endl;
        std::cout << "1. Alterar informações" << std::endl;
        std::cout << "2. Excluit barraca" << std::endl;
        std::cout << "3. Olhar informações de todas as barracas" << std::endl;
        std::cout << "4. Olhar informacao de uma barraca específica" << std::endl;
        std::cout << "5. Olhar historico de pedidos para a barraca" << std::endl;
        std::cout << "6. Adicionar produto no estoque" << std::endl;
        std::cout << "7. Editar quantidade de produto no estoque" << std::endl;
        std::cout << "10. Editar preço de produto no estoque" << std::endl;
        std::cout << "8. Mostrar itens no estoque" << std::endl;
        std::cout << "9. Excluir item do estoque" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcaoBarraca;
        std::cin.ignore();

        switch (opcaoBarraca) {
            case 1: {
                AuxBarraca info;
                info.nome = nomeBarraca;
                
                std::cout << "Insira a hora inicial de funcionamento da barraca" << std::endl;
                std::cin >> info.horaInicial;
                if (verificaEntradaNum() || !verificaHora(info.horaInicial))
                    break;

                std::cout << "Insira o minuto inicial de funcionamento da barraca" << std::endl;
                std::cin >> info.MinutoInicial;
                if (verificaEntradaNum() || !verificaMinuto(info.MinutoInicial))
                    break;

                std::cout << "Insira a hora final de funcionamento da barraca" << std::endl;
                std::cin >> info.horaFinal;
                if (verificaEntradaNum() || !verificaHora(info.horaInicial))
                    break;

                std::cout << "Insira o minuto final de funcionamento da barraca" << std::endl;
                std::cin >> info.MinutoFinal;
                if (verificaEntradaNum() || !verificaMinuto(info.MinutoInicial))
                    break;

                std::cout << "Insira sua senha:" << std::endl;
                std::cin >> info.senha;
                if (verificaEntradaNum())
                    break;

                atualizaBarraca(info);
                break;
            }
            case 2:
                excluiBarraca(nomeBarraca);
                break;
            case 3:
                mostrarTodasBarracasEProdutos();
                break;
            case 4:{
                std::string barraca;
                std::cout << "Insira o nome da barraca:" << std::endl;
                std::getline(std::cin >> std::ws, barraca);
                mostrarUmaBarraca(barraca);
                break;
            }
            case 5:
                buscaPedidosBarraca(nomeBarraca);
                break;
            case 6: {
                AuxEstoque info;
                info.nomeBarraca = nomeBarraca;
                std::cout << "Nome do produto: ";
                std::getline(std::cin, info.nomeProduto);
                std::cout << "Quantidade: ";
                std::cin >> info.qtd;
                std::cout << "Preço: ";
                std::cin >> info.preco;
                std::cin.ignore();
                adicionaProdutoNoEstoque(info);
                break;
            }
            case 7: {
                AuxEstoque info;
                info.nomeBarraca = nomeBarraca;
                std::cout << "Nome do produto: ";
                std::getline(std::cin, info.nomeProduto);
                std::cout << "Nova quantidade: ";
                std::cin >> info.qtd;
                std::cin.ignore();
                editarQuantidadeProduto(info);
                break;
            }
            case 8:
                mostrarItensNoEstoqueUmaBarraca(nomeBarraca);
                break;
            case 9: {
                std::string nomeProduto;
                std::cout << "Nome do produto: ";
                std::getline(std::cin, nomeProduto);
                excluiItemDoEstoque(nomeBarraca, nomeProduto);
                break;
            }
            case 10: {
                AuxEstoque info;
                info.nomeBarraca = nomeBarraca;
                std::cout << "Nome do produto: ";
                std::getline(std::cin, info.nomeProduto);
                std::cout << "Novo preco: ";
                std::cin >> info.preco;
                std::cin.ignore();
                editarPrecoProduto(info);
                break;
            }
            case 0:
                std::cout << "Saindo do menu da barraca..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida." << std::endl;
                break;
        }
    }
    return 0;
}

int exibirMenu() {
    int opcao = -1;
    while (opcao) {
        std::cout << " MENU PRINCIPAL" << std::endl;
        std::cout << "1. cadastrar cliente" << std::endl;
        std::cout << "2. Fazer login como cliente" << std::endl;
        std::cout << "3. Criar barraca" << std::endl;
        std::cout << "4. Fazer login como barraca" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:{
                AuxCliente novoCliente;
                std::cout << "Insira seu nome:" << std::endl;
                std::getline(std::cin >> std::ws, novoCliente.nome);

                std::cout << "Insira seu cpf (apenas números):" << std::endl;
                std::cin >> novoCliente.cpf;
                if (verificaEntradaNum())
                    break;

                std::cout << "Insira sua senha:" << std::endl;
                std::cin >> novoCliente.senha;
                if (verificaEntradaNum())
                    break;

                criaCliente(novoCliente);
                break;
            }
            case 2:
            {
                AuxCliente loginCliente;

                std::cout << "Insira seu cpf (apenas números):" << std::endl;
                std::cin >> loginCliente.cpf;
                if (verificaEntradaNum())
                    break;

                std::cout << "Insira sua senha:" << std::endl;
                std::cin >> loginCliente.senha;
                if (verificaEntradaNum())
                    break;
                
                if(fazerLoginCliente(loginCliente))
                {
                    std::cout << "Não foi possível fazer login com os dados fornecidos." << std::endl;
                    break;
                }
                menuCliente(loginCliente.cpf);
                break;
            }
            case 3:{
                AuxBarraca novaBarraca;
                std::cout << "Insira o nome da barraca:" << std::endl;
                std::getline(std::cin >> std::ws, novaBarraca.nome);

                std::cout << "Insira a hora inicial de funcionamento da barraca" << std::endl;
                std::cin >> novaBarraca.horaInicial;
                if (verificaEntradaNum() || !verificaHora(novaBarraca.horaInicial))
                    break;

                std::cout << "Insira o minuto inicial de funcionamento da barraca" << std::endl;
                std::cin >> novaBarraca.MinutoInicial;
                if (verificaEntradaNum() || !verificaMinuto(novaBarraca.MinutoInicial))
                    break;

                std::cout << "Insira a hora final de funcionamento da barraca" << std::endl;
                std::cin >> novaBarraca.horaFinal;
                if (verificaEntradaNum() || !verificaHora(novaBarraca.horaInicial))
                    break;

                std::cout << "Insira o minuto final de funcionamento da barraca" << std::endl;
                std::cin >> novaBarraca.MinutoFinal;
                if (verificaEntradaNum() || !verificaMinuto(novaBarraca.MinutoInicial))
                    break;

                std::cout << "Insira sua senha:" << std::endl;
                std::cin >> novaBarraca.senha;
                if (verificaEntradaNum())
                    break;

                criaBarraca(novaBarraca);
                break;
            }
            case 4:{
                AuxBarraca loginBarraca;

                std::cout << "Insira o nome da barraca:" << std::endl;
                std::getline(std::cin >> std::ws, loginBarraca.nome);

                std::cout << "Insira sua senha:" << std::endl;
                std::cin >> loginBarraca.senha;
                if (verificaEntradaNum())
                    break;
                
                if(fazerLoginBarraca(loginBarraca))
                {
                    std::cout << "Não foi possível fazer login com os dados fornecidos." << std::endl;
                    break;
                }
                menuBarraca(loginBarraca.nome);
                break;
            }
            case 0:
                break;
            default:
                std::cout << " Opcao inválida!" << std::endl;
        }

    }
    return 0;
}