# include <udf.h>
# include <math.h>
# include <mem.h>
# include <dynamesh_tools.h>
DEFINE_GRID_MOTION(fsi,domain,dt,time,dtime) 
{
Thread *tf = DT_THREAD(dt); 
face_t f;
Node *v;
real NV_VEC(dr);
int n;
real dp;
real x;
real y;
real z;
real r;
real gr;
real h;
real th;
real E;
float s;
float a;
float b;
SET_DEFORMING_THREAD_FLAG(THREAD_T0(tf));
begin_f_loop(f,tf)
{
	f_node_loop(f,tf,n)
{
	v=F_NODE(f,tf,n);
	s=CURRENT_TIME/CURRENT_TIMESTEP;
	a=s/69;
	b=s/138;
	x=NODE_X(v);
	y=NODE_Y(v);
	z=NODE_Z(v);
	/*node coordinate*/
	r=sqrt(y*y+z*z);
	/*current radius*/
	if (x<=-0.003 || x>=0.002)
	{gr=0.0025;
	 th=500000;}
	else if (x>-0.003 && x<0)
	{ gr=0.001875-0.000625*sin((x+0.0015)*M_PI/0.003);
	th=500000/(sqrt(1/(1+(0.000625*cos((x+0.0015)*M_PI/0.003)*0.000625*cos((x+0.0015)*M_PI/0.003)))));}
	else
	{gr=0.001875-0.000625*sin((x+0.001)*M_PI/0.002);
	th=500000/(sqrt(1/(1+(0.000625*cos((x+0.001)*M_PI/0.002)*0.000625*cos((x+0.001)*M_PI/0.002)))));}
	h=0.003-gr;
        /*geometry*/
	E=th*((r+h)*(r+h)-r*r)/(1.5*r*r);
	/*young modulus*/
        if (b==(int)b)
	{F_UDMI(f,tf,1)=F_P(f,tf);
         F_UDMI(f,tf,0)=F_UDMI(f,tf,0);
        dp=(F_P(f,tf)-F_UDMI(f,tf,0))*(r+h)/(E*r);}
	else if (a==(int)a)
	{F_UDMI(f,tf,0)=F_P(f,tf);
         F_UDMI(f,tf,1)=F_UDMI(f,tf,1);
	dp=(F_P(f,tf)-F_UDMI(f,tf,1))*(r+h)/(E*r);}
	else
	{F_UDMI(f,tf,0)=F_UDMI(f,tf,0);
         F_UDMI(f,tf,1)=F_UDMI(f,tf,1);
         dp=0;}
	NV_D(dr, =, 0, y*dp, z*dp);
	/*displacement vector*/
	if (NODE_POS_NEED_UPDATE (v))
	/* update node position */
	{
		NODE_POS_UPDATED(v);
		NV_V(NODE_COORD(v), +=, dr);
        /* node coordinate = node coordinate + dr */
    }
}
	Update_Face_Metrics (f,tf);
}
end_f_loop(f,tf);
}
