#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSTRSIZE 255/*字符数组最大长度*/
#define FILENAME_MAX 20
typedef struct
{
    char ch[MAXSTRSIZE+1];/*一般情况下，0号单元存储串的长度，但是因为后面有文件的读写，难以控制指针变量，所以不存储*/
    int length;/*定义字符串的长度*/
}String;/*定义顺序串的类型*/

void CreateTextFile();/*全局定义：建立文本文档*/
void WordCount();/*单词统计数量*/
void WordPosition();/*单词定位*/

/*建立文本文档*/
void CreateTextFile()
{
    String S;/*定义一个指针变量*/
    FILE *fp=NULL;
    char filename[FILENAME_MAX];
    char flag;/*定义一个用来判断输入是否已经结束的变量*/
    int i=0;
    printf("请输入新建的文件名：");
    scanf("%s",filename);
    getchar();/*输入字符串后，敲了一个回车，scanf并不读取换行符'\n',所以会出现文本里从第二行读入的情况*/
    if((fp=fopen(filename,"w"))==NULL)
    {
        printf("cannot open the file.\n");
        exit(0);
    }
    printf("请输入文本内容（以“#”结束）：\n");
    flag='n';/*判断符号的初始值不为#，说明能够输入*/
    while(flag!='#')/*一行为一个字符数组*/
    {
        gets(S.ch);
        S.length=strlen(S.ch);
        if(S.ch[S.length-1]!='#')/*没有#，继续输入*/
        {
            fwrite(&S,S.length,1,fp);/*指针变量&S，表示写入文件的数据块在内存中的起始位置；字节长度；写入数据块的个数*/
            S.ch[S.length]='\0';/*给字符数组加上结束符*/
            flag='n';
        }
        else/*停止输入*/
        {
            fwrite(&S,S.length-1,1,fp);/*S.length-1的原因是最后一个是结束字符#，不读入文件*/
            S.ch[S.length-1]='\0';
            flag='#';
        }
        fprintf(fp,"%c",10);/*每读入一行字符，在文件里输入一个换行*/
    }
    fclose(fp);
    fp=NULL;
    printf("成功建立文本文件!\n");
}
/*字符串的匹配*/
int Index(String S,String T,int pos)/*字符串的匹配*/
{
    int i=pos-1;/*i用于主串S中当前位置下标，若pos不为0，则从pos位置开始匹配*/
    int j=0;/*j用于子串T中当前位置下标*/
    while(i<S.length&&j<T.length)/*若i小于S长度且j小于T的长度时循环*/
    {
        if(S.ch[i]==T.ch[j])/*两个字母相等则继续*/
        {
            i++;
            j++;
        }
        else/*不相等则指针后退重新开始匹配*/
        {
            i=i-j+1;/*i退回上次匹配首位的下一位*/
            j=0;/*j退回子串T的首位*/
        }
    }
    if(j>=T.length)
        return i-T.length;
    else
        return -1;

}
/*单词个数的统计*/
void WordCount()/**/
{
    FILE *fp=NULL;
    String S,T;/*定义两个串的变量*/
    char filename[FILENAME_MAX];
    int count=0,j,pos;
    printf("请输入文件名：");
    scanf("%s",filename);
    if(!(fp=fopen(filename,"r")))
    {
        printf("没有这个文件，请重新选择！\n");
        return;
    }
    printf("请输入要统计数量的单词：");
    scanf("%s",T.ch);
    T.length=strlen(T.ch);
    while(!feof(fp))/*文件存在,扫描整个文本文件，文件没结束时*/
    {
        memset(S.ch,'\0',256);/*初始化字符数组*/
        fgets(S.ch,256,fp);/*向文件读取255个字符，若遇到换行符则结束，将读出来的字符串加结束标志存放到S.ch字符数组中*/
        S.length=strlen(S.ch);
        pos=0;/*初始化开始检索的位置*/
        while(pos<S.length-1)/*检索整个主串*/
        {
            j=Index(S,T,pos);/*调用字符串匹配函数*/
            if(j<0)/*匹配失败，则读取下一行字符*/
                break;
            else
            {
                count++;/*匹配成功，单词加一*/
                pos=j+T.length;/*继续下一次的匹配*/
            }
        }
    }
    if(count>0)
        printf("单词%s出现在文本文件%s中共出现%d次。\n",T.ch,filename,count);
    else
        printf("文本文件%s中没有这个单词！\n",filename);
    fclose(fp);
    fp=NULL;
}
/*单词定位，判断单词在的行数和第几个字母*/
void WordPosition()
{
    FILE *fp=NULL;
    String S,T;/*定义两个串的变量*/
    char filename[FILENAME_MAX];
    int i,j,pos,l,count,sum=0;/*l是单词所在的行数,coumt是每行一个单次出现的个数，sum是单词在整个文本出现次数*/
    int t[20];/*如果一行中多次出现同一个单词，用来存放单词的多个位置*/
    printf("请输入文件名：");
    scanf("%s",filename);
    if(!(fp=fopen(filename,"r")))
    {
        printf("没有这个文件，请重新选择！\n");
        return;
    }
    printf("请输入要搜索的单词：");
    scanf("%s",T.ch);
    T.length=strlen(T.ch);
    l=0;/*初始化行数*/
    while(!feof(fp))/*扫描整个文件，文件没有结束时*/
    {
        memset(S.ch,'\0',256);/*初始化字符数组*/
        fgets(S.ch,256,fp);/*向文件读取255个字符，若遇到换行符则结束，将读出来的字符串加结束标志存放到S.ch字符数组中*/
        S.length=strlen(S.ch);
        l++;/*行数加一*/
        pos=0;/*初始化开始检索的位置*/
        count=0;/*初始化单词计数*/
        while(pos<S.length-1)
        {
            j=Index(S,T,pos);/*调用字符串的匹配*/
            if(j<0)/*匹配失败，则读取下一行字符*/
                break;
            else
            {
                count++;/*匹配成功，单词加一*/
                t[count]=j;/*记录单词在该行的位置*/
                pos=j+T.length;;/*继续下一次的匹配*/
            }
        }
        if(count>0)/*.......*/
        {
            printf("行号：%d，出现次数：%d，在该行的位置为：",l,count);
            for(i=1;i<=count;i++)
            printf("%4d",t[i]+1);
            printf("\n");
        }
        sum+=count;/*统计单词在文件总共出现的次数*/
    }
    if(sum==0)/*单词在文件出现次数为0*/
        printf("文本文件%s中没有这个单词！\n",filename);
    fclose(fp);
    fp=NULL;
}

int main()
{
    int chioce;
    printf("*************************单词检索统计系统*************************\n");
    printf("——————————————1.建立文件——————————————\n");
    printf("——————————————2.单词计数——————————————\n");
    printf("——————————————3.单词定位——————————————\n");
    printf("——————————————4.结束程序——————————————\n");
    printf("******************************************************************\n");
    printf("请输入选项：");
    while(~scanf("%d",&chioce))
    {
        if(chioce==4)
            {
                printf("*************************感谢使用！！！**************************\n");
                break;
            }
        switch(chioce)
        {
            case 1:
                CreateTextFile();
                break;
            case 2:
                WordCount();
                break;
            case 3:
                WordPosition();
                break;
            default:
                printf("**************输入错误！请重新输入**************\n");
                break;
        }
        printf("\n请输入选项：");
    }
    return 0;
}

