# include<stdio.h>
# include<iostream>
#include <cstring>
using namespace std;
/*
    _______               __________
   |scanner| --------->  |scanBuffer|
   |_______|  put in     |__________|


*/
//design a word-table
//define a two-dimensional array,the row could represents class code，the column represent others

char dim_word[] = {'D','I','M','\0'};
char if_word[] = {'I','F','\0'};
char do_word[] = {'D','O','\0'};
char stop_word[] = {'S','T','O','P','\0'};
char end_word[] = {'E','N','D','\0'};
char id_word[] = {'I','D','\0'};
char int_word[] = {'I','N','T','\0'};
char equ_word[] = {'=','\0'};
char plu_word[] = {'+','\0'};
char star_word[] = {'*','\0'};
char power_word[] = {'*','*','\0'};
char dou_word[] = {',','\0'};
char lb_word[] = {'(','\0'};
char rb_word[] = {')','\0'};


char* wt[14] = {dim_word,if_word,do_word,stop_word,end_word,
                id_word,int_word,equ_word,plu_word,star_word,power_word,dou_word,lb_word,rb_word};

enum{DIM,IF,DO,STOP,END,ID,INT,EQU,PLUS,STAR,POWER,DOU,LEFTBRACKET,RIGHTBRACKET};
//scanbuffer，size fixed


char scanBuffer[128]={};
char* startscan = scanBuffer;
char* searchscan = scanBuffer;

char* p;
char* lp;
char* tk;
int wordCompare();

//first judge basic class
int Scanner(char *ch)
{
    //put a char in scanbuffer
    tk = ch;
    while(*tk != '\0')
    {   
        p = tk;

        if((*p == ' ') || (*p == '\n'))
        {  
            if(startscan != searchscan)
            {
                *(++searchscan) = '\0';
                printf("scanbuffer:%s\n",scanBuffer);
                int w_type = wordCompare();
                searchscan = startscan;
            }
            else
            {
                continue;
            }   
        }
        else
        {
            //put in scanner
            *searchscan = *p; 
            searchscan++;
            
        }

        tk++;
    }

    if(searchscan != startscan)
    {
        *(++searchscan) = '\0';
        printf("scanbuffer:%s\n",scanBuffer);
        int w_type = wordCompare();
        searchscan = startscan;
    }

    return 0;


}

int wordCompare()
{

    //the type compose have three part: basic;basic+identfy;identify
    //judge category compare with all class 
    //word compare
    int type = 99;
    char* p = scanBuffer;
    
    for(int i= 0; i <= sizeof(wt)/sizeof(char *); i++)
    {
        if(*p == wt[i][0])
        {
            char* pp = wt[i];
            //basic word

            while(*p == *pp && *p != '\0')
            {
                printf("scanbuffer current char:%c\n",*p);
                printf("wordtable current char:%c\n",*pp);
                p++;
                pp++;

            }

            if(*p == '\0' && *pp =='\0')
            {
                type = i;
                break; 
            }
            else if(*p == '\0' && *pp != '\0')
            {
                type = ID;
                printf("type:%d\n",type);
                break;
            }
            else
            {
                p = scanBuffer;
                break;
            }

        }

    }       
    //id+basic word 
    char *idp;
    while(*p != '\0')
    {
        //id word or basic
        int flag = 0;
        for(int i= 0; i <= sizeof(wt)/sizeof(char *); i++)
        {
            if(*p == wt[i][0])
            {
                flag = 1;
                char* pp = wt[i];
                while(*p == *pp)
                {
                    printf("scanbuffer current char:%c\n",*p);
                    printf("wordtable current char:%c\n",*pp);
                    p++;
                    pp++;
                }
                if(*p != '\0' && *pp == '\0')
                {
                    type = i;
                    printf("type:%d\n", type);
                    break;
                }
                else if(*p == '\0' && *pp != '\0')
                {
                    type = ID;
                    printf("type:%d\n",type);
                    break;
                }
                //in case basic+identfy,only need check calculate symbol or other single symbol
                else if(*p != *pp)
                {
                    int idflag = 0;
                    while(idflag == 1)
                    {
                        for(int i = 7;i<=14;i++)
                        {
                            if(*p != wt[i][0])
                            {
                                idflag = 1;
                            }
                            else
                            {
                                idflag = 0;
                            }
                        } 
                        if(idflag == 1)
                        {
                            printf("identify char");
                            p++;
                        }
                        else
                        {
                            //idflag = 0;
                            break;
                        }
                    
                    }
                    type = ID;
                    printf("type:%d\n",type);
                    break;
                }
            }

        }
        //in case basic+identfy,only need check calculate symbol or other single symbol
        if(flag == 0)
        {
            int idflag = 0;
            while(idflag == 1)
            {
                for(int i = 7;i<=14;i++)
                {
                    if(*p != wt[i][0])
                    {
                        idflag = 1;
                    }
                    else
                    {
                        idflag = 0;
                    }
                } 
                if(idflag == 1)
                {
                    printf("identify char");
                    p++;
                }
                else
                {
                    //idflag = 0;
                    break;
                }
            
            }
            type = ID;
            printf("type:%d\n",type);
            break;
        }
            
        //p++;
    }    

    //determine basic word type

    //clean buffer
    printf("clean buffer!\n");
    for(int k =0; scanBuffer[k] != '\0';k++)
    {
        scanBuffer[k] ='\0';
    }

    printf("the scanbuffer type:%d\n",type);
    return type;
}

/*
2022:
    1.26 step 1: question: the code could run,but the answer can't show in screen,there have some logistic problem
    1.28 step 2: buffer is correct,but tpye comparition is not useful
    1.29 step 3：could show type! but type is wrong
*/
int main(void)
{
    char text[] = "IF (i=1) {i++}";
    Scanner(text);

    return 0;
}
