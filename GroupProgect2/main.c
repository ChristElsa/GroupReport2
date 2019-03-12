#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define n 10

int main()
{
  
    FILE *f=fopen("result.txt","a");    //opens the file in appending mode
    if(f==NULL){
        printf("Error opening the file\n");
        return 0;
    }

    int opr,    //number of operations
        caseOp, //case operation + - * /
        num1,   //variable 1
        num2,   //variable 2
        resUs,  //user's answer
        res;    //result of current channel
    int count=0;    //counter of the right answers
    char c;
    char s[10]; //string containing user's answer

    int index[10];  //array of flag for correct answers
    int ind=0;

    srand(time(NULL));  //random number generator's function
    res=0;

    clock_t start, end; //time couting variables
    int flag=0;
    int flag1=0;  //flag to exclude two or more consecutive operations of type 2 and 3
    start=clock();  //start counting time

    for(int i=0; i<n; i++){
        opr=rand()%(6-3)+3; 
        res=rand()%(101-0);
        printf("The number %d question: ",i+1);
        printf("%d",res); fprintf(f,"%d",res);
        for(int j=0; j<opr; j++){
            caseOp=rand()%(4-0);
            if((caseOp==2||caseOp==3)&&flag1==1){
                caseOp=rand()%(2-0);
                flag1=0;
            }
            switch(caseOp){
            case(0):    //+ addition
                num2=rand()%(101-0);
                printf("+%d",num2); fprintf(f,"+%d",num2);
                res+=num2;
                flag=1;
                break;
            case(1):    //- subtraction
                num2=rand()%(101-0);
                printf("-%d",num2); fprintf(f,"-%d",num2);
                res-=num2;
                flag=2;
                break;
            case(2):    //* multiplication
                if(flag==0){
                    num2=rand()%(101-0);
                    res*=num2;
                }else if(flag==1){
                    res-=num2;
                    num1=rand()%(101-0);
                    res=num2*num1+res;
                    flag=0;
                }else if(flag==2){
                    res+=num2;
                    num1=rand()%(101-0);
                    res=res-num2*num1;
                    flag=0;
                }
                flag1=1;
                printf("*%d",num1); fprintf(f,"*%d",num1);
                break;
            case(3):    // / division
                if(flag==0){
                    num2=rand()%(101-0);
                    res/=num2;
                }else if(flag==1){
                    res=res-num2;
                    num1=rand()%(101-0);
                    res=num2/num1+res;
                    flag=0;
                }else if(flag==2){
                    res+=num2;
                    num1=rand()%(101-0);
                    res=res-num2/num1;
                    flag=0;
                }
                flag1=1;
                printf("/%d",num1); fprintf(f,"/%d",num1);
                break;
            }
        }
        fprintf(f,"=%d\n",res);
        printf("\n");
       
        c=getchar();    //user's input   
        if(c=='\n'){   //ENTER control 
            index[ind++]=1;
            continue;  
        }
        int k;
        for(k=0; c!='\n'; k++){
            s[k]=c;
            c=getchar();
        }
        s[k]='\0';
        
        printf("Thanks\n");
        resUs=atoi(s);  //char to int conversion
        if(resUs==res){
            count++;
            index[ind++]=0;
        } else {
            index[ind++]=1;
        }
    }   //for

    end=clock();
    fclose(f);

    double time=((double)(end-start))/CLOCKS_PER_SEC;
    printf("\ntime: %.4f sec\n",time);
    printf("the number of correct answers: %d\n",count);
    printf("\nThe following is the right answer of the questions you got wrong:\n");

    char line[50];
    f=fopen("result.txt","r");  //reading the file
    int i=0;
    while ((fgets(line, 50, f))!=NULL) {
        if((index[i]==1)&&(i<=10)){
            printf("%s",line);
        }
        i++;
    }

    fclose(f);
    return 0;
}

