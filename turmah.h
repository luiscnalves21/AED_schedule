//
// Created by gonca on 26/10/2022.
//

#ifndef PROJETO_AED_TURMAH_H
#define PROJETO_AED_TURMAH_H
#include<string>
#include<list>
#include"slot.h"
using namespace std;
class turmaH{
    public:
        void TurmaH(string codUC, string codTurma, list<slot> horarioUCturma);//Construtor
        string getCodUC();
        string getCodTurma();
        list<slot> getHorarioUCTurma();
    private:
        string codUC;
        string codTurma;
        list<slot> horarioUCturma;
};


#endif //PROJETO_AED_TURMAH_H
