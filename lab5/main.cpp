#include <iostream>
#include <hash_table.h>
#include <arch_lzw.h>
#include <arch.h>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

double f_size(string in, string out){
    ifstream file(in, ios_base::in | ios_base::binary);
    ifstream file1(out, ios_base::in | ios_base::binary);
    double i_in=0, i_out=0;

    while(!file.eof()){
        file.get();
        i_in++;
    }
    while(!file1.eof()){
        file1.get();
        i_out++;
    }
    file.close();
    file1.close();
    return i_out/i_in;
}

int main(int argv, char** argc)
{
    for(int i=1;i<argv;i++) cout<<argc[i]<<" ";
    cout<<endl;
    if(argv==5){
        if(strcmp(argc[4], "lzw")==0){
            arch_lzw A(argc[2], argc[3], argc[1]);
            A.read_f();
            cout<<"--lzw"<<endl;
            if(strcmp(argc[1], "compress")==0) cout<<f_size(argc[2], argc[3])<<endl;
            return 0;
        }
    }
    if(argv==6){
        if(strcmp(argc[5], "huffman")==0){
            Arch B(argc[2], argc[3], argc[1], argc[4]);
            B.read_f();
            cout<<"--huffman"<<endl;
            if(strcmp(argc[1], "compress")==0) cout<<f_size(argc[2], argc[3])<<endl;
            return 0;
        }
    }
    if(argv==7){
        if(strcmp(argc[5], "huffman")==0){
            Arch B(argc[2], "prom", argc[1], argc[4]);
            B.read_f();
            cout<<"--huffman"<<endl;
            if(strcmp(argc[6], "lzw")==0){
                arch_lzw A("prom", argc[3], argc[1]);
                A.read_f();
                cout<<"--lzw"<<endl;
                if(strcmp(argc[1], "compress")==0) cout<<f_size(argc[2], argc[3])<<endl;
                return 0;
            }
        }
        if(strcmp(argc[5], "lzw")==0){
            arch_lzw A(argc[2], "prom", argc[1]);
            A.read_f();
            cout<<"--lzw"<<endl;
            if(strcmp(argc[6], "huffman")==0){
                Arch B("prom", argc[3], argc[1], argc[4]);
                B.read_f();
                cout<<"--huffman"<<endl;
                if(strcmp(argc[1], "compress")==0) cout<<f_size(argc[2], argc[3])<<endl;
                return 0;
            }
        }
    }
    return 0;
}
