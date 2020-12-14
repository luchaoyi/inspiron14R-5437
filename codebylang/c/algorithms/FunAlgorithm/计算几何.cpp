//判断点在矩形区域内
bool IsPointInRect(const Rect& rect,const Point& p)
{
	//不用考虑坐标原点，坐标轴方向
	//     .
	//. |  .  | .
	//	   .
	double xr=(p.x-rect.p1.x1)*(p.x-rect.p2.x);
	double yr=(p.y-rect.p1.y)*(p.y-rect.p2.y);

	return (xr<0.0)&&(yr<0.0);
}
//点与圆
bool IsPointInCircle(const Point& p,const Circle& c)
{
	return (PointDistance(p,c)<c.radius);
}

double PointDistance(const Point& p1,const Point& p2)
{
	return sqrt((p1.x-p2.x)^2+(p1.y-p2.y)^2);
}

//向量差积 x1*y2-x2*y1  P×Q > 0   右手法则 x-->y，Q在P的逆时针方向
//叉积值=向量组成的平行四边形的面积

double CrossProduct(...){;}
double DotProduct(...){;}

//...
