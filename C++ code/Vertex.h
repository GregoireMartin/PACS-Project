#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include <map>
#include <iostream>
#include "Edge.h"
#include "usefulfunctions.h"

using std::cout;
using std::endl;
template<class T,class V>
class Edge;
class ostream;

template<class T, class V>
using VertexPointer= std::shared_ptr<Vertex<T,V>>;

template<class T,class V>
using EdgePointer= std::shared_ptr<Edge<T,V>>;


//Class Vertex used to define a Vertex in a Graph
//2 templates caracterize a Vertex
//template T is the type of attribute of a Vertex (which is the same type of attribute of an Edge)
//template V is the type of id of a Vertex (generally an integer)
template<class T,class V>
class Vertex{
protected:
    std::list<VertexPointer<T,V>> m_neighbors;          //list of pointers to neighbors vertices
    std::list<EdgePointer<T,V>> m_edges;                //list of pointers to linked edges
    T m_attribute;                                      //Attribute of the Vertex
    V m_id;                                             //Id of the Vertex

public:
    //Constructor of Vertex Class
    Vertex(const T & _attribute,const V & _id):m_attribute(_attribute),m_id(_id){};
    //Constructor of Vertex Class with initialization of neighbors and edges lists
    Vertex(const std::list<VertexPointer<T,V>> & _neighbors, const std::list<EdgePointer<T,V>> & _edges, const T & _attribute,
    const V & _id):m_attribute(_attribute),m_neighbors(_neighbors),m_edges(_edges),m_id(_id){};
    std::list<VertexPointer<T,V>> get_neighbors() const;    //Return the list of neighbors vertices
    std::list<EdgePointer<T,V>> get_edges() const;         //Return the list of edges linked to the vertex
    void print(std::ostream &flux) const;               //Print the Vertex information into an ostream
    void redefine_attribute(const T &attribute);        //Change the attribute of the Vertex
    V get_id() const;                                   //Return the id of the Vertex
    T get_attribute() const;                            //Return the attribute of the Vertex
    T get_edge_attribute_directed(VertexPointer<T,V> neighbor) const; //Return the attribute of an edge linking the Vertex and his neighbor in a directed graph
    T get_edge_attribute(VertexPointer<T,V> neighbor) const;          //Return the attribute of an edge linking the Vertex and his neighbor in an undirected graph
    void add_neighbor(const VertexPointer<T,V> neighbor);                   //Add a neighbor to the Vertex
    void add_edge(const EdgePointer<T,V> edge);                             //Add an edge to the Vertex
    void delete_neighbor(const VertexPointer<T,V> neighbor);                //Delete a neighbor of the Vertex
    void delete_edge(const EdgePointer<T,V> edge);                          //Delete an edge of the Vertex
    void replace_neighbor(const VertexPointer<T,V> neighbor1,const VertexPointer<T,V> neighbor2);   //Replace a neighbor of the Vertex
    void replace_edge(const EdgePointer<T,V> edge1,const EdgePointer<T,V> edge2);                   //Replace an edge of the Vertex
    bool is_neighbor(const Vertex<T,V> &vertex) const;                            //Return a bool true if the considerated vertex is a neighbor of the Vertex
    bool is_neighbor(const V vertex_id) const;                                    //Return a bool true if the considerated vertex is a neighbor of the Vertex
    double get_distance(const VertexPointer<T,V> vertex)const;                          //Return the distance between 2 vertices
    friend bool operator == (const VertexPointer<T,V> lhs, const VertexPointer<T,V> rhs){
        return lhs->get_id() == rhs->get_id();
    };
};

/*
Ordering relationship made to sort a vector of pointers to vertices according their id
template<class T,class V>
struct less_than_id
{
    bool operator() (VertexPointer<T,V> vertex1,VertexPointer<T,V> vertex2)
    {
        return (vertex1->get_id() <  vertex2->get_id());
    }
};
*/

//Return the list of neighbors vertices
template<class T,class V>
std::list<VertexPointer<T,V>> Vertex<T,V>::get_neighbors() const
{
  return m_neighbors;
}

//Return the list of linked edges
template<class T,class V>
std::list<EdgePointer<T,V>> Vertex<T,V>::get_edges() const
{
    return m_edges;
}

//get the attribute of an edge in an undirected graph
template<class T,class V>
T Vertex<T,V>::get_edge_attribute(VertexPointer<T,V> neighbor) const
{
    bool criteria(false);
    T value;
    typename std::list<EdgePointer<T,V>>::const_iterator it=m_edges.begin();
    for (;it!=m_edges.end();++it)
    {
        if ((((*it)->first_vertex_id()==m_id) && ((*it)->second_vertex_id()==(*neighbor).get_id())) || (((*it)->second_vertex_id()==m_id) && ((*it)->first_vertex_id()==(*neighbor).get_id())))
        {
            criteria=true;
            value=(*it)->get_attribute();
        }
    }
    assert(criteria==true);
    return value;
}

//get the attribute of an edge in an directed graph
template<class T,class V>
T Vertex<T,V>::get_edge_attribute_directed(VertexPointer<T,V> neighbor) const
{
    bool criteria(false);
    T value;
    typename std::list<EdgePointer<T,V>>::const_iterator it=m_edges.begin();
    for (;it!=m_edges.end();++it)
    {
        if (((*it)->first_vertex_id()==m_id) && ((*it)->second_vertex_id()==(*neighbor).get_id()))
        {
            criteria=true;
            value=(*it)->get_attribute();
        }
    }
    assert(criteria==true);
    return value;
}

//Return the id of the Vertex
template<class T,class V>
V Vertex<T,V>::get_id() const
{
    return m_id;
}

//Change the attribute of the Vertex
template<class T,class V>
 void Vertex<T,V>::redefine_attribute(const T &attribute)
 {
     m_attribute=attribute;
 }

//Return the attribute of the Vertex
template<class T,class V>
T Vertex<T,V>::get_attribute() const
{
    return m_attribute;
}

//Add a neighbor to the neighbors vertices
//the neighbor will always be added at the end of the current neighbors_list
//Please take care adding a neighbor doesn't add any edges to the vertex so remember to use the add_edge function after add_neighbor.
template<class T,class V>
void Vertex<T,V>::add_neighbor(VertexPointer<T,V> neighbor)
{
    m_neighbors.push_back(neighbor);
}

//Add an edge to the linked edges
//the edge will always be added at the end of the current edges_list
template<class T,class V>
void Vertex<T,V>::add_edge(EdgePointer<T,V> edge)
{
    m_edges.push_back(edge);
}


//Erase a neighbor in the neighbors_vertices
template<class T,class V>
void Vertex<T,V>::delete_neighbor(VertexPointer<T,V> neighbor)
{
    bool criteria(false);
    typename std::list<VertexPointer<T,V>>::iterator it = m_neighbors.begin();
    for ( ; (it != m_neighbors.end()) && (criteria==false) ; )
    {
        if ((*neighbor)=(*(*it)))
        {
            it=m_neighbors.erase(it);
            criteria=true;
        }
        else
        {
            ++it;
        }
    }
    if (criteria==false)
    {
        std::cout<<"This vertex is not a neighbor"<<endl;
    }
}


//Erase an edge in the linked_edges
template<class T,class V>
void Vertex<T,V>::delete_edge(EdgePointer<T,V> edge)
{
    bool criteria(false);
    typename std::list<EdgePointer<T,V>>::iterator it = m_edges.begin();
    for ( ; (it != m_edges.end()) && (criteria==false) ;)
    {
        if ((*edge)=(*(*it)))
        {
            it=m_edges.erase(it);
            criteria=true;
        }
        else
        {
            ++it;
        }
    }
    if (criteria==false)
    {
        std::cout<<"The edge indicated is not an edge of the Vertex"<<endl;
    }
}

//Replace a neighbor1 by a neighbor2 in the neighbors_vector
template<class T,class V>
void Vertex<T,V>::replace_neighbor(VertexPointer<T,V> neighbor1,VertexPointer<T,V> neighbor2)
{
    bool criteria(false);
    typename std::list<VertexPointer<T,V>>::iterator it = m_neighbors.begin();
    for ( ; (it != m_neighbors.end()) && (criteria==false) ; ++it )
    {
        if ((*neighbor1)=(*(*it)))
        {
            (*it)=neighbor2;
            criteria=true;
        }
    }
    if (criteria==false)
    {
        std::cout<<"The first Vertex indicated is not a neighbor of the Vertex"<<endl;
    }
}

//Replace an edge1 by an edge2 in the linked_edges
//Throw an exception if the edge1 is not find as an edge of the Vertex
template<class T,class V>
void Vertex<T,V>::replace_edge(EdgePointer<T,V> edge1,EdgePointer<T,V> edge2)
{
    typename std::list<EdgePointer<T,V>>::iterator it = m_edges.begin();
    bool criteria(false);
    for ( ; (it != m_edges.end()) && (criteria==false) ; ++it )
    {
        if ((*edge1)=(*(*it)))
        {
            (*it)=edge2;
            criteria=true;
        }
    }
    if (criteria==false)
    {
        std::cout<<"The first edge indicated is not an edge of the Vertex"<<endl;
    }
}


//Calculate the distance between two vertices
//The vertices don't need to be neighbors
//The distance is calculated as follow:
//generate a new vector for each of the two vertices which is composed by the old vertex attribute and
//the vector of mean of the linked_edges attribute
//The distance is given as the euclidian distance between these 2 new vectors
//The get_distance function is defined for the following vertex/edge attributes: int,double,vector<int>,vector<double>.
template<>
double Vertex<std::vector<int>,int>::get_distance(const VertexPointer<std::vector<int>,int> vertex)const
{
    std::vector<int> vector_made_for_distance_computation1=m_attribute;
    std::vector<int> vector_made_for_distance_computation2=vertex->get_attribute();
    std::list<EdgePointer<std::vector<int>,int>> construction_list(vertex->get_edges());
    int number_of_neighbors1(m_neighbors.size()),number_of_neighbors2(construction_list.size());
    std::vector<int> mean_vector1(m_attribute.size(),int(0)),mean_vector2(vertex->get_attribute().size(),int(0));
    if ((m_edges.empty()) && (construction_list.empty()))
    {
        return euclidean_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
    else
    {
        typename std::list<EdgePointer<std::vector<int>,int>>::const_iterator it1=m_edges.begin();
        typename std::list<EdgePointer<std::vector<int>,int>>::const_iterator it2=construction_list.begin();
        for (;it1!=m_edges.end();++it1)
        {
            mean_vector1+=(*it1)->get_attribute();
        }
        for (;it2!=construction_list.end();++it2)
        {
            mean_vector2+=(*it2)->get_attribute();
        }
        if (number_of_neighbors1!=0)
        {
            mean_vector1/=number_of_neighbors1;
        }
        if (number_of_neighbors2!=0)
        {
            mean_vector2/=number_of_neighbors2;
        }
        vector_made_for_distance_computation1.insert( vector_made_for_distance_computation1.end(), mean_vector1.begin(), mean_vector1.end() );
        vector_made_for_distance_computation2.insert( vector_made_for_distance_computation2.end(), mean_vector2.begin(), mean_vector2.end() );
        return vectors_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
}

template<>
double Vertex<std::vector<double>,int>::get_distance(const VertexPointer<std::vector<double>,int> vertex)const
{
    std::vector<double> vector_made_for_distance_computation1=m_attribute;
    std::vector<double> vector_made_for_distance_computation2=vertex->get_attribute();
    std::list<EdgePointer<std::vector<double>,int>> construction_list(vertex->get_edges());
    double number_of_neighbors1(m_neighbors.size()),number_of_neighbors2(construction_list.size());
    std::vector<double> mean_vector1(m_attribute.size(),double(0.0)),mean_vector2(vertex->get_attribute().size(),double(0.0));
    if ((m_edges.empty()) && (construction_list.empty()))
    {
        return euclidean_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
    else
    {
        typename std::list<EdgePointer<std::vector<double>,int>>::const_iterator it1=m_edges.begin();
        typename std::list<EdgePointer<std::vector<double>,int>>::const_iterator it2=construction_list.begin();
        for (;it1!=m_edges.end();++it1)
        {
            mean_vector1+=(*it1)->get_attribute();
        }
        for (;it2!=construction_list.end();++it2)
        {
            mean_vector2+=(*it2)->get_attribute();
        }
        if (number_of_neighbors1!=0)
        {
            mean_vector1/=number_of_neighbors1;
        }
        if (number_of_neighbors2!=0)
        {
            mean_vector2/=number_of_neighbors2;
        }
        vector_made_for_distance_computation1.insert( vector_made_for_distance_computation1.end(), mean_vector1.begin(), mean_vector1.end() );
        vector_made_for_distance_computation2.insert( vector_made_for_distance_computation2.end(), mean_vector2.begin(), mean_vector2.end() );
        return vectors_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
}

template<>
double Vertex<double,int>::get_distance(const VertexPointer<double,int> vertex)const
{
    std::vector<double> vector_made_for_distance_computation1,vector_made_for_distance_computation2;
    vector_made_for_distance_computation1.push_back(m_attribute);
    vector_made_for_distance_computation2.push_back(vertex->get_attribute());
    std::list<EdgePointer<double,int>> construction_list(vertex->get_edges());
    double number_of_neighbors1(m_neighbors.size()),number_of_neighbors2(construction_list.size());
    double mean_vector1=double(0.0),mean_vector2=double(0.0);
    if ((m_edges.empty()) && (construction_list.empty()))
    {
        return euclidean_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
    else
    {
        typename std::list<EdgePointer<double,int>>::const_iterator it1=m_edges.begin();
        typename std::list<EdgePointer<double,int>>::const_iterator it2=construction_list.begin();
        for (;it1!=m_edges.end();++it1)
        {
            mean_vector1+=double((*it1)->get_attribute());
        }
        for (;it2!=construction_list.end();++it2)
        {
            mean_vector2+=double((*it2)->get_attribute());
        }
        if (number_of_neighbors1!=0)
        {
            mean_vector1/=number_of_neighbors1;
        }
        if (number_of_neighbors2!=0)
        {
            mean_vector2/=number_of_neighbors2;
        }
        vector_made_for_distance_computation1.push_back(mean_vector1);
        vector_made_for_distance_computation2.push_back(mean_vector2);
        return vectors_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
}

template<>
double Vertex<int,int>::get_distance(const VertexPointer<int,int> vertex)const
{
    std::vector<double> vector_made_for_distance_computation1,vector_made_for_distance_computation2;
    vector_made_for_distance_computation1.push_back(double(m_attribute));
    vector_made_for_distance_computation2.push_back(double(vertex->get_attribute()));
    std::list<EdgePointer<int,int>> construction_list(vertex->get_edges());
    int number_of_neighbors1(m_neighbors.size()),number_of_neighbors2(construction_list.size());
    double mean_vector1=double(0.0),mean_vector2=double(0.0);
    if ((m_edges.empty()) && (construction_list.empty()))
    {
        return euclidean_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
    else
    {
        typename std::list<EdgePointer<int,int>>::const_iterator it1=m_edges.begin();
        typename std::list<EdgePointer<int,int>>::const_iterator it2=construction_list.begin();
        for (;it1!=m_edges.end();++it1)
        {
            mean_vector1+=double((*it1)->get_attribute());
        }
        for (;it2!=construction_list.end();++it2)
        {
            mean_vector2+=double((*it2)->get_attribute());
        }
        if (number_of_neighbors1!=0)
        {
            mean_vector1/=number_of_neighbors1;
        }
        if (number_of_neighbors2!=0)
        {
            mean_vector2/=number_of_neighbors2;
        }
        vector_made_for_distance_computation1.push_back(mean_vector1);
        vector_made_for_distance_computation2.push_back(mean_vector2);
        return vectors_distance(vector_made_for_distance_computation1,vector_made_for_distance_computation2);
    }
}

//Print the information of a Vertex
//The information printed are in this order:
//Vertex_id, Vertex_attribute
//for each of the linked__edges
//print the edge information
//for each of the neighbors_vertices
//print the id
template<class T,class V>
void Vertex<T,V>::print(std::ostream &flux) const
{
    typename std::list<VertexPointer<T,V>>::const_iterator it=m_neighbors.begin();
    typename T::const_iterator it2=m_attribute.begin();
    flux <<"Vertex_id: "<<m_id<<endl;
    flux <<"Vertex attribute: "<<endl;
    for (;it2!=m_attribute.end();++it2)
    {
        flux << *it2<<"," ;
    }
    flux<<endl;
    typename std::list<EdgePointer<T,V>>::const_iterator it3=m_edges.begin();
    flux <<"edges:"<< endl;
    for (;it3!=m_edges.end();++it3)
    {
        (*it3)->print(flux);
    }
    flux <<"Vertex neighbors: "<<endl;
    for (;it!=m_neighbors.end();++it)
    {
        flux << (*it)->get_id()<<endl;
    }

};


//Specialized print function of a Vertex with double attribute
//The information printed are in this order:
//Vertex_id, Vertex_attribute
//for each of the linked__edges
//print the edge information
//for each of the neighbors_vertices
//print the id
template<>
void Vertex<double,std::pair<int,int>>::print(std::ostream &flux) const
{
    typename std::list<std::shared_ptr<Vertex<double,std::pair<int,int>>>>::const_iterator it=m_neighbors.begin();
    flux <<"Vertex_id: "<<m_id<<endl;
    flux <<"Vertex attribute: "<<m_attribute<<endl;
    typename std::list<std::shared_ptr<Edge<double,std::pair<int,int>>>>::const_iterator it3=m_edges.begin();
    flux <<"edges:"<< endl;
    for (;it3!=m_edges.end();++it3)
    {
        (*it3)->print(flux);
    }
    flux <<"Vertex neighbors: "<<endl;
    for (;it!=m_neighbors.end();++it)
    {
        flux << (*it)->get_id()<<endl;
    }

};

//Return a bool true if the considerated vertex is a neighbor
//the check if a vertex is equal to an other vertex is based on the id of the vertices
template<class T,class V>
bool Vertex<T,V>::is_neighbor(const Vertex<T,V> &vertex) const
{
    typename std::list<VertexPointer<T,V>>::const_iterator it=m_neighbors.begin();
    for (;it!=m_neighbors.end();++it)
    {
        if ((*(*it))==vertex)
        {
            return true;
        }
    }
    return false;
}

//Return a bool true if the considerated vertex is a neighbor
//the check if a vertex is equal to an other vertex is based on the id of the vertices
template<class T,class V>
bool  Vertex<T,V>::is_neighbor(const V vertex_id) const
{
    typename std::list<VertexPointer<T,V>>::const_iterator it=m_neighbors.begin();
    for (;it!=m_neighbors.end();++it)
    {
        if (((*it)->get_id())==vertex_id)
        {
            return true;
        }
    }
    return false;
}


//Operator != for vertices is based on the id of both vertices
template<class T,class V>
bool operator!=(Vertex<T,V> &vertex1,Vertex<T,V> &vertex2)
{
    return ((vertex1.get_id())!=(vertex2.get_id()));
}

//Operator << add the information of the Vertex in the given ostream flux
template<class T,class V>
std::ostream &operator<<( std::ostream &flux, Vertex<T,V> &vertex1)
{
    vertex1.print(flux) ;
    return flux;
};

//Operator << for a list of Vertices
//It print the information of each vertices of the list
template<class T,class V>
std::ostream &operator<<(std::ostream &flux,std::list<VertexPointer<T,V>> vertex_vector)
{
    typename std::list<VertexPointer<T,V>>::const_iterator it=vertex_vector.begin();
    for (;it!=vertex_vector.end();++it)
    {
        flux<<(*(*it))<<endl;
    }
    return flux;
}

#endif // VERTEX_H_INCLUDED
