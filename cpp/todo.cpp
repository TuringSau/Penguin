#include<iostream>
#include<vector>

using namespace std;

void displayMenu();
void viewTasks(const vector<string>& tasks);


int main(){
    vector<string> tasks;
    int choice;

    do{
        displayMenu();
        cout<<"Enter your choice";
        cin>> choice;
        cin.ignore();

        switch(choice){
            case 1:
                addTask(tasks);

            case 2:
                viewTasks(tasks);
                break;
        }
    }while(true);
}

void displayMenu(){
    cout<<"To do list";
    cout<<"1. Add Task";
    cout<<"2. viewTasks";
}

void addTask(vector<string>& tasks){
    string task;
    cout<<"Enter the task:";
    getline(cin,task);
    tasks.push_back(task);
    cout<<"task added successfully";
}

void viewTasks(const vector<string>& tasks){
    if(tasks.empty()){
        cout<<"Task list is empty";
        return;
    }
    for(int i = 0; i<tasks.size();i++){
        cout<<i+1<<"."<<tasks[i]<<endl;
    }
}