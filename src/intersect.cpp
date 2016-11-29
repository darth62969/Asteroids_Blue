// Returns a Vertex indicating where the two line segments intersect.
// The line segments are v1 to v2 and v3 to v4.
Vertex intersect(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	float ua_num = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
	float den = ((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

	float ub_num = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));

	float ua = ua_num / den;
	float ub = ub_num / den;

	Vertex v;
	v.x = -100;
	v.y = -100;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		v.x = v1.x + ua * (v2.x - v1.x);
		v.y = v1.y + ua * (v2.y - v1.y);
	}

	return v;
}