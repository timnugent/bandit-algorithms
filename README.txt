Epsilon-Greedy, Softmax and LinUCB Contextual Bandit Implementations
--------------------------------------------------------------------
Tim Nugent 2015

Upper confidence bound (UCB) contextual bandit with disjoint linear models - see algorithm 1 here (also in docs directory):

http://www.research.rutgers.edu/~lihong/pub/Li10Contextual.pdf

Annealing softmax (Blotzmann Exploration) and annealing Epsilon-Greedy implementations:

http://www.cs.mcgill.ca/~vkules/bandits.pdf

Build
-----

Requires C++ build-essential package (e.g. sudo apt-get install build-essential) and Eigen headers, which are included. Just run 'make'.

The Python script to plot the results requires matplotlib (e.g. sudo apt-get install python-matplotlib).

Run
---

Run with 'make test'. This runs the binary and then calls the python scipt to plot the results.

Output
------

bin/cbandit > data/cbandit_out.csv
src/plot.py data/cbandit_out.csv
['1', '0', '1']
['2', '0', '1']
['3', '0.333333', '1']
['4', '0.25', '0.75']
['5', '0.4', '0.6']
['6', '0.5', '0.5']
['7', '0.428571', '0.428571']
['8', '0.375', '0.5']
['9', '0.333333', '0.444444']
['10', '0.4', '0.4']
...
['2995', '0.982638', '0.249082']
['2996', '0.982644', '0.248999']
['2997', '0.982649', '0.248916']
['2998', '0.982655', '0.248833']
['2999', '0.982661', '0.24875']
['3000', '0.982667', '0.248667']
Parsed  data/cbandit_out.csv
Written data/cb-vs-random.png
...
bin/smbandit > data/sm-eg-bandit_out.csv
src/plot2.py data/sm-eg-bandit_out.csv
['1', '0', '0', '0']
['2', '0', '0', '0']
['3', '0', '0.333333', '0']
['4', '0', '0.25', '0']
...
['2995', '0.976294', '0.976294', '0.211018']
['2996', '0.976302', '0.976302', '0.211282']
['2997', '0.97631', '0.97631', '0.211545']
['2998', '0.976318', '0.976318', '0.211474']
['2999', '0.976325', '0.976325', '0.211404']
['3000', '0.976333', '0.976333', '0.211333']
Parsed  data/sm-eg-bandit_out.csv
Written data/sm-vs-eg-vs-random.png


See the plot data/cb-vs-random.png. The results show how the contextual bandit compares with a random strategy at selecting the best of 4 arms, with 'best' being determined by the context (in this case a a vector of length 2 - see line 37-44 in main.cpp). The contextual bandit learns which contexts yield a reward by updating the A matrix for the best arm at each step, and the B vector for this arm if there is a non-zero reward (i.e. the selected arm is correct). As expected, the random strategy converges to about 25%, while the contextual bandit learns quickly and converges to ~98% over 3000 steps. Methods such as the contextual bandit are therefore well suited to personalised (this data is provided as the context) recommender systems where feedback is partial (i.e. user clicks). The second plot data/sm-vs-eg-vs-random.png shows the performance of annealing Epsilon-Greedy and Softmax bandits vs a random strategy, with 5 Bernoulli arms.

Bugs
----

timnugent@gmail.com