#include "../include/gestaoh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <cmath>

GestaoH::GestaoH() {
    estudantes_ = set<Student> {};
    horario_ = vector<TurmaH> {};
    pedido_ = queue<vector<Pedido>> {};
    numberOfStudentsPerUcTurma_ = vector<pair<UcTurma, int>> {};
}

GestaoH::GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<vector<Pedido>> pedido, vector<pair<UcTurma, int>> numberOfStudentsPerUcTurma) {
    estudantes_ = std::move(estudantes); // em vez de fazer estudantes_ = estudantes fazemos
    horario_ = std::move(horario);       // isso para não copiarmos o objeto duas vezes
    pedido_ = std::move(pedido);         // (sugestão do CLion)
    numberOfStudentsPerUcTurma_ = std::move(numberOfStudentsPerUcTurma);
}

void GestaoH::lerClasses() {
    string line1, line2, temp, word;
    string classCode1, classCode2, ucCode1, ucCode2, weekday, sstartHour, sduration, type, tempClassCode, tempUcCode;
    double startHour, duration;
    Slot aux;
    vector<TurmaH> horario; // criar vector de ucCode/classCode e uma list<Slot>
    string ficheiro = "../schedule/classes.csv";
    ifstream ifs1, ifs2;
    list<Slot> slot; // criar lista de slots para cada ucCode/classCode
    ifs1.open(ficheiro, ios::in);
    getline(ifs1, temp);
    // objetivo aqui é fazer dois ciclos para correr o ficheiro todo
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

void GestaoH::lerStudentClasses() {
    string line, temp, word, sstudentCode, studentName, ucCode, classCode, tempStudentName; // tempStudentName para guardar o nome estudante anterior
    int tempSstudentCode; // para guardar o código do estudante anterior
    set<Student> estudantes; // criar set de estudantes
    list<UcTurma> listaUcTurma; // criar lista de ucTurma para cada estudante
    UcTurma ucTurma; // criar UcTurma para cada conjunto de ucCode/classCode
    vector<pair<UcTurma, int>> studentsPerUcTurma;
    string ficheiro = "../schedule/students_classes.csv";
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
            // o próximo if é só para saber qual o tamanho do maior nome de um estudante
            if (tempStudentName.length() > getMaxLength()) {
                setMaxLength((int)tempStudentName.length());
            }
        }
        UcTurma aux;
        bool verifyUcTurma = false;
        for (auto & i : studentsPerUcTurma) { // percorre o vetor de estudantes por turma
            if (classCode == i.first.getClassCode() && ucCode == i.first.getUcCode()) { // verifica se a ucturma já está no vetor
                i.second++; // se sim, adiciona mais um estudante
                verifyUcTurma = true;
                break;
            }
        }
        if (!verifyUcTurma) { // se não, cria uma nova ucturma e coloca no vetor
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
    setNumberOfStudentsPerUcTurma(studentsPerUcTurma); // povoar o vetor<pair<UcTurma, int>>
    setEstudantes(estudantes); // povoar o set<Student>
}

// funções auxiliares para desenhar
// função para ajudar a centralizar textos
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

// ajuda a desenhar as horas das slots
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

// ajuda a desenhar o tipo das slots
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

void GestaoH::drawEstudante(const Student& estudante, bool header) const {
    // desenha o cabeçalho quando é o primeiro estudante
    if (header) {
        cout << "+-------------+---------------------------+----------+-----------+\n"
                "| StudentCode |        StudentName        |  UcCode  | ClassCode |\n"
                "+-------------+---------------------------+----------+-----------+\n";
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
    int c = 0;
    list<UcTurma> classUc = estudante.getTurmas();
    for (const UcTurma& u : classUc) {
        if (c > 0) {
            cout << "|             |                           ";
        }
        cout << "| " << u.getUcCode() << " |  " << u.getClassCode() << "  |\n";
        c++;
    }
    // desenha o rodapé
    for (int i = 0; i < 36+getMaxLength(); i++) {
        if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
        cout << "-";
        if (i == 35+getMaxLength()) cout << "+\n";
    }
}

void GestaoH::drawEstudantes() const {
    set<Student> estudantes = getEstudantes();
    int v = 1;
    for (const Student& s : estudantes) {
        drawEstudante(s, v);
        v = 0;
    }
}

void GestaoH::drawHorario() const {
    vector<TurmaH> horario = getHorario();
    cout << "+----------+-----------+-------------+----------+----------+-------+\n"
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

void GestaoH::drawNumberOfStudentsPerUcTurma() const {
    vector<pair<UcTurma, int>> nOS = getNumberOfStudentsPerUcTurma();
    cout << "+----------+-----------+----------+\n"
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

void GestaoH::drawMenu() {
    cout << "\n+-----------------------------------------+\n"
            "|           GESTAO DE HORARIOS            |\n"
            "+-----------------------------------------+\n"
            "| [1] - Listar estudantes e UCs           |\n"
            "| [2] - Listar um estudante em especifico |\n"
            "| [3] - Listar Blocos de Aulas            |\n"
            "| [4] - Numero de estudantes por Uc/Turma |\n"
            "| [5] - Alteracao de turmas               |\n"
            "| [Q] - Sair da aplicacao                 |\n"
            "+-----------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

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

set<Student> GestaoH::getEstudantes() const {
    return estudantes_;
}

vector<TurmaH> GestaoH::getHorario() const {
    return horario_;
}

queue<vector<Pedido>> GestaoH::getPedido() const {
    return pedido_;
}

Student GestaoH::getSpecificStudent(int n) const {
    set<Student> estudantes = getEstudantes();
    for (Student s : estudantes) {
        if (s.getCode() == n) {
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

void GestaoH::setEstudantes(set<Student> estudantes) {
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

void GestaoH::processarPedidos(){
    vector<Pedido> pedido;
    UcTurma novaUcTurma;
    Student newStudent;
    list<UcTurma> turmas;
    list<Slot> horarioUc;
    Slot novaAula;
    int CAP = 26; // capacidade máxima de uma turma (pode ser alterado)
    while(!pedido_.empty()){ // enquanto a queue não estiver vazia
        pedido = pedido_.front(); // buscar o primeiro elemento da queue
        unsigned n = 0;
        for(auto& index : horario_){ // vai buscar ao vetor dos horários o slot da aula TP ou PL que a turma para que quer mudar vai ocupar
            if(index.getUcCode() == pedido[n].getUcCode() && index.getClassCode() == pedido[n].getFinalClassCode()){
                for(const auto& e: index.getHorarioUcClass()){
                    if(e.getType() == "TP" || e.getType() == "PL"){
                        novaAula = e;
                    }
                }
            }
        }
        while(n < pedido.size()){
            if(pedido[n].getType() == "A"){ // adicionar a uma turma
                for(auto& i: estudantes_){ // percorre o set estudantes
                    if(pedido[n].getStudentCode() == i.getCode()){ // verifica o código de estudante com o do pedido
                        for(auto &s: numberOfStudentsPerUcTurma_){ // percorre o vetor numberOfStudentsPerUcTurma_
                            if(s.first.getUcCode() == pedido[n].getUcCode() && s.first.getClassCode() == pedido[n].getFinalClassCode()){ // verifica se é a turma e unidade curricular correta
                                if(s.second < CAP){ // verifica se o número de estudantes na ucturma não está no limite, para se poder por mais 1 aluno
                                    for(const auto& ucturma: i.getTurmas()){ // percorre a lista de ucturmas de um estudante
                                        for(auto& cadeira: horario_){ // percorre as cadeiras no vetor dos horários
                                            if((ucturma.getUcCode() == cadeira.getUcCode() && ucturma.getClassCode() == cadeira.getClassCode()) && (ucturma.getUcCode() != pedido[n].getUcCode())){ // verifica se é a mesma cadeira e turma e se o estudante já está inscrito na cadeira
                                                for(auto& aula: cadeira.getHorarioUcClass()){ // percorre a lista de horários de uma ucturma específica
                                                    if(aula.getType() == "TP" || aula.getType() == "PL"){ // verifica se é a aula teórico-prática ou prática laboratorial
                                                        if(aula.getWeekday() == novaAula.getWeekday()){ // verifica se é no mesmo dia da semana
                                                            if(aula.getStartHour() > novaAula.getFinalHour() || aula.getFinalHour() < novaAula.getStartHour()){ // verifica se a aula de uma cadeira existente não se sobrepõe à nova
                                                                newStudent = i; // foi necessário remover o estudante do set
                                                                estudantes_.erase(i); // para se poder inserir um novo
                                                                turmas = i.getTurmas(); // uma vez que não é possível alterar os valores já no set
                                                                s.second++;
                                                                novaUcTurma.setClassCode(pedido[n].getFinalClassCode());
                                                                novaUcTurma.setUcCode(pedido[n].getUcCode());
                                                                turmas.push_back(novaUcTurma);
                                                                newStudent.setTurmas(turmas);
                                                                estudantes_.insert(newStudent);
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
            }
            if(pedido[n].getType() == "R"){ // remover de uma turma
                for(auto& i: estudantes_){
                    if(pedido[n].getStudentCode() == i.getCode()){
                        for(auto &s: numberOfStudentsPerUcTurma_){
                            if(s.first.getUcCode() == pedido[n].getUcCode() && s.first.getClassCode() == pedido[n].getInitialClassCode()){ // aqui não será necessário verificar o número de estudantes
                                newStudent = i; // de uma turma, visto que nunca poderá passar do limite e não existe limite mínimo
                                estudantes_.erase(i);
                                turmas = i.getTurmas();
                                s.second--;
                                for(auto itr = turmas.begin(); itr != turmas.end(); itr++){ // percorre a lista de ucturmas de um estudante
                                    if(itr->getUcCode() == pedido[n].getUcCode() && itr->getClassCode() == pedido[n].getInitialClassCode()){ // verificação da ucturma
                                        turmas.erase(itr); // remoção da ucturma da lista do estudante
                                    }
                                }
                                newStudent.setTurmas(turmas);
                                estudantes_.insert(newStudent);
                            }
                        }
                    }
                }
            }
            if(pedido[n].getType() == "T" || pedido[n].getType() == "CT"){ // troca de turma
                for(auto& i: estudantes_){
                    if(pedido[n].getStudentCode() == i.getCode()){
                        for(auto &s: numberOfStudentsPerUcTurma_){ // preciso de percorrer o vetor 2 vezes
                            for(auto &d: numberOfStudentsPerUcTurma_){ // uma vez que preciso da turma que o estudante está e aquela para a qual ele quer mudar
                                if(s.first.getUcCode() == pedido[n].getUcCode() && d.first.getUcCode() == pedido[n].getUcCode() && s.first.getClassCode() == pedido[n].getInitialClassCode() && d.first.getClassCode() == pedido[n].getFinalClassCode()){ // verifica se s é a turma inicial e d a turma final
                                    if((abs((s.second-1) - (d.second+1)) < 4) && (s.second < CAP || d.second < CAP)){ // verifica se a diferença entre o número de estudantes depois da mudança é menor que 4 e se ambos estão abaixo do limite máximo
                                        for(const auto& ucturma: i.getTurmas()) { // percorre a lista de ucturmas de um estudante
                                            for(auto &cadeira: horario_) { // percorre as cadeiras no vetor dos horários
                                                if((ucturma.getUcCode() == cadeira.getUcCode() && ucturma.getClassCode() == cadeira.getClassCode()) && (ucturma.getUcCode() != pedido[n].getUcCode())) { // verifica se é a mesma cadeira e turma e se difere da cadeira que pretendemos mudar
                                                    for(auto &aula: cadeira.getHorarioUcClass()) { // percorre a lista de horários de uma ucturma específica
                                                        if(aula.getType() == "TP" || aula.getType() == "PL") { // verifica se é a aula teórico-prática ou prática laboratorial
                                                            if(aula.getWeekday() == novaAula.getWeekday()) { // verifica se é no mesmo dia da semana
                                                                if(aula.getStartHour() > novaAula.getFinalHour() || aula.getFinalHour() < novaAula.getStartHour()) { // verifico se existe sobreposição de aulas
                                                                    s.second--;
                                                                    d.second++;
                                                                    newStudent = i;
                                                                    estudantes_.erase(i);
                                                                    turmas = i.getTurmas();
                                                                    for(auto &turma: turmas) { // percorre a lista de ucturmas do estudante
                                                                        if(turma.getUcCode() == pedido[n].getUcCode() && turma.getClassCode() == pedido[n].getInitialClassCode()) { // verifica se é a ucturma correta
                                                                            turma.setClassCode(pedido[n].getFinalClassCode()); // troca na lista o código da turma
                                                                        }
                                                                    }
                                                                    newStudent.setTurmas(turmas);
                                                                    estudantes_.insert(newStudent);
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
                }
            }
            n++;
        }
        pedido_.pop(); // remove o primeiro elemento da queue
    }
}

void GestaoH::addNumberOfStudentsPerUcTurma(const UcTurma& ucTurma) {
    for (pair<UcTurma, int>& i : numberOfStudentsPerUcTurma_) {
        if (i.first.getUcCode() == ucTurma.getUcCode() && i.first.getClassCode() == ucTurma.getClassCode()) {
            i.second += 1;
        }
    }
}
