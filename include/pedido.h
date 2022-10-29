#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

using namespace std;

class Pedido {
    public:
        // constructor
        Pedido(const string& tipo, int turma, const string& uc);

        // accessors
        string getTipo() const;
        int getTurma() const;
        string getUc() const;
    private:
        string tipo_;   /* remover estudante turma/uc
                        * adicionar estudante turma/uc
                        * alterar turma/uc estudante
                        * alterar conjunto turmas/ucs estudante */
        int turma_;
        string uc_;
};

#endif
