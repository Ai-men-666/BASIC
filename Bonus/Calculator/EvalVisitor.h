#include "ExprParser.h"
#include "ExprVisitor.h"

#include <iostream>

class EvalVisitor : public ExprVisitor {
public:

  std::any visitCalc(ExprParser::CalcContext *ctx) override {
    /// TODO
  }

  std::any visitMulDiv(ExprParser::MulDivContext *ctx) override {
    /// TODO
  }

  std::any visitAddSub(ExprParser::AddSubContext *ctx) override {
    /// TODO
  }

  std::any visitInt(ExprParser::IntContext *ctx) override {
    /// TODO
  }

  std::any visitParens(ExprParser::ParensContext *ctx) override {
    /// TODO
  }

};
