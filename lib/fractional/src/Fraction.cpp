#include "Fraction.h"

#include <numeric>

static bool multiply_overflow(std::uint64_t a, std::uint64_t b) {
    std::uint64_t x = a * b;
    return b != 0 && x / b != a;
}

static void reduce_pair(std::uint64_t &a, std::uint64_t &b) {
    std::uint64_t g = std::gcd(a, b);
    a /= g;
    b /= g;
}

static void reduce_pair(std::int64_t &a, std::uint64_t &b) {
    std::uint64_t g = std::gcd(a, b);
    a /= static_cast<int64_t>(g);
    b /= g;
}

Fraction::Fraction(std::int64_t integer) : m_numerator(integer) {}

Fraction::Fraction(std::int64_t numerator, std::uint64_t denominator)
    : m_numerator(numerator), m_denominator(denominator) {
    Normalize();
}

Fraction &Fraction::Normalize() {
    reduce_pair(m_numerator, m_denominator);
    if (m_numerator == 0) {
        m_denominator = 1;
    }
    return *this;
}

std::int64_t Fraction::Numerator() const noexcept {
    return m_numerator;
}

std::uint64_t Fraction::Denominator() const noexcept {
    return m_denominator;
}
int Fraction::Sign() const noexcept {
    return m_numerator > 0 ? 1 : m_numerator < 0 ? -1 : 0;
}

std::string Fraction::ToString() const {
    if (m_numerator == 0) {
        return "0";
    }
    if (m_denominator == 1) {
        return std::to_string(m_numerator);
    }
    return std::to_string(m_numerator).append("/").append(std::to_string(m_denominator));
}

Fraction::operator double() const {
    return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
}

Fraction Fraction::Inverse() const {
    if (Sign() < 0) {
        return Fraction(-static_cast<std::int64_t>(m_denominator), static_cast<std::uint64_t>(-m_numerator));
    } else {
        return Fraction(static_cast<std::int64_t>(m_denominator), static_cast<std::uint64_t>(m_numerator));
    }
}

std::ostream &operator<<(std::ostream &stream, const Fraction &fraction) {
    return stream << fraction.ToString();
}

Fraction &Fraction::operator+=(const Fraction &other) {
    std::uint64_t other_denominator = other.m_denominator;
    reduce_pair(this->m_denominator, other_denominator);
    this->m_numerator = this->m_numerator * static_cast<std::int64_t>(other_denominator) +
                        other.m_numerator * static_cast<std::int64_t>(this->m_denominator);
    this->m_denominator *= other.m_denominator;
    return this->Normalize();
}
Fraction &Fraction::operator-=(const Fraction &other) {
    return *this += -other;
}
Fraction &Fraction::operator*=(const Fraction &other) {
    std::int64_t other_num    = other.m_numerator;
    std::uint64_t other_denom = other.m_denominator;
    reduce_pair(this->m_numerator, other_denom);
    reduce_pair(other_num, this->m_denominator);
    this->m_numerator *= other_num;
    this->m_denominator *= other_denom;
    return *this;
}
Fraction &Fraction::operator/=(const Fraction &other) {
    return *this *= other.Inverse();
}
Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
    Fraction temp = lhs;
    temp += rhs;
    return temp;
}
Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
    Fraction temp = lhs;
    temp -= rhs;
    return temp;
}
Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
    Fraction temp = lhs;
    temp *= rhs;
    return temp;
}
Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
    Fraction temp = lhs;
    temp /= rhs;
    return temp;
}
Fraction operator-(const Fraction &arg) {
    return Fraction(-arg.Numerator(), arg.Denominator());
}

bool operator==(const Fraction &lhs, const Fraction &rhs) {
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

bool operator!=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Fraction &lhs, const Fraction &rhs) {
    if (multiply_overflow(lhs.Numerator(), rhs.Denominator()) ||
        multiply_overflow(rhs.Numerator(), lhs.Denominator())) {
        return static_cast<double>(lhs) < static_cast<double>(rhs);
    }
    return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

bool operator<=(const Fraction &lhs, const Fraction &rhs) {
    return rhs >= lhs;
}

bool operator>(const Fraction &lhs, const Fraction &rhs) {
    return rhs < lhs;
}

bool operator>=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs < rhs);
}
