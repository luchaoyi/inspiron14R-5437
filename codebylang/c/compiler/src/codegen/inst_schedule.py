#简单调度 失败则增大Cycle
Cycle = 1
Ready = leaves of D  #存放的是当前Cycle可以调度的指令，及其前置依赖已经解除
Active = [] #存放已经被调度的节点, 随着Cycle时间的增加Active内的指令执行完成会被移除

while(Ready U Active != []):
    for op in Active:
        # 满足此条件则可以调度依赖op的op即op的后继者们
        if S(op) + delay(op) < Cycle:
            remove op from Active
            for s in [sucessors of op in D]:
                if s is ready
                    add s to Ready
    if Ready !=[] :
        remove an op from Ready   #Ready里面都是可以调度的指令，调度哪一个取决于优先级，因此Ready是一个优先级队列
        S(op) = Cycle
        add op to Active 
    Cycle = Cycle + 1

#调度长度L(S) = max(S(n) + delay(n))

#----------------------------------------
#虎书 迭代模调度
#失败时尝试n*c次后增大Cycle
#----------------------------------------
c = 3 
for T=Tmin : +INF:
    Budget = n * c  #不能顺利调度时一个周期T最多尝试 n*c次
    for i = 1 to n:
        LastTime[i] = 0     #最近一次指令i的调度时间
        SchedTime[i] = none #指令调度时间
    while Budget > 0 and 有未调度的指令:
        Budget -= 1
        令h是具有最高优先级的未调度指令

        th_min = 0;
        for p in precessor(h):
            if SchedTime[p] != none:  #h的前驱已经调度
                th_min = max(th_min, SchedTime[p] + Delay(p, h)) #p调度之后的Delay(p,h)个时刻h才能调度
        #考察h所有前驱，th_min是最早可以调度h的时刻, h被调度在th_min后的T个时刻的最早满足m约束的槽位
        for t = th_min to th_min + T -1:
            if SchedTime[h] != none:
                if 没有资源冲突:  #数据依赖已经满足，检查资源约束
                    SchedTime[h] = t

#->注意：h没有调度成功在T下会删除有资源冲突的已经调度指令进行不同尝试, 而不是直接增大T
#->这是一种回
#调度失败时强行调度h为SchedTime[h] = max(thmin, 1 + LastTime[h])
#并将h有资源冲突的指令消除重新调度,已经重新调度h的后继指令
        if SchedTime[h] = none: #指令h调度失败
            SchedTime[h] = max(thmin, 1 + LastTime[h])
        LasrTime[h] = SchedTime[h]

        # h不能调度则将h后继已经调度的指令(上一轮次尝试的调度)置为未调度
        for h的每一个后继s：
            if SchedTime[s] != none：
                if SchedTime[h] + Delay(h, s) > SchedTime[s]:
                    SchedTime[s] = none
        #将h有资源冲突的指令置为未调度
        while 当前有资源冲突:
            令s是除h外涉及资源冲突的指令
            SchedTime[s] = none 
        
    if 所有指令已经调度:
        RegisterAlloc()
        if 无寄存器溢出:
            return 一个调度成功的循环
