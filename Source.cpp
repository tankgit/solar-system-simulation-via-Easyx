#include<graphics.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>

#define MAX_W 1000
#define MAX_H 1000
#define MAX_NUM_PLANET 10
#define PI 3.1415926535
#define EARTH_Y 365

typedef struct star{
	TCHAR* name;
	int x;
	int y;
	int r;
	int orbit;
	double period;
	int color;
	struct star *center;
}star;

star *sun = (star*)malloc(sizeof(star));
star *p[MAX_NUM_PLANET];

void initStar();
void setting(int* o,int* s,int* p,int* n,int* f,int* b,char c);
double syncPeriod();
void calculate(star *s, int t);
void deploy(star *s);
void showName(int n);
void showOrbit(int s);
void hint();
void speedBar(int* s);

int main(){
	initgraph(MAX_W, MAX_H);
	initStar();
	double sync = syncPeriod();
	srand(time_t(0));
	int time=rand()%+100;
	int o = 1, s = 60, ps = 0, n=1,f=0,b=0;
	char cmd;
	while (1){
		hint();
		if (_kbhit()){
			cmd = _getch();
			if (cmd == 'q'){
				closegraph();
				return 0;
			}
			setting(&o, &s, &ps, &n,&f,&b, cmd);
		}
		BeginBatchDraw();
		deploy(sun);
		for (int i = 0; i < MAX_NUM_PLANET; i++)
		{
			calculate(p[i], time);
			deploy(p[i]);
		}
		showName(n);
		showOrbit(o);
		time = time >=  sync? 1 : time+1;
		if (f){
			f = 0;
			time += 1 * EARTH_Y;
		}
		if (b){
			b = 0;
			time -= 1 * EARTH_Y;
		}
		if (ps == 1)
		while (ps)
		{
			ps = _getch() - 112;
			if (ps+112 == 'q'){
				closegraph();
				return 0;
			}
		}
		speedBar(&s);
		FlushBatchDraw();
		Sleep(s);
		cleardevice();
	}
	EndBatchDraw();
	return 0;
}

void initStar()
{
	sun->name = _T("Sun");
	sun->x = MAX_W / 2;
	sun->y = MAX_H / 2;
	sun->r = 20;
	sun->orbit = 0;
	sun->period = 0;
	sun->color = 0x0000ff;
	sun->center = NULL;
	for (int i = 0; i < MAX_NUM_PLANET; i++)
	{
		p[i] = (star*)malloc(sizeof(star));
		p[i]->x = 0;
		p[i]->y = 0;
		p[i]->orbit = 40 * (i + 1);
		p[i]->center = sun;
	}
	p[0]->name=_T("Mercury");
	p[0]->r = 4;
	p[0]->period = 58.5;
	p[0]->color = 0xaabb00;

	p[1]->name=_T("Venus");
	p[1]->r = 4;
	p[1]->period = 225.7;
	p[1]->color = 0x726392;

	p[2]->name=_T("Earth");
	p[2]->r = 6;
	p[2]->period = EARTH_Y;
	p[2]->color = 0xa82bc1;

	p[3]->name=_T("Mars");
	p[3]->r = 5;
	p[3]->period = 1.9*EARTH_Y;
	p[3]->color = 0x2fd01f;

	p[4]->name=_T("Jupiter");
	p[4]->r = 12;
	p[4]->period = 11.8*EARTH_Y;
	p[4]->color = 0x8b2cf1;

	p[5]->name=_T("Saturn");
	p[5]->r = 10;
	p[5]->period = 29.5*EARTH_Y;
	p[5]->color = 0x2ddbba;

	p[6]->name=_T("Uranus");
	p[6]->r = 13;
	p[6]->period = 84*EARTH_Y;
	p[6]->color = 0xfba8d2;

	p[7]->name=_T("Neptune");
	p[7]->r = 11;
	p[7]->period = 164.7*EARTH_Y;
	p[7]->color = 0x20bff;

	p[8]->name=_T("Moon");
	p[8]->r = 2;
	p[8]->period = 30;
	p[8]->color = 0x20bff;
	p[8]->center = p[2];
	p[8]->orbit = 11;

	p[9]->name=_T("U-1");
	p[9]->r = 4;
	p[9]->period = 300;
	p[9]->color = 0x20bff;
	p[9]->center = p[6];
	p[9]->orbit = 20;

}

void setting(int* o, int* s, int* p, int* n,int* f,int* b,char c)
{
	switch (c){
		case 'o':*o = !*o; break;
		case 'p':*p = !*p; break;
		case 'u':*s = *s<=0?0:*s-2; break;
		case 'd':*s = *s>=120?120:*s+2; break;
		case 'n':*n = !*n; break;
		case 'f':*f = !*f; break;
		case 'b':*b = !*b; break;
	}
}

double syncPeriod()
{
	double t=1;
	for (int i=0; i < MAX_NUM_PLANET; i++)
		t *= p[i]->period;
	return t;
}

void calculate(star *s, int t){
	s->x = s->center->x + (int)(s->orbit*cos(t*2*PI/s->period));
	s->y = s->center->y + (int)(s->orbit*sin(t*2*PI/s->period));
}

void deploy(star *s){
	setfillcolor(s->color);
	solidcircle(s->x, s->y, s->r);
}

void showName(int n)
{
	if (n)
	{
		for (int i = 0; i < MAX_NUM_PLANET; i++)
		{
			settextcolor(p[i]->color);
			LOGFONT f;
			gettextstyle(&f);     
			f.lfItalic = true;
			f.lfHeight = 3;
			f.lfWidth = 0;
			settextstyle(&f);
			outtextxy(p[i]->x,p[i]->y, p[i]->name);
		}
		settextcolor(sun->color);
		outtextxy(sun->x, sun->y, sun->name);
	}
}

void showOrbit(int s)
{
	if (s){
		setlinestyle(PS_SOLID,1);
		for (int i = 0; i < MAX_NUM_PLANET; i++)
		{
			setlinecolor(p[i]->color);
			circle(p[i]->center->x, p[i]->center->y, p[i]->orbit);
		}
	}
}

void hint()
{

	LOGFONT f;
	gettextstyle(&f);
	f.lfItalic = false;
	settextstyle(&f);
	settextcolor(0xffffff);

	TCHAR t[] = _T("Solar System");
	outtextxy(MAX_W/2-40, 15, t);

	TCHAR a[] = _T("c Tank 2016  derektanko@gmail.com");
	outtextxy(10, MAX_H-25, a);

	setlinecolor(0xffffff);
	setlinestyle(PS_SOLID, 2);
	circle(14, MAX_H - 16, 6);

	TCHAR o[] = _T("O: Show/Hide orbits");
	outtextxy(10, 10, o);

	TCHAR n[] = _T("N: Show/Hide names");
	outtextxy(10, 30, n);

	TCHAR p[] = _T("P: Pause/Play");
	outtextxy(10, 50, p);

	TCHAR s[] = _T("U/D: +/- Speed");
	outtextxy(10, 70, s);

	TCHAR q[] = _T("Press \"Q\" to quit");
	outtextxy(MAX_W-120, 10, q);

	TCHAR fb[] = _T("F/B: +/- 10 years");
	outtextxy(10, 110, fb);


	setlinecolor(0xffffff);
	setlinestyle(PS_SOLID, 2);
	rectangle(5, 5, 164, 134);
}

void speedBar(int* s)
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfItalic = false;
	settextstyle(&f);
	settextcolor(0x7777ff);
	TCHAR d[] = _T("-|");
	outtextxy(10, 90, d);
	TCHAR u[] = _T("|+");
	outtextxy(149, 90, u);
	setlinecolor(0x7777ff);
	line(17, 99, 149, 99);
	setfillcolor(0x7777ff);
	solidcircle(166-(*s + 23), 99, 5);
}