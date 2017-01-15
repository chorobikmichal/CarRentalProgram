#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

typedef struct availableNode{
  char plateNum[100];
  int milage;
    struct availableNode *next;
}availableNode;

typedef struct rentedNode{
  char plateNum[100];
  int milage;
  char returnDate[100];
    struct rentedNode *next;
}rentedNode;

typedef struct repairNode{
  char plateNum[100];
  int milage;
    struct repairNode *next;
}repairNode;

//-------------------AVAILABLE NODE FUNC DECLARATIONS------------------------------
availableNode* createRecord_A(char data[100],int milage);
availableNode* add_Front_A(availableNode* theList, availableNode* toBeAdded);
void itemPrint_A(availableNode * theList);
void sort_node_A (availableNode* head);
//-------------------RENTED NODE FUNC DECLARATIONS------------------------------
rentedNode* createRecord_R(char returnDate[100],availableNode* source);
rentedNode* add_Front_R(rentedNode* theList, rentedNode* toBeAdded);
void itemPrint_R(rentedNode * theList);
availableNode* remove_R(availableNode* head);
void sort_node_R (rentedNode* head);
rentedNode* move_R(rentedNode* head,char plate[100]);
//-------------------REPAIR NODE FUNC DECLARATIONS------------------------------
repairNode* createRecord_RP(char data[100],int milage);
repairNode* add_Front_RP(repairNode* theList, repairNode* toBeAdded);
void itemPrint_RP(repairNode * theList);
repairNode* move_RP(repairNode* head,char plate[100]);
//----------------------PARSING-------------------------------------------------
availableNode* ava_parsing(FILE* fp,availableNode* head);
rentedNode* rented_parsing(FILE* fp,rentedNode* rented_head);
repairNode* repair_parsing(FILE* fp,repairNode* repair_head);
//----------------------SAVING DATA---------------------------------------------
void ava_save(FILE* fp,availableNode* head);
void rented_save(FILE* fp,rentedNode* head);
void repair_save(FILE* fp,repairNode* head);

int main(){

  availableNode* ava_head=NULL;
  availableNode* ava_record = NULL;
  rentedNode* rented_head=NULL;
  rentedNode* rented_record = NULL;
  rentedNode* current=NULL;
  repairNode* repair_head=NULL;
  repairNode* repair_record = NULL;

  int choice;
  char str1[100];
  int milage;
  char returnDate[100];
  double price=0;
  double income=0;
  double diffrence=0;

  FILE* fp;
  fp = fopen("data.txt","r");
  ava_head=ava_parsing(fp,ava_head);
  rented_head=rented_parsing(fp,rented_head);
  fclose(fp);


  while(choice!=7){

    printf("\nchoose one of the options by entering the choice number\n");
    printf("(1) add a new car to the available-for-rent list\n");
    printf("(2) add a returned car to the available-for-rent list\n");
    printf("(3) add a returned car to the repair list\n");
    printf("(4) transfer a car from the repair list to the available-for-rent list\n");
    printf("(5) rent the first available car\n");
    printf("(6) print all the lists\n");
    printf("(7) quit\n");

    scanf("%d",&choice);

    switch(choice) {
      case 1  :
        printf("Enter the lisence plate of the car (the format should be AAAA-000)\n");
        scanf("%s", &str1);
        if((strlen(str1)>8)||(strlen(str1)<8)){
          printf("Wrong input. (the format should be AAAA-000)\n");
          break;
        }
        printf("Enter the milage of the car\n");
        scanf("%d", &milage);//the new line character caused this statement to be skipped so i had to put it twice

        ava_record = createRecord_A(str1, milage);
        ava_head = add_Front_A(ava_head,ava_record);
        if(ava_head->next!=NULL){
          sort_node_A (ava_head);
        }
        break;
      case 2  :
        printf("Enter the lisence plate of the car (the format should be AAAA-000)\n");
        scanf("%s", &str1);
        if((strlen(str1)>8)||(strlen(str1)<8)){
          printf("Wrong input. (the format should be AAAA-000)\n");
          break;
        }
        printf("Enter the milage of the car\n");
        scanf("%d", &milage);//the new line character caused this statement to be skipped so i had to put it twice

        current = rented_head;
        while((strcmp(current->plateNum,str1)!=0)){
          current=current->next;
        }
        diffrence=milage-current->milage;

        printf("A car has been returned and was added to the available car list\n");
        printf("• a flat rate of $40.00 for up to 100 km\n");
        printf("• 15 cents per km for the additional %lf kilometers.\n",diffrence);

        price=40;
        if(diffrence>100){
          diffrence=diffrence-100;
          diffrence=diffrence*0.15;
          price=price+diffrence;
        }
        income=income+price;

        rented_head = move_R(rented_head,str1);
        availableNode* ava_node =createRecord_A(str1,milage);
        ava_head = add_Front_A(ava_head,ava_node);
        if(ava_head->next!=NULL){
          sort_node_A(ava_head);
        }
        break;
      case 3  :
        printf("Enter the lisence plate of the car (the format should be AAAA-000)\n");
        scanf("%s", &str1);
        if((strlen(str1)>8)||(strlen(str1)<8)){
          printf("Wrong input. (the format should be AAAA-000)\n");
          break;
        }
        printf("Enter the milage of the car\n");
        scanf("%d", &milage);//the new line character caused this statement to be skipped so i had to put it twice

        current = rented_head;
        while((strcmp(current->plateNum,str1)!=0)){
          current=current->next;
        }
        diffrence=milage-current->milage;

        printf("A car has been returned and was added to the repair car list\n");
        printf("• a flat rate of $40.00 for up to 100 km\n");
        printf("• 15 cents per km for the additional %lf kilometers.\n",diffrence);

        price=40;
        if(diffrence>100){
          diffrence=diffrence-100;
          diffrence=diffrence*0.15;
          price=price+diffrence;
        }
        income=income+price;

        rented_head = move_R(rented_head,str1);
        repairNode* rp_node =createRecord_RP(str1,milage);
        repair_head = add_Front_RP(repair_head,rp_node);
        break;
      case 4  :
        printf("Enter the lisence plate of the car (the format should be AAAA-000)\n");
        scanf("%s", &str1);
        if((strlen(str1)>8)||(strlen(str1)<8)){
          printf("Wrong input. (the format should be AAAA-000)\n");
          break;
        }
        //We here find the proper milage for the createRecord_A to recieve
        repairNode* current = repair_head;
        while((strcmp(current->plateNum,str1)!=0)){
          current=current->next;
        }
        milage=current->milage;

        repair_head = move_RP(repair_head,str1);
        ava_node =createRecord_A(str1,milage);
        ava_head = add_Front_A(ava_head,ava_node);
        if(ava_head->next!=NULL){
          sort_node_A(ava_head);
        }
        break;
      case 5  :
        printf("Please enter the return date of the car(yymmdd)\n");
        scanf("%s",&returnDate);
        if((strlen(returnDate)>6)||(strlen(returnDate)<6)){
          printf("Wrong input. (the format should be yymmdd)\n");
          break;
        }
        rented_record = createRecord_R(returnDate,ava_head);
        rented_head = add_Front_R(rented_head,rented_record);
        ava_head=(remove_R(ava_head));
        if(rented_head->next!=NULL){
          sort_node_R(rented_head);
        }
        break;
      case 6  :
        itemPrint_A(ava_head);
        itemPrint_R(rented_head);
        itemPrint_RP(repair_head);

        break;
      case 7  ://QUIT
        printf("TOTAL INCOME WAS %.2lf$\n",income);
        break;
      default :
        printf("This choice was not an option\n");
        break;
    }
  }//while loop ends

//----------------------------I write the data file here---------------------------------------------
  fp = fopen("data.txt","w");
  ava_save(fp,ava_head);
  rented_save(fp,rented_head);
  repair_save(fp,repair_head);
  fclose(fp);

}
//--------------------------AVAILABLE NODE FUNCTIONS----------------------------------
availableNode* createRecord_A(char data[100],int milage){

  availableNode* n = malloc(sizeof(availableNode));

  for(int i=0; i<8; i++){
    n->plateNum[i]=data[i];
  }

  n->milage = milage;
  n->next = NULL;

  return n;
}
availableNode* add_Front_A(availableNode* theList, availableNode* toBeAdded){

	if(theList!=NULL) {
		toBeAdded->next = theList;
		return toBeAdded;
	} else {
    theList=toBeAdded;
		theList->next=NULL;
		return theList;
	}
}
void itemPrint_A(availableNode * theList) {
  printf("available cars\n");

		while(theList!=NULL) {

			printf("Car name: %s ",theList->plateNum);
			printf("Milage : %d\n\n",theList->milage);

			theList=theList->next;
		}
}
void sort_node_A (availableNode* head){

  availableNode* current = head;
  availableNode* next = head->next;
  int temp1;
  char temp2;

  do{
    if((current->milage)>(next->milage)){
      temp1 = current-> milage;
      current->milage=next->milage;
      next->milage=temp1;

      for(int y=0;y<9;y++){
        temp2 = current->plateNum[y];
        current->plateNum[y]=next->plateNum[y];
        next->plateNum[y]=temp2;
      }
    }
    current = next;
    next = next->next;

  }while(next!=NULL);//while loop ends
}
//--------------------------RENTED NODE FUNCTIONS----------------------------------
rentedNode* createRecord_R(char returnDate[100],availableNode* source){
  char data[100];
  int milage;
  rentedNode* n =malloc(sizeof(availableNode));

  for(int i=0; i<8; i++){
    n->plateNum[i]=source->plateNum[i];
  }

  n->milage = source->milage;
  n->next = NULL;

  for(int s=0; s<6; s++){
    n->returnDate[s] = returnDate[s];
  }
  return n;
}
rentedNode* add_Front_R(rentedNode* theList, rentedNode* toBeAdded){

	if(theList!=NULL) {
		toBeAdded->next = theList;
		return toBeAdded;
	} else {
    theList=toBeAdded;
		theList->next=NULL;
		return theList;
	}
}
void itemPrint_R(rentedNode * theList) {

  printf("rented cars\n");
	while(theList!=NULL) {

    printf("Car name: %s ",theList->plateNum);
		printf("Milage : %d ",theList->milage);
    printf("Return Date: %s \n\n",theList->returnDate);
		theList=theList->next;
		}
}
availableNode* remove_R(availableNode* head){
  availableNode*temp=head;
  head=head->next;
  free(temp);
  return(head);
}
void sort_node_R (rentedNode* head){

  rentedNode* current = head;
  rentedNode* next = head->next;
  int temp1;
  char temp2;
  int check=0;

  do{

    char pos0[2];
    pos0[0]= current->returnDate[0];
    char pos1[2];
    pos1[0]= current->returnDate[1];
    char pos2[2];
    pos2[0]= current->returnDate[2];
    char pos3[2];
    pos3[0]= current->returnDate[3];
    char pos4[2];
    pos4[0]= current->returnDate[4];
    char pos5[2];
    pos5[0]= current->returnDate[5];

    char next_pos0[2];
    next_pos0[0]= next->returnDate[0];
    char next_pos1[2];
    next_pos1[0]= next->returnDate[1];
    char next_pos2[2];
    next_pos2[0]= next->returnDate[2];
    char next_pos3[2];
    next_pos3[0]= next->returnDate[3];
    char next_pos4[2];
    next_pos4[0]= next->returnDate[4];
    char next_pos5[2];
    next_pos5[0]= next->returnDate[5];

      if((atoi(pos1)+(10*atoi(pos0)))>(atoi(next_pos1)+(10*atoi(next_pos0)))){
        check++;
      } else if((atoi(pos1)+(10*atoi(pos0)))==(atoi(next_pos1)+(10*atoi(next_pos0)))){
        if((atoi(pos3)+(10*atoi(pos2)))>(atoi(next_pos3)+(10*atoi(next_pos2)))){
          check++;
        }
      } else if((atoi(pos1)+(10*atoi(pos0)))==(atoi(next_pos1)+(10*atoi(next_pos0)))){
        if((atoi(pos3)+(10*atoi(pos2)))==(atoi(next_pos3)+(10*atoi(next_pos2)))){
          if((atoi(pos5)+(10*atoi(pos4)))>(atoi(next_pos5)+(10*atoi(next_pos4)))){
            check++;
          }
        }
      }

    if(check>0){

      temp1 = current-> milage;
      current->milage=next->milage;
      next->milage=temp1;

      for(int y=0;y<8;y++){
        temp2 = current->plateNum[y];
        current->plateNum[y]=next->plateNum[y];
        next->plateNum[y]=temp2;
      }

      for(int x=0;x<6;x++){
        temp2 = current->returnDate[x];
        current->returnDate[x]=next->returnDate[x];
        next->returnDate[x]=temp2;
      }
    }
    current = next;
    next = next->next;
    check=0;

  }while(next!=NULL);//while loop ends

}
rentedNode* move_R(rentedNode* head,char plate[100]){
  rentedNode* current = head;
  rentedNode* n = NULL;

  //When there is only one item in the list
  if(current->next==NULL){
    //free(current);
    return(NULL);
  }

  while((strcmp(current->plateNum,plate)!=0)){
    n=current;
    current=current->next;
  }
  if(current->next!=NULL){
      n->next=current->next;
  }else{
      n->next=NULL;
  }
  //free(current);
  return(head);
}

//--------------------------REPAIR NODE FUNCTIONS----------------------------------
repairNode* createRecord_RP(char data[100],int milage){

  repairNode*n;
  n=malloc(sizeof(availableNode));

  for(int i=0; i<8; i++){
    n->plateNum[i]=data[i];
  }
  n->milage = milage;
  n->next = NULL;

  return n;
}
repairNode* add_Front_RP(repairNode* theList, repairNode* toBeAdded){

	if(theList!=NULL) {
		toBeAdded->next = theList;
		return toBeAdded;
	} else {
    theList=toBeAdded;
		theList->next=NULL;
		return theList;
	}
}
void itemPrint_RP(repairNode * theList) {
  printf("Cars for Repair\n");

		while(theList!=NULL) {

      printf("Car name: %s ",theList->plateNum);
			printf("Milage : %d\n\n",theList->milage);

			theList=theList->next;
		}
}
repairNode* move_RP(repairNode* head,char plate[100]){
  repairNode* current = head;
  repairNode* n = NULL;

  //When there is only one item in the list
  if(current->next==NULL){
    //free(current);
    return(NULL);
  }

  while((strcmp(current->plateNum,plate)!=0)){
    n=current;
    current=current->next;
  }

  if(current->next!=NULL){
      n->next=current->next;
  }else{
      n->next=NULL;
  }
  //free(current);
  return(head);
}
availableNode* ava_parsing(FILE* fp,availableNode* ava_head){

  char word[100];
  char plate[100];
  char milageS[100];
  int milage;
  char pos[100];

  while(1){
    fscanf(fp, "%s", word);
    if(feof(fp)){
      break ;
    }
    if(strcmp(word,"ava")==0){
      fscanf(fp, "%s", pos);
      int length = atoi(pos);
      for(int u=0;u<length;u++){
        fscanf(fp, "%s", plate);
        fscanf(fp, "%s", milageS);
        milage=atoi(milageS);
        availableNode* ava_record=NULL;

        ava_record = createRecord_A(plate, milage);
        ava_head = add_Front_A(ava_head,ava_record);
        if(ava_head->next!=NULL){
          sort_node_A (ava_head);
        }
      }
      break ;
    }
  }

  return(ava_head);
}
rentedNode* rented_parsing(FILE* fp,rentedNode* rented_head){

  char word[100];
  char plate[100];
  char milageS[100];
  int milage;
  char pos[100];
  char returnDate[100];

  fseek(fp, 0, 0);

  while(1){
    fscanf(fp, "%s", word);
    if(feof(fp)){
      break ;
    }
    if(strcmp(word,"r")==0){
      fscanf(fp, "%s", pos);
      int length = atoi(pos);
      for(int q=0;q<length;q++){
        fscanf(fp, "%s", plate);
        fscanf(fp, "%s", milageS);
        fscanf(fp, "%s", returnDate);
        milage=atoi(milageS);

//-----------this node has to be created here cause createRecord_R expects all the info to be passes from available car list-------------------------------
        rentedNode*n;
        n=malloc(sizeof(rentedNode));
        for(int i=0; i<8; i++){
          n->plateNum[i]=plate[i];
        }
        n->milage = milage;
        n->next = NULL;
        for(int r=0; r<6; r++){
          n->returnDate[r]=returnDate[r];
        }
//----------------------------------------------------------------------------------

        rented_head = add_Front_R(rented_head,n);
        if(rented_head->next!=NULL){
          sort_node_R(rented_head);
        }
      }
      break ;
    }
  }
  return(rented_head);
}

repairNode* repair_parsing(FILE* fp,repairNode* repair_head){

    char word[100];
    char plate[100];
    char milageS[100];
    int milage;
    char pos[100];

    fseek(fp, 0, 0);

    while(1){
      fscanf(fp, "%s", word);
      if(feof(fp)){
        break ;
      }
      if(strcmp(word,"rp")==0){
        fscanf(fp, "%s", pos);
        int length = atoi(pos);
        for(int q=0;q<length;q++){
          fscanf(fp, "%s", plate);
          fscanf(fp, "%s", milageS);
          milage=atoi(milageS);

          repairNode* rp_node =createRecord_RP(plate,milage);
          repair_head = add_Front_RP(repair_head,rp_node);
        }
        break ;
      }
    }
    return(repair_head);
  }
//-------------------------------SAVING DATA------------------------------------
void ava_save(FILE* fp,availableNode* head){

  int count=0;
  availableNode* n=head;

  if(head!=NULL){
    count=1;
    while(head->next!=NULL){
      count++;
      head=head->next;
    }
    fprintf(fp, "ava %d ",count);
    for(int x=0;x<count;x++){
      fprintf(fp, "%s %d ",n->plateNum,n->milage);
      n=n->next;
    }
  }

}
void rented_save(FILE* fp,rentedNode* head){

  int count=0;
  rentedNode* n=head;

  if(head!=NULL){
    count=1;
    while(head->next!=NULL){
      count++;
      head=head->next;
    }
    fprintf(fp, "r %d ",count);

    for(int x=0;x<count;x++){

        fprintf(fp, "%s %d %s ",n->plateNum,n->milage,n->returnDate);
    }
  }

}
void repair_save(FILE* fp,repairNode* head){

  int count=0;
  repairNode* n=head;

  if(head!=NULL){
    count=1;
    while(head->next!=NULL){
      count++;
      head=head->next;
    }
    fprintf(fp, "rp %d ",count);
    for(int x=0;x<count;x++){
      fprintf(fp, "%s %d ",n->plateNum,n->milage);
      n=n->next;
    }
  }
}
