

%{

单纯形法：Ndim空间广义三角形

init 三角形

最佳点 次佳点 最差点

B G W

M = B+G/2 良边的中点

R :反射点 R=M+(M+W) = 2M - W


if R min 则沿R方向是正确的
	则在延伸一点 E = 2R-M
	拓展移动
if R == W
	则 或许 M更小 但还要构成三角形
	所以考率 W-->M  M-->R 选取 c1,c2一个较小的c中点
	收缩移动

	if 选取的C不小于W
		则应向B收缩
		1/2




鲍威尔方法是坐标上升法
改变对每一维求最小值
改变此维大小坐标上升


%}