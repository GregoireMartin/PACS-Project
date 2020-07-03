#ifndef SET_OF_GRAPH_H_INCLUDED
#define SET_OF_GRAPH_H_INCLUDED
#include "Graph.h"
template<class T,class V>
class Graph;

template<class T, class V>
using VertexPointer= std::shared_ptr<Vertex<T,V>>;

template<class T,class V>
using EdgePointer= std::shared_ptr<Edge<T,V>>;

template<class T, class V>
using GraphPointer= std::shared_ptr<Graph<T,V>>;

//Class Set_of_Graph created to define a set of graph
//template T defines the type of Vertex and Edge attribute
//template V defines the type of Vertex id (can only be an integer or a std::pair<int,int>)
//A set of graph is defined as a vector of pointers to graph objects
template<class T,class V>
class Set_of_Graph{
public:
    Set_of_Graph();                                   //Initialize an empty Set_of_Graph
    void add_graph(GraphPointer<T,V> graph1);         //Add a graph to the Set_of_Graph
    void delete_graph(GraphPointer<T,V> graph1);      //Delete a graph to the Set_of_Graph
    std::list<GraphPointer<T,V>> get_set_of_graph() const;   //Return a list containing pointers to the graphs
    GraphPointer<T,V> get_graph_pointer(int place) const;    //Return the pointer to graph in position place of the set
protected:
    typename std::list<GraphPointer<T,V>> m_set_of_graph;  //list of pointers to Graph Objects
};


//Initialize an empty Set_of_Graph
template<class T,class V>
Set_of_Graph<T,V>::Set_of_Graph():m_set_of_graph(std::list<GraphPointer<T,V>>())
{
};


//Add a graph to the Set_of_Graph
template<class T,class V>
void Set_of_Graph<T,V>::add_graph(GraphPointer<T,V> graph1)
{
    m_set_of_graph.push_back(graph1);
}

//Delete a graph of the Set_of_Graph
template<class T,class V>
void Set_of_Graph<T,V>::delete_graph(GraphPointer<T,V> graph1)
{
    bool condition(false);
    typename std::list<GraphPointer<T,V>>::iterator it=m_set_of_graph.begin();
    for (;it!=m_set_of_graph.end();)
    {
        if ((*it)==graph1)
        {
            it=m_set_of_graph.erase(it);
            condition=true;
        }
        else
        {
            ++it;
        }
    }
    if (condition==false)
    {
        std::cout<<"The searched graph is not in the current Set of Graphs"<<endl;
    }
}

//Return a list of pointers to the graphs
template<class T,class V>
std::list<GraphPointer<T,V>> Set_of_Graph<T,V>::get_set_of_graph() const
{
    return m_set_of_graph;
}

//Return the pointer to graph in position place of the set
template<class T,class V>
GraphPointer<T,V> Set_of_Graph<T,V>::get_graph_pointer(int place) const
{
    assert(place<=int(m_set_of_graph.size()));
    int index(0);
    GraphPointer<T,V> pointer(nullptr);
    typename std::list<GraphPointer<T,V>>::const_iterator it=m_set_of_graph.begin();
    for(;it!=m_set_of_graph.end();++it)
    {
        index+=1;
        if (index==place)
        {
            pointer=(*it);
        }
    }
    return pointer;
}

#endif // SET_OF_GRAPH_H_INCLUDED
