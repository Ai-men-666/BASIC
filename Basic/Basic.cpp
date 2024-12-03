/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include <variant>

#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    std::string order;
    order = scanner.nextToken();
    TokenType firstType = scanner.getTokenType(order);
    if(order == "REM") {
        return;
    }
    if(order == "LIST") {
        program.list();
        return;
    }
    if(order == "RUN") {
        program.run(state);
        return;
    }
    if(order == "QUIT") {
        program.quit();
        return;
    }
    try {
        int lineNumber = 0;
        if(firstType == NUMBER) {
            lineNumber = stringToInteger(order);
            program.addSourceLine(stringToInteger(order),line);
            order = scanner.nextToken();
            if(!scanner.hasMoreTokens()) {
                program.removeSourceLine(lineNumber);
            }
        }else {
            program.addSourceLine(line);
        }
        if (order == "LET") {
            Expression *exp = parseExp(scanner);
            std::string name = scanner.nextToken();
            Statement *stmt = new LetStatement(name,exp);
            if(firstType != NUMBER) {
                stmt->execute(state,program);
            }else {
                program.setParsedStatement(lineNumber,stmt);
            }
        }

        if(order == "PRINT") {
            Expression *exp = parseExp(scanner);
            Statement *stmt = new PrintStatement(exp);
            if(firstType != NUMBER) {
                stmt->execute(state,program);
            }else {
                program.setParsedStatement(lineNumber,stmt);
            }
        }

        if (order == "INPUT") {
            order = scanner.nextToken();
            Statement *stmt = new InputStatement(order);
            if(firstType != NUMBER) {
                stmt->execute(state,program);
            }else {
                program.setParsedStatement(lineNumber,stmt);
            }
        }
        if(order == "CLEAR") {
            program.clear(state);
        }
        if(order == "GOTO") {
            int targetLine = stringToInteger(scanner.nextToken());
            Statement* stmt = new GotoStatement(targetLine);
            program.setParsedStatement(lineNumber,stmt);
        }
        if(order == "IF") {
            std::string condition1,condition2;
            std::string tmp = scanner.nextToken();
            while(tmp != "=" && tmp != ">" && tmp != "<") {
                condition1 = condition1 + ' ' + tmp;
                tmp = scanner.nextToken();
            }
            std::string op = tmp;
            tmp = scanner.nextToken();
            while(tmp != "THEN") {
                condition2 = condition2 + ' ' + tmp;
                tmp = scanner.nextToken();
            }
            tmp = scanner.nextToken();
            TokenScanner scanner1,scanner2;
            scanner1.ignoreWhitespace();
            scanner1.scanNumbers();
            scanner1.setInput(condition1);
            scanner2.ignoreWhitespace();
            scanner2.scanNumbers();
            scanner2.setInput(condition2);
            Expression* condition1Exp = parseExp(scanner1);
            Expression* condition2Exp = parseExp(scanner2);
            Statement* stmt = new IfStatement(condition1Exp,op,condition2Exp,stringToInteger(tmp));
            program.setParsedStatement(lineNumber,stmt);
        }
        if(order == "REM") {
            Statement *stmt = nullptr;
            if(firstType != NUMBER) {
                stmt->execute(state,program);
            }else {
                program.setParsedStatement(lineNumber,stmt);
            }
        }
        if(order == "END") {
            Statement *stmt = new EndStatement();
            if(firstType != NUMBER) {
                stmt->execute(state,program);
            }else {
                program.setParsedStatement(lineNumber,stmt);
            }
        }
    }catch (ErrorException e) {
        std::cout << e.getMessage() << '\n';
    }
    return;
    //todo
}

