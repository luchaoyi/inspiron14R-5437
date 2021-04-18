#BB内， m条指令的依赖DAg
def Build_DAG(Insts, m):
    DAG D = {Nodes:[], Edges:[], Label:[], Roots:[]}
    for j = 1 to m:
        D.Nodes.append(j)
        ConfSet = []
        for k = 1 to j-1:
            if Conflict(Inst[j], Inst[k]):
                ConfSet.append(k)
        #起点之一
        if ConfSet.empty:
            D.Roots.append(j)
        else:
            for k in ConfSet:
                D.Edges.append((k,j))
                D.Label[(k,j)] = Lantency(Insts[k],1, Insts[j], IssuLantency);

