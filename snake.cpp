#include<bits/stdc++.h>
#include<string>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#define MAX 17
using namespace std;
void someInitialValueOfSnake();
class snake{
	public:
	int x,y;
	char a;

	snake *next;
	snake(){

		next=NULL;
		a='+';
	}
};


class food{
	public:
	int x,y;
	char a;
	food(){
		a='$';
	}
};

class Data_BASE{

	public:
	void put(char* str,int len)
		  {
            
		   ofstream file;
		   ofstream myfile ("example.txt");
            for(int i=0;i<len;i++)
        	myfile<<str[i];
		   myfile.close();
		 

		  }

    void get(char* str,int&len)
		  {

	
           ifstream is ("example.txt");
        	   char c;
 			 while (is.get(c))        
 			   str[len++]=c;

				  str[len]='\0';
				  
				 is.close();
		  }

};

void changeDirection(snake *head,int x,int y,char mat[MAX][MAX]){

while(head){
			swap(head->x,x);
			swap(head->y,y);
			head=head->next;
		}
		mat[x][y]='`';

}

snake* createSnakeLength(snake*head,food *f){

    snake *temp=new snake;
	temp->a='O';
	head->a='+';
	temp->x=f->x;
	temp->y=f->y;
	temp->next=head;
	return temp;
	}
void moveSnake(char mat[MAX][MAX],snake*head){
    while(head){
    	if(head->x>-1&&head->y>-1)mat[head->x][head->y]=head->a;

    	//cout<<head->x<<head->y<<endl;
    	head=head->next;

	}
}
void moveFood(char mat[MAX][MAX],food *f){
   mat[f->x][f->y]=f->a;
}
bool snakeGetKilled(snake* head){
	snake* temp=head;
	head=head->next;
	while(head&&!(temp->x==head->x&&head->y==temp->y)){
		head=head->next;
	}
	if(head)return true;
	return false;
}
void printBoard(char mat[MAX][MAX],int score){ 
for(int i=0;i<=MAX*2;i++)
   cout<<"X";
cout<<endl;
	for(int i=0;i<MAX;i++){
	cout<<"X";

		for(int j=0;j<MAX;j++){
			if(mat[i][j]=='`')
			cout<<" ";
			else cout<<mat[i][j];
			if(j!=MAX-1)cout<<" ";
		}
			cout<<"X";
			cout<<endl;
	}
	for(int i=0;i<=MAX*2;i++)cout<<"X";
		cout<<endl;
  cout<<"Score:- "<<score;
    
}

void intilize(char mat[MAX][MAX]){
		for(int i=0;i<MAX;i++)
			for(int j=0;j<MAX;j++)
			mat[i][j]='`';
}
int isCorrectDirection(char pre,char dir){

if(pre=='a'&&dir=='d' ||pre=='A'&&dir=='D'||pre=='W'&&dir=='S'||pre=='w'&&dir=='s'||
pre=='d'&&dir=='a'||pre=='D'&&dir=='A'||pre=='S'&&dir=='W'||pre=='s'&&dir=='w'
) return 0;

if(dir=='w'||dir=='s'||dir=='a'||dir=='d')
  return 1;
return 0;

}
void direction(char dir,snake* head,char mat[MAX][MAX]){

int x,y;
      y=head->y;
      x=head->x;
	if(dir=='w'||dir=='W'){
	    if(head->x==0){
	    head->x=MAX-1;
	    }else head->x--;


	}else if(dir=='A'||dir=='a'){

	   if(head->y==0)
	     head->y=MAX-1;
	     else head->y--;
	}else if(dir=='d'||dir=='D'){
	if(head->y==MAX-1)
	head->y=0; else head->y++;

	}else if(dir=='s'||dir=='S'){
	if(head->x==MAX-1)
	head->x=0;
	else head->x++;
	}else if(dir=='p') return ;


    changeDirection(head->next,x,y,mat);
}


void newFoodPosition(food *f){
f->x=abs(rand()*7+10007+73+1L<<7)%MAX;
f->y=abs(rand()*31+10007+73+1L<<13)%MAX;
}


 void someInitialValueOfSnake(){
 
   int x=abs(rand()*7+10007-131<<3)%(MAX-MAX/2);
   int y=rand()%MAX;
  
    char str[100];
    int len=0;
    str[len++]=0;
    str[len++]='w';
    str[len++]='O';
    str[len++]=x;
    str[len++]=y;
    for(int i=0;i<2;i++){
    	 x++;
    	 str[len++]='+';
         str[len++]=x;
         str[len++]=y;
    }
    str[len]='\0';
	Data_BASE obj;
	obj.put(str,len);
 }
 
 int sankeGetFood(food*f,snake *head,char dir){
 int x=0;
 int y=0;
 if(dir=='w'){
 		x--;
 		if(head->x==0)x=MAX-1;

 }
 else if(dir=='s')x++;
 else if(dir=='a'){
 	y--;
 	if(head->y==0)y=MAX-1;
 }
 else if(dir=='d')y++;


 if((head->x+x)%MAX==f->x&&(head->y+y)%MAX==f->y)return 1;
 return 0;
 }
 int isCollide(food*f ,snake* head){

 	while(head){
 		if(f->x==head->x&&f->y==head->y)return 1;
 		head=head->next;
 	}
 	return 0;
 }

 snake* initilizeSnake(char *dir,int&score){
snake* head=NULL,*qhead=NULL;
char str[100];
int tlen=0;
Data_BASE obj;
obj.get(str,tlen);
if(tlen==0){
someInitialValueOfSnake();
obj.get(str,tlen);
}
int x,y;
score=(int)str[0];
*dir=str[1];
for(int i=2;str[i];)
  {
  	snake* temp=new snake;
	temp->a=str[i++]; 
    x=(int)str[i++]; 
   y=(int)str[i++]; 
   temp->x=x;
   temp->y=y;
    if(head==NULL){
    	head=qhead=temp;
    }else{
    	qhead->next=temp;
    	qhead=qhead->next;
    }
  
  }


  
    return head;
}
void gameOver(int score){
 
  someInitialValueOfSnake();

    system("cls");
    cout<<"\a\a\a\a\a\a\a\a";
    cout<<endl<<endl<<endl<<endl<<"\t\t\t\t\t\t\tGame Over"<<endl;
    cout<<"\t\t\t\t\t\t\tScore :- "<<score;
    cout<<endl<<endl<<endl<<endl;
     //someInitialValueOfSnake();
  
    getch();
    exit(0);

}

void save(snake* head,char dir,int score){
    Data_BASE obj;
    char str[100];
    int len=0;
    str[len++]=score;
    str[len++]=dir;
 
  while(head){
  	str[len++]=head->a;
  	str[len++]=head->x;
  	str[len++]=head->y;
  	head=head->next;
  }
 
  str[len]='\0';
  obj.put(str,len);
 exit(0);
	
}

void welcomescreen(){
	cout<<"-------------------------------------------"<<endl;
	cout<<"|    ____  ___   __ ____   _    __  ____   |"<<endl;
	cout<<"|   [  _*||   \\ | || __ | | |  / / | ___|  |"<<endl;
	cout<<"|   | {   | |\\ \\| |||__|| | |_/ /  |{__    |"<<endl;
	cout<<"|    \\ \\  | | \\ | |||  || | | \\ \\  |{___   |"<<endl;
	cout<<"|   __}_} |_|  |__|||  || |_|  \\_| |____|  |"<<endl;
	cout<<"|                                      GAME|"<<endl;
	cout<<"|  ->Enter 1 for a new game                |"<<endl;
	cout<<"|  ->Enter 2 to  resume game	           |"<<endl;	
	cout<<"-------------------------------------------|"<<endl;	
}

int main(){
	system("mode con: cols=45 lines=14");
	char mat[MAX][MAX];
	char dir,pre;
	int score=0;
	food f;
	welcomescreen();
	
    int choice;
    cin>>choice;
    if(choice==1)
 	  someInitialValueOfSnake();
 	  	system("mode con: cols=36 lines=20");
	
   	long unsigned int speed=170.00;
          snake* head=NULL;
          head= initilizeSnake(&dir,score);
          pre=dir;
          newFoodPosition(&f);
          intilize(mat);
          srand(time(0));
              while(1){

                moveSnake(mat,head);
                moveFood(mat,&f);
                system("cls");
                printBoard(mat,score);
                _sleep(speed);
                	 if(kbhit())
	    				{
	    					dir=getch();
	    					if(dir=='e'||dir=='E')
	    					     save(head,pre,score);

	    				}
		 
		  if(isCorrectDirection(pre,dir))
		           pre=dir;      
		   
		   char temp=pre;						
					    if(sankeGetFood(&f,head,temp)){
					            cout<<"\a";
					            head=createSnakeLength(head,&f);
					             score++;
					          do{
					              newFoodPosition(&f);
					             }while(isCollide(&f,head));
					         }
							else direction(temp,head,mat);
					                      
					        if(snakeGetKilled(head)){
					            gameOver(score);
					     }
					                 

            }



}

