# include <udf.h>
# include <math.h>
DEFINE_PROFILE(minlet345, thread, position) 
{
face_t f; 
real t = CURRENT_TIME;
real p;
if (t>=0.1 && t<=0.35)
{p=(0.2*sin((t+0.0875)*2/0.25*M_PI)+0.3)*0.0025*0.0025*M_PI*1060;}
else if (t>=0.85 && t<=1.1)
{p=(0.2*sin((t+0.0875)*2/0.25*M_PI)+0.3)*0.0025*0.0025*M_PI*1060;}
else
{p=0.1*0.0025*0.0025*M_PI*1060;}
begin_f_loop(f, thread)
{
F_PROFILE(f, thread, position) = p;
} 
end_f_loop(f, thread)
}
