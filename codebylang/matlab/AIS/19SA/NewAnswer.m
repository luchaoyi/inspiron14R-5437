function S2 = NewAnswer(S1)

N=length(S1);

%rand select position exchange
S2=S1;

a=round(rand(1,2)*(N-1)+1);%round Four to five homes in

S2(a(1))=S1(a(2));
S2(a(2))=S1(a(1));


end

