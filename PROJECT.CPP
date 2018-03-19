#include<fstream>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<iostream>
using namespace std;
void start();
struct element
{
  int atomicno;
  float mass;
  char name[20],symbol[3];
  void input();
  void output();
};
void element :: input()
{
  cout<<"\n\nEnter name of element   => ";
  gets(name);
  cout<<"Enter atomic no.        => ";
  cin>>atomicno;
  cout<<"Enter atomic mass      => ";
  cin>>mass;
  cout<<"Enter chemical symbol   => ";
  gets(symbol);
}
void element :: output()
{
  char block;
  int group,period;
  if( (atomicno>56&&atomicno<72)||(atomicno>88&&atomicno<104) )
	 block='f';
  else
  {
	 if(atomicno<3)
		period=1;
	 else if(atomicno<11)
		period=2;
	 else if(atomicno<19)
		period=3;
	 else if(atomicno<37)
		period=4;
	 else if(atomicno<55)
		period=5;
	 else if(atomicno<87)
		period=6;
	 else if(atomicno<113)
		period=7;
	 switch(period)
	 {
		case 1 : if(atomicno==2)
					 group=18;
					else
						group=1; break;
		case 2 : if(atomicno>4)
						group=atomicno+8;
					else
						group=atomicno-2; break;
		case 3 : if(atomicno>12)
						group=atomicno;
					else
						group=atomicno-10; break;
		case 4 : group=atomicno-18; break;
		case 5 : group=atomicno-36; break;
		case 6 : if(atomicno>71)
						group=atomicno-68;
					else
						group=atomicno-54; break;
		case 7 : if(atomicno>103)
						group=atomicno-100;
					else
						group=atomicno-86; break;
	 }
	 if(group>12)
		block='p';
	 else if(group>2)
		block='d';
	 else
		block='s';
  }
  cout<<"\n\tElement name    =>     "<<name;
  cout<<"\n\tAtomic no.      =>     "<<atomicno;
  cout<<"\n\tAtomic mass     =>     "<<mass<<" g/mol";
  cout<<"\n\tChemical symbol =>     "<<symbol;
  if(block!='f')
  {
	 cout<<"\n\tGroup no.       =>     "<<group;
	 cout<<"\n\tPeriod no.      =>     "<<period;
  }
  cout<<"\n\tBlock           =>     "<<block<<"-block";
}
void inputFile()
{
  element temp;
  fstream f;
  f.open("ELEMENTS.DAT",ios::binary|ios::app);
  temp.input();
  f.write( (char*)&temp,sizeof(temp) );
  f.close();
}
void reloadFile()
{
  element A;
  fstream f,fbak;
  f.open("ELEMENTS.DAT",ios::binary|ios::out);
  fbak.open("ELEMENTS.BAK",ios::binary|ios::in);
  while(fbak.read( (char*)&A,sizeof(A) ))
	 f.write( (char*)&A,sizeof(A) );
  f.close();
  fbak.close();
}
void display(int atmno)
{
  element temp;
  ifstream f;
  f.open("ELEMENTS.DAT",ios::binary);
  f.seekg((atmno-1)*sizeof(temp));
  f.read( (char*)&temp,sizeof(temp) );
  temp.output();
  f.close();
}
void searchElement()
{
  char temp[20];
  int atmno=0;
  clrscr();
  cout<<"\n\n\tSearch for......   => ";
  gotoxy(5,22);
  cout<<"Note :- You can enter name, symbol or atomic no. of the element you want\n            to search for. ";
  gotoxy(32,3);
  cin>>temp;
  if(isdigit(temp[0]))
  {
	 for(int i=0;temp[i]!='\0';i++)
		if(isdigit(temp[i]))
			atmno=(atmno*10)+(temp[i]-48);
		else
		{
			cout<<"\n\n\t**********************  Invalid input ********************** ";
         cout<<"\n\n\tInput should be name, symbol or atomic no. of the element... "; 
			return;
		}
	 if(atmno>0&&atmno<113)
		display(atmno);
	 else
	 {
		cout<<"\n\tData is available only for first 112 elements......";
		cout<<"\n\n\tEnter atomic no. from 1 to 112 only ......";
	 }
	 return;
  }
  for(int i=0;temp[i]!='\0';i++)
		if(isdigit(temp[i]))
		{
			cout<<"\n\n\t**********************  Invalid input ********************** ";
         cout<<"\n\n\tInput should be name, symbol or atomic no. of the element... "; 
			return;
		}
  if(islower(temp[0]))
  {
	 temp[0]=toupper(temp[0]);
	 cout<<"\n\tDisplaying results for \" "<<temp<<" \"....\n";
  }
  element A;
  ifstream f;
  f.open("ELEMENTS.DAT",ios::binary);
  while( f.read( (char*)&A,sizeof(A) ) )
	 if( strcmp(A.symbol,temp)==0 || strcmp(A.name,temp)==0 )
	 {
		A.output();
		f.close();
		return;
	 }
  cout<<"\n\n \t\t Sorry,  No data found on \" "<<temp<<" \"";
  cout<<"\n\n \t\t Are you sure you typed correctly.... ";
}
void displayPeriodicTable()
{
  clrscr();
  cout<<"\n            ___                                _______";
  cout<<"\n           |   |                                  |   ";
  cout<<"\n           |___|  __  _  ___  _   _  ___   __     |    _    _      _";
  cout<<"\n           |     |__ |_|  |  / \\ | \\  |   /       |   /_\\  |_) |  |_";
  cout<<"\n           |     |__ |\\  _|_ \\_/ |_/ _|_  \\__     |   | |  |_) |_ |_";
  cout<<"\n  ___                                                                     ____ ";
  cout<<"\n | H |____                                            ___________________| He |";
  cout<<"\n | Li  Be |                                          | B   C   N   O   F   Ne |";
  cout<<"\n | Na  Mg | ________________________________________ | Al  Si  P   S   Cl  Ar |";
  cout<<"\n | K   Ca || Sc  Ti  V   Cr  Mn  Fe  Co  Ni  Cu  Zn || Ga  Ge  As  Se  Br  Kr |";
  cout<<"\n | Rb  Sr || Y   Zr  Nb  Mo  Tc  Ru  Rh  Pd  Ag  Cd || In  Sn  Sb  Te  I   Xe |";
  cout<<"\n | Cs  Ba || #   Hf  Ta  W   Re  Os  Ir  Pt  Au  Hg || Tl  Pb  Bi  Po  At  Rn |";
  cout<<"\n | Fr  Ra || ##  Rf  Db  Sg  Bh  Hs  Mt  Ds  Rg  Cn ||________________________|";
  cout<<"\n |________||________________________________________|                          ";
  cout<<"\n   s-Block               d-Block                              p-Block ";
  cout<<"\n _____________________________________________________________________________";
  cout<<"\n|#  Lanthanoids    La  Ce  Pr  Nd  Pm  Sm  Eu  Gd  Tb  Dy  Ho  Er  Tm  Yb  Lu |";
  cout<<"\n|## Actinoids      Ac  Th  Pa  U   Np  Pu  Am  Cm  Bk  Cf  Es  Fm  Md  No  Lr |";
  cout<<"\n|_____________________________________________________________________________|";
  cout<<"\n                              f-block";
  cout<<"\n\n\n\t\t Enter any key to return to menu......";
  return;
}
float getAtomicMass(char a,char b='\0')
{
  char temp[3];
  temp[0]=a;
  temp[1]=b;
  temp[2]='\0';
  element A;
  ifstream f;
  f.open("ELEMENTS.DAT",ios::binary);
  while( f.read( (char*)&A,sizeof(A) ) )
	 if( strcmp(A.symbol,temp)==0)
		return A.mass;
  return 0;
}
float calculateMM(char* A)
{
  float mass=0;
  for(int i=0;A[i]!='\0';i++)
  {
	 int nom=0;
	 float moe=0;
	 char temp[30];
	 if(isupper(A[i]))
	 {
		if(!islower(A[i+1]))
		{
		  moe=getAtomicMass(A[i]);
		  if(isdigit(A[i+1]))
			 for(int j=i+1;isdigit(A[j]);j++)
				nom=(nom*10)+(A[j]-48);
		  else
			 nom=1;
		}
		else
		{
		  moe=getAtomicMass(A[i],A[i+1]);
		  if(isdigit(A[i+2]))
			 for(int j=i+2;isdigit(A[j]);j++)
				nom=(nom*10)+(A[j]-48);
			 else
				nom=1;
		}
	 }
	 else if(A[i]=='(')
	 {
		i++;
		for(int j=0;A[i]!=')';i++,j++)
		  temp[j]=A[i];
		temp[j]='\0';
		moe=calculateMM(temp);
		if(isdigit(A[i+1]))
		  for(int j=i+1;isdigit(A[j]);j++)
			 nom=(nom*10)+(A[j]-48);
		else
		  nom=1;
	 }
	 else if(A[i]=='.')
	 {
		i++;
		if(isdigit(A[i]))
		  for(;isdigit(A[i]);i++)
			 nom=(nom*10)+(A[i]-48);
		else
		  nom=1;
		for(int j=0;A[i]!='\0';i++,j++)
		  temp[j]=A[i];
		temp[j]='\0';
		moe=calculateMM(temp);
	 }
	 mass+=(nom*moe);
  }
  return mass;
}
void nameHeavyElement()
{

  char name[30]="",s[5]="",atmno[5];
  do
  {
	 clrscr();
	 cout<<"\n\n\tEnter the atomic no. of Heavy Element.... => ";
	 gotoxy(5,22);
	 cout<<"Note :- Heavy elements are those whose atomic no. is more than 100 ";
	 gotoxy(55,3);
	 gets(atmno);
	 if(strlen(atmno)<3)
	 {
		cout<<"\n\n\  Sorry... It is not a heavy element... Press any key to try again...";
		getch();
	 }
  }while(strlen(atmno)<3);
  for(int i=0;atmno[i]!='\0';i++)
  {
	 if(!isdigit(atmno[i]))
	 {
		cout<<"\n  Invalid atomic no. ";
		break;
	 }
	 switch(atmno[i]-48)
	 {
		case 0 : strcat(name,"nil");  strcat(s,"n"); break;
		case 1 : strcat(name,"un");   strcat(s,"u"); break;
		case 2 : strcat(name,"bi");   strcat(s,"b"); break;
		case 3 : strcat(name,"tri");  strcat(s,"t"); break;
		case 4 : strcat(name,"quad"); strcat(s,"q"); break;
		case 5 : strcat(name,"pent"); strcat(s,"p"); break;
		case 6 : strcat(name,"hex");  strcat(s,"h"); break;
		case 7 : strcat(name,"sept"); strcat(s,"s"); break;
		case 8 : strcat(name,"oct");  strcat(s,"o"); break;
		case 9 : strcat(name,"enn");  strcat(s,"e"); break;
	 }
  }
  name[0]=toupper(name[0]);
  s[0]=toupper(s[0]);
  if(name[strlen(name)-1]=='i')
	 strcat(name,"um");
  else
	 strcat(name,"ium");
  cout<<"\n\n\n\tIUPAC name of element => "<<name;
  cout<<"\n\n\tSymbol                => "<<s;
}
void menu()
{
  int choice;
  char ch;
  do
  {
	 clrscr();
	 cout<<"\n\t\t       _"<<endl;
	 cout<<"\t\t |\\/| |_  |\\ |  |  |"<<endl;
	 cout<<"\t\t |  | |_  | \\|  |__|"<<endl;
	 cout<<"\n\n 1. Display Periodic Table ";
	 cout<<"\n 2. Search for Element ";
	 cout<<"\n 3. Calculate Molecular Mass ";
	 cout<<"\n 4. Display IUPAC name for heavy elements";
	 cout<<"\n 5. Restart";
	 cout<<"\n 6. Exit ";
	 cout<<"\n\n\nEnter your choice  => ";
	 cin>>choice;
	 switch(choice)
	 {
		case 1 : displayPeriodicTable(); break;
		case 2 : searchElement(); break;
		case 3 : char mf[30];
					clrscr();
					cout<<"\n\n\n  Enter Molecular Formula whose molar mass you want to know\n\n\t  => ";
					gets(mf);
					cout<<"\n  The Molecular Mass of "<<mf<<" is "<<calculateMM(mf)<<" g/mol"; break;
      case 4 : nameHeavyElement(); break;
      case 5 : start(); return;
    }
    getch();
  }while(choice!=6);
  do
  {
    clrscr();
    cout<<"\n\n\n\n\n\t\tAre you sure you want to exit (Y/N)....";
    cin>>ch;
    if(tolower(ch)=='n')
		menu();
	 else if(tolower(ch)=='y')
	 {
		clrscr();
		exit(0);
	 }
  }while(tolower(ch)!='y'||tolower(ch)!='n');
}
void modifyRecord()
{
  int atmno,choice;
  element temp,A;
  fstream f;
  clrscr();
  cout<<"\n\n\tEnter atomic no. of element you want to modify  => ";
  cin>>atmno;
  f.open("ELEMENTS.DAT",ios::binary|ios::in|ios::out);
  f.seekg((atmno-1)*sizeof(temp),ios::beg);
  f.read( (char*)&temp,sizeof(temp) );
  cout<<"\n\t\tFor element of atomic no. "<<atmno;
  cout<<"\n\t ___________________________________________________________________";
  cout<<"\n\t|                      | Existing values     | Enter new values     |";
  cout<<"\n\t|______________________|_____________________|______________________|";
  cout<<"\n\t| Name of element      |                     |                      |";
  cout<<"\n\t|______________________|_____________________|______________________|";
  cout<<"\n\t| Symbol               |                     |                      |";
  cout<<"\n\t|______________________|_____________________|______________________|";
  cout<<"\n\t| Atomic mass (g/mol)  |                     |                      |";
  cout<<"\n\t|______________________|_____________________|______________________|";
  gotoxy(34,9);
  cout<<temp.name;
  gotoxy(34,11);
  cout<<temp.symbol;
  gotoxy(34,13);
  cout<<temp.mass;
  gotoxy(5,22);
  cout<<"Note :- If you don't want to change a value then enter \"0\" (zero)\n            for it.."; 
  gotoxy(56,9);
  gets(A.name);
  gotoxy(56,11);
  gets(A.symbol);
  gotoxy(56,13);
  cin>>A.mass;
  if(strcmp(A.name,"0")==0)
	 strcpy(A.name,temp.name);
  if(strcmp(A.symbol,"0")==0)
	 strcpy(A.symbol,temp.symbol);
  if(A.mass==0)
	 A.mass=temp.mass;
  A.atomicno=temp.atomicno;
  temp=A;
  f.seekg(f.tellg()-sizeof(temp),ios::beg);
  f.write( (char*)&temp,sizeof(temp) );
  f.close();
}
void displayAll()
{
  int i=0;
  element A;
  ifstream f;
  f.open("ELEMENTS.DAT",ios::binary);
  while(f.read( (char*)&A,sizeof(A) ))
  {
	 if(i%14==0)
	 {
      clrscr();
		cout<<"\n       _____________________________________________________________";
		cout<<"\n      | Atomic No. |      Name        |   Atomic Mass    |  Symbol  |";
		cout<<"\n      |____________|__________________|__________________|__________|";
		cout<<"\n      |            |                  |                  |          |";
	 }
	 cout<<"\n      |"<<setw(6)<<A.atomicno<<"      | "<<A.name;
	 for(int j=0;j<17-strlen(A.name);j++)
		cout<<" ";
	 cout<<"|"<<setw(15)<<setprecision(3)<<A.mass<<"   |    "<<A.symbol;
	 for(j=0;j<6-strlen(A.symbol);j++)
		cout<<" ";
	 cout<<"|";
	 if(i%14==13)
	 {
		cout<<"\n      |____________|__________________|__________________|__________|";
		cout<<"\n\n\t      Press any key to display next page......";
      getch();
    }
    i++;
  }
}
void adminmenu()
{
  char ch;
  int choice;
  do
  {
    clrscr();
    cout<<"\n\t  /\\    __         ___                    _"<<endl;      
    cout<<"\t /__\\  |  \\  |\\/|   |   |\\ |        |\\/| |_  |\\ |  |  |"<<endl;
    cout<<"\t |  |  |__/  |  |  _|_  | \\|        |  | |_  | \\|  |__|"<<endl; 
    cout<<"\n\n 1. Display All Data  ";
	 cout<<"\n 2. Insert more elements  ";
	 cout<<"\n 3. Reload default data file ";
	 cout<<"\n 4. Modify by atomic no. ";
	 cout<<"\n 5. Restart";
    cout<<"\n 6. Exit ";
    cout<<"\n\nEnter the choice => ";
    cin>>choice;
    switch(choice)
    {
      case 1 : displayAll(); break;
		case 2 : inputFile(); break;
		case 3 : cout<<"\n\n\t Please wait while file is reloading.......";
					reloadFile();
					cout<<"\n\n\t The file has been reloaded.......";
					cout<<"\n\n\t Press any key to continue.....";
					getch();  break;
      case 4 : modifyRecord(); break;
      case 5 : start(); return;
    }
  }while(choice!=6);
  do
  {
    clrscr();
	 cout<<"\n\n\n\n\n\t\tAre you sure you want to exit (Y/N)....";
    cin>>ch;
	 if(tolower(ch)=='n')
		adminmenu();
	 else if(tolower(ch)=='y')
	 {
		clrscr();
		exit(0);
	 }
  }while(tolower(ch)!='y'&&tolower(ch)!='n');
}
void start()
{
  clrscr();
  char password[]="`password";
  cout<<"\n\n        ____"<<endl;
  cout<<"       |    |"<<endl;
  cout<<"       |    |   ___    ____   _____    ____     ___    _____    ____"<<endl;
  cout<<"       |____|  |      |    |    |     /    \\   |   \\     |     /"<<endl;
  cout<<"       |       |___   |____|    |    |      |  |    |    |    |"<<endl;
  cout<<"       |       |      | \\       |    |      |  |    |    |    |"<<endl;
  cout<<"       |       |___   |  \\    __|__   \\____/   |___/   __|__   \\____"<<endl<<endl;
  cout<<"\t\t      _______         "<<endl;
  cout<<"\t\t         |              "<<endl;
  cout<<"\t\t         |             ___             ___"<<endl;
  cout<<"\t\t         |      /\\    |   \\   |       |"<<endl;
  cout<<"\t\t         |     /__\\   |___/   |       |___"<<endl;
  cout<<"\t\t         |    |    |  |   \\   |       |"<<endl;
  cout<<"\t\t         |    |    |  |___/   |____   |___   "<<endl;
  cout<<"\n\n\n\t\t\tPress any key to continue......";
  int i=0;
  char temp=getch();
  while(temp==password[i++])
  {
    if(password[i]=='\0')
	 adminmenu();
	 temp=getch();
  }
  if(i<strlen(password))
    menu();
}
void main()
{
  start();
}
