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

struct node_crime  //������ṹ�洢Υ����Ϣ 
{
	char time[128];  //Υ��ʱ�� 
	char place[128];  //Υ�µص� 
	char crimecode[128];  //Υ�´��� 
	char deal[128];  //������� 
	node_crime *next;
};

struct car
{
	char num[128];  //��� 
	char cartype[128];  //�ͺ� 
	char price[128];  //�۸� 
	char drivername[128];  //���� 
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
	car carlist[102];  //ÿ������Ӧһ��car�ṹ�� 
	node_crime *nowcrime;  //���������ʱ���� 
	int carcount;  //��������Υ������ 
	int i,j,k,flag;  //ѭ������ 
	FILE *filein,*fileout;  //��������ļ�ָ�� 
	char tempstr[128];  //��ʱ�ַ���������ȥ����-------���� 
	
	filein=fopen("input.txt","r");
	fileout=fopen("output.txt","w");
	if (!filein or !fileout)
	{
		cout<<"opening error!";
		exit(1);
	}
	//�򿪶�Ӧ�ļ� 
	
	fscanf(filein, "%d", &carcount);  //���복������ 
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
		
		//���복����Ϣ 
		
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
		//����Υ����Ϣ 
	}
	
	string operation="00";
	string str="";
	string str_="";
	while(operation!="-1")
	{
		cout<<"���������\n";
		cout<<"1.��������Ų���Υ��\n";
		cout<<"2.��ʱ��β���Υ��\n";
		cout<<"3.���ص����Υ��\n";
		cout<<"4.��Υ�´������Υ��\n";
		cout<<"5.�����³�������Ϣ\n";
		cout<<"6.ɾ����������Ϣ\n";
		cout<<"7.�����µ�Υ�¼�¼\n"; 
		cout<<"����-1���˳����򲢲鿴��ǰ����״��\n" ;
		
		cin>>operation; 
		if (operation=="-1") break;
		switch((int)operation[0]-(int)'0')
		{
			case 1:
			{
				cout<<"\n�����복����ţ�\n";
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
					cout<<"\nδ�ҵ����Ϊ "<<str<<" �ĳ���\n"; 
				}
				break;
			}
			case 2:
			{
				cout<<"\n��������ʼʱ�䣬��ʽΪYYYY-MM-DD-HH-MM-SS�����߽�\n";
				cin>>str;
				cout<<"\n���������ʱ�䣬��ʽͬ��\n";
				cin>>str_;
				if (str.size()!=19 or str_.size()!=19)
				{
					cout<<"\n������������²���\n";
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
							cout<<"\n����Υ�¼�¼��\n";
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
					cout<<"\nδ�ҵ� "<<str<<" �� "<<str_<<"֮���Υ�¼�¼\n";
				}
				break;
			}
			case 3:
			{
				cout<<"\n������ص㣬������ѧԺ·����\n";
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
							cout<<"\n����Υ�¼�¼��\n";
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
						cout<<"\n����Υ�¼�¼��\n";
						cout<<nowcrime->time;
						cout<<nowcrime->place;
						cout<<nowcrime->crimecode;
						cout<<nowcrime->deal;
						cout<<endl;
					}
				}
				if (flag==0)
				{
					cout<<"\nδ�ҵ�λ��\n"<<str<<"\n��Υ�¼�¼\n";
				}
				break;
			}
			case 4:
			{
				cout<<"\n������Υ�´��룺\n";
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
					cout<<"\nδ�ҵ�Υ�´���Ϊ\n"<<str<<"\n��Υ�¼�¼\n";
				}
				break;
			}
			case 5:
			{
				cout<<"\n�������³�������Ϣ��";
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
				cout<<"\n������ϡ�\n";
				break;
			}
			case 6:
			{
				cout<<"\n������ɾ������ı�ţ�\n";
				string s;
				cin>>s;
				int flag=0; //0��ʾδ�ҵ�ɾ������ 
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
						cout<<"\nɾ���ɹ�\n";
						flag=1;
					}
				}
				if (flag==0)
				{
					cout<<"δ�ҵ����Ϊ"<<s<<"�ĳ���\n"; 
				}
				break;
			}
			case 7:
			{
				cout<<"������Υ�³������\n";
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
					cout<<"δ�ҵ����Ϊ"<<str<<"�ĳ�����\n";
					break;
				}
				cout<<"������Υ��ʱ�䣬��ʽΪYYYY-MM-DD HH:MM:SS\n";
				getline(cin,str);
				if (str.size()!=19 or str_.size()!=19)
				{
					cout<<"������������²���\n";
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
				cout<<"������Υ�µص�\n";
				cin>>thiscrime->place;
				cout<<"������Υ�´���\n";
				cin>>thiscrime->crimecode;
				cout<<"�����봦�����\n";
				cin>>thiscrime->deal;
				break;
			}
			default:
			{
				cout<<"��ʽ��������������\n";
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
	cout<<"��ǰ����״����\n";
	for (int i=1; i<=carcount; i++)
	{
		cout<<carlist[i];
	}
	cout<<"\n_____��л����ʹ�ã��ټ���_____\n";
	
	fclose(filein);
	fclose(fileout);
	return 0;
	//�رղ������ļ���������� 
}
