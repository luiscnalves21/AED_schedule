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

        // accessors
        set<Student> getEstudantes() const;
        vector<TurmaH> getHorario() const;
        queue<Pedido> getPedido() const;
    private:
        set<Student> estudantes_;
        vector<TurmaH> horario_;
        queue<Pedido> pedido_;
};

#endif