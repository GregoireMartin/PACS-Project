#include <chrono>
#include "database_generation.h"
#include "BK_matcher.h"
typedef std::map<std::pair<int,int>,double> Mymap1;
typedef std::map<std::pair<int,int>,std::vector<int>> Mymap2;
typedef std::map<std::pair<int,int>,std::vector<double>> Mymap3;
int main()
{
    std::cout<<"The following example try to find the optimal matching between 2 simple oriented graph"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot"<<endl;
    std::cout<<"the objective of this instance is to check if the matcher can make the difference between oriented and unoriented graph"<<endl;
    {
        //Define the graphs
        Mymap1 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=double(1);
        dico1[std::pair<int,int>(1,1)]=double(1);
        dico1[std::pair<int,int>(2,2)]=double(1);
        dico1[std::pair<int,int>(0,1)]=double(-1);
        dico1[std::pair<int,int>(1,2)]=double(-1);
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=double(1);
        dico2[std::pair<int,int>(1,1)]=double(1);
        dico2[std::pair<int,int>(0,0)]=double(1);
        dico2[std::pair<int,int>(2,1)]=double(-1);
        dico2[std::pair<int,int>(1,0)]=double(-1);
        bool oriented(true);
        //create the 2 graphs
        std::shared_ptr<Graph<double,int>> pointer1(new Graph<double,int>(dico1,oriented));
        std::shared_ptr<Graph<double,int>> pointer2(new Graph<double,int>(dico2,oriented));
        //Create the set of graph
        Set_of_Graph<double,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between 2 unoriented graph"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot"<<endl;
    std::cout<<"The objective of this instance is to see if the matcher can find an existing optimal subgraph matching between 2 positive weighted graphs"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({1,1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({2,1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({1,1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({3,2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({1,2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({3,2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({1,2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({2,1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({1,2});
        bool oriented(false);
        //Create the 2 graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the same 2 unoriented graphs"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot"<<endl;
    std::cout<<"The objective of this instance is to see if the matcher can deal with negative weights"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({-2,-0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({-2,-1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({-3,-2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({-1,-2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({-3,-2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({-1,-2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({-2,-1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({-1,-2});
        bool oriented(false);
        //Create the graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //Create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the same 2 unoriented graphs"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot"<<endl;
    std::cout<<"The objective of this instance is to see if the matcher can deal with mixed weights"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({-2,-1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({-3,2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({1,-2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({-3,2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({1,-2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({-2,-1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({1,-2});
        bool oriented(false);
        //Create the graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //Create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCAS and the letter A"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement1_pivot with an initial weight of 1000 and a stopping criteria of 500"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_LUCAS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement2_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000),int(500));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCAS and the letter A"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement2_pivot with an initial weight of 1000 and a stopping criteria of 500"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_LUCAS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement2_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000),int(500));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCAS and the letter A"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot with an initial weight of 1000"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_LUCAS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"We now want to see the influence of chosing a good initial weight on the algorithm, first we will launch the BK with a small stopping criteria to find an upperbound"<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCAS and the letter A"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot with an initial weight of 5.5"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_LUCAS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(5.5));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    /*
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCAS written by a drunk man and the letter A"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement2_pivot with an initial weight equal to 20 and a stopping criteria of 1000"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_drunk_LUCAS(dico2,indice2);
        std::cout<<"pass"<<endl;
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        std::cout<<(*pointer1)<<endl;
        std::cout<<(*pointer2)<<endl;
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement2_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(20),int(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    */
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCASLIS and the word LI"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement1_pivot with an initial weight of 1000 and a stopping criteria of 1000"<<endl;;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_L(dico1,indice1);
        add_letter_I(dico1,indice1);
        add_LUCAS(dico2,indice2);
        add_LIS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        auto start = std::chrono::steady_clock::now();
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement1_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000),int(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCASLIS and the word LI"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement2_pivot with an initial weight of 1000 and a stopping criteria of 1000"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_L(dico1,indice1);
        add_letter_I(dico1,indice1);
        add_LUCAS(dico2,indice2);
        add_LIS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        auto start = std::chrono::steady_clock::now();
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement2_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000),int(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<std::endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCASLIS and the word LI"<<endl;
    std::cout<<"we will use the BK_matcher_precise_chosen_pivot with an initial weight of 1000"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_L(dico1,indice1);
        add_letter_I(dico1,indice1);
        add_LUCAS(dico2,indice2);
        add_LIS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        auto start = std::chrono::steady_clock::now();
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_precise_chosen_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(1000));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"The following example try to find the optimal matching between the word LUCASLIS and the word LI"<<endl;
    std::cout<<"we will use the BK_matcher_fast_improvement2_pivot with an initial weight of 10 and a stopping criteria of 500"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_L(dico1,indice1);
        add_letter_I(dico1,indice1);
        add_LUCAS(dico2,indice2);
        add_LIS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        auto start = std::chrono::steady_clock::now();
        std::pair<std::list<std::pair<int,int>>,double> result=BK_matcher_fast_improvement2_pivot(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)),double(10.0),int(500));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }

    std::cout<<std::endl;
    std::cout<<"we will now compare the previous results with the matcher_huge_graph_version"<<endl;
    std::cout<<"we expect this matcher to be faster than the BK but obviously less accurate"<<endl;
    std::cout<<"Let's start with the first instance"<<endl;
    {
        //Define the graphs
        Mymap1 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=double(1);
        dico1[std::pair<int,int>(1,1)]=double(1);
        dico1[std::pair<int,int>(2,2)]=double(1);
        dico1[std::pair<int,int>(0,1)]=double(-1);
        dico1[std::pair<int,int>(1,2)]=double(-1);
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=double(1);
        dico2[std::pair<int,int>(1,1)]=double(1);
        dico2[std::pair<int,int>(0,0)]=double(1);
        dico2[std::pair<int,int>(2,1)]=double(-1);
        dico2[std::pair<int,int>(1,0)]=double(-1);
        bool oriented(true);
        //create the 2 graphs
        std::shared_ptr<Graph<double,int>> pointer1(new Graph<double,int>(dico1,oriented));
        std::shared_ptr<Graph<double,int>> pointer2(new Graph<double,int>(dico2,oriented));
        //Print the graphs
        std::cout<<"graph1: "<<endl<<*pointer1<<endl;
        std::cout<<"graph2: "<<endl<<*pointer2<<endl;
        //Create the set of graph
        Set_of_Graph<double,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }

    std::cout<<endl;
    std::cout<<"Now the second instance with positive weights"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({1,1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({2,1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({1,1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({3,2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({1,2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({3,2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({1,2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({2,1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({1,1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({3,2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({1,2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({1,2});
        bool oriented(false);
        //Create the 2 graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"Now the second instance with negative weights"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({-2,-0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({-2,-1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({-3,-2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({-1,-2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({-3,-2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({-1,-2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({-2,-1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({-2,-0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({-3,-2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({-1,-2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({-1,-2});
        bool oriented(false);
        //Create the graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //Create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"Now the second instance with mixed weights"<<endl;
    {
        //Define the graphs
        Mymap2 dico1,dico2;
        //1st graph
        dico1[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico1[std::pair<int,int>(2,2)]=std::vector<int>({-2,-1});
        dico1[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico1[std::pair<int,int>(0,1)]=std::vector<int>({-3,2});
        dico1[std::pair<int,int>(0,3)]=std::vector<int>({1,-2});
        dico1[std::pair<int,int>(1,3)]=std::vector<int>({-3,2});
        dico1[std::pair<int,int>(2,1)]=std::vector<int>({1,-2});
        //2nd graph
        dico2[std::pair<int,int>(2,2)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(4,4)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(8,8)]=std::vector<int>({-2,-1});
        dico2[std::pair<int,int>(5,5)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(2,4)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(2,5)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(4,5)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(8,4)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(0,0)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(1,1)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(3,3)]=std::vector<int>({-1,-1});
        dico2[std::pair<int,int>(7,7)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(6,6)]=std::vector<int>({2,0});
        dico2[std::pair<int,int>(0,3)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(3,1)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(3,4)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(3,7)]=std::vector<int>({-3,2});
        dico2[std::pair<int,int>(6,7)]=std::vector<int>({1,-2});
        dico2[std::pair<int,int>(1,4)]=std::vector<int>({1,-2});
        bool oriented(false);
        //Create the graphs
        std::shared_ptr<Graph<std::vector<int>,int>> pointer1(new Graph<std::vector<int>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<int>,int>> pointer2(new Graph<std::vector<int>,int>(dico2,oriented));
        //Create the set of graph
        Set_of_Graph<std::vector<int>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"Now the LUCAS and A instance"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_A(dico1,indice1);
        add_LUCAS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"Now the LUCASLI and LI instance"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_letter_L(dico1,indice1);
        add_letter_I(dico1,indice1);
        add_LUCAS(dico2,indice2);
        add_LIS(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        auto start = std::chrono::steady_clock::now();
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(set_of_graph1.get_graph_pointer(int(1)),set_of_graph1.get_graph_pointer(int(2)));
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    std::cout<<endl;
    std::cout<<"Finally I will test this matcher on an instance that basically BK can't deal with in its actual form:"<<endl;
    std::cout<<"following example try to find the optimal matching between the word PRECIPITEVOLISSIMEVOLMENTE and the word VOLISSIME"<<endl;
    {
        Mymap3 dico1,dico2;
        int indice1(-1),indice2(-1);
        add_VOLISSIME(dico1,indice1);
        add_PRECIPITEVOLISSIMEVOLMENTE(dico2,indice2);
        bool oriented(false);
        std::shared_ptr<Graph<std::vector<double>,int>> pointer1(new Graph<std::vector<double>,int>(dico1,oriented));
        std::shared_ptr<Graph<std::vector<double>,int>> pointer2(new Graph<std::vector<double>,int>(dico2,oriented));
        Set_of_Graph<std::vector<double>,int> set_of_graph1;
        set_of_graph1.add_graph(pointer1);
        set_of_graph1.add_graph(pointer2);
        //start timer
        auto start = std::chrono::steady_clock::now();
        //BK Matcher
        std::pair<std::list<std::pair<int,int>>,double> result=matcher_huge_graph_version(pointer1,pointer2);
        std::list<std::pair<int,int>>::iterator it=result.first.begin();
        //Print the optimal permutation and the distance
        std::cout<<"Optimal permutation"<<endl;
        for (;it!=result.first.end();++it)
        {
            std::cout<<"Vertex: "<<it->first<<" permute with Vertex: "<<it->second<<endl;
        }
        std::cout<<"Graphs Distances: "<<result.second<<endl;
        //Print the time
        auto finish = std::chrono::steady_clock::now();
        double elapsed =std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
        std::cout<<"execution_time of the matching algorithm:"<<elapsed<<endl;
    }
    return 0;
}
