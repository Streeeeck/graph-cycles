#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
//66.		Дана матрица весов дуг. Определить и вывести все циклы в орграфе, заданной длины х (вводится с клавиатуры)	Матрица инцидентности
using namespace std;

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
		vector < vector<int> > v;
		
	public:
		B(string str):A(str){
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
		int getv(int a, int b){
			return v[a][b];
		}
		void show(){
			cout<<endl<<"-------------------------------------------------"<<endl;
			for(int j=0;j<count_v;j++)//вывод
			{
    			string ts;
    			if(v[0][j]>=0)cout<<" ";
		    	for(int i=0;i<count_r;i++)
		    	{	
		    		int tv=v[i][j];
					if( abs(tv)>99) ts=" ";
					else if (abs(tv)>9) ts="  ";
		    		else ts="   ";
		    		if (tv<0)ts+=" ";
		    		cout<<tv<<ts;	
		    	}	
		    	cout<<endl;
		    }
		   /* int mas[count_r];

		    for(int i=0;i<count_r;i++)
		    {
		    	for(int j=0;j<count_v;j++)
				{
					int tmp=v[j][i];
					if(tmp<0){
						if(tmp<-9)mas[j]=3;//отстут для 0
						else mas[j]=2;
					}					
		    		
		    	}
			}
		    for(int i=0;i<count_r;i++)
		    {
		    
		    	for(int j=0;j<count_v;j++)
		    	{
		    		string ts="";
		    		int tmp=v[j][i];
		    		int sp=0;
		    		if(tmp>0) sp=3;
		    		//else if (tmp>9) sp=2;
		    		else if(tmp<0)sp=1;
		    		else sp=mas[j];
		    		for	(int q=0;q < sp;q++)
		    			ts+=" ";
		    			cout<<ts<<tmp;
		    		
		    	}
		    	cout<<endl;
		    	
		    }*/
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
							cout<<w<<" ";
							break;
						}
					}
				}
			
			}
			if(id+1>r.size())return -1;
			return r[id];
		}
		void zad(int x){//циклы заданной длин
		
		
		}
			
			
			
};


int main(int argc, char** argv) {
    string s="graph1.tgf";
    cout<<s;
    B* b=new B(s);
    b->add_v("v8");
    b->add_r("v1","v8", 20);   
    b->show();
    cout<<endl<<"1"<<endl;
    cout<<b->getv(16,0)<<endl<<"-------------------------------------------------"<<endl;
    cout<<endl<<"2"<<endl;
    b->del_v("v1");
    cout<<endl<<"3"<<endl;
    b->show();
    b->A::show();
       cout<<endl<<"-------------------------------------------------"<<endl;
    cout<<b->getnamebyid(b->vertex("v2",1));
       delete b;
       
	return 0;
}
