#include "ValItAl.hpp"
#include <fstream>
#include <sstream>

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
    
    int State::getState()const{
        int s = state;
        return s;
    }
    string State::getGridIndex()const{
        string i = gridIndex;
        return i;
    }
    vector<string> State::getActions()const{
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
    }
    int Algorithm::Reward(State s, string action){
        if (s.getState() == 2 && action == "right"){return /*3**/50/*0*/;}
        else if (s.getState() == 6 && action == "up"){return /*3**/100/*0*/;}
        /*else if (s.getState() == 5 && action == "right"){return 3;}
        else if (s.getState() == 5 && action == "up"){return 5;}
        else if (s.getState() == 4 && action == "right"){return -10;}
        else if (s.getState() == 2 && action == "down"){return -15;}*/
        else
        {
            //return 5;
            return /*3**/0/*7*/;
        }
        
    }  
    
    State Algorithm::movesTo(State s, string action)const{
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
        return s;       
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
            if (s.isTerminal()){moves = "stay";}
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

    std::ostream & operator<<(std::ostream& os, const Algorithm & VIA){
        os << "states" << "{s" << VIA.states[0].getState();
        for (int i=1;i<6;i++){
            os << ", s" << VIA.states[i].getState();
        }
        os << '}' << '\n';
        os << "values" << '{' << VIA.states[0].val;
        for (int i=1;i<6;i++){
            os << ", " << VIA.states[i].val;
        }
        os << '}' << '\n';
        os << "policy" << '{' << VIA.pi[0];
        for (int i=1;i<6;i++){
            os << ", " << VIA.pi[i];
        }
        os << '}' << '\n';
        os << "number of iterations: " << VIA.iterations << '\n';

        os << "\n////////////////////////////////////////////////////////////////\n";

        os << "\n1.   How many iterations does it take for the Value Iteration algorithm to converge?\n";
        os << "     number of iterations: " << VIA.iterations << '\n';
        os << "     s" << VIA.states[0].getState() << ": " << VIA.states[0].val;
        for (int i=1;i<6;i++){
            os << ", s" << VIA.states[i].getState() << ": " << VIA.states[i].val;
        }
        os << '\n' << '\n';
        os << "2.   Assuming we start in state s1, give the states that form the optimal policy (π∗) to reach the terminal state (s3).\n";
        os << "     state " << VIA.states[0].getState() << " at " << VIA.states[0].getGridIndex() << " moves " << VIA.pi[VIA.states[0].index] << " to s" << VIA.movesTo(VIA.states[0], VIA.pi[VIA.states[0].index]).getState() << ".\n";
        os << "     state " << VIA.s4.getState() << " at " << VIA.s4.getGridIndex() << " moves " << VIA.pi[VIA.s4.index] << " to s" << VIA.movesTo(VIA.s4, VIA.pi[VIA.s4.index]).getState() << ".\n";
        os << "     state 5 at " << VIA.s5.getGridIndex() << " moves right to s6.\n";
        os << "     state 6 at " << VIA.s6.getGridIndex() << " moves up to s3.\n";
        os << "     so graphically...\n"<< "        s1    s2    s3\n        |            ^\n        |            |\n        s4 -> s5 -> s6";
        os << '\n' << '\n';
        os << "3.   Is it possible to change the reward function so that V∗ changes, but the optimal policy (π∗) remains unchanged?\n";
        os << "     Yes it is possible. When I mmultiplied the reward funtion for each transition by a factor of 3 and ran the code, I got new values for each state \n";
        os << "     but the policy remain unchanged. Same thing happened when I changed every 0 reward to 5 instead of multiplying everything by 3.\n";
        os << "     values{153.6, 192, 0, 192, 240, 300}\n     policy{down, down, , right, right, up}\n";
        os << "     values{63.4, 73, 0, 73, 85, 100}\n     policy{down, down, , right, right, up}\n";
        os << "     When I changed the rewards for each transition between states to any number (view commented out parts of reward function),\n";
        os << "     the policies, values and even iterations changed:\n";
        os << "     values{35, 35, 0, 35, 35, 35}\n     policy{down, left, , up, left, left}\n     number of iterations: 157\n";
        return os;
    }
}

int main(int argc, char * argv[]){
    CLNSIH001::Algorithm algrthm;
    std::ofstream answers("Output.txt", std::ios::out);
    answers << algrthm;
    answers.close();
    return 0;
}