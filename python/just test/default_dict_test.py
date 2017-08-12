#!/bin/env python
from collections import defaultdict

d = defaultdict(lambda:len(d), UNK='0')
UNK = d['UNK']
print UNK
print d['a']

# use d to init a new dict
d = defaultdict(lambda:UNK, d)
print 'd:',d
print 'a=>', d['a']
print 'b=>', d['b']
print 'd:',d
