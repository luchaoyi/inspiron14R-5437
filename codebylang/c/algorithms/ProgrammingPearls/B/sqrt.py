# x^2-a=0 xi+1 = xi - (xi-a/xi)/2
#牛顿方法是求f(x)=0的方法 X(n+1)=X(n)-f(X(n))/f'(X(n))
#最优化方法求解的是目标函数F的导数F'(x)=0


def sqrt(a):
    xold=a
    xnew=xold - (xold-a/xold)*0.5

    print xold 
    print xnew

    while abs(xnew-xold)>0.0000000000001:
        xold=xnew
        xnew=xold - (xold-a/xold)*0.5

    return xnew


