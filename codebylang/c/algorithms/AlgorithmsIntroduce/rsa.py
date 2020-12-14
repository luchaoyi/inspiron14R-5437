#gcd(a,b)=gcd(b,a mod b)
import  random

def gcd(a,b):
    if b==0:
        return a
    else:
        return gcd(b,a%b)

def pollaed_rho(n):
    i=1
    x=int(random.random()*n-1)
    y=x
    k=2
    while True:
        i=i+1
        x=(x**2-1)%n
        d=gcd(y-x,n)
        if d!=1 and d!=n:
            #print d
            return d,n/d
        if i==k:
            y=x
            k=2*k

