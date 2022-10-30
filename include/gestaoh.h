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
        void lerClasses();
        void lerStudentClasses();

        // draw methods
        void drawEstudantes() const;
        void drawHorario() const;

        // getters
        set<Student> getEstudantes() const;
        vector<TurmaH> getHorario() const;
        queue<Pedido> getPedido() const;
        int getMaxLength() const;

        // setters
        void setEstudantes(set<Student> estudantes);
        void setHorario(vector<TurmaH> horario);
        void setPedido(queue<Pedido> pedido);
        void setMaxLength(int maxLength);

        // other functions
        void addPedido(Pedido pedido);
    private:
        set<Student> estudantes_;
        vector<TurmaH> horario_;
        queue<Pedido> pedido_;
        int maxLength_ = 0;
};

#endif