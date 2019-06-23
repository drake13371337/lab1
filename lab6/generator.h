#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <list>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

vector<string> name_pull = {"Joe", "Aaliyah", "Olive", "Tanisha", "Eiliyah", "Shazia", "Jamelia", "Alena", "Kyran", "Yannis"};
vector<string> surname_pull = {"Joyner", "Stone", "Robles", "Harris", "Dalton", "Beck", "Ingram", "Dillon", "Fuentes", "Hampton"};
vector<string> list_pull = {"Phone", "Purse", "Pen", "Book", "Bottle", "Card", "Amulet", "Ring", "Belt", "Tablet"};
string abc = "qwertyuiopasdfghjklzxcvbnm";
string abc_ = "QWERTYUIOPASDFGHJKLZXCVBNM";

struct employee{
    int salary;
    string name, surname;
    list<string> some_list;
};

ostream & operator<<(ostream & out, const employee& n){
    out<<n.name<<" "<<n.surname<<endl;
    out<<"Salary: "<<n.salary;
    out<<"[ ";
    for(auto iter : n.some_list)
        cout<<iter<<" ";
    out<<"]"<<endl;
    return out;
}

bool operator< (employee const & n, employee const & n1){
    return n.salary < n1.salary;
}

vector<int> int_generator(int count){
    vector<int> res;
    srand(time(NULL));
    for(int i=0; i<count; i++){
        res.push_back(rand()%10000);
    }
    return res;
}
vector<employee> struct_generator(int count){
    vector<employee> res;
    employee buff;
    int buff1;
    srand(time(NULL));
    for(int i=0; i<count; i++){
        buff.salary=10000+rand()%10000;
        buff.name=name_pull[rand()%10];
        buff.surname=surname_pull[rand()%10];
        buff1=1+rand()%5;
        buff.some_list.clear();
        for(int j=0; j<buff1;j++){
            buff.some_list.push_back(list_pull[rand()%10]);
        }
        res.push_back(buff);
    }
    return res;
}
vector<string> string_generator(int count){
    vector<string> res;
    string buff;
    int size;
    srand(time(NULL));
    for(int i=0; i<count; i++){
        size=rand()%15;
        buff.clear();
        buff.append(1, abc_[rand()%26]);
        for(int j=0; j<size; j++){
            buff.append(1, abc[rand()%26]);
        }
        res.push_back(buff);
    }
    return res;
}

#endif // GENERATOR_H
