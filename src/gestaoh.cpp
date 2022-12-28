#include "../include/gestaoh.h"
#include "../include/menu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>


GestaoH::GestaoH() {
    estudantes_ = set<Student> {};
    horario_ = vector<TurmaH> {};
    pedido_ = queue<vector<Pedido>> {};
    numberOfStudentsPerUcTurma_ = vector<pair<UcTurma, int>> {};
}


/**
 * Função que efetua a leitura do ficheiro "classes.csv" e preenche o vetor horario que contém o horário de todas as turmas nas respetivas unidades curriculares.
 * Complexidade Temporal O(n*log(n))
 */
void GestaoH::lerClasses() {
    string line1, line2, temp, word;
    string classCode1, classCode2, ucCode1, ucCode2, weekday, sstartHour, sduration, type, tempClassCode, tempUcCode;
    double startHour, duration;
    Slot aux;
    vector<TurmaH> horario; // criar vetor de ucCode/classCode e uma list<Slot>
    string ficheiro = "../classes.csv";
    ifstream ifs1, ifs2;
    list<Slot> slot; // criar lista de slots para cada ucCode/classCode
    ifs1.open(ficheiro, ios::in);
    getline(ifs1, temp);
    // objetivo aqui é fazer dois ciclos para correr o ficheiro completo
    // visto que as mesmas ucCode/classCode não estão seguidas no ficheiro
    while(getline(ifs1, line1)) {
        stringstream s1(line1);
        getline(s1, classCode1, ','), getline(s1, ucCode1, ','), getline(s1, weekday, ','), getline(s1, sstartHour, ','), getline(s1, sduration, ','), getline(s1, type, '\r');
        startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
        aux = Slot(weekday, startHour, duration, type); // cria slot
        slot.push_back(aux); // adiciona slot à list<Slot>
        ifs2.open(ficheiro, ios::in);
        getline(ifs2, temp);
        while (getline(ifs2, line2)) {
            stringstream s2(line2);
            getline(s2, classCode2, ','), getline(s2, ucCode2, ','), getline(s2, weekday, ','), getline(s2, sstartHour, ','), getline(s2, sduration, ','), getline(s2, type, '\r');
            if (line1 != line2 && classCode1 == classCode2 && ucCode1 == ucCode2) { // verificar se é o mesmo par ucCode/classCode
                startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
                aux = Slot(weekday, startHour, duration, type); // cria slot
                slot.push_back(aux); // adiciona slot à list<Slot>
            }
        }
        ifs2.close(); // fechar o ficheiro para podermos abri-lo novamente desde o início
        TurmaH turmaH(ucCode1, classCode1, slot); // criar uma TurmaH com as informações todas
        horario.push_back(turmaH); // fazer push da TurmaH para o vector<TurmaH>
        slot = {}; // esvaziar a lista de slots para começar de novo
    }
    setHorario(horario); // povoar o vector<TurmaH>
}
/**
 * Função que efetua a leitura do ficheiro "students_classes.csv" e preenche o set estudantes onde se encontra o código e o nome de estudantes e a lista de unidades curriculares e respetivas turmas de cada um.
 * Complexidade Temporal O(log n)
 */
void GestaoH::lerStudentClasses() {
    string line, temp, word, sstudentCode, studentName, ucCode, classCode, tempStudentName; // tempStudentName para guardar o nome estudante anterior
    int tempSstudentCode; // para guardar o código do estudante anterior
    set<Student> estudantes; // criar set de estudantes
    list<UcTurma> listaUcTurma; // criar lista de ucTurma para cada estudante
    UcTurma ucTurma; // criar UcTurma para cada conjunto de ucCode/classCode
    vector<pair<UcTurma, int>> studentsPerUcTurma;
    string ficheiro = "../students_classes.csv";
    ifstream ifs;
    ifs.open(ficheiro, ios::in); // abre ficheiro
    getline(ifs, temp); // passa a primeira linha à frente
    // como as cadeiras/turmas de cada estudante estão seguidas
    // só precisamos de fazer um ciclo
    while(getline(ifs, line)){
        stringstream s(line);
        getline(s, sstudentCode, ','), getline(s, studentName, ','), getline(s, ucCode, ','), getline(s, classCode, '\r');
        int studentCode = stoi(sstudentCode); // converter para int o código do estudante
        if (tempStudentName != studentName && !tempStudentName.empty()) { // esta condição serve para ignorarmos a primeira iteração e para verificarmos se já mudou para outro estudante
            Student estudante(tempSstudentCode, tempStudentName, listaUcTurma); // criar um objeto estudante
            estudantes.insert(estudante); // adicionar esse objeto estudante ao set<Student>
            listaUcTurma = {}; // esvaziar a list<UcTurma>
            // o próximo if é só para determinar o tamanho do maior nome de um estudante
            if (tempStudentName.length() > getMaxLength()) {
                setMaxLength((int)tempStudentName.length());
            }
        }
        UcTurma aux;
        bool verifyUcTurma = false;
        for (pair<UcTurma, int>& i : studentsPerUcTurma) { // percorre o vetor de estudantes por turma
            if (classCode == i.first.getClassCode() && ucCode == i.first.getUcCode()) { // verifica se a ucturma já está no vetor
                i.second++; // se sim, adiciona mais um estudante
                verifyUcTurma = true;
                break;
            }
        }
        if(!verifyUcTurma) { // se não, cria uma ucturma e coloca no vetor
            aux.setUcCode(ucCode);
            aux.setClassCode(classCode);
            pair<UcTurma, int> numberOfStudent = {aux, 1};
            studentsPerUcTurma.push_back(numberOfStudent);
        }
        ucTurma.setUcCode(ucCode); // insere o ucCode
        ucTurma.setClassCode(classCode); // insere o classCode
        listaUcTurma.push_back(ucTurma); // adiciona o conjunto ucCode/classCode à list<UcTurma>
        tempStudentName = studentName; // muda o nome do estudante temporário para o estudante atual
        tempSstudentCode = studentCode; // muda o número do estudante temporário para o estudante atual
    }
    if (!listaUcTurma.empty()) {
        Student estudante(tempSstudentCode, tempStudentName, listaUcTurma); // criar um objeto estudante
        estudantes.insert(estudante); // adicionar esse objeto estudante ao set<Student>
        if (tempStudentName.length() > getMaxLength()) {
            setMaxLength((int)tempStudentName.length());
        }
    }
    setNumberOfStudentsPerUcTurma(studentsPerUcTurma); // povoar o vetor<pair<UcTurma, int>>
    setEstudantes(estudantes); // povoar o set<Student>
}


/**
 * Função para ajudar a centralizar textos.
 * @param n
 * @param v
 * @return
 */
pair<int, int> auxCenterDraw(int n, bool v) {
    int pad1 = n;
    int pad2;
    if (v) {
        pad2 = pad1+1;
    }
    else {
        pad2 = pad1;
    }
    return pair<int, int> {pad1, pad2};
}

/**
 * Ajuda a desenhar as horas das slots.
 * @param n
 */
void auxHourDraw(double n) {
    bool flag_decimal = true;
    bool flag_two_digits = false;

    if(ceil(n) == floor(n)) flag_decimal = false;
    if (n >= 10.0) flag_two_digits = true;

    if (flag_two_digits && flag_decimal) cout << "   " << n << "   |";
    else if (flag_two_digits) cout << "    " << n << "    |";
    else if (flag_decimal) cout << "   " << n << "    |";
    else cout << "    " << n << "     |";
}

/**
 * Ajuda a desenhar o tipo das slots.
 * @param type
 */
void auxTypeDraw(const string& type) {
    switch (type.length()) {
        case 1:
            cout << "   " << type << "   |\n";
            break;
        case 2:
            cout << "   " << type << "  |\n";
            break;
    }
}

/**
 * Função desenha um gráfico com um bool header se for o primeiro estudante da lista a aparecer ou bool simple se for necessário só imprimir o estudante.
 * Complexidade Temporal O(n)
 * @param estudante
 * @param header
 * @param simple
 */
void GestaoH::drawEstudante(const Student& estudante, bool header, bool simple) const {
    // desenha o cabeçalho quando é o primeiro estudante
    if (header) {
        if (simple) {
            cout << "\n+-------------+---------------------------+\n"
                    "| StudentCode |        StudentName        |\n"
                    "+-------------+---------------------------+\n";
        }
        else {
            cout << "\n+-------------+---------------------------+----------+-----------+\n"
                    "| StudentCode |        StudentName        |  UcCode  | ClassCode |\n"
                    "+-------------+---------------------------+----------+-----------+\n";
        }
    }
    // apresenta as informações relativas a um estudante
    cout << "|  " << estudante.getCode() << "  | ";
    pair<int, int> pad = auxCenterDraw(getMaxLength()-(int)estudante.getName().length(), (int)estudante.getName().length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << estudante.getName();
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    if (!simple) {
        int c = 0;
        list<UcTurma> classUc = estudante.getTurmas();
        for (const UcTurma &u: classUc) {
            if (c > 0) {
                cout << "|             |                           ";
            }
            cout << "| " << u.getUcCode() << " |  " << u.getClassCode() << "  |\n";
            c++;
        }
    }
    else {
        cout << "|\n";
    }
    // desenha o rodapé
    if (simple) {
        for (int i = 0; i < 15+getMaxLength(); i++) {
            if (i == 0 || i == 13) cout << "+";
            cout << "-";
            if (i == 14+getMaxLength()) cout << "+\n";
        }
    }
    else {
        for (int i = 0; i < 36+getMaxLength(); i++) {
            if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
            cout << "-";
            if (i == 35+getMaxLength()) cout << "+\n";
        }
    }
}

/**
 * O mesmo que a função drawEstudante, mas com um loop para fazer todos os estudantes.
 * Complexidade Temporal O(n^2)
 * @param estudantes
 * @param simple
 */
void GestaoH::drawEstudantes(set<Student> estudantes, bool simple) const {
    if (estudantes.empty()) {
        estudantes = getEstudantes();
    }
    int v = 1;
    for (const Student& s : estudantes) {
        drawEstudante(s, v, simple);
        v = 0;
    }
}
/**
 * Função que desenha o horário de uma unidade curricular e respetiva turma.
 * Complexidade Temporal O(n^3)
 */
void GestaoH::drawHorario() const {
    vector<TurmaH> horario = getHorario();
    cout << "\n+----------+-----------+-------------+----------+----------+-------+\n"
            "|  UcCode  | ClassCode |   Weekday   | Start H. | Final H. |  Type |\n"
            "+----------+-----------+-------------+----------+----------+-------+\n";
    for (const TurmaH& s : horario) {
        if (s.getUcCode().length() == 5) cout << "|  " << s.getUcCode() << "   |  ";
        else cout << "| " << s.getUcCode() << " |  ";
        cout << s.getClassCode() << "  |  ";
        int c = 0;
        list<Slot> slot = s.getHorarioUcClass();
        for (const Slot& u : slot) {
            if (c > 0) {
                cout << "|          |           |  ";
            }
            pair<int, int> pad = auxCenterDraw(9-(int)u.getWeekday().length(), (int)u.getWeekday().length()%2 == 1);
            for (int f = 0; f < pad.first; f++) {
                cout << " ";
                ++f;
            }
            cout << u.getWeekday();
            for (int e = 0; e < pad.second; e++) {
                cout << " ";
                ++e;
            }
            cout << " |";
            auxHourDraw(u.getStartHour());
            auxHourDraw(u.getFinalHour());
            auxTypeDraw(u.getType());
            c++;
        }
        for (int i = 0; i < 61; i++) {
            if (i == 0 || i == 10 || i == 21 || i == 34 || i == 44 || i == 54) cout << "+";
            cout << "-";
            if (i == 60) cout << "+\n";
        }
    }
}
/**
 * Função de binary search.
 * Complexidade Temporal O(log n)
 * @param v
 * @param key
 * @return key if found, -1 if not found
 */
int binarySearch(const vector<TurmaH>& v, const TurmaH& key) {
    int low = 0, high = (int)v.size()-1;
    while (low <= high) {
        int middle = low+(high-low)/2;
        if (key < v[middle]) high = middle-1;
        else if (key == v[middle]) return middle;
        else low = middle+1;
    }
    return -1;
}
/**
 * Cada dia é representado por um vetor e os blocos de aulas serão inseridos no respetivo vetor.
 * Complexidade Temporal O(1)
 * @param n1
 * @param tab1
 * @param tab2
 * @param tab3
 * @param tab4
 * @param tab5
 * @param dBlocos
 * @param tBlocos
 * @param qBlocos
 * @param s
 * @param tempTurma
 */
void inserir(int n1, vector<string>& tab1, vector<string>& tab2, vector<string>& tab3, vector<string>& tab4, vector<string>& tab5, bool dBlocos, bool tBlocos, bool qBlocos, const Slot& s, const TurmaH& tempTurma) {
    if (s.getWeekday() == "Monday") {
        tab1[n1] = " " + tempTurma.getUcCode() + " ";
        tab1[n1+1] = " " + tempTurma.getClassCode() + "  ";
        if (s.getType().length() == 1) tab1[n1+2] = "    " + s.getType() + "     ";
        else tab1[n1+2] = "    " + s.getType() + "    ";
        if (tBlocos) {
            tab1[n1+3] = "          ";
            tab1[n1+4] = "          ";
        }
        else if (qBlocos) {
            tab1[n1+3] = "          ";
            tab1[n1+4] = "          ";
            tab1[n1+5] = "          ";
            tab1[n1+6] = "          ";
        }
    }
    else if (s.getWeekday() == "Tuesday") {
        tab2[n1] = " " + tempTurma.getUcCode() + " ";
        tab2[n1+1] = " " + tempTurma.getClassCode() + "  ";
        if (s.getType().length() == 1) tab2[n1+2] = "    " + s.getType() + "     ";
        else tab2[n1+2] = "    " + s.getType() + "    ";
        if (tBlocos) {
            tab2[n1+3] = "          ";
            tab2[n1+4] = "          ";
        }
        else if (qBlocos) {
            tab2[n1+3] = "          ";
            tab2[n1+4] = "          ";
            tab2[n1+5] = "          ";
            tab2[n1+6] = "          ";
        }
    }
    else if (s.getWeekday() == "Wednesday") {
        tab3[n1] = " " + tempTurma.getUcCode() + " ";
        tab3[n1+1] = " " + tempTurma.getClassCode() + "  ";
        if (s.getType().length() == 1) tab3[n1+2] = "    " + s.getType() + "     ";
        else tab3[n1+2] = "    " + s.getType() + "    ";
        if (tBlocos) {
            tab3[n1+3] = "          ";
            tab3[n1+4] = "          ";
        }
        else if (qBlocos) {
            tab3[n1+3] = "          ";
            tab3[n1+4] = "          ";
            tab3[n1+5] = "          ";
            tab3[n1+6] = "          ";
        }
    }
    else if (s.getWeekday() == "Thursday") {
        tab4[n1] = " " + tempTurma.getUcCode() + " ";
        tab4[n1+1] = " " + tempTurma.getClassCode() + "  ";
        if (s.getType().length() == 1) tab4[n1+2] = "    " + s.getType() + "     ";
        else tab4[n1+2] = "    " + s.getType() + "    ";
        if (tBlocos) {
            tab4[n1+3] = "          ";
            tab4[n1+4] = "          ";
        }
        else if (qBlocos) {
            tab4[n1+3] = "          ";
            tab4[n1+4] = "          ";
            tab4[n1+5] = "          ";
            tab4[n1+6] = "          ";
        }
    }
    else if (s.getWeekday() == "Friday") {
        tab5[n1] = " " + tempTurma.getUcCode() + " ";
        tab5[n1+1] = " " + tempTurma.getClassCode() + "  ";
        if (s.getType().length() == 1) tab5[n1+2] = "    " + s.getType() + "     ";
        else tab5[n1+2] = "    " + s.getType() + "    ";
        if (tBlocos) {
            tab5[n1+3] = "          ";
            tab5[n1+4] = "          ";
        }
        else if (qBlocos) {
            tab5[n1+3] = "          ";
            tab5[n1+4] = "          ";
            tab5[n1+5] = "          ";
            tab5[n1+6] = "          ";
        }
    }
}
/**
 * Desenha o horário de um estudante.
 * Complexidade Temporal O(n^3)
 * @param estudante
 */
void GestaoH::drawHorarioEstudante(const Student& estudante) const {
    list<UcTurma> turmasEstudante = estudante.getTurmas(); // turmas do estudante
    vector<TurmaH> turmasGerais = horario_; // todas as turmas
    sort(turmasGerais.begin(), turmasGerais.end()); // ordenar turmas gerais
    vector<pair<Slot, UcTurma>> verifySobr;
    vector<pair<Slot, UcTurma>> sobr; // vector com as slots Ts sobrepostas
    int h1 = 8, h2 = 8;
    string zero = ":00", trinta = ":30", hifen = "-", hifens10 = "----------", hifens11 = "-----------", mais = "+";
    bool v, dBlocos, tBlocos, qBlocos;
    int n;
    bool verTP = false, verT = false; // verificar se há sobreposição
    string frase;
    vector<string> tab1(48, hifens10), tab2(48, hifens10), tab3(48, hifens10), tab4(48, hifens10), tab5(48, hifens10);
    for (const UcTurma& turma : turmasEstudante) {
        TurmaH tempTurma(turma.getUcCode(), turma.getClassCode(), {});
        n = binarySearch(turmasGerais, tempTurma); // return do indice da ucturma
        tempTurma = turmasGerais[n];
        for (const Slot &s: tempTurma.getHorarioUcClass()) {
            pair<Slot, UcTurma> aux;
            for (const pair<Slot, UcTurma> &sl: verifySobr) {
                if ((s.getStartHour() >= sl.first.getStartHour() && s.getStartHour() < sl.first.getFinalHour() && s.getWeekday() == sl.first.getWeekday()) || (s.getFinalHour() > sl.first.getStartHour() && s.getFinalHour() <= sl.first.getFinalHour() && s.getWeekday() == sl.first.getWeekday())) {
                    if ((s.getType() == "TP" || s.getType() == "PL") && (sl.first.getType() == "TP" || sl.first.getType() == "PL")) {
                        verTP = true;
                        break;
                    }
                    else if (s.getType() == "T" && (sl.first.getType() == "TP" || sl.first.getType() == "PL")) {
                        aux.first = s;
                        aux.second = UcTurma(turma.getUcCode(), turma.getClassCode());
                        sobr.push_back(aux);
                        verT = true;
                        frase = "\n! AVISO ! -> Existe sobreposicao de aulas T com aulas TP ou PL, e por isso as aulas T nao estao representadas.\n";
                    }
                    else {
                        aux.first = s;
                        aux.second = UcTurma(turma.getUcCode(), turma.getClassCode());
                        sobr.push_back(aux);
                        aux = sl;
                        sobr.push_back(aux);
                        verT = true;
                        frase = "\n! AVISO ! -> Existe sobreposicao de aulas T com aulas T, e por isso essas aulas nao estao representadas.\n";
                    }
                }
            }
            if (verTP) {
                break;
            } else {
                aux.first = s;
                aux.second = UcTurma(turma.getUcCode(), turma.getClassCode());
                verifySobr.push_back(aux);
            }
        }
    }
    if (!verTP) {
        cout << "\n+-----------+----------+----------+----------+----------+----------+\n"
                "|   Horas   | Segunda  |   Terca  |  Quarta  |  Quinta  |   Sexta  |\n"
                "+-----------+----------+----------+----------+----------+----------+\n";
        for (int i = 0; i < 24; i++) {
            h2 += i % 2;
            v = i%2;
            for (const UcTurma& turma : turmasEstudante) {
                TurmaH tempTurma(turma.getUcCode(), turma.getClassCode(), {});
                n = binarySearch(turmasGerais, tempTurma); // return do indice da ucturma
                tempTurma = turmasGerais[n];
                for (const Slot& s : tempTurma.getHorarioUcClass()) {
                    if (verT) {
                        bool dentro = false;
                        for (const pair<Slot, UcTurma>& sl : sobr) {
                            if (s.getType() == sl.first.getType() && s.getWeekday() == sl.first.getWeekday() && s.getStartHour() == sl.first.getStartHour() && s.getFinalHour() == sl.first.getFinalHour()) dentro = true;
                        }
                        if (!dentro) {
                            if (s.getFinalHour()-s.getStartHour() == 1.0) {
                                dBlocos = true;
                                tBlocos = false;
                                qBlocos = false;
                            }
                            else if (s.getFinalHour()-s.getStartHour() == 1.5) {
                                dBlocos = false;
                                tBlocos = true;
                                qBlocos = false;
                            }
                            else if (s.getFinalHour()-s.getStartHour() == 2.0) {
                                dBlocos = false;
                                tBlocos = false;
                                qBlocos = true;
                            }
                            int n1 = 0;
                            if (v && s.getStartHour() == (h1 + 0.5)) {
                                if (h1 >= 16) {
                                    n1 += 32;
                                }
                                n1 += (h1%8)*4+2;
                                inserir(n1, tab1, tab2, tab3, tab4, tab5, dBlocos, tBlocos, qBlocos, s, tempTurma);
                            }
                            else if (s.getStartHour() == (h1 + 0.0)) {
                                if (h1 >= 16) {
                                    n1 += 32;
                                }
                                n1 += (h1%8)*4;
                                inserir(n1, tab1, tab2, tab3, tab4, tab5, dBlocos, tBlocos, qBlocos, s, tempTurma);
                            }
                        }
                    }
                    else {
                        if (s.getFinalHour()-s.getStartHour() == 1.0) {
                            dBlocos = true;
                            tBlocos = false;
                            qBlocos = false;
                        }
                        else if (s.getFinalHour()-s.getStartHour() == 1.5) {
                            dBlocos = false;
                            tBlocos = true;
                            qBlocos = false;
                        }
                        else if (s.getFinalHour()-s.getStartHour() == 2.0) {
                            dBlocos = false;
                            tBlocos = false;
                            qBlocos = true;
                        }
                        int n1 = 0;
                        if (v && s.getStartHour() == (h1 + 0.5)) {
                            if (h1 >= 16) {
                                n1 += 32;
                            }
                            n1 += (h1%8)*4+2;
                            inserir(n1, tab1, tab2, tab3, tab4, tab5, dBlocos, tBlocos, qBlocos, s, tempTurma);
                        }
                        else if (s.getStartHour() == (h1 + 0.0)) {
                            if (h1 >= 16) {
                                n1 += 32;
                            }
                            n1 += (h1%8)*4;
                            inserir(n1, tab1, tab2, tab3, tab4, tab5, dBlocos, tBlocos, qBlocos, s, tempTurma);
                        }
                    }
                }
            }
            h1 += i%2;
        }
        h1 = 8, h2 = 8;
        for (int i = 0; i < 24; i++) {
            h2 += i%2;
            v = i%2;
            if (h1 >= 10 && h2 >= 10) {
                if (v) cout << "|" << h1 << trinta << hifen << h2 << zero << "|";
                else cout << "|" << h1 << zero << hifen << h2 << trinta << "|";
            }
            else if (h2 >= 10) {
                if (v) cout << "|0" << h1 << trinta << hifen << h2 << zero << "|";
                else cout << "|0" << h1 << zero << hifen << h2 << trinta << "|";
            }
            else {
                if (v) cout << "|0" << h1 << trinta << hifen << "0" << h2 << zero << "|";
                else cout << "|0" << h1 << zero << hifen << "0" << h2 << trinta << "|";
            }

            // desenhar as "slots"
            cout << tab1[i*2] << mais << tab2[i*2] << mais << tab3[i*2] << mais << tab4[i*2] << mais << tab5[i*2] << "|\n";
            cout << mais << hifens11 << mais << tab1[i*2+1] << mais << tab2[i*2+1] << mais << tab3[i*2+1] << mais << tab4[i*2+1] << mais << tab5[i*2+1] << "|\n";
            h1 += i%2;
        }
        cout << frase << endl;
        for (const pair<Slot, UcTurma>& s : sobr) {
            cout << s.second.getUcCode() << " " << s.second.getClassCode() << " ";
            if (s.first.getWeekday() == "Monday") {
                cout << "Segunda: ";
            }
            else if (s.first.getWeekday() == "Tuesday") {
                cout << "Terca: ";
            }
            else if (s.first.getWeekday() == "Wednesday") {
                cout << "Quarta: ";
            }
            else if (s.first.getWeekday() == "Thursday") {
                cout << "Quinta: ";
            }
            else if (s.first.getWeekday() == "Friday") {
                cout << "Sexta: ";
            }
            int aS = s.first.getStartHour(); // parte inteira
            int bS = ceil(s.first.getStartHour()); // arredondar para cima
            int aF = s.first.getFinalHour(); // parte inteira
            int bF = ceil(s.first.getFinalHour()); // arredondar para cima
            if (aS == bS) cout << aS << ":00-" << aF << ":30 ";
            else cout << aS << ":30-" << aF << ":00 ";
            cout << "Tipo: " << s.first.getType() << endl;
        }
    }
    else cout << "Sobreposicao de aulas TP ou PL com TP ou PL.\n";
}
/**
 * Desenha o número de estudantes por turma na respetiva unidade curricular
 * Complexidade Temporal O(n)
 */
void GestaoH::drawNumberOfStudentsPerUcTurma() const {
    vector<pair<UcTurma, int>> nOS = getNumberOfStudentsPerUcTurma();
    sort(nOS.begin(), nOS.end());
    cout << "\n+----------+-----------+----------+\n"
            "|          |           |  Number  |\n"
            "|  UcCode  | ClassCode |    of    |\n"
            "|          |           | Students |\n"
            "+----------+-----------+----------+\n";
    for (const pair<UcTurma, int>& ut : nOS) {
        cout << "| " << ut.first.getUcCode() << " |  " << ut.first.getClassCode() << "  | ";
        if (ut.second >= 10) cout << "   " << ut.second << "    |\n";
        else cout << "    " << ut.second << "    |\n";
        cout << "+----------+-----------+----------+\n";
    }
}
/**
 * Desenho do Menu principal
 * Complexidade Temporal O(1)
 */
void GestaoH::drawMenu() {
    cout << "\n+---------------------------------------------+\n"
            "|           GESTAO DE HORARIOS                |\n"
            "+---------------------------------------------+\n"
            "| [1] - Listar estudantes e UCs               |\n"
            "| [2] - Listar Blocos de Aulas                |\n"
            "| [3] - Numero de estudantes por Uc/Turma     |\n"
            "| [4] - Listar estudantes no ano X            |\n"
            "| [5] - Listar estudantes na turma X          |\n"
            "| [6] - Listar estudantes na UC X             |\n"
            "| [7] - Listar um estudante em especifico     |\n"
            "| [8] - Horario de um estudante em especifico |\n"
            "| [9] - Alteracao de turmas                   |\n"
            "| [P] - Processar Pedidos                     |\n"
            "| [Q] - Sair da aplicacao                     |\n"
            "+---------------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}
/**
 * Desenho do menu de Pedidos
 * Complexidade Temporal O(1)
 */
void GestaoH::drawPedido() {
    cout << "\n+-----------------------------------------+\n"
            "|               FAZER PEDIDO              |\n"
            "+-----------------------------------------+\n"
            "| [A] - Adicionar Turma                   |\n"
            "| [R] - Remover Turma                     |\n"
            "| [T] - Troca de Turma                    |\n"
            "| [C] - Conjunto de Trocas                |\n"
            "| [V] - Voltar ao Menu principal          |\n"
            "+-----------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

/**
 * Caso o input do utilizador seja S vai mostrar as unidades curriculares e as respetivas turmas de cada estudante
 * @return true se S para sim for pressionado, False se N para não for pressionado
 */

bool GestaoH::mostrarSpecs() {
    string op;
    while (true) {
        cout << "\nDeseja ver as UCs e Turmas dos estudantes [S/N]:";
        cin >> op;
        if (op == "S" || op == "s") return true;
        else if (op == "N" || op == "n") return false;
        else Menu::teclaErro();
    }
}

set<Student> GestaoH::getEstudantes() const {
    return estudantes_;
}

vector<TurmaH> GestaoH::getHorario() const {
    return horario_;
}

queue<vector<Pedido>> GestaoH::getPedido() const {
    return pedido_;
}

Student GestaoH::getSpecificStudent() const {
    set<Student> estudantes = getEstudantes();
    string n;
    while (true) {
        cout << "\nNumero UP: up";
        cin >> n;
        if (all_of(n.begin(), n.end(), ::isdigit)) {
            if (n.length() <= 9) break;
        }
        Menu::teclaErro();
    }
    for (Student s : estudantes) {
        if (s.getCode() == stoi(n)) {
            return s;
        }
    }
    return {};
}

vector<pair<UcTurma, int>> GestaoH::getNumberOfStudentsPerUcTurma() const {
    return numberOfStudentsPerUcTurma_;
}

int GestaoH::getMaxLength() const {
    return maxLength_;
}

void GestaoH::setEstudantes(set<Student> estudantes){
    estudantes_ = std::move(estudantes);
}

void GestaoH::setHorario(vector<TurmaH> horario) {
    horario_ = std::move(horario);
}

void GestaoH::setPedido(queue<vector<Pedido>> pedido) {
    pedido_ = std::move(pedido);
}

void GestaoH::setNumberOfStudentsPerUcTurma(vector<pair<UcTurma, int>> numberOfStudentsPerUcTurma) {
    numberOfStudentsPerUcTurma_ = std::move(numberOfStudentsPerUcTurma);
}

void GestaoH::setMaxLength(int maxLength) {
    maxLength_ = maxLength;
}

void GestaoH::addPedido(const vector<Pedido>& pedido){
    pedido_.push(pedido);
}
/**
 * Função que processa os pedidos que se encontram na fila de espera.
 * Complexidade Temporal O(n^6 * log(n))
 */
void GestaoH::processarPedidos(){
    vector<Pedido> pedidoaux = {};
    UcTurma novaUcTurma;
    Student novoStudent;
    Slot novaAula;
    int counter = 0;
    int CAP = 26; // capacidade máxima de uma turma (pode ser alterado)
    bool flag = false;
    while(!pedido_.empty()) {
        pedidoaux = pedido_.front();
        counter = 0;
        for (Pedido &temp: pedidoaux) {
            if (temp.getType() == "A") {
                for (TurmaH &turmah: horario_) {
                    if (turmah.getUcCode() == temp.getUcCode() && turmah.getClassCode() == temp.getFinalClassCode()) {
                        list<Slot> horarioUc = std::move(turmah.getHorarioUcClass());
                        for (Slot &horario: horarioUc) {
                            if (horario.getType() == "TP" || horario.getType() == "PL") {
                                novaAula = horario;
                            }
                        }
                    }
                }
                for (Student student: estudantes_) {
                    if (temp.getStudentCode() == student.getCode()) {
                        list<UcTurma> turmas = student.getTurmas();
                        for (pair<UcTurma, int> &number: numberOfStudentsPerUcTurma_) {
                            if (number.first.getUcCode() == temp.getUcCode() &&
                                number.first.getClassCode() == temp.getFinalClassCode()) {
                                if (number.second < CAP) {
                                    for (UcTurma ucturma: turmas) {
                                        for (TurmaH &turma: horario_) {
                                            if (turma.getUcCode() == ucturma.getUcCode() &&
                                                turma.getClassCode() == ucturma.getClassCode()) {
                                                list<Slot> horarioUc = turma.getHorarioUcClass();
                                                for (Slot &aula: horarioUc) {
                                                    if (aula.getType() == "TP" || aula.getType() == "PL") {
                                                        if (aula.getWeekday() == novaAula.getWeekday()) {
                                                            if ((aula.getStartHour() == novaAula.getStartHour() &&
                                                                 aula.getFinalHour() == novaAula.getFinalHour()) ||
                                                                (aula.getStartHour() < novaAula.getFinalHour() &&
                                                                 aula.getStartHour() > novaAula.getStartHour()) ||
                                                                (aula.getFinalHour() < novaAula.getFinalHour() &&
                                                                 aula.getFinalHour() > novaAula.getStartHour())) {
                                                                flag = false;
                                                                counter++;
                                                            }
                                                        } else if (aula.getWeekday() != novaAula.getWeekday()) {
                                                            flag = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (temp.getType() == "R") {
                list<UcTurma> tempaux = {};
                for (Student student: estudantes_) {
                    if (student.getCode() == temp.getStudentCode()) {
                        list<UcTurma> turmas = student.getTurmas();
                        for (pair<UcTurma, int> &number: numberOfStudentsPerUcTurma_) {
                            if (number.first.getUcCode() == temp.getUcCode() &&
                                number.first.getClassCode() == temp.getInitialClassCode()) {
                                number.second--;
                                novoStudent = student;
                                estudantes_.erase(student);
                                novaUcTurma.setUcCode(temp.getUcCode());
                                novaUcTurma.setClassCode(temp.getInitialClassCode());
                                for (auto itr: turmas) {
                                    if (itr.getUcCode() == novaUcTurma.getUcCode() &&
                                        itr.getClassCode() == novaUcTurma.getClassCode()) {
                                        continue;
                                    } else {
                                        tempaux.push_back(itr);
                                    }
                                }
                                novoStudent.setTurmas(tempaux);
                                estudantes_.insert(novoStudent);
                                cout << "Pedido de " << temp.getStudentCode() << " efetuado com sucesso" << endl;
                                break;
                            }
                        }
                    }
                }
            }
            else if (temp.getType() == "T") {
                for (TurmaH &turmah: horario_) {
                    if (turmah.getUcCode() == temp.getUcCode() && turmah.getClassCode() == temp.getFinalClassCode()) {
                        list<Slot> horarioUc = std::move(turmah.getHorarioUcClass());
                        for (Slot &horario: horarioUc) {
                            if (horario.getType() == "TP" || horario.getType() == "PL") {
                                novaAula = horario;
                            }
                        }
                    }
                }
                for (Student student: estudantes_) {
                    if (temp.getStudentCode() == student.getCode()) {
                        list<UcTurma> turmas = student.getTurmas();
                        for (pair<UcTurma, int> &number: numberOfStudentsPerUcTurma_) {
                            for (pair<UcTurma, int> &number2: numberOfStudentsPerUcTurma_) {
                                if (number.first.getUcCode() == temp.getUcCode() &&
                                    number.first.getClassCode() == temp.getFinalClassCode() &&
                                    number2.first.getUcCode() == temp.getUcCode() &&
                                    number2.first.getClassCode() == temp.getInitialClassCode()) {
                                    if (abs((number.second + 1) - (number2.second - 1)) <= 4 && number.second < CAP) {
                                        for (UcTurma &ucturma: turmas) {
                                            for (TurmaH &turma: horario_) {
                                                if ((turma.getUcCode() == ucturma.getUcCode() &&
                                                    turma.getClassCode() == ucturma.getClassCode()) && ucturma.getUcCode() != temp.getUcCode()) {
                                                    list<Slot> horarioUc = turma.getHorarioUcClass();
                                                    for (Slot &aula: horarioUc) {
                                                        if (aula.getType() == "TP" || aula.getType() == "PL") {
                                                            if ((aula.getStartHour() == novaAula.getStartHour() &&
                                                                 aula.getFinalHour() == novaAula.getFinalHour()) ||
                                                                (aula.getStartHour() < novaAula.getFinalHour() &&
                                                                 aula.getStartHour() > novaAula.getStartHour()) ||
                                                                (aula.getFinalHour() < novaAula.getFinalHour() &&
                                                                 aula.getFinalHour() > novaAula.getStartHour())) {
                                                                flag = false;
                                                                counter++;
                                                                break;
                                                            }
                                                            else if (aula.getWeekday() != novaAula.getWeekday()) {
                                                                flag = true;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (flag || counter == 0) {
                                            flag = false;
                                            novoStudent = student;
                                            estudantes_.erase(student);
                                            number.second++;
                                            number2.second--;
                                            for (UcTurma &help: turmas) {
                                                if (help.getUcCode() == temp.getUcCode() &&
                                                    help.getClassCode() == temp.getInitialClassCode()) {
                                                    help.setClassCode(temp.getFinalClassCode());
                                                }
                                            }
                                            novoStudent.setTurmas(turmas);
                                            estudantes_.insert(novoStudent);
                                            cout << "Pedido de " << temp.getStudentCode() << " efetuado com sucesso"
                                                 << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(temp.getType() == "CT"){
                for (TurmaH &turmah: horario_) {
                    if (turmah.getUcCode() == temp.getUcCode() && turmah.getClassCode() == temp.getFinalClassCode()) {
                        list<Slot> horarioUc = std::move(turmah.getHorarioUcClass());
                        for (Slot &horario: horarioUc) {
                            if (horario.getType() == "TP" || horario.getType() == "PL") {
                                novaAula = horario;
                            }
                        }
                    }
                }
                for (Student student: estudantes_) {
                    if (temp.getStudentCode() == student.getCode()) {
                        list<UcTurma> turmas = student.getTurmas();
                        for (pair<UcTurma, int> &number: numberOfStudentsPerUcTurma_) {
                            for (pair<UcTurma, int> &number2: numberOfStudentsPerUcTurma_) {
                                if (number.first.getUcCode() == temp.getUcCode() &&
                                    number.first.getClassCode() == temp.getFinalClassCode() &&
                                    number2.first.getUcCode() == temp.getUcCode() &&
                                    number2.first.getClassCode() == temp.getInitialClassCode()) {
                                    if (abs((number.second + 1) - (number2.second - 1)) <= 4 && number.second < CAP) {
                                        for (UcTurma &ucturma: turmas) {
                                            for (TurmaH &turma: horario_) {
                                                if ((turma.getUcCode() == ucturma.getUcCode() &&
                                                     turma.getClassCode() == ucturma.getClassCode()) && ucturma.getUcCode() != temp.getUcCode()) {
                                                    list<Slot> horarioUc = turma.getHorarioUcClass();
                                                    for (Slot &aula: horarioUc) {
                                                        if (aula.getType() == "TP" || aula.getType() == "PL") {
                                                            if ((aula.getStartHour() == novaAula.getStartHour() &&
                                                                 aula.getFinalHour() == novaAula.getFinalHour()) ||
                                                                (aula.getStartHour() < novaAula.getFinalHour() &&
                                                                 aula.getStartHour() > novaAula.getStartHour()) ||
                                                                (aula.getFinalHour() < novaAula.getFinalHour() &&
                                                                 aula.getFinalHour() > novaAula.getStartHour())) {
                                                                flag = false;
                                                                counter++;
                                                                break;
                                                            }
                                                            else if (aula.getWeekday() != novaAula.getWeekday()) {
                                                                flag = true;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (flag || counter == 0) {
                                            flag = false;
                                            novoStudent = student;
                                            estudantes_.erase(student);
                                            number.second++;
                                            number2.second--;
                                            for (UcTurma &help: turmas) {
                                                if (help.getUcCode() == temp.getUcCode() &&
                                                    help.getClassCode() == temp.getInitialClassCode()) {
                                                    help.setClassCode(temp.getFinalClassCode());
                                                }
                                            }
                                            novoStudent.setTurmas(turmas);
                                            estudantes_.insert(novoStudent);
                                            cout << "Pedido de " << temp.getStudentCode() << " efetuado com sucesso"
                                                 << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            pedido_.pop();
        }
    }
}

/**
 * Adiciona 1 ao número de elementos de uma unidade curricular e respetiva turma.
 * Complexidade Temporal O(n)
 * @param ucTurma
 */
void GestaoH::addNumberOfStudentsPerUcTurma(const UcTurma& ucTurma) {
    for (pair<UcTurma, int>& i : numberOfStudentsPerUcTurma_) {
        if (i.first.getUcCode() == ucTurma.getUcCode() && i.first.getClassCode() == ucTurma.getClassCode()) {
            i.second += 1;
        }
    }
}

/**
 *
 * Complexidade Temporal O(n^2)
 * @return set com todos os estudantes que pertençam ao ano que o utilizador dá input
 */
set<Student> GestaoH::studentsPerYear() {
    set<Student> aux;
    string n = "0";
    while (true) {
        cout << "\nIndique o ano (1, 2, 3):";
        cin >> n;
        if (n >= "1" && n <= "3") break;
        Menu::teclaErro();
    }
    for (const Student& student : estudantes_) {
        for (UcTurma& ucturma : student.getTurmas()) {
            if (n[0] == ucturma.getClassCode()[0]) {
                aux.insert(student);
                break;
            }
        }
    }
    return aux;
}

/**
 *
 * Complexidade Temporal O(n^2)
 * @return um set de Estudantes que pertençam a uma unidade curricular que tenha sido dada pelo utilizador
 */
set<Student> GestaoH::studentsPerUc() {
    set<Student> aux;
    string uc;
    while (true) {
        cout << "\nIndique o numero da unidade curricular:";
        cin >> uc;
        if (all_of(uc.begin(), uc.end(), ::isdigit)) break;
        Menu::teclaErro();
    }
    for (const Student& student: estudantes_) {
        for (UcTurma& ucturma: student.getTurmas()) {
            if (stoi(uc) == stoi(ucturma.getUcCode().substr(ucturma.getUcCode().size()-3, 3))) {
                aux.insert(student);
            }
        }
    }
    return aux;
}

/**
 *
 * Complexidade Temporal O(n^2)
 * @return um set de Estudantes que estejam numa turma na respetiva unidade curricular dadas pelo utilizador
 */
set<Student> GestaoH::studentsPerUcPerClass() {
    set<Student> aux;
    string uc, cl_ano, cl_nr;
    while (true) {
        cout << "\nIndique o numero da unidade curricular:";
        cin >> uc;
        if (all_of(uc.begin(), uc.end(), ::isdigit)) break;
        Menu::teclaErro();
    }
    cout << "\nIndique o ano e o numero da turma.\n";
    while (true) {
        cout << "\nAno (1, 2, 3):";
        cin >> cl_ano;
        if (cl_ano >= "1" && cl_ano <= "3") break;
        Menu::teclaErro();
    }
    while (true) {
        cout << "\nNr:";
        cin >> cl_nr;
        if (all_of(cl_nr.begin(), cl_nr.end(), ::isdigit)) break;
    }
    for (const Student& student: estudantes_) {
        for (UcTurma& ucturma: student.getTurmas()) {
            if (stoi(uc) == stoi(ucturma.getUcCode().substr(ucturma.getUcCode().size()-3, 3)) && stoi(cl_ano) == stoi(ucturma.getClassCode().substr(0, 1)) && stoi(cl_nr) == stoi(ucturma.getClassCode().substr(ucturma.getClassCode().size()-2, 2))) {
                aux.insert(student);
            }
        }
    }
    return aux;
}
