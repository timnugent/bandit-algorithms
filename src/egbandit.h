// Annealing Epsilon Greedy Bandit Implementation, by Tim Nugent 2015

#ifndef EGBandit_H
#define EGBandit_H

#include <iostream>
#include <string>
#include <cfloat>
#include <vector>
#include <math.h>
#include <numeric>

using namespace std;

class EGBandit{

public:

	EGBandit(vector<string>& ar) : arms(ar), gen(rd()), dis(0.0, 1.0) {
		for(auto arm: arms){
			counts.push_back(0);
			values.push_back(0.0);
			rewards.push_back(0.0);
		}
		srand (time(NULL));
	}
	
	void results(){
		double total_reward = 0.0;
		for(unsigned int i = 0; i < arms.size(); i++){
			cout << "# " << arms[i] << "\t" << rewards[i] << endl;
			total_reward += rewards[i];
		}
		cout << "# Total:\t" << total_reward << endl;
	}
	
	int best_arm(){

		int t = accumulate(counts.begin(),counts.end(),0);
		double epsilon = 1.0 / log(t + DBL_EPSILON);

		int ind = 0;
		double max_val = -10000.0;

    	if(dis(gen) > epsilon){
    		for(unsigned int i = 0; i < values.size(); i++){
    			if(values[i] > max_val){
    				ind = i;
    				max_val = values[i];
    			}
    			return(ind);
    		}
    	}else{
    		return(rand() % values.size());
    	}
	}

	void update(int arm, double reward){
		int n = ++counts[arm];
		double value = values[arm];
		values[arm] = ((n - 1) / double(n)) * value + (1.0 / double(n)) * reward;
		rewards[arm] += reward;
	}

private:

	vector<string> arms;
	vector<int> counts;
	vector<double> values, rewards;
	random_device rd;
    mt19937 gen;
	uniform_real_distribution<double> dis;
	
};

#endif
