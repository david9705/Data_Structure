#include <iostream>
#include<fstream>
#include<ctime>
using namespace std;

int* failure_function(char [],int [],int );


int main(int argc, char* argv[])
{
	int text_size=0;
	int i,j,row=0;
	int pattern_size[100]={0};
	
	ifstream infile_pattern("aaaa.txt",ios::in);
	
	if(!infile_pattern)  
	{
		cerr<<"Pattern file could not be opened!"<<endl;
		exit(1);
	}
	
	
	
	char text1[2000];
	char pattern1[2000][100];
	
	
	
	i=0;
	j=0;
	int x=0;
	char temp;
	while(infile_pattern.get(temp))  //read pattern
	{
	
		if(temp=='\n')
		{
			pattern1[i][j]=temp;
			pattern_size[i] = j;
			j=0;
			i++;
		}
		else
		{
			pattern1[i][j]=temp;
			j++;
		}
	}
	pattern1[i][j]='\n';
	pattern_size[i] = j;
	i++;
	row=i;


	for(int i=0;i<row;i++)               //pattern轉成小寫  
	{
		for(int j=0;j<pattern_size[i];j++)
		{
			if(pattern1[i][j]>=65&&pattern1[i][j]<=90)
			{
				pattern1[i][j]=pattern1[i][j]+32;
			}
		}
	}


	ifstream infile_txt("kk.txt",ios::in);
	
	if(!infile_txt)    
	{
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
		
	i=0;
	j=0;
	x=0;
	
	
	while(infile_txt.get(text1[i]))    //store text in array
	{
		
		
		text_size++;
		
		if(text1[i]==EOF)   //讀完檔 
		{
			i=0;
			break;
		}
		if(text1[i]=='\n')    //讀完一行開始執行kmp 
		{
			for(int l=0;l<text_size;l++)   //text轉成小寫 
			{
				if(text1[l]>=65&&text1[l]<=90)
				{
					text1[l]=text1[l]+32;
				}
			}
			
			int x=0;
			int next[pattern_size[x]];
			for(int k=0;k<row;k++)
			{
				int *ptr;
				
				ptr=failure_function(pattern1[k],next,pattern_size[k]);   //接failurefunction 
			
				int pos_p=0,pos_t=0;
			
									
					while((pos_p<pattern_size[k])&&(pos_t<text_size))
					{
						if(pattern1[k][pos_p]==text1[pos_t])   //找到一樣的pattern 
						{
						
							if(pos_p==pattern_size[k]-1)
							{
								cout<< j+1<<" "<<pos_t - pattern_size[x] + 2<<" \" ";
								for(int q=0;q<pattern_size[k];q++)
								{
									cout<<pattern1[k][q];
								}
								pos_p=*(ptr+pos_p)+1;
								pos_t++;
								
								cout<<"\"";
								
								cout<<"  \" ";
								for(int y=0;y<text_size-1;y++)
								{
									cout<<text1[y];
								}
								cout<<"\" "<<endl;
							
							}
							else     
							{
								pos_p++;
								pos_t++;
							}
						}
						else
						{
							if(pos_p==0)    //第一個字就錯 
							{
								pos_t++;
							}
							else    //後面的字錯 
							{
								pos_p=*(ptr+pos_p-1)+1;
							}
						}
					}
					
				
			}
			i=0;
			j++;   //i歸零,繼續下一行	
		}
		x++;
		i++;
	}
	cout<<"Time used: "<<(static_cast<double>(clock())/CLK_TCK)*1000<<"ms"<<endl;
}



int* failure_function(char a[],int p[],int size)
{

	int i, j, k, flag;

    for(j = 0;j < size;j++){
        if(j == 0) p[j] = -1;
        else{
            k = j - 1;
            while(k >= 0){
                flag = 0;
                for(i = 0;i <= k;i++){
                    if(a[i] != a[j-k+i]){
                        break;
                    }
                    if(i == k){
                        p[j] = k;
                        flag = 1;
                    }
                }
                if(flag == 1)break;
                if(k == 0)p[j] = -1;
                k--;
            }
        }
    }
    return p;
}


