import os
from random import randint, random
os.system("g++ solution.cpp -o test -std=c++11 -O2")
size = 4
simulationSize = 100
interval = 100

def readResult():
  f = open("result", "r")
  lines = f.readlines()
  result = []
  for i, line in enumerate(lines):
    l = line.split()
    result += [[int(l[2 + i].split(',')[0]), int(l[4 + i])]]
  return(result)

best = [[-1, -1e20], [-1, -1e20]]
for i in range(1, interval + 1):
  print("size: %d, simulationSize: %d, prevWeight: %lf" % (size, simulationSize, i / interval))
  os.system("./test %d %d 0 %lf > result" % (size, simulationSize, i / interval))
  result = readResult()
  for j in range(2):
    if (result[j][1] > best[j][1]):
      best[j] = [i, result[j][1]]
  print(best)

print("\nEnded:")
print(best)
