#include <catch2/catch_test_macros.hpp>

#include "Expression.h"
#include "Fraction.h"

TEST_CASE("Initialization and view", "[Fraction]") {
    SECTION("zero") {
        REQUIRE(Fraction().ToString() == "0");
        REQUIRE(static_cast<double>(Fraction()) == 0.0);
        REQUIRE(Fraction(0).ToString() == "0");
        REQUIRE(static_cast<double>(Fraction(0)) == 0.0);
        REQUIRE(Fraction(0, 1).ToString() == "0");
        REQUIRE(static_cast<double>(Fraction(0, 1)) == 0.0);
        REQUIRE(Fraction(0, 37).ToString() == "0");
        REQUIRE(static_cast<double>(Fraction(0, 37)) == 0.0);
    }
    SECTION("from integer") {
        REQUIRE(Fraction(1).ToString() == "1");
        REQUIRE(static_cast<double>(Fraction(1)) == 1.0);
        REQUIRE(Fraction(-1).ToString() == "-1");
        REQUIRE(static_cast<double>(Fraction(-1)) == -1.0);
        REQUIRE(Fraction(2).ToString() == "2");
        REQUIRE(static_cast<double>(Fraction(2)) == 2.0);
        REQUIRE(Fraction(-4572).ToString() == "-4572");
        REQUIRE(static_cast<double>(Fraction(-4572)) == -4572.0);
        REQUIRE(Fraction(1000000).ToString() == "1000000");
        REQUIRE(static_cast<double>(Fraction(1000000)) == 1000000.0);
    }
    SECTION("explicit") {
        REQUIRE(Fraction(2, 3).ToString() == "2/3");
        REQUIRE(static_cast<double>(Fraction(2, 3)) == 2.0 / 3.0);
        REQUIRE(Fraction(1, 1).ToString() == "1");
        REQUIRE(static_cast<double>(Fraction(1, 1)) == 1.0);
        REQUIRE(Fraction(-4, 1).ToString() == "-4");
        REQUIRE(static_cast<double>(Fraction(-4, 1)) == -4.0);
        REQUIRE(Fraction(4, 3).ToString() == "4/3");
        REQUIRE(static_cast<double>(Fraction(4, 3)) == 4.0 / 3.0);
        REQUIRE(Fraction(-1, 7).ToString() == "-1/7");
        REQUIRE(static_cast<double>(Fraction(-1, 7)) == -1.0 / 7.0);
        REQUIRE(Fraction(3, 7).ToString() == "3/7");
        REQUIRE(static_cast<double>(Fraction(3, 7)) == 3.0 / 7.0);
    }
    SECTION("reducing") {
        REQUIRE(Fraction(2, 4).ToString() == "1/2");
        REQUIRE(static_cast<double>(Fraction(2, 4)) == 0.5);
        REQUIRE(Fraction(24, 8).ToString() == "3");
        REQUIRE(static_cast<double>(Fraction(24, 8)) == 3.0);
        REQUIRE(Fraction(28, 21).ToString() == "4/3");
        REQUIRE(static_cast<double>(Fraction(28, 21)) == 4.0 / 3.0);
        REQUIRE(Fraction(-88, 121).ToString() == "-8/11");
        REQUIRE(static_cast<double>(Fraction(-88, 121)) == -8.0 / 11.0);
    }
    SECTION("copying") {
        Fraction f = Fraction(3, 5);
        REQUIRE(f.ToString() == "3/5");
        REQUIRE(static_cast<double>(f) == 3.0 / 5.0);
        REQUIRE(Fraction(f).ToString() == "3/5");
        REQUIRE(static_cast<double>(Fraction(f)) == 3.0 / 5.0);
        Fraction ff = f;
        REQUIRE(ff.ToString() == "3/5");
        REQUIRE(static_cast<double>(ff) == 3.0 / 5.0);
    }
}

TEST_CASE("Comparison", "[Fraction]") {
    SECTION("equal") {
        REQUIRE(Fraction() == Fraction());
        REQUIRE(Fraction() == Fraction(0));
        REQUIRE(Fraction() == Fraction(0, 1));
        REQUIRE(Fraction() == Fraction(0, 32));
        REQUIRE(Fraction(1) == Fraction(1));
        REQUIRE(Fraction(5) == Fraction(5, 1));
        REQUIRE(Fraction(-1) == Fraction(-2, 2));
        REQUIRE(Fraction(54) == Fraction(162, 3));
        REQUIRE(Fraction(2, 3) == Fraction(2, 3));
        REQUIRE(Fraction(1, 2) == Fraction(5, 10));
        REQUIRE(Fraction(-33, 121) == Fraction(-3, 11));
        REQUIRE_FALSE(Fraction() == Fraction(1));
        REQUIRE_FALSE(Fraction(2) == Fraction(1));
        REQUIRE_FALSE(Fraction(2, 3) == Fraction(2, 4));
        REQUIRE_FALSE(Fraction(2) == Fraction(3, 2));
        REQUIRE_FALSE(Fraction(10, 7) == Fraction(10000, 7001));
    }
    SECTION("unequal") {
        REQUIRE(Fraction(0, 5) != Fraction(1));
        REQUIRE(Fraction(-2, 3) != Fraction(1, 2));
        REQUIRE(Fraction(5) != Fraction(1, 5));
        REQUIRE_FALSE(Fraction(5, 10) != Fraction(1, 2));
        REQUIRE_FALSE(Fraction(7, 5) != Fraction(7, 5));
        REQUIRE_FALSE(Fraction(5) != Fraction(5, 1));
    }
    SECTION("lesser") {
        REQUIRE(Fraction(5) < Fraction(6));
        REQUIRE(Fraction(-4) < Fraction(-3));
        REQUIRE(Fraction(-4) < Fraction(-3, 2));
        REQUIRE(Fraction(-10) < Fraction(-20, 11));
        REQUIRE(Fraction(0) < Fraction(1));
        REQUIRE(Fraction(2) < Fraction(6, 2));
        REQUIRE(Fraction(5) < Fraction(26, 5));
        REQUIRE_FALSE(Fraction(1) < Fraction());
        REQUIRE_FALSE(Fraction(2, 3) < Fraction(2, 4));
        REQUIRE_FALSE(Fraction(12) < Fraction(0));
        REQUIRE_FALSE(Fraction(-12) < Fraction(-12));
    }
    SECTION("greater") {
        REQUIRE(Fraction(1) > Fraction());
        REQUIRE(Fraction(2, 3) > Fraction(2, 4));
        REQUIRE(Fraction(12) > Fraction(0));
        REQUIRE(Fraction(47, 5) > Fraction(9));
        REQUIRE(Fraction(42, 5) > Fraction(43, 6));
        REQUIRE_FALSE(Fraction() > Fraction(0));
        REQUIRE_FALSE(Fraction(5) > Fraction(6));
        REQUIRE_FALSE(Fraction(-4) > Fraction(-3, 2));
        REQUIRE_FALSE(Fraction(-10) > Fraction(-20, 11));
        REQUIRE_FALSE(Fraction(0) > Fraction(1));
        REQUIRE_FALSE(Fraction(5) > Fraction(26, 5));
        REQUIRE_FALSE(Fraction(-12) > Fraction(-12));
        REQUIRE_FALSE(Fraction(0) > Fraction(0));
    }
    SECTION("le") {
        REQUIRE(Fraction() <= Fraction());
        REQUIRE(Fraction() <= Fraction(1));
        REQUIRE(Fraction(2, 3) <= Fraction(2, 3));
        REQUIRE_FALSE(Fraction(3, 2) <= Fraction(2, 3));
        REQUIRE_FALSE(Fraction(8) <= Fraction(2));
    }
    SECTION("ge") {
        REQUIRE(Fraction() >= Fraction());
        REQUIRE(Fraction(2) >= Fraction(0));
        REQUIRE(Fraction(2, 3) >= Fraction(2, 3));
        REQUIRE(Fraction(25, 7) >= Fraction(3));
        REQUIRE_FALSE(Fraction(2, 3) >= Fraction(2, 2));
        REQUIRE_FALSE(Fraction(6, 7) >= Fraction(1));
    }
}

TEST_CASE("Methods", "[Fraction]") {
    SECTION("Numerator()") {
        REQUIRE(Fraction(3, 5).Numerator() == 3);
        REQUIRE(Fraction().Numerator() == 0);
        REQUIRE(Fraction(-5).Numerator() == -5);
        REQUIRE(Fraction(4, 10).Numerator() == 2);
    }
    SECTION("Denominator()") {
        REQUIRE(Fraction(3, 5).Denominator() == 5);
        REQUIRE(Fraction().Denominator() == 1);
        REQUIRE(Fraction(-5).Denominator() == 1);
        REQUIRE(Fraction(4, 10).Denominator() == 5);
    }
    SECTION("Inverse()") {
        REQUIRE(Fraction(1).Inverse() == Fraction(1));
        REQUIRE(Fraction(3, 5).Inverse() == Fraction(5, 3));
        REQUIRE(Fraction(-4, 7).Inverse() == Fraction(-7, 4));
        REQUIRE(Fraction(10).Inverse() == Fraction(1, 10));
        REQUIRE(Fraction(-9).Inverse() == Fraction(-1, 9));
        REQUIRE(Fraction(8, 3).Inverse() == Fraction(3, 8));
    }
}

TEST_CASE("Operations", "[Fraction]") {
    SECTION("+") {
        Fraction f1 = Fraction(3, 5);
        Fraction f2 = Fraction(7, 3);
        REQUIRE((f1 + f2 == Fraction(44, 15) && f1 == Fraction(3, 5) && f2 == Fraction(7, 3)));

        REQUIRE(Fraction() + Fraction() == Fraction());
        REQUIRE(Fraction(5) + Fraction(2) == Fraction(7));
        REQUIRE(Fraction(1, 5) + Fraction(1, 5) == Fraction(2, 5));
        REQUIRE(Fraction(1) + Fraction() == Fraction(1, 1));
        REQUIRE(Fraction(3, 7) + Fraction(4, 7) == Fraction(1));
        REQUIRE(Fraction(10, 2) + Fraction(3) == Fraction(8));
        REQUIRE(Fraction(2, 3) + Fraction(4, 9) == Fraction(10, 9));
        REQUIRE(Fraction(1, 3) + Fraction(1, 2) == Fraction(5, 6));
        REQUIRE(Fraction(4, 3) + Fraction(2, 7) == Fraction(34, 21));
        REQUIRE(Fraction(-4) + Fraction(5) == Fraction(1));
        REQUIRE(Fraction(-3, 5) + Fraction(2) == Fraction(7, 5));
        REQUIRE(Fraction(-2, 8) + Fraction(-3, 9) == Fraction(-7, 12));
    }
    SECTION("-") {
        Fraction f1 = Fraction(3, 5);
        Fraction f2 = Fraction(7, 3);
        REQUIRE((f1 - f2 == Fraction(-26, 15) && f1 == Fraction(3, 5) && f2 == Fraction(7, 3)));

        REQUIRE(Fraction() - Fraction() == Fraction());
        REQUIRE(Fraction(1) - Fraction(1) == Fraction());
        REQUIRE(Fraction(1, 5) - Fraction(-1, 5) == Fraction(2, 5));
        REQUIRE(Fraction(3, 7) - Fraction(2, 9) == Fraction(13, 63));
        REQUIRE(Fraction(-57, 9) - Fraction(-23, 7) == Fraction(-64, 21));
    }
    SECTION("*") {
        Fraction f1 = Fraction(3, 5);
        Fraction f2 = Fraction(7, 3);
        REQUIRE((f1 * f2 == Fraction(7, 5) && f1 == Fraction(3, 5) && f2 == Fraction(7, 3)));

        REQUIRE(Fraction() * Fraction() == Fraction());
        REQUIRE(Fraction() * Fraction(5, 2) == Fraction());
        REQUIRE(Fraction(5) * Fraction(2) == Fraction(10));
        REQUIRE(Fraction(1, 5) * Fraction(1, 5) == Fraction(1, 25));
        REQUIRE(Fraction(-1) * Fraction(-5, 7) == Fraction(5, 7));
        REQUIRE(Fraction(3, 7) * Fraction(4, 7) == Fraction(12, 49));
        REQUIRE(Fraction(10, 2) * Fraction(3) == Fraction(15));
        REQUIRE(Fraction(2, 3) * Fraction(4, 9) == Fraction(8, 27));
        REQUIRE(Fraction(1, 3) * Fraction(1, 2) == Fraction(1, 6));
        REQUIRE(Fraction(21, 10) * Fraction(2, 7) == Fraction(3, 5));
        REQUIRE(Fraction(-4) * Fraction(5) == Fraction(-20));
    }
    SECTION("/") {
        Fraction f1 = Fraction(3, 5);
        Fraction f2 = Fraction(7, 3);
        REQUIRE((f1 / f2 == Fraction(9, 35) && f1 == Fraction(3, 5) && f2 == Fraction(7, 3)));

        REQUIRE(Fraction() / Fraction(3, 5) == Fraction());
        REQUIRE(Fraction() / Fraction(1) == Fraction());
        REQUIRE(Fraction(3, 7) / Fraction(1) == Fraction(3, 7));
        REQUIRE(Fraction(5, 9) / Fraction(2) == Fraction(5, 18));
        REQUIRE(Fraction(7, 3) / Fraction(3, 7) == Fraction(49, 9));
        REQUIRE(Fraction(-1, 2) / Fraction(2, 3) == Fraction(-3, 4));
        REQUIRE(Fraction(-5, 2) / Fraction(-1, 3) == Fraction(15, 2));
    }
    SECTION("unary -") {
        Fraction f = Fraction(3, 8);
        REQUIRE((-f == Fraction(-3, 8) && f == Fraction(3, 8)));

        REQUIRE(-Fraction() == Fraction());
        REQUIRE(-Fraction(5) == Fraction(-5));
        REQUIRE(-Fraction(10, 2) == Fraction(-5));
        REQUIRE(-Fraction(5, 7) == Fraction(-5, 7));
    }
    SECTION("mutable") {
        Fraction f = Fraction(4, 5);
        REQUIRE(((f *= 5) == Fraction(4) && f == Fraction(4)));
        REQUIRE(((f += Fraction(3, 7)) == Fraction(31, 7) && f == Fraction(31, 7)));
        REQUIRE(((f -= Fraction(8, 9)) == Fraction(223, 63) && f == Fraction(223, 63)));
        REQUIRE(((f /= 2) == Fraction(223, 126) && f == Fraction(223, 126)));
    }
    SECTION("complex") {
        REQUIRE(Fraction(2, 3) * Fraction(3, 2) / Fraction(45) == Fraction(1, 45));
        REQUIRE(Fraction() + Fraction(45) - Fraction() == Fraction(45));
        REQUIRE(Fraction(5) == (Fraction() + Fraction(5, 6)) * Fraction(6));
        REQUIRE(Fraction(1) / Fraction(7) == Fraction(1, 7));
        REQUIRE(Fraction(3, 2) * Fraction(3, 8) + Fraction(1, 3) * Fraction(5, 7) == Fraction(269, 336));
        REQUIRE(Fraction(3, 2) * Fraction(3, 8) / (Fraction(1, 3) + Fraction(5, 7)) == Fraction(189, 352));
    }
}

TEST_CASE("Expressions", "[Expression]") {
    REQUIRE(Const(Fraction(2, 3)).Eval({}) == Fraction(2, 3));
    REQUIRE(Const(Fraction()).Eval({}) == Fraction(0));
    REQUIRE(Const(Fraction(-4, 6)).Eval({}) == Fraction(-2, 3));

    REQUIRE(Variable("x").Eval({{"x", Fraction(10)}}) == Fraction(10));
    REQUIRE(Variable("y").Eval({{"x", Fraction(10)}}) == Fraction(0));
    REQUIRE(Variable("sdhfdsg").Eval({{"y", Fraction(5)}, {"sdhfdsg", Fraction(10)}}) == Fraction(10));

    REQUIRE(Negate(Const(10)).Eval({}) == Fraction(-10));
    REQUIRE(Add(Const(10), Const(10)).Eval({}) == Fraction(20));
    REQUIRE(Multiply(Const(10), Const(10)).Eval({}) == Fraction(100));
    REQUIRE(Divide(Const(10), Const(10)).Eval({}) == Fraction(1));
    REQUIRE(Subtract(Const(10), Const(10)).Eval({}) == Fraction(0));

    REQUIRE(Subtract(Const(10), Variable("x")).Eval({{"x", 5}}) == Fraction(5));
    REQUIRE(Add(Variable("z"), Variable("x")).Eval({{"x", 5}, {"z", 16}}) == Fraction(21));
    REQUIRE(Subtract(Const(Fraction(3, 5)), Variable("x")).Eval({{"x", Fraction(1, 5)}}) == Fraction(2, 5));
    REQUIRE(Add(Variable("z"), Variable("x")).Eval({{"x", Fraction(3, 6)}, {"z", Fraction(1, 8)}}) == Fraction(5, 8));

    REQUIRE(Add(Multiply(Const(2), Variable("x")), Const(1)).Eval({{"x", 7}}) == Fraction(15));
    REQUIRE(Multiply(Add(Const(2), Variable("z")), Const(1)).Eval({{"z", 8}}) == Fraction(10));
    REQUIRE(Add(Multiply(Variable("x"), Variable("x")),
                Add(Multiply(Variable("y"), Variable("y")), Multiply(Variable("z"), Variable("z"))))
                .Eval({{"x", 4}, {"y", -2}, {"z", 3}}) == Fraction(29));
    REQUIRE(Add(Add(Multiply(Variable("x"), Variable("x")), Multiply(Variable("y"), Variable("y"))),
                Multiply(Variable("z"), Variable("z")))
                .Eval({{"x", 4}, {"y", -2}, {"z", 3}}) == Fraction(29));
    //    REQUIRE(Divide(Multiply(Const(1), Variable("x"))));

    REQUIRE(Const(10).Eval({}) == 10);
    const Add expr(Multiply(Const(2), Variable("x")), Const(1));
}
