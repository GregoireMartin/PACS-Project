#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include <memory>
#include <list>
#include "Vertex.h"
template<class T,class V>
class Vertex;

template<class T,class V>
using VertexPointer= std::shared_ptr<Vertex<T,V>>;

template<class T,class V>
class Edge;

template<class T,class V>
using EdgePointer= std::shared_ptr<Edge<T,V>>;


//Class Edge which describe an edge between two vertices in a graph, in case of an directed graph an Edge goes from the first vertex to the second vertex
//template T is the type of attribute of a Edge (which is the same type of attribute of an Vertex)
//template V is the type of id of a Vertex (generally an integer)
template<class T,class V>
class Edge
{
public:
    Edge(const T & _attribute, const VertexPointer<T,V> vertex1, const VertexPointer<T,V> vertex2);         //Constructor with initialization of vertices as Vertex object
    void give_attribute(const T & _attribute);                              //Changes the attribute of the Edge
    void give_vertices(const VertexPointer<T,V> vertex1,const Vertex<T,V> vertex2);    //Changes the list of Vertices of the Edge
    void print(std::ostream &flux) const;                                   //Print the information about the Edge
    T get_attribute() const;                                                //Return the attribute of the Edge
    VertexPointer<T,V> first_vertex() const;                                //Return a pointer to the first Vertex of the Edge
    VertexPointer<T,V> second_vertex() const;                               //Return a pointer to the second Vertex of the Edge
    V first_vertex_id() const;                                              //Return the id of the first Vertex of the Edge
    V second_vertex_id() const;                                             //Return the id of the second Vertex of the Edge

    //Check if 2 edges are equal
    friend bool operator == (const EdgePointer<T,V> lhs, const EdgePointer<T,V> rhs){
        return lhs->first_vertex_id() == rhs->first_vertex_id() && lhs->second_vertex_id()==rhs->second_vertex_id();
    };
protected:
    T m_attribute;                                                          //Attribute of the Edge
    std::list<VertexPointer<T,V>> m_vertices;                               //List of pointers to vertices of the Edge
    std::pair<V,V> vertices_id;                                             //Pair of id corresponding to the Edge's vertices
};


//Constructor with initialization of vertices as Vertex object
template<class T,class V>
Edge<T,V>::Edge(const T & attribute,const VertexPointer<T,V> vertex1, const VertexPointer<T,V> vertex2):m_attribute(attribute),m_vertices(std::list<VertexPointer<T,V>>({vertex1,vertex2})),vertices_id(std::pair<V,V>({vertex1->get_id(),vertex2->get_id()}))
{
};



//Change the attribute of the Edge
template<class T,class V>
void Edge<T,V>::give_attribute(const T &attribute)
{
    m_attribute=attribute;
}


//Give Vertices to an Edge and erase the previous ones
template<class T,class V>
void Edge<T,V>::give_vertices(const VertexPointer<T,V> vertex1,const Vertex<T,V> vertex2)
{
    m_vertices.clear();
    m_vertices.push_back(vertex1);
    m_vertices.push_back(vertex2);
    vertices_id.first=vertex1->get_id();
    vertices_id.second=vertex2->get_id();
}

//Return the Edge attribute
template<class T,class V>
T Edge<T,V>::get_attribute() const
{
    return m_attribute;
}


//Return the first Vertex of the Edge
template<class T,class V>
VertexPointer<T,V> Edge<T,V>::first_vertex() const
{
    return *(m_vertices.begin());
}

//Return the first Vertex_id of the Edge
template<class T,class V>
V Edge<T,V>::first_vertex_id() const
{
    return vertices_id.first;
}

//Return the second Vertex of the Edge
template<class T,class V>
VertexPointer<T,V> Edge<T,V>::second_vertex() const
{
    return *(std::advance(m_vertices.end(),-1));
}

//Return the second Vertex_id of the Edge
template<class T,class V>
V Edge<T,V>::second_vertex_id() const
{
    return vertices_id.second;
}


//Print the information of an Edge in the following order:
//Ids of the Vertices
//Edge attribute
template<class T,class V>
void Edge<T,V>::print(std::ostream &flux) const
{
    typename std::list<VertexPointer<T,V>>::const_iterator it=m_vertices.begin();
    flux<<"Neighbors Vertices:"<<std::endl;
    for (;it!=m_vertices.end();++it)
    {
        flux << (*it)->get_id();
    }
    flux<<std::endl;
    flux<<"Edge attribute: ";
    typename T::const_iterator it2=m_attribute.begin();
    for (;it2!=m_attribute.end();++it2)
    {
        flux <<(*it2)<<",";
    }
    flux<<std::endl;

};

//Specialized print function made for product_graph print
//only print the Edge attribute
template<>
void Edge<double,std::pair<int,int>>::print(std::ostream &flux) const
{
    flux<<"Edge attribute: "<<m_attribute<<std::endl;

};

//Operator << which added the print information of an Edge to the current ostream flux
template<class T,class V>
std::ostream &operator<<( std::ostream &flux, Edge<T,V> &edge1)
{
    edge1.print(flux) ;
    return flux;
};



#endif // EDGE_H_INCLUDED
