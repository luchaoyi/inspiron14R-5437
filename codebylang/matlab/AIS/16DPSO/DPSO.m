 
   
   DPSO 思想： 设置粒子探测外界环境变化动态调整
   响应为按一定比例随机选择粒子初始化
   
    % 变化超过阈值，重新初始化
    if abs(oFitness - nFitness)>1
        index=randperm(20);
        pop(index(1:10),:)=unidrnd(501,[10,2]);
        V(index(1:10),:)=unidrnd(100,[10,2])-50;
    end
    
    APSO: 响应方式是如果粒子if当前位置fitness>个体最优位置fitness以当前位置更新个体最优位置
    
    EPSO:检测全局最优值变化
    
    TDPSO：引入蒸发系数，粒子逐渐遗忘自身记忆，适应动态环境
    		T->[0,1], T*Pi(k) 使Pi(k) 即个体最优值逐渐减小遗忘 
    
