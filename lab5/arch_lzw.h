#ifndef ARCH_LZW_H
#define ARCH_LZW_H

#include <hash_table.h>
#include <fstream>
#include <bitset>

using namespace std;

class arch_lzw{
private:
    hash_table table;

    string in_filename;
    string out_filename;
    string mode;
public:
    arch_lzw();
    arch_lzw(string in_f, string out_f, string m);

    int read_f();

    int compress();
    int decompress();

    string char_bt(const char input);
    char bt_char(string input);
};

#endif // ARCH_LZW_H
