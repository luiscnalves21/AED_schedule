#include "../include/gestaoh.h"

GestaoH::GestaoH() {
    estudantes_ = set<Student> {};
    horario_ = vector<TurmaH> {};
    pedido_ = queue<Pedido> {};
}

GestaoH::GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<Pedido> pedido) {
    estudantes_ = estudantes;
    horario_ = horario;
    pedido_ = pedido;
}

set<Student> GestaoH::getEstudantes() const {
    return estudantes_;
}

vector<TurmaH> GestaoH::getHorario() const {
    return horario_;
}

queue<Pedido> GestaoH::getPedido() const {
    return pedido_;
}