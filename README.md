# Fraction & arithmetic expressions
This is a C++ assignment I got in my university.

## Fraction

`Fraction` type represents a rational number with integer numerator and denominator.

This type supports following operations:
- Default constructing, constructing from an integer, constructing from both numerator and denominator
- Getting a numerator and a denominator: `int64_t Numerator()`, `uint64_t Denominator()`
- Casting to `double` and `std::string`
- Arithmetic operations `+`, `+=`, `-`, `-=`, `*`, `*=`, `/`, `/=`, unary `-`
- Comparison operations: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Stream output: `<<`

Correctness of the result of operations on fractions with huge numerators or denominators is not guaranteed.

## Arithmetic expressions

This library contains a class hierarchy describing expressions and arithmetic operations, such as
`Const`, `Variable`, `Negate`, `Add`, `Subtract`, `Multiply`, `Divide`

An example of constructing `2 * x + 1`:

```
const Add expr(Multiply(Const(2), Variable("x")), Const(1));
```

Same can be done with C++ operators:

```cpp
const Add expr = Const(2) * Variable("x") + Const(1);
```

To evaluate an expression use `Eval` method and pass a string to Fraction map:

```cpp
const Fraction result = expr.Eval({
    {"x", Fraction(100)}
    {"y", Fraction(42)}
}); // 201
```

This library does not handle errors.

## Testing

The repository contains simple tests both for `Fraction.h` and `Arithmetic.h` using Catch2.
