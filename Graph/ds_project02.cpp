#include<iostream>
#include<fstream>
#define maxx 2147483647

using namespace std;
int* sort(int [][100],bool *);
bool all_0(int [][100]);



int main(int argc , char *argv[])
{
	ifstream infile(argv[1],ios::in);

	if(!infile)  
	{
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}

	while(infile)
	{
		 
		
		
		int v,e,e_tree,p1,p2,par_n=0;
		int mat[100][100];
		int tree1[100];
		int tree2[100];
		bool mark[100][100]={0};
		char ch;
		infile>>v>>e;   //讀取點與邊 
	
		
		for(int i=0;i<100;i++)                //每一個邊都先設成無限大 
		{
			for(int j=0;j<100;j++)
			{
				mat[i][j]=maxx;
			}
		}
	
	
		for(int i=0;i<e;i++)				  //讀取無向邊的權重	
		{
			int j=0,k=0,temp1;
			infile>>j;
			infile>>k;
			infile>>temp1;
			mat[j][k]=temp1;
			mat[k][j]=mat[j][k];
		}
		
		
		
		e_tree=0;
		int x=0; 
		int cnt_y[v];              
		int v1,v2;    //計算有幾個邊被加進去&推進 
		bool sign=false;
		while(e_tree<v-1&&all_0(mat))        //開始Kruskal    //要全部不等於0 
		{
			int *k=sort(mat,&mark[0][0]);
			
		
			v1=*k;
			v2=*(k+1);
			
			for(int i=0;i<e;i++)
			{
				for(int j=0;j<e;j++)
				{
					if(((tree1[i]==*k&&tree2[j]==*(k+1))||(tree1[i]==*(k+1)&&tree2[j]==*k))&&(mark[*k][*(k+1)]!=1||mark[*(k+1)][*k]!=1))    //確認是否有環 
					{
						//e_tree=e_tree-1;
						//有環就不加進去 
					}
					else
					{
						tree1[e_tree]=v1; 			//存到tree,分成2個比較好印 
						tree2[e_tree]=v2;
						//刪除無向&找到的最小邊 
					
					}
				}
				
			}
			e_tree++;
			
		}     
		
		for(int y=0;y<v;y++)
		{
			for(int i=0;i<e_tree;i++)
			{
				if(tree1[i]==y)cnt_y[y]++;
			}
		}
		for(int y=0;y<v;y++)
		{
			if(cnt_y[y]==0)sign=true;
		}
		
	
		
		if(e_tree!=v-1||sign==true)
		{
			cout<<"No spanning tree!!!"<<endl;
			
		}
		else
		{
			for(int i=0;i<e_tree;i++)
			{
				cout<<"( "<<tree1[i]<<" , "<<tree2[i]<<" ) ";
			}
			cout<<endl;
			
		}
		cout<<endl;
		
	
	
		
		
		//v是頂點喔~~ 
		while(infile)
		{
			infile>>ch;
			if(ch=='x'||ch=='z'||ch=='X'||ch=='Z')
			{
				break;	
			}
			else	p1=ch-'0';
			infile>>p2;
			int sht1[v];
			int sht2[v];
			int cnt=0,j=0;
			int dist[v];
			int d[v];       // 紀錄起點到各個點的最短路徑長度
			int parent[v];  // 紀錄各個點在最短路徑樹上的父親是誰
			bool visit[v];  // 紀錄各個點是不是已在最短路徑樹之中
			
			
		    for (int i=0; i<v; i++) visit[i] = false;   // initialize
		    for (int i=0; i<v; i++) d[i] = maxx;
		    
		 
		    d[p1] = 0;
		    parent[p1] = p1;
		 
		    for (int k=0; k<v; k++)
		    {
		        int a = -1, b = -1, min = maxx;
		        for (int i=0; i<9; i++)
		            if (!visit[i] && d[i] < min)
		            {
		                a = i;  // 記錄這一條邊
		                min = d[i];
		            }
		 
		        if (a == -1) break;     // 起點有連通的最短路徑都已找完
			    if (min == maxx) break;  // 不連通即是最短路徑長度無限長
		        visit[a] = true;
		 
		        // 以邊ab進行relaxation
		        for (b=0; b<v; b++)
		        {
		        	if (!visit[b]&&d[a] + mat[a][b] < d[b]&&mat[a][b]!=maxx)
		            {
		                d[b] = d[a] + mat[a][b];
		                parent[b] = a;
					}
				}
				
			    
		    
			}
			
		    
			
			if(!visit[p2])
			{
				cout<<"No shortest path!!"<<endl;
				
			}
			else
			{
				for(int i=p2;i!=p1;i = parent[i])
		    	{	
					sht1[cnt]=parent[i];
		    		sht2[cnt]=i;
		    		cnt++;
				}
				
				if(p1==p2)
				{
					cout<<"( "<<p1<<" , "<<p2<<" ) ";
				}
				for(int i=cnt-1;i>=0;i--)
				{
					cout<<"( "<<sht1[i]<<" , "<<sht2[i]<<" ) ";
				}cout<<endl;
			}
			
				
		}
				
		if(ch == 'x'||ch=='X')
		{
			break;	
		}	
	}
	
	
	return 0;	
}



int* sort(int b[][100],bool *a)
{
	int temp[3]; 
	int min=maxx;
	int num;
	
	
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			if(b[i][j]!=maxx&&b[i][j]<min&&(*(a+100*i+j)!=1||*(a+100*j+i)!=1))      
			{
				min=b[i][j];
				temp[0]=i;
				temp[1]=j;
				
			}
			
				
		}
	}
	
	*(a+100*temp[0]+temp[1])=1;
	*(a+100*temp[1]+temp[0])=1;


	temp[2]=min;
	
	
	return &temp[0];
}

bool all_0(int x[][100])
{
	int n=0;
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			if(x[i][j]!=0)return true;
			
		}
	}
	return false;
	
}


