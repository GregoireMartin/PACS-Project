#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Vertex.h"
template<class T,class V>
class Vertex;
template<class T,class V>
class Edge;

template<class T, class V>
using VertexPointer= std::shared_ptr<Vertex<T,V>>;

template<class T,class V>
using EdgePointer= std::shared_ptr<Edge<T,V>>;

//Class Graph used to define a Graph
//A Graph is defined by a map where the key is defining the considered vertex or edge and the value is the attribute
//2 templates caracterize a Graph
//template T is the type of attribute of a Vertex or an Edge (which is the same type of attribute of an Edge)
//template V is the type of id of a Vertex (can be only an integer or a std::pair<int,int>)
//An unoriented graph will be describe by a map containing only one instance of each edge,the class doesn't check that the given map for the construction is valid
//If an user want to tranform a map into a valid map for an unoriented graph he must applied the struct unoriented_map to it before constructing the Graph
//The fact that a graph is oriented or not must be specified at the creation of the graph
template<class T,class V>
class Graph{
public:
    Graph(std::map<std::pair<int,int>,T> original_graph,bool oriented);                                                     //Constructor of a simple graph
    Graph(std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> product_graph_constructor,bool oriented);       //Constructor of a product_graph
    void add_vertex(T &attribute,V id_vertex);                                                                              //Add a vertex to the graph
    void add_edge(V id_vertex1,V id_vertex2,T &edge_attribute);                                                             //Add an edge to the graph
    void delete_vertex(V id_vertex);                                                                                        //Delete a vertex
    bool is_oriented() const;                                                                                               //Return the orientation of the graph
    bool isempty() const;                                                                                                   //Return a bool to check if the graph is empty
    int get_vertices_nbr() const;                                                                                           //Return the number of vertices of the graph
    std::list<VertexPointer<T,V>> get_vertices() const;                                                                     //Return a list of pointer to Vertices Object corresponding to the Vertices of the Graph
    std::list<V> get_vertices_id() const;                                                                                   //Return a list of vertices_id
    std::map<std::pair<V,V>,T> get_m_graph() const;                                                                         //Return the map describing the graph
    bool are_neighbors(V id_vertex1,V id_vertex2) const;                                                                    //Check if two vertices are neighbors in an undirected graph
    bool are_neighbors_directed(V id_vertex1,V id_vertex2) const;                                                           //Check if two vertices are neighbors in a directed graph
    void print(std::ostream &flux) const;                                                                                   //Print the information of the graph
protected:
    std::map<std::pair<V,V>,T> m_graph;     //The map describing the graph, the key is defining the vertex or the edge and the value is the attribute, a key (u1,u1) correspond to the vertex u1 whereas a key (u1,v1) correspond to the edge between u1 and v1
    int m_vertices_nbr;                     //Number of vertices of the Graph
    bool m_oriented;                        //Boolean equal to true if the graph is oriented,false otherwise
};

//Equivalence relationship between edges in a map
template<class V>
struct unoriented_map
{
    bool operator() (const std::pair<V,V> pair1,const std::pair<V,V> pair2)
    {
        if (pair1.first==pair2.second && pair1.second==pair2.first)
        {
            return false;
        }
        else
        {
            return pair1<pair2;
        }
    }
};

//Constructor of a simple graph
template<class T,class V>
Graph<T,V>::Graph(std::map<std::pair<int,int>,T> original_graph,bool oriented)
{
    m_graph=original_graph;
    m_oriented=oriented;
    m_vertices_nbr=0;
    typename std::map<std::pair<int,int>,T>::iterator it=original_graph.begin();
    for (;it!=original_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            m_vertices_nbr+=1;
        }
    }
}

//Constructor of a product_graph
template<>
Graph<double,std::pair<int,int>>::Graph(std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> product_graph_constructor,bool oriented)
{
    m_graph=product_graph_constructor;
    m_oriented=oriented;
    m_vertices_nbr=0;
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it=m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            m_vertices_nbr+=1;
        }
    }
}

//Give the number of vertices of a graph
template<class T,class V>
int Graph<T,V>::get_vertices_nbr() const
{
    return m_vertices_nbr;
}

//Return a bool to check if the graph is empty
template<class T,class V>
bool Graph<T,V>::isempty() const
{
    return bool(m_graph.size()==0);
}

//Add a vertex to the graph,update the vertices number
template<class T,class V>
void Graph<T,V>::add_vertex(T &attribute,V id_vertex)
{
    m_graph[std::pair<V,V>(id_vertex,id_vertex)]=attribute;
    m_vertices_nbr+=1;
}

//Delete a vertex
template<class T,class V>
void Graph<T,V>::delete_vertex(V id_vertex)
{
    typename std::map<std::pair<V,V>,T>::iterator it=m_graph.begin();
    for(;it!=m_graph.end();)
    {
        if ((it->first.first==id_vertex) || (it->first.second==id_vertex))
        {
            it=m_graph.erase(it);
        }
        else
        {
            ++it;
        }
    }
    m_vertices_nbr-=1;
}

//Add an edge to the Graph
template<class T,class V>
void Graph<T,V>::add_edge(V id_vertex1,V id_vertex2,T &edge_attribute)
{
    m_graph[std::pair<V,V>(id_vertex1,id_vertex2)]=edge_attribute;
}

//Return the orientation of the graph
template<class T,class V>
bool Graph<T,V>::is_oriented() const
{
    return m_oriented;
}

//Method that creates the Vertices and Edges object corresponding to the Graph and return a vector of shared pointers to the Vertices Objects
//(each of these Vertices are already connected with Edges according the Graph)
template<class T,class V>
std::list<VertexPointer<T,V>> Graph<T,V>::get_vertices() const
{
    typename std::map<std::pair<V,V>,T>::const_iterator it = m_graph.begin();
    typename std::list<VertexPointer<T,V>> vertices_vector;
    typename std::map<V,VertexPointer<T,V>> construction_map;
    for ( ; it != m_graph.end() ; ++it )
    {
        if (it->first.first==it->first.second)
        {
            V vertex_id(it->first.first);
            T attribute(it->second);
            vertices_vector.push_back(VertexPointer<T,V>(new Vertex<T,V>(attribute,vertex_id)));
            construction_map[it->first.first]=vertices_vector.back();
        }
    }
    it=m_graph.begin();
    if (m_oriented==false)
    {
        for ( ; it != m_graph.end() ; ++it )
        {
            if (it->first.first!=it->first.second)
            {
                T attribute(it->second);
                EdgePointer<T,V> pointer_edge(new Edge<T,V>(attribute,construction_map[it->first.first],construction_map[it->first.second]));
                construction_map[it->first.first]->add_edge(pointer_edge);
                construction_map[it->first.second]->add_edge(pointer_edge);
                construction_map[it->first.first]->add_neighbor(construction_map[it->first.second]);
                construction_map[it->first.second]->add_neighbor(construction_map[it->first.first]);
            }
        }
    }
    else
    {
        for ( ; it != m_graph.end() ; ++it )
        {
            if (it->first.first!=it->first.second)
            {
                T attribute(it->second);
                EdgePointer<T,V> pointer_edge(new Edge<T,V>(attribute,construction_map[it->first.first],construction_map[it->first.second]));
                construction_map[it->first.first]->add_edge(pointer_edge);
                construction_map[it->first.first]->add_neighbor(construction_map[it->first.second]);
            }
        }
    }
    return vertices_vector;
}


//Return a list of the graph vertices id
template<class T,class V>
std::list<V> Graph<T,V>::get_vertices_id() const
{
    std::list<V> vertices_id_vector;
    typename std::map<std::pair<V,V>,T>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            vertices_id_vector.push_back(it->first.first);
        }
    }
    return vertices_id_vector;
}

//Check if 2 vertices are neighbors according their id in the case of an undirected graph
template<class T,class V>
bool Graph<T,V>::are_neighbors(V id_vertex1,V id_vertex2) const
{
    assert(m_oriented==false);
    typename std::map<std::pair<V,V>,T>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (((it->first.first==id_vertex1) && (it->first.second==id_vertex2)) || ((it->first.first==id_vertex2) && (it->first.second==id_vertex1)))
        {
            return true;
        }
    }
    return false;
}

//Check if 2 vertices are neighbors according their id in the case of a directed graph
template<class T,class V>
bool Graph<T,V>::are_neighbors_directed(V id_vertex1,V id_vertex2) const
{
    assert(m_oriented==true);
    typename std::map<std::pair<V,V>,T>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if ((it->first.first==id_vertex1) && (it->first.second==id_vertex2))
        {
            return true;
        }
    }
    return false;
}

//Return the map describing the Graph
template<class T,class V>
std::map<std::pair<V,V>,T> Graph<T,V>::get_m_graph() const
{
    return m_graph;
}

//Print the information of the current Graph in the following order:
//for each element in the map:
//if it is a Vertex: Print the Vertex number and its attribute
//if it is an Edge: Print the Edge id and its attribute
template<class T,class V>
void Graph<T,V>::print(std::ostream &flux) const
{
    typename std::map<std::pair<V,V>,T>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            flux<<"Vertex number:"<<it->first.first<<" attribute: ";
            typename T::const_iterator it2 = it->second.begin();
            for (;it2!=it->second.end();++it2)
            {
                flux<<(*it2)<<",";
            }
            flux<<endl;
        }
        else
        {
           flux<<"Edge:"<<it->first.first<<","<<it->first.second<<" attribute: ";
           typename T::const_iterator it2=it->second.begin();
           for (;it2!=it->second.end();++it2)
            {
                flux<<(*it2)<<",";
            }
            flux<<endl;
        }
    }
}

//Specialization of the Print method for double attribute
//the information of the current Graph in the following order:
//for each element in the map:
//if it is a Vertex: Print the Vertex number and its attribute
//if it is an Edge: Print the Edge id and its attribute
template<>
void Graph<double,std::pair<int,int>>::print(std::ostream &flux) const
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            flux<<"Vertex number:"<<it->first.first<<" attribute: "<<it->second<<endl;
        }
        else
        {
           flux<<"Edge:"<<it->first.first<<","<<it->first.second<<" attribute: "<<it->second<<endl;
        }
    }
}

template<>
void Graph<double,int>::print(std::ostream &flux) const
{
    typename std::map<std::pair<int,int>,double>::const_iterator it = m_graph.begin();
    for (;it!=m_graph.end();++it)
    {
        if (it->first.first==it->first.second)
        {
            flux<<"Vertex number:"<<it->first.first<<" attribute: "<<it->second<<endl;
        }
        else
        {
           flux<<"Edge:"<<it->first.first<<","<<it->first.second<<" attribute: "<<it->second<<endl;
        }
    }
}

//Operator << add the information of the Graph in the ostream flux
template<class T,class V>
std::ostream &operator<<( std::ostream &flux, Graph<T,V> &graph1)
{
    graph1.print(flux) ;
    return flux;
};


#endif // GRAPH_H_INCLUDED
