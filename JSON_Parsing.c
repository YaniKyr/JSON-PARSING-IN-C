#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Reg{
char tmstmp[50];
float value;
};

int SizeofFile(FILE *fp){
    char c;
    int n=0;
    c = getc(fp);

    while(c!=EOF){
        if(c==':') n++;
        c = getc(fp);
    }
    return n;
}


int PARSE(FILE *fp,struct Reg *arr){
    
    if(fp==NULL) fprintf(stderr,"ERROR");
    int i=0;
    int *numOfChars;
    int numOfJsons=0;
    int n1=0;
    int  n ;
    char c;
    int j=0;
    char *buf;

fseek(fp,0,SEEK_SET);
    c = getc(fp);

    while(c!=EOF){
        if(c == '}') numOfJsons++; //Counts the '}'
        
        c = getc(fp);
    }

    
    fseek(fp,0,SEEK_SET);


    numOfChars=(int*)malloc(numOfJsons*sizeof(int));// A dynamic array that counts the chars before '}'
    numOfChars[i]=0;
    

    c = getc(fp);
    
    while(c!=EOF){

        if(c != '}')  numOfChars[i]=numOfChars[i]+1; // It counts the chars before '}'/
            else if(c=='}') i++;   //The "i" takes numOfChars in the next element of the array

        c = getc(fp);//Restarts the pointer fp1
    }
  

    
    i=0;
    n=0;
    fseek(fp,0,SEEK_SET);
    

    while(i<numOfJsons){
        buf=malloc(numOfChars[i]*sizeof(char)+2);
        fscanf(fp,"%[^\n]%n",buf,&n1);//It reads the file until \n
        

        char *buf2;
        buf2=malloc(numOfChars[i]*sizeof(char)+2);
        buf2=strcpy(buf2,buf); //buf loads to buf2
        
        fscanf(fp,"%*c"); //It does not consider the first char "{"

            while(strlen(buf2)>=(n)){
                
                sscanf(buf2,"%*c%*c%[^\"]%*c%*c%*c%*c%f%*c%*c%n",arr[j].tmstmp,&arr[j].value ,&n);
                //'n' counts the chars in one registration. 'n' is between 30-40 
                buf2+=n;//The loop ends, when n is bigger than buf2

                j++;
               }
            i++;
        }

    return j;
}



int main()
{

   
    struct Reg *arr=NULL;
    int numOfInsertions=0;//Number of JSONS
    int n;
    FILE *fp;
    fp = fopen("My_FILE.txt","r");
    n = SizeofFile(fp);
        

    arr=(struct Reg*)malloc(n*sizeof(struct Reg));
    
    numOfInsertions =PARSE(fp,arr); //It returns the number of registrations
 

//for (int i=0; i<numOfInsertions ; i++) printf("\nTimestamp:%s | Value:%f", arr[i].tmstmp,arr[i].value);
   

}
