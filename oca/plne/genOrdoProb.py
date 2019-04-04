import random

random.seed(2)

nbMachine = 100
nbTask = 10000
rangeCost = (5,20)
rangeTime = (1,10)

res = "c s machine cost\nc e task machine duration\n"
for j in range(1, nbMachine+1):
    res += "s %d %d\n"%(j, random.randint(rangeCost[0], rangeCost[1]))

for i in range(1, nbTask+1):
    for j in range(1, nbMachine+1):
        res += "e %d %d %d\n"%(i, j, random.randint(rangeTime[0], rangeTime[1]))

with open("m%d_t%d.in"%(nbMachine, nbTask), "w") as f:
    f.write(res)

