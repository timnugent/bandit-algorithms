#!/usr/bin/python
import matplotlib.pyplot as plt
import csv, sys

def main(argv):

	if len(argv) > 1:
		steps = []
		cb = []
		eg = []
		rand = []

		try:
			with open(argv[1], 'rb') as csvfile:
				data = csv.reader(csvfile, delimiter=',')
				for row in data:
					if row[0] != "step" and row[0][0] != '#':
						print(row)
						steps.append(row[0])
						cb.append(row[1])
						eg.append(row[2])
						rand.append(row[3])

			png = "data/sm-vs-eg-vs-random.png"
			fig, ax = plt.subplots()
			t1, = ax.plot(steps, cb, label="Softmax")
			t2, = ax.plot(steps, eg, label="Epsilon Greedy")
			t3, = ax.plot(steps, rand, label="Random")
			plt.legend([t1,t2,t3], loc=4, numpoints=1)
			ax.set_title('Softmax vs Epsilon Greedy vs Random')
			ax.set_ylabel('Probability of selecting best arm')
			ax.set_xlabel('Steps')
			plt.ylim([0.0,1.0])
			plt.savefig(png)
			print("Parsed  " + argv[1])  
			print("Written " + png)  

		except:
			print("Couldn't parse " + argv[1])
	else:
		print("Usage:\n" + argv[0] + " <csv file>")	

if __name__ == "__main__":
    main(sys.argv)      