import numpy as np
import matplotlib.pyplot as plt

data = []
with open("sort.txt", "r") as rf:
	while True:
		line = rf.readline()
		if line == "":
			break
		data.append(int(line))
span = int(input("span is: \n"))
plt.figure()
plt.plot(data[:span])
plt.figure()
plt.plot(data[span:2*span])
plt.show()	
