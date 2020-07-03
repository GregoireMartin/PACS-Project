#ifndef BK_MATCHER_H_INCLUDED
#define BK_MATCHER_H_INCLUDED
#include "Set_of_graph.h"

//The following function determine the optimal matching for a vertex of the first graph
//In this function the distance between a vertex u of the first graph and a vertex v of the second is defined as follows :
//u.get_distance(v) where get_distance is the function of the class Vertex
//the function return an std::pair containing the optimal (u,v) match in term of id and the distance between the 2 vertices
template<class T,class V>
std::pair<std::pair<int,int>,double> elementary_matching(VertexPointer<T,V> vertex1,GraphPointer<T,V> graph2)
{
    typename std::map<std::pair<int,int>,double> productgraph_constructor;
    typename std::list<VertexPointer<T,V>> vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it3=vertices_graph2.begin();
    for (;it3!=vertices_graph2.end();++it3)
    {
        productgraph_constructor[std::pair<int,int>({vertex1->get_id(),(*it3)->get_id()})]=vertex1->get_distance((*it3));;
    }
    double minimum(productgraph_constructor.begin()->second);
    std::pair<int,int> match(productgraph_constructor.begin()->first);
    typename std::map<std::pair<int,int>,double>::iterator it=productgraph_constructor.begin();
    for (;it!=productgraph_constructor.end();++it)
    {
        if (it->second<minimum)
        {
            match=it->first;
            minimum=it->second;
        }
    }
    return std::pair<std::pair<int,int>,double>({match,minimum});
}

//The following functions are creating a product_graph of two graphs with the same orientation (you are not supposed to match a directed graph with an undirected one)
//A product_graph of 2 graphs G1 and G2 is defined as a new graph where each vertices (u,v) of the product_graph is made of u in G1 and v in G2
//An edge between (u1,v1) and (u2,v2) exists if and only if the application f(u)=v is injective
//In this function the attribute of a Vertex (u,v) of the product_graph is defined as u.get_distance(v) where get_distance is the function of the class Vertex
//The attribute of an Edge is 0.0
//The aim of this function is to determine after the minimum weighted clique by applying the BronKerbosch_minimal_clique algorithm
template<class T,class V>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph(GraphPointer<T,V> graph1,GraphPointer<T,V> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<T,V>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<T,V>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<T,V>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<T,V>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=(*it3)->get_distance((*it4));
            construction_graph1[(*it3)->get_id()]=*it3;
            construction_graph2[(*it4)->get_id()]=*it4;
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double(0.0);
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }
    return productgraph_constructor;
}


//The following function is creating a product_graph of two graphs
//A product_graph of 2 graphs G1 and G2 is defined as a new graph where each vertices (u,v) of the product_graph is made of u in G1 and v in G2
//An edge between (u1,v1) and (u2,v2) exists if and only if the application f(u)=v is injective
//In this function the attribute of a Vertex (u,v) of the product_graph is defined as u.get_distance(v) where get_distance is the function of the class Vertex
//The attribute of an Edge ((u1,v1),(u2,v2)) is equal to the euclidian distance between the edges attribute of (u1,u2) and (v1,v2).
//If only one of the 2 edges exists it is defined as the norm of the attribute of this edge, if none of these edges exist then it is 0
//The aim of this function is to determine after the minimum weighted clique by applying the BronKerbosch_minimal_clique algorithm
template<class T,class V>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_improvement(GraphPointer<T,V> graph1,GraphPointer<T,V> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<T,V>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<T,V>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<T,V>>::iterator it4=vertices_graph2.begin();
    typename std::map<V,VertexPointer<T,V>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=(*it3)->get_distance((*it4));
            construction_graph1[(*it3)->get_id()]=(*it3);
            construction_graph2[(*it4)->get_id()]=(*it4);
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=vectors_distance(construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]),construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    T vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=norm_euclidian(vector1);
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    T vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=norm_euclidian(vector1);
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=0.0;
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }
    return productgraph_constructor;
}

//Specialization of the function in the case of double attribute for edges/vertices
template<>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_improvement<double,int>(GraphPointer<double,int> graph1,GraphPointer<double,int> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<double,int>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<double,int>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<double,int>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<double,int>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<double,int>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=(*it3)->get_distance((*it4));
            construction_graph1[(*it3)->get_id()]=(*it3);
            construction_graph2[(*it4)->get_id()]=(*it4);
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]))-double(construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second])),2));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    double vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    double vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double(0.0);
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }
    return productgraph_constructor;
}

//Specialization of the function in the case of integer attribute for edges/vertices
template<>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_improvement<int,int>(GraphPointer<int,int> graph1,GraphPointer<int,int> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<int,int>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<int,int>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<int,int>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<int,int>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<int,int>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=(*it3)->get_distance((*it4));
            construction_graph1[(*it3)->get_id()]=(*it3);
            construction_graph2[(*it4)->get_id()]=(*it4);
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]))-double(construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second])),2));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    int vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    int vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double(0.0);
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }
    return productgraph_constructor;
}

//The following function is creating a product_graph of two graphs
//A product_graph of 2 graphs G1 and G2 is defined as a new graph where each vertices (u,v) of the product_graph is made of u in G1 and v in G2
//An edge between (u1,v1) and (u2,v2) exists if and only if the application f(u)=v is injective
//In this function the attribute of a Vertex (u,v) of the product_graph is defined as u.get_distance(v) where get_distance is the function of the class Vertex
//The attribute of an Edge ((u1,v1),(u2,v2)) is equal to the sum of both vertex (u1,v1) and (u2,v2), this sum is divided by 10 if (u1,u2) and (v1,v2) are both edges or not edges
//The aim of this function is to determine after the minimum weighted clique by applying the BronKerbosch_minimal_clique algorithm

template<class T,class V>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_new_improvement(GraphPointer<T,V> graph1,GraphPointer<T,V> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<T,V>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<T,V>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<T,V>>::iterator it4=vertices_graph2.begin();
    typename std::map<V,VertexPointer<T,V>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=(*it3)->get_distance((*it4));
            construction_graph1[(*it3)->get_id()]=(*it3);
            construction_graph2[(*it4)->get_id()]=(*it4);
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double(((it1->second)+(it2->second))/3);
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double((it1->second)+(it2->second));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double((it1->second)+(it2->second));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double(((it1->second)+(it2->second))/3);;
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }
    return productgraph_constructor;
}

//The following function is creating a product_graph of two graphs
//A product_graph of 2 graphs G1 and G2 is defined as a new graph where each vertices (u,v) of the product_graph is made of u in G1 and v in G2
//An edge between (u1,v1) and (u2,v2) exists if and only if the application f(u)=v is injective
//In this function the attribute of a Vertex (u,v) of the product_graph is defined as the scalar product between the attribute of u and v
//The attribute of an edge ((u1,v1),(u2,v2)) is defined as the scalar product between the attribute of the edges (u1,u2) and (v1,v2)
//If one of these edges doesn't exist then it is just equal to minus the norm of one edge, if none of them exist then its 0
//The aim of this function is to determine after the maximal weighted clique by applying the BronKerbosch_maximal_clique algorithm
template<class T,class V>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_kernelversion(GraphPointer<T,V> graph1,GraphPointer<T,V> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<T,V>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<T,V>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<T,V>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<T,V>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=scalar_product((*it3)->get_attribute(),(*it4)->get_attribute());
            construction_graph1[(*it3)->get_id()]=*it3;
            construction_graph2[(*it4)->get_id()]=*it4;
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=scalar_product(construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]),construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    T vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-norm_euclidian(vector1);
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    T vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-norm_euclidian(vector1);
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=0.0;
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }

    return productgraph_constructor;
}


template<>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_kernelversion<double,int>(GraphPointer<double,int> graph1,GraphPointer<double,int> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<double,int>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<double,int>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<double,int>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<double,int>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<double,int>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=((*it3)->get_attribute())*((*it4)->get_attribute());
            construction_graph1[(*it3)->get_id()]=*it3;
            construction_graph2[(*it4)->get_id()]=*it4;
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=(construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]))*(construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    double vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-sqrt(pow(vector1,2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    double vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-sqrt(pow(vector1,2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=0.0;
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }

    return productgraph_constructor;
}


template<>
std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> get_productgraph_kernelversion<int,int>(GraphPointer<int,int> graph1,GraphPointer<int,int> graph2)
{
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> productgraph_constructor;
    typename std::list<VertexPointer<int,int>>  vertices_graph1=graph1->get_vertices();
    typename std::list<VertexPointer<int,int>>  vertices_graph2=graph2->get_vertices();
    typename std::list<VertexPointer<int,int>>::iterator it3=vertices_graph1.begin();
    typename std::list<VertexPointer<int,int>>::iterator it4=vertices_graph2.begin();
    typename std::map<int,VertexPointer<int,int>> construction_graph1,construction_graph2;
    for (;it3!=vertices_graph1.end();++it3)
    {
        it4=vertices_graph2.begin();
        for (;it4!=vertices_graph2.end();++it4)
        {
            productgraph_constructor[std::pair<std::pair<int,int>,std::pair<int,int>>({{(*it3)->get_id(),(*it4)->get_id()},{(*it3)->get_id(),(*it4)->get_id()}})]=((*it3)->get_attribute())*((*it4)->get_attribute());
            construction_graph1[(*it3)->get_id()]=*it3;
            construction_graph2[(*it4)->get_id()]=*it4;
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it1=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double>::iterator it2=productgraph_constructor.begin();
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>> productgraph_constructor2;
    for(;it1!=productgraph_constructor.end();++it1)
    {
        it2=productgraph_constructor.begin();
        for(;it2!=productgraph_constructor.end();++it2)
        {
            if ((*construction_graph1[it1->first.first.first]!=*construction_graph1[it2->first.first.first]) && (*construction_graph2[it1->first.first.second]!=*construction_graph2[it2->first.first.second]))
            {
                if  ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=double((construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]))*(construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second])));
                }

                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==true) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    int vector1=construction_graph1[it1->first.first.first]->get_edge_attribute(construction_graph1[it2->first.first.first]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==true))
                {
                    int vector1=construction_graph2[it1->first.first.second]->get_edge_attribute(construction_graph2[it2->first.first.second]);
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=-sqrt(pow(double(vector1),2));
                }
                if ((construction_graph1[it1->first.first.first]->is_neighbor(it2->first.first.first)==false) && (construction_graph2[it1->first.first.second]->is_neighbor(it2->first.first.second)==false))
                {
                    productgraph_constructor2[std::pair<std::pair<int,int>,std::pair<int,int>>({it1->first.first,it2->first.first})]=0.0;
                }
            }
        }
    }
    typename std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double,unoriented_map<std::pair<int,int>>>::iterator it=productgraph_constructor2.begin();
    for(;it!=productgraph_constructor2.end();++it)
    {
        productgraph_constructor[it->first]=it->second;
    }

    return productgraph_constructor;
}

//The following functions are used for the BronKerbosch algorithm
//This function give the intersection of 2 std::list
template<typename T>
std::list<T> intersect(const std::list<T> A, const std::list<T> B)
{
    std::list<T> out;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),std::back_inserter(out));
    return out;
}


//Erase all the element b of a list A and return A
template<class V>
std::list<V> suppr(std::list<V> A, V b)
{
    typename std::list<V>::iterator it=A.begin();
    for(;it!=A.end();)
    {
        if((*it)==b)
        {
            it=A.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return A;
}

//Return a vector of neighbors_id of a given vertex described by his id according a distance_matrix
//This function is used in the case of an undirected graph only because the BronKerbosch algorithm is only applied to the product graph
//which is unoriented
template<class V,class T>
std::list<V> get_neighbor(V vertex,std::map<std::pair<V,V>,T> &distance_matrix)
{
    std::list<V> neighbor;
    std::map<V,int> neighbor_map;
    typename std::map<std::pair<V,V>,T>::iterator it=distance_matrix.begin();
    for (;it!=distance_matrix.end();++it)
    {
        if (((distance_matrix.find(std::pair<V,V>({vertex,it->first.first}))!=distance_matrix.end()) || (distance_matrix.find(std::pair<V,V>({it->first.first,vertex}))!=distance_matrix.end())) && (vertex!=(it->first.first)))
        {
            neighbor_map[it->first.first]=1;
        }
    }
    typename std::map<V,int>::iterator it2=neighbor_map.begin();
    for (;it2!=neighbor_map.end();++it2)
    {
        neighbor.push_back(it2->first);
    }
    return neighbor;
}

//BronKerbosch algorithm in the case of the search of the minimum weighted clique
//The function is calling recursively it self by uploading the following variables:
//R which is the current clique described by a vector of vertices_id
//R weight which is the current weight of the considered clique, this weight is calculated as the sum of the weight of the vertices and the edges in the clique
//P which is a vector of vertices id describing the remaining possible candidates for the clique
//X which is a vector of vertices id made to avoid to report multiple times the same minimum weighted clique
//distance_matrix is the product_graph on which we want to find the minimal clique
//minimal_weight is the current best weight found by our algorithm
//minimal_weighted_clique is the current best minimal clique found by our algorithm
//A branch and bound strategy is used in the case of the minimum_weighted_clique to improve the performance
//We cut the branch that correspond to the possible cliques that we know are above our current upper_bound
template<class V,class T>
void BronKerboschWithoutPivot_minimum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &minimal_weight,std::list<V> &minimal_weighted_clique)
{
    if (R_weight>=minimal_weight)
    {
        return;
    }
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight<minimal_weight)
            {
                std::cout<<"Minimal weighted clique founded with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                minimal_weight=R_weight;
                minimal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    it=P.begin();
    for(;it!=P.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithoutPivot_minimum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,minimal_weight,minimal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//Selecting the best pivot for the BronKerbosch with pivot algorithm:

//Here the strategy is to take the pivot with the more neighbors in PUX where P and X are defined like in the BronKerbosch algorithm
//Return the id of the best candidate
template<class T,class V>
V select_pivot(std::list<V> &union_P_and_X,std::map<std::pair<V,V>,T> &distance_matrix)
{
    std::vector<int> numbers_of_neighbors(union_P_and_X.size(),0);
    V candidate((*union_P_and_X.begin()));
    int maximum(0);
    typename std::list<V>::iterator it=union_P_and_X.begin();
    for (;it!=union_P_and_X.end();++it)
    {
        if (int(get_neighbor((*it),distance_matrix).size())>maximum)
        {
            maximum=get_neighbor((*it),distance_matrix).size();
            candidate=(*it);
        }
    }
    return candidate;
}

//Here the strategy is to take a random pivot with in PUX where P and X are defined like in the BronKerbosch algorithm
//Return the id of the chosen_vertex
template<class V>
V select_pivot_random(std::list<V> &union_P_and_X)
{
    srand(time(NULL)); // initialization of rand
    int sizelist(int(union_P_and_X.size())),counter(0);
    int chosen_index=rand()%sizelist;
    typename std::list<V>::iterator it=union_P_and_X.begin();
    for (;(it!=union_P_and_X.end()) && (counter!=chosen_index);++it)
    {
        counter+=1;
    }
    return (*it);
}


//BronKerbosch algorithm in the case of the search of the minimum weighted clique
//The function is calling recursively it self by uploading the following variables:
//R which is the current clique described by a list of vertices_id
//R weight which is the current weight of the considered clique, this weight is calculated as the sum of the weight of the vertices and the edges in the clique
//P which is a list of vertices id describing the remaining possible candidates for the clique
//X which is a list of vertices id made to avoid to report multiple times the same minimum weighted clique
//distance_matrix is the product_graph on which we want to find the minimal clique
//minimal_weight is the current best weight found by our algorithm
//minimal_weighted_clique is the current best minimal clique found by our algorithm
//A pivot is calculated at each call to optimize the search part of the algorithm
//A branch and bound strategy is used in the case of the minimum_weighted_clique to improve the performance
//We cut the branch that correspond to the possible cliques that we know are above our current upper_bound
template<class V,class T>
void BronKerboschWithPivot_firststrategy_minimum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &minimal_weight,std::list<V> &minimal_weighted_clique)
{
    if (R_weight>=minimal_weight)
    {
        return;
    }
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight<minimal_weight)
            {
                std::cout<<"Minimal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                minimal_weight=R_weight;
                minimal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot(union_P_and_X,distance_matrix);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_firststrategy_minimum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,minimal_weight,minimal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}


template<class V,class T>
void BronKerboschWithPivot_secondstrategy_minimum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &minimal_weight,std::list<V> &minimal_weighted_clique)
{
    if (R_weight>=minimal_weight)
    {
        return;
    }
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight<minimal_weight)
            {
                std::cout<<"Minimal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                minimal_weight=R_weight;
                minimal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot_random(union_P_and_X);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_secondstrategy_minimum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,minimal_weight,minimal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//Version of BK with Pivot with an early stopping criteria if you find more than a certain number of non_improving clique
template<class V,class T>
void BronKerboschWithPivot_thirdstrategy_minimum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &minimal_weight,std::list<V> &minimal_weighted_clique,int &non_improving_clique,int stopping_criteria)
{
    if (non_improving_clique>stopping_criteria)
    {
        return;
    }
    if (R_weight>=minimal_weight)
    {
        non_improving_clique+=1;
        return;
    }
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight<minimal_weight)
            {
                std::cout<<"Minimal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                minimal_weight=R_weight;
                minimal_weighted_clique=R;
                non_improving_clique=0;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot(union_P_and_X,distance_matrix);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_thirdstrategy_minimum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,minimal_weight,minimal_weighted_clique,non_improving_clique,stopping_criteria);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//Version of BK with Pivot with an early stopping criteria if you find more than a certain number of non_improving clique
template<class V,class T>
void BronKerboschWithPivot_thirdstrategy_with_random_minimum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &minimal_weight,std::list<V> &minimal_weighted_clique,int &non_improving_clique,int stopping_criteria)
{
    if (non_improving_clique>stopping_criteria)
    {
        return;
    }
    if (R_weight>=minimal_weight)
    {
        non_improving_clique+=1;
        return;
    }
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight<minimal_weight)
            {
                std::cout<<"Minimal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                minimal_weight=R_weight;
                minimal_weighted_clique=R;
                non_improving_clique=0;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot_random(union_P_and_X);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_thirdstrategy_minimum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,minimal_weight,minimal_weighted_clique,non_improving_clique,stopping_criteria);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//BronKerbosch algorithm in the case of the search of the maximum weighted clique
//The function is calling recursively it self by uploading the following variables:
//R which is the current clique described by a list of vertices_id
//R weight which is the current weight of the considered clique, this weight is calculated as the sum of the weight of the vertices and the edges in the clique
//P which is a list of vertices id describing the remaining possible candidates for the clique
//X which is a list of vertices id made to avoid to report multiple times the same maximum weighted clique
//distance_matrix is the product_graph on which we want to find the maximum clique
//maximum_weight is the current best weight found by our algorithm
//maximum_weighted_clique is the current best maximum clique found by our algorithm
template<class V,class T>
void BronKerboschWithoutPivot_maximum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &maximal_weight,std::list<V> &maximal_weighted_clique)
{
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight>maximal_weight)
            {
                std::cout<<"Maximal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                maximal_weight=R_weight;
                maximal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    it=P.begin();
    for(;it!=P.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithoutPivot_maximum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,maximal_weight,maximal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//BronKerbosch algorithm in the case of the search of the maximum weighted clique
//The function is calling recursively it self by uploading the following variables:
//R which is the current clique described by a list of vertices_id
//R weight which is the current weight of the considered clique, this weight is calculated as the sum of the weight of the vertices and the edges in the clique
//P which is a list of vertices id describing the remaining possible candidates for the clique
//X which is a list of vertices id made to avoid to report multiple times the same maximum weighted clique
//distance_matrix is the product_graph on which we want to find the maximum clique
//maximum_weight is the current best weight found by our algorithm
//maximum_weighted_clique is the current best maximum clique found by our algorithm
//at each iteration a pivot is calculated to optimize the search of the algorithm
template<class V,class T>
void BronKerboschWithPivot_firststrategy_maximum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &maximal_weight,std::list<V> &maximal_weighted_clique)
{
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight>maximal_weight)
            {
                std::cout<<"Maximal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                maximal_weight=R_weight;
                maximal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot(union_P_and_X,distance_matrix);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_firststrategy_maximum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,maximal_weight,maximal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

template<class V,class T>
void BronKerboschWithPivot_secondstrategy_maximum_clique(std::list<V> R,double R_weight, std::list<V> P, std::list<V> X ,std::map<std::pair<V,V>,T> &distance_matrix,double &maximal_weight,std::list<V> &maximal_weighted_clique)
{
    if((P.size() == 0) && (X.size() == 0) && (R.size()>=1))
        {
            if (R_weight>maximal_weight)
            {
                std::cout<<"Maximal weighted clique found with weight: "<<R_weight<<endl;
                std::cout<<"Clique Vertices: "<<endl;
                typename std::list<V>::iterator it=R.begin();
                for (; it!=R.end(); ++it){ std::cout<<(*it)<<","; }
                std::cout<<endl;
                maximal_weight=R_weight;
                maximal_weighted_clique=R;
            }
        return;
        }
    std::list<V> P1;
    typename std::list<V>::iterator it=P.begin();
    for (;it!=P.end(); ++it){ P1.push_back((*it));}
    std::list<V> union_P_and_X=P;
    it=X.begin();
    for (;it!=X.end(); ++it){ union_P_and_X.push_back((*it));}
    V pivot=select_pivot_random(union_P_and_X);
    std::list<V> P_minus_pivot_neighborhood=P;
    std::list<V> pivot_neighborhood = get_neighbor(pivot,distance_matrix);
    it=pivot_neighborhood.begin();
    for (;it!=pivot_neighborhood.end(); ++it){ P_minus_pivot_neighborhood=suppr(P_minus_pivot_neighborhood,(*it));}
    it=P_minus_pivot_neighborhood.begin();
    for (;it!=P_minus_pivot_neighborhood.end(); ++it)
    {
        V vertex = (*it);
        std::list<V> neighborhood = get_neighbor(vertex,distance_matrix);
        double ndist=distance_matrix[std::pair<V,V>({vertex,vertex})];
        typename std::list<V>::iterator it2=R.begin();
        for (;it2!=R.end(); ++it2)
        {
            ndist+=std::max(distance_matrix[std::pair<V,V>({(*it2),vertex})],distance_matrix[std::pair<V,V>({vertex,(*it2)})]);
        }
        R.push_back(vertex);
        BronKerboschWithPivot_secondstrategy_maximum_clique(R,R_weight+ndist,intersect(P1,neighborhood),intersect(X,neighborhood),distance_matrix,maximal_weight,maximal_weighted_clique);
        R = suppr(R,vertex);
        P1 = suppr(P1,vertex);
        X.push_back(vertex);
    }
}

//BK Matcher
//All the matcher return an std::pair where the first element is a list of std::pair<int,int> corresponding to optimal permutation and the second element is a double corresponding to the minimum weight

//This version is a precise version of the BK matcher using a random_pivot strategy
//You need to specify the position of the 2 graphs in the set of graph and an initial_minimum_weight which only need to be larger than the weight of the smallest possible clique
//If you have an idea of the minimum weighted clique weight you are looking for take this parameter just a bit bigger than it
//Otherwise set this parameter equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*largest_weight_of_the_product_graph
//Or just give a value too big compare to the value of your problem
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> BK_matcher_precise_random_pivot(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph,double initial_minimum_weight)
{
    Graph<double,std::pair<int,int>> graphproduct(get_productgraph_improvement(first_graph,second_graph),false);
    std::list<std::pair<int,int>> R;
    double R_weight(0.0);
    std::list<std::pair<int,int>> P=graphproduct.get_vertices_id();
    std::list<std::pair<int,int>> X;
    std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> distance_matrix1=graphproduct.get_m_graph();
    double minimal_weight(initial_minimum_weight);
    std::list<std::pair<int,int>> minimal_weighted_clique;
    std::list<Vertex<std::vector<double>,std::pair<int,int>> *> best_current_clique;
    BronKerboschWithPivot_secondstrategy_minimum_clique(R,R_weight,P,X,distance_matrix1,minimal_weight,minimal_weighted_clique);
    return std::pair<std::list<std::pair<int,int>>,double>({minimal_weighted_clique,minimal_weight});
}

//This version is a precise version of the BK matcher using a selected_pivot strategy
//You need to specify the position of the 2 graphs in the set of graph and an initial_minimum_weight which only need to be larger than the weight of the smallest possible clique
//If you have an idea of the minimum weighted clique weight you are looking for take this parameter just a bit bigger than it
//Otherwise take this parameter equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*largest_weight_of_the_product_graph
//Or just give a value too big compare to the value of your problem
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> BK_matcher_precise_chosen_pivot(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph,double initial_minimum_weight)
{
    Graph<double,std::pair<int,int>> graphproduct(get_productgraph_improvement(first_graph,second_graph),false);
    std::list<std::pair<int,int>> R;
    double R_weight(0.0);
    std::list<std::pair<int,int>> P=graphproduct.get_vertices_id();
    std::list<std::pair<int,int>> X;
    std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> distance_matrix1=graphproduct.get_m_graph();
    double minimal_weight(initial_minimum_weight);
    std::list<std::pair<int,int>> minimal_weighted_clique;
    std::list<Vertex<std::vector<double>,std::pair<int,int>> *> best_current_clique;
    BronKerboschWithPivot_firststrategy_minimum_clique(R,R_weight,P,X,distance_matrix1,minimal_weight,minimal_weighted_clique);
    return std::pair<std::list<std::pair<int,int>>,double>({minimal_weighted_clique,minimal_weight});
}

//This version is a fast version of the BK matcher using a selected_pivot strategy
//You need to specify the position of the 2 graphs in the set of graph,an initial_minimum_weight which only need to be larger than the weight of the smallest possible clique
//and a stopping criteria which is the maximum number of non_improving_clique you found before stopping the algorithm (early stopping criteria)
//A smart choice of initial_minimum_weight and stopping-criteria can greatly improve the efficiency of this algorithm
//If you have no idea how to chose them then:
//Take the initial_minimum_weight parameter equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*largest_weight_of_the_product_graph
//Or just give a value too big compare to the value of your problem
//Take the stopping_criteria equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*10
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> BK_matcher_fast_improvement1_pivot(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph,double initial_minimum_weight,int stopping_criteria)
{
    Graph<double,std::pair<int,int>> graphproduct(get_productgraph_improvement(first_graph,second_graph),bool(false));
    std::list<std::pair<int,int>> R;
    double R_weight(0.0);
    std::list<std::pair<int,int>> P=graphproduct.get_vertices_id();
    std::list<std::pair<int,int>> X;
    std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> distance_matrix1=graphproduct.get_m_graph();
    double minimal_weight(initial_minimum_weight);
    std::list<std::pair<int,int>> minimal_weighted_clique;
    std::list<Vertex<std::vector<double>,std::pair<int,int>> *> best_current_clique;
    int non_improving_clique(0);
    BronKerboschWithPivot_thirdstrategy_minimum_clique(R,R_weight,P,X,distance_matrix1,minimal_weight,minimal_weighted_clique,non_improving_clique,stopping_criteria);
    return std::pair<std::list<std::pair<int,int>>,double>({minimal_weighted_clique,minimal_weight});
}

//This version is a fast version of the BK matcher using a selected_pivot strategy
//You need to specify the position of the 2 graphs in the set of graph,an initial_minimum_weight which only need to be larger than the weight of the smallest possible clique
//and a stopping criteria which is the maximum number of non_improving_clique you found before stopping the algorithm (early stopping criteria)
//A smart choice of initial_minimum_weight and stopping-criteria can greatly improve the efficiency of this algorithm
//If you have no idea how to chose them then:
//Take the initial_minimum_weight parameter equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*largest_weight_of_the_product_graph
//Or just give a value too big compare to the value of your problem
//Take the stopping_criteria equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*10
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> BK_matcher_fast_improvement2_pivot(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph,double initial_minimum_weight,int stopping_criteria)
{
    Graph<double,std::pair<int,int>> graphproduct(get_productgraph_new_improvement(first_graph,second_graph),false);
    std::list<std::pair<int,int>> R;
    double R_weight(0.0);
    std::list<std::pair<int,int>> P=graphproduct.get_vertices_id();
    std::list<std::pair<int,int>> X;
    std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> distance_matrix1=graphproduct.get_m_graph();
    double minimal_weight(initial_minimum_weight);
    std::list<std::pair<int,int>> minimal_weighted_clique;
    std::list<Vertex<std::vector<double>,std::pair<int,int>> *> best_current_clique;
    int non_improving_clique(0);
    BronKerboschWithPivot_thirdstrategy_minimum_clique(R,R_weight,P,X,distance_matrix1,minimal_weight,minimal_weighted_clique,non_improving_clique,stopping_criteria);
    return std::pair<std::list<std::pair<int,int>>,double>({minimal_weighted_clique,minimal_weight});
}

//This version is a fast version of the BK matcher using a selected_pivot strategy
//You need to specify the position of the 2 graphs in the set of graph,an initial_minimum_weight which only need to be larger than the weight of the smallest possible clique
//and a stopping criteria which is the maximum number of non_improving_clique you found before stopping the algorithm (early stopping criteria)
//A smart choice of initial_minimum_weight and stopping-criteria can greatly improve the efficiency of this algorithm
//If you have no idea how to chose them then:
//Take the initial_minimum_weight parameter equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*largest_weight_of_the_product_graph
//Or just give a value too big compare to the value of your problem
//Take the stopping_criteria equal to: number_of_vertices_of_graph1*number_of_vertices_of_graph2*10
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> BK_matcher_fast_improvement2_randompivot(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph,double initial_minimum_weight,int stopping_criteria)
{
    Graph<double,std::pair<int,int>> graphproduct(get_productgraph_new_improvement(first_graph,second_graph),false);
    std::list<std::pair<int,int>> R;
    double R_weight(0.0);
    std::list<std::pair<int,int>> P=graphproduct.get_vertices_id();
    std::list<std::pair<int,int>> X;
    std::map<std::pair<std::pair<int,int>,std::pair<int,int>>,double> distance_matrix1=graphproduct.get_m_graph();
    double minimal_weight(initial_minimum_weight);
    std::list<std::pair<int,int>> minimal_weighted_clique;
    std::list<Vertex<std::vector<double>,std::pair<int,int>> *> best_current_clique;
    int non_improving_clique(0);
    BronKerboschWithPivot_thirdstrategy_with_random_minimum_clique(R,R_weight,P,X,distance_matrix1,minimal_weight,minimal_weighted_clique,non_improving_clique,stopping_criteria);
    return std::pair<std::list<std::pair<int,int>>,double>({minimal_weighted_clique,minimal_weight});
}

//In order to be able to treat the case of a productgraph with around 1000 vertices I have created an heuristic matcher which is less accurate than the BK matcher
//But it proceeds much more quicker.
//Please put the smaller graph on first position and the bigger one on second.
//The principle of this matcher is a greedy approach of the construction of the optimal matching
//I construct step by step the best matching for each vertex of the first graph
//Each time an optimal matching is found for a vertex of the first graph I erase the corresponding matching vertex of the second graph in order to make a feasible solution
template<class T,class V>
std::pair<std::list<std::pair<int,int>>,double> matcher_huge_graph_version(GraphPointer<T,V> first_graph,GraphPointer<T,V> second_graph)
{
    typename std::list<VertexPointer<T,V>>  vertices_graph1=first_graph->get_vertices();
    typename std::list<VertexPointer<T,V>>::iterator it=vertices_graph1.begin();
    std::list<std::pair<int,int>> Result_final_matching;
    std::pair<std::pair<int,int>,double> resultmatching;
    double final_distance(0.0);
    for (;(it!=vertices_graph1.end()) && (second_graph->isempty()!=true);++it)
    {
        resultmatching=elementary_matching((*it),second_graph);
        Result_final_matching.push_back(resultmatching.first);
        final_distance+=resultmatching.second;
        second_graph->delete_vertex(int(resultmatching.first.second));
    }
    return std::pair<std::list<std::pair<int,int>>,double>({Result_final_matching,final_distance});
}


#endif // BK_MATCHER_H_INCLUDED
