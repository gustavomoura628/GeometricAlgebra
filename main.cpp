//This program calculates all basic operations between multivectors

#include <iostream>
#include <string>
#include "lib/Expression.h"
#include "lib/Multivector.h"
using namespace std;

int main(){
    string s;
    getline(cin,s);
    Multivector a(s.c_str());
    getline(cin,s);
    Multivector b(s.c_str());
    getline(cin,s);
    Multivector c(s.c_str());
    //cout << a << "\n";
    //cout << b << "\n";
    //cout << a*b << "\n";
    //cout << a.conjugate() << "\n";
    cout << b*c*a*c*b << "\n";
    return 0;
}
