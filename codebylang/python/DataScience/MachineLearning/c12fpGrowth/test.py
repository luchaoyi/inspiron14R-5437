import  fpGrowth



simDat = fpGrowth.loadSimpDat()

initSet = fpGrowth.createInitSet(simDat)

myFptree,myHeaderTab = fpGrowth.createTree(initSet,3)
myFptree.disp()

freqItems=[]
fpGrowth.mineTree(myFptree,myHeaderTab,3,set([]),freqItems)
print freqItems
