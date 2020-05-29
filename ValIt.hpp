#ifndef VALIT_HPP
#define VALIT_HPP
#include <string>
#include <vector>

namespace CLNSIH001{
    class State
    {
    int state;
    int endState = 3;   //terminal state
    std::string index;
    std::vector<std::string> moves;
    void Actions();
    std::string Label();
        
    public:
        State(const int && s);
        int getState();     //state number
        std::string getIndex();     //grid index of state
        std::vector<std::string> getActions();//possible directions agent may move in from current state
    };

    struct Algorithm
    {
        State s1{1}, s2{2}, s3{3}, s4{4}, s5{5}, s6{6}; //each block in 2x3 grid
        State states[6] = {s1, s2, s3, s4, s5, s6}; //set of states
        string pi[6];   //policies where each index is the policy for state(index+1) eg. index 0 = policy for s1
        int Pr = 1;     //transition probability
        double discout = 0.8;   //discount factor
        std::vector<double*> values{6}, preVals{6};//where each index is the value for state(index+1)
        int Reward(State s, string action);     //returns the reward of doing a specified action in a block
        State movesTo(State s, string action);//returns new state when action is performed in the current state(s)
    };
}

#endif