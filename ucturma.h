//
// Created by gonca on 26/10/2022.
//

#ifndef PROJETO_AED_UCTURMA_H
#define PROJETO_AED_UCTURMA_H
#include<string>
using namespace std;
class UCTURMA{
    public:
        void ucTurma(string codUC, string codTurma);// Construtor
        string getCodUC();
        string getCodTurma();
    private:
        string codUC;
        string codTurma;

};
#endif //PROJETO_AED_UCTURMA_H
