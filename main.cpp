#include <iostream>
#include <vector>
#include <string>

// do not use using namespace std; as it is bad practice
// notice that nothing is global scope.
class Foo {
public: // put public first
    Foo(int a, std::string s) : a_(a), s_(s) { } // member initialization, very elegant
    int get_a(){return a_;} // acceser functions to support encapsulation
    std::string get_s(){return s_;}
private:
    int a_;
    std::string s_;
};

// vector is taken as an address
// int and string are taken using forward addresses, or universal addresses
void make(std::vector<Foo>& c, int&& a, std::string&& s){
    Foo e{a,s};    // member initialization is called
                    // you can trust vectors to clean up after themselves.
    c.push_back(e);
}

int main()
{
    // it is better to use std::vector over std::list
    std::vector<Foo> v; // this is an lvalue, which means it has a variable name
    make(v,5,"orion"); // 5 and "orion" are rvalues, since they lack a variable name.
    make(v,10,"alt"); // I used forward addresses to allow them in. I.e, std::string&& s
    make(v,5,"neko");
    for(unsigned i = 0; i<v.size(); i++){   //v.size() gives an unsigned int. This means that the int cannot be a negative number.
                                            // thus i must be unsigned, else the compiler gives a warning.
        std::cout << v.at(i).get_s() << " ";
    }
    std::cout << std::endl; // prints: orion alt neko
    v.erase(v.begin()); // vector's erase function takes an iterator
    // this is called a range for loop. you should use this by default, unless you need something more
    for(auto e: v){
        std::cout << e.get_s() << " ";
    }
    std::cout << std::endl; // prints: alt neko
    v.pop_back();
    for(auto e: v){ std::cout << e.get_s() << " "; } std::cout << std::endl; // prints: alt
    return 0;
}
/* This program was compiled with GNU GCC Compiler. */
/* The flags were: -Wextra -Wall -std=c++11 -Weffc++ -fexceptions */
