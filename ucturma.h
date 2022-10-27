#ifndef UCTURMA_H
#define UCTURMA_H

#include<string>

using namespace std;

class UcTurma {
    public:
        // constructor
        UcTurma(const string& codUc, const string& codTurma);

        // accessors
        string getCodUc() const;
        string getCodTurma() const;

    private:
        string codUc_;
        string codTurma_;

};

#endif
