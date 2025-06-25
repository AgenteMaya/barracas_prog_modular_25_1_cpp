#include "estoque.h"
#include "testeEstoque.h"
#include <map>
#include <iostream>

struct Produto{
    std::string nome;
    int qtd;
    float preco;
};

struct Estoque{
    std::string nomeBarraca;
    std::map<std::string, Produto> lProdutos; //nome do item, 
};

static std::map<std::string, Estoque> lEstoque;


int criaEstoque (std::string nomeBarraca)
{
    auto verifica = buscaConfirmaBarraca(nomeBarraca);
    if (verifica)
        return 2;

    Estoque novoEstoque{};
    novoEstoque.nomeBarraca = nomeBarraca; 

    auto resultado = lEstoque.emplace(nomeBarraca, novoEstoque);

    if (!resultado.second) {
        return 1; 
    }   

    return 0;
}

int adicionaProdutoNoEstoque(AuxEstoque infoEstoque)
{   
    auto verifica = buscaConfirmaBarraca(infoEstoque.nomeBarraca);
    if (verifica)
        return 2;

    auto resultado = lEstoque[infoEstoque.nomeBarraca].lProdutos.emplace(infoEstoque.nomeProduto, Produto {infoEstoque.nomeProduto, infoEstoque.qtd, infoEstoque.preco});

    if (!resultado.second) {
        return 1; 
    }

    return 0;
}

int editarQuantidadeProduto(AuxEstoque infoEstoque)
{
    auto it = lEstoque.find(infoEstoque.nomeBarraca);
    if (it == lEstoque.end()) {
        return 1;
    } 

    auto it2 = it->second.lProdutos.find(infoEstoque.nomeProduto);
    if (it2 == it->second.lProdutos.end()) {
        return 2;
    } 

    it2->second.qtd += infoEstoque.qtd;

    if (it2->second.qtd <0)
        it2->second.qtd = 0;
    return 0;
}

int editarPrecoProduto(AuxEstoque infoEstoque)
{
    auto it = lEstoque.find(infoEstoque.nomeBarraca);
    if (it == lEstoque.end()) {
        return 1;
    } 

    auto it2 = it->second.lProdutos.find(infoEstoque.nomeProduto);
    if (it2 == it->second.lProdutos.end()) {
        return 2;
    } 

    it2->second.qtd = infoEstoque.preco;
    return 0;
}

int mostrarItensNoEstoqueUmaBarraca(std::string barraca)
{
    auto it = lEstoque.find(barraca);
    if (it == lEstoque.end()) {
        return 1;
    } 

    std::cout << "        Produtos: " << it->second.lProdutos.size() << " itens" << std::endl;
    for (auto& produto : it->second.lProdutos)
    {
        std::cout << "                   " << produto.first << "  -  " << produto.second.qtd << " disponível(eis). Valor: " << produto.second.preco << std::endl;
    }
    return 0;
}

int excluiItemDoEstoque (std::string nomeBarraca, std::string nomeProduto)
{
    auto it = lEstoque.find(nomeBarraca);
    if (it == lEstoque.end()) {
        return 2;
    } 

    auto resultado = it->second.lProdutos.erase(nomeProduto);
    if (resultado) //se a chave existir
        return 0;
    return 1;
}

int excluiEstoque (std::string nomeBarraca)
{    
    auto resultado = lEstoque.erase(nomeBarraca);
    if (resultado) //se a chave existir
        return 0;
    return 1;
}

int confereNoEstoque(AuxEstoque& infoEstoque)
{
    auto barraca = lEstoque.find(infoEstoque.nomeBarraca);
    if (barraca == lEstoque.end()) {
        return 1; 
    }

    auto produtoAchado = barraca->second.lProdutos.find(infoEstoque.nomeProduto);
    if (produtoAchado == barraca->second.lProdutos.end() || produtoAchado->second.qtd == 0){ 
        return 2;
    }
    
    infoEstoque.preco = produtoAchado->second.preco;
    infoEstoque.qtd = produtoAchado->second.qtd;
    return 0;
}