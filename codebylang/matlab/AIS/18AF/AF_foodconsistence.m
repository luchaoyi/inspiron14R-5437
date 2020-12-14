function [Y]=AF_foodconsistence(X)
%浓度函数评价解的优劣度
fishnum=size(X,2);
for i=1:fishnum
    Y(1,i)=sin(X(1,i))/X(1,i)*sin(X(2,i))/X(2,i);   
end

