SHELL := /bin/bash
all:
	g++ -O3 --std=c++11 -Wall -Wextra -Ieigen-3.2.4 src/main_cb.cpp -o bin/cbandit
	g++ -O3 --std=c++11 -Wall -Wextra -Ieigen-3.2.4 src/main_sm-eg.cpp -o bin/sebandit
clean:
	rm -f bin/cbandit bin/sebandit data/cbandit_out.csv data/sm-eg-bandit_out.csv data/cb-vs-random.png data/sm-vs-eg-vs-random.png
test:
	bin/cbandit > data/cbandit_out.csv
	src/plot1.py data/cbandit_out.csv
	if [ -a /usr/bin/display ]; then display data/cb-vs-random.png; fi;
	bin/sebandit > data/sm-eg-bandit_out.csv
	src/plot2.py data/sm-eg-bandit_out.csv
	if [ -a /usr/bin/display ]; then display data/sm-vs-eg-vs-random.png; fi;