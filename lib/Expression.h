#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
using namespace std;

//The class expression is used to store all expression of the type 7e1e2 or more generally scalar * k-vector
//The k-vector can be loaded in any base order, however it automatically sorts them

class Expression{
    public:
        int grade;
        double value;
        int * bases;
        
        //using construct function to facilitate reuse
        void construct();
        void construct(double value, double grade, int * bases);
        void construct(double value, const string basestr);
        void construct(const string input);
        void construct(Expression a, Expression b);
        
        Expression();
        Expression(double value, double grade, int * bases);
        Expression(double value, const string basestr);
        Expression(const string input);
        Expression(Expression a, Expression b);//Multiplies two expressions
        
        void sort();
        void simplify();
        bool equalBase(Expression b);

        string toString() const;
};

#endif
