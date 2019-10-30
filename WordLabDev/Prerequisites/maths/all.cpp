#include "operatorRight.cpp"
constexpr int maths::fact(const int n){
	return (n<1)?std::numeric_limits<int>::quiet_NaN():(n==1)?1:n*fact(n-1);
}
#include "calc.cpp"
#include "calc_expr.cpp"
#include "filter.cpp"
