#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
struct Stack
{
 int data;
 struct Stack* next;
};

struct Stack* createStack()
{ 
  struct Stack* stack=(struct Stack*)malloc(sizeof(struct Stack));
  stack=NULL;
  return stack;
}

void push(struct Stack** stack,int item)
{
 struct Stack* temp=(struct Stack*)malloc(sizeof(struct Stack));
 temp->data=item;
 if(*stack == NULL)
 {
  *stack =temp;
  temp->next=NULL;
  }
 else 
 {
  temp->next=*stack;
  *stack=temp;
  }
}

int pop(struct Stack** stack)
{
 if(*stack == NULL)
 { 
  return INT_MIN;
 }
 struct Stack* temp=*stack;
 int item;
 *stack=(*stack)->next;
 item =temp->data;
 free(temp);
 return item;
}
void moveDisk(char fromPole,char toPole,int disk);
void moveDiskBetweenTwoPoles(struct Stack** src, struct Stack** dest,char s, char d)
{
 int pole1TopDisk=pop(src);
 int pole2TopDisk=pop(dest);
 if(pole1TopDisk==INT_MIN)
 {
  push(src,pole2TopDisk);
  moveDisk(d,s,pole2TopDisk);
 }
 else if(pole2TopDisk==INT_MIN)
 {
  push(dest,pole1TopDisk);
  moveDisk(s,d,pole1TopDisk);
 }
 else if(pole1TopDisk > pole2TopDisk)
 {
  push(src,pole1TopDisk);
  push(src,pole2TopDisk);
  moveDisk(d,s,pole2TopDisk);
 }
 else
 {
  push(dest,pole2TopDisk);
  push(dest,pole1TopDisk);
  moveDisk(s,d,pole1TopDisk);
 }
}

void moveDisk(char fromPole,char toPole,int disk)
{
 printf("move disk %d from %c and %c\n",disk,fromPole,toPole);
}

void TohIterative(int num_of_disks,struct Stack* src,struct Stack* aux,struct Stack* dest)
{
 int i ,total_moves;
 char s= 'S',d='D',a='A';
 if(num_of_disks%2==0)
 {
  char temp=d;
  d=a;
  a=temp;
 }
 total_moves=pow(2,num_of_disks)-1;
printf("no.of moves are : %d",total_moves);
 for (int i=num_of_disks;i>=1;i--)
 {
  push(&src,i);
 }
 for (i=1;i<=total_moves;i++)
 {
  if(i%3==1){moveDiskBetweenTwoPoles(&src,&dest,s,d);}
  if(i%3==2){moveDiskBetweenTwoPoles(&src,&aux,s,a);}
  if(i%3==0){moveDiskBetweenTwoPoles(&aux,&dest,a,d);}
 }
}
int main()
{
 unsigned int num_of_disk=3;
 struct Stack* src,*dest,*aux;
 src=createStack();
 aux=createStack();
 dest=createStack();
 TohIterative(num_of_disk,src,aux,dest);
 return 0;
}