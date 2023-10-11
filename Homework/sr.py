'''
module: _numint2.py
author: Luis Paris
description:
- formulas from Chapra's numerical methods textbook
- implements discrete single/multi segment simpson's 1/3 & 3/8 rules
  (2nd & 3rd order newton-cotes integration formulas)
- chapters on numerical integration for discrete functions
- implemented from algorithms/pseudocode provided
'''

import _numint

def simp13(f0, f1, f2, h):
    return h * (f0 + 4*f1 + f2) / 3.
#end simp13()

def simp38(f0, f1, f2, f3, h):
    return 3*h * (f0 + 3*(f1+f2) + f3) / 8.
#end simp13()

#fi fi+1 fi+2
#  1  4  1
#        1  4  1
#              1  4  1
#  ===================
#  1  4  2  4  2  4  1
def simp13m(fpts, h, n):
    sum = fpts[0]
    for i in range(1, n-1, 2):
        sum += 4*fpts[i] + 2*fpts[i+1]
    sum += 4*fpts[n-1] + fpts[n]
    return h*sum/3.
#end simp13m()

#fi fi+1 fi+2 fi+3
#  1  3  3  1
#           1  3  3  1
#                    1  3  3  1
#  ==============================
#  1  3  3  2  3  3  2  3  3  1
def simp38m(fpts, h, n):
    sum = fpts[0]
    for i in range(1, n-2, 3):
        sum += 3*(fpts[i] + fpts[i+1]) + 2*fpts[i+2]
    sum += 3*(fpts[n-2] + fpts[n-1]) + fpts[n]
    return 3*h*sum/8.
#end simp38m()

def simpint(fpts, x0, xn, n):
    h = (xn - x0) / float(n)
    if n <= 1:
        sum = _numint.trap(fpts[n-1], fpts[n], h)
    else:
        m = n
        sum = 0.
        if n % 2:  #if n is odd (3,5,7,...)
            sum += simp38(fpts[n-3], fpts[n-2], fpts[n-1], fpts[n], h)
            m = n - 3
        if m:
            sum += simp13m(fpts, h, m)
    return sum
#end simpint()

'''
module: _numint2.py
author: Luis Paris
description:
- formulas from Chapra's numerical methods textbook
- implements discrete single/multi segment simpson's 1/3 & 3/8 rules
  (2nd & 3rd order newton-cotes integration formulas)
- chapters on numerical integration for discrete functions
- implemented from algorithms/pseudocode provided
'''

import _numint

def simp13(f0, f1, f2, h):
    return h * (f0 + 4*f1 + f2) / 3.
#end simp13()

def simp38(f0, f1, f2, f3, h):
    return 3*h * (f0 + 3*(f1+f2) + f3) / 8.
#end simp13()

#fi fi+1 fi+2
#  1  4  1
#        1  4  1
#              1  4  1
#  ===================
#  1  4  2  4  2  4  1
def simp13m(fpts, h, n):
    sum = fpts[0]
    for i in range(1, n-1, 2):
        sum += 4*fpts[i] + 2*fpts[i+1]
    sum += 4*fpts[n-1] + fpts[n]
    return h*sum/3.
#end simp13m()

#fi fi+1 fi+2 fi+3
#  1  3  3  1
#           1  3  3  1
#                    1  3  3  1
#  ==============================
#  1  3  3  2  3  3  2  3  3  1
def simp38m(fpts, h, n):
    sum = fpts[0]
    for i in range(1, n-2, 3):
        sum += 3*(fpts[i] + fpts[i+1]) + 2*fpts[i+2]
    sum += 3*(fpts[n-2] + fpts[n-1]) + fpts[n]
    return 3*h*sum/8.
#end simp38m()

def simpint(fpts, x0, xn, n):
    h = (xn - x0) / float(n)
    if n <= 1:
        sum = _numint.trap(fpts[n-1], fpts[n], h)
    else:
        m = n
        sum = 0.
        if n % 2:  #if n is odd (3,5,7,...)
            sum += simp38(fpts[n-3], fpts[n-2], fpts[n-1], fpts[n], h)
            m = n - 3
        if m:
            sum += simp13m(fpts, h, m)
    return sum
#end simpint()

def trap(f0, f1, h):
    return h * (f0 + f1) / 2.
#end trap()
