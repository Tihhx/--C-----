#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 999
#define MAX 20
typedef char vertextype;
typedef int edgetype;

/*景点抽象数据结构*/
typedef struct vertexnode  			    
{
	/*景点编号*/
	vertextype vertex[5];		
	 /*景点名称*/ 		   
	char vertexname[100];
	/*景点简介*/ 		    
	char vertexinfo[1000];
	
	int flage;
}vertexnode;
typedef struct {
	/*景点信息域*/ 
	vertexnode vers[MAX];   
	/*邻接矩阵*/      
	edgetype edges[MAX][MAX];
	/*n顶点数，e边数*/ 
	int n,e;				    
}Mgraph;

 /*菜单函数*/ 
int menu();
/*创建图函数*/				 
void creat(Mgraph *p);
/*景点查找函数*/
void find (Mgraph *p);
/*保存景点数据*/
void save(Mgraph *p);
/*从键盘输入景点数据*/
void input(Mgraph *p); 
/*计算最短路径*/ 
void dijkstra(Mgraph *p);
/*增加景点*/ 
void add(Mgraph *p);
/*删除景点*/ 
void dele(Mgraph *p);
/*深度优先输出所有路径*/
void dfs(Mgraph p,int start,int end,char *t);
/*修改景点*/
void alter (Mgraph *p); 
/*景点名称转下标*/
int change (Mgraph *p,char s[]);
int main()
{
		int i,j;
		int start,end;
		char s[200];
		char str1[100];
		char str2[100];
		Mgraph *p;
		p=(Mgraph *)malloc(sizeof(Mgraph));
		while(1){
		i=menu();
		switch(i)
		{
			case 1:find(p);break;
			case 2:dijkstra(p);break;
			case 3:
				printf("请输入起点:");
				scanf("%s",str1);
				printf("请输入终点:");
				scanf("%s",str2);
				start=change(p,str1);
				end=change(p,str2);
				dfs(*p,start,end,"");
				break;
			case 4:input(p);break;
			case 5:creat(p);break;
			case 6:add(p);break;
			case 7:alter(p);break;
			case 8:dele(p);break;
			case 9:save(p);break; 
			case 0:exit(0);break;
			default:printf("功能选择错误！\n");
		}
	}
}

int menu()
{
	int i;
	printf("=========校园旅游导航程序======\n");
	printf("|        1.查询景点信息       |\n");
	printf("|        2.查询最短路径       |\n");
	printf("|        3.查询所有路径       |\n");
	printf("|        4.输入景点信息       |\n");
	printf("|        5.从文件读取景点信息 |\n");
	printf("|        6.增加景点           |\n");
	printf("|        7.修改景点           |\n");
	printf("|        8.删除景点           |\n");
	printf("|        9.保存景点           |\n");
	printf("|        0.退出               |\n");
	printf("===============================\n");
	printf("请选择功能:");
	scanf("%d",&i); 
	return i;
}
/*景点名转下标*/
int change (Mgraph *p,char s[100])
{
	int i;
	for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertexname)==0)){return i;}
	} 
	printf("输入景点名错误！\n");
	return -1;
}

/*读取文件中图的信息*/
void creat(Mgraph *p){
	FILE *rf;
	int i,j,w;
	/*读取文件中图的信息*/
	rf=fopen("mapData.txt","r");					  
	if(rf){
		/*读取顶点数，边数*/ 
		fscanf(rf,"%d %d",&p->n,&p->e);				  
		for(i=0;i<p->n;i++){
			/*读取顶点编号*/ 
			fscanf(rf,"%s",&p->vers[i].vertex);
			/*读取景点名称*/ 		 
			fscanf(rf,"%s",&p->vers[i].vertexname); 
			/*读取景点简介*/  
			fscanf(rf,"%s",&p->vers[i].vertexinfo);	
		}
		/*读入边数据*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				fscanf(rf,"%d %d %d",&i,&j,&w);
				p->edges[i][j]=w;
			}		
		}
	}		
		fclose(rf); 
		printf("景点信息已经加载!\n");
}


void find (Mgraph *p){
	int n,i;
	char s[100];
	printf("========校园旅游导航程序=======\n");
	printf("|       查询景点信息          |\n");
	printf("|       1.显示全部景点信息    |\n");
	printf("|       2.按景点名称查询      |\n");
	printf("|       3.按景点编号查询      |\n");
	printf("|       0.退出                |\n");
	printf("===============================\n");
	printf("请选择功能：");
	scanf("%d",&n);
	/*显示全部景点信息*/ 
	if(n==1){
		for(i=0;i<p->n;i++){
		printf("景点编号：%s\n",p->vers[i].vertex);
		printf("景点名称：%s\n",p->vers[i].vertexname);
		printf("景点简介：%s\n",p->vers[i].vertexinfo);
		printf("===============================\n");
	}
	}
	/*按景点名称查询*/ 
	else if(n==2){
		printf("请输入景点名称:");
		scanf("%s",s);
		for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertexname)==0)){
				printf("景点编号：%s\n",p->vers[i].vertex);
				printf("景点名称：%s\n",p->vers[i].vertexname);
				printf("景点简介：%s\n",p->vers[i].vertexinfo);
				return;
			}else {printf("没找到该景点！");return;} 
		}
	}
	/*按景点编号查询*/ 
	else if(n==3){
		printf("请输入景点编号:");
		scanf("%s",s);
		for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertex)==0)){
				printf("景点编号：%s\n",p->vers[i].vertex);
				printf("景点名称：%s\n",p->vers[i].vertexname);
				printf("景点简介：%s\n",p->vers[i].vertexinfo);
				return;
			}else {printf("没找到该景点！");return;} 
		}
	}
	/*退出*/ 
	else if(n==0) {return;} 
	else printf("功能选择错误!"); 	 
}

/*保存景点数据*/
void save(Mgraph *p){
	int i,j,k,w;
	FILE *rf;
	/*将景点数据写入文件*/
	rf=fopen("1111.txt","w");					  
	if(rf){
		/*写入顶点数，边数*/ 
		fprintf(rf,"%d %d\n",p->n,p->e);				  
		for(i=0;i<p->n;i++){
			/*写入顶点编号*/ 
			fprintf(rf,"%s\n",p->vers[i].vertex);
			/*写入景点名称*/ 		 
			fprintf(rf,"%s\n",p->vers[i].vertexname); 
			/*写入景点简介*/  
			fprintf(rf,"%s\n",p->vers[i].vertexinfo);	
		}
		/*写入矩阵*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				fprintf(rf,"%d %d %d",i,j,p->edges[i][j]);
				fprintf(rf,"\n");
			}
		}
		fclose(rf); 
		printf("景点信息已经保存!\n");
	}
}

void input(Mgraph *p){
	int i,j,k,w;					  
		/*读取顶点数，边数*/ 
		printf("请输入景点数和路径数:"); 
		scanf("%d %d",&p->n,&p->e);				  
		for(i=0;i<p->n;i++){
			/*输入顶点编号*/ 
			printf("请输入景点编号:");
			scanf("%s",&p->vers[i].vertex);
			/*输入景点名称*/ 
			printf("请输入景点名称:");		 
			scanf("%s",&p->vers[i].vertexname); 
			/*输入景点简介*/  
			printf("请输入景点简介:");
			scanf("%s",&p->vers[i].vertexinfo);	
			p->vers[i].flage=0;
		}
		/*初始化矩阵*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				if(i==j) p->edges[i][j]=0;			//对角线置0 
				else p->edges[i][j]=INFINITY;		//其他置无穷大，999 
			}
		}
		/*输入边数据*/
		for(k=0;k<p->e;k++){
			printf("请输入起点终点及权重:");
			scanf("%d %d %d",&i,&j,&w);
			p->edges[i][j]=w;
			p->edges[j][i]=w;
		}
	}
	
/*求最短路径*/ 
void dijkstra(Mgraph *p){
	int i,j,v=-1,t=INFINITY,count=0;
	int top=0;
	int stack[MAX];
	char start[100]; 		//开始起点名称 
	char end[100];			//结束起点名称 
	int dist[MAX]; 		//记录最短距离 
	int path[MAX];			//记录最短路径 
	char flage[MAX];		//标记是否被读取 
	
	for(i=0;i<p->n;i++){	//初始化 
		dist[i]=INFINITY;
		path[i]=-1;
		flage[i]='N';
	}
	printf("请输入起点名称：");
	scanf("%s",start);
	printf("请输入终点名称：");
	scanf("%s",end);
	/*初始化起点，准备开始记录最短路径*/ 
	for(i=0;i<p->n;i++){
		/*景点名称转下标*/ 
		if((strcmp(start,p->vers[i].vertexname)==0))
		{
			/*初始化起点*/ 
			dist[i]=0;		//自己到自己距离为0 
			flage[i]='Y';	//起点标记位已经读取 
			for(j=0;j<p->n;j++){		//读取和起点直接相邻的邻边及权重 
				if(p->edges[i][j] != 999 ||p->edges[i][j] != 0){
						dist[j]=p->edges[i][j];
						path[j]=i;
				}
			}
		} 
	}
	/*调试*/ 
//	for(i=0;i<p->n;i++)
//	{
//		printf("path %d \n",path[i]);
//		printf("dist %d \n",dist[i]);
//		printf("flage %c \n",flage[i]);
//	}
	while(1){
		for(i=0;i<p->n;i++){
			if(dist[i]<t && flage[i]=='N'){
		//	printf("dist[i]=%d t=%d  %d\n",dist[i],t,dist[i+1]);
			t=dist[i];
			v=i;
		//	printf("dist[i]=%d t=%d  %d\n",dist[i],t,dist[i+1]);
			break;}
		}
		t=INFINITY;
		if(v==-1) break; 
		flage[v]='Y';
		for(i=0;i<p->n;i++){
			if(p->edges[v][i] != 999 && p->edges[v][i] != 0 && flage[i]!='Y'){
				if(dist[v]+p->edges[v][i]<dist[i]){
					dist[i] = dist[v]+p->edges[v][i];
					path[i]=v;
				}
			}
		}
		v=-1;	
	}
		 /*调试*/ 
//	for(i=0;i<p->n;i++)
//	{
//		printf("path %d \n",path[i]);
//		printf("dist %d \n",dist[i]);
//		printf("flage %c \n",flage[i]);
//	}

	/*处理终点，并输出起点到终点的最短路径*/
	for(i=0;i<p->n;i++){
		/*景点名称转下标*/ 
		if((strcmp(end,p->vers[i].vertexname)==0))
		{
			t=i;
			break; 
		} 
	}
	for(i=t;dist[i]!=0;i=path[i]){        
		/*进栈调试*/ 
	//	printf("%d\n",i);
		stack[top]=i;
		top++;
	}
	if(top==0)
	{
		printf("没有通路！\n");
		return;
	}
	printf("最短路径为:\n");
	printf("%s-->",start);
	for(i=top-1;i>0;i--){
		printf("%s-->",p->vers[stack[i]].vertexname);
	}
	printf("%s\n",end);
	
	for(i=0;i<p->n;i++)
		p->vers[i].flage=0;
}

void alter (Mgraph *p)
{
	char s[100];
	char ch;
	int i,j,k;
	printf("请输入要修改的景点名称：");
	scanf("%s",s);
	i=change(p,s);
	if(i==-1)
	{
		printf("输入景点名称有误！\n"); 
		return ; 
	} 
		printf("请输入景点的新编号:");
		scanf("%s",p->vers[i].vertex); 
		printf("请输入景点的新名称:");
		scanf("%s",p->vers[i].vertexname);
		printf("请输入景点的新简介:");
		scanf("%s",p->vers[i].vertexinfo);  
	 
		while(1)
		{
			printf("是否输入边关系？Y/N\n");
			getchar(); 
			ch=getchar();
			if(ch=='N'||ch=='n') 
				return; 
			printf("请输入起点景点名称:");
			scanf("%s",s); 
			if(change(p,s)==-1)
			{		
				printf("输入景点名称有误！\n"); 
				return ; 
			} 
			j=change(p,s);
			printf("请输入终点景点名称:");
			scanf("%s",s); 
			if(change(p,s)==-1)
			{		
				printf("输入景点名称有误！\n"); 
				return ; 
			} 
			k=change(p,s);
			printf("请输入权重（999为不连通）:");
			scanf("%d",&i);
			p->edges[j][k]=i;
			p->edges[k][j]=i;
		} 
	 

}

void add(Mgraph *p)
{
	char s[100];
	 int j,k,q;
	 int i=p->n;
	 p->n++;
	 p->vers[i].flage=0;
	 printf("请输入要添加的景点\n景点编号：");
	 scanf("%s",p->vers[i].vertex);
	 printf("景点名称：");
	 scanf("%s",p->vers[i].vertexname);
	 printf("景点简介：");
	 scanf("%s",p->vers[i].vertexinfo);
	 printf("请输入该景点和几个景点有边：");
	 scanf("%d",&j);
	 for(k=0;k<j;k++)
	 {
	 	p->edges[k][i]=999;
		p->edges[i][k]=999; 
	 } 
	 p->edges[i][i]=0;
	 for(k=0;k<j;k++){
	 	printf("请输入和它相连景点的名称：");
	 	scanf("%s",s);
	 	printf("%d\n",change (p,s));
	 	if(change (p,s)==-1)
	 		return;
	 	printf("请输入权重:");
	 	scanf("%d",&q);
	 	p->edges[change(p,s)][i]=q;
	 	p->edges[i][change(p,s)]=q;
	 }
	for(i=0;i<p->n;i++)
		p->vers[i].flage=0;
} 

void dele(Mgraph *p)
{
	char s[100];
	int i,j,k;
	for(j=0;j<p->n;j++){  //修改前矩阵 
		for(k=0;k<p->n;k++)
		{
			printf("%-5d",p->edges[j][k]);
		}
		printf("\n");
	}
	printf("请输入要删除景点的名称:");
	scanf("%s",s);
	i=change(p,s);
	if(i==-1)
	{
		printf("删除错误！\n");
		return ;
	}
	for(j=i;j<p->n-1;j++)
	{
		strcpy(p->vers[j].vertex,p->vers[j+1].vertex);
		strcpy(p->vers[j].vertexname,p->vers[j+1].vertexname);
		strcpy(p->vers[j].vertexinfo,p->vers[j+1].vertexinfo);
	}
	for(k=0;k<p->n;k++){
		for(j=i;j<p->n-1;j++){
			p->edges[k][j]=p->edges[k][j+1];
		}
		}
	for(k=0;k<p->n;k++){
		for(j=i;j<p->n-1;j++){
			p->edges[j][k]=p->edges[j+1][k];
		}
		}
	p->n--;
	for(j=0;j<p->n;j++){           //显示修改后矩阵 
		for(k=0;k<p->n;k++)
		{
			printf("%-5d",p->edges[j][k]);
		}
		printf("\n");
	}
	for(i=0;i<p->n;i++)
		p->vers[i].flage=0;
	 
}


void dfs (Mgraph p,int start,int end,char *t)
{
	char path[1000];
	int i,j,k;
	if(p.vers[start].flage==1){return;} /*如果顶点没有被标记就处理*/
	p.vers[start].flage=1;
	strcpy(path,t);                   
	strcat(path,p.vers[start].vertexname);
	strcat(path,"-->");
	if(start==end) {
		for(j=0;j<strlen(t);j++)
		{
			printf("%c",t[j]);
		}
		
		printf("%s\n",p.vers[end].vertexname);
		return;
	}
	for(i=0;i<p.n;i++)
	{
		if(p.edges[start][i]!=999 && p.edges[start][i]!=0)
		{dfs(p,i,end,path);}
	}
}

 
