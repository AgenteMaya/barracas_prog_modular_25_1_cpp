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

typedef struct produto Produto;

struct barraca
{
    std::string nome;
    tm horarioInicial;
    tm horarioFinal;
    size_t senha;
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

int atualizaBarraca (auxBarraca infoBarraca)
{
    auto resultado = lBarracas.find(infoBarraca.nome);
    if (resultado == lBarracas.end()) {
        return 1; 
    }

    resultado->second.horarioInicial = criarHorario(infoBarraca.horaInicial, infoBarraca.MinutoInicial);
    resultado->second.horarioFinal = criarHorario(infoBarraca.horaFinal, infoBarraca.MinutoFinal);
    resultado->second.senha = infoBarraca.senha;
    return 0;
}

int excluiBarraca (std::string nomeBarraca){
    
    auto resultado = lBarracas.erase(nomeBarraca);
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


int buscaConfirmBarraca(std::string nomeBarraca)
{
    auto resultado = lBarracas.find(nomeBarraca);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 
    return 0;
}

int buscaBarraca (auxBarraca& barraca)
{
    auto resultado = lBarracas.find(barraca.nome);

    if (resultado == lBarracas.end()) {
        return 1; 
    } 

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
        mostrarItensNoEstoqueUmaBarraca(it->second.nome);        
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
    mostrarItensNoEstoqueUmaBarraca(it->second.nome);        

    return 0;
}

int buscaConfirmaBarraca(std::string nomeBarraca)
{
    auto it = lBarracas.find(nomeBarraca);
    if (it == lBarracas.end()) {
        return 1;
    } 
    return 0;
}