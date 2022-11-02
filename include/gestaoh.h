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
        GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<vector<Pedido>> pedido, vector<pair<UcTurma, int>> numberOfStudentsPerUcTurma);

        // methods
        void lerClasses(); // lê o ficheiro classes.csv e guarda as informações num vector<TurmaH>
        void lerStudentClasses(); // lê o ficheiro student_classes.csv

        // draw methods
        void drawEstudantes() const; // desenha um set de estudantes
        void drawEstudante(const Student& estudante, bool header) const; // desenha um estudante, e caso seja true, desenha também o header
        void drawHorario() const; // desenha um vector de turmas
        void drawNumberOfStudentsPerUcTurma() const; // desenha o numero de estudantes por uc/turma
        static void drawPedido(); // desenha o pedido
        static void drawMenu(); // desenha o menu

        // getters
        set<Student> getEstudantes() const;
        vector<TurmaH> getHorario() const;
        queue<vector<Pedido>> getPedido() const; // ! FALTA IMPLEMENTAR !
        Student getSpecificStudent(int n) const; // return de um estudante específico de um set de estudantes
        vector<pair<UcTurma, int>> getNumberOfStudentsPerUcTurma() const;
        int getMaxLength() const; // return do tamanho máximo de um nome de estudante do set de estudantes

        // setters
        void setEstudantes(set<Student> estudantes);
        void setHorario(vector<TurmaH> horario);
        void setPedido(queue<vector<Pedido>> pedido);
        void setNumberOfStudentsPerUcTurma(vector<pair<UcTurma, int>> numberOfStudentsPerUcTurma);
        void setMaxLength(int maxLength);

        // other functions
        void addPedido(const vector<Pedido>& pedido); // ! FALTA IMPLEMENTAR !
        void processarPedidos();
        void addNumberOfStudentsPerUcTurma(const UcTurma& ucTurma);
    private:
        set<Student> estudantes_;
        vector<TurmaH> horario_;
        queue<vector<Pedido>> pedido_;
        vector<pair<UcTurma, int>> numberOfStudentsPerUcTurma_;
        int maxLength_ = 0;
};

#endif