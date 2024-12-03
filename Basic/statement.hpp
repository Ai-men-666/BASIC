/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <sstream>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include "parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;

};
class PrintStatement : public Statement {
public:
 PrintStatement(Expression *exp);

 virtual ~PrintStatement();

 virtual void execute(EvalState &state, Program &program);

private:
 Expression *exp;
};

class LetStatement : public Statement {
public:
 LetStatement(std::string name, Expression *exp);

 virtual ~LetStatement();

 virtual void execute(EvalState &state, Program &program);

private:
 Expression *exp;
 std::string name;
};

class IfStatement : public Statement {
public:
 IfStatement(Expression *condition1,std::string op,Expression *condition2,int targetLine);

 virtual void execute(EvalState &state, Program &program) ;

 virtual ~IfStatement();

private:
 Expression *condition1;
 Expression *condition2;
 std::string op;
 int targetLine;
};

class InputStatement : public Statement {
public:
 InputStatement(std::string varName);

 virtual void execute(EvalState &state, Program &program);

 virtual ~InputStatement();

private:
 std::string varName;
 int value;
};

class GotoStatement:public Statement {
public:
 GotoStatement(int targetLine);

 virtual void execute(EvalState &state, Program &program);

 virtual ~GotoStatement();

private:
 int targetLine;
};

class RemStatement:public Statement {
public:
 RemStatement();

 virtual void execute(EvalState &state, Program &program){};

 virtual ~RemStatement();
};

class EndStatement:public Statement {
public:
 EndStatement();

 virtual void execute(EvalState &state, Program &program);

 virtual ~EndStatement();
};
/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

#endif
