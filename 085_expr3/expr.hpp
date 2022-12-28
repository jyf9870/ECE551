#ifndef _EXPR_H_
#define _EXPR_H_
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;  //abstract method
  virtual ~Expression() {}
  virtual long evaluate() const = 0;  //abstract method
};
class NumExpression : public Expression {
 private:
  long numb;

 public:
  NumExpression(long number) : numb(number) {}
  std::string toString() const {
    std::stringstream result;
    result << numb;
    return result.str();
  }  //actually implement it
  long evaluate() const { return numb; }
  virtual ~NumExpression() {}
};
class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return result.str();
  }
  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  ~PlusExpression() {
    delete this->lhs;
    delete this->rhs;
  }
};
class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return result.str();
  }
  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  ~MinusExpression() {
    delete this->lhs;
    delete this->rhs;
  }
};
class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return result.str();
  }
  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  ~TimesExpression() {
    delete this->lhs;
    delete this->rhs;
  }
};
class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return result.str();
  }
  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  ~DivExpression() {
    delete this->lhs;
    delete this->rhs;
  }
};

#endif
