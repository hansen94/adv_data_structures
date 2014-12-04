#/usr/bin/python
# 
# Randomized Test Cases
# 
# 


import sys, os

if len(sys.argv) < 2:
    print "Usage:", sys.argv[0], "<number of tests> <max vertices> <max edges>"
    exit()


import time
def time_exec(f):
    t0 = time.time()
    val = f()
    return time.time() - t0, val

import random, tempfile
def mktestfile(genpath, max_vert, max_edge):
    fname = tempfile.mktemp()
    f = open(fname, "w")
    verts = random.randrange(2, max_vert)
    edges = random.randrange(verts-1, max_edge)
    out = os.popen4(["python", genpath,
                     str(verts),
                     str(edges)])
    txt = out[1].read()
    f.write(txt)
    f.close()
    return fname
    

def test(exepath, fname):
    out = os.popen4([exepath, fname])
    return out[1].read()


ntests = int(sys.argv[1])
nedge  = int(sys.argv[3])
nvert  = min(int(sys.argv[2]), nedge+1)


sep = ","
print sep.join(j for j in ["TestNum", "Success", "Excel", "RefTime", "RTotCost", "RMinCost",
                           "RDiffCost", "RTotLat", "RMinLat", "RDiffLat",
                           "CusTime", "CTotCost", "CMinCost",
                           "CDiffCost", "CTotLat", "CMinLat", "CDiffLat"])
for i in range(ntests):
    fname = mktestfile("./generator.py", nvert, nedge)
    rtime, rval = time_exec(lambda: test("./refnetplan", fname))
    ctime, cval = time_exec(lambda: test("./netplan", fname))
    print sep.join([str(i), str(rval==cval), str(ctime < rtime), str(rtime), rval.replace("\n", sep), str(ctime), cval.replace("\n", sep)])



