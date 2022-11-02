#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

using namespace std;

class Pedido {
    public:
        // constructor
        Pedido(); // default constructor
        Pedido(int studentCode, const string& type, const string& initialClassCode, const string& finalClassCode_, const string& ucCode);

        // accessors
        int getStudentCode() const;
        string getType() const;
        string getInitialClassCode() const;
        string getFinalClassCode() const;
        string getUcCode() const;
    private:
        int studentCode_;
        string type_;   /* remover estudante turma/uc
                        * adicionar estudante turma/uc
                        * alterar turma/uc estudante
                        * alterar conjunto turmas/ucs estudante */
        string initialClassCode_;
        string finalClassCode_;
        string ucCode_;
};

#endif
