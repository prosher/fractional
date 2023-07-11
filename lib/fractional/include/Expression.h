#include <map>
#include <memory>
#include <string>

#include "Fraction.h"

#ifndef SMALLTASK56_EXPRESSION_H
#define SMALLTASK56_EXPRESSION_H

class Expression {
public:
    [[nodiscard]] virtual Fraction Eval(const std::map<std::string, Fraction> &var_map) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Expression> Clone() const                           = 0;

    virtual ~Expression() = default;
};

class Const: virtual public Expression {
public:
    explicit Const(Fraction value);
    [[nodiscard]] Fraction Value() const;
    [[nodiscard]] Fraction Eval(const std::map<std::string, Fraction> &var_map) const override;
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

private:
    Fraction m_value;
};

class Variable: virtual public Expression {
public:
    explicit Variable(std::string name);
    [[nodiscard]] std::string Name() const;
    [[nodiscard]] Fraction Eval(const std::map<std::string, Fraction> &var_map) const override;
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

private:
    std::string m_name;
};

class UnaryOperation: virtual public Expression {
public:
    explicit UnaryOperation(const Expression &argument);
    [[nodiscard]] Fraction Eval(const std::map<std::string, Fraction> &var_map) const override;

    ~UnaryOperation() override = default;
protected:
    [[nodiscard]] virtual Fraction calc(const Fraction &arg) const = 0;

private:
    std::unique_ptr<Expression> m_arg;
};

class BinaryOperation: virtual public Expression {
public:
    explicit BinaryOperation(const Expression &left, const Expression &right);
    [[nodiscard]] Fraction Eval(const std::map<std::string, Fraction> &var_map) const override;

    ~BinaryOperation() override = default;
protected:
    [[nodiscard]] virtual Fraction calc(const Fraction &left, const Fraction &right) const = 0;

private:
    std::unique_ptr<Expression> m_left;
    std::unique_ptr<Expression> m_right;
};

class Add: public BinaryOperation {
public:
    explicit Add(const Expression &left, const Expression &right);
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

protected:
    [[nodiscard]] Fraction calc(const Fraction &left, const Fraction &right) const override;
};

class Subtract: public BinaryOperation {
public:
    explicit Subtract(const Expression &left, const Expression &right);
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

protected:
    [[nodiscard]] Fraction calc(const Fraction &left, const Fraction &right) const override;
};

class Multiply: public BinaryOperation {
public:
    explicit Multiply(const Expression &left, const Expression &right);
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

protected:
    [[nodiscard]] Fraction calc(const Fraction &left, const Fraction &right) const override;
};

class Divide: public BinaryOperation {
public:
    explicit Divide(const Expression &left, const Expression &right);
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

protected:
    [[nodiscard]] Fraction calc(const Fraction &left, const Fraction &right) const override;
};

class Negate: public UnaryOperation {
public:
    explicit Negate(const Expression &argument);
    [[nodiscard]] std::unique_ptr<Expression> Clone() const override;

protected:
    [[nodiscard]] Fraction calc(const Fraction &arg) const override;
};

[[nodiscard]] Add operator+(const Expression &lhs, const Expression &rhs);
[[nodiscard]] Subtract operator-(const Expression &lhs, const Expression &rhs);
[[nodiscard]] Multiply operator*(const Expression &lhs, const Expression &rhs);
[[nodiscard]] Divide operator/(const Expression &lhs, const Expression &rhs);
[[nodiscard]] Negate operator-(const Expression &arg);

#endif  // SMALLTASK56_EXPRESSION_H
