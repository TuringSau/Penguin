#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

void displayMaze(const vector<vector<char>>& maze){
    for(const auto& row: maze){
        for(char cell: row){
            cout<< cell;
        }
        cout<<endl;
    }
}
vector<vector<char>>  loadMaze(const string& filename){
    ifstream file(filename);
    vector<vector<char>> maze;

    if(!file){
        cerr<<"Error: could not open file";
    }
    string line;
    while(getline(file,line)){
        maze.push_back(vector<char>(line.begin(),line.end()));
    }

    file.close();
    return maze;
}
pair<int,int> findPosition(const vector<vector<char>>& maze, char target){
    for(int i = 0; i < maze.size();i++){
        for( int j = 0;j < maze[i].size();j++){
            if(maze[i][j] == target){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

bool solveMazeDFS(vector<vector<char>>& maze, int x, int y){
    if(maze[x][y] == 'E'){
        return true;
    }
    if(maze[x][y] == '#' || maze[x][y] == '*') return false;

    if(maze[x][y] != 'S') maze[x][y] = '*';

    if(solveMazeDFS(maze,x-1,y)||
        solveMazeDFS(maze,x+1,y),
        solveMazeDFS(maze,x,y-1),
        solveMazeDFS(maze,x,y+1)
    )
    {
        return true;
    }

    if(maze[x][y] != 'S' ) maze[x][y] = ' ';
    return false;
}
