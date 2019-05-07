#ifndef ARCH_H
#define ARCH_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Arch{
private:
    string in_filename;
    string out_filename;
    string mode;
    string prefix;

    int orig_data_size;
    int stat_size;

    map<string,int> statistic;

    list<pair<int,string>> statistic_list;
    vector<pair<string,string>> code_vec;
public:
    Arch();
    Arch(string in_f, string out_f, string m, string pref);

    int read_f();
    void start();

    int compress();
    int decompress();
    int code_form();
};

#endif // ARCH_H
