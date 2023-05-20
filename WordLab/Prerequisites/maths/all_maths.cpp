inline std::map<enum maths::operatorNames, std::vector<std::string>> maths::getOperatorsMap() {
    const static std::map<enum maths::operatorNames, std::vector<std::string>> operatorsMap = {
            {maths::operatorNames::Unknown,             {"#", "unknown"}},
            {maths::operatorNames::Addition,            {"+", "plus"}},
            {maths::operatorNames::Subtraction,         {"-", "minus"}},
            {maths::operatorNames::Multiplication,      {"*", "times"}},
            {maths::operatorNames::Division,            {"/", "divided_by"}},
            {maths::operatorNames::Not,                 {"~", "not"}},
            {maths::operatorNames::Modulo,              {"%", "mod"}},
            {maths::operatorNames::Exponentiation,      {"^", "power"}},
            {maths::operatorNames::Factorial,           {"!", "fact"}},
            {maths::operatorNames::Equal,               {"==", "equals"}},
            {maths::operatorNames::LessThan,            {"<", "less_than"}},
            {maths::operatorNames::GreaterThan,         {">", "greater_than"}},
            {maths::operatorNames::PrefixIncrement,     {"++"}},
            {maths::operatorNames::PrefixDecrement,     {"--"}},
            {maths::operatorNames::PostfixIncrement,    {"++"}},
            {maths::operatorNames::PostfixDecrement,    {"--"}}
    };
    return operatorsMap;
}

inline std::string maths::getOperator(enum operatorNames const operatorName) {
    const auto operatorsMap = maths::getOperatorsMap();
    const auto Operator = operatorsMap.find(operatorName);
    if (Operator != operatorsMap.end()) {
        return Operator->second[0];
    } else {
        return operatorsMap.find(operatorNames::Unknown)->second[0];
    }
}

inline std::vector<std::set<std::string>> maths::getOperatorsGroupedByPrecedence() {
    const static std::vector<std::set<std::string>> operators = {
            {/* 0 */}, {/* 1: "+-" */
                    getOperator(maths::operatorNames::Addition),
                    getOperator(maths::operatorNames::Subtraction)
            }, {/* 2: "* /" */
                    getOperator(maths::operatorNames::Multiplication),
                    getOperator(maths::operatorNames::Division)
            }, {/* 3: "~%^!" */
                    getOperator(maths::operatorNames::Not),
                    getOperator(maths::operatorNames::Modulo),
                    getOperator(maths::operatorNames::Exponentiation),
                    getOperator(maths::operatorNames::Factorial)
            }, {/* 4: "<>" */
                    getOperator(maths::operatorNames::LessThan),
                    getOperator(maths::operatorNames::GreaterThan)
            }, {/* 5: "++ -- ==" */
                    getOperator(maths::operatorNames::PostfixIncrement),
                    getOperator(maths::operatorNames::PostfixDecrement),
                    getOperator(maths::operatorNames::Equal)
            }
    };
    return operators;
}

inline int maths::operatorsRight(const std::string s, int br, const std::set<std::string> operators, PKC br1, PKC br2) {
    int i = 0;
    for (i = 0; s[i] != 0; i++) {
        if (strchr(br1, s[i]) != nullptr) {
            ++br;
        }
        if (strchr(br2, s[i]) != nullptr) {
            --br;
        }
        if (br == 0 && operators.find(toString(s[i])) != operators.end()) {
            if (s[i] == '+') {
                if (s[i - 1] != '+' && s[i + 1] != '+') {
                    break;
                }
            } else if (s[i] == '-') {
                if (s[i - 1] != '-' && s[i + 1] != '-') {
                    break;
                }
            } else {
                break;
            }
        }
    }
    if (s[i] != '\0') {
        return i;
    } else {
        return 0;
    }
}

inline constexpr long long maths::factorial(const int n) {
    if ( n > 1 ) {
        return n * factorial(n - 1);
    } else if ( n == 1 ) {
        return 1;
    } else {
        return std::numeric_limits<long long>::quiet_NaN();
    }
}

inline double maths::evaluate(const std::string Operator, const std::vector<double> parameters, const std::vector<bool> isParameterValid) {
    double a = 0, b = 0;
    if (isParameterValid[0] == true) {
        a = parameters[0];
    } else {
        a = std::numeric_limits<double>::quiet_NaN();
    }
    if (isParameterValid[1] == true) {
        b = parameters[1];
    } else {
        b = std::numeric_limits<double>::quiet_NaN();
    }

    enum operatorNames operatorName = operatorNames::Unknown;
    const auto operatorsMap = maths::getOperatorsMap();
    for (const auto & tempOperator: operatorsMap) {
        if (Operator == tempOperator.second[0]) {
            operatorName = tempOperator.first;
        }
    }

    double result = 0;

    switch (operatorName) {
        case operatorNames::Addition:
            result = (a + b);
            break;
        case operatorNames::Subtraction:
            result = (a - b);
            break;
        case operatorNames::Multiplication:
            result = (a * b);
            break;
        case operatorNames::Division:
            result = (a / b);
            break;
        case operatorNames::Not:
            result = !(b);
            break;
        case operatorNames::Modulo:
            result = fmod(a, b);
            break;
        case operatorNames::Exponentiation:
            result = pow(a, b);
            break;
        case operatorNames::Factorial:
            result = maths::factorial(a);
            break;
        case operatorNames::Equal:
            result = (a == b);
            break;
        case operatorNames::LessThan:
            result = (a < b);
            break;
        case operatorNames::GreaterThan:
            result = (a > b);
            break;
        default:
            result = std::numeric_limits<double>::quiet_NaN();
            break;
    }
    return result;
}

inline double maths::calc(const std::string expression) {
    const auto operatorsMap = maths::getOperatorsMap();
    const static std::vector<std::set<std::string>> operators = maths::getOperatorsGroupedByPrecedence();
    PKC br1 = "(", br2 = ")";
    const std::string delimiters = std::string(" .") + br1 + br2;
    int i = 0, bracketLevel = 0;
    std::string currentOperator = "", expressionLeft = "", expressionRight = "";
    for (i = 0; i < expression.length(); i++) {
        if (strchr(br1, expression[i]) != nullptr) {
            bracketLevel++;
        }
        if (strchr(br2, expression[i]) != nullptr) {
            bracketLevel--;
        }
        if (bracketLevel == 0) {
            {
                volatile unsigned short operatorLth = 1;
                for (;; ++operatorLth) {
                    const volatile char cPrev = expression[i + operatorLth - 1];
                    const volatile char c = expression[i + operatorLth];
                    if (c == '\0' || isdigit(c) || delimiters.find(c) != std::string::npos) {
                        break;
                    }
                    if (isalpha(cPrev) == false && isalpha(c) == true) {
                        break;
                    }
                }
                currentOperator = expression.substr(i, operatorLth);
                expressionRight = expression.substr(i + operatorLth);
            }

            // The Highest Precedence: ==, ++, --.
            // 10 ++ - 12 -- + 3 = 3
            //    ^
            if (operators[5].find(currentOperator) != operators[5].end()) {
                if (! operatorsRight(expressionRight, bracketLevel, operators[1], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[2], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[3], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[4], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[5], br1, br2)) {
                    break;
                }
            }

            // Precedence Level 4: <, >.
            // 1 < 5 * 2 - 5 > 1 = 1
            //               ^
            if (operators[4].find(currentOperator) != operators[4].end()) {
                if (! operatorsRight(expressionRight, bracketLevel, operators[1], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[2], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[3], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[4], br1, br2)) {
                    break;
                }
            }

            // Precedence Level 3: ~, %, ^, !.
            // 2 ^ 3 + 2 ^ 3 = 16
            //           ^
            if (operators[3].find(currentOperator) != operators[3].end()) {
                // 2 ^ 3 + 2 ^ 3 = 16
                //           ^
                if (! operatorsRight(expressionRight, bracketLevel, operators[1], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[2], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[3], br1, br2)) {
                    break;
                }
            }

            // Precedence Level 2: *, /.
            // 2 * 2 / 4
            //       ^
            if (operators[2].find(currentOperator) != operators[2].end()) {
                if (! operatorsRight(expressionRight, bracketLevel, operators[1], br1, br2)
                && ! operatorsRight(expressionRight, bracketLevel, operators[2], br1, br2)) {
                    break;
                }
            }

            // Precedence Level 1: +, -.
            // 1 + 2 * 10 - 4 * 5
            //            ^
            // 1 + 2 * 10 - 1 - 20
            //                ^
            if (operators[1].find(currentOperator) != operators[1].end()) {
                if (! operatorsRight(expressionRight, bracketLevel, operators[1], br1, br2)) {
                    break;
                }
            }


        }
    }
    if (i == expression.length()) {
        if (expression == "()") {
            return 0;
        } else if (expression == "inf") {
            return std::numeric_limits<double>::infinity();
        } else if (expression == "pi") {
            return M_PI;
        } else if (expression == "e") {
            return M_E;
        } else if (expression == "sqrt2") {
            return M_SQRT2;
        } else if (strchr(br1, expression[0]) != nullptr) {
            return calc(expression.substr(1));// recursive
        } else {
            // atof("nan") == nan
            return atof(expression.c_str());// evaluate
        }
    } else {
        double a = 0, b = 0;
        bool hasA = false, hasB = false;
        if (i > 0) {
            expressionLeft = std::string(expression).substr(0, i);
            a = calc(expressionLeft);// recursive
            hasA = true;
        }
        if (i + currentOperator.length() < expression.length()) {
            expressionRight = expression.substr(i + currentOperator.length());
            b = calc(expressionRight);// recursive
            hasB = true;
        }
        if (currentOperator == "==") {
            if (hasA == true && hasB == true) {
                return (a == b);
            } else {
                return std::numeric_limits<double>::quiet_NaN();
            }
        } else if (currentOperator == "++") {
            if (hasA == true) {
                return (a + 1);
            } else if (hasB == true) {
                return (b + 1);
            } else {
                return std::numeric_limits<double>::quiet_NaN();
            }
        } else if (currentOperator == "--") {
            if (hasA == true) {
                return (a - 1);
            } else if (hasB == true) {
                return (b - 1);
            } else {
                return std::numeric_limits<double>::quiet_NaN();
            }
        } else {
            return evaluate(currentOperator, {a, b}, {hasA, hasB});
        }
    }
}


inline std::string maths::calculateWithBSVSupported(const std::string expression) {
    const static double M_1_10 = maths::calc("1/10");
    const static double M_1_9 = maths::calc("1/9");
    const static double M_1_8 = maths::calc("1/8");
    const static double M_1_7 = maths::calc("1/7");
    const static double M_1_6 = maths::calc("1/6");
    const static double M_1_5 = maths::calc("1/5");
    const static double M_2_7 = maths::calc("2/7");
    const static double M_3_10 = maths::calc("3/10");
    const static double M_1_3 = maths::calc("1/3"), M_7_3_7 = maths::calc("7/3/7");
    const static double M_3_5 = maths::calc("3/5");
    const static double M_2_3 = maths::calc("2/3");

    const double result = maths::calc(expression);

    const char * format = "<blk-grn>( %s ) <ylw-blk>(\\(%s\\))<blk-blk>(  )";

    char s[128] = "";

    if (result == std::numeric_limits<double>::infinity()) {
        snprintf(s, sizeof(s), format, "inf", "infinity");
    } else if (result == M_PI) {
        snprintf(s, sizeof(s), format, "pi", "3.14159265358979323846264338327950288");
    } else if (result == M_PI_2) {
        snprintf(s, sizeof(s), format, "pi/2", "1.57079632679489661923132169163975144");
    } else if (result == M_1_PI) {
        snprintf(s, sizeof(s), format, "1/pi", "0.318309886183790671537767526745028724");
    } else if (result == M_2_PI) {
        snprintf(s, sizeof(s), format, "2/pi", "0.636619772367581343075535053490057448");
    } else if (result == M_E) {
        snprintf(s, sizeof(s), format, "e", "2.71828182845904523536028747135266250");
    } else if (result == M_SQRT2) {
        snprintf(s, sizeof(s), format, "sqrt2", "1.41421356237309504880168872420969808");
    } else if (result == M_SQRT1_2) {
        snprintf(s, sizeof(s), format, "sqrt2/2", "0.707106781186547524400844362104849039");
    } else if (result == M_1_10) {
        snprintf(s, sizeof(s), format, "1/10", "0.1");
    } else if (result == M_1_9) {
        snprintf(s, sizeof(s), format, "1/9", "0.111111111111111111111111111111111111");
    } else if (result == M_1_8) {
        snprintf(s, sizeof(s), format, "1/8", "0.125");
    } else if (result == M_1_7) {
        snprintf(s, sizeof(s), format, "1/7", "0.142857142857142857142857142857142857");
    } else if (result == M_2_7) {
        snprintf(s, sizeof(s), format, "2/7", "0.285714285714285714285714285714285714");
    } else if (result == M_1_6) {
        snprintf(s, sizeof(s), format, "1/6", "0.16666666666666666666666666666666666");
    } else if (result == M_1_5) {
        snprintf(s, sizeof(s), format, "1/5", "0.2");
    } else if (result == M_3_10) {
        snprintf(s, sizeof(s), format, "3/10", "0.3");
    } else if (result == M_1_3 || result == M_7_3_7) {
        snprintf(s, sizeof(s), format, "1/3", "0.33333333333333333333333333333333333");
    } else if (result == M_3_5) {
        snprintf(s, sizeof(s), format, "3/5", "0.6");
    } else if (result == M_2_3) {
        snprintf(s, sizeof(s), format, "2/3", "0.66666666666666666666666666666666666");
    } else if (std::floor(result) != result) {
        snprintf(s, sizeof(s), "%lf <red-blk>(\\(%.*f\\))<blk-blk>(  )", result, 17, result);
    } else {
        snprintf(s, sizeof(s), "%ld", static_cast<long>(result));
    }
    return s;
}


int maths::filter(int n, int *flags, int *length) {
    int r;
    for(r = 0; r < *length; r++) {
        if(flags[r] == n) {
            return r;
        }
    }
    flags[r++] = n;
    *length = r;
    return 0;
}