#include "database_generation.h"

/*
File generating the word database, the available letters are L,U,C,A,S,P,R,E,I,P,T,V,O,M and N.
A "drunk" version of the letters wanting to be more faithful to the random way of writing the letters has been created for the letters L,U,C,A and S.
The edge_calculation function is used in the case of the drunk versions to calculate the distance between 2 vertices of a letter.
There are also word creation functions such as LUCAS, VOLISSIME, VOLMENTE or PRECIPITE.
To write a word from a letter don't forget to link the letters together by adding an edge of the value (0.0,0.0).
Words and letters are non-oriented graphs.
*/

std::vector<double> edge_calcul(std::map<std::pair<int,int>,std::vector<double>> &map1,int id1,int id2)
{
    std::vector<double> result;
    result.push_back(sqrt(pow(map1[std::pair<int,int>(id1,id1)][0]-map1[std::pair<int,int>(id2,id2)][0],2)));
    result.push_back(sqrt(pow(map1[std::pair<int,int>(id1,id1)][1]-map1[std::pair<int,int>(id2,id2)][1],2)));
    return result;
}
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_L(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,0.2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),2.0+distribution(generator)});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_L(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_U(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_U(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,0.2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),2.0+distribution(generator)});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),2.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_C(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_C(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,0.2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),2.0+distribution(generator)});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),2.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_A(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.5,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start-1,start+1})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start+1,start-1})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.5,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.5,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_A(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,0.2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),0.0+distribution(generator)});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.5+distribution(generator),1.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0+distribution(generator),2.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.5+distribution(generator),1.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    map1[std::pair<int,int>({start,start-2})]=edge_calcul(map1,start,start-2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_S(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_S(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,0.2);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),2.0+distribution(generator)});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),2.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),1.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),1.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0+distribution(generator),0.0+distribution(generator)});
    map1[std::pair<int,int>({start-1,start})]=edge_calcul(map1,start-1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_P(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start+3,start})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start+3})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,1.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_O(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    map1[std::pair<int,int>({start+3,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start+3})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_I(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,2.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_V(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_R(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start+3,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start+3})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start+4,start})]=std::vector<double>({2.0,1.0});
    map1[std::pair<int,int>({start,start+4})]=std::vector<double>({2.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_E(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start+3,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start+3})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,1.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,1.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,1.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_T(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start+2,start})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start+2})]=std::vector<double>({1.0,0.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_M(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({1.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({1.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_N(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    start+=1;
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({0.0,2.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({2.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({2.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,0.0});
    start+=1;
    map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,2.0});
    map1[std::pair<int,int>({start,start})]=std::vector<double>({2.0,2.0});
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_PRECIPITEVOLISSIMEVOLMENTE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_PRECIPITE(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_VOLISSIME(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_VOLMENTE(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOLMENTE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_V(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_O(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_L(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_M(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_N(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_T(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_PRECIPITE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_P(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_R(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_C(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_I(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_P(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_I(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_T(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOLISSIME(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_V(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_O(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_L(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_I(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_S(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_S(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_I(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_M(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_E(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}


std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_LUCAS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_L(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_U(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_C(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_A(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_S(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_LUCAS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_drunk_letter_L(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_drunk_letter_U(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_drunk_letter_C(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_drunk_letter_A(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_drunk_letter_S(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_LIS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_L(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_I(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_S(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_OL(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_O(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_L(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOL(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start)
{
    if (start!=-1)
    {
        map1[std::pair<int,int>({start-1,start})]=std::vector<double>({0.0,0.0});
        map1[std::pair<int,int>({start,start-1})]=std::vector<double>({0.0,0.0});
    }
    add_letter_V(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_O(map1,start);
    map1[std::pair<int,int>({start+1,start})]=std::vector<double>({0.0,0.0});
    map1[std::pair<int,int>({start,start+1})]=std::vector<double>({0.0,0.0});
    add_letter_L(map1,start);
    return std::pair<std::map<std::pair<int,int>,std::vector<double>>,int>({map1,start});
}

