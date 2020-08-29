#pragma once
#include "exprast.h"

class IntegerExprAST : public ExprAST {
public:
    IntegerExprAST(int32_t value);

private:
    int32_t value;
};