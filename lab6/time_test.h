#ifndef TIME_TEST_H
#define TIME_TEST_H

#include <generator.h>
#include <sorter.h>
#include <time.h>

void time_test(int count, int shell_type){
    clock_t ch, ch1;
    vector<int> a;
    a=int_generator(count);

    cout<<"std::sort -- int("<<count<<") -- ";
    ch=clock();
    sort_f(a);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    cout<<"bubble sort -- int("<<count<<") -- ";
    ch=clock();
    bubble(a);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    switch(shell_type){
        case 0:{
            cout<<"Shell -- int("<<count<<") -- ";
            break;
        }
        case 1:{
            cout<<"Shell(Hibbard) -- int("<<count<<") -- ";
            break;
        }
        case 2:{
            cout<<"Shell(Sedgewick) -- int("<<count<<") -- ";
            break;
        }
    }
    ch=clock();
    shell(a, shell_type);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;
    cout<<endl;
    //////////////////////////////////////////////////////////////////
    vector<string> b;
    b=string_generator(count);

    cout<<"std::sort -- string("<<count<<") -- ";
    ch=clock();
    sort_f(b);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    cout<<"bubble sort -- string("<<count<<") -- ";
    ch=clock();
    bubble(b);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    switch(shell_type){
        case 0:{
            cout<<"Shell -- string("<<count<<") -- ";
            break;
        }
        case 1:{
            cout<<"Shell(Hibbard) -- string("<<count<<") -- ";
            break;
        }
        case 2:{
            cout<<"Shell(Sedgewick) -- string("<<count<<") -- ";
            break;
        }
    }
    ch=clock();
    shell(b, shell_type);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;
    cout<<endl;
    //////////////////////////////////////////////////////////
    vector<employee> c;
    c=struct_generator(count);

    cout<<"std::sort -- struct("<<count<<") -- ";
    ch=clock();
    sort_f(c);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    cout<<"bubble sort -- struct("<<count<<") -- ";
    ch=clock();
    bubble(c);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;

    switch(shell_type){
        case 0:{
            cout<<"Shell -- struct("<<count<<") -- ";
            break;
        }
        case 1:{
            cout<<"Shell(Hibbard) -- struct("<<count<<") -- ";
            break;
        }
        case 2:{
            cout<<"Shell(Sedgewick) -- struct("<<count<<") -- ";
            break;
        }
    }
    ch=clock();
    shell(c, shell_type);
    ch1=clock();
    cout<<"Time: "<<(ch1-ch)/(double)CLOCKS_PER_SEC<<"sec"<<endl;
}


#endif // TIME_TEST_H
