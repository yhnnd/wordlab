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

inline constexpr int maths::factorial(const int n) {
    if ( n > 1 ) {
        return n * factorial(n - 1);
    } else if ( n == 1 ) {
        return 1;
    } else {
        return std::numeric_limits<int>::quiet_NaN();
    }
}

inline float maths::evaluate(const std::string Operator, const std::vector<float> parameters, const std::vector<bool> isParameterValid) {
    float a = 0, b = 0;
    if (isParameterValid[0] == true) {
        a = parameters[0];
    } else {
        a = std::numeric_limits<float>::quiet_NaN();
    }
    if (isParameterValid[1] == true) {
        b = parameters[1];
    } else {
        b = std::numeric_limits<float>::quiet_NaN();
    }

    enum operatorNames operatorName = operatorNames::Unknown;
    const auto operatorsMap = maths::getOperatorsMap();
    for (const auto & tempOperator: operatorsMap) {
        if (Operator == tempOperator.second[0]) {
            operatorName = tempOperator.first;
        }
    }

    float result = 0;

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
            result = std::numeric_limits<float>::quiet_NaN();
            break;
    }
    return result;
}

inline float maths::calc(const std::string expression) {
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
                    const volatile char c = expression[i + operatorLth];
                    if (c == '\0' || isdigit(c) || delimiters.find(c) != std::string::npos) {
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
            return std::numeric_limits<float>::infinity();
        } else if (expression == "pi") {
            return M_PI;// boost::math::constants::pi<float>();
        } else if (expression == "e") {
            return M_E;// boost::math::constants::e<float>();
        } else if (strchr(br1, expression[0]) != nullptr) {
            return calc(expression.substr(1));// recursive
        } else {
            // atof("nan") == nan
            return atof(expression.c_str());// evaluate
        }
    } else {
        float a = 0, b = 0;
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
                return std::numeric_limits<float>::quiet_NaN();
            }
        } else if (currentOperator == "++") {
            if (hasA == true) {
                return (a + 1);
            } else if (hasB == true) {
                return (b + 1);
            } else {
                return std::numeric_limits<float>::quiet_NaN();
            }
        } else if (currentOperator == "--") {
            if (hasA == true) {
                return (a - 1);
            } else if (hasB == true) {
                return (b - 1);
            } else {
                return std::numeric_limits<float>::quiet_NaN();
            }
        } else {
            return evaluate(currentOperator, {a, b}, {hasA, hasB});
        }
    }
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