#ifndef MULTIVECTOR_H_
#define MULTIVECTOR_H_
#include <string>
#include <vector>
#include "Expression.h"
using namespace std;

//store multiple expressions that represent a multivector
class Multivector{
    public:
    vector<Expression> exp;

    Multivector();
    Multivector(Expression e);
    Multivector(const string s);

    Multivector copy(Multivector a);
    
    void addExpression(Expression e);
    void addExpression(double v, string s);
    void addExpression(const string s);
    
    static bool compare(Expression a, Expression b);//used for the vector template's sort() function
    void sort();
    void removeZeros();
    void simplify();
    
    double scalar();
 
    Multivector add(Multivector a, Multivector b);   
    Multivector multiply(Multivector a, Multivector b);
    Multivector scalarMultiply(double d, Multivector a);
    Multivector inverse(Multivector v);
    Multivector inverse();
    Multivector conjugate(Multivector v);
    Multivector conjugate();

    string toString() const;
};
ostream& operator<< ( ostream& outs, const Multivector obj ) ;
Multivector operator*(Multivector a, Multivector b);
Multivector operator*(double a, Multivector b);
Multivector operator*(Multivector b,double a);
Multivector operator/(Multivector a, Multivector b);
Multivector operator/(Multivector a, double b);
Multivector operator/(double b, Multivector a);
Multivector operator+(Multivector a, Multivector b);
Multivector operator+(Multivector a, double b );
Multivector operator+(double b, Multivector a);
Multivector operator-(Multivector a, Multivector b);
Multivector operator-(Multivector a, double b );
Multivector operator-(double b, Multivector a);
Multivector operator-(Multivector a);
#endif
