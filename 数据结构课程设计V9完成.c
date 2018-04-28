#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 999
#define MAX 20
typedef char vertextype;
typedef int edgetype;

/*����������ݽṹ*/
typedef struct vertexnode  			    
{
	/*������*/
	vertextype vertex[5];		
	 /*��������*/ 		   
	char vertexname[100];
	/*������*/ 		    
	char vertexinfo[1000];
	
	int flage;
}vertexnode;
typedef struct {
	/*������Ϣ��*/ 
	vertexnode vers[MAX];   
	/*�ڽӾ���*/      
	edgetype edges[MAX][MAX];
	/*n��������e����*/ 
	int n,e;				    
}Mgraph;

 /*�˵�����*/ 
int menu();
/*����ͼ����*/				 
void creat(Mgraph *p);
/*������Һ���*/
void find (Mgraph *p);
/*���澰������*/
void save(Mgraph *p);
/*�Ӽ������뾰������*/
void input(Mgraph *p); 
/*�������·��*/ 
void dijkstra(Mgraph *p);
/*���Ӿ���*/ 
void add(Mgraph *p);
/*ɾ������*/ 
void dele(Mgraph *p);
/*��������������·��*/
void dfs(Mgraph p,int start,int end,char *t);
/*�޸ľ���*/
void alter (Mgraph *p); 
/*��������ת�±�*/
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
				printf("���������:");
				scanf("%s",str1);
				printf("�������յ�:");
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
			default:printf("����ѡ�����\n");
		}
	}
}

int menu()
{
	int i;
	printf("=========У԰���ε�������======\n");
	printf("|        1.��ѯ������Ϣ       |\n");
	printf("|        2.��ѯ���·��       |\n");
	printf("|        3.��ѯ����·��       |\n");
	printf("|        4.���뾰����Ϣ       |\n");
	printf("|        5.���ļ���ȡ������Ϣ |\n");
	printf("|        6.���Ӿ���           |\n");
	printf("|        7.�޸ľ���           |\n");
	printf("|        8.ɾ������           |\n");
	printf("|        9.���澰��           |\n");
	printf("|        0.�˳�               |\n");
	printf("===============================\n");
	printf("��ѡ����:");
	scanf("%d",&i); 
	return i;
}
/*������ת�±�*/
int change (Mgraph *p,char s[100])
{
	int i;
	for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertexname)==0)){return i;}
	} 
	printf("���뾰��������\n");
	return -1;
}

/*��ȡ�ļ���ͼ����Ϣ*/
void creat(Mgraph *p){
	FILE *rf;
	int i,j,w;
	/*��ȡ�ļ���ͼ����Ϣ*/
	rf=fopen("mapData.txt","r");					  
	if(rf){
		/*��ȡ������������*/ 
		fscanf(rf,"%d %d",&p->n,&p->e);				  
		for(i=0;i<p->n;i++){
			/*��ȡ������*/ 
			fscanf(rf,"%s",&p->vers[i].vertex);
			/*��ȡ��������*/ 		 
			fscanf(rf,"%s",&p->vers[i].vertexname); 
			/*��ȡ������*/  
			fscanf(rf,"%s",&p->vers[i].vertexinfo);	
		}
		/*���������*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				fscanf(rf,"%d %d %d",&i,&j,&w);
				p->edges[i][j]=w;
			}		
		}
	}		
		fclose(rf); 
		printf("������Ϣ�Ѿ�����!\n");
}


void find (Mgraph *p){
	int n,i;
	char s[100];
	printf("========У԰���ε�������=======\n");
	printf("|       ��ѯ������Ϣ          |\n");
	printf("|       1.��ʾȫ��������Ϣ    |\n");
	printf("|       2.���������Ʋ�ѯ      |\n");
	printf("|       3.�������Ų�ѯ      |\n");
	printf("|       0.�˳�                |\n");
	printf("===============================\n");
	printf("��ѡ���ܣ�");
	scanf("%d",&n);
	/*��ʾȫ��������Ϣ*/ 
	if(n==1){
		for(i=0;i<p->n;i++){
		printf("�����ţ�%s\n",p->vers[i].vertex);
		printf("�������ƣ�%s\n",p->vers[i].vertexname);
		printf("�����飺%s\n",p->vers[i].vertexinfo);
		printf("===============================\n");
	}
	}
	/*���������Ʋ�ѯ*/ 
	else if(n==2){
		printf("�����뾰������:");
		scanf("%s",s);
		for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertexname)==0)){
				printf("�����ţ�%s\n",p->vers[i].vertex);
				printf("�������ƣ�%s\n",p->vers[i].vertexname);
				printf("�����飺%s\n",p->vers[i].vertexinfo);
				return;
			}else {printf("û�ҵ��þ��㣡");return;} 
		}
	}
	/*�������Ų�ѯ*/ 
	else if(n==3){
		printf("�����뾰����:");
		scanf("%s",s);
		for(i=0;i<p->n;i++){
			if((strcmp(s,p->vers[i].vertex)==0)){
				printf("�����ţ�%s\n",p->vers[i].vertex);
				printf("�������ƣ�%s\n",p->vers[i].vertexname);
				printf("�����飺%s\n",p->vers[i].vertexinfo);
				return;
			}else {printf("û�ҵ��þ��㣡");return;} 
		}
	}
	/*�˳�*/ 
	else if(n==0) {return;} 
	else printf("����ѡ�����!"); 	 
}

/*���澰������*/
void save(Mgraph *p){
	int i,j,k,w;
	FILE *rf;
	/*����������д���ļ�*/
	rf=fopen("1111.txt","w");					  
	if(rf){
		/*д�붥����������*/ 
		fprintf(rf,"%d %d\n",p->n,p->e);				  
		for(i=0;i<p->n;i++){
			/*д�붥����*/ 
			fprintf(rf,"%s\n",p->vers[i].vertex);
			/*д�뾰������*/ 		 
			fprintf(rf,"%s\n",p->vers[i].vertexname); 
			/*д�뾰����*/  
			fprintf(rf,"%s\n",p->vers[i].vertexinfo);	
		}
		/*д�����*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				fprintf(rf,"%d %d %d",i,j,p->edges[i][j]);
				fprintf(rf,"\n");
			}
		}
		fclose(rf); 
		printf("������Ϣ�Ѿ�����!\n");
	}
}

void input(Mgraph *p){
	int i,j,k,w;					  
		/*��ȡ������������*/ 
		printf("�����뾰������·����:"); 
		scanf("%d %d",&p->n,&p->e);				  
		for(i=0;i<p->n;i++){
			/*���붥����*/ 
			printf("�����뾰����:");
			scanf("%s",&p->vers[i].vertex);
			/*���뾰������*/ 
			printf("�����뾰������:");		 
			scanf("%s",&p->vers[i].vertexname); 
			/*���뾰����*/  
			printf("�����뾰����:");
			scanf("%s",&p->vers[i].vertexinfo);	
			p->vers[i].flage=0;
		}
		/*��ʼ������*/
		for(i=0;i<p->n;i++){					     
			for(j=0;j<p->n;j++){
				if(i==j) p->edges[i][j]=0;			//�Խ�����0 
				else p->edges[i][j]=INFINITY;		//�����������999 
			}
		}
		/*���������*/
		for(k=0;k<p->e;k++){
			printf("����������յ㼰Ȩ��:");
			scanf("%d %d %d",&i,&j,&w);
			p->edges[i][j]=w;
			p->edges[j][i]=w;
		}
	}
	
/*�����·��*/ 
void dijkstra(Mgraph *p){
	int i,j,v=-1,t=INFINITY,count=0;
	int top=0;
	int stack[MAX];
	char start[100]; 		//��ʼ������� 
	char end[100];			//����������� 
	int dist[MAX]; 		//��¼��̾��� 
	int path[MAX];			//��¼���·�� 
	char flage[MAX];		//����Ƿ񱻶�ȡ 
	
	for(i=0;i<p->n;i++){	//��ʼ�� 
		dist[i]=INFINITY;
		path[i]=-1;
		flage[i]='N';
	}
	printf("������������ƣ�");
	scanf("%s",start);
	printf("�������յ����ƣ�");
	scanf("%s",end);
	/*��ʼ����㣬׼����ʼ��¼���·��*/ 
	for(i=0;i<p->n;i++){
		/*��������ת�±�*/ 
		if((strcmp(start,p->vers[i].vertexname)==0))
		{
			/*��ʼ�����*/ 
			dist[i]=0;		//�Լ����Լ�����Ϊ0 
			flage[i]='Y';	//�����λ�Ѿ���ȡ 
			for(j=0;j<p->n;j++){		//��ȡ�����ֱ�����ڵ��ڱ߼�Ȩ�� 
				if(p->edges[i][j] != 999 ||p->edges[i][j] != 0){
						dist[j]=p->edges[i][j];
						path[j]=i;
				}
			}
		} 
	}
	/*����*/ 
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
		 /*����*/ 
//	for(i=0;i<p->n;i++)
//	{
//		printf("path %d \n",path[i]);
//		printf("dist %d \n",dist[i]);
//		printf("flage %c \n",flage[i]);
//	}

	/*�����յ㣬�������㵽�յ�����·��*/
	for(i=0;i<p->n;i++){
		/*��������ת�±�*/ 
		if((strcmp(end,p->vers[i].vertexname)==0))
		{
			t=i;
			break; 
		} 
	}
	for(i=t;dist[i]!=0;i=path[i]){        
		/*��ջ����*/ 
	//	printf("%d\n",i);
		stack[top]=i;
		top++;
	}
	if(top==0)
	{
		printf("û��ͨ·��\n");
		return;
	}
	printf("���·��Ϊ:\n");
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
	printf("������Ҫ�޸ĵľ������ƣ�");
	scanf("%s",s);
	i=change(p,s);
	if(i==-1)
	{
		printf("���뾰����������\n"); 
		return ; 
	} 
		printf("�����뾰����±��:");
		scanf("%s",p->vers[i].vertex); 
		printf("�����뾰���������:");
		scanf("%s",p->vers[i].vertexname);
		printf("�����뾰����¼��:");
		scanf("%s",p->vers[i].vertexinfo);  
	 
		while(1)
		{
			printf("�Ƿ�����߹�ϵ��Y/N\n");
			getchar(); 
			ch=getchar();
			if(ch=='N'||ch=='n') 
				return; 
			printf("��������㾰������:");
			scanf("%s",s); 
			if(change(p,s)==-1)
			{		
				printf("���뾰����������\n"); 
				return ; 
			} 
			j=change(p,s);
			printf("�������յ㾰������:");
			scanf("%s",s); 
			if(change(p,s)==-1)
			{		
				printf("���뾰����������\n"); 
				return ; 
			} 
			k=change(p,s);
			printf("������Ȩ�أ�999Ϊ����ͨ��:");
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
	 printf("������Ҫ��ӵľ���\n�����ţ�");
	 scanf("%s",p->vers[i].vertex);
	 printf("�������ƣ�");
	 scanf("%s",p->vers[i].vertexname);
	 printf("�����飺");
	 scanf("%s",p->vers[i].vertexinfo);
	 printf("������þ���ͼ��������бߣ�");
	 scanf("%d",&j);
	 for(k=0;k<j;k++)
	 {
	 	p->edges[k][i]=999;
		p->edges[i][k]=999; 
	 } 
	 p->edges[i][i]=0;
	 for(k=0;k<j;k++){
	 	printf("���������������������ƣ�");
	 	scanf("%s",s);
	 	printf("%d\n",change (p,s));
	 	if(change (p,s)==-1)
	 		return;
	 	printf("������Ȩ��:");
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
	for(j=0;j<p->n;j++){  //�޸�ǰ���� 
		for(k=0;k<p->n;k++)
		{
			printf("%-5d",p->edges[j][k]);
		}
		printf("\n");
	}
	printf("������Ҫɾ�����������:");
	scanf("%s",s);
	i=change(p,s);
	if(i==-1)
	{
		printf("ɾ������\n");
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
	for(j=0;j<p->n;j++){           //��ʾ�޸ĺ���� 
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
	if(p.vers[start].flage==1){return;} /*�������û�б���Ǿʹ���*/
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

 
