#ifndef UCTURMA_H
#define UCTURMA_H

#include <string>

using namespace std;

class UcTurma {
    // overload operator < para comparar students pelo número de estudante e adicioná-los ao set
    friend bool operator<(const UcTurma& ucturma1, const UcTurma& ucturma2) {
        int uc1 = stoi(ucturma1.getUcCode().substr(ucturma1.getUcCode().size()-3, 3));
        int uc2 = stoi(ucturma2.getUcCode().substr(ucturma2.getUcCode().size()-3, 3));
        int tu1 = stoi(ucturma1.getClassCode().substr(ucturma1.getClassCode().size()-2, 2));
        int tu2 = stoi(ucturma2.getClassCode().substr(ucturma2.getClassCode().size()-2, 2));
        if (uc1 < uc2) return true;
        else if (uc1 == uc2) {
            if (tu1 < tu2) return true;
        }
        return false;
    }

    friend bool operator==(const UcTurma& ucturma1, const UcTurma& ucturma2) {
        int uc1 = stoi(ucturma1.getUcCode().substr(ucturma1.getUcCode().size()-3, 3));
        int uc2 = stoi(ucturma2.getUcCode().substr(ucturma2.getUcCode().size()-3, 3));
        int tu1 = stoi(ucturma1.getClassCode().substr(ucturma1.getClassCode().size()-2, 2));
        int tu2 = stoi(ucturma2.getClassCode().substr(ucturma2.getClassCode().size()-2, 2));
        return uc1 == uc2 && tu1 == tu2;
    }

    public:
        // constructor
        UcTurma(); // default constructor
        UcTurma(const string& ucCode, const string& classCode);

        // getters
        string getUcCode() const;
        string getClassCode() const;

        // setters
        void setUcCode(const string& ucCode);
        void setClassCode(const string& classCode);
        void addNumberOfStudents(); // ver para que é que serve
    private:
        string ucCode_;
        string classCode_;

};

#endif
