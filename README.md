## Documentation
## Programming language - C++

Challenges
1) Packages sorting based on the urgency and weight of the packages
2) Path finding from start (S) to the end (E) while avoiding obstacles (X)

Process
1) Packages sorting
    - Using standard 'algorithm' library in order to solve it
    - Sorting higher urgency goes first followed by heavier weight goes first

2) Pathfinding
    - Using A* algorithm
    - A* guarantees the shortest yet optimum path if the heuristic is admissible

Types of algorithm
1) A* algorithm
2) Dijkstra's algorithm
3) Breadth-First Search algorithm
4) Greedy Best-First Search algorihtm
5) Depth-First Search algorithm

Comparison in theory
1) A* algorithm
    A* algorithm combines actual path cost and heuristic value to reach to the goal.  In this case, it is finding the OPTIMAL path to reach the end point.  This algorithm is able to find the shortest path efficiently.  However, it is only optimal when heuristic is admissible.
2) Dijkstra's algorithm
    Dijakstra's algorithmm finds the SHORTEST path by considering the actual cost of the path without a heuristic value.  It gurantees the shortest path in non-weighted graph.  However, when it comes to heuristic-driven searches, it will be slower than A* algorithm because Dijkstra's algorithm explores all possible paths and consider all nodes in an increasing order of cost.
3) Breadth-First Search algorithm
    Breadth-First Seach algorithm also gurantees the SHORTEST path in non-weighted graph.  It explores all the nodes before moving deeper and it is quite simple to implement if the graph is unweighted.  Due to the nature of exploring all the nodes, it is meant to be slow.  Its is used in unweighted map such as maze.
4) Greedy Best-First Search algorihtm
    Greedy Best-First Search algorithm is another algorithm that uses heuristic values to prioritize nodes closer to the goal.  It is by far the fastest algorithm but it is not always accurate.  It is good for finding path quickly but not guranteed the shortest or optimal path.  It may get stuck in a local minima if the heuristic is misleading
5) Depth-First Search algorithm
    Depth-First Search algorithm takes the longest time to execute as it explore the entire nodes.  This feature is great for programmes such as maze because it explore entire nodes in order to find a optimum path.  In return, Dfs takes the long time in order to find the end path.

- Algorithm that uses heuristic values -> A* algorithm and Greedy Best-First Search algorithm
- Time execution test, lowest time to highest by theory -> A* (with a good heuristic), Dijakstra, BFS, GBFS, DFS

Comparison by practical
This comparison is made with a random 50 x 50 grid to test the time execution.
1) A* algorithm
![Astar1](https://github.com/user-attachments/assets/cdeb6c54-ca07-4754-958e-439c51684fb7)
![Astar2](https://github.com/user-attachments/assets/0b3f69e8-733f-45a8-9907-4613a5f533fa)
![Astar3](https://github.com/user-attachments/assets/704c6777-6abc-4469-a7c9-9fc2bd294dff)
Average time execution -> 602.3 ms

3) Dijkstra's algorithm
![Dijk1](https://github.com/user-attachments/assets/3a6104ba-6c49-43ff-8e9e-38b263260606)
![Dijk2](https://github.com/user-attachments/assets/77179260-85e2-47d0-97c8-282acc843926)
![Dijk3](https://github.com/user-attachments/assets/b332fd54-96f4-4ad5-954e-999d48482209)
Average time execution -> 3687 ms

5) Breadth-First Search algorithm
![Bfs1](https://github.com/user-attachments/assets/066ab89b-f06d-429b-b444-60d1b4873d2d)
![Bfs2](https://github.com/user-attachments/assets/886d80d6-75a6-4ca3-b0a2-b66da2dc659b)
![Bfs3](https://github.com/user-attachments/assets/4dbd004e-c209-4d19-a6f7-95ad457180d2)

Average time execution -> 1309.7 ms
4) Greedy Best-First Search algorihtm
![Gbfs1](https://github.com/user-attachments/assets/a38758ae-2d56-405a-9056-6499b5f4d206)
![Gbfs2](https://github.com/user-attachments/assets/bf420abb-1257-4483-bbcd-9a38718b51b6)
![Gbfs3](https://github.com/user-attachments/assets/eebf61f3-6e54-49b4-85d0-33d06f06ffa3)

Average time execution -> 191.7 ms

5) Depth-First Search algorithm
![Dfs1](https://github.com/user-attachments/assets/1e626915-8724-40ed-91f0-567f1f09e789)
![dfs2](https://github.com/user-attachments/assets/6cfed591-7031-416b-bcb5-7442aaeccf06)
![Dfs3](https://github.com/user-attachments/assets/333a3a65-fbd6-4d6a-9cb5-8bb024426f02)
Average time execution -> 1567 ms

Time execution test, lowest to highest time by practical -> GBFS, A*, BFS, DFS, Dijakstra
Reasoning
1) The excellent performance of Gbfs suggests that the heuristic used is very accurate in estimating the distance to the goal. In such cases, GBFS can be remarkably fast as it prioritizes exploring nodes that appear closest to the goal.
2) Dijkstra's algorithm doesn't use a heuristic to guide the search. It explores nodes uniformly, which can lead to exploring many unnecessary nodes, especially in larger or more complex grids.
3) Bfs explores the graph level by level, ensuring it finds the shortest path. However, it might explore more nodes than A* in some cases, leading to a moderate execution time.
4) Dfs suppose to be the slowest but the testing that i did shows that dijakstra is the slowest.  It could be because of the map grid size is too big and takes alot longer for the dijakstra to explore one by one.  Another reason could be because of the dijakstra implementation might have inefficientcy that contributes to the slow performance as the test code is done with AI code.
