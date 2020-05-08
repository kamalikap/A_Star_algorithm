#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>


using namespace std;

enum class State {kEmpty, kObstacle, kClosed, kPath};


const int delta[4][2]{{-1,0}, {0, -1}, {1, 0}, {0,1}};

//3,Function
vector<State> ParseLine(string a){
	istringstream my_stream(a);

	int n;
	char c;
	vector<State> r;
	while(my_stream >> n >> c){
		if (n==0){
			r.push_back(State::kEmpty);	
		}else{
			r.push_back(State::kObstacle);
		}
	}
	return r;
}

//2. Function

vector<vector<State>> ReadBoardFile(string path) {
	ifstream my_file(path);
	string line;
	
	vector<vector<State>> board;
	if (my_file){
		while (getline(my_file, line)){
			vector<State> row = ParseLine(line);
			board.push_back(row);
		}
		return board;
	}
}

//7. Function
bool Compare(const vector<int> node1, const vector<int> node2){
	int f1 = node1[2] + node1[3];
	int f2 = node2[2] + node2[3];

	if (f1 > f2){
		return true;
	} else{
		return false;
	}
}



//8. Function
void CellSort(vector<vector<int>> *v){
	sort(v->begin(), v->end(), Compare);
}

//5. Function
int Heuristic(int x1, int y1, int x2, int y2 ){
	//Manhattan Distance
	int dist;
	dist = abs(x2-x1) + abs(y2-y1);
	return dist;
}


//9. Function: Adds neighboring nodes to the open vector
bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
	
	bool on_grid_x = (x>=0 && x< grid.size());
	bool on_grid_y = (y>=0 && y< grid[0].size());
	
	if (on_grid_x  && on_grid_y)
		return grid[x][y]== State::kEmpty;
	return false;
}




//6. Function
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid){
	vector<int> node {x,y,g,h};
	open.push_back(node);
	grid[x][y] = State::kClosed;
}

//10. Function
void ExpandNeighbors(const vector<int> current, int goal[2], vector<vector<int>> &open, vector<vector<State>> &grid){
	int x = current[0];
	int y = current[1];
	int g = current[2];

	for(int i=0; i< 4; i++){
		int x2 = x + delta[i][0];
		int y2 = y + delta[i][1];
		if (CheckValidCell(x2, y2, grid)){
			int g2 = g + 1;
			int h2 = Heuristic(x2, y2, goal[0], goal[1]);
			AddToOpen(x2, y2, g2, h2, open, grid);
		}
	}
}

//4. Function
vector<vector<State>> Search(vector<vector<State>> grid, int start[2], int goal[2]){
	vector<vector<int>> open {};
	int x = start[0]; 
	int y = start[1];
	int g =0;
	int h;
	h= Heuristic(x, y, goal[0], goal[1]); //first h=0
	AddToOpen(x, y, g, h, open, grid);
	
	while(open.size() > 0){
		CellSort(&open);
		auto current = open.back();
		open.pop_back();
		x= current[0];
		y= current[1];
		grid[x][y] = State::kPath;
		
		if (x ==goal[0] && y==goal[1]){
			return grid;
		}
		ExpandNeighbors(current, goal, open, grid);
	}
	cout << "No path found\n";
        return vector<vector<State>>{};
}

		

string CellString(State cell ){
	switch(cell){
		case State::kObstacle: return "* ";
		case State::kPath: return "> ";
		default: return "0 ";
	}
}

void PrintBoard(vector<vector<State>> board){
	for (auto i=0; i<board.size(); i++){
		for(int j=0; j<board[i].size(); j++){
			cout << CellString(board[i][j]);
		}

		cout << "\n";
	}
}



//First Function
int main(){
        auto board = ReadBoardFile("1.board");

        int start[2] = {0,0};
        int goal[2] = {4,5};
        
	auto solution=Search(board,start, goal);

        PrintBoard(solution);
}



