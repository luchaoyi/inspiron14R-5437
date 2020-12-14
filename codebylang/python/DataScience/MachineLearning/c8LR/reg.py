
#线性回归是最小均方误差的无偏估计，引入偏差降低预测均方误差
#每一点的数据集权值不同所以，拟合theta不同
def lwlr(testPoint,xArr,yArr,k=1.0):
    xMat = mat(xArr) ; yMat = mat(yArr)

    m=shape(xMat)[0]
    
    weights = mat(eye(m))

    #计算对于数据点其它样本的权值
    for j in range m:
        diffMat = testPoint - xMat[j,:]
        weights[j,j] = exp(diffMat*diffMat.T/(-2.0*k**2))
    
    xTx = xMat.T*(weights*xMat)
    if linalg.det(xTx) == 0.0:
        #error 不能求逆
        return
    ws = xTx.I*(xMat.T*(weights*yMat))
    return testPoint*ws


#n>m时，缩减系数来理解数据
def ridgeRegres(xMat,yMat,lam=0.2):
    
    xTx = xMat.T*xMat 
    denom = xTx + eye(shape(xMat)[1])*lam #岭回归

    if linalg.det(denom) == 0.0:
        return
    ws = denom.I *(xMat.T*yMat)
    return ws

#lasso方法对w引入约束 Ewk^2 <=lamda E|wk|<=lamda 当lamda足够小时，一些系数会被迫缩减为0,变相排除了不重要的特征
#缩减贡献小的特征
#前向逐步回归，每次改变一个特征进行优化回归，坐标上升法思想属于贪心策略

def stageWise(xArr,yArr,eps=0.01,numIt=100):
    xMat=mat(xArr);yMat=mat(yArr).T
    yMean=mean(yMat,0)
    yMat=yMat - yMean
    xMat=regularize(xMat)
    m,n=shape(xMat)

    returnMat=zeros((numIt,n))

    ws=zeros((n,1));wsTest=ws.copy();wsMax=ws.copy()

    for i in range(numIt):
        print ws.T
        lowestError=inf;
        for j in range(n):
            #改变某个特征 - or + 一小步选择更优的
            for sign in [-1,1]:
                wsTest = ws.copy()
                wsTest[j]+=eps*sign
                yTest = xMat*wsTest
                rssE = rssError(yMat.A,yTest.A)
                if rssE < lowestError:
                    lowestError=rssE
                    wsMax=wsTest

        #一次迭代，尝试所有系数改变（+，-）,最终选择一个改变
        #逐步回归，逐步改变某个特征，每次只改变了一个特征，所以是逐步回归
        #依次迭代，只有某一个系数有微小的变化，因为贪心，所以谨慎
        ws=wsMax.copy()
        returnMat[i,:]=ws.T
    return returnMat
            
