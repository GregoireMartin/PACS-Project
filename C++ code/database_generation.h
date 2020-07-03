#ifndef DATABASE_GENERATION_H_INCLUDED
#define DATABASE_GENERATION_H_INCLUDED
#include <vector>
#include <map>
#include <iostream>
#include <random>

std::vector<double> edge_calcul(std::map<std::pair<int,int>,std::vector<double>> &map1,int id1,int id2);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_L(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_U(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_C(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_A(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_letter_S(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_drunk_LUCAS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_L(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_U(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_C(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_A(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_S(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_P(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_R(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_E(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_T(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_M(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_N(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_O(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_I(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_letter_V(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOLMENTE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_PRECIPITEVOLISSIMEVOLMENTE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOLISSIME(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_PRECIPITE(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOLIS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_LUCAS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_LIS(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_OL(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);
std::pair<std::map<std::pair<int,int>,std::vector<double>>,int> add_VOL(std::map<std::pair<int,int>,std::vector<double>> &map1,int &start);

#endif // DATABASE_GENERATION_H_INCLUDED
