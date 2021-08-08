#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../lib/Multivector.h"
#include "../lib/Expression.h"
using namespace std;

//store multiple expressions that represent a multivector
Multivector::Multivector(){}
Multivector::Multivector(Expression e){
    addExpression(e);
}
Multivector::Multivector(const string s){
    addExpression(s);
}

Multivector Multivector::copy(Multivector a){
    int i;
    Multivector c;
    for(i=0;i<a.exp.size();i++){
        c.addExpression(Expression(
                    a.exp.at(i).value,
                    a.exp.at(i).grade,
                    a.exp.at(i).bases));
    }
    simplify();
    return c;
}

void Multivector::addExpression(Expression e){
    exp.push_back(e);
    simplify();
}
void Multivector::addExpression(double v, string s){
    addExpression(Expression(v,s));
}
void Multivector::addExpression(const string s){
    int start = 0;
    int end = 0;
    while(true){
        for(;s.c_str()[end]!= '+' && s.c_str()[end]!='\0';end++);
        string str2 = &(s.c_str()[start]);
        str2[end-start]='\0';
        addExpression(Expression(str2.c_str()));
        if(s.c_str()[end] == '\0')break;
        end++;
        start=end;
    }
}

//used for the vector template's sort() function
bool Multivector::compare(Expression a, Expression b){
    if(a.grade > b.grade)return false;
    else if(a.grade < b.grade)return true;
    else{
        int i;
        for(i=0;i<a.grade;i++){
            if(a.bases[i] > b.bases[i])return false;
            else if(a.bases[i] < b.bases[i])return true;
        }
    }
    return true;
}
void Multivector::sort(){
    std::sort(exp.begin(),exp.end(),compare);
}
void Multivector::removeZeros(){
    int i;
    for(i=0;i<exp.size();i++){
        if(abs(exp.at(i).value) < pow(10,-12)){
            exp.erase(exp.begin()+i);
            i--;
        }
    }
}
//after sorting expressions by grade it adds equal bases
void Multivector::simplify(){
    sort();
    int i;
    for(i=0;i+1<exp.size();i++){
        if(exp.at(i).equalBase(exp.at(i+1))){
            exp.at(i).value+=exp.at(i+1).value;
            exp.erase(exp.begin()+i+1);
            i--;
        }
    }
    removeZeros();
}

double Multivector::scalar(){
    if(exp.at(0).grade > 0)return 0;
    return exp.at(0).value;
}

Multivector Multivector::add(Multivector a, Multivector b){
    Multivector c;
    int i;
    for(i=0;i<a.exp.size();i++){
        c.addExpression(Expression(
                    a.exp.at(i).value,
                    a.exp.at(i).grade,
                    a.exp.at(i).bases));
    }
    for(i=0;i<b.exp.size();i++){
        c.addExpression(Expression(
                    b.exp.at(i).value,
                    b.exp.at(i).grade,
                    b.exp.at(i).bases));
    }
    c.simplify();
    return c;
}
Multivector Multivector::multiply(Multivector a, Multivector b){
    Multivector c;
    int i,j;
    for(i=0;i<a.exp.size();i++){
        for(j=0;j<b.exp.size();j++){
        c.addExpression(Expression(
                    Expression(
                    a.exp.at(i).value,
                    a.exp.at(i).grade,
                    a.exp.at(i).bases),
                    Expression(
                    b.exp.at(j).value,
                    b.exp.at(j).grade,
                    b.exp.at(j).bases)));
        }
    }
    c.simplify();
    return c;
}
Multivector Multivector::scalarMultiply(double d, Multivector a){
    Multivector c;
    int i,j;
    for(i=0;i<a.exp.size();i++){
        c.addExpression(Expression(
                    d*a.exp.at(i).value,
                    a.exp.at(i).grade,
                    a.exp.at(i).bases));
    }
    c.simplify();
    return c;
}
Multivector Multivector::inverse(Multivector v){
    int i;
    Multivector r;
    double mod = 0;
    for(i=0;i<v.exp.size();i++)
        mod+=pow(v.exp.at(i).value,2);

    for(i=0;i<v.exp.size();i++)
        r.addExpression(Expression(
                    v.exp.at(i).value/mod,
                    v.exp.at(i).grade,
                    v.exp.at(i).bases));

    return r;
}
Multivector Multivector::inverse(){
    return inverse(*this);
}

Multivector Multivector::conjugate(Multivector v){
    int i;
    double d = v.scalar();
    return 2*d - v;
}
Multivector Multivector::conjugate(){
    return conjugate(*this);
}

string Multivector::toString() const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);
    int i;
    if((int)exp.size() == 0)
        oss << "0";
    for(i=0;i<exp.size();i++){
        oss << exp.at(i).toString();
        if(i<exp.size()-1)oss << " + ";
    }
    return oss.str();
}
ostream& operator<< ( ostream& outs, const Multivector obj ) {    return outs << obj.toString();}
Multivector operator*(Multivector a, Multivector b){    return a.multiply(a,b);}
Multivector operator*(double a, Multivector b){    return b.scalarMultiply(a,b);}
Multivector operator*(Multivector b,double a){    return b.scalarMultiply(a,b);}
Multivector operator+(Multivector a, Multivector b){    return a.add(a,b);}
Multivector operator+(Multivector a, double b ){    return a.add(a, Multivector(Expression(b,0,NULL)));}
Multivector operator+(double b, Multivector a){    return a.add(a, Multivector(Expression(b,0,NULL)));}
Multivector operator/(Multivector a, Multivector b){    return a.multiply(a,b.inverse());}
Multivector operator/(Multivector a, double b){    return a*(1/b);}
Multivector operator/(double b, Multivector a){    return b*a.inverse();}
Multivector operator-(Multivector a, Multivector b){    return a+(-1*b);}
Multivector operator-(Multivector a, double b ){    return a+(-b);}
Multivector operator-(double b, Multivector a){    return b+(-1*a);}
Multivector operator-(Multivector a){    return (-1*a);}
