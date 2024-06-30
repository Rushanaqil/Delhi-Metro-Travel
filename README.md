# Delhi-Metro-Travel


This is a simple C++ program that asks the user for details about the Delhi Metro's source and destination stations. The shortest path between these stations and the fare are then displayed by the program. It also comes with a metro map to help commuters find their way around the system.

The solution leverages Graph data structures. In this graph, nodes represent metro stations, each containing details like the station name and connecting lines. The edges, which represent the connections between stations, indicate the distance between them. The cost of each edge corresponds to this distance.

To determine the shortest path from the source to the destination station, the program employs algorithms such as Dijkstra, breadth-first search, and depth-first search. The fare is calculated based on the total distance traveled. Ultimately, the program displays the metro route and the total fare.

The primary functionality is implemented in “metro.cpp”.

