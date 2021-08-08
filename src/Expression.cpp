//This program calculates all basic operations between multivectors

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../lib/Expression.h"
using namespace std;

//using construct function to facilitate reuse
void Expression::construct(double value, double grade, int * bases){
    this->value = value;
    this->grade = grade;
    this->bases = (int*)malloc(sizeof(int)*grade);
    for(int i=0;i<grade;i++)this->bases[i]=bases[i];
    simplify();
}
void Expression::construct(){
    this->value = 0;
    this->grade = 0;
}
Expression::Expression(){
    construct();
}
Expression::Expression(double value, double grade, int * bases){
    construct(value,grade,bases);
}
Expression::Expression(Expression a, Expression b){
    construct(a,b);
}

//Multiplies two expressions
void Expression::construct(Expression a, Expression b){
    this->value = a.value*b.value;
    this->grade = a.grade+b.grade;
    this->bases = (int*)malloc(sizeof(int)*grade);
    for(int i=0;i<grade;i++){
        if(i<a.grade)this->bases[i]=a.bases[i];
        else this->bases[i]=b.bases[i-a.grade];
    }
    simplify();
}
Expression::Expression(double value, const string basestr){
    construct(value,basestr);
}
void Expression::construct(double value, const string basestr){
    const char * bstr = basestr.c_str();
    this->value = value;
    int i=0;
    grade = 0;
    while(bstr[i]!='\0'){
        if(bstr[i]=='e')grade++;
        i++;
    }
    bases = (int*)malloc(sizeof(int)*grade);
    i=0;
    int j=0;
    while(true){
        while(bstr[i]!='e' && bstr[i]!='\0')i++;
        if(bstr[i]=='\0')break;
        sscanf(&bstr[i],"e%d",&bases[j]);
        j++;
        i++;
    }
    simplify();
}
Expression::Expression(const string input){
    construct(input);
}
void Expression::construct(const string input){
    double value;
    const char * str = input.c_str();
    int i=0;
    while(str[i]!='e' && str[i]!='\0')
        i++;
    string str2 = input;
    str2[i] = '\0';
    int retv = sscanf(str2.c_str(),"%lf",&value);
    if(retv == EOF){
        value=1;
        for(i=0;input.c_str()[i] != 'e' && input.c_str()[i] != '\0';i++)if(input.c_str()[i] == '-'){
            value = -1;
            break;
        }
    }
    construct(value,&str[i]);
}

//sorts bases
void Expression::sort(){
    int i,j;
    int t;
    int nochange;
    for(i=0;i<grade;i++){
        nochange = true;
        for(j=1;j<grade-i;j++){
            if(bases[j-1]>bases[j]){
                nochange = false;
                value = -value;
                t = bases[j-1];
                bases[j-1]=bases[j];
                bases[j]=t;
            }
        }
        if(nochange)break;
    }
}

//with the bases sorted it can count if there are even or odd number of equal bases
//if even the bases multiply to 1
//else it multiplies to itself
void Expression::simplify(){
    sort();
    int v = bases[0];
    int count = 0;
    int i=0;
    int vsize = 0;
    while(i<grade){
        v=bases[i];
        while(v==bases[i] && i<grade){
            count++;
            i++;
        }
        if(count % 2 == 1)vsize++;
        count = 0;
    }
    if(vsize == grade)return;


    int * newbases = (int*)malloc(sizeof(int)*vsize);
    v = bases[0];
    count = 0;
    i=0;
    int j=0;
    while(i<grade){
        v=bases[i];
        while(v==bases[i] && i<grade){
            count++;
            i++;
        }
        if(count % 2 == 1){
            newbases[j]=v;
            j++;
        }
        count = 0;
    }
    grade = vsize;
    bases = newbases;
}
string Expression::toString() const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);
    oss << value << " ";
    int i;
    for(i=0;i<grade;i++){
        oss << "e"<<bases[i];
    }
    return oss.str();
}

bool Expression::equalBase(Expression b){
    if(this->grade != b.grade)return false;
    int i;
    for(i=0;i<grade;i++){
        if(bases[i] != b.bases[i])return false;
    }
    return true;
}
