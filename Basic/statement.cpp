/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

PrintStatement::PrintStatement(Expression *exp) {
 this->exp = exp;
}

PrintStatement::~PrintStatement() {
 delete exp;
}

void PrintStatement::execute(EvalState &state, Program &program) {
 int result = exp->eval(state);
 std::cout << result << std::endl;
}

LetStatement::LetStatement(std::string name, Expression *exp):name(name),exp(exp){}

void LetStatement:: execute(EvalState &state, Program &program) {
 int value = exp->eval(state);
}

LetStatement::~LetStatement(){
 /*std::cout << "delete Let" << '\n';*/
  delete exp;
}

IfStatement::IfStatement(Expression *condition1,std::string op,Expression *condition2,int targetLine) : condition1(condition1),condition2(condition2),op(op),targetLine(targetLine) {}

void IfStatement::execute(EvalState &state, Program &program) {
 if(!program.findLine(targetLine)) {
  throw ErrorException("LINE NUMBER ERROR");
 }
 int condition1Value = condition1->eval(state);
 int condition2Value = condition2->eval(state);
 bool res;
 if(op == "=") {
  res = (condition1Value == condition2Value);
 }
 if(op == ">") {
  res = (condition1Value > condition2Value);
 }
 if(op == "<") {
  res = (condition1Value < condition2Value);
 }
 if (res) {
  program.setRunLine(targetLine);
 }
}

IfStatement::~IfStatement(){
 delete condition1;
 delete condition2;
}

InputStatement::InputStatement(std::string varName) : varName(varName){}

void InputStatement::execute(EvalState &state, Program &program) {
 /*std::string input;
 std::cin >> input;
 TokenScanner scanner;
 scanner.ignoreWhitespace();
 scanner.scanNumbers();
 scanner.setInput(input);
 std::string tmp;
 bool isDigital = true;
 while (scanner.hasMoreTokens()) {
  tmp = scanner.nextToken();
  if(scanner.getTokenType(tmp) != NUMBER) {
   isDigital = false;
  }
 }
 if(!isDigital) {
  std::cin >> input;
 }
 TokenScanner scanner2;
 scanner2.ignoreWhitespace();
 scanner2.scanNumbers();
 scanner2.setInput(input);
 scanner2.setInput(input);
 Expression *exp = parseExp(scanner2);
 int value = exp->eval(state);
 state.setValue(varName, value);*/
 bool correctInput = false;
 std::string input;
 while(!correctInput) {
  correctInput = true;
  std::cout << "? ";
  std::getline(std::cin,input);
  if((input[0] > '9' || input[0] < '0') && input[0] != '-') {
   correctInput = false;
  }
  for(int i = 1;i < input.length();i++) {
   if(input[i] > '9' || input[i] < '0') {
    correctInput = false;
    std::cout << "INVALID NUMBER" << '\n';
    break;
   }
  }
 }
 int value = stringToInteger(input);
 state.setValue(varName,value);
}

InputStatement::~InputStatement(){}
GotoStatement::GotoStatement(int targetLine):targetLine(targetLine) {}

void GotoStatement::execute(EvalState &state, Program &program) {
if(program.findLine(targetLine)) {
 program.setRunLine(targetLine);
}else {
 throw ErrorException("LINE NUMBER ERROR");
}
}
GotoStatement::~GotoStatement(){}

RemStatement::RemStatement() {}

RemStatement::~RemStatement(){}

EndStatement::EndStatement() {}

void EndStatement::execute(EvalState &state, Program &program) {
 program.isFinish = true;
}

EndStatement::~EndStatement(){}
//todo
