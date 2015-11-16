// Annealing Softmax Bandit Implementation, by Tim Nugent 2015

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "egbandit.h"
#include "smbandit.h"

using namespace std;

int main(){

    // Steps and reward counts
    unsigned int T = 3000;

    vector<string> arms_sm = {"arm1", "arm2", "arm3", "arm4", "arm5"};

    std::random_device m_seed;
    std::mt19937 gen;  
    bernoulli_distribution d1(0.1); // arms 1-4
    bernoulli_distribution d2(0.9); // arm 5

    SMBandit* B = new SMBandit(arms_sm);
    SMBandit* E = new SMBandit(arms_sm);

    int sm_reward = 0, eg_reward = 0, _rand = 0;

    // CSV header
    cout << "step,cb,random" << endl;

    for(unsigned int t = 1; t <= T; t++){

        // Softmax
        int arm = B->best_arm();
        double reward = d1(gen);
        if(arm == 4){
            reward = d2(gen);  
            sm_reward++;          
        }
        B->update(arm,reward);
 
        // Epsilon Greedy
        arm = E->best_arm();
        reward = d1(gen);
        if(arm == 4){
            reward = d2(gen);  
            eg_reward++;          
        }
        E->update(arm,reward);

        // Random
        int rand_strat = rand() % arms_sm.size();
        if(rand_strat == 4){    
            _rand++;
        }


        cout << t << "," << (double)sm_reward/t << "," << (double)eg_reward/t << "," << (double)_rand/t << endl;
    }
    B->results();

    delete B;
    return(0);

}
