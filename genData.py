import numpy as np
import matplotlib.pyplot as plt

dataLength = int(input("dataLength"))
data = np.random.randn(dataLength, 1) * dataLength
data = data.astype(np.int64)

with open('data.txt', 'w') as wf:
	for i in data:
		wf.write("%d\n"%i)
plt.figure()
plt.hist(data)
plt.figure()
plt.plot(data[1000:3000])
plt.show()
print(sum(data))
