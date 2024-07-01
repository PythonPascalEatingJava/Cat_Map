#include<bits/stdc++.h>
using namespace std;

int cmpdate(string a,string b)
{
	int len=min(a.size(),b.size());
	int i=0;
	for (i=0; i<=3; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	for (i=5; i<=6; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	for (i=8; i<=9; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	for (i=11; i<=12; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	for (i=14; i<=15; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	for (i=17; i<=18; i++)
	{
		if ((int)a[i]>(int)b[i]) return 1;
		if ((int)a[i]<(int)b[i]) return -1;
	}
	return 0;
}

struct node_crime  //用链表结构存储违章信息 
{
	char time[128];  //违章时间 
	char place[128];  //违章地点 
	char crimecode[128];  //违章代码 
	char deal[128];  //处理情况 
	node_crime *next;
};

struct car
{
	char num[128];  //编号 
	char cartype[128];  //型号 
	char price[128];  //价格 
	char drivername[128];  //车主 
	int crimecount;
	node_crime *crime;
};

int tonum(char* s)
{
	int i,x=0;
	for (i=0; s[i]!='\0'; i++)
	{
		x*=10;
		x+=(int)s[i]-(int)'0';
	}
	return x;
}

ostream& operator<<(ostream& os, car c)
{
	cout<<"____________________\n";
	node_crime *crimenow=c.crime;
	cout<<c.num<<' '<<c.cartype<<' '<<c.price<<' '<<c.drivername<<endl;
	cout<<c.crimecount<<endl;
	for (int i=0; i<c.crimecount; i++)
	{
		cout<<endl;
		cout<<crimenow->time;
		cout<<crimenow->place;
		cout<<crimenow->crimecode;
		cout<<crimenow->deal;
		crimenow=crimenow->next;
	}
}
istream& operator>>(istream& is, car c)
{
	cin>>c.num>>c.cartype>>c.price>>c.drivername;
}

int main()
{
	car carlist[102];  //每辆车对应一个car结构体 
	node_crime *nowcrime;  //链表操作临时变量 
	int carcount;  //车总数、违章总数 
	int i,j,k,flag;  //循环变量 
	FILE *filein,*fileout;  //输入输出文件指针 
	char tempstr[128];  //临时字符串，用于去除“-------”行 
	
	filein=fopen("input.txt","r");
	fileout=fopen("output.txt","w");
	if (!filein or !fileout)
	{
		cout<<"opening error!";
		exit(1);
	}
	//打开对应文件 
	
	fscanf(filein, "%d", &carcount);  //读入车辆总数 
	for (i=1; i<=carcount; i++)
	{
		//printf("i=%d\n",i);
		fscanf(filein,"%s",tempstr);
		//cout<<tempstr;
		fscanf(filein,"%s",carlist[i].num);
		//cout<<carlist[i].num;
		fscanf(filein,"%s",carlist[i].cartype);
		//cout<<carlist[i].cartype;
		fscanf(filein,"%s",carlist[i].price);
		//cout<<carlist[i].price;
		fscanf(filein,"%s",carlist[i].drivername);
		//cout<<carlist[i].drivername;
		fscanf(filein,"%s",tempstr);
		//cout<<tempstr<<endl;
		carlist[i].crimecount=tonum(tempstr);
		fgets(tempstr,1024,filein);
		//cout<<carlist[i].crimecount;
		
		//读入车辆信息 
		
		if (carlist[i].crimecount==0)
		{
			carlist[i].crime=NULL;
			//cout<<"innocent!\n";
		}
		else
		{
			carlist[i].crime=new node_crime;
			nowcrime=carlist[i].crime;
			for (j=1; j<=carlist[i].crimecount; j++)
			{
				//printf(" j=%d\n",j);
				fgets(nowcrime->time,1024,filein);
				fgets(nowcrime->place,1024,filein);
				fgets(nowcrime->crimecode,1024,filein);
				fgets(nowcrime->deal,1024,filein);
				//cout<<"\ntime:"<<nowcrime->time<<endl;
				//cout<<"\nplace:"<<nowcrime->place<<endl;
				nowcrime->next=(j!=carlist[i].crimecount?new node_crime:NULL);
				nowcrime=(j!=carlist[i].crimecount?nowcrime->next:NULL);
			}
		}
		//读入违章信息 
	}
	
	string operation="00";
	string str="";
	string str_="";
	while(operation!="-1")
	{
		cout<<"输入操作：\n";
		cout<<"1.按车辆编号查找违章\n";
		cout<<"2.按时间段查找违章\n";
		cout<<"3.按地点查找违章\n";
		cout<<"4.按违章代码查找违章\n";
		cout<<"5.载入新车辆的信息\n";
		cout<<"6.删除车辆的信息\n";
		cout<<"7.加入新的违章记录\n"; 
		cout<<"输入-1以退出程序并查看当前车辆状况\n" ;
		
		cin>>operation; 
		if (operation=="-1") break;
		switch((int)operation[0]-(int)'0')
		{
			case 1:
			{
				cout<<"\n请输入车辆编号：\n";
				cin>>str;
				flag=0;
				for (int i=1; i<=carcount; i++)
				{
					if (carlist[i].num==str)
					{
						flag=1;
						nowcrime=carlist[i].crime;
						while(nowcrime->next!=NULL)
						{
							cout<<nowcrime->time;
							cout<<nowcrime->place;
							cout<<nowcrime->crimecode;
							cout<<nowcrime->deal;
							nowcrime=nowcrime->next;
							cout<<endl;
						}
						cout<<nowcrime->time;
						cout<<nowcrime->place;
						cout<<nowcrime->crimecode;
						cout<<nowcrime->deal;
						cout<<endl;
						break;
					}
				}
				if (flag==0)
				{
					cout<<"\n未找到编号为 "<<str<<" 的车辆\n"; 
				}
				break;
			}
			case 2:
			{
				cout<<"\n请输入起始时间，格式为YYYY-MM-DD-HH-MM-SS，含边界\n";
				cin>>str;
				cout<<"\n请输入结束时间，格式同上\n";
				cin>>str_;
				if (str.size()!=19 or str_.size()!=19)
				{
					cout<<"\n输入错误，请重新操作\n";
					break;
				}
				
				flag=0;
				for (int i=1; i<=carcount; i++)
				{
					car c=carlist[i];
					nowcrime=carlist[i].crime;
					while(nowcrime!=NULL and nowcrime->next!=NULL)
					{
						if (cmpdate(str,nowcrime->time)<=0 and cmpdate(str_,nowcrime->time)>=0)
						{
							flag=1;
							cout<<"\n发现违章记录：\n";
							cout<<c.num<<' '<<c.cartype<<' '<<c.price<<' '<<c.drivername<<endl;
							cout<<nowcrime->time;
							cout<<nowcrime->place;
							cout<<nowcrime->crimecode;
							cout<<nowcrime->deal;
							nowcrime=nowcrime->next;
							cout<<endl;
						}
						nowcrime=nowcrime->next;
					}
				}
				if (flag==0)
				{
					cout<<"\n未找到 "<<str<<" 与 "<<str_<<"之间的违章记录\n";
				}
				break;
			}
			case 3:
			{
				cout<<"\n请输入地点，例：“学院路”：\n";
				cin>>str;
				str=str+'\n';
				
				flag=0;
				for (int i=1; i<=carcount; i++)
				{
					cout<<"running on i="<<i<<";\n";
					nowcrime=carlist[i].crime;
					if (carlist[i].crimecount==0) continue;
					if (carlist[i].crimecount!=1)
					while(nowcrime!=NULL and nowcrime->next!=NULL)
					{
						if (str==nowcrime->place)
						{
							flag=1;
							cout<<"\n发现违章记录：\n";
							cout<<nowcrime->time;
							cout<<nowcrime->place;
							cout<<nowcrime->crimecode;
							cout<<nowcrime->deal;
							nowcrime=nowcrime->next;
							cout<<endl;
						}
						nowcrime=nowcrime->next;
					}
					if (str==nowcrime->place)
					{
						flag=1;
						cout<<"\n发现违章记录：\n";
						cout<<nowcrime->time;
						cout<<nowcrime->place;
						cout<<nowcrime->crimecode;
						cout<<nowcrime->deal;
						cout<<endl;
					}
				}
				if (flag==0)
				{
					cout<<"\n未找到位于\n"<<str<<"\n的违章记录\n";
				}
				break;
			}
			case 4:
			{
				cout<<"\n请输入违章代码：\n";
				cin>>str;
				str=str+'\n';
				flag=0;
				for (int i=1; i<=carcount; i++)
				{
					nowcrime=carlist[i].crime;
					while(nowcrime!=NULL and nowcrime->next!=NULL)
					{
						if (str==nowcrime->crimecode)
						{
							flag=1;
							cout<<nowcrime->time;
							cout<<nowcrime->place;
							cout<<nowcrime->crimecode;
							cout<<nowcrime->deal;
							nowcrime=nowcrime->next;
							cout<<endl;
						}
						nowcrime=nowcrime->next;
					}
				}
				if (flag==0)
				{
					cout<<"\n未找到违章代码为\n"<<str<<"\n的违章记录\n";
				}
				break;
			}
			case 5:
			{
				cout<<"\n请输入新车辆的信息：";
				car newcar;
				char newnum[128];
				char newcartype[128];
				char newprice[128];
				char newdrivername[128];
				int newcrimecount;
				cin>>newcar;
				newcar.crimecount=0;
				newcar.crime=NULL;
				carlist[carcount]=newcar;
				carcount++;
				cout<<"\n载入完毕。\n";
				break;
			}
			case 6:
			{
				cout<<"\n请输入删除对象的编号：\n";
				string s;
				cin>>s;
				int flag=0; //0表示未找到删除对象 
				for (int i=1; i<carcount; i++)
				{
					int j=0;  
					for (j=0; j<s.size(); j++)
					{
						if (s[j]!=carlist[i].num[j])
						break;
					}
					if (j==s.size() and (carlist[i].num[j]>'9' or carlist[i].num[j]<'0'))
					{
						for (int k=i; k<=carcount; k++)
						{
							carlist[k]=carlist[k+1];
						}
						carcount--;
						cout<<"\n删除成功\n";
						flag=1;
					}
				}
				if (flag==0)
				{
					cout<<"未找到编号为"<<s<<"的车辆\n"; 
				}
				break;
			}
			case 7:
			{
				cout<<"请输入违章车辆编号\n";
				cin>>str;
				str=str+'\n';
				flag=0;
				int i;
				for (i=1; i<=carcount; i++)
				{
					if (carlist[i].num==str)
					{
						flag=1;
						break;
					}
				}
				if (flag==0)
				{
					cout<<"未找到编号为"<<str<<"的车辆。\n";
					break;
				}
				cout<<"请输入违章时间，格式为YYYY-MM-DD HH:MM:SS\n";
				getline(cin,str);
				if (str.size()!=19 or str_.size()!=19)
				{
					cout<<"输入错误，请重新操作\n";
					break;
				}
				str=str+'\n';
				node_crime* thiscrime;
				for (thiscrime=carlist[i].crime; thiscrime!=NULL; thiscrime=thiscrime->next)
				{}
				thiscrime=new node_crime;
				thiscrime->next=NULL;
				for (int k=0; k<str.size(); k++)
				thiscrime->time[k]=str[k];
				cout<<"请输入违章地点\n";
				cin>>thiscrime->place;
				cout<<"请输入违章代码\n";
				cin>>thiscrime->crimecode;
				cout<<"请输入处理情况\n";
				cin>>thiscrime->deal;
				break;
			}
			default:
			{
				cout<<"格式错误，请重新输入\n";
				operation=""; 
				break;
			}
		}; 
	}
	
	ofstream destFile("output.txt",ios::out);
	fprintf(fileout,"%d\n",carcount);
	for (int i=1; i<=carcount; i++)
	{
		fprintf(fileout,"------------------------\n");
		fprintf(fileout,"%s ",carlist[i].num);
		fprintf(fileout,"%s ",carlist[i].cartype);
		fprintf(fileout,"%s ",carlist[i].price);
		fprintf(fileout,"%s\n",carlist[i].drivername);
		destFile<<carlist[i].cartype;
		destFile<<carlist[i].price;
		destFile<<carlist[i].drivername;
		node_crime* thiscrime=carlist[i].crime;
		for (int j=0; j<carlist[i].crimecount; j++)
		{
			fprintf(fileout,"%s",thiscrime->time);
			fprintf(fileout,"%s",thiscrime->place);
			fprintf(fileout,"%s",thiscrime->crimecode);
			fprintf(fileout,"%s",thiscrime->deal);
			thiscrime=thiscrime->next;
		}
	}
	destFile.close();
	cout<<"当前车辆状况：\n";
	for (int i=1; i<=carcount; i++)
	{
		cout<<carlist[i];
	}
	cout<<"\n_____感谢您的使用，再见。_____\n";
	
	fclose(filein);
	fclose(fileout);
	return 0;
	//关闭并保存文件，程序结束 
}
