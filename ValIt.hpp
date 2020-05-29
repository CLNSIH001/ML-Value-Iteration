#ifndef VALIT_HPP
#define VALIT_HPP
#include <string>
#include <vector>

namespace CLNSIH001{
    class State
    {
    int state;
    int endState = 3;
    std::string index;
    std::vector<std::string> moves;
    void Actions();
    std::string Label();
        
    public:
        State(const int && s);
        int getState();
        std::string getIndex();
        std::vector<std::string> getActions();
    };

    struct Algrthm
    {
        State s1{1}, s2{2}, s3{3}, s4{4}, s5{5}, s6{6};
    };
}

#endif