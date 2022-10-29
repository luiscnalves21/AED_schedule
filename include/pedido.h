#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

using namespace std;

class Pedido {
    public:
        // constructor
        Pedido(const string& tipo, const string& turma, const string& uc);

        // accessors
        string getTipo() const;
        string getTurma() const;
        string getUc() const;
    private:
        string tipo_;   /* remover estudante turma/uc
                        * adicionar estudante turma/uc
                        * alterar turma/uc estudante
                        * alterar conjunto turmas/ucs estudante */
        string turma_;
        string uc_;
};

#endif
