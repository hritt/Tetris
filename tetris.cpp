#include<iostream>
using namespace std;
#include<math.h>//pow()
//#include<windows.h>
//#include<conio.h>
//#include<string>
#include<time.h>

//#define up
//#define down
//#define left
//#define right
//#define esc//

typedef struct point{
	int x;
	int y;
};
class square{
	point pt1;//private
	point pt2;
	point pt3;
	point pt4;
public:
	square(){};
	square(int pt1x,int pt1y,int pt2x,int pt2y,int pt3x,int pt3y,int pt4x,int pt4y);
	void move(char ch,bool stop);
	void change(int a,int &b,bool stop);
	void showw();
	void showb();
	void showwhite();
	void showblack();
	bool isexit();
	void marksquare();
	void shownext();
};
class frame{
	int score;
	int level;
public:
	frame();
	void begin();
	void initfirst(int pt1x,int pt1y,int pt2x,int pt2y,int pt3x,int pt3y,int pt4x,int pt4y,square &s);
	void init();
	square nextsquare(int x,int y);
	void showroom();
	void check();
}

square s[7][4];//一共7种，每种4个方向//注意全局与局部
bool room[15][10];//游戏空间

void go(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);//不懂?//x,y代表？
}
void color(int n_color)// 函数作用：设置输出的文本前景色和背景色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n_color);
}

square::square(int pt1x,int pt1y,int pt2x,int pt2y,int pt3x,int pt3y,int pt4x,int pt4y)
{
	pt1.x=pt1x;pt1.y=pt1y;
	pt2.x=pt2x;pt2.y=pt2y;
	pt3.x=pt3x;pt3.y=pt3y;
	pt4.x=pt4x;pt4.y=pt4y;
}
void square::move(char ch,bool &stop)
{
	square s1(pt1.x,pt1.y,pt2.x,pt2.y,pt3.x,pt3.y,pt4.x,pt4.y);
	switch(ch){
	case 'l':pt1.x=pt1.x-2;//x横坐标？y纵坐标？
			 pt2.x=pt2.x-2;
			 pt3.x=pt3.x-2;
			 pt4.x=pt4.x-2;
			 break;
	case 'd':pt1.x=pt1.x+2;
			 pt2.x=pt2.x+2;
			 pt3.x=pt3.x+2;
			 pt4.x=pt4.x+2;
			 break;
	case 'r':pt1.y=pt1.y+1;
			 pt2.y=pt2.y+1;
			 pt3.y=pt3.y+1;
			 pt4.y=pt4.y+1;
			 break;
	default:cerr<<"error!";
	}
	//边界处理//x横向为10个单位//y纵向15个单位
	if(pt1.x<0||pt1.x>18||pt2.x<0||pt2.x>18||pt3.x<0||pt3.x>18||pt4.x<0||pt4.x>18)
		*this=s1;//this?
	if(pt1.y>14||pt2.y>14||pt3.y>14||pt4.y>14||/*...*/)
	{
		*this=s1;
		stop=true;//停止
	}
	if(ch='l'||ch='r')
		stop=false;//取消按左右键发生重叠时发生停留现象
}
void square::change(int a,int &b,bool stop)
{
	square s1(pt1.x,pt1.y,pt2.x,pt2.y,pt3.x,pt3.y,pt4.x,pt4.y);
	int x=pt1.x;
	int y=pt1.y;
	b=(b+1)%4;
	*this=s[i][j];//...下面开始晕了
	if(pt1.x<x)
	{
		int i=x-pt1.x;
		...
	}
	if(pt1.y<y)
	{
		int j=y-pt1.y;
		...
	}
	if(pt1.x<0||pt1.x>18||pt2.x<0||pt2.x>18||pt3.x<0||pt3.x>18||pt4.x<0||pt4.x>18)
	{
		*this=s1;
		b--;//why??
	}

	if(pt1.y>14||pt2.y>14||pt3.y>14||pt4.y>14||/*...*/)
	{
		*this=s1;
		b--;
		stop=true;
	}
}
bool square::isexit()//不明白??
{
	if(room[pt1.y][pt1.x/2]==1||room[pt2.y][pt2.x/2]==1||room[pt3.y][pt3.x/2]==1||room[pt4.y][pt4.x/2]==1)
		return true;
	else
		return false;
}
void square::showb()
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),"■",2,0,0);//不懂?
}
void square::showw()
{
	color(0x02);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),"□",2,0,0);
	color(0x0c);
}
void square::showblack()
{
	go(pt1.x,pt1.y);
	showb();
	go(pt2.x,pt2.y);
	showb();
	go(pt3.x,pt3.y);
	showb();
	go(pt4.x,pt4.y);
	showb();
}
void square::showwhite()
{
	//color(0x02);why?
//	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),"□",2,0,0);
	//color(0x0c);
	go(pt1.x,pt1.y);
	showw();
	go(pt2.x,pt2.y);
	showw();
	go(pt3.x,pt3.y);
	showw();
	go(pt4.x,pt4.y);
	showw();
}
void square::marksquare()//当方块停留时，把方块四个点的坐标在游戏空间room[][]中相应位置标记为1
{
	for(int i=0;i<15;i++)
		for(int j=0;j<10;j++)
			if((pt1.x==2*j&&pt1.y==i)||(pt2.x==2*j&&pt2.y==i)||(pt3.x==2*j&&pt3.y==i)||(pt4.x==2*j&&pt4.y==i))
				room[i][j]=1;
}
void square::shownext()
{
	color(0xb2);
	for(int i=0;i<4;i++)
	{
		go(26,3+i);//??
		cout<<"□□□□";
	}
	color(0xbc);
	go(pt1.x+26,pt1.y+3);//???
	showw();
	go(pt2.x,pt2.y);
	showw();
	go(pt3.x,pt3.y);
	showw();
	go(pt4.x,pt4.y);
	showw();
}
void frame::initfirst(int pt1x,int pt1y,int pt2x,int pt2y,int pt3x,int pt3y,int pt4x,int pt4y,square &s)
{
	s.pt1.x=pt1x;s.pt1.y=pt1y;
	s.pt2.x=pt2x;s.pt2.y=pt2y;
	s.pt3.x=pt3x;s.pt3.y=pt3y;
	s.pt4.x=pt4x;s.pt4.y=pt4y;
}
void frame::init()
{
	initfirst(2,1,0,0,2,0,0,1,s[0][0]);//修改具体参数
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//■■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);//■
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);//■
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■■■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//    ■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■■■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//  ■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■■■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//  ■■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//■■

	initfirst(2,1,0,0,2,0,0,1,s[0][0]);
	initfirst(2,1,0,0,2,0,0,1,s[0][1]);
	initfirst(2,1,0,0,2,0,0,1,s[0][2]);//■■
	initfirst(2,1,0,0,2,0,0,1,s[0][3]);//  ■■
}
frame::frame()
{
	score=0;
	level=1;
	system("color bc");
	system("title tetris by hritt");
	//color()设置前景色、背景色//没写//上面system已经实现了
	//--接下来写界面--
	//go()将光标移到制定位置//没影响
	//下一个
	//分数
	//等级
}
frame::begin()
{
	init();//需要吗？
	square sq,sq2;
	score=0;//已经初始化了吧？
	for(int i=0;i<15;i++)//初始化不该放在这吧？
		for(int j=0;j<10;j++)
			room[i][j]=0;
	srand((unsigned)time(NULL));
	int m=rand()%7;
	int n=rand()%4;
	sq=s[m][n];
	while(1)
	{
		bool stop=false;
		int x=rand()%...
		int y=...
		sq2=nextbock(x,y);
		go(20,21);
		showroom();
		if(sq.isexit())
		{
			go(4,5);
			cout<<"失败!";
			exit(-1);//-1,0,1
		}
		while(stop==false)
		{
			showroom();
			sq.showblack();
			int delay=10*level;//???
			int max_delay=100;
			char ch='\0';
			while(delay<max_delay)
			{
				if(_kbhit())//??为什么以这种形式来获取键盘
				{
					intkey=_getch();
					switch(key)
					{
					case up://up??1,2,3,4??
						sq.showwhite();
						sq.change(i,j,stop);
						sq.showblack();
						break;
					case down:
						ch='d';//??
						delay=max_delay;
						break;
					case left:
						ch='l';
						sq.showwhite();
						sq.move(ch,stop);
						sq.showblack();
						break;
					case right:
						ch='r';
						sq.showwhite();
						sq.move(ch,stop);
						sq.showblack();
						break;
					case esc:
						exit(-1);
						break;
					}
				}
				_sleep((11-level)*1);//??why *1
				delay++;
			}
			if(ch='d')
			{
				sq.showwhite();
				sq.move(ch,lark);
				sq.showblack();
			}
		}
		if(stop==true)
		{
			sq.marksquare();
		}
		check();//接下来几句需要吗
		sq=sq2;
		m=x;
		n=y;
	}
}
square frame::nextsquare(int x,int y)
{
	square sq=s[x][y];
	sq.shownext();
	return sq;
}
void frame::showroom()
{
	go(0,0);
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(scrop[i][j]==0)
			{
				color(0x02);
				square::showwhite();
			}
			else
			{
				color(0x03);
				square::showblack();
			}
		}
		go(0,i+1);
	}
	go(0,0);
	color(0x0c);
}
void frame::check()//销行
{
	bool mark=1;
	int line=0;
	int line_marked[4]={0,0,0,0};//line_marked用于记录游戏空间中被全部标记的某一行的行号，（即需要被消去的行的行号）
	int kai=0;                   //s用于记录line_marked中当前被标记的个数
	//检查哪些行需要消去
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<1;j++)
		{
			if(room[i][j]==0)
				mark=0;
		}
		if(mark==1)
		{
			line++;
			line_marked[kai++]=i;
		}
		mark=1;
	}
	if(kai>0)
		score=score+pow(2,kai);
	go(26,10);
	color(0xbc);
	cout<<" "<<score;//打印分数
	color(0x00);
	int dis=line;
	//取消前闪烁
	for(int goline=0;goline<kai;goline++)
	{
		color(0x04);
		go(0,line_marked[goline]);
		for(int s=0;s<10;s++)
			cout<<"■";
		_sleep(100);//???
		color(0x0d);
		go(0,line_marked[goline]);
		for(s=0;s<10;s++)
			cout<<"■";
		_sleep(100);
	}
	//销行前闪烁
	kai=0;
	//销行
	for(int k=1;k<dis;k++)
	{
		for(int p=line_marked[kai++];p>=1;p--)
			for(int q=0;q<10;q++)
				room[p][q]=room[p-1][q];
		for(int h=0;h<10;h++)
			room[0][h]=0;
	}
	//销行
	if(score/100+1>level)
	{
		level=score/100+1;
		color(0xbc);
		go(26,13);
		cout<<"等级:"<<level;
	}
	if(level>9)
	{
		go(4,5);
		cout<<"恭喜，通关了!";
		exit(-1);
	}
}

int main()
{
	frame f;
	f.begin();
	return 0;
}
