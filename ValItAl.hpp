#ifndef VALITAL_HPP
#define VALITAL_HPP
#include <string>
#include <vector>
#include <array>
#include <tuple>

namespace CLNSIH001{
    class State
    {
    int state;      //state number
    std::string gridIndex;
    std::vector<std::string> moves;
    void Actions();
    std::string Label();
        
    public:
        double val; int index;  //index is the state position in an array
        State(const int && s);
        int getState();     //state number
        std::string getGridIndex();     //grid index of state
        std::vector<std::string> getActions();//possible directions agent may move in from current state
        bool isTerminal();
    };

    class Algorithm
    {
    private:
        int Pr;     //transition probability
        double discount;   //discount factor
        int iterations;     //number of complete iterations
        int Reward(State s, std::string action);     //returns the reward of doing a specified action in a block
        State movesTo(State s, std::string action);//returns new state when action is performed in the current state(s)
        std::tuple<std::array<std::string, 6>, std::vector<double> > val_it_al(double threshold);   //main part of Assignment. Threshold is the degree of accuracy
    public:
        std::array<std::string, 6> pi;   //policies where each index is the policy for state(index+1) eg. index 0 = policy for s1
        State s1{1}, s2{2}, s3{3}, s4{4}, s5{5}, s6{6}; //each block in 2x3 grid
        State states[6] = {s1, s2, s3, s4, s5, s6}; //set of states
        Algorithm();        
    };
}

#endif