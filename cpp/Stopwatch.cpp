#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;

void startWatch(){
    auto starttime = steady_clock::now();
    cout<<"stopwatch started";

    cin.get();
    auto endtime = steady_clock::now();
    duration<double> elapsed = endtime - starttime;
    cout<<elapsed.count();
}

void countdownTimer(int seconds){
    for(int i = seconds; i > 0; i--){
        cout<<"\r Time remaining:"<<i<<" seconds "<<flush;
       
    }
    cout << "\r Time is up";
}
