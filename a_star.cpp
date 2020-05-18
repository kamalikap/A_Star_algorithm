#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>  //for sort

using namespace std;


enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};


//variable delta has 4 rows, with two co-ordinates
const int delta[4][2]{{-1,0}, {0, -1}, {1, 0}, {0,1}};


//3.
//Function parses each line in the file and whenever it encounters
// 1 gives it a value of kObstacle and for
// 0 kEmpty
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


//2.
//Function reads the file "1.board" line by line and adds it to the vector board.
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


//8.
// Function accepts two node of vector type int. Remember this node has the form of (x, y, g, h)
//f-value is argument’s g val(a[2]) + h val(a[3])
//It compares the f-val of both the nodes. (F1>f2)
//If the f val of first argument is greater than second, it will return true or else false.
//values in a Node are given as:
	//Node[0] is x co-ordinate of start
	//Node[1] is y co-ordinate of start
	//Node[2] is g value of the node
	//Node[3] is the heuristic value of the node
bool Compare(const vector<int> node1, const vector<int> node2){
	int f1 = node1[2] + node1[3];
	int f2 = node2[2] + node2[3];

	if (f1 > f2){
		return true;
	} else{
		return false;
	}
}


//7.
//Function sorts the open list according to f-val(g+h) from Compare function.
void CellSort(vector<vector<int>> *v){
	sort(v->begin(), v->end(), Compare);
}


//5.
//Function computes the distance to the goal
//Heuristic function calculates the Manhattan Distance.
//Ex:For first iteration- x1-0, y1-0, x2-4, y2-5 , MD = (4-0)+(5-0)=9,
//From first, it will take 9 steps to reach the goal.
int Heuristic(int x1, int y1, int x2, int y2 ){
	//Manhattan Distance
	int dist;
	dist = abs(x2-x1) + abs(y2-y1);
	return dist;
}


//10.
//Function ensures that the potential neighbor coordinates are 
//on the grid and that the cell is open/empty.
//Checks the (x,y) coordinate is on the grid.
//	X > 0 and < grid.size
//	Y> 0 and < length of x(grid[0])
//	If both x and y are present then check the node is empty, (by default, the node is set to empty, if it is not closed or an obstacle)
//	If both the conditions are valid, return true 
bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
	
	bool on_grid_x = (x>=0 && x< grid.size());
	bool on_grid_y = (y>=0 && y< grid[0].size());
	
	if (on_grid_x  && on_grid_y)
		return grid[x][y]== State::kEmpty;
	return false;
}


//6. 
//Function adds the node to the open list and marks the grid cell as closed.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid){
	vector<int> node {x,y,g,h};
	open.push_back(node);
	grid[x][y] = State::kClosed;
}


//9.
//Function loops through the current node's neighbors and calls appropriate functions to add neighbors to the open list.
void ExpandNeighbors(const vector<int> current, int goal[2], vector<vector<int>> &open, vector<vector<State>> &grid){
	
	//assign the values of x, y, g to current node values.
	int x = current[0];
	int y = current[1];
	int g = current[2];

	// loop through all the potential neighbors of the current node.
	for(int i=0; i< 4; i++){
		int x2 = x + delta[i][0];
		int y2 = y + delta[i][1];

		//check if the cell is valid.
		if (CheckValidCell(x2, y2, grid)){
			
			//if the cell is valid then update the g and h values
			//add to the open vectors list.
			int g2 = g + 1;
			int h2 = Heuristic(x2, y2, goal[0], goal[1]);
			AddToOpen(x2, y2, g2, h2, open, grid);
		}
	}
}


//4.
//Function performs the Search operation.
//int start[2] represnts two elements in the array.
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

		//initialize the current value to the last element of the vector.
		auto current = open.back();

		//pop the last element of the vector
		open.pop_back();
		x= current[0];
		y= current[1];
		grid[x][y] = State::kPath;
		
		//if x and y equals to goal then, we reached the end point.
		//return the grid.
		if (x ==goal[0] && y==goal[1]){
			grid[start[0]][start[1]]= State::kStart;
			grid[goal[0]][goal[1]]= State::kFinish;
			return grid;
		}
		
		//if length of open vector is zero then check for neighbors.
		ExpandNeighbors(current, goal, open, grid);
	}
	cout << "No path found\n";
        return vector<vector<State>>{};
}

		
//12.
//Function assigns values to the particular States.
string CellString(State cell ){
	switch(cell){
		case State::kObstacle: return "* ";
		case State::kPath: return "> ";
		case State::kStart: return "s ";
		case State::kFinish: return "g ";
		default: return "0 ";
	}
}


//11.
//Function prints the grid with the updated values.
void PrintBoard(vector<vector<State>> board){
	for (auto i=0; i<board.size(); i++){
		for(int j=0; j<board[i].size(); j++){
			cout << CellString(board[i][j]);
		}

		cout << "\n";
	}
}


//1.
//Main Function
int main(){
        auto board = ReadBoardFile("1.board");

        int start[2] = {0,0};
        int goal[2] = {4,5};
        
	auto solution=Search(board,start, goal);

        PrintBoard(solution);
}


