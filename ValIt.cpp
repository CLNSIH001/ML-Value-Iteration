#include "ValIt.hpp"
#include <iostream>

namespace CLNSIH001{
    using namespace std;
    State::State(const int && s) : state(s)
    {
        if (state != endState){Actions();}
        index = Label();
    }
    
    void State::Actions(){
        if (state+3 <= 6){moves.push_back("down");}
        if (state-3 >= 1){moves.push_back("up");}
        if (state+1 <= 6){moves.push_back("right");}
        if (state != 1 && state != 4){moves.push_back("left");}
    }
    string State::Label(){
        int x, y;
        if (state >= 1 && state <=3){
            y = 1;
            x = state-1;}
        else{
            y=0;
            x = state-4;}
        return 's'+to_string(state)+": "+'('+to_string(x)+','+to_string(y)+')';
    }
    
    int State::getState(){
        int s = state;
        return s;
    }
    string State::getIndex(){
        string i = index;
        return i;
    }
    vector<string> State::getActions(){
        vector<string> a = moves;
        return a;
    }

}