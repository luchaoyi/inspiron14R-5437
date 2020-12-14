
function path = DijkstraPlan(position,signcan)

% position :节点位置
% signcan	   :节点间是否可达


[n,m] = size(signcan)

%initial cost mat
cost = ones(n,m)*10000;

for i=1:n
	for j=1:m
		if signcan(i,j) == 1
			cost(i,j) = sqrt(sum((position(i,:)- position(j,:)).^2));
		end
	end
end


dist = cost(1,:);
s=zeros(size(dist));

s(1) = 1;dist(1) = 0;

path = zeros(size(dist));

path(1,:) = 1;


for num = 2:n

	mindist = 10000;

	for i=1:length(dist)
		if s(i) == 0  %已经到达点排除
			if dist(i) < mindist
				mindist = dist(i)
				u=i;
			end
		end
	end

	s(u) = 1;
	
	for w = 1:length(dist)
		if s(i) == 0
			if dist(u) + cost(u,w) < dist(w)
				dist(w) = dist(u)+cost(u,w);

				path(w) = u;
			end
		end
	end
end


