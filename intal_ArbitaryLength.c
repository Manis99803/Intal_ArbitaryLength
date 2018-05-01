#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct format{
    int numberOfDigit;              //Number of Digits in a intal
    short int *data;                
    
};
typedef struct format* format;


void* intal_create(char* str){
    format intal;
    intal = (format)malloc(sizeof(struct format));
    char* copyString = malloc(sizeof(char) * strlen(str) + 1);
    strcpy(copyString, str);
    intal->numberOfDigit = strlen(str);
    intal->data = (short int*)malloc(sizeof(short int) * (intal->numberOfDigit) +1);
    int  i;
    for (i = 0; i < intal->numberOfDigit; i++) {
        if(copyString[i]<='9' && copyString[i]>='0')           //Condition to check wheter all the passed string doesn't contain any special character
          intal->data[i] = copyString[i] - '0';
        else
          return intal_create("0");              //If the passed string has charcater other than number return NULL pointer
    }
    return intal;
}


char* intal2str(void* temp){
    //char* str = malloc(sizeof(char)*length+1);
    if(temp==NULL){
      char *str;
      str=malloc(sizeof(char)*4);
      strcpy(str,"NaN");
      return str;             //If the pointer is NULL which means it is Not a number
    }
    format intal;
    intal = temp;
    int length = intal->numberOfDigit,i;
    char* str = malloc(sizeof(char)*length+1);
    if(intal->numberOfDigit == 1 && intal->data[0] == 0){       
        str[0] = '0';
        str[1] = 0;
        return str;
    }
    while(intal->data[0] == 0 && length > 1){         //Checking for the extra zero's in the beginning
      intal->data++;
      length--;
    }
    if(length == 0){                              //After checking for the extra zero condtion if the length reduces to zero which means the number is zero 
        str[0] = '0';
        str[1] = 0;
        return str;
    }
    for (i = 0; i < length; i++) {
      str[i] = (intal->data[i]) + '0';
    }
    intal->numberOfDigit = length;
    str[length] = 0;
    return str;
}
void intal_destroy(void* intal)
{
  format intal1=intal;
  if(intal1!=NULL){
    free(intal1);
  }
}
void* intal_add(void *intal1,void *intal2){
  if(intal1==NULL || intal2==NULL){
    return NULL;

  }
  char *str1,*str2;
  format temp1,temp2,temp3;
  str1=intal2str(intal1);
  str2=intal2str(intal2);
  int lengthDifference,length1,length2;
  length1=((format )intal1)->numberOfDigit;
  length2=((format )intal2)->numberOfDigit;
  char *tempString;
  
  if(length1>length2){              //We ar making sure that the length of intal2 is bigger than the length of intal1
    
    str1=intal2str(intal2);
    str2=intal2str(intal1);
  } 
  length1=strlen(str1);
  length2=strlen(str2);
  char *str3=malloc(sizeof(char)*(length2)+1);        //Empty string for storing the result it will have result in  reverse order
  char *str4=malloc(sizeof(char)*(length2+1));        //Final string which will have the result 
  lengthDifference=length2 - length1;
  int carry=0,q=0,i;
  for(i=length1-1;i>=0;i--){                          //Performing basic addition process
    int sum=((str1[i]-'0')+(str2[i+lengthDifference]-'0')+carry);
    str3[q]=(sum%10+'0');
    q++;
    carry=sum/10;
  }
  for(i=length2-length1-1;i>=0;i--){
    int sum=(str2[i]-'0')+carry;
    str3[q]=sum%10+'0';
    q++;
    carry=sum/10;
  }
  if(carry){
    str3[q]=carry+'0';

  }
  str3[i]='\0';
  int k=0;
  for(i=q;i>=0;i--){
    if((str3[i]>='0') && (str3[i]<='9')){
      str4[k]=str3[i];
      k++;
    }
    
  }
  str4[k]='\0';
  format  sum=intal_create(str4);
  return (void*)sum;
}
int intal_compare(void *intal1,void *intal2){
  if(intal1==NULL || intal2==NULL)
    return -2;
  if(((format )intal1)->numberOfDigit>((format )intal2)->numberOfDigit){
    return 1;
  }
  else if(((format )intal1)->numberOfDigit<((format )intal2)->numberOfDigit)
    return -1;
  else{
    int i=0,count=0;
    char *str1;
    char *str2;
    str1=intal2str(intal1);
    str2=intal2str(intal2);
    for(i=0;i<strlen(str1);i++){
      if(str1[i]>str2[i])
        return 1;
      else if(str1[i]<str2[i])
        return -1;
      else
        count+=1;
    }
    if((count == strlen(str1)) && (count ==strlen(str2)))
      return 0;
  }
}

void* intal_increment(void* intal){
  if(intal==NULL){
    void *new_intal=NULL;
    return new_intal;

  }
  int length,i,carry;
  length=((format )intal)->numberOfDigit;
  carry=((format )intal)->data[length-1]+1;
  if(carry<9){
    ((format )intal)->data[length-1]+=1;
    return intal;
  }
  int j=0,carryForward=0;
  for(i=length-1;i>=0;i--){
    if(i==length-1) carry=((format )intal)->data[i]+1+carryForward;
    else carry=((format )intal)->data[i]+carryForward;
    if(carry>9){
      carryForward=1;
      ((format )intal)->data[i]=carry%10;} 
    else{
      carryForward=0;
      ((format )intal)->data[i]=carry;
    }
  }
  if(carryForward==1){
    format new_intal;
    new_intal=(format )malloc(sizeof(format));
    new_intal->numberOfDigit=length+1;
    new_intal->data=malloc(sizeof(int)*(length+1));
    int j=0,i;
    for(i=1;i<length+1;i++){
      new_intal->data[i]=((format )intal)->data[j];
      j++;
    }
    new_intal->data[0]=carryForward;
    new_intal->numberOfDigit=length+1;
    intal_destroy(intal);
    return new_intal;

  }
  return intal;
}

void* intal_diff(void* temp1, void* temp2){
  if(temp1==NULL && temp2==NULL)
    return NULL;
  format intal1, intal2, new_intal, difference;
  intal1 = temp1;
  intal2 = temp2;
  new_intal = (format)malloc(sizeof(struct format));
  new_intal->data = (short int*)malloc(sizeof(short int) * 2);
  new_intal->data[0] = 0;
  new_intal->numberOfDigit = 1;
  int compare = intal_compare(intal1, intal2),i;
  if(compare == 0){                                               //If the compare returns 0 which means both the number are equal so return zero
    return intal_create(intal2str(new_intal));
  }
  if(compare == -1){            //If second number is greater than the first number that swapping the number
    format temp = intal1;
    intal1 = intal2;
    intal2 = temp;
  }
  int count = 0;
  int length1, length2, length3, length;
  length1 = intal1->numberOfDigit;
  length2 = intal2->numberOfDigit;
  length = length3 = length1 + 1;
  difference = (format)malloc(sizeof(struct format));
  difference->data = (short int*)malloc(sizeof(short int) * length + 1);
  difference->numberOfDigit = length;
  int borrow = 0;
  while(length3 > 0){
    if(length2 == 0){
      break;
    }
    int sub = (intal1->data[--length1] - (intal2->data[--length2]) - borrow);   //Performing subtraction by taking the last digit of both the numbers
    if(sub < 0){                        //If sub less than 0 which means a borrow is required
      sub+= 10;
      borrow = 1;
    }
    else {borrow = 0;}
    difference->data[--length3] = sub;
    count++;
  }

  while(length3 > 0){
    int sub = ((intal1->data[--length1]) - borrow);
    borrow = 0;
    if(sub < 0){
      sub+= 10;
      borrow = 1;
    }
    if(length1 < -1){
      sub = 0;
    }
    difference->data[--length3] = sub;
    count++;
  }
  for (i = 0; i <= length - count; i++) {
     difference->data[i] = 0;
  }
  return intal_create(intal2str((difference)));
}

void* intal_multiply(void* intal1,void* intal2){
  if(intal1==NULL || intal2==NULL)
    return NULL;
  char *str1,*str2,*str3;
  int numberOfDigit1,numberOfDigit2;
  numberOfDigit1=((format)intal1)->numberOfDigit;
  numberOfDigit2=((format)intal2)->numberOfDigit;
  str1=intal2str(intal1);
  str2=intal2str(intal2);
  str3=malloc(sizeof(char)*(numberOfDigit1+numberOfDigit2+1));
  int *c;
  c=malloc(sizeof( int)*(numberOfDigit1+numberOfDigit2));
  memset(c,0,sizeof( int)*(numberOfDigit1+numberOfDigit2));
  int i,j;
  for(i=numberOfDigit1-1;i>=0;i--){                                 //Performing basic mulitplcation operation
    for(j=numberOfDigit2-1;j>=0;j--){
      c[i+j+1]+=(str2[j]-'0')*(str1[i]-'0');
    }
  }
  for(i=numberOfDigit1+numberOfDigit2-1;i>=0;i--){
    if(c[i]>=10){
      c[i-1]+=c[i]/10;
      c[i]%=10;
    }
  }
  i=0;
  while(c[i]==0)
    i++;
  j=0;
  while(i<numberOfDigit1+numberOfDigit2){
    str3[j]=c[i]+'0';
    i++;j++;
  }
  str3[j]='\0';
  free(c);
   void *product;
   product=intal_create(str3);
  return product;
}


void* intal_divide(void* temp1, void* temp2){
  if(temp1==NULL && temp2==NULL)
    return NULL;
  if(((format)temp2)->data[0]==0)
    return NULL;
  if(temp1==NULL || temp2==NULL)
    return NULL;
  //printf("%s %s\n",intal2str(temp1),intal2str(temp2));
  format temp3, temp4, quotient, inputIntal;
  temp3 = intal_create(intal2str(temp1));
  temp4 = intal_create(intal2str(temp2));

  while(temp4->data[0] == 0 && temp4->numberOfDigit > 1){      //Checking for extraZero
    temp4->data++;
    temp4->numberOfDigit--;
  }
  if(temp4->numberOfDigit == 0){
    temp4->data[0] = 0;
    temp4->numberOfDigit = 1;
    return NULL;
  }

  while(temp3->data[0] == 0 && temp3->numberOfDigit > 1){
    temp3->data++;
    temp3->numberOfDigit--;
  }
  if(temp3->numberOfDigit == 0){
    temp3->data[0] = 0;
    temp3->numberOfDigit = 1;
    return intal_create(intal2str(temp3));
  }

  int compare = intal_compare(temp3, temp4);

  if(compare == 0){                                 //If intals are equal then the quotient value is 1
    format new_intal;
    new_intal = (format)malloc(sizeof(struct format));
    new_intal->numberOfDigit = 1;
    new_intal->data = (short int*)malloc(sizeof(short int) *2 +1);
    new_intal->data[0] = 1;
    return intal_create(intal2str(new_intal));
  }

  if(compare == -1){                              //If second intal is greater than the first intal then the quotient value is 0
    format new_intal;
    new_intal = (format)malloc(sizeof(struct format));
    new_intal->numberOfDigit = 1;
    new_intal->data = (short int*)malloc(sizeof(short int) *2 +1);
    new_intal->data[0] = 0;
    return intal_create(intal2str(new_intal));
  }

  if(temp4->numberOfDigit == 1 && temp4->data[0] == 1){   //If the second intal has only one digit and the value is one 1 ,then the quotient is equal to intal1
    return intal_create(intal2str(temp3));
  }

  quotient = (format)malloc(sizeof(struct format));       //Array which will have the quotient value
  quotient->data = (short int*)malloc(sizeof(short int) * temp3->numberOfDigit + 1);
  quotient->data[0] = 0;
  quotient->numberOfDigit = 0;

  if(temp3->numberOfDigit == temp4->numberOfDigit || (temp3->numberOfDigit - temp4->numberOfDigit == 1)){
    while(compare >= 0){                            //Performing long divison getting the digits from first intal which is equal or greater than the second intal 
      temp3 = intal_diff(temp3, temp4);
      quotient->data[0]++;
      compare = intal_compare(temp3, temp4);
    }
    if(quotient->data[0] >= 10){
      quotient->numberOfDigit = 2;
    }
    else{
      quotient->numberOfDigit = 1;
      return ((quotient));
    }
    int c = quotient->data[0];
    for (int i = 1; i >= 0; i--) {
      quotient->data[i] = c%10;
      c = c/10;
    }
    return intal_create(intal2str(quotient));
  }

  inputIntal = (format)malloc(sizeof(struct format));
  inputIntal->data = (short int*)malloc(sizeof(short int) * temp3->numberOfDigit + 1);
  inputIntal->numberOfDigit = 0;
  int  i;
  for (i = 0; i < temp4->numberOfDigit; i++) {
    inputIntal->data[i] = temp3->data[i];
    inputIntal->numberOfDigit++;
  }
  compare = intal_compare(inputIntal, temp4); //Performing long divison getting the digits from first intal which is equal or greater than the second intal 
  if(compare < 0){
    inputIntal->data[inputIntal->numberOfDigit] = temp3->data[inputIntal->numberOfDigit];
    inputIntal->numberOfDigit++;
    compare = 1;
  }
  temp3->data = temp3->data + inputIntal->numberOfDigit - 1;
  temp3->numberOfDigit = temp3->numberOfDigit - (inputIntal->numberOfDigit - 1);
  int count = 0;
  int c;
  while(temp3->numberOfDigit > 0){
      c = 0;
      while(compare >= 0){
        inputIntal = intal_diff(inputIntal, temp4);   //Performing repeated subtraction till the intal_compare return -1 on returning -1 the count value is appended to quotient
        c++;
        compare = intal_compare(inputIntal, temp4);
      }
      quotient->data[count++] = c;
      quotient->numberOfDigit++;
      temp3->data++;
      inputIntal->data[inputIntal->numberOfDigit++] = temp3->data[0];
      compare = intal_compare(inputIntal, temp4);
      temp3->numberOfDigit--;
    }
  return intal_create(intal2str(quotient));
}
void* intal_pow(void *intal1,void* intal2){    //Decrease and Conquer Approcah
   if(intal1==NULL && intal2==NULL)
    return NULL;
  if(((format)intal1)->data==0 && ((format)intal2)->data==0){
    char *str=malloc(sizeof(char)*2);
    strcpy(str,"0");
    return intal_create(intal2str(str));
  }
 
  format temp1;
  temp1=intal2;
  if(intal1==NULL || temp1==NULL){
    return NULL;
  }
  char *str1,*str2,*str3;
  str1=intal2str(intal1);
  str2=intal2str(temp1);
  int n;
  if(strcmp(intal2str(temp1),"0")==0)
    return (void *)(intal_create("1"));
  format new_intal;
  new_intal=intal_pow(intal1,intal_divide(temp1,intal_create("2")));
  if((str2[strlen(str2)-1]-'0')%2==0)
    return intal_multiply(new_intal,new_intal);       //If even
  else
    return intal_multiply(intal1,intal_multiply(new_intal,new_intal)); //If odd
}
void* intal_decrement(void *intal){
  if(intal==NULL){
    return NULL;

  }
  if(((format )intal)->numberOfDigit==1 && ((format )intal)->data[0]==0)                  //If intal is zero
    return (void *)intal;
  int length,i,decrement;
  length=((format )intal)->numberOfDigit;
  decrement=((format )intal)->data[length-1]-1;
  if(decrement<10 && decrement>=0){
    ((format )intal)->data[length-1]-=1;
    return intal;
  }
  char *str;
  str=intal2str(intal);
  int borrow=-1,k,j,index;
  length=((format )intal)->numberOfDigit;
    decrement=(str[length-1]-'0')-1;
    if(decrement==-1){
       j=length-2,index=0;
      while(borrow!=1){
        decrement=(str[j]-'0')-1;
        if(decrement==-1){
          borrow=-1;
        }
        else{
          borrow=1;
        }
        index=j;
        j--;
      }
    }
      if((index)==0){
        if((str[index]-'0')-1==0){
      for(k=index-1;k<((format )intal)->numberOfDigit-1;k++){
        if(k==0)
          ((format )intal)->data[index]=0;
        else
          ((format )intal)->data[index]=9;
      }
      return intal;
      }
      else
      {
        ((format )intal)->data[index]-=1;
        for(k=index+1;k<((format )intal)->numberOfDigit;k++){
        ((format )intal)->data[k]=9;
      }
      return intal;
      
      }
      }
      
      else{
        ((format )intal)->data[index]-=1;
        index++;
        while(index!=length-1){
          ((format )intal)->data[index]=9;
          index++;
        }
        ((format )intal)->data[index]=9;
        return intal;
      }
  }

