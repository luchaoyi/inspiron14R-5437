x=-1:0.1:1;
y1=sin(x);
y2=cos(x);
plot(x,y1,'r',x,y2,'g');
gtext('look') %鼠标指定位置显示说明文字
legend('sin','cos');%依据绘图先后顺序，标识曲线含义,用以区分不同曲线.

figure 
%plot3 三维曲线
t=0:pi/50:8*pi;
x=sin(t);
y=cos(t);
z=t;
plot3(x,y,z)
%mesh三维网格曲面

figure
[X,Y]=meshgrid(x,y); %根据x.y变化范围步长生成二维网格,X矩阵表示X轴变化，横向变换，对应位置的Y是同一个X.Y矩阵表示X变化
R=sqrt(X.^2+Y.^2)+eps;%+eps避免div 0 error,数值计算中需要注意避免div 0 
Z=sin(R)./R;
mesh(X,Y,Z)
%surf三维阴影曲面

figure
surf(X,Y,Z)
