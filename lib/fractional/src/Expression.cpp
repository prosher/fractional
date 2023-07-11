#include "Expression.h"

#include <utility>

Const::Const(Fraction value) : m_value(value) {}
Fraction Const::Value() const {
    return m_value;
}
Fraction Const::Eval(const std::map<std::string, Fraction>& var_map) const {
    return Value();
}
std::unique_ptr<Expression> Const::Clone() const {
    return std::unique_ptr<Expression>(new Const(*this));
}

Variable::Variable(std::string name) : m_name(std::move(name)) {}
std::string Variable::Name() const {
    return m_name;
}
Fraction Variable::Eval(const std::map<std::string, Fraction>& var_map) const {
    return var_map.contains(Name()) ? var_map.at(Name()) : 0;
}
std::unique_ptr<Expression> Variable::Clone() const {
    return std::unique_ptr<Expression>(new Variable(*this));
}
UnaryOperation::UnaryOperation(const Expression& argument) : m_arg(argument.Clone()) {}
Fraction UnaryOperation::Eval(const std::map<std::string, Fraction>& var_map) const {
    return calc(m_arg->Eval(var_map));
}

BinaryOperation::BinaryOperation(const Expression& left, const Expression& right)
    : m_left(left.Clone()), m_right(right.Clone()) {}
Fraction BinaryOperation::Eval(const std::map<std::string, Fraction>& var_map) const {
    return calc(m_left->Eval(var_map), m_right->Eval(var_map));
}

Add::Add(const Expression& left, const Expression& right) : BinaryOperation(left, right) {}
Fraction Add::calc(const Fraction& left, const Fraction& right) const {
    return left + right;
}
std::unique_ptr<Expression> Add::Clone() const {
    return std::unique_ptr<Expression>(new Add(*this));
}
Add operator+(const Expression& lhs, const Expression& rhs) {
    return Add(lhs, rhs);
}

Subtract::Subtract(const Expression& left, const Expression& right) : BinaryOperation(left, right) {}
Fraction Subtract::calc(const Fraction& left, const Fraction& right) const {
    return left - right;
}
std::unique_ptr<Expression> Subtract::Clone() const {
    return std::unique_ptr<Expression>(new Subtract(*this));
}
Subtract operator-(const Expression& lhs, const Expression& rhs) {
    return Subtract(lhs, rhs);
}

Multiply::Multiply(const Expression& left, const Expression& right) : BinaryOperation(left, right) {}
Fraction Multiply::calc(const Fraction& left, const Fraction& right) const {
    return left * right;
}
std::unique_ptr<Expression> Multiply::Clone() const {
    return std::unique_ptr<Expression>(new Multiply(*this));
}
Multiply operator*(const Expression& lhs, const Expression& rhs) {
    return Multiply(lhs, rhs);
}

Divide::Divide(const Expression& left, const Expression& right) : BinaryOperation(left, right) {}
Fraction Divide::calc(const Fraction& left, const Fraction& right) const {
    return left / right;
}
std::unique_ptr<Expression> Divide::Clone() const {
    return std::unique_ptr<Expression>(new Divide(*this));
}
Divide operator/(const Expression& lhs, const Expression& rhs) {
    return Divide(lhs, rhs);
}

Negate::Negate(const Expression& argument) : UnaryOperation(argument) {}
Fraction Negate::calc(const Fraction& argument) const {
    return -argument;
}
std::unique_ptr<Expression> Negate::Clone() const {
    return std::unique_ptr<Expression>(new Negate(*this));
}
Negate operator-(const Expression& argument) {
    return Negate(argument);
}
