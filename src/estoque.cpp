#ifdef TESTE_ON
    #include "testeEstoque.h"
#else
    #include "estoque.h"
    #include "barracaEstoque.h"
#endif
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

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
    std::cout << infoEstoque.nomeBarraca << std::endl;

    auto barraca = lEstoque.find(infoEstoque.nomeBarraca);
    if (barraca == lEstoque.end()) {
        return 1; 
    }

    std::cout << infoEstoque.nomeProduto << std::endl;
    auto produtoAchado = barraca->second.lProdutos.find(infoEstoque.nomeProduto);
    if (produtoAchado == barraca->second.lProdutos.end() || produtoAchado->second.qtd == 0){ 
        return 2;
    }
    
    infoEstoque.preco = produtoAchado->second.preco;
    infoEstoque.qtd = produtoAchado->second.qtd;
    return 0;
}

bool salvaEstoqueCSV(std::ofstream& arquivo) {
    if (!arquivo.is_open()) return false;

    for (const auto& par : lEstoque) {
        const Estoque& e = par.second;

        std::ostringstream produtosSerializados;
        for (auto it = e.lProdutos.begin(); it != e.lProdutos.end(); ++it) {
            const Produto& p = it->second;
            produtosSerializados << p.nome << ":" << p.qtd << ":" << p.preco;
            if (std::next(it) != e.lProdutos.end()) {
                produtosSerializados << ";";
            }
        }

        arquivo << e.nomeBarraca << ","
                << "\"" << produtosSerializados.str() << "\"" << std::endl;
    }

    return arquivo.good();
}

bool carregaEstoqueCSV(std::ifstream& arquivo) {
    if (!arquivo.is_open()) return false;

    std::string linha;
    bool carregouAlgum = false;

    while (std::getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string campo;
        Estoque e;

        // Nome da barraca
        if (!std::getline(ss, campo, ',')) continue;
        e.nomeBarraca = campo;

        // Produtos serializados
        if (!std::getline(ss, campo)) continue;

        if (!campo.empty() && campo.front() == '"' && campo.back() == '"') {
            campo = campo.substr(1, campo.length() - 2);
        }

        std::istringstream produtosStream(campo);
        std::string produtoStr;

        while (std::getline(produtosStream, produtoStr, ';')) {
            size_t pos1 = produtoStr.find(':');
            size_t pos2 = produtoStr.find(':', pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                Produto p;
                p.nome = produtoStr.substr(0, pos1);
                try {
                    p.qtd = std::stoi(produtoStr.substr(pos1 + 1, pos2 - pos1 - 1));
                    p.preco = std::stof(produtoStr.substr(pos2 + 1));
                } catch (...) {
                    continue; // erro de conversão
                }
                e.lProdutos[p.nome] = p;
            }
        }

        lEstoque[e.nomeBarraca] = e;
        carregouAlgum = true;
    }

    return carregouAlgum;
}
