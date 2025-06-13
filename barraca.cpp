/**
 * @date 08/06/2025
 */



#include "barraca.h"
#include "testeBarraca.h"

#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>


struct barraca{
    std::string nome;
    tm horarioInicial;
    tm horarioFinal;
    size_t senha;
    //size_t id;
    std::map<size_t, size_t> lProdutos; //<id do produto, qtdProduto>
};

typedef struct barraca Barraca;

static std::map<std::string, Barraca> lBarracas;


/* int criaId(){
    if (lBarracas.empty())
        return 1;
    auto itMaior = lBarracas.rend();
    return itMaior->first + 1;
};
 */

std::tm criarHorario(int hora, int minuto) {
    std::tm horario{};
    horario.tm_hour = hora;
    horario.tm_min = minuto;
    horario.tm_isdst = -1;    
    mktime(&horario); 
    return horario;
}

int criaBarraca (auxBarraca infoBarraca)
{
    Barraca novaBarraca{};
    novaBarraca.nome = infoBarraca.nome;
    novaBarraca.horarioInicial = criarHorario(infoBarraca.horaInicial, infoBarraca.MinutoInicial);
    novaBarraca.horarioFinal = criarHorario(infoBarraca.horaFinal, infoBarraca.MinutoFinal);
    novaBarraca.senha = infoBarraca.senha;

    auto resultado = lBarracas.emplace(novaBarraca.nome, novaBarraca);

    if (!resultado.second) {
        return 1; 
    }   
    return 0;
}

int atualizaBarraca (auxBarraca infoBarraca, std::string id)
{
    auto resultado = lBarracas.find(id);

    if (resultado == lBarracas.end()) {
        return 2; 
    } 

    auto retorno = excluiBarraca(id);

    if (!retorno) 
        retorno = criaBarraca(infoBarraca);
    
    return retorno;
}

int excluiBarraca (std::string id){
    auto resultado = lBarracas.erase(id);
    if (resultado)
        return 0;
    return 1;
}

int buscaBarraca (std::string id, auxBarraca& barraca)
{
    auto resultado = lBarracas.find(id);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 

    barraca.nome = resultado->second.nome;
    resultado->second.horarioInicial = criarHorario(barraca.horaInicial, barraca.MinutoInicial);
    resultado->second.horarioFinal = criarHorario(barraca.horaFinal, barraca.MinutoFinal);

    return 0;
}

int mostrarTodasBarracasEProdutos(){
    if (lBarracas.empty())
        return 1;

    for(auto it = lBarracas.begin(); it != lBarracas.end(); it++)
    {
        std::cout << "Barraca " << it->second.nome << std::endl;
        std::cout << "        Produtos: ";
        for(auto it2 = it->second.lProdutos.begin(); it2 != it->second.lProdutos.end(); it2++)
        {
            AuxProduto auxProduto;
            auto verifica = buscaProduto(it2->second, auxProduto);
            if (!verifica)
                std::cout << "                   " << auxProduto.nome << "  -  " << it2->first;
        }
    }

    return 0;
}

int mostrarUmaBarracaNome(std::string nome)
{
    auto it = std::find_if(lBarracas.begin(), lBarracas.end(), [&nome](const auto& par){
        return par.second.nome == nome;
    });

    if (it == lBarracas.end()) {
        return 1;
    } 

    std::cout << "Barraca " << it->second.nome << std::endl;
    std::cout << "Horários:  " << it->second.horarioInicial.tm_hour << ":" << it->second.horarioInicial.tm_min;
    std::cout << " até " << it->second.horarioFinal.tm_hour << " : " << it->second.horarioFinal.tm_min << std::endl;

    if (!it->second.lProdutos.empty())
    {
        std::cout << "        Produtos: ";
        for(auto it2 = it->second.lProdutos.begin(); it2 != it->second.lProdutos.end(); it2++)
        {
            AuxProduto auxProduto;
            auto verifica = buscaProduto(it2->first, auxProduto);
            if (!verifica)
                std::cout << "                   " << auxProduto.nome << "  -  " << it2->first;
        }
    }
    
    return 0;
}



int editarQuantidadeProduto(size_t idProduto, size_t idBarraca, int alteracao)
{
    auto it = lBarracas.find(idBarraca);
    if (it == lBarracas.end()) {
        return 1;
    } 

    auto it2 = it->second.lProdutos.find(idBarraca);
    if (it2 == it->second.lProdutos.end()) {
        return 2;
    } 

    it2->second += alteracao;
    return 0;
}

int adicionaProdutoNoEstoque(size_t idProduto, int qtd, size_t idBarraca)
{
    auto it = lBarracas.find(idBarraca);
    if (it == lBarracas.end()) {
        return 1;
    } 

    it->second.lProdutos.emplace(idProduto, qtd);

    return 0;
}

int main(){
    return 0;
}