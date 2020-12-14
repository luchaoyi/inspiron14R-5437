function [S,R]=Metropolis(S1,S2,D,T)


% R2-R1<0 better p=1; else p=exp(-dr/T);
R1=pathLength(D,S1);
R2=pathLength(D,S2);

dc=R2-R1;

	if dc<0
		S=S2;
		R=R2;
	elseif exp(-dc/T)>=rand
		S=S2;
		R=R2;
	else %Refuse to accept
		S=S1;
		R=R1;
	end
end