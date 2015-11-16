// LinUCB Contextual Bandit Implementation, by Tim Nugent 2015

#include <iostream>
#include <vector>
#include <string>
#include "cbandit.h"

using namespace std;

int main(){

    srand((unsigned int) time(0));

    // Arms
    vector<string> arms = {"arm1", "arm2", "arm3", "arm4"};
    // Dimension of context vector 
    unsigned int d = 2;
    // Create contextual bandit
    CBandit* C = new CBandit(arms,d);

    // Steps and reward counts
    unsigned int T = 3000;
    int cb_reward = 0, rand_reward = 0;
    
    // CSV header
    cout << "step,cb,random" << endl;

    for(unsigned int t = 1; t <= T; t++){

        // Create random context        
        VectorXd context = VectorXd::Random(d);
        for (unsigned int i = 0; i < context.rows(); i++){
            if (context(i) < 0) context(i) *= -1;        
        }

        // Set 'correct' arm according to context
        int correct = 0;
        if(context(0) < 0.5 && context(1) > 0.5){
            correct = 1;
        }else if(context(0) > 0.5 && context(1) < 0.5){
            correct = 2;
        }else if(context(0) > 0.5 && context(1) > 0.5){
            correct = 3;
        } 

        // See if the contextual bandit can figure out the correct arm based on the context
        // If it's correct, give a reward; update
        if(C->best_arm(context) == correct){      
            C->update(context, 1.0);
            cb_reward++;
        }else{
            C->update(context, 0.0);
        }

        // Now compare with a random strategy
        int rand_strat = rand() % arms.size();
        if(rand_strat == correct){    
            rand_reward++;
        }

        // Write line to CSV file
        cout << t << "," << (double)cb_reward/t << "," << (double)rand_reward/t << endl;
    }

    // Summary statistics for each arm
    C->results();

    delete C;
    return(0);
}
