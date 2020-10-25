#define SHOW_CONSOLE
#include"graphics.h"
#include<iostream>
#include <time.h>
#include <vector>
#include <cmath>
using namespace std;
mouse_msg msg;
void getposition()
{
	msg = getmouse();
	cout << "x: " << msg.x << "y: " << msg.y << endl;
	
}
class game
{
private:
	    const int W = 900;
	    const int H = 480;
		bool Jump = false;//跳跃开关
	    PIMAGE back = newimage(W, H);//这里需要提前预设的原因是这个是间接获取并不是直接打开图像，需要提前设定好长宽
		PIMAGE temp = newimage();//创建临时图像
        PIMAGE player_ = newimage();
		PIMAGE wq = newimage();
		
public:
	game()
	{
		initgraph(W, H);
		setcaption("随便");
		setinitmode(INIT_ANIMATION);// 把绘图更新模式设置为手动，仅调用delay_fps/delay_ms等函数时才刷新，避免闪烁
		setbkcolor(WHITE);
		randomize();// 随机数初始化，如果需要使用随机数的话
		getimage(temp, "01.jpg");
		int tempWidth = getwidth(temp), tempHeight = getheight(temp);
		putimage(back, 0, 0, W, H, temp, 0, 0, tempWidth, tempHeight);
		delimage(temp);
		temp = NULL;
		getimage(player_, "player.jpg", 0, 0);
		getimage(wq, "wq1.jpg", 0, 0);
	}
	~game()
	{
		delimage(player_);
		delimage(wq);
		delimage(back);
	}
	void player(int px,int py)
	{	
		putimage_withalpha(NULL, player_, px, py);	
		putimage_withalpha(NULL, wq, px + 40, py);

	}
	void walk_p(int *px, int *py)//用于改变坐标
	{
		int x=0;
		if (kbhit())
			x = getch();
		cout <<"Player_x"<<*px <<"Player_y"<<*py<< endl;
		switch (x)
		{
		case 119://w
			break;
		case 97://a
			*px -= 15;
			break;
		case 115://s
			break;
		case 100://d
			*px += 15;
			break;
		case 106://j
			break;
		case 32://按空格键跳跃，以及跳跃的实现
			if (!Jump) {
				Jump = true;
				for (int i = 330; i >= 230; i -= 10) {
					walk_p(px, &i);
					drew(*px, i);
				}
				for (int i = 230; i <= 330; i += 10) {
					walk_p(px, &i);
					drew(*px, i);
					Jump = false;
				}
			}
			break;
		}
	}
	void drew(int px,int py=330)
	{
		putimage(0, 0, back);
		player(px, py);
		delay_fps(60);
		cleardevice();
	}
	void gameloop()
	{
		int px=0, py=330;
		while(is_run())
		{
			// todo: 逻辑更新
			walk_p(&px, &py);
			// todo: 图形更新
			drew(px,py);
			//清屏，重新在新的位置绘图图像	
		}
	}
};
int main()
{
	game g;
	g.gameloop();
	//关闭图形界面
	closegraph();
	return 0;
}


