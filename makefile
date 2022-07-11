all:
	bellmanford.exe
	kruskal.exe
	dijkstra.exe

bellmanford.exe: bellmanford.cpp
	g++ -o bellmanford.exe bellmanford.cpp

dijkstra.exe:	dijkstra.cpp
	g++ -o dijkstra.exe dijkstra.cpp

kruskal.exe:	kruskal.cpp
	g++ -o kruskal.exe kruskal.cpp
	