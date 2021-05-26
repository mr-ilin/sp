/* $n11 */
#include "code-gen.h"

using namespace std;

std::string semicolon = ";\n\t";
std::string q_sign = "\n\t? ";
std::string colon = "\n\t: ";
std::string comma = "\n\t ,";

void tCG::init() {
    declarations.clear();
    Authentication = "IIO";
}

int tCG::p01() { // S -> PROG
    debug();
    string header = "/*  " + Authentication + "   */\n";
    header += "#include \"mlisp.h\"\n";
    header += declarations;
    header += "//________________ \n";
    S1->obj = header + S1->obj;
    debug();
    return 0;
}

int tCG::p02() { //     PROG -> CALCS
    debug();
    S1->obj = "int main(){\n "
              + S1->obj
              + "std::cin.get();\n\t return 0;\n\t }\n";
    debug();
    return 0;
}

int tCG::p03() { //     PROG -> DEFS
    debug();
    S1->obj += "int main(){\n "
               "display(\"No calculations!\");\n\t newline();\n\t "
               " std::cin.get();\n\t return 0;\n\t }\n";
    debug();
    return 0;
}

int tCG::p04() { //     PROG -> DEFS CALCS
    debug();
    S1->obj += "int main(){\n "
               + S2->obj
               + "std::cin.get();\n\t return 0;\n\t }\n";
    debug();
    return 0;
}

int tCG::p05() { //        E -> $id
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p06() { //        E -> $int
    S1->obj = S1->name + '.';
    return 0;
}

int tCG::p07() { //        E -> $dec
    S1->obj = S1->name;
    return 0;
}

int tCG::p08() { //        E -> AREX
    return 0;
}

int tCG::p09() { //        E -> IF
    return 0;
}

int tCG::p10() { //        E -> EASYLET
    return 0;
}

int tCG::p11() { //        E -> CPROC
    return 0;
}

// завершает выражение и вставляет в него последний операнд
int tCG::p12() { //     AREX -> HAREX E )
    debug();
    std::string op = S1->name;
    if (S1->count == 0) {
        if (op == "/") {
            S1->obj = "(1. / " + S2->obj + ")";
        } else if (op == "-") {
            S1->obj = "(" + op + S2->obj + ")";
        }
    } else {
        S1->obj = "(" + S1->obj + " " + op + " " + S2->obj + ")";
    }
    debug();
    return 0;
}

int tCG::p13() { //    HAREX -> ( AROP
    debug();
    S1->obj += S2->name;
    S1->name = S2->name;
    S1->count = 0;
    debug();
    return 0;
}

// Добавляет дополнительные операнды.
// Все операнды – числовые выражения
int tCG::p14() { //    HAREX -> HAREX E
    debug();
    std::string op = S1->name; // символ операции
    if (S1->count == 0) {
        S1->obj = S2->obj;
    } else {
        S1->obj += " " + op + " " + S2->obj;
    }
    ++(S1->count);
    debug();
    return 0;
}

int tCG::p15() { //     AROP -> +
    return 0;
}

int tCG::p16() { //     AROP -> -
    return 0;
}

int tCG::p17() { //     AROP -> *
    return 0;
}

int tCG::p18() { //     AROP -> /
    return 0;
}

int tCG::p19() { //       IF -> ( if BOOL E E )
    //                        S1  S2  S3 S4 S5 S6
    debug();
    S1->obj = "(" + S3->obj + q_sign/* ? */ + S4->obj
            + colon/* , */ + S5->obj + ")";
    debug();
    return 0;
}

// завершает легкий let числовым выражением, которое вычисляет его значение
int tCG::p20() { //  EASYLET -> HEASYL E )
    S1->obj += ",\n\t" + S2->obj + "\n\t)";
    debug();
    return 0;
}

int tCG::p21() { //   HEASYL -> ( let ( )
    S1->obj += "(\n";
    S1->count = 0;
    return 0;
}

// вставляет внутреннее выражение класса INTER
int tCG::p22() { //   HEASYL -> HEASYL INTER
    debug();
    if (S1->count > 0) {
        S1->obj += ",\n";
    }
    S1->obj += "\t" + S2->obj;
    ++(S1->count);
    debug();
    return 0;
}

int tCG::p23() { //    CPROC -> HCPROC )
    debug();
    S1->obj += ")";
    debug();
    return 0;
}

// вставляет  в начало цепочки имя процедуры.
int tCG::p24() { //   HCPROC -> ( $id
    debug();
    S1->obj = decor(S2->name) + "(";
    S1->count = 0;
    debug();
    return 0;
}

// Добавляет аргументы вызова. Все аргументы – числовые выражения.
int tCG::p25() { //   HCPROC -> HCPROC E
    debug();
    if (S1->count != 0) {
        S1->obj += "\n\t, ";
    }
    S1->obj += S2->obj;
    ++(S1->count);
    debug();
    return 0;
}

int tCG::p26() { //      STR -> $str
    S1->obj = S1->name;
    return 0;
}

int tCG::p27() { //      STR -> SCOND
    return 0;
}

int tCG::p28() { //    SCOND -> ( cond SBRANCHES )
    S1->obj = S3->obj;
    debug();
    return 0;
}

int tCG::p29() { //SBRANCHES -> SELSE
    return 0;
}

int tCG::p30() { //SBRANCHES -> SCLAUS SBRANCHES
    S1->obj += colon/* : */ + S2->obj;
    debug();
    return 0;
}

int tCG::p31() { //   SCLAUS -> ( BOOL STR )
    S1->obj = S2->obj + q_sign/* ? */ + S3->name;
    debug();
    return 0;
}

int tCG::p32() { //    SELSE -> ( else STR )
    S1->obj = S3->name;
    debug();
    return 0;
}

int tCG::p33() { //     BOOL -> $bool
    debug();
    if (S1->name == "#t") {
        S1->obj = "true";
    } else {
        S1->obj = "false";
    }
    debug();
    return 0;
}

int tCG::p34() { //     BOOL -> $idq
    S1->obj += decor(S1->name);
    debug();
    return 0;
}

int tCG::p35() { //     BOOL -> REL
    return 0;
}


int tCG::p36() { //     BOOL -> AND
    return 0;
}

int tCG::p37() { //     BOOL -> ( not BOOL )
    debug();
    S1->obj = "!" + S3->obj;
    debug();
    return 0;
}

int tCG::p38() { //     BOOL -> CPRED
    return 0;
}

int tCG::p39() { //    CPRED -> HCPRED )
    S1->obj += ")";
    debug();
    return 0;
}

int tCG::p40() { //   HCPRED -> ( $idq
    S1->obj += decor(S2->name);
    return 0;
}

// Добавляем аргументы вызова предиката
int tCG::p41() { //   HCPRED -> HCPRED ARG
    debug();
    if (S1->count != 0) {
        S1->obj += "\n\t, ";
    } else {
        S1->obj += "(";
    }
    S1->obj += S2->obj;
    ++(S1->count);
    debug();
    return 0;
}

int tCG::p42() { //      ARG -> E
    return 0;
}

int tCG::p43() { //      ARG -> BOOL
    return 0;
}

int tCG::p44() { //      REL -> ( = E E )
    debug();
    S1->obj = "(" + S3->obj + " == " + S4->obj + ")";
    debug();
    return 0;
}

int tCG::p45() { //      REL -> ( <= E E )
    debug();
    S1->obj = "(" + S3->obj + " " + S2->name + " " + S4->obj + ")";
    debug();
    return 0;
}

int tCG::p46() { //      AND -> HAND BOOL )
    debug();
    S1->obj += " && " + S2->obj + ")";
    debug();
    return 0;
}

int tCG::p47() { //     HAND -> ( and
    debug();
    S1->obj = "(";
    debug();
    return 0;
}

int tCG::p48() { //     HAND -> HAND BOOL
    debug();
    S1->obj = "(" + S2->obj;
    debug();
    return 0;
}

int tCG::p49() { //      SET -> HSET E )
    S1->obj += " = " + S2->obj;
    debug();
    return 0;
}

int tCG::p50() { //     HSET -> ( set! $id
    S1->obj = decor(S3->name);
    debug();
    return 0;
}

int tCG::p51() { //  DISPSET -> ( display E )
    S1->obj = "display(" + S3->obj + ")";
    return 0;
}

int tCG::p52() { //  DISPSET -> ( display BOOL )
    S1->obj = "display(" + S3->obj + ")";
    return 0;
}

int tCG::p53() { //  DISPSET -> ( display STR )
    S1->obj = "display(" + S3->obj + ")";
    return 0;
}

int tCG::p54() { //  DISPSET -> ( newline )
    S1->obj = "newline()";
    return 0;
}

int tCG::p55() { //  DISPSET -> SET
    return 0;
}

int tCG::p56() { //    INTER -> DISPSET
    return 0;
}

int tCG::p57() { //    INTER -> E
    return 0;
}

int tCG::p58() { //    CALCS -> CALC
    return 0;
}

int tCG::p59() { //    CALCS -> CALCS CALC
    debug();
    S1->obj += S2->obj;
    debug();
    return 0;
}

int tCG::p60() { //     CALC -> E
    S1->obj = "display(" + S1->obj + ")" + semicolon/* ; */ + "newline()" + semicolon/* ; */;
    return 0;
}

int tCG::p61() { //     CALC -> BOOL
    S1->obj = "display(" + S1->obj + ")" + semicolon/* ; */ + "newline()" + semicolon/* ; */;
    return 0;
}

int tCG::p62() { //     CALC -> STR
    S1->obj = "display(" + S1->obj + ")" + semicolon/* ; */ + "newline()" + semicolon/* ; */;
    return 0;
}

int tCG::p63() { //     CALC -> DISPSET
    S1->obj += semicolon;
    return 0;
}

int tCG::p64() { //     DEFS -> DEF
    return 0;
}

int tCG::p65() { //     DEFS -> DEFS DEF
    debug();
    S1->obj += S2->obj;
    debug();
    return 0;
}

int tCG::p66() { //      DEF -> PRED
    return 0;
}

int tCG::p67() { //      DEF -> VAR
    return 0;
}

int tCG::p68() { //      DEF -> PROC
    return 0;
}

// формирует конец тела процедуры-предиката и вставляет в него булеское выражение,
// вычисляющее значение процедуры
int tCG::p69() { //     PRED -> HPRED BOOL )
    declarations += S1->obj + semicolon/*;*/;
    S1->obj += "{\nreturn\n" + S2->obj + semicolon/*;*/ + "}\n";
    debug();
    return 0;
}

// завершает список параметров процедуры-предиката.
int tCG::p70() { //    HPRED -> PDPAR )
    if (S1->count > 0) {
        S1->obj += S2->name;
    } else {
        S1->obj += "(" + S2->name;
    }
    debug();
    return 0;
}

// формирует начало определения процедуры-предиката с именем $idq
int tCG::p71() { //    PDPAR -> ( define ( $idq
    debug();
    S1->obj = "bool " + decor(S4->name) + "/*" + S4->line + "*/"; // to-check
    debug();
    return 0;
}

// добавляет в список  параметров булевский идентификатор $idq
int tCG::p72() { //    PDPAR -> PDPAR $idq
    debug();
    if (S1->count == 0) {
        S1->obj += "(";
    } else {
        S1->obj += (S1->count % 2 == 0 ? comma : ", ");
    }
    S1->obj += "bool " ;
    S1->obj += decor(S2->name);
    ++(S1->count);
    debug();
    return 0;
}

// добавляет в список  параметров числовой идентификатор $id.
int tCG::p73() { //    PDPAR -> PDPAR $id
    if (S1->count == 0) {
        S1->obj += "(";
    } else {
        S1->obj += (S1->count % 2 == 0 ? comma : ", ");
    }
    S1->obj += "double " ;
    S1->obj += S2->name;
    ++(S1->count);
    debug();
    return 0;
}

// инициализация переменной
int tCG::p74() { //      VAR -> VARDCL E )
    debug();
    declarations += "extern double " + decor(S1->obj) + ";\n\t";
    S1->obj = "double " + decor(S1->obj) + "(" + S2->obj + ");\n\t";
    debug();
    return 0;
}

// формируем обьявление переменной
int tCG::p75() { //   VARDCL -> ( define $id
    debug();
    S1->obj = S3->name + "/*" + S3->line + "*/";
    debug();
    return 0;
}

// формирует конец тела числовой процедуры и вставляет в него блок
int tCG::p76() { //     PROC -> HPROC BLOCK )
    S1->obj += S2->obj + "}\n";
    debug();
    return 0;
}

// заканчиваем определение числовой процедуры
int tCG::p77() { //     PROC -> HPROC E )
    debug();
    S1->obj += "return\n" + S2->obj + semicolon/* ; */ + "}\n";
    debug();
    return 0;
}

// Завершаем список параметров
int tCG::p78() { //    HPROC -> PCPAR )
    debug();
    declarations += S1->obj + ")" + semicolon;
    S1->obj += ") {\n\t";
    debug();
    return 0;
}

// добавляем выражения в функцию
int tCG::p79() { //    HPROC -> HPROC INTER
    debug();
    S1->obj += S2->obj + semicolon;
    debug();
    return 0;
}

// Начало определения числовой процедуры
int tCG::p80() { //    PCPAR -> ( define ( $id
    debug();
    S1->obj = "double " + decor(S4->name) + "/*" + S4->line + "*/" + "(";
    S1->name = S4->name;
    S1->count = 0;
    debug();
    return 0;
}

int tCG::p81() { //    PCPAR -> PCPAR $id
    debug();
    if (S1->count > 0) {
        S1->obj += S1->count % 2 ? ", " : "\n\t , ";
    }
    S1->obj += "double " + decor(S2->name);
    ++(S1->count);
    debug();
    return 0;
}

// завершает тело блока числовым выражением
int tCG::p82() { //    BLOCK -> HBLOCK E )
    S1->obj += "return\n" + S2->obj + semicolon/* ; */ + "}//let\n";
    debug();
    return 0;
}

// завершает список локальных переменных
int tCG::p83() { //   HBLOCK -> BLVAR )
    return 0;
}

// вставляет в тело блока дополнительные выражения класса INTER
int tCG::p84() { //   HBLOCK -> HBLOCK INTER
    S1->obj += S2->obj + semicolon/*;*/;
    debug();
    return 0;
}

// формирует начало блока и вставляет в него определение первой локальной переменной.
int tCG::p85() { //    BLVAR -> ( let ( LOCDEF
    S1->obj = "{ //let\n" + S4->obj + "\n\t";
    debug();
    return 0;
}

// наращивает список локальных переменных
int tCG::p86() { //    BLVAR -> BLVAR LOCDEF
    S1->obj += S2->obj + "\n\t";
    debug();
    return 0;
}

// формирует определение локальной переменной
int tCG::p87() { //   LOCDEF -> ( $id E )
    S1->obj = "double " + decor(S2->name) + "(" + S3->obj + ");";
    debug();
    return 0;
}

//_____________________
int tCG::p88() { return 0; }

int tCG::p89() { return 0; }

int tCG::p90() { return 0; }

int tCG::p91() { return 0; }

int tCG::p92() { return 0; }

int tCG::p93() { return 0; }

int tCG::p94() { return 0; }

int tCG::p95() { return 0; }

int tCG::p96() { return 0; }

int tCG::p97() { return 0; }

int tCG::p98() { return 0; }

int tCG::p99() { return 0; }

int tCG::p100() { return 0; }

int tCG::p101() { return 0; }

int tCG::p102() { return 0; }

int tCG::p103() { return 0; }

int tCG::p104() { return 0; }

int tCG::p105() { return 0; }

int tCG::p106() { return 0; }

int tCG::p107() { return 0; }

int tCG::p108() { return 0; }

int tCG::p109() { return 0; }

int tCG::p110() { return 0; }

