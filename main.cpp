#include "arch.h"

using namespace std;

int main(int argv, char** argc)
{
    Arch A(argc[2], argc[3], argc[1], argc[4]);
    int err = A.read_f();
    if(err==-1) cout<<"Error..."<<endl;
    return 0;
}
