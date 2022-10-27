#include "ucturma.h"

UcTurma::UcTurma(const string& codUc, const string& codTurma) {
    codUc_ = codUc;
    codTurma_ = codTurma;
}

string UcTurma::getCodUc() const {
    return codUc_;
}

string UcTurma::getCodTurma() const {
    return codTurma_;
}
