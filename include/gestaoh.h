#ifndef GESTAOH_H
#define GESTAOH_H

#include <string>
#include <set>
#include <vector>
#include <queue>
#include "student.h"
#include "turmah.h"
#include "pedido.h"

using namespace std;

class GestaoH {
    public:
        // constructors
        GestaoH(); // default constructor
        GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<Pedido> pedido);

        // methods
        void lerClasses(); // lê o ficheiro classes.csv e guarda as informações num vector<TurmaH>
        void lerStudentClasses(); // lê o ficheiro student_classes.csv

        // draw methods
        void drawEstudantes() const; // desenha um set de estudantes
        void drawEstudante(const Student& estudante, bool header, bool oneStudent) const; // desenha um estudante, e caso seja true, desenha também o header e o footer
        void drawHorario() const; // desenha um vector de turmas
        static void drawMenu(); // desenha o menu

        // getters
        set<Student> getEstudantes() const;
        vector<TurmaH> getHorario() const;
        queue<Pedido> getPedido() const; // ! FALTA IMPLEMENTAR !
        Student getSpecificStudent(int n) const; // return de um estudante específico de um set de estudantes
        int getMaxLength() const; // return do tamanho máximo de um nome de estudante do set de estudantes

        // setters
        void setEstudantes(set<Student> estudantes);
        void setHorario(vector<TurmaH> horario);
        void setPedido(queue<Pedido> pedido);
        void setMaxLength(int maxLength);

        // other functions
        void addPedido(const Pedido& pedido); // ! FALTA IMPLEMENTAR !
    private:
        set<Student> estudantes_;
        vector<TurmaH> horario_;
        queue<Pedido> pedido_;
        int maxLength_ = 0;
};

#endif