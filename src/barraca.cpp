/**
 * @author Mayara Ramos Damazio
 * @date 08/06/2025
 *
 */



#include "barraca.h"
#include "testeBarraca.h"

#include <map>
#include <utility>
#include <iostream>
#include <algorithm>


struct barraca{
    std::string nome;
    tm horarioInicial;
    tm horarioFinal;
    size_t senha;
    std::map<size_t, size_t> lProdutos; //<id do produto, qtdProduto>
};

typedef struct barraca Barraca;

static std::map<std::string, Barraca> lBarracas;

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
        return 1; 
    }
    
    resultado = lBarracas.find(infoBarraca.nome);
    if (resultado != lBarracas.end()) {
        return 2; 
    }

    auto barraca = lBarracas.extract(id);
    barraca.key() = infoBarraca.nome;

    Barraca novaBarraca{};
    novaBarraca.nome = infoBarraca.nome;
    novaBarraca.horarioInicial = criarHorario(infoBarraca.horaInicial, infoBarraca.MinutoInicial);
    novaBarraca.horarioFinal = criarHorario(infoBarraca.horaFinal, infoBarraca.MinutoFinal);
    novaBarraca.senha = infoBarraca.senha;

    barraca.mapped() = novaBarraca;

    lBarracas.insert(std::move(barraca));

    return 0;

}

int excluiBarraca (std::string id){
    
    auto resultado = lBarracas.erase(id);
    if (resultado) //se a chave existir
        return 0;
    return 1;
}


#ifdef TESTE_ON
void excluirTodasBarracas ()
{    
    lBarracas.clear();
}
#endif


int buscaBarraca (std::string id, auxBarraca& barraca)
{
    auto resultado = lBarracas.find(id);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 

    barraca.nome = resultado->second.nome;
    barraca.horaInicial = resultado->second.horarioInicial.tm_hour;
    barraca.MinutoInicial = resultado->second.horarioInicial.tm_min; 
    barraca.horaFinal = resultado->second.horarioFinal.tm_hour;
    barraca.MinutoFinal = resultado->second.horarioFinal.tm_min;
    barraca.senha = resultado->second.senha;   

    return 0;
}

int mostrarTodasBarracasEProdutos(){

    std::cout << lBarracas.size() << std::endl;
    if (lBarracas.empty()){
        std::cout << "Não há Barracas cadastradas. " << std::endl;
        return 1;
    }
        

    for(auto it = lBarracas.begin(); it != lBarracas.end(); it++)
    {
        std::cout << "Barraca " << it->second.nome << std::endl;
        std::cout << "Horários:  " << it->second.horarioInicial.tm_hour << ":" << it->second.horarioInicial.tm_min;
        std::cout << " até " << it->second.horarioFinal.tm_hour << ":" << it->second.horarioFinal.tm_min << std::endl;
        
        std::cout << "        Produtos: " << it->second.lProdutos.size() << " itens  " << std::endl;
        for(auto it2 = it->second.lProdutos.begin(); it2 != it->second.lProdutos.end(); it2++)
        {
            AuxProduto auxProduto;
            auto verifica = buscaProduto(it2->second, auxProduto);
            if (!verifica)
                std::cout << "                   " << auxProduto.nome << "  -  " << it2->second << "disponível(eis)" << std::endl;
        }
    }
    

    return 0;
}


int mostrarUmaBarraca(std::string id)
{
    auto it = lBarracas.find(id);
    if (it == lBarracas.end()) {
        return 1;
    } 

    std::cout << "Barraca " << it->second.nome << std::endl;
    std::cout << "Horários:  " << it->second.horarioInicial.tm_hour << ":" << it->second.horarioInicial.tm_min;
    std::cout << " até " << it->second.horarioFinal.tm_hour << " : " << it->second.horarioFinal.tm_min << std::endl;

    std::cout << "        Produtos: " << it->second.lProdutos.size() << "itens" << std::endl;
    for(auto it2 = it->second.lProdutos.begin(); it2 != it->second.lProdutos.end(); it2++)
    {
        AuxProduto auxProduto;
        auto verifica = buscaProduto(it2->first, auxProduto);
        if (!verifica)
            std::cout << "                   " << auxProduto.nome << "  -  " << it2->second << " disponível(eis)"  << std::endl;;
    }
    return 0;
}


int editarQuantidadeProduto(size_t idProduto, std::string idBarraca, int alteracao)
{
    auto it = lBarracas.find(idBarraca);
    if (it == lBarracas.end()) {
        return 1;
    } 

    auto it2 = it->second.lProdutos.find(idProduto);
    if (it2 == it->second.lProdutos.end()) {
        return 2;
    } 

    it2->second += alteracao;
    return 0;
}

int adicionaProdutoNoEstoque(size_t idProduto, int qtd, std::string idBarraca)
{   
    auto it = lBarracas.find(idBarraca);
    if (it == lBarracas.end()) {
        return 1;
    } 

    auto verifica = buscaConfirmProduto(idProduto);    
    if (verifica)
        return 2;
    
    auto resultado = it->second.lProdutos.emplace(idProduto, qtd);

    if (!resultado.second) {
        return 3; 
    }

    return 0;
}
