/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() {
    /*std::cout << "delete";*/
    for(auto it = parsedStatement.begin();it != parsedStatement.end();it++) {
        if(it->second != NULL) {
            delete it->second;
        }
    }
    parsedStatement.clear();
    line.clear();
    hasLineNumber.clear();
}

void Program::clear(EvalState &state) {
    line.clear();
    curLine = 1;
    state.Clear();
    // Replace this stub with your own code
    //todo
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    if(line.find(lineNumber)) {
        this->line.erase(lineNumber);
    }
    hasLineNumber[lineNumber] = true;
    curLine = std::max(curLine,lineNumber + 1);
    this->line[lineNumber] = line;
    // Replace this stub with your own code
    //todo
}
void Program::addSourceLine(const std::string &line) {
    this->line[curLine] = line;
    hasLineNumber[curLine] = false;
    setParsedStatement(curLine,nullptr);
    curLine++;
    // Replace this stub with your own code
    //todo
}
void Program::removeSourceLine(int lineNumber) {
    auto it = line.find(lineNumber);
    if(it != line.end()) {
        line.erase(lineNumber);
        setParsedStatement(lineNumber,nullptr);
    }
    // Replace this stub with your own code
    //todo
}

std::string Program::getSourceLine(int lineNumber) {
    auto it = line.find(lineNumber);
    if(it == line.end()) {
        return "";
    }
    return it->second;
    // Replace this stub with your own code
    //todo
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if(line.find(lineNumber) == line.end()) {
        parsedStatement[lineNumber] = stmt;
        return;
    }else {
        Statement *oldStmt = getParsedStatement(lineNumber);
        if(oldStmt != nullptr) {
            delete oldStmt;
        }
        parsedStatement[lineNumber] = stmt;
    }
    // Replace this stub with your own code
    //todo
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
    auto it = parsedStatement.find(lineNumber);
    if(it != parsedStatement.end()) {
        return it->second;
    }
    return nullptr;
   // Replace this stub with your own code
   //todo
}

int Program::getFirstLineNumber() {
    if(line.empty()) {
        return -1;
    }
    return line.begin()->first;
    // Replace this stub with your own code
    //todo
}

int Program::getNextLineNumber(int lineNumber) {
    auto it = line.upper_bound(lineNumber);
    if(it != line.end()) {
        return it->first;
    }
    return -1;
    // Replace this stub with your own code
    //todo
}

void Program::quit() {
    this->~Program();
    exit(0);
}

void Program::run(EvalState &state) {
    isFinish = false;
    this->runLine = getFirstLineNumber();
    while(runLine != -1 && !isFinish) {
        Statement *stmt = getParsedStatement(runLine);
        if(stmt != nullptr && hasLineNumber[runLine]) {
            stmt->execute(state,*this);
        }
        runLine = getNextLineNumber(runLine);
    }
}

void Program::list() {
    for(auto it = line.begin();it != line.end();it++) {
        std::cout << it->second << '\n';
    }
}

void Program::print(TokenScanner scanner,EvalState &state) {
    Expression *exp = parseExp(scanner);
    std::cout << exp->eval(state) << '\n';
}

void Program::setRunLine(int targetLine) {
    runLine = targetLine - 1;
}

bool Program::findLine(int lineNumber) {
    if(parsedStatement.find(lineNumber) != parsedStatement.end()) {
        return true;
    }
    return false;
}

//more func to add
//todo


