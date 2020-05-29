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

    int Algorithm::Reward(State s, string action){
        if (s.getState() == 2 && action == "right"){return 50;}
        else if (s.getState() == 6 && action == "up"){return 100;}
        else
        {
            return 0;
        }
    }  
    State Algorithm::movesTo(State s, string action){
        if (action == "up"){
            int nextState = s.getState()-3;
            return states[nextState-1];
        }
        else if (action == "down"){
            int nextState = s.getState()+3;
            return states[nextState-1];
        }
        else if (action == "left"){
            int nextState = s.getState()-1;
            return states[nextState-1];
        }
        else if (action == "right"){
            int nextState = s.getState()+1;
            return states[nextState-1];
        }       
    }
}