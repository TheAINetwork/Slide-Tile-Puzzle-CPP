import os
from random import randint, random
os.system("g++-7 solution.cpp -o test -std=c++17 -O2")
size = 3
simulationSize = 100
interval = 100
prevdx, dx, amount = 0.0, 0.5, 100

def readResult():
  f = open("result", "r")
  lines = f.readlines()
  result = []
  for i, line in enumerate(lines):
    l = line.split()
    result += [[int(l[2 + (i>0)].split(',')[0]), int(l[4 + (i>0)])]]
  return(result)

def run(best, i, node = None):
  if (node is None):
    os.system("./test %d %d 0 %lf > result" % (size, simulationSize, i / interval))
  else:
    os.system("./test %d %d 0 %lf %lf %lf %lf > result" % (size, simulationSize, node[0], node[1], node[2], node[3])) #i / interval, node[0], node[1], node[2]))
  result = readResult()
  for j in range(len(best)):
    if (result[j][1] > best[j][1]):
      if (node is None):
        best[j] = [i, result[j][1]]
      else:
        best[j] = [i, result[j][1], node]

def shift(number):
  result = number + (dx - 2 * random() / (1/dx))
  while (result < 0):
    result = number + (dx - 2 * random() / (1/dx))
  return(result)

def generateNeighbors(node):
  configSet = set()
  while (len(configSet) < amount):
    configSet.add(tuple(map(shift, node)))
  return(configSet)

def hillClimb():
  best, prevBest, stuck = [[-1, -1e20, [0, 1, 1, 1]] for i in range(3)], -1, 0
  node = [0, 1, 1, 1]
  episodes = 100
  while (episodes):
    print(episodes)
    configSet = generateNeighbors(node)
    for i, config in enumerate(configSet):
      if (config[1] == 0 and config[2] == 0 and config[3] == 0): continue
      # print(i, config)
      run(best, 0, config)
    if (prevBest == best[2][1]):
      stuck += 1
      if (stuck < 11): dx += prevdx
    else:
      stuck = 0
      dx = prevdx
    prevBest = best[2][1]
    print(best[2], stuck)
    node = best[2][2]
    episodes -= 1
  return(best)

def bestPrev():
  best = [[-1, -1e20] for i in range(3)]
  for i in range(1, interval + 1):
    print("size: %d, simulationSize: %d, prevWeight: %lf" % (size, simulationSize, i / interval))
    run(best, i)
    print(best)
  return(best)

best = hillClimb()
print("\nEnded:")
print(best)