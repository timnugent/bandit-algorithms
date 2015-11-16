// LinUCB Contextual Bandit Implementation, by Tim Nugent 2015

#ifndef CBandit_H
#define CBandit_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class CBandit{

public:

	CBandit(vector<string>& ar, unsigned int dim) : arms(ar), d(dim), step(0), best_index(0), rho(0.1), average(dim){
		for(auto arm: arms){
			a_matrix.push_back(MatrixXd::Identity(d,d));
			b_vector.push_back(VectorXd::Zero(d));
			rewards.push_back(0.0);
		}
	}

	void set_rho(double r){
		rho = r;
	}

	void results(){
		double total_reward = 0.0;
		for(unsigned int i = 0; i < arms.size(); i++){
			cout << "# " << arms[i] << "\t" << rewards[i] << endl;
			total_reward += rewards[i];
		}
		cout << "# Total:\t" << total_reward << endl;
	}

	int best_arm(VectorXd& x){

		// Update the average
		if(!step) average.setZero();
		average = (step*average + x)/(step+1);
		step++;

		VectorXd context = x - average;
		string tmp = "";
		best_index = 0;
		double best_payoff = -1000000.0;
		for(unsigned int i = 0; i < arms.size(); i++){
			double p = payoff(context,i);
			// If there's a tie we grab the last arm in the tie.. we should pick randomly
			if(p >= best_payoff){
				best_payoff = p;
				best_index = i;
			}
			tmp += to_string(p) + " " + arms[i] + ", ";
		}
		//cout << "payoffs: " << tmp << endl;
		return(best_index);
	}

	void update(VectorXd& x, double reward){
		VectorXd context = x - average;
		a_matrix[best_index] += context * context.transpose();
	    if(reward != 0.0){
	    	b_vector[best_index] += reward * context;
	    }
		rewards[best_index] += reward;
	}

private:

	double alpha(){
		return 1.0 + sqrt(log(2.0/rho)/2.0);
	}

	double payoff(VectorXd& context, unsigned int arm){
		VectorXd o = a_matrix[arm].inverse() * b_vector[arm];
		VectorXd t = context.transpose() * a_matrix[arm].inverse();
		double p = o.transpose().dot(context) + alpha() * sqrt(t.dot(context));
		return(p);
	}

	vector<string> arms;
	unsigned int d, step, best_index;	
	double rho;
	vector<MatrixXd> a_matrix;
	vector<VectorXd> b_vector;
	VectorXd average;
	vector<double> rewards;

};

#endif
