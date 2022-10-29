#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

using namespace std;

class Pedido {
    public:
        // constructor
        Pedido(int studentCode, const string& tipo, const string& codTurmaInicial, const string& codTurmaFinal, const string& codUc);

        // accessors
        int getStudentCode() const;
        string getTipo() const;
        string getCodTurmaInicial() const;
        string getCodTurmaFinal() const;
        string getCodUc() const;
    private:
        int studentCode_;
        string tipo_;   /* remover estudante turma/uc
                        * adicionar estudante turma/uc
                        * alterar turma/uc estudante
                        * alterar conjunto turmas/ucs estudante */
        string codTurmaInicial_;
        string codTurmaFinal_;
        string codUc_;
};

#endif
