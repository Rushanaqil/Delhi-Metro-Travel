# Delhi-Metro-Travel


This is a simple C++ program that asks the user for details about the Delhi Metro's source and destination stations. The shortest path between these stations and the fare are then displayed by the program. It also comes with a metro map to help commuters find their way around the system.

The solution leverages Graph data structures. In this graph, nodes represent metro stations, each containing details like the station name and connecting lines. The edges, which represent the connections between stations, indicate the distance between them. The cost of each edge corresponds to this distance.

To determine the shortest path from the source to the destination station, the program employs algorithms such as Dijkstra, breadth-first search, and depth-first search. The fare is calculated based on the total distance traveled. Ultimately, the program displays the metro route and the total fare.

The primary functionality is implemented in “metro.cpp”.


`FUNCTIONS AND THEIR PURPOSE `


1. Class  `Metro_Graph`:
This class represents a graph data structure to model the Delhi Metro system.

2. Nested Class  `Vertex`:
-Purpose: Represents a vertex in the graph, which corresponds to a metro station.
-Attributes:
 “unordered_map<string, int> neighbours”: Stores the neighboring stations and the distances to them.

3. Static Member `vertices`:
- Purpose: Stores all the vertices (stations) in the metro network.
- Type: unordered_map<string, Vertex>

4. Constructor `Metro_Graph`:
- Purpose: Initializes the graph by clearing all vertices.

5. `int numVetex()`:
- Purpose: Returns the number of vertices (stations) in the graph.
- Return: Integer representing the number of vertices.

6. `bool CheckIfContainsVertex(string vname)`:
- Purpose: Checks if a vertex (station) with the given name exists in the graph.
- Parameters: “vname” - Name of the station.
- Return: Boolean indicating whether the vertex exists.

7. `void addStation(string vname)`:
- Purpose: Adds a new station to the graph.
- Parameters: “vname” - Name of the station to add.

8. `void removeStation(string vname)`:
- Purpose: Removes a station from the graph along with its connections.
- Parameter: “vname” - Name of the station to remove.

 9. `int numEdges()`:
- Purpose: Returns the number of edges (connections) in the graph.
- Return: Integer representing the number of edges.

10. `bool containsEdge(string vname1, string vname2)`:
- Purpose: Checks if there is an edge (connection) between two stations.
- Parameters: “vname1”, “vname2” - Names of the stations.
- Return: Boolean indicating whether the edge exists.

11. `void addEdge(string vname1, string vname2, int value)`:
- Purpose: Adds an edge (connection) between two stations with a specified distance.
- Parameters: “vname1”, “vname2” - Names of the stations, “value” - Distance between the stations.

12. `void removeEdge(string vname1, string vname2)`:
- Purpose: Removes the edge (connection) between two stations.
- Parameters: “vname1”, “vname2” - Names of the stations.

13. `void display_Map()`:
- Purpose: Displays the entire metro map, showing all stations and their connections.
- Output: Prints the map to the console.

14. `void display_Stations()`:
- Purpose: Displays a list of all stations in the metro network.
- Output: Prints the station names to the console.

15. `bool checkPath(string vname1, string vname2, unordered_map<string, bool> &processed)`: 
- Purpose: Checks if there is a path between two stations.
- Parameters: “vname1”, “vname2” - Names of the stations, 
  “processed” - Map to track processed stations.
- Return: Boolean indicating whether a path exists.

16. Nested Class `DijkstraPair`:
- Purpose: Represents a pair used in Dijkstra's algorithm for finding the shortest path.
- Attributes:
  - “string vname”: Name of the current station.
  - “string PathSoFar”: Path taken so far.
  - “int cost”: Cost (distance or time) to reach the current station.
- Operator Overloading: Defines the less than operator for priority queue ordering.

17. `int dijkstra(string source, string des, bool nan)`:
- Purpose: Uses Dijkstra's algorithm to find the shortest path from source to destination.
- Parameters: “source”, “des” - Names of the source and destination stations, “nan” - Boolean to differentiate between distance and time calculations.
- Return: Integer representing the shortest distance or time.

18. Nested Class `Pair`:
- Purpose: Represents a pair used in the search algorithms for finding minimum distance and time.
- Attributes:
  - `string vname`: Name of the current station.
  - `string PathSoFar`: Path taken so far.
  - `int min_dis`: Minimum distance to reach the current station.
  - `int min_time`: Minimum time to reach the current station.

19. `string Get_Minimum_Distance(string source, string destination)`:
- Purpose: Finds the path with the minimum distance between source and destination.
- Parameters: “source”, “destination” - Names of the source and destination stations.
- Return: String representing the path with the minimum distance.

20. `string Get_Minimum_Time(string source, string destination)`: 
- Purpose: Finds the path with the minimum time between source and destination.
- Parameters: “source”, “destination” - Names of the source and destination stations.
- Return: String representing the path with the minimum time.

21. `vector<string> get_Interchanges(string str)`:
- Purpose: Identifies the interchanges in a given path.
- Parameters: “str” - String representing the path.
- Return: Vector of strings representing the interchanges.

22. `Static void Create_Metro_Map(Metro_Graph &g)`: 
- Purpose: Initializes the metro map by adding stations and their connections.
- Parameters: “g” - Reference to a “Metro_Graph” object.

23. `Static string *printCodelist()`: 
- Purpose: Prints the list of stations along with their codes.
- Return: Array of strings representing the station codes.
  
24.  `int main()`:
- Purpose: Main function to interact with the metro map. Provides a menu for various actions.
- Output: Executes actions based on user input.

The `main()` function creates an instance of `Metro_Graph`, initializes the metro map, and provides a menu for the user to interact with the metro network, such as displaying stations, showing the metro map, finding shortest paths, etc.
