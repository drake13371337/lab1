#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
using namespace std;

class Graph{
  private:
    int n;
    int** graph_matr;
    list<pair<int,int>>* graph_list;
    string mode;
    string filename;

  public:
    Graph(){
        cout<<"No file name"<<endl;
    }
    Graph(string filename){
        bool trigger = false;
        bool trigger1 = false;
        string buff, vert, weight;
        int vi, wi;
        pair<int,int> buff_pair;

        ifstream file(filename, ios_base::in);
        file.seekg(0, ios_base::beg);
        file>>buff;
        this->n=atoi(buff.c_str());
        file>>this->mode;
        cout<<"N="<<n<<"; ";
        cout<<"Mode="<<mode<<";"<<endl<<endl;
        buff.clear();

        if(mode=="matrix"){
            graph_matr = new int*[n];
            for(int i=0;i<n;i++) graph_matr[i] = new int[n];

            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    graph_matr[i][j]=0;
        }
        if(mode=="list"){
           graph_list = new list<pair<int,int>>[n];
        }

        for(int i=0;i<n;i++){
            file>>buff;
            for(int j=0;j<buff.size();j++){
                if(!(buff.empty())){
                    if(trigger){
                        vert=vert+buff[j];
                    }
                    if(trigger1){
                        weight=weight+buff[j];
                    }
                    if(buff[j]=='-'){
                        j=j+1;
                    }
                    if(buff[j]=='('){
                        trigger=true;
                    }
                    if(buff[j]==')'){
                        trigger1=false;
                        vi=atoi(vert.c_str());
                        wi=atoi(weight.c_str());

                        if(mode=="matrix")
                            graph_matr[i][vi-1]=wi;
                        if(mode=="list"){
                            buff_pair.first=vi;
                            buff_pair.second=wi;
                            graph_list[i].push_back(buff_pair);
                        }
                        vert.clear();
                        weight.clear();
                    }
                    if(buff[j]==','){
                        trigger=false;
                        trigger1=true;
                    }
                }
            }
            buff.clear();
        }
        file.close();

        if(mode=="matrix"){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++)
                    cout<<graph_matr[i][j]<<" ";
                cout<<endl;
            }
        }
        if(mode=="list"){
            for(int i=0;i<n;i++){
                cout<<i+1;
                for(auto iter = graph_list[i].begin(); iter!=graph_list[i].end(); iter++){
                    buff_pair = *iter;
                    cout<<"->("<<buff_pair.first<<","<<buff_pair.second<<")";
                }
                cout<<endl;

            }
        }
    }
    ~Graph(){
        delete [] graph_matr;
    }
    string alg_dijkstra(int a, int b){
        string res;
        int *pointers, *way;
        bool *inf;
        bool *active_pointers;
        int buff, way_it, curr;
        int first = a-1;
        int second = b-1;
        queue<int> q1;

        pointers = new int[n];
        way = new int[n];
        active_pointers = new bool[n];
        inf = new bool[n];

        for(int i=0;i<n;i++){
            active_pointers[i]=true;
            pointers[i]=0;
            way[i]=0;
            inf[i]=true;
        }

        q1.push(first);
        inf[first]=0;

        while(!q1.empty()){
            curr=q1.front();
            q1.pop();

            if(mode=="matrix"){
                for(int i=0;i<n;i++){
                    if(graph_matr[curr][i]!=0 && curr!=second){
                        if(inf[i]==true){
                            pointers[i]=graph_matr[curr][i]+pointers[curr];
                            inf[i]=false;
                            q1.push(i);
                        }
                        buff=graph_matr[curr][i]+pointers[curr];
                        if(inf[i]==false && buff<pointers[i]){
                             pointers[i]=buff;
                        }
                    }
                }
            }
            if(mode=="list"){
                if(curr!=second){
                    for(auto iter = graph_list[curr].begin(); iter!=graph_list[curr].end(); iter++){
                        if(inf[iter->first-1]==true){
                            pointers[iter->first-1]=iter->second+pointers[curr];
                            inf[iter->first-1]=false;
                            q1.push(iter->first-1);
                        }
                        buff=iter->second+pointers[curr];
                        if(inf[iter->first-1]==false && buff<pointers[iter->first-1]){
                            pointers[iter->first-1]=buff;
                        }
                    }
                }
            }
            active_pointers[curr]=false;
        }

        q1.push(second);
        way_it=1;
        way[0]=second+1;

        while(!q1.empty()){
            curr=q1.front();
            q1.pop();
            if(mode=="matrix"){
                for(int j=0;j<n;j++){
                    for(int i=0;i<n;i++){
                        if(graph_matr[j][curr]!=0 && curr!=first){
                            buff=pointers[curr]-graph_matr[j][curr];
                            if(pointers[j]==buff){
                                q1.push(j);
                                way[way_it]=j+1;
                                way_it++;
                                break;
                            }
                        }
                    }
                }
            }
            if(mode=="list"){
                for(int j=0;j<n;j++){
                    for(auto iter = graph_list[j].begin(); iter!=graph_list[j].end(); iter++){
                        if((iter->first-1)==curr && curr!=first){
                            buff=pointers[curr]-(iter->second);
                            if(pointers[j]==buff){
                                q1.push(j);
                                way[way_it]=j+1;
                                way_it++;
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout<<endl;
        res="Length: "+to_string(pointers[second])+" Way: ";
        for(int j=n-1;j>=0;j--){
            if(way[j]!=0)
                res=res+"->"+to_string(way[j]);
        }

        delete [] active_pointers;
        delete [] pointers;
        delete [] inf;
        delete [] way;

        return res;
    }
};


int main(){
    Graph A("test.txt");
    string res = A.alg_dijkstra(1, 3);
    cout<<res<<endl;
    return 0;
}
