#pragma once
#include "expr_ast.h"

class IntegerExprAST : public ExprAST {
public:
    IntegerExprAST(int32_t value);

private:
    int32_t value;
};