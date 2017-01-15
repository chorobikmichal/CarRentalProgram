#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

/*******************
Michal Chorobik
0937145
Assignment 3
October 6, 2016
*******************/

double stack[100];
int top=-1;

//Adds a double into the stack
void push(double c);
//pulls the lastly added double from the stack
double pop();

void main (int argc, char *argv[]){
  char tempNum[2];
  double temp1,temp2;

  int len=strlen(argv[1]);

  for(int i=0;i<len;i++){

    if(isdigit(argv[1][i])){
      tempNum[0]=argv[1][i];
      tempNum[1]='\0';
      push(atoi(tempNum));
    } else {
      temp1=pop();
      temp2=pop();

      if(argv[1][i]=='+'){
        push(temp2+temp1);
      } else if (argv[1][i]=='-'){
        push(temp2-temp1);
      } else if (argv[1][i]=='*'){
        push(temp2*temp1);
      } else if (argv[1][i]=='/'){
        if(temp1==0){
          printf("Wrong input. Cannot divide by zero \n");
          exit(0);//stack is full
        }
        push(temp2/temp1);
      }
    }

  }

    temp1=pop();
    printf("the answer is %.2lf \n",temp1);

}

void push(double c){
  stack[++top]=c;//++top would increment it and apply the change in that same line
}

double pop(){
  if(top<0){
    printf("Wrong input \n");
    exit(0);//stack is full
  }
  return stack[top--];
}
