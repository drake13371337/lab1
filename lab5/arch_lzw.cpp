#include "arch_lzw.h"
#define BTS 12
arch_lzw::arch_lzw(){

}

arch_lzw::arch_lzw(string in_f, string out_f, string m){
    out_filename=out_f;
    in_filename=in_f;
    mode=m;
}

int arch_lzw::read_f(){
    unsigned char buff;
    string s_buff;
    int index_i = 0;

    cout<<"Opening file..."<<endl;
    ifstream file(in_filename, ios_base::in);
    if(!file.is_open()) return -1;
    if(file.get()==EOF) return -1;
    cout<<"Reading..."<<endl;
    file.close();

    if(mode=="compress"){
        for(int i=0;i<256;i++){
            buff=(unsigned char)index_i;
            s_buff.append(1, buff);
            table.add(s_buff);
            index_i++;
            s_buff.clear();
        }
        cout<<"Compressing..."<<endl;
        compress();
        cout<<"Done..."<<endl;
        return 0;
    }
    if(mode=="decompress"){
        for(int i=0;i<256;i++){
            buff=(unsigned char)index_i;
            s_buff.append(1, buff);
            table.add(s_buff);
            index_i++;
            s_buff.clear();
        }
        cout<<"Decompressing..."<<endl;
        decompress();
        cout<<"Done..."<<endl;
        return 0;
    }

    return -1;
}

int arch_lzw::compress(){
    ofstream file1(out_filename, ios_base::out | ios_base::binary);
    ifstream file(in_filename, ios_base::in | ios_base::binary);

    string x, buff1, buff;
    char y, x_c;
    vector<int> res;

    x_c=file.get();
    x.append(1, x_c);
    while(!file.eof()){
        y=file.get();
        buff1.clear();
        buff1.append(x);
        buff1.append(1, y);
        if(table.search(buff1)==1){
            x=buff1;
        } else {
            res.push_back(table.rdwr_str(x));
            table.add(buff1);
            x.clear();
            x.append(1, y);
        }
    }
    for(auto iter : res){
        bitset<BTS> bt(iter);
        buff.append(bt.to_string());
        while(buff.length()>=8){
            file1<<bt_char(buff.substr(0, 8));
            buff.erase(0, 8);
        }
    }
    if(buff.length()>0){
        int l = buff.length();
        for(int i=0;i<8-l;i++) buff.append(1, '0');
        file1<<bt_char(buff.substr(0, 8));
        buff.erase(0, 8);
    }

    //for(auto iter : res){
    //    cout<<iter<<" ";
    //}
    //cout<<endl;

    //cout<<table<<endl;
    file.close();
    file1.close();
    return 0;
}

int arch_lzw::decompress(){
    ofstream file1(out_filename, ios_base::out | ios_base::binary);
    ifstream file(in_filename, ios_base::in | ios_base::binary);

    char buff;
    string buff1;
    vector<int> line;
    int res, x, y;

    while(!file.eof()){
        buff=file.get();
        if(file.eof()) break;
        buff1.append(char_bt(buff));
        while(buff1.length() >= BTS){
            bitset<BTS> bt(buff1.substr(0, BTS));
            res=bt.to_ulong();
            buff1.erase(0, BTS);
            line.push_back(res);
        }
    }

    //for(auto iter : line){
    //  cout<<iter<<" ";
    //}
    //cout<<endl;
    //cout<<table<<endl;

    x=line[0];
    file1<<table.str_rdwr(x).c_str();
    buff1=table.str_rdwr(x);
    buff=buff1[0];
    for(unsigned int i=1; i<line.size();i++){
        y=line[i];
        if(table.search(table.str_rdwr(y))==1){
            buff1.clear();
            buff1.append(table.str_rdwr(y));
        } else {
            buff1.clear();
            buff1.append(table.str_rdwr(x));
            buff1.append(1, buff);
        }
        file1<<buff1.c_str();
        buff=buff1[0];
        buff1.clear();
        buff1.append(table.str_rdwr(x));
        buff1.append(1, buff);
        table.add(buff1);
        x=y;
    }
    //cout<<table<<endl;
    file.close();
    file1.close();
    return 0;
}

string arch_lzw::char_bt(const char input){
    string res;
    for(int i=0; i<8;i++){
        res.append(to_string(input>>i&1));
    }
    return res;
}

char arch_lzw::bt_char(string input){
    char res = 'a';
    for(int i=7; i>=0;i--){
        if(input[i]=='0'){
            res&=~(1<<i);
        }
        if(input[i]=='1'){
            res|=1<<i;
        }
    }
    return res;
}
