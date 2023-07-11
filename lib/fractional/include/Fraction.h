#include <cstdint>
#include <iostream>
#ifndef FRACTIONAL_FRACTION_H
#define FRACTIONAL_FRACTION_H

class Fraction {
public:
    Fraction() = default;
    Fraction(std::int64_t integer);
    explicit Fraction(std::int64_t numerator, std::uint64_t denominator);

    [[nodiscard]] std::int64_t Numerator() const noexcept;
    [[nodiscard]] std::uint64_t Denominator() const noexcept;

    explicit operator double() const;
    [[nodiscard]] std::string ToString() const;

    Fraction &operator+=(const Fraction &other);
    Fraction &operator-=(const Fraction &other);
    Fraction &operator*=(const Fraction &other);
    Fraction &operator/=(const Fraction &other);

    [[nodiscard]] Fraction Inverse() const;

private:
    std::int64_t m_numerator{0};
    std::uint64_t m_denominator{1};

    [[nodiscard]] int Sign() const noexcept;
    Fraction &Normalize();
};

[[nodiscard]] Fraction operator+(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] Fraction operator-(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] Fraction operator*(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] Fraction operator/(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] Fraction operator-(const Fraction &arg);

[[nodiscard]] bool operator==(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] bool operator!=(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] bool operator<(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] bool operator<=(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] bool operator>(const Fraction &lhs, const Fraction &rhs);
[[nodiscard]] bool operator>=(const Fraction &lhs, const Fraction &rhs);

std::ostream &operator<<(std::ostream &stream, const Fraction &fraction);

#endif  // FRACTIONAL_FRACTION_H
