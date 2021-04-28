#include "NumberWithUnits.hpp"
#include <map>
#include <stdexcept>
#include <string>
using namespace std;
const double EPS = 0.001;
namespace ariel{

    static map<string, map<string, double>> unitMap;
    // function to convert types
    double convert(double value, const string& type1, const string& type2){
        if(type1 == type2) {
            return value;
        }
        try{
            return value * unitMap.at(type1).at(type2);
        }
        catch(const exception& exp){
            throw invalid_argument{" "+type1+" can't convert to "+type2+""};
        }
    }
    //constructor 
    NumberWithUnits:: NumberWithUnits (double num,const string &unit){
        if (unitMap.count(unit) == 0) //check if the type is part of the units type
        {
            throw invalid_argument("No unit called "+unit);
        }
        value=num;
        type=unit;
    }
    void NumberWithUnits:: read_units(ifstream &file){
        double num1=0; 
        double num2=0;
        string unit1, unit2, equal;
        while(file >> num1 >> unit1 >> equal >> num2 >> unit2){

            unitMap[unit1][unit2] = num2;
            unitMap[unit2][unit1]= 1/num2;
            for(auto &map : unitMap[unit1]) {
                double val = unitMap[unit2][unit1] * map.second;
                unitMap[unit2][map.first] = val;
                unitMap[map.first][unit2] = 1/val;
            }
            for(auto &pair : unitMap[unit2]) {
                double val = unitMap[unit1][unit2] * pair.second;
                unitMap[unit1][pair.first] = val;
                unitMap[pair.first][unit1] = 1/val;
            }
        }
    }
        
    // Arithmetic operators
    NumberWithUnits &NumberWithUnits:: operator +=(const NumberWithUnits& num1)
    {
        this->value+= convert(num1.value,num1.type,this->type);
        return *this;

    }
    NumberWithUnits &NumberWithUnits:: operator -=(const NumberWithUnits& num1)
    {
        this->value-= convert(num1.value,num1.type,this->type);
        return *this;

    }
    NumberWithUnits operator +(const NumberWithUnits& num1,const NumberWithUnits& num2)
    {
        double temp=num1.value+ convert(num2.value,num2.type,num1.type);
        NumberWithUnits x(temp,num1.type);
        return x;
    }
    NumberWithUnits operator -(const NumberWithUnits& num1,const NumberWithUnits& num2)
    {
        double temp=num1.value- convert(num2.value,num2.type,num1.type);
        NumberWithUnits x(temp,num1.type);
        return x;
    }
    /*
    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(value,type);
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-value,type);
    }
    */   
    NumberWithUnits operator*(const NumberWithUnits& num1,double num2){
        double temp=num2*num1.value;
        return NumberWithUnits(temp,num1.type);
    }
    NumberWithUnits operator*(double num1,const NumberWithUnits& num2){
        double temp=num1*num2.value;
        return NumberWithUnits(temp,num2.type);
    }
        
    // compares operator

    bool NumberWithUnits:: operator==(const NumberWithUnits& num1)const{
        return (abs(this->value- convert(num1.value, num1.type, this->type)) <= EPS);
    }
    bool operator !=(const NumberWithUnits& num1,const NumberWithUnits& num2){
        return !(num1==num2);
    }
    bool operator <=(const NumberWithUnits& num1,const NumberWithUnits& num2){
        return( (num1==num2)||(num1<num2));
    }
    bool operator >=(const NumberWithUnits& num1,const NumberWithUnits& num2){
        return( (num1==num2)||(num1>num2));
    }
    bool operator <(const NumberWithUnits& num1,const NumberWithUnits& num2){
        return (num1.value < convert(num2.value, num2.type, num1.type));
    }
    bool operator >(const NumberWithUnits& num1,const NumberWithUnits& num2){
        return (num1.value > convert(num2.value, num2.type, num1.type));
    }

    //output && input operators
    
    ostream& operator<< (ostream& os, const NumberWithUnits& num){
        os<<num.value<<"[" <<num.type << "]";
        return os;
    }
    istream& operator>> (istream& input, NumberWithUnits& num){
        double value=0;
        char ch1=' ';
        string unit;
        char ch2=' ';
        input>>value>>ch1>>unit;
        if(unit.at(unit.length()-1)== ']')
        {
            unit=unit.substr(0,unit.length()-1);
        } 
        else
        {
            input>>ch2;
        }
        if(unitMap.count(unit)==0){
            throw invalid_argument{unit+"doesnt exist"};
        }
        num.value=value;
        num.type=unit;
        return input;

    }
    
    
}