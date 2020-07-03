#ifndef USEFULFUNCTIONS_H_INCLUDED
#define USEFULFUNCTIONS_H_INCLUDED
#include <math.h>
#include <algorithm>
#include <assert.h>
#include <numeric>

//Operator + to calculate the sum term to term of 2 vectors
template<class S>
std::vector<S>& operator+=(std::vector<S> &vector1,const std::vector<S> &vector2)
{
    if(vector1.size()>=vector2.size())
    {
        for (int k=0;k<int(vector2.size());++k)
        {
            vector1[k]+=vector2[k];
        }
        return vector1;
    }
    else
    {
        for (int k=0;k<int(vector1.size());++k)
        {
            vector1[k]+=vector2[k];
        }
        return vector1;
    }
}


//Operator /= that divide each coordinate of a vector by a same number
template<class S>
std::vector<S>& operator/=(std::vector<S> &vector1,const S &number)
{
    assert(number!=0);
    for (int k=0;k<int(vector1.size());++k)
    {
        vector1[k]/=number;
    }
    return vector1;
}



//Operator << which add the information of a given vector in the ostream flux
template<class S>
std::ostream &operator<<( std::ostream &flux,const std::vector<S> &vector1)
{
    typename std::vector<S>::const_iterator it=vector1.begin();
    flux<<"vector: ";
    for (;it!=vector1.end();++it)
    {
        flux<<(*it)<<",";
    }
    flux<<std::endl;
    return flux;
};


//Operator << for std::pair
template<class V>
std::ostream &operator<<( std::ostream &flux,const std::pair<V,V> &pair1)
{
    flux<<"("<<pair1.first<<","<<pair1.second<<")" ;
    return flux;
};


//Operator < for std::pair
//Order first according the first attribute and then according the second one
template<class V>
bool operator<(const std::pair<V,V> &pair1,const std::pair<V,V> &pair2)
{
    if (pair1.first!=pair2.first)
    {
        return pair1.first<pair2.first;
    }
    else
    {
        return pair1.second<pair2.second;
    }
}

//Calculate the sum of the coordinates of a vector
template<class S>
double vector_sum(std::vector<S> &vector1)
{
    double sum(0.0);
    for (int k=0;k<int(vector1.size());++k)
    {
        sum+=vector1[k];
    }
    return sum;
}

//Calculate the scalar product between two vectors, in our case the vectors will always have the same size
template<class S>
double scalar_product(std::vector<S> const &a,std::vector<S> const &b)
{
    double scalarproduct(0.0);
    int length1(a.size()),length2(b.size());
    for (int k=0;k<std::max(length1,length2);++k)
    {
        if ((k<length1) && (k<length2))
        {
            scalarproduct+=b[k]*a[k];
        }
    }
    return scalarproduct;
}


//Calculate the norm of a vector
template<class S>
double norm_euclidian(std::vector<S>& a)
{
    return sqrt(scalar_product(a,a));
}


//Calculate the euclidian distance between 2 vectors
template<class S>
double euclidean_distance(S &a,S &b)
{
    double valeur = 0.0;
    if (int(a.size())<=int(b.size()))
    {
        for (int i = 0; i < int(a.size()); ++i)
        {
            double op = (b[i] - a[i]);
            valeur += pow(op, 2);
        }
        for (int j=int(a.size()); j<int(b.size()); ++j)
        {
            valeur += pow(double(b[j]), 2);
        }

    }
    else
    {
        for (int i = 0; i < int(b.size()); ++i)
        {
            double op = (b[i] - a[i]);
            valeur += pow(op, 2);
        }
        for (int j=int(b.size()); j<int(a.size()); ++j)
        {
            valeur += pow(double(a[j]), 2);
        }

    }
    return sqrt(valeur);
}

//Euclidian distance for double
template<>
double euclidean_distance<double>(double &a,double &b)
{
    return abs(a-b);
}
//Euclidian distance for int
template<>
double euclidean_distance<int>(int &a,int &b)
{
    return abs(double(a-b));
}

// Computes the distance between two std::vectors
template <typename T>
double	vectors_distance(const std::vector<T>& a, const std::vector<T>& b)
{
	std::vector<double>	auxiliary;

	std::transform (a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),[](T element1, T element2) {return pow((element1-element2),2);});

	return  sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
}


double min_between(int element1,int element2)
{
    if (element1>element2)
    {
        return element2;
    }
    return element1;
}



#endif // USEFULFUNCTIONS_H_INCLUDED
