#include "arch.h"

Arch::Arch()
{

}

Arch::Arch(string in_f, string out_f, string m, string pref){
    out_filename=out_f;
    in_filename=in_f;
    mode=m;
    prefix=pref;
    orig_data_size=0;
    stat_size=0;
}

int Arch::read_f(){
    string buff_res, buff1;
    char buff;
    pair<int,char> buff2;

    if(mode=="compress"){
        cout<<"Opening file..."<<endl;
        ifstream file1(in_filename, ios_base::in);
        if(!file1.is_open()) return -1;
        cout<<"Reading..."<<endl;

        while(!file1.eof()){
            file1.get();
            orig_data_size++;
        }
        file1.close();

        orig_data_size--;

        ifstream file(in_filename, ios_base::in);

        while(!file.eof()){
            buff=file.get();
            if(statistic.find(buff)==statistic.end()){
                statistic.insert(pair<char,int>(buff, 1));
            }else{
                statistic[buff]++;
            }
        }
        if(statistic.size()==1){
            file.close();
            return -1;
        }
        for(auto iter = statistic.begin(); iter!=statistic.end(); iter++)
            statistic_list.push_back(pair<int,char>(iter->second, iter->first));

        stat_size=statistic_list.size();
        statistic_list.sort();

        file.close();
        cout<<"Compressing..."<<endl;
        compress();
        //cout<<"-----"<<endl;
        //for(auto iter = statistic_list.begin(); iter!=statistic_list.end(); iter++)
        //   cout<<" Num: "<<iter->first<<" Char: "<<iter->second<<endl;

        //  cout<<" orig_data_size:"<<orig_data_size<<endl;
        cout<<"Done..."<<endl;
        return 0;
    }
    if(mode=="decompress"){
        cout<<"Opening file..."<<endl;
        ifstream file1(in_filename, ios_base::in);
        if(!file1.is_open()) return -1;
        cout<<"Reading..."<<endl;
            file1>>buff1;
            if(buff1!=prefix){
                cout<<"Incorrect prefix..."<<endl;
            }else{
                file1>>buff1;
                orig_data_size=atoi(buff1.c_str());
                file1>>buff1;
                stat_size=atoi(buff1.c_str());
                file1.get();
                for(int i=0;i<stat_size;i++){
                    buff=file1.get();
                    buff2.second=buff;
                    file1.get();
                    while(true){
                        buff=file1.get();
                        buff1.clear();
                        buff1.append(1, buff);
                        if(buff1==" ") break;
                        buff_res=buff_res+buff1;
                    }
                    buff2.first=atoi(buff_res.c_str());
                    buff_res.clear();
                    statistic_list.push_back(buff2);
                }
            }
        file1.close();
        cout<<"Decompressing..."<<endl;
        decompress();
        cout<<"Done..."<<endl;
        return 0;
    }

    //cout<<"stat_size:"<<stat_size;
    //cout<<" orig_data_size:"<<orig_data_size<<endl;
    //for(auto iter = statistic.begin(); iter!=statistic.end(); iter++)
    //    cout<<"Char: "<<iter->first<<" Num: "<<iter->second<<endl;
    //cout<<"-----"<<endl;
    //for(auto iter = statistic_list.begin(); iter!=statistic_list.end(); iter++)
    //    cout<<" Num: "<<iter->first<<" Char: "<<iter->second<<endl;

    return -1;
}

bool tr_sort(const pair<int,string> &a, const pair<int,string> &b){
    return (a.first<b.first);
}

int Arch::code_form(){
    list<pair<int,string>> code_list;
    pair<int,string> buff2;
    string buff, buff1;
    for(auto iter = statistic_list.begin(); iter!=statistic_list.end(); iter++){
        code_vec.push_back(pair<string,char>("",iter->second));
        buff.append(1, iter->second);
        code_list.push_back(pair<int, string>(iter->first, buff));
        buff.clear();
    }

    if(code_list.size()==1){
        code_vec.begin()->first="0";
    }

    for(int i=0;i<stat_size;i++){
        if(code_list.size()>1){
            auto iter = code_list.begin();
            auto iter1 = code_list.begin();
            iter1++;
            for(int j=0; j<code_vec.size();j++){
                for(int k=0;k<iter->second.size();k++){
                    buff=code_vec[j].second;
                    buff1=iter->second.at(k);
                    if(buff==buff1){
                        code_vec[j].first.push_back('0');
                    }
                }
                for(int k=0;k<iter1->second.size();k++){
                    buff=code_vec[j].second;
                    buff1=iter1->second.at(k);
                    if(buff==buff1){
                        code_vec[j].first.push_back('1');
                    }
                }
            }
            iter1->second=iter1->second+iter->second;
            iter1->first=iter1->first+iter->first;
            buff2.first = iter1->first;
            buff2.second = iter1->second;
            code_list.pop_front(); code_list.pop_front();
            code_list.push_front(buff2);
        }
        code_list.sort(tr_sort);
        //for(auto iter = code_vec.begin(); iter!=code_vec.end(); iter++)
        //   cout<<"Char: "<<iter->second<<" | Code: "<<iter->first<<endl;
        //cout<<"-----"<<endl;
    }
    for(int j=0; j<code_vec.size();j++){
        reverse(code_vec[j].first.begin(), code_vec[j].first.end());
    }
    //for(auto iter = code_vec.begin(); iter!=code_vec.end(); iter++)
    //   cout<<"Char: "<<iter->second<<" | Code: "<<iter->first<<endl;
    //cout<<"-----"<<endl;
}

int Arch::compress(){
    char buff, res;
    string buff1, cur_queue;
    int buff_i = 0;

    code_form();

    ofstream file(out_filename, ios_base::out | ios_base::binary);
    ifstream file1(in_filename, ios_base::in);

    file<<prefix;
    file<<" ";
    file<<orig_data_size;
    file<<" ";
    file<<stat_size;
    file<<" ";

    for(auto iter = statistic_list.begin(); iter!=statistic_list.end(); iter++){
        file<<iter->second;
        file<<":";
        file<<iter->first;
        file<<" ";
    }

    while(!file1.eof()){
        buff=file1.get();
        for(int j=0; j<code_vec.size();j++)
            if(buff==code_vec[j].second)
                cur_queue.append(code_vec[j].first);
        while(cur_queue.length()>8){
            res=bt_char(cur_queue.substr(0, 8));
            file<<res;
            //cout<<"C: "<<bt_char(cur_queue.substr(0, 8))<<" CD: "<<cur_queue.substr(0, 8)<<endl;
            cur_queue.erase(0, 8);
        }
    }
    if(!cur_queue.empty()){
        buff_i=cur_queue.length()-1;
        for(int i=buff_i; i<8; i++)
            cur_queue.append(1, '0');
        file<<bt_char(cur_queue.substr(0, 8));
        //cout<<"C: "<<bt_char(cur_queue.substr(0, 8))<<" CD: "<<cur_queue.substr(0, 8)<<endl;
        cur_queue.erase(0, 8);
    }

    file1.close();
    file.close();
    return 0;
}

int Arch::decompress(){
    string buff1, cur_queue;
    char buff;
    int buff_i = 0, count_ch = 0;

    code_form();

    ofstream file1(out_filename, ios_base::out);
    ifstream file(in_filename, ios_base::in | ios_base::binary);

    for(int i=0;i<stat_size+3;i++) file>>buff1;
    buff1.clear();
    buff=file.get();

    while(true){
        buff=file.get();
        //cout<<"C: "<<buff<<" CD: "<<char_bt(buff)<<endl;
        buff1.append(char_bt(buff));
        buff_i=buff1.length();
        for(int i=0;i<buff_i;i++){
            cur_queue.append(1 ,buff1[0]);
            buff1.erase(0, 1);
            for(int j=0; j<code_vec.size();j++)
                if(cur_queue==code_vec[j].first && orig_data_size>count_ch){
                    file1<<code_vec[j].second;
                    count_ch++;
                    cur_queue.clear();
                }
        }
        if(count_ch==orig_data_size) break;
    }

    file.close();
    file1.close();
}

string Arch::char_bt(const char input){
    string res;
    for(int i=0; i<8;i++){
        res.append(to_string(input>>i&1));
    }
    return res;
}

char Arch::bt_char(string input){
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
