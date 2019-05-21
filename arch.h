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

    map<unsigned char,int> statistic;

    list<pair<int,unsigned char>> statistic_list;
    vector<pair<string,unsigned char>> code_vec;
public:
    Arch();
    Arch(string in_f, string out_f, string m, string pref);

    int read_f();
    void start();

    int compress();
    int decompress();
    int code_form();

    string char_bt(const unsigned char input);
    unsigned char bt_char(string input);
};

#endif // ARCH_H
