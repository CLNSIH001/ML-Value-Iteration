#include "ValItAl.hpp"
#include <iostream>

namespace CLNSIH001{
    using namespace std;
    
    State::State(const int && s) : state(s)
    {
        if (!isTerminal()){Actions();}
        gridIndex = Label();
        val = 0.0; index = state-1;
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
    string State::getGridIndex(){
        string i = gridIndex;
        return i;
    }
    vector<string> State::getActions(){
        vector<string> a = moves;
        return a;
    }
    bool State::isTerminal(){
        if (state == 3) return true;
        else
            return false;
    }

    
    Algorithm::Algorithm(){
        discount = 0.8;
        Pr = 1;
        iterations = 0;
        vector<double> v;
        tie(pi, v) = val_it_al(0.0);;
        for (int i=0; i<6; i++){
            states[i].val = v.at(i);
        }
        
        /////////////////
        cout << "states" << "{s" << states[0].getState();
        for (int i=1;i<6;i++){
            cout << ", s" << states[i].getState();
        }
        cout << '}' << endl;
        cout << "values" << '{' << states[0].val;
        for (int i=1;i<6;i++){
            cout << ", " << states[i].val;
        }
        cout << '}' << endl;
        cout << "policy" << '{' << pi[0];
        for (int i=1;i<6;i++){
            cout << ", " << pi[i];
        }
        cout << '}' << endl;
        cout << "number of iterations: " << iterations << endl;
        ////////////////
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
    
    tuple<array<string, 6>, vector<double> > Algorithm::val_it_al(double threshold){
        bool stop = false;      //BaseCase to stop iterations
        vector<double> values{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //old vector of state values
        array<string, 6> policy;
        while (stop == false)
        {
            vector<double> newVal(6, 0.0);
            for (State s : states){
                if (s.isTerminal()){newVal.at(s.index) = 0.0;}
                else{
                    double max = 0;
                    for (string a : s.getActions()){
                        //because transition probability is 1 (deterministic) there is no need for sum as 
                        //the agent is (definitely) moved to ONE state (no other) for each action performed
                        double r = Reward(s, a) + discount*Pr*values.at(movesTo(s,a).index);
                        if (max < r){max = r;}
                    }
                    newVal.at(s.index) = max;
                }
            }
            ++iterations;
            bool goOn = false;
            for (int i = 0; i < newVal.size(); i++)
            {
                if (abs(values.at(i) - newVal.at(i)) > threshold){
                    goOn = true;
                    values = newVal;
                }
            }
            if (goOn == false){stop = true;}
        }
        for (State s : states){
            double max = 0;
            string moves;
            for (string a : s.getActions()){
                double r = Reward(s, a) + discount*Pr*values.at(movesTo(s,a).index);
                if (max < r){
                    max = r;
                    moves = a;
                }
            }
            policy.at(s.index) = moves;
        }
        return make_tuple(policy, values);
    }
}

int main(){
    CLNSIH001::Algorithm algrthm; return 0;
}