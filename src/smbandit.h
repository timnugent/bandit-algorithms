// Annealing Softmax Bandit Implementation, by Tim Nugent 2015

#ifndef SMBandit_H
#define SMBandit_H

#include <iostream>
#include <string>
#include <cfloat>
#include <vector>
#include <math.h>
#include <numeric>

using namespace std;

class SMBandit{

public:

	SMBandit(vector<string>& ar) : arms(ar), gen(rd()), dis(0.0, 1.0) {
		for(auto arm: arms){
			counts.push_back(0);
			values.push_back(0.0);
			rewards.push_back(0.0);
		}
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
		double temperature = 1.0 / log(t + DBL_EPSILON);
		double z = 0.0;
		for(auto v: values){
			z += exp(v/temperature);
		}
		probs.clear();
		for(auto v: values){
			probs.push_back(exp(v/temperature)/z);
		}		
		z =	dis(gen);
		double cum_prob = 0.0;
		for(unsigned int i = 0; i < probs.size(); i++){
			cum_prob += probs[i];
			if(cum_prob > z){
				return(i);
			}
		}
		return(probs.size()-1);

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
	vector<double> values, rewards, probs;
	random_device rd;
    mt19937 gen;
	uniform_real_distribution<double> dis;
};

#endif
