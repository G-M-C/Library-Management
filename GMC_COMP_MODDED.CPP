#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
class member
  {
     char memcode[10];
     char memname[20];
     char membno[50];
     int ino;
   public:
	   void member_create()
	     {cout<<"\nNEW MEMBER ENTRY";
	      cout<<"\nEnter Member ID";
	       gets(memcode);
	      cout<<"\nEnter Member Name";
	      gets(memname);
	      ino=0;
	      strcpy(membno,"No book issued");
	      cout<<"\nNEW MEMBER SUCCESSFULLY CREATED";
	      }

	   void member_display()
	     {cout<<"\nMember ID: "<<memcode;
	      cout<<"\nMember Name: "<<memname;
	      cout<<"\nNo of Books issued: "<<ino;
	      cout<<"\nBook Code: "<<membno;}


	   void member_update()
	   {cout<<"\nMember ID: "<<memcode;
	    cout<<"\nMember Name: "<<memname;
	    char ans[3];
	    textcolor(132);cout<<'\n';
	     cprintf("Want to Modify ? (yes/no) ");
	     textcolor(WHITE);
		    cin>>ans;
		    if(strcmpi(ans,"yes")==0)
		    gets(memname);}

	    char* returnmemcode()
	     { return memcode;}
	    char* returnmembno()
	     { return membno;}
	    int returnino()
	     { return ino;}

	    void addino()
	    {ino=1;}
	    void resetino()
	    {ino=0;
	     strcpy(membno,"No book issued"); }
	    void getmembno(char b[])
	     { strcpy(membno,b);}
	    void gen()
	    {cout<<memcode<<setw(30)<<memname<<setw(10)<<ino<<endl;}
	     };








class book
  {
     char bcode[10];
     char bname[25];
     char author[20];


   public:
	   int stock;
	   void book_create()
	     {cout<<"\nNEW BOOK ENTRY";
	      cout<<"\nEnter the book code ";
	      gets(bcode);
	      cout<<"\nEnter the book name" ;
	      gets(bname);
	      cout<<"\nEnter the author's name";
	      gets(author);
	      cout<<"Enter number of copies available";
	      cin>>stock;
	      cout<<"\nNEW BOOK HAS SUCCESSFULLY BEEN ENTERED";
	      }

	   void book_display()
		{
		   cout<<"\nBook Code: "<<bcode;
		   cout<<"\nBook Name: "<<bname;
		   cout<<"\nAuthor   : "<<author;
		   cout<<"\nStock    : "<<stock;}

	  void book_update()
		  { char ans[3];
		    cout<<"\nBook Code : "<<bcode;
		    cout<<"\nBook Name : "<<bname;

		    textcolor(132);
		    cout<<'\n';
		    cprintf("Want to Modify ? (yes/no) ");
		    textcolor(WHITE);
		    cin>>ans;
		    if(strcmpi(ans,"yes")==0)
		    gets(bname);
		    cout<<"\nAuthor: ";
		    textcolor(132);cout<<'\n';
		    cprintf("Want to Modify ? (yes/no) ");
		    textcolor(WHITE);
		    cin>>ans;
		    if(strcmpi(ans,"yes")==0)
		    gets(author);
					   }

	  char* returnbcode()
	  {return bcode;}
	  void gen()
	  {cout<<bcode<<setw(20)<<bname<<setw(20)<<author<<setw(20)<<stock<<endl;
	  }
	  };





fstream fio,fio1;
book bk;
member mem;


void book_write()
 { char ch;
   fio.open("book.dat",ios::out|ios::binary|ios::app);
   do
      { clrscr();
	bk.book_create();
	fio.write((char*)&bk,sizeof(book));
	cout<<"\nWant to add more records ? (y/n)";
	cin>>ch;
	}while(ch=='y' || ch=='Y');
   fio.close();}

void member_write()
 { char ch;
   fio.open("member.dat",ios::out|ios::binary|ios::app);
   do{
       clrscr();
       mem.member_create();
       fio.write((char*)&mem,sizeof(member));
	cout<<"\nWant to add more records ? (y/n)";
	cin>>ch;
	}while(ch=='y' || ch=='Y');
	fio.close(); }

void display_specificbook(char n[])
 { clrscr();
  cout<<"\nBook details\n";
  int flag=0;
  fio.open("book.dat",ios::in|ios::binary);
  while(fio.read((char*)&bk,sizeof(book)))
   {
       if(strcmpi(bk.returnbcode(),n)==0)
       { flag=1;
	 bk.book_display();}}
  fio.close();
  if(flag==0)
   cout<<"\nBook does not exist ";
   getch();}

void display_specificmem(char n[])
{
  cout<<"\nMember details\n";
  int flag=0;
  fio.open("member.dat",ios::in|ios::binary);
  while(fio.read((char*)&mem,sizeof(member)))
    {
      if((strcmpi(mem.returnmemcode(),n)==0))
       { mem.member_display();
	 flag=1;}}
  fio.close();
  if(flag==0)
   cout<<"\nMember does not exist";
   getch();
   }

void modify_book()
{ char n[10];
  int flag=0;
  clrscr();
  cout<<"\nEnter the Book Code";
  cin>>n;
  fio.open("book.dat",ios::in|ios::out|ios::binary);
  while(fio.read((char*)&bk,sizeof(book)))
  {
    if(strcmpi(bk.returnbcode(),n)==0)
      {bk.book_display();
       cout<<"\nEnter new details ";
       bk.book_update();
       int pos=fio.tellp()-sizeof(bk);
       fio.seekp(pos);
       fio.write((char*)&bk,sizeof(book));
       cout<<"\Book Details updated ";
       flag=1;}
  }
  fio.close();
  if(flag!=1)
      cout<<"\Book not found ";
  getch();
  }

  void modify_member()
{ char n[10];
  int flag=0;
  clrscr();
  cout<<"\nEnter the Member Code";
  cin>>n;
  fio.open("member.dat",ios::in|ios::out|ios::binary);
  while(fio.read((char*)&mem,sizeof(member)))
  {
    if(strcmpi(mem.returnmemcode(),n)==0)
      {mem.member_display();
       cout<<"\nEnter new details ";
       mem.member_update();
       int pos=fio.tellp()-sizeof(mem);
       fio.seekp(pos);
       fio.write((char*)&mem,sizeof(member));
       cout<<"\Memeber Details updated ";
       flag=1;}
  }
  fio.close();
  if(flag!=1)
      cout<<"\nMemeber not found ";
  getch();
  }

void delete_book()
{ char n[6];
  clrscr();
  cout<<"\nEnter the Book Code of the book that has to be deleted";
  cin>>n;
  fio.open("book.dat",ios::in|ios::out|ios::binary);
  fio1.open("Temp.dat",ios::out|ios::binary);
  fio.seekg(0,ios::beg);
  while(fio.read((char*)&bk,sizeof(book)))
  {
    if(strcmpi(bk.returnbcode(),n)!=0)
       {fio1.write((char*)&bk,sizeof(book));}
  }
  fio1.close();
  fio.close();
  remove("book.dat");
  rename("Temp.dat","book.dat");
  cout<<"\nRecord is deleted ";
  getch();
  }

void delete_member()
{ char n[6];
  clrscr();
  cout<<"\nEnter the Member Code of the Member record that has to be deleted";
  cin>>n;
  fio.open("member.dat",ios::in|ios::out|ios::binary);
  fio1.open("Temp1.dat",ios::out|ios::binary);
  fio.seekg(0,ios::beg);
  while(fio.read((char*)&mem,sizeof(member)))
  {
    if(strcmpi(mem.returnmemcode(),n)!=0)
       {fio1.write((char*)&mem,sizeof(member));}
  }
  fio1.close();
  fio.close();
  remove("member.dat");
  rename("Temp1.dat","member.dat");
  cout<<"\nRecord is deleted ";
  getch();
  }


void show_all_b()
{clrscr();
 fio.open("book.dat",ios::in,ios::binary);
 if(!fio)
 {cout<<"\nWARNING!!! FILE CAN'T BE OPENED";}
 else
 {cout<<"\n\t\tLIST OF BOOKS\n\n";
  textcolor(129);
  textbackground(RED);
  cprintf("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
  cout<<'\n';
  cout<<"Book Code   "<<setw(1)<<"Book Name  "<<setw(20)<<"Author "<<setw(20)<<"Stock\n";
  textcolor(132);
  textbackground(BLUE);
  cprintf("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
  cout<<'\n';
  textcolor(WHITE);
  textbackground(BLACK);



  while(fio.read((char*)&bk,sizeof(book)))
  {
     bk.gen();
  }}
  fio.close();
  getch();
  }

void show_all_m()
{clrscr();
 fio.open("member.dat",ios::in,ios::binary);
 if(!fio)
 {cout<<"\nWARNING!!! FILE CAN'T BE OPENED";}
 else
 {cout<<"\n\t\tLIST OF MEMBERS\n\n";
   textcolor(129);
  textbackground(RED);
  cprintf("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
  cout<<'\n';
  cout<<"Member Code         "<<setw(10)<<"Member Name   "<<setw(20)<<"Book Issued\n";
 textcolor(132);
  textbackground(BLUE);
  cprintf("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
  cout<<'\n';
  textcolor(WHITE);
  textbackground(BLACK);
  while(fio.read((char*)&mem,sizeof(member)))
  {
     mem.gen();
  }}
  fio.close();
  getch();
}

void issue_book()

{ char m[10],b[10];
  int mflag=0,bflag=0;
  clrscr();
  cout<<"\nBOOK ISSUE";
  cout<<"\nEnter the Member Code";
  cin>>m;
  fio.open("member.dat",ios::in|ios::out|ios::binary);
  fio1.open("book.dat",ios::in|ios::out|ios::binary);
  while(fio.read((char*)&mem,sizeof(member)) && mflag==0)
   {
     if(strcmpi(mem.returnmemcode(),m)==0)
	{
	  mflag=1;
	  if(mem.returnino()==0)
	     {cout<<"\nEnter the Book Code";ofstream bkout;
            bkout.open("temp.dat",ios::out|ios::binary);
	      cin>>b;
	      while(fio1.read((char*)&bk,sizeof(book)) && bflag==0)
		 {if(strcmpi(bk.returnbcode(),b)==0)if(bk.stock!=0)
		  {bk.book_display();
		   bflag=1;bk.stock-=1;
		   mem.addino();
		   mem.getmembno(bk.returnbcode());
		   int pos=fio.tellp()-sizeof(mem);
		   fio.seekp(pos);
		   fio.write((char*)&mem,sizeof(member));
		   cout<<"\nBook Issued Successfully";
		   cout<<"\n!!!..Please write today's date behind the book"
		       <<" a fine or Rs.5 will be charged per day"
		       <<" if not returned in 15 days";
              fio1.seekp(ios::beg);book bo;
	      while(!fio1.eof());
                {if(bo.returnbcode()!=b)
                  {fio1.read((char*)&bo,sizeof(book));
		   bkout.write((char*)&bo,sizeof(book));}
                 else
		   bkout.write((char*)&bk,sizeof(book));}
		 delete("book.dat");
                 rename("temp.dat","book.dat");}
                 
		   else cout<<"No More copies available!lease try again later"<<endl;
		  }
		  if(bflag==0)
		     cout<<"\nBook does not exist ";
	}
	else
	  cout<<"\nThe last book has not been returned ";
   }
  }
    if(mflag==0)
    cout<<"\nMember not found";
    getch();
    fio.close();
    fio1.close();
}

void book_deposit()
{ char m[10],b[10];
  int mflag=0,bflag=0,fine,day;
  clrscr();
  cout<<"\nDEPOSIT BOOK";
  cout<<"\nEnter the Member Code";
  cin>>m;
  fio.open("member.dat",ios::in|ios::out|ios::binary);
  fio1.open("book.dat",ios::in|ios::out|ios::binary);
  while(fio.read((char*)&mem,sizeof(member)) && mflag==0)
     {
	if(strcmpi(mem.returnmemcode(),m)==0)
	   {
	     mflag=1;
	    if(mem.returnino()==1)
		 {
		   while(fio1.read((char*)&bk,sizeof(book)) && bflag==0)
		 {
		    if(strcmpi(bk.returnbcode(),mem.returnmembno())==0)
		     {bk.book_display();
		      bflag=1;
		      cout<<"\nNo:of days after issual ? ";
		      cin>>day;
		      if(day>15)
		       {fine=(day-15)*5;
			cout<<"\nPlease pay a fine of Rs: "<<fine;
		       }
			mem.resetino();
			int pos=fio.tellp()-sizeof(mem);
			fio.seekp(pos);
			fio.write((char*)&mem,sizeof(member));
			cout<<"\nBOOK DEPOSITED SUCCESSFULLY";
		     }
		 }
		 if(bflag==0)
		    cout<<"\nBook does not exist";
		 }
	    else
	       cout<<"\nNo Book was issued !!!";
	    }
       }
       if(mflag==0)
       cout<<"\nMember does not exist";
       getch();
       fio.close();
       fio1.close();
}
void god_mode()
{ clrscr();
  ifstream fin1, fin2;
  fin1.open("member.dat",ios::in|ios::binary);
  fin2.open("book.dat",ios::in|ios::binary);
  remove("member.dat");
  remove("book.dat");
  if(!fin1 && !fin2)
  textcolor(132);
  cout<<'\n';
  cprintf("ALL MEMBER AND BOOK RECORDS ARE DELETED");
  textcolor(WHITE);
  getch();
}

void admin()
 { clrscr();
   int ch;
   textcolor(137);
   cout<<'\n';
   cprintf("LIBRARIAN OPTIONS");
   textcolor(WHITE);
   cout<<"\nPlease choose from the below "
       <<"\n1.Add members"
       <<"\n2.Display all member records"
       <<"\n3.Display the record of a specific member"
       <<"\n4.Modify member record";
   textcolor(BLACK);textbackground(WHITE);cout<<'\n';
       cprintf("5.Delete member record");
   textcolor(WHITE);textbackground(BLACK);
   cout<<"\n6.Add books"
       <<"\n7.Display all book records"
       <<"\n8.Display the record of a specific book"
       <<"\n9.Modify book record";
     textcolor(BLACK);textbackground(WHITE);cout<<'\n';
     cprintf("10.Delete book record");
     textcolor(131);textbackground(RED);cout<<'\n';
     cprintf("11.Erase all records");textbackground(BLACK);
     textcolor(BROWN);cout<<'\n';
     cprintf("12.Return to main menu");
     textcolor(WHITE);
   cin>>ch;
   switch(ch)
    { case 1: clrscr();
	      member_write();break;
      case 2: show_all_m();break;
      case 3: char code[10];
	      clrscr();
	      cout<<"\nPlease enter the member code of record";
	      cin>>code;
	      display_specificmem(code);break;
      case 4: modify_member();break;
      case 5: delete_member();break;
      case 6: clrscr();
	      book_write();break;
      case 7: show_all_b();break;
      case 8: char cd[10];
	      cout<<"\nPlease enter the book code";
	      cin>>cd;
	      display_specificbook(cd);break;
      case 9: modify_book();break;
      case 10: delete_book();break;
      case 11: god_mode();break;
      case 12: return;
	  default:cout<<"\nWrong selection of choice";
      }
      admin();
      }
 void main()
 { int ch;
   do{
      clrscr();
      textcolor(WHITE);
      cprintf("Please choose from the below");
      textcolor(YELLOW);cout<<'\n';
      cprintf("1.Access Librarian Options");
      textcolor(CYAN);cout<<'\n';
      cprintf("2.Issue A Book");
      textcolor(GREEN);cout<<'\n';
      cprintf("3.Deposit A Book");
      textcolor(132);cout<<'\n';
      cprintf("4.Exit");
      textcolor(WHITE);

      cin>>ch;


      if(ch==1)
      {admin();}
      if(ch==2)
      issue_book();
      if(ch==3)
      book_deposit();
      }while(ch!=4);
      getch();
      }
































