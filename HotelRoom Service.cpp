#include<fstream.h>
#include<studentio.h>
#include<string.h>
#include<iomanip.h>
#include<ctype.h>
#include<process.h>
class society
{
	int mcode;
	char mname[15];
	char housetype[20];
	int Noofrooms;
	float cost;
	public:
		void getdata();
		void printdata();
		int ret_noRoom(){return Noofrooms;}
		int checktype(char type[]){return strcmpi(type, housetype);}
		void update(){cost*=1.1;}//increase cost by 10%
};

void society::getdata()
{
  cout<<"Enter Member code:\n";
  cin>>mcode;
  cout<<"Enter Member name:\n";
  gets(mname);
  cout<<"Enter House type:\n";
  gets(housetype);
  cout<<"Enter No. of rooms:\n";
  cin>>Noofrooms;
  cout<<"Enter cost:\n";
  cin>>cost;
}

void society::printdata()
{
  cout<<"Member code: "<<mcode<<endl;
  cout<<"Member name: "<<mname<<endl;
  cout<<"House type: "<<housetype<<endl;
  cout<<"No of Rooms: "<<Noofrooms<<endl;
  cout<<"Cost: "<<cost<<endl;
}

//Global variable
society o1, o2;
//Functions

void append()
{
  ofstream f2("Society.dat", ios::binary | ios::app);
  o1.getdata();
  f2.write((char*)&o1, sizeof(o1));
  f2.close();
}

void Display()
{
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  while(f1.read((char*)&o1, sizeof(o1)))
	{
	 o1.printdata();
	 cout<<endl;
	}
  f1.close();
}

void Search_rooms()
{
  cout<<"Enter the maximum No of Rooms \n";
  int n, flag=0;
  cin>>n;
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  while(f1.read((char*)&o1, sizeof(o1)))
	  if(o1.ret_noRoom()<n)
		{
			o1.printdata();
			flag=1;
		}
  if(flag==0)
	cout<<"No records found.";
  f1.close();
}

void Disp_house()
{
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  while(f1.read((char*)&o1, sizeof(o1)))
	 if(o1.checktype("HIG")==0||o1.checktype("Duplex")==0)
	  o1.printdata();
  f1.close();
}

void Delete()
{ int flag=0;
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  ofstream f2("temp.dat", ios::binary);
  while(f1.read((char*)&o1, sizeof(o1)))
	  if(o1.ret_noRoom()!=1)
		 {
			f2.write((char*)&o1, sizeof(o1));
			flag=1;
		 }
  if(flag==0)
	cout<<"No records deleted.";
  f1.close();
  f2.close();
  remove("Society.dat");
  rename("Temp.dat", "Society.dat");
}
void copy()
{
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  ofstream f2("Delux.dat", ios::binary);
  while(f1.read((char*)&o1, sizeof(o1)))
	 if(o1.checktype("Villa")==0||o1.checktype("Duplex")==0)
		f2.write((char*)&o1, sizeof(o1));
  f1.close();
}

/*void Modify()
{
  ifstream f1("Society.dat", ios::binary);
  if(!f1)
  {
	 cout<<"Error 404: File does not exist";
	 return;
	}
  ofstream f2("temp.dat", ios::binary);
  while(f1.read((char*)&o1, sizeof(o1)))
  {
	  if(o1.ret_noRoom()==4 && o1.checktype("Flat")==0)
		 {
			o1.update();
			f2.write((char*)&o1, sizeof(o1));
		 }
	  else
			f2.write((char*)&o1, sizeof(o1));
  }
  f1.close();
  f2.close();
  remove("Society");
  rename("temp.dat", "Society.dat");
}*/
//Modify() (2)
void Modify()
{
  fstream f("Society.dat", ios::binary | ios::out | ios::in);
  while(f.read((char*)&o1, sizeof(o1)))
	 {
	  if(o1.ret_noRoom()==4 && o1.checktype("Flat")==0)
		 {
			f.seekp(f.tellg()-sizeof (o1));
			o1.update();
			f.write((char*)&(o1), sizeof(o1));
		 }
	 }
  f.close();
}
//Main

void main()
{
 int ch;
 char d;
 do
 {
	cout<<"Menu-\n";
	cout<<"1.Append\n";
	cout<<"2.Display records\n";
	cout<<"3.Searching for No of rooms\n";
	cout<<"4.Display records of house type HIG and Duplex\n";
	cout<<"5.Delete records\n";
	cout<<"6.Copy records\n";
	cout<<"7.Modify records\n";
	cin>>ch;
	switch(ch)
	{
		case 1:append();
				 break;
		case 2:Display();
				 break;
		case 3:Search_rooms();
				 break;
		case 4:Disp_house();
				 break;
		case 5:Delete();
				 break;
		case 6:copy();
				 break;
		case 7:Modify();
				 break;
		default:cout<<"Entered Wrong choice\n";
	}
	cout<<"Do you option to continue\n";
	cin>>d;
}while(d=='Y' || d=='y');
exit(1);
}
