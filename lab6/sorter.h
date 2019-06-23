#ifndef SORTER_H
#define SORTER_H

#include <generator.h>
#include <algorithm>
#include <math.h>

using namespace std;

template <typename T>
void sort_f(vector<T> & obj){
    sort(obj.begin(), obj.end());
}

template <typename T1>
void shell(vector<T1> & obj, int mode){
    int size = obj.size();
    switch(mode){
        case 0:{
            int d = size/2;
            while(d>0){
                for(int i=0; i<size-d; i++){
                    int j=i;
                    while(j>=0 && obj[j+d]<obj[j]){
                        swap(obj[j+d], obj[j]);
                        j--;
                    }
                }
                d=d/2;
            }
            break;
        }
        case 1:{
            for(int i=1; i<size; i++){
                int d = pow(2, i) - 1;
                if(d<=size){
                    for(int k=0; k<size-d; k++){
                        int j=k;
                        while (j>=0 && obj[j+d]<obj[j]){
                            swap(obj[j+d], obj[j]);
                            j--;
                        }
                    }
                }
            }
            break;
        }
        case 2:{
            for(int i=0; i<size; i++){
                int d;
                if((i%2)!=1) d=9*pow(2, i)-9*pow(2, i/2) + 1;
                else d=8*pow(2, i)-6*pow(2, (i+1)/2) + 1;
                if(d<=size){
                    for(int k=0; k<size-d; k++){
                        int j=k;
                        while (j>=0 && obj[j+d]<obj[j]){
                            swap(obj[j+d], obj[j]);
                            j--;
                        }
                    }
                }
            }
            break;
        }
    }
}
template <typename T2>
void bubble(vector<T2> & obj){
    int size = obj.size();
    for(int i=1; i<size; ++i)
        for(int j=0; j<size-i; j++)
            if(obj[j+1]<obj[j]){
                swap(obj[j+1], obj[j]);
            }
}

#endif // SORTER_H
