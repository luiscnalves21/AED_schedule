#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include<list>
#include<string>
#include "ucturma.h"

using namespace std;

class Student {
    public:
        // constructor
        Student(int code, const string& name, list<UcTurma> turmas);

        // accessors
        string getName() const;
        int getCode() const;
        list<UcTurma> getTurmas() const;

    private:
        int code_;
        string name_;
        list<UcTurma> turmas_;
};

#endif
