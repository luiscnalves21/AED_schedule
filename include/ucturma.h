#ifndef UCTURMA_H
#define UCTURMA_H

#include <string>

using namespace std;

class UcTurma {
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
    private:
        string ucCode_;
        string classCode_;

};

#endif
