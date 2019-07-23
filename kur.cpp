#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
//66.		Дана матрица весов дуг. Определить и вывести все циклы в орграфе, заданной длины х (вводится с клавиатуры)	Матрица инцидентности
using namespace std;
struct stack{
	int id;
	stack *pred;
};
class A{
	protected:
		ifstream file;
		int count_v;
    	vector < string > names;	
	public:	
		A(string str){
			file.open(str.c_str());
			file>>str;
			while(str!="#"&&!file.eof())
    		{
		    	file>>str;
		    	names.push_back(str);
		    	file>>str;	
		    }
		    count_v = names.size();
		}
		~A(){
			file.close();
		}
		virtual void show(){
			for (int i=0;i<count_v;i++)
				cout<<names[i]<<" ";
			cout<<endl;
		}

		int getcv(){
			return count_v;
		}
		int getidbyv(string name){
			int i=0;
			bool flag=0;
			for (;i<count_v;i++)
				if(names[i]==name)
				{
					flag=1;
					break;
				}
				
				
			if(flag)return i;
			else return -1;
		}
		string getnamebyid(int id){
			if (id>names.size()) return "no";
			return names[id];
		}
	
};
class B: public A{
	private:
		int count_r;
		vector <vector<int> > v;
		bool flag;
		stack *tek,*pr, *tmp,*start;
		vector<int> mascolour;//0 white, 1 gray, 2 black
		int lcycle;
	public:
		B(string str):A(str){
			flag=1;
			lcycle=0;
			file>>str;
		    while(!file.eof())
			{
				vector < int > r(count_v,0);
				int t1=atoi(str.c_str());
		    	file>>str;
				int t2=atoi(str.c_str());
				file>>str;
				int t3=atoi(str.c_str());
				file>>str;
				r[t1-1]=t3;
				r[t2-1]=-t3;
				v.push_back(r);
		    }
		    count_r=v.size();
		}
		~B(){
			
		}
		friend void counter(B* bb);
		int getv(int a, int b){
			return v[a][b];
		}
		void show(){
			cout<<endl<<"-------------------------------------------------"<<endl;
			for(int j=0;j<count_v;j++)//вывод
			{
		    	for(int i=0;i<count_r;i++)
		    	{	
		    		int tv=v[i][j];
		    		cout<<tv<<"\t";
		    	}	
		    	cout<<endl;
		    }
		    cout<<endl<<"-------------------------------------------------"<<endl;
		}
		int getcr(){
			return count_r;
		}
		void add_v(string name){
			for(int i=0;i<count_v;i++)
				if(name==names[i])
				{
					cout<<"this name already exist, try another name!"<<endl;
					return;
				}
			names.push_back(name);
			count_v++;
			for(int i=0;i<count_r;i++)
				v[i].push_back(0);
		}
		void add_r(string n1, string n2, int ves){
			bool f1=0,f2=0;
			for(int i=0;i<count_v;i++)
			{
				if(n1==names[i])f1=1;
				if(n2==names[i])f2=1;				
			}
			if(!(f1&&f2)) {
				cout<<"error! this pieks not find!"<<endl;
				return;
			}
			vector < int > r(count_v,0);
			r[getidbyv(n1)]=ves;
			r[getidbyv(n2)]=-ves;
			v.push_back(r);
			count_r++;
		}
		void del_r(int id){
			v.erase(v.begin()+id);
			count_r--;
		}
		void napr_r(int id){// изменить направлени
			for (int i=0;i<count_v;i++)
			if(v[id][i]!=0) v[id][i]=-v[id][i];
		}
		void ves_r(int id,  int ves){//изметнить ве
			for (int i=0;i<count_v;i++)
			if(v[id][i]!=0) v[id][i]=v[id][i]/abs(v[id][i])*ves;
		}
		void del_v(string name){// удаляет вершину c удалением ребер связанных с вершиной
			int i=getidbyv(name);
			if(i<0){
				cout<<"such a peak is not exist!"<<endl;
				return;
			}
			
			int id=getridbyv(name);
			while(id>=0)
			{
				del_r(id);
				id=getridbyv(name);
			}
			
			names.erase(names.begin()+i);
			
			for(int w=0;w<count_r;w++)
			{
				v[w].erase(v[w].begin()+i);
			}
			count_v--;
		}
		int getridbyv(string name){
			int id=getidbyv(name);
			if(id < 0) return -2;
			for(int i=0;i<count_r;i++)
				if(v[i][id]!=0)return i;
			return -1;
		}
		int first(string name){
			int i=getidbyv(name);
			if(i<0) return -1;
			return vertex(name,0);	
		}
		int next(string name, int id){
			int i=getidbyv(name);
			if(i<0) return -1;
			return vertex(name,id+1);	
		}
		int vertex(string name, int id){
			if(id<0)return -1;
			int i=getidbyv(name);
			if(i<0) return -1;
			vector < int > r(0,0);
			for(int q=0;q<count_r;q++)
			{
				int tmp=v[q][i];
				
				if(tmp>0)
				{
					for(int w=0;w<count_r;w++)
					{
						if(w==i)continue;
						if(v[q][w]<0) {
							r.push_back(w);	
							break;
						}
					}
				}
			
			}
			if(id+1>r.size())return -1;
			return r[id];
		}
		bool operator*(int q){
			if(q<=0) return false;
			for(int j=0;j<count_v;j++)//вывод
				for(int i=0;i<count_r;i++)
	    			v[i][j]*=q;	
		
		
			return true;
		}
		void spsm(){
			for(int i=0;i<count_v;i++)
			{
				cout<<getnamebyid(i)<<" ";
				for (int j=0;;j++)
				{
					int ver=vertex( getnamebyid(i) , j );
					if(ver<0) break;
					cout<<ver<<" ";
				}
				cout<<endl;
			}
		}
		int cycle_of_cycles(int l){
			
			for(int i=0;i<count_v;i++){
				mascolour=vector <int>(count_v,0);
				cycle(i,l);
				mascolour.clear();
				flag=1;
				lcycle=0;
				cout<<endl<<"--------------------------------";
			}
			mascolour.clear();
			lcycle=0;
			flag=1;
			cout<<endl;
		}
		void cycle (int v_number, int l){
			vector < vector<int> > vv;
			vv=v;
			if(flag){
				tek=new stack;
				tek->pred=NULL;
				tek->id=v_number;
				flag=0;
				mascolour[v_number]=2;
			}
			else {
				tmp=tek;
				tek=new stack;
				tek->pred=tmp;
				tek->id=v_number;
				mascolour[v_number]=1;
			}
			for(int i=0;i<count_r;i++){
				int vrtx=vertex(getnamebyid(v_number),i);
				if (vrtx<0) break;
				else {
					if(mascolour[vrtx]==0)
					{
						cycle(vrtx,l);	
					}
					else if(mascolour[vrtx]==2)
					{
						lcycle++;
						tmp=tek;
						while(tmp->pred!=NULL){
							pr=tmp->pred;
											lcycle++;
							tmp=tmp->pred;
						}
						tmp=tek;
						if(lcycle==l)
						{
							cout<<endl;
							tmp=tek;
							cout<<names[vrtx]<<"<-";
							while(tmp->pred!=NULL){
								cout<<names[tmp->id]<<"<-";
								tmp=tmp->pred;
							}		
							cout<<names[vrtx]<<endl;
						}
						lcycle=0;
					}		
				}
			}
			mascolour[v_number]=0;
			tmp=tek->pred;
			delete tek;
			tek=tmp;
		}		
};
void counter(B* bb){
	cout<<endl<<bb->count_v<<"  "<<bb->count_r<<endl;
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	
	
	
	int q=1;
	string s="graph1.tgf";
	cout<<"Какой граф 1,2,3?";
	cin>>q;
	if(q==2)s="graph2.tgf";
	else if(q==3)s="graph3.tgf";
    
    B* b=new B(s);
    b->show();
    bool quit=0;

    
	while(!quit)
    {
    	int a;
    	string n1,n2;
		int m,n;
    	cout<<"1:Показать граф "<<endl;
    	cout<<"2:Добавить вершину "<<endl;
    	cout<<"3:Добавить дугу "<<endl;
    	cout<<"4:Удалить вершину "<<endl;   	
    	cout<<"5:Удалить дугу "<<endl; 
    	cout<<"6:Изменить вес дуги "<<endl;		   	
    	cout<<"7:Изменить направление дуги "<<endl;
    	cout<<"8:Вывести циклы заданной длины "<<endl;
    	cout<<"9:Выйти "<<endl;
    	cout<<"Выберете действие ";
    	cin>>a;
		switch(a){
			case 1:{
				b->show();
				break;
			}
			case 2:{
				string n;
				cout<<"Введите название вершины ";
				cin>>n;
				b->add_v(n);
				break;
			}
			case 3:{
				
				cout<<"Введите название 1 вершины ";
				cin>>n1;
				cout<<"Введите название 2 вершины ";
				cin>>n2;
				cout<<"Введите вес дуги ";
				cin>>m;
				b->add_r(n1,n2,m);
				break;
			}
			case 4:{
				cout<<"Введите имя вершины ";
				cin>>n1;
				b->del_v(n1);
				break;
			}
			case 5:{
				cout<<"Введите индекс дуги ";
				cin>>m;
				b->del_r(m);
		
				break;
			}
			case 6:{
				cout<<"Введите индекс дуги ";
				cin>>m;
				cout<<"Введите новый вес дуги дуги ";
				cin>>n;
				b->ves_r(m,n);
				break;
			}
			case 7:{
				cout<<"Введите индекс дуги ";
				cin>>m;
				b->napr_r(m);
				break;
			}
			case 8:{
				cout<<"Введите длину цикла ";
				cin>>m;
				b->cycle_of_cycles(m);
				break;
			}
			case 9:{
				quit=1;
				break;
			}
				
		}
	}
	
    delete b;
	return 0;
}
