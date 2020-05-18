# A_Star Algorithm / Path finding / Motion Planning problem

Given: Map, Starting Location, Goal Location, Cost

Goal: Find minimum cost path.


## Intro
Peter Hart, Nils Nilsson and Bertram Raphael of Stanford Research Institute (now SRI International)
first published the algorithm in 1968.</br>
• It can be seen as an extension of Edsger Dijkstra's 1959 algorithm.</br> 
• A* achieves better performance by using heuristics to guide its search.</br>
• Space complexity- O(b**d)


## Build
* mkdir a_star
* cd a_star
* git clone https://github.com/kamalikap/A_Star_algorithm.git
* g++ ./a_star.cpp -o a_star.out
* ./a_star.out


## Input:
0,1,0,0,0,</br>
0,1,0,0,0,</br>
0,1,0,0,0,</br>
0,1,0,0,0,</br>
0,0,0,1,0,</br>

## Output:
s * 0 0 0 0 </br>
p * 0 0 0 0 </br>
p * 0 0 0 0 </br>
p * 0 p p p </br>
p p p p * g </br>


## Algorithm
This algo is similar to breadth first search with additional step of computing heuristic.

Search( grid, start_point, goal_point ) :
1. Initialize an empty list of open nodes.
2. Initialize a starting node with the following:</br>
        • x and y values given by initial_point.</br>
        • g = 0, where g is the cost for each move.</br>
        • h given by the heuristic function (a function of the current coordinates and the goal).
3. Add the new node to the list of open nodes.
4. while the list of open nodes is nonempty:
        1. Sort the open list by f-value
        2. Pop the optimal cell (called the current cell).
        3. Mark the cell's coordinates in the grid as part of the path.
        4. if the current cell is the goal cell:</br>
                •return the grid.</br>
        5. else, expand the search to the current node's neighbors. This includes the following steps:</br>
                • Check each neighbor cell in the grid to ensure that the cell is empty: it hasn't been closed and is not an obstacle.</br>
                • If the cell is empty, compute the cost (g value) and the heuristic, and add to the list of open nodes.</br>
                • Mark the cell as closed.
5. If you exit the while loop because the list of open nodes is empty, you have run out of new nodes to explore and haven't found a path


## Explanation

Below is a 5x6 matrix with start and goal nodes assigned at (0, 0) and (4, 5) respectively. </br>

s|*|0|0|0|0</br>
0|*|0|0|0|0</br>
0|*|0|0|0|0</br>
0|*|0|0|0|0</br>
0|0|0|0|*|g</br>

Example of a heuristic fucntion</br>

s(9)|8|7|6|5|4</br>
8|7|6|5|4|3</br>
7|6|5|4|3|2</br>
6|5|4|3|2|1</br>
5|4|3|2|1|g(0)</br>


### Expansion without Heuristic
* Open = [0,0]- now we check if the start is goal or not , it not look at all the successors. 
g_value or expansion it took to get there. So here the g value is 0.
* [0,0]---[1, 0] [0, 1] >>  g val  is 1. 
Now we always expand with the smallest g_val. So these both have the same value so we expand one of them.
* [1, 0]-----[2, 0]  [1,1]  >> gval : 2.
* [2, 0] -----[3, 0]  [2,1] >> g val :3
* [3, 0] ------[4, 0]  [3, 1]  >> g val:4
* [2,1] -------[2,2] >> g val:4
* [4, 0] -------[4,1] >>  g val:5
* [2,2]--------[2,3]  >> g val: 5
* [4,1] ---------[4, 2]>> g val: 6
* [2, 3] --------[1,3]>> g val:6
* [4, 2] ----- [4, 3]>> g val: 7
* [1,3] ------[0, 3]  [1, 4] g val: 7
* [0, 3] ------[0, 4] g val: 8
* [1, 4] -------[1, 5] g val :8
* [0, 4] ---[0,5] g val: 9
* [1, 5] ----[2,5] g val:9
* [2, 5]----- [3, 5] g val: 10
* [3, 5] -----[4,5] gval: 11-GOAL


### Expansion with Heuristic
Heuristic function is an optimistic guess of how far we are away from the goal.
h(x, y) <= distance to goal from x, y.

* At first we will have a openlist, add our state, write the g-val and also 
g-val + heuristic(0 +9) which is called f-val.
* Open <State>  <g val>  <f val> </br>
Open [0, 0] 0  9 </br>
F = g +h(x,y)
* Now remove the element with the low F value.
* Suppose we try to expand node [4,1]
* [4, 1] 5 9
* [4,1] -----[4,2] 6 9
* [4,2]----[3, 2] 7 11
* [4,2]----[4, 3] 7  9   - A star makes a difference for the first time. Here f val of [4, 3] is lesser than [3, 2] so we expand with [4,3] node.
* [4,3] -----[3,3] 8 11
* [4,3]----[4,4] 8 9       - expand towards [4,4] as less f val
* [4, 4] ---[3,4] 9 11
* [4, 4]—[4,5] 9  9

Reached Goal


## References
* Wikipedia- A_star Search Algorithm
* C++ Nanodegree Udacity
