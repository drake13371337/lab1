#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class hash_table{
private:

    vector<pair<int,list<pair<string, int>>>> table;
    vector<pair<string, int>> ind;

    int hash_func_type;
    int index = 0;
    pair<string, int> search_buffer;

    int r_hash(string line){
        int res_hash = 0;
        for(unsigned int i=0; i<line.length(); i++){
            res_hash = res_hash+(unsigned char)line[i]*7*(1+i);
        }
        return res_hash;
    }
public:
    hash_table(){ hash_func_type=2; }
    hash_table(int hash_type){
        hash_func_type=hash_type;
    }

    int add(string line){
        int hesh_buff = mult_hash(line);
        int search_state = search(line);

        if(search_state==2){
            table[hesh_buff].second.push_back(pair<string, int>(line, index));
            ind.push_back(table[hesh_buff].second.back());
            index++;
            return 1;
        }
        if(search_state==0){
            table.resize(hesh_buff+1);
            pair<string, int> buff1(line, index);
            list<pair<string, int>> buff3{buff1};
            pair<int,list<pair<string, int>>> buff(1, buff3);

            table[hesh_buff]=buff;
            ind.push_back(table[hesh_buff].second.front());
            index++;
            return 1;
        }
        if(search_state==-1){
            pair<string, int> buff1(line, index);
            list<pair<string, int>> buff3{buff1};
            pair<int,list<pair<string, int>>> buff(1, buff3);
            table[hesh_buff]=buff;

            ind.push_back(table[hesh_buff].second.front());
            index++;
        }
        return 0;
    }

    int del(string s){
        int key=mult_hash(s);
        if(search(s)==1){
            pair<string, int> buff1;
            list<pair<string, int>> buff3{buff1};
            pair<int,list<pair<string, int>>> buff(0, buff3);
            table[key]=buff;
        }
        return 0;
    }

    int search(string s){

            int key=mult_hash(s);
            if(table.empty()) return 0;
            if(table.size()<key+1) return 0;
            if((table[key].first)!=0){
                for(auto iter : table[key].second){
                    if((iter.first)==s){
                        search_buffer.first=iter.first;
                        search_buffer.second=iter.second;
                        return 1;
                    }
                }
                return 2;
            } else return -1;
            return 0;

    }

    pair<string,int> obj_search(string s){
        search(s);
        return search_buffer;
    }

    int rdwr_str(string s){
        search(s);
        return search_buffer.second;
    }

    string str_rdwr(int k){
        return ind[k].first;
    }

    int mult_hash(string line){
        switch(hash_func_type){
        case 0:
            return line.length();
            break;
        case 1:
            return hash<string>()(line);
            break;
        case 2:
            return r_hash(line);
            break;
        }
        return 0;
    }

    friend ostream & operator<<(ostream & out, const hash_table& n){
        for(int i=0;i<n.ind.size();i++){
            out<<" STR: "<<n.ind[i].first<<" P_STR: "<<i<<endl;
            /*if(n.table[i].first==1){
                out<<"HASH: "<<i<<" PULL: ";
                for(auto iter1 : n.table[i].second){
                    out<<"[ "<<iter1.first<<" - "<<iter1.second<<" ] ";
                }
                out<<endl;
            }*/
        }
        return out;
    }
};

#endif // HASH_TABLE_H
