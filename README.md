# GraphSpace
## Graph Space Package on C++

This C++ package allows to create and manipulate population of Graphs and performs a matching between them.
The package is organized as follow:

- Vertex.h: template class creating a vertex of a graph
- Edge.h: template class creating an edge between two vertices
- Graph.h: template class creating a graph (can be oriented or not)
- setofGraph.h: template class creating a set of graph
- usefullfunctions.h: mathematical and other functions usefull for the matching
- main.cpp: main file launching instances
- database_generation.cpp: functions generating the words database, you can create your own words by following the commentary on the beginning if the file but take care not all the letters are implemented
- database_generation.h: header file of the database

### Compilation
The compilation can be done with the following instructions:
**g++ -g -Wall -std=c++11 database_generation.cpp main.cpp -o results**

### How to test the code
On main.cpp:

1. Define out of the main loop the type of graph you want to create using the following by typing in C++: typedef std::map<std::pair<V,V>,T> Mymap;
   Where you replace T and V by respectively the type of the attribute and the type of the id.
2. Define your map (describing your graph) either by using the existing add_letter functions or on your own. If you want to create an undirected graph than you don't need to specify two times each edge. Don't forget to create the boolean oriented equal to true if your graph is oriented and false otherwise.
3. Create and initialize your Graph Object dynamically by using: GraphPointer<T,V> new.
4. You can if you want to print your graphs by running the std::cout<<Your graph Object<<std::endl; command.
5. You can now use the matching method you want to match your two graphs and obtain the result with the following type of command:   std::pair<std::list<std::pair<int,int>>,double> result=the_matching_function(parameters);
6. You can print the Optimal permutation and the distance obtained in the previous step.

## Python matcher and database

To use the Python code you need to download the git repository in the following link:   https://github.com/annacalissano/GraphSpace/tree/GraphPacs
Then you need to install cplex by running in your environment the following command line:   pip install cplex
By doing so you will install the Basic version of cplex so you won't be able to perform GAS matching on big instances. If you want to be able to use the GAS matching on big instances you need to download the Student version of cplex on Ibm: https://www.ibm.com/academic/technology/data-science
However the services seems to be down so you might just take the basic cplex version (I wasn't able to download the Student one either).
Then open the jupyter notebook(be sure to have a recent version of Python) and change the paths to the GraphSpace package to the repository where you have download it.

### How to test the code
1. Run the kernel containing the libraries importation and the definitions of add_letter functions and create a new Kernel.
2. Define your dictionnaries (describing your graphs) either by using the existing add\_letter functions or on your own. If you want to create an undirected graph you have to specify two times each edge. If you use the add_letter functions to create a new word you have to start your indices at -1 and don't forget to upload the value of the indice at each step and to link the letters with theirs neighbors by doing as followed:
   x1,first_indice=add_letter(x1,first_indice)
   x1[(first_indice+1,first_indice)]=[0,0]
   x1[(first_indice,first_indice+1)]=[0,0]
   Where first_indice must start at -1 at the beginning (you need to be sure that your vertices start by number 0 with no missing number)
3. Create your Graphset with your 2 dictionaries x1 and x2:
   G = GraphSet()
   G.add(Graph(x=x1, y=None, adj=None))
   G.add(Graph(x=x2, y=None, adj=None))
4. Choose your matching and launch it:
   match = GA(euclidean())
   match.dis(G.X[0], G.X[1])
5. Print the result of the matching: print(match.f)



## Acknowledgements

I would like to thank Anna Calissano for her help and kindness throughout the project. Thanks also to Gianluca Zeni who answered my questions as soon as possible. Finally, thanks to Noemi Rossi and Matteo Savino for theirs advices.