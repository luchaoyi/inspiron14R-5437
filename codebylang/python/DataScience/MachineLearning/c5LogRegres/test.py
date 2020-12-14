import random

d=range(20)
for i in range(20):

	

	i=random.choice(d)

	print '%d' %i

	del(d[d.index(i)])
	
	

print d

print '--------------------------------------------------------------------'


dataIndex = range(20)
for i in range(20):
        randIndex = int(random.uniform(0,len(dataIndex)))
        print '%d' %randIndex

        #每次斩掉一个最终dataIndex = []
        del(dataIndex[randIndex])


print dataIndex

print '--------------------------------------------------------------------'

dataIndex = range(20)
for i in range(20):
        randIndex = int(random.uniform(0,len(dataIndex)))
        print '%d' %dataIndex[randIndex]
        del(dataIndex[randIndex])

	


print dataIndex	
	
	
	


