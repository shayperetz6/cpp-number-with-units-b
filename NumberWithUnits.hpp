#include <iostream>
#include <fstream>
#include <sstream>
namespace ariel {
    class NumberWithUnits{
        double value;
        std::string type;

        public:
        NumberWithUnits(double num,const std::string &unit);
        static void read_units(std::ifstream &file);
        // Arithmetic operators
        NumberWithUnits &operator +=(const NumberWithUnits& num1);
        friend NumberWithUnits operator +(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend  NumberWithUnits operator -(const NumberWithUnits& num1,const NumberWithUnits& num2);
        NumberWithUnits operator +()
        {
             return NumberWithUnits(value,type);
        };
        NumberWithUnits operator -(){
          return NumberWithUnits(-value,type);  
        };
        NumberWithUnits &operator -=(const NumberWithUnits& num1);
        friend NumberWithUnits operator*(const NumberWithUnits& num1,double num2);
        friend NumberWithUnits operator*(double num1,const NumberWithUnits& num2);


        // incerase && decrease operators
        NumberWithUnits& operator ++(){
            value++;
            return *this;
        };
        const NumberWithUnits operator ++(int){
            NumberWithUnits copy=*this;
            value++;
            return copy;
        };
        NumberWithUnits& operator --(){
            value--;
            return *this;
        };
        const NumberWithUnits operator --(int){
            NumberWithUnits copy=*this;
            value--;
            return copy;
        };

        // compares operators

        bool operator ==(const NumberWithUnits& num1)const;
        friend bool operator !=(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend bool operator <=(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend bool operator >=(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend bool operator <(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend bool operator >(const NumberWithUnits& num1,const NumberWithUnits& num2);

        //output && input operators
    
        friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& num);
        friend std::istream& operator>> (std::istream& input, NumberWithUnits& num);
    

    };
}