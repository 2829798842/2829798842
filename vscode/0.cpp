#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>  
#include<windows.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //用来检测按键的点击事件
POINT p;
HWND h=GetForegroundWindow();
int o,xunwen,oo,ooo=0;//由于改用多线程，为了让鼠标交互的信息有效执行，采用全局变量，可以在各个线程中互相传递 
int n[10],m[10],num=0;//设置数组长度为10，这个数字10跟下面的二级指针数组对应，结合后来的鼠标交互操作，十个刚好  
static int order=0;//一个静态变量，使得导入的矩阵编号清晰 
float scale = 0.01; // 缩小比例，后弃用 
float **a[10];//运用二重指针数组，避免二维数组做函数参数时长度未定情况 ;但是要先申请空间

pthread_cond_t condition1 = PTHREAD_COND_INITIALIZER;//条件变量 
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁
pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER;//条件变量 
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁
pthread_cond_t condition3 = PTHREAD_COND_INITIALIZER;//条件变量 
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁
pthread_cond_t condition4 = PTHREAD_COND_INITIALIZER;//条件变量 
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁
//这里选择了多个互斥锁，避免在不适当的地方搞混了，以及同时占用（虽然显然不会） 

void restore(float *p[],int x,int y); //储存矩阵函数 
void input();
void output(float **c,int p,int q);
void transform();
void add();
void multiply();
float determinant(float **c,int n);//计算行列式，以及伴随矩阵的余子式 
float **adjoint(float **c,int n);//计算伴随矩阵 
void setjindutiao(int p);//进度条，初始加载用，有本地时间，可以及时注意 
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);//跟鼠标钩子相关 
void *jz(void *arg);//这是本来的main函数，后来改成多线程后，改用线程函数 

void restore(float *p[],int x,int y){
	int i,j;
	printf("\n请点击任意处继续");
	pthread_cond_signal(&condition3);// 发送信号	
	pthread_mutex_lock(&mutex3);
	pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
	pthread_mutex_unlock(&mutex3);
	if(ooo==1) {
		ooo=0;
		return ;
	}
	system("cls");
	printf("是否保存该结果为新的矩阵:\n\n是:点击我\n\n否:点击我\n");
	pthread_cond_signal(&condition2);// 发送信号
	
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&condition2, &mutex2); // 等待条件变量
	pthread_mutex_unlock(&mutex2);
	
	if(!xunwen) return;
	else{
		printf("请选择保存的数组编号\n");
		int ord;
		printf("\n\n\n\n\n0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
		pthread_cond_signal(&condition4);// 发送信号
		pthread_mutex_lock(&mutex4);		pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
		pthread_mutex_unlock(&mutex4);
		ord=oo;
		free(a[ord]); 
		a[ord]=(float **)malloc(sizeof(float *)*x) ;//申请行空间 
		for(i=0; i<x;i++) {
			a[ord][i]=(float *)malloc(sizeof(float)*y);//申请列空间 
		}
		n[ord]=x,m[ord]=y;
		for(i=0; i<x; i++)
			for(j=0; j<y; j++)
				a[ord][i][j]=p[i][j];
	}
} 
void input() {
	int i,j;
	do{
		printf("请输入行数：");
		scanf("%d",&n[order]);
		if(n[order]<=0) printf("输入数据错误，请重新输入！！！\n");
	}
	while(n[order]<=0);
	do{
		printf("请输入列数：");
		scanf("%d",&m[order]);
		if(m[order]<=0) printf("输入数据错误，请重新输入！！！\n");
	}
	while(m[order]<=0);
	printf("请输入元素：\n");
	a[order]=(float **)malloc(sizeof(float *)*n[order]) ;//申请行空间
	for(i=0; i<n[order]; i++) {
		a[order][i]=(float *)malloc(sizeof(float)*m[order]);//申请列空间
		printf("第%d行：",i+1);
		for(j=0; j<m[order]; j++) {
			scanf("%f",&a[order][i][j]);//全局变量order所以输入的矩阵是顺序的 
		}
	}
	printf("\n第%d号矩阵已导入。\n",order);//及时报号，提醒矩阵位置 
	order++;
	if(order==10) order=0;//防止矩阵数量溢出 
}
void output(float **c,int p,int q) {
	int i,j;
	if(c&&p!=0&&q!=0)
	{
		for(i=0; i<p; i++) {
			printf("第%d行：",i+1);
			for(j=0; j<q; j++) {
				printf("%.1f ",c[i][j]);
			}
			printf("\n");
		}
	}
	else printf("不存在该矩阵！！！");
	printf("\n");
}
void transform() {
	int i,j;
	float b[m[num]][n[num]];
	for(i=0; i<n[num]; i++) {
		for(j=0; j<m[num]; j++) {
			b[j][i]=a[num][i][j];
		}
	}
	for(i=0; i<m[num]; i++) {//转置行数与列数互换
		for(j=0; j<n[num]; j++) {
			printf("%.1f ",b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	float *temp[m[num]];//指针数组，二维数组和指针数组可以互换，因为矩阵用的是二级指针，所以不能直接用二维数组导入，那就只能先二维数组和指针数组互换了，然后再在函数中传 
    for(int i = 0; i < m[num]; ++i)
        temp[i]=b[i];
	restore(temp,m[num],n[num]);
}
void add() {
	int i,j,ord;
	float c[n[num]][m[num]],d[n[num]][m[num]];
	printf("请输入将相加矩阵\n");
	printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
	pthread_cond_signal(&condition4);// 发送信号
	pthread_mutex_lock(&mutex4);	
	pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
	pthread_mutex_unlock(&mutex4);
	ord=oo;num=ord;
	if(!a[num]){
		printf("不存在该矩阵！！！");
		printf("\n请点击任意处继续");
		pthread_cond_signal(&condition3);// 发送信号	
		pthread_mutex_lock(&mutex3);
		pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
		pthread_mutex_unlock(&mutex3);
		return ;
	}
	for(i=0; i<n[num]; i++)
		for(j=0; j<m[num]; j++) {
			d[i][j]=a[num][i][j];
	}
	system("cls");
	printf("是否运用新的矩阵:\n\n是:点击我\n\n否:点击我\n");
	pthread_cond_signal(&condition2);// 发送信号
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&condition2, &mutex2); // 等待条件变量
	pthread_mutex_unlock(&mutex2);
	if(!xunwen){
		printf("请点击相加矩阵");
		printf("\n\n\n\n\n\n0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
		pthread_cond_signal(&condition4);// 发送信号
		pthread_mutex_lock(&mutex4);	
		pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
		pthread_mutex_unlock(&mutex4);
		ord=oo;
		if(m[ord]==m[num]&&n[ord]==n[num]){//检验合法性 
			num=ord;
			for(i=0; i<n[num]; i++) {
				for(j=0; j<m[num]; j++) {
					d[i][j]=a[num][i][j]+d[i][j];
				}
			}
		}
		else{
			printf("输入矩阵无法相加！！！");
			return ;
		}
	}
	else{
		printf("请输入元素：\n");
		for(i=0; i<n[num]; i++) {
			printf("第%d行：",i+1);
			for(j=0; j<m[num]; j++) {
				scanf("%f",&c[i][j]);
			}
		}
		for(i=0; i<n[num]; i++) {
			for(j=0; j<m[num]; j++) {
				d[i][j]=c[i][j]+d[i][j];
			}
		}
	}
	printf("相加后的矩阵为：\n");
	for(i=0; i<n[num]; i++) {
		printf("第%d行：",i+1);
		for(j=0; j<m[num]; j++) {
			printf("%.1f ",d[i][j]);
		}
		printf("\n");
	}
	float *temp[n[num]];
    for(int i = 0; i < n[num]; ++i)
        temp[i]=d[i];
	restore(temp,n[num],m[num]);
}
void multiply() {
	int i,j,k,r,ord;
	float c[m[num]][r],d[n[num]][r];
	printf("请输入将相乘矩阵\n");
	printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");	
	pthread_cond_signal(&condition4);// 发送信号
	pthread_mutex_lock(&mutex4);
	pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
	pthread_mutex_unlock(&mutex4);
	ord=oo;num=ord;
	if(!a[num]){
		printf("不存在该矩阵！！！");
		printf("\n请点击任意处继续");
		pthread_cond_signal(&condition3);// 发送信号	
		pthread_mutex_lock(&mutex3);
		pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
		pthread_mutex_unlock(&mutex3);
		return ;
	}
	system("cls");
	printf("是否运用新的矩阵:\n\n是:点击我\n\n否:点击我\n");
	pthread_cond_signal(&condition2);// 发送信号
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&condition2, &mutex2); // 等待条件变量
	pthread_mutex_unlock(&mutex2);
	if(!xunwen){
		printf("请输入相乘矩阵");
		printf("\n\n\n\n\n\n0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
		pthread_cond_signal(&condition4);// 发送信号
		pthread_mutex_lock(&mutex4);	
		pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
		pthread_mutex_unlock(&mutex4);
		ord=oo;
		if(m[num]==n[ord]){//矩阵相乘条件为左矩阵的列等于右矩阵的行，左列右行 
			r=n[ord];
			for(i=0; i<n[ord]; i++) {
				for(j=0; j<m[ord]; j++) {
					c[i][j]=a[ord][i][j];
				}
			}
		}
		else{
			printf("输入矩阵无法相乘！！！");
			printf("\n请点击任意处继续");
			pthread_cond_signal(&condition3);// 发送信号	
			pthread_mutex_lock(&mutex3);
			pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
			pthread_mutex_unlock(&mutex3);
			return ;
		}
	}
	else{
		printf("请输入列数：");
		scanf("%d",&r);
		printf("请输入元素：\n");
		for(i=0; i<m[num]; i++) {
			printf("第%d行：",i+1);
			for(j=0; j<r; j++) {
				scanf("%f",&c[i][j]);
			}
		}
	}
	for(i=0; i<n[num]; i++) {//但是输出为左行右列 
		for(j=0; j<r; j++) {
			for(k=0; k<m[num]; k++) {
				d[i][j]+=a[num][i][k]*c[k][j];//这里还是用了同济大学课本上的那种乘法运算，好写，虽然现实中我不用awa 
			}
		}
	}
	printf("相乘后的矩阵为：\n");
	for(i=0; i<n[num]; i++) {
		printf("第%d行：",i+1);
		for(j=0; j<r; j++) {
			printf("%.1f ",d[i][j]);
		}
		printf("\n");
	}
	float *temp[n[num]];
    for(int i = 0; i < n[num]; ++i)
        temp[i]=d[i];
	restore(temp,n[num],r);
} 
float determinant(float **c,int n) {//按第一行完全展开式计算|A|
	float det,t,**temp1;
	temp1=(float **)malloc(sizeof(float *)*(n-1));//为储存降阶矩阵开辟空间
	for(int p=0; p<n-1; p++) {
		temp1[p]=(float *)malloc(sizeof(float)*(n-1));
	}
	if(n==1) det=c[0][0];
	else if(n==2) {
		det=c[0][0]*c[1][1]-c[0][1]*c[1][0];//作为终止条件; 二阶矩阵直接计算 ;
	} else {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n-1; j++) {//记录第一行元素对应余子式的矩阵
				for(int k=0; k<n-1; k++) {
					temp1[j][k]=c[j+1][(k>=i)?k+1:k];//若列数小于i则不变;若列数大于等于i则向后移动一列;从而记录余子式的矩阵
				}
			}
			t=determinant(temp1,n-1);//递归计算
			if(i%2==0) {//判断余子式的正负;与第一行元素相乘;相加得行列式
				det+=c[0][i]*t;
			} else {
				det-=c[0][i]*t;
			}
		}
	}
	return det;
}
float **adjoint(float **c,int n) {//计算每一行每一列的每个元素所对应的余子式，组成A*
	float **temp2,**adj;
	if(n==2) {
		adj=(float **)malloc(sizeof(float *)*n);//为n阶伴随矩阵开辟空间
		for(int p=0; p<n; p++) {
			adj[p]=(float *)malloc(sizeof(float)*n);
		}
		adj[0][0]=a[num][1][1];
		adj[0][1]=(-1)*a[num][1][0];
		adj[1][0]=(-1)*a[num][0][1];
		adj[1][1]=a[num][0][0];
 
	} else {
		temp2=(float **)malloc(sizeof(float *)*(n-1));//为n-1阶矩阵开辟空间
		for(int p=0; p<n-1; p++) {
			temp2[p]=(float *)malloc(sizeof(float)*(n-1));
		}
		adj=(float **)malloc(sizeof(float *)*n);//为n阶伴随矩阵开辟空间
		for(int p=0; p<n; p++) {
			adj[p]=(float *)malloc(sizeof(float)*n);
		}
		for(int i=0; i<n; i++) {//每行
			for(int j=0; j<n; j++) {//每列
				for(int k=0; k<n-1; k++) {//n-1阶矩阵
					for(int t=0; t<n-1; t++) {
						temp2[k][t]=c[(k>=i)?k+1:k][(t>=j)?t+1:t];//剔除元素所在行与列之后的矩阵
					}
				}
				adj[j][i]=determinant(temp2,n-1);//计算代数余子式Aji为  转置  后的
				if((i+j)%2==1) {//判断符号(-1)^(i+j)
					adj[j][i]=-adj[j][i];
				}
			}
		}
	}
	return adj;
}

void *sb(void *arg){
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	//----------循环检测----------
	//pthread_cond_wait(&condition, &mutex); // 等待条件变量
	
	while(1) {                      			//循环检测
		pthread_mutex_lock(&mutex1);
		pthread_cond_wait(&condition1, &mutex1); // 等待条件变量
		pthread_mutex_unlock(&mutex1);

		//pthread_mutex_unlock(&mutex);
		while(1){
			Sleep(100);
			if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
				if((p.y>=0&&p.y<=65)&&(p.x>=0&&p.x<=100)){
					o=1;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=0&&p.y<=65)&&(p.x>=225&&p.x<=305)){
					o=2;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=0&&p.y<=65)&&(p.x>=450&&p.x<=530)){
					o=3;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=85&&p.y<=105)&&(p.x>=0&&p.x<=80)){
					o=4;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=85&&p.y<=105)&&(p.x>=225&&p.x<=305)){
					o=5;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=85&&p.y<=105)&&(p.x>=450&&p.x<=530)){
					o=6;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=120&&p.y<=140)&&(p.x>=0&&p.x<=80)){
					o=7;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=120&&p.y<=140)&&(p.x>=225&&p.x<=305)){
					o=8;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=120&&p.y<=140)&&(p.x>=450&&p.x<=530)){
					o=9;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
				else if((p.y>=160&&p.y<=180)&&(p.x>=0&&p.x<=80)){
					o=0;
					pthread_cond_signal(&condition1);// 发送信号
					break;
				}
			}
		}
	}
	return NULL; // 返回退出线程
}
void *rs(void *arg){
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	//----------循环检测----------
	//pthread_cond_wait(&condition, &mutex); // 等待条件变量
	
	while(1) {                      			//循环检测
		pthread_mutex_lock(&mutex2);
		pthread_cond_wait(&condition2, &mutex2); // 等待条件变量
		pthread_mutex_unlock(&mutex2);
		//pthread_cond_signal(&condition2);// 发送信号	
		//pthread_mutex_unlock(&mutex);
		while(1){
			Sleep(100);
			if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
				if((p.y>=85&&p.y<=105)&&(p.x>=0&&p.x<=90)){
					xunwen=1;
					pthread_cond_signal(&condition2);// 发送信号
					break;
				}
				if((p.y>=120&&p.y<=140)&&(p.x>=0&&p.x<=90)){
					xunwen=0;
					pthread_cond_signal(&condition2);// 发送信号
					break;
				}
			}
		}
	}
	return NULL; // 返回退出线程
}
void *dj(void *arg){
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	//----------循环检测----------
	//pthread_cond_wait(&condition, &mutex); // 等待条件变量
	
	while(1) {                      			//循环检测
		pthread_mutex_lock(&mutex3);
		pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
		pthread_mutex_unlock(&mutex3);
		
		//pthread_cond_signal(&condition2);// 发送信号	
		//pthread_mutex_unlock(&mutex);
		while(1){
			Sleep(100);
			if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
				pthread_cond_signal(&condition3);// 发送信号	
			}
		}
	}
	return NULL; // 返回退出线程
}
void *ma(void *arg){
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	//----------循环检测----------
	//pthread_cond_wait(&condition, &mutex); // 等待条件变量
	
	while(1) {                      			//循环检测
		pthread_mutex_lock(&mutex4);
		pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
		pthread_mutex_unlock(&mutex4);

		//pthread_mutex_unlock(&mutex);
		while(1){
			Sleep(100);
			if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
				if((p.y>=255&&p.y<=270)&&(p.x>=80&&p.x<=90)){
					oo=1;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=255&&p.y<=270)&&(p.x>=155&&p.x<=165)){
					oo=2;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=255&&p.y<=270)&&(p.x>=230&&p.x<=240)){
					oo=3;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=255&&p.y<=270)&&(p.x>=305&&p.x<=315)){
					oo=4;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=290&&p.y<=305)&&(p.x>=0&&p.x<=15)){
					oo=5;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=290&&p.y<=305)&&(p.x>=80&&p.x<=90)){
					oo=6;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=290&&p.y<=305)&&(p.x>=155&&p.x<=165)){
					oo=7;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=290&&p.y<=305)&&(p.x>=230&&p.x<=240)){
					oo=8;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=290&&p.y<=305)&&(p.x>=305&&p.x<=315)){
					oo=9;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
				else if((p.y>=255&&p.y<=270)&&(p.x>=0&&p.x<=15)){
					oo=0;
					pthread_cond_signal(&condition4);// 发送信号
					break;
				}
			}
		}
	}
	return NULL; // 返回退出线程
}
void *jz(void *arg)
{
	int ord,i,j,qaq=0;
	float z[10];
	float **bt[10];
	float *temp[100000];//这个是因为后面储存要用到指针数组，毕竟是在循环内部，只能预置了，但是因为代码限制，我无法预知矩阵的长宽，所以直接用一个比较大的值来替代了，当然，如果你非要搞个100 0000*100 0000的矩阵，那么不管我事了，自己改改行了 
	int flag=1;
	printf("请输入矩阵内容：\n(序号默认为0，最大为9)\n");
	input();//看着我的casio计算器，服了，词法分析，ε=(′ο｀*)))唉，那就这样吧 
			//啊众所周知，祖传代码会有注释吐槽 
	//pthread_cond_signal(&condition); // 发送信号
	do {
		system("cls");//清空界面，不然太乱了，至于历史么，case 9 
		pthread_cond_signal(&condition1);// 发送信号
		printf("初始化矩阵 		打印矩阵 		矩阵转置 \n\n");
		printf("矩阵相加 		矩阵相乘		矩阵求逆 \n\n");
		printf("伴随矩阵 		求行列式 		矩阵总览 \n\n");
		printf("退出程序\n\n请选择功能:(点击对应文字)(矩阵编号为0~9!!!)\n(由于代码限制，为了节省CPU占用，所以如果点击没用，请多次点击)\n");
		pthread_mutex_lock(&mutex1);
		pthread_cond_wait(&condition1, &mutex1); // 等待条件变量
		pthread_mutex_unlock(&mutex1);
		switch(o) {
			case 1:
				printf("请输入矩阵内容：\n(初始矩阵序号为0)\n");
				input();
				printf("\n请点击任意处继续");
				pthread_cond_signal(&condition3);// 发送信号	
				pthread_mutex_lock(&mutex3);
				pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
				pthread_mutex_unlock(&mutex3);
				break;
			case 2:
				printf("请选择输出矩阵\n");
				printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
				pthread_cond_signal(&condition4);// 发送信号
				pthread_mutex_lock(&mutex4);
				pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
				pthread_mutex_unlock(&mutex4);
				ord=oo;
				num=ord;
				printf("矩阵内容为：\n");
				output(a[num],n[num],m[num]);
				printf("\n请点击任意处继续");
				pthread_cond_signal(&condition3);// 发送信号	
				pthread_mutex_lock(&mutex3);
				pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
				pthread_mutex_unlock(&mutex3); 
				break;
			case 3:
				printf("请选择将要转置矩阵\n");
				printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
				pthread_cond_signal(&condition4);// 发送信号
				pthread_mutex_lock(&mutex4);
				pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
				pthread_mutex_unlock(&mutex4);
				ord=oo;num=ord;
				if(a[num]) printf("转置后的矩阵为：\n");
				else {
					printf("不存在该矩阵！！！");
					ooo=1;
				}
				transform();
				break;
			case 4:
				add();
				break;
			case 5:
				multiply();
				break;
			case 6:
				printf("请输入将求逆矩阵：\n");
				printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
				pthread_cond_signal(&condition4);// 发送信号
				pthread_mutex_lock(&mutex4);
				pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
				pthread_mutex_unlock(&mutex4);
				ord=oo;num=ord;
				bt[num]=adjoint(a[num],n[num]);
				z[num]=determinant(a[num],n[num]);//返回行列式的值
				if(z[num]==0||(m[num]!=n[num])) {//判断是否可逆
					printf("\n矩阵不可逆！！\n");
					printf("\n请点击任意处继续");
					pthread_cond_signal(&condition3);// 发送信号	
					pthread_mutex_lock(&mutex3);
					pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
					pthread_mutex_unlock(&mutex3);
					continue;
				} else {
					printf("逆矩阵为：\n");
					for(int i=0; i<n[num]; i++) {
						printf("第%d行：",i+1);
						for(int j=0; j<n[num]; j++) {
							bt[num][i][j]=bt[num][i][j]/z[num];//A逆==A*/|A|
							printf("%.1f ",bt[num][i][j]);//因为实现储存要用到指针数组，所以这里直接改变bt矩阵 
						}
						printf("\n");
					}
				}
    			for(int i = 0; i < n[num]; ++i)
        			temp[i]=bt[num][i];
				restore(temp,n[num],n[num]);
				break;
			case 7:
				printf("请输入将求伴随矩阵：\n");
				printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
				pthread_cond_signal(&condition4);// 发送信号
				pthread_mutex_lock(&mutex4);
				pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
				pthread_mutex_unlock(&mutex4);
				ord=oo;num=ord; 
				if(m[num]!=n[num]||m[num]==1)//伴随矩阵定义为方阵定义 ,矩阵求逆也是 
											 //伴随矩阵定义为余子式，所以至少是二阶方阵 
				{
					printf("该矩阵无法求伴随矩阵！！！\n");
					printf("\n请点击任意处继续");
					pthread_cond_signal(&condition3);// 发送信号	
					pthread_mutex_lock(&mutex3);
					pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
					pthread_mutex_unlock(&mutex3);
					continue;
				}	
				else{
					if(!a[num]){
						printf("不存在该矩阵！！！");
						printf("\n请点击任意处继续");
						pthread_cond_signal(&condition3);// 发送信号	
						pthread_mutex_lock(&mutex3);
						pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
						pthread_mutex_unlock(&mutex3);
						continue;
					}
					printf("伴随矩阵为：\n");
					bt[num]=adjoint(a[num],n[num]);
					output(bt[num],n[num],n[num]);
					for(int i = 0; i < n[num]; ++i)
        				temp[i]=bt[num][i];
					restore(temp,n[num],n[num]);
				}
				
				break;
			case 8:
				printf("请输入将求行列式矩阵：\n");//行列式是后写的，那么直接用伴随矩阵那块求行列式 
				printf("0	1	2	3	4\n\n5	6	7	8	9\n(请点击数字进行选择)\n");
				pthread_cond_signal(&condition4);// 发送信号
				pthread_mutex_lock(&mutex4);
				pthread_cond_wait(&condition4, &mutex4); // 等待条件变量
				pthread_mutex_unlock(&mutex4);
				ord=oo;num=ord;
				z[num]=determinant(a[num],n[num]);
				if(m[num]!=n[num] || n[num]==0)
					printf("该矩阵无法求行列式！！！"); 
				else
					printf("该矩阵行列式为：%.1f",z[num]);
				printf("\n");
				printf("\n请点击任意处继续");
				pthread_cond_signal(&condition3);// 发送信号	
				pthread_mutex_lock(&mutex3);
				pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
				pthread_mutex_unlock(&mutex3);
				break;
			case 9://概览 
				qaq=0;
				do{
					if(a[qaq]){//检查是否存在该矩阵
						printf("第%d个矩阵:\n",qaq);
						output(a[qaq],n[qaq],m[qaq]);
					}
				}while(++qaq<10);
				printf("\n请点击任意处继续");
				pthread_cond_signal(&condition3);// 发送信号	
				pthread_mutex_lock(&mutex3);
				pthread_cond_wait(&condition3, &mutex3); // 等待条件变量
				pthread_mutex_unlock(&mutex3);
				break;
			case 0:
				flag=0;
				printf("感谢使用！！\n");
				break;
			default:
				;
				break;
		}
	} while(flag);
	printf("释放内存中......");//释放内存时间比较长，其实代码结束后就不需要管内存泄漏的问题了， 所以这一步，也好 
	
	pthread_exit(NULL); // 主动退出线程
	return NULL; // 返回退出线程
}
int main(){
	SetConsoleOutputCP(65001);
    // 设置控制台输入代码页为UTF-8  
    SetConsoleCP(65001);
	system("cls");//清屏 
	pthread_t tid1, tid2, tid3, tid4, tid5;
    pthread_create(&tid1, NULL, jz, NULL);//原主函数 
    pthread_create(&tid2, NULL, sb, NULL);//功能列表按键导入 
    pthread_create(&tid3, NULL, rs, NULL);//储存 
    pthread_create(&tid4, NULL, dj, NULL);//检测鼠标点击行为，替代了指令system("pause"); 
    pthread_create(&tid5, NULL, ma, NULL);//数字编号导入对应矩阵 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    return 0;//代码结束 
}