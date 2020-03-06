#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct Book/*结构体*/
{
    char bookname[20];/*书名*/
    int id ;/*书的编号*/
    char classfy[20];/*书的分类*/
    char author[20];/*作者*/
    char publisher[20];/*出版社*/
    float price;/*价格*/
    struct Book *book_next;/*链表的指针域*/
};
struct People
{
    char peoplename[20];/* 姓名*/
    char cla[20];/*班级*/
    int number;/*学号*/
    char bookname[20];/*书名*/
    int id;/*书的编号*/
    char borrowdata[20];/*借书日期*/
    char returndata[20];/*还书日期*/
    struct People *people_next;
};
struct Book *Create();/*创建链表*/
void Savebook(struct Book *book_head,int e);/*将链表的数据保存到文件,e用来记录是否追加*/
void Copybook(struct Book *book_head);/*从文件中复制图书记录，初始化链表*/
void Addbook(struct Book *book_head);/*添加图书*/
void Alterbook(struct Book *book_head);/*修改图书信息*/
void Deletebook(struct Book *book_head);/*删除图书*/
void Seebook(struct Book *book_head);/*浏览图书*/
void Searchbook_bookname(struct Book *book_head);/*通过书名查询图书*/
void Searchbook_id(struct Book *book_head);/*通过编号查询图书*/
void Searchbook_author(struct Book *book_head);/*通过作者查询图书*/
void Searchbook_publisher(struct Book *book_head);/*通过出版社查询图书*/
void Savepeople(struct People *people_head,int e);/*存放借书的人的数据*/
void Copypeople(struct People *people_head);/*从文件中复制借书数据至内存*/
void Borrowbook(struct People *people_head);/*借书*/
void Returnbook(struct People *people_head);/*还书*/
/*新建表头节点*/
struct Book *Createbook()
{
    struct Book *book_head;
    book_head=(struct Book *)malloc(sizeof(struct Book));/*分配头结点空间*/
    book_head->book_next=NULL;/*头结点指针域初始化，设为空*/
    return book_head;
}
struct People *Createpeople()
{
    struct People *people_head;
    people_head=(struct People *)malloc(sizeof(struct People));/*分配头结点空间*/
    people_head->people_next=NULL;/*头结点指针域初始化，设为空*/
    return people_head;
}
/*添加图书*/
void Addbook(struct Book *book_head)
{
    struct Book *s,*p;/*定义指针变量，s指向新节点*/
    char flag='y';/*定义flag，方便用户重复输入*/
    p=book_head;
    while(p->book_next!=NULL)/*遍历链表至尾节点*/
    {
        p=p->book_next;
    }
    while(flag=='y')/*开辟新空间，存入数据，添加进链表*/
    {
        s=(struct Book *)malloc(sizeof(struct Book));
        printf(" 请输入书名：");
        fflush(stdin);/*清空输入缓存区，为了确保不影响后面的数据读取*/
        scanf("%s",s->bookname);
        printf(" 请输入书的编号：");
        fflush(stdin);
        scanf("%d",&s->id);
        printf(" 请输入书的分类：");
        fflush(stdin);
        scanf("%s",s->classfy);
        printf(" 请输入作者：");
        fflush(stdin);
        scanf("%s",s->author);
        printf(" 请输入出版社名称：");
        fflush(stdin);
        scanf("%s",s->publisher);
        printf(" 请输入书的价格：");
        fflush(stdin);
        scanf("%f",&s->price);
        printf("\n");
        p->book_next=s;/*将新节点s添加进链表，并且平往后移动*/
        p=s;
        s->book_next=NULL;
        printf("——————添加成功！——————\n");
        printf("——————是否继续添加？y或n——————\n");
        fflush(stdin);
        scanf("%c",&flag);
        if(flag=='y') continue;
        else if(flag=='n') break;
    }
    int e=0;
    Savebook(book_head,e);/*保存至文件*/
}
/*修改图书信息*/
void Alterbook(struct Book *book_head)
{
    struct Book *p;
    int t=0;/*t变量用于判断是否找到书*/
    char name[20];
    p=book_head;
    printf("请输入要修改信息的书名：");
    scanf("%s",name);
    while(p->book_next!=NULL)
    {
        p=p->book_next;
        if(strcmp(p->bookname,name)==0)
        {
            t=1;
            printf(" 请输入修改后的书名：");
            fflush(stdin);/*清空输入缓存区，为了确保不影响后面的数据读取*/
            scanf("%s",p->bookname);
            printf(" 请输入修改后的书的编号：");
            fflush(stdin);
            scanf("%d",&p->id);
            printf(" 请输入修改后的书的分类：");
            fflush(stdin);
            scanf("%s",p->classfy);
            printf(" 请输入修改后的作者：");
            fflush(stdin);
            scanf("%s",p->author);
            printf(" 请输入修改后的出版社名称：");
            fflush(stdin);
            scanf("%s",p->publisher);
            printf(" 请输入修改后的书的价格：");
            fflush(stdin);
            scanf("%f",&p->price);
            printf("\n");
        }
    }
    if(t==0)
        printf("——————没有找到这本书的记录！——————\n");
    int e=1;
    Savebook(book_head,e);
}
/*删除图书*/
void Deletebook(struct Book *book_head)
{
    struct Book *p,*q;
    int t=0;/*记录是否有删除的书*/
    char name[20];
    p=q=book_head;
    printf("请输入要删除的书的书名：");
    scanf("%s",name);
    printf("\n");
    while(p!=NULL)
    {
        if(strcmp(p->bookname,name)==0)
        {
            t++;
            for(;q->book_next!=p;)/*找到所要删除节点的上一个节点q*/
            {
                q=q->book_next;
            }
            q->book_next=p->book_next;
            free(p);
        }
        p=p->book_next;
    }
    if(t!=0)
    {
        printf("——————删除成功！——————\n");
    }
    else
    {
       printf("——————没有找到要删除的书！——————\n");
    }
    //Save_updata(book_head);
    int e=1;
    Savebook(book_head,e);
}
/*浏览图书信息*/
void Seebook(struct Book *book_head)
{
    struct Book *p;
    if(book_head==NULL||book_head->book_next==NULL)/*判断文件数据是否为空*/
    {
        printf("——————没有图书记录——————\n");
    }
    else
    {
        p=book_head;
        printf("      书名       编号       分类        作者       出版社       价格\n");
        while(p->book_next!=NULL)/*指针从头结点开始遍历至尾节点，依次输出图书信息*/
        {
            p=p->book_next;
            printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
        }
    }
}
/*通过书名查询图书*/
void Searchbook_bookname(struct Book *book_head)
{
    struct Book *p;
    char name[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*判断文件数据是否为空*/
    {
        printf("————————————图书文件为空！————————————\n");
    }
    else
    {
        printf("请输入你要查找的书的书名：");
        fflush(stdin);
        scanf("%s",name);
        printf("\n");
        while(p->book_next!=NULL)/*指针从头结点遍历至尾节点，查找图书信息*/
        {
            p=p->book_next;
            if(strcmp(p->bookname,name)==0)
            {
                printf("——————————————图书已找到！图书信息如下：——————————————\n");
                printf("      书名       编号       分类        作者       出版社       价格\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("——————————————查询完毕！——————————————\n");
    }
}
/*通过编号查询图书*/
void Searchbook_id(struct Book *book_head)
{
    struct Book *p;
    int bookid;
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*判断文件数据是否为空*/
    {
        printf("————————————图书文件为空！————————————\n");
    }
    else
    {
        printf("请输入你要查找的书的编号：");
        fflush(stdin);
        scanf("%d",&bookid);
        printf("\n");
        while(p->book_next!=NULL)/*指针从头结点遍历至尾节点，查找图书信息*/
        {
            p=p->book_next;
            if((p->id)==bookid)
            {
                printf("——————————————图书已找到！图书信息如下：——————————————\n");
                printf("      书名       编号       分类        作者       出版社       价格\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("————————————查询完毕！————————————\n");
    }
}
/*通过作者查询图书*/
void Searchbook_author(struct Book *book_head)
{
    struct Book *p;
    char authorname[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*判断文件数据是否为空*/
    {
        printf("————————————图书文件为空！————————————\n");
    }
    else
    {
        printf("请输入你要查找的书的作者：");
        fflush(stdin);
        scanf("%s",authorname);
        printf("\n");
        while(p->book_next!=NULL)/*指针从头结点遍历至尾节点，查找图书信息*/
        {
            p=p->book_next;
            if(strcmp(p->author,authorname)==0)
            {
                printf("——————————————图书已找到！图书信息如下：——————————————\n");
                printf("      书名       编号       分类        作者       出版社       价格\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("————————————查询完毕！————————————\n");
    }
}
/*通过出版社查询图书*/
void Searchbook_publisher(struct Book *book_head)
{
    struct Book *p;
    char pub[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*判断文件数据是否为空*/
    {
        printf("————————————图书文件为空！————————————\n");
    }
    else
    {
        printf("请输入你要查找的书的出版社：");
        fflush(stdin);
        scanf("%s",pub);
        printf("\n");
        while(p->book_next!=NULL)/*指针从头结点遍历至尾节点，查找图书信息*/
        {
            p=p->book_next;
            if(strcmp(p->publisher,pub)==0)
            {
                printf("——————————————图书已找到！图书信息如下：——————————————\n");
                printf("      书名       编号       分类        作者       出版社       价格\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("————————————查询完毕！————————————\n");
    }
}
/*借书*/
void Borrowbook(struct People *people_head)
{
    struct People *s,*p;/*定义指针变量，s指向新节点*/
    char flag='y';/*定义flag，方便用户重复输入*/
    p=people_head;
    while(p->people_next!=NULL)/*遍历链表至尾节点*/
    {
        p=p->people_next;
    }
    while(flag=='y')/*开辟新空间，存入数据，添加进链表*/
    {
        s=(struct People *)malloc(sizeof(struct People));
        printf(" 请输入你的姓名：");
        fflush(stdin);/*清空输入缓存区，为了确保不影响后面的数据读取*/
        scanf("%s",s->peoplename);
        printf(" 请输入班级：");
        fflush(stdin);
        scanf("%s",s->cla);
        printf(" 请输入学号：");
        fflush(stdin);
        scanf("%d",&s->number);
        printf(" 请输入书名：");
        fflush(stdin);
        scanf("%s",s->bookname);
        printf(" 请输入书的编号：");
        fflush(stdin);
        scanf("%d",&s->id);
        printf(" 请输入借书日期：");
        fflush(stdin);
        scanf("%s",s->borrowdata);
        printf(" 请输入还书日期：");
        fflush(stdin);
        scanf("%s",s->returndata);
        printf("\n");
        p->people_next=s;/*将新节点s添加进链表，并且平往后移动*/
        p=s;
        s->people_next=NULL;
        printf("——————借书成功！——————\n");
        printf("——————是否继续借书？y或n——————\n");
        fflush(stdin);
        scanf("%c",&flag);
        if(flag=='y') continue;
        else if(flag=='n') break;
    }
    int e=0;
    Savepeople(people_head,e);/*保存至文件*/
}
/*还书*/
void Returnbook(struct People *people_head)
{
    struct People *p,*q;
    int t=0;/*记录是否有删除的记录*/
    int bookid;
    p=q=people_head;
    printf("请输入要还的书的编号：");
    scanf("%d",&bookid);
    printf("\n");
    while(p!=NULL)
    {
        if((p->id)==bookid)
        {
            t++;
            for(;q->people_next!=p;)/*找到所要删除节点的上一个节点q*/
            {
                q=q->people_next;
            }
            q->people_next=p->people_next;
            free(p);
        }
        p=p->people_next;
    }
    if(t!=0)
    {
        printf("——————还书成功！——————\n");
    }
    else
    {
       printf("——————没有找到借书信息，还书失败！——————\n");
    }
    int e=1;
    Savepeople(people_head,e);
}
/*从文件中复制图书记录，初始化链表*/
void Copybook(struct Book *book_head)
{
    struct Book bookrecord;/*对象*/
    FILE *fp;
    fp=fopen("books.txt","r");
    if(fp==NULL)
    {
        printf("Cannot open the file!\n");
        exit(0);
    }
    while((fscanf(fp,"%s%d%s%s%s%f",bookrecord.bookname,&bookrecord.id,bookrecord.classfy,bookrecord.author,bookrecord.publisher,&bookrecord.price))!=EOF)
    {
        struct Book *p;
        p=(struct Book *)malloc(sizeof(struct Book));
        p->book_next=NULL;
        strcpy(p->bookname,bookrecord.bookname);/*"."是对对象成员的调用，”->"是指针中的成员*/
        p->id=bookrecord.id;
        strcpy(p->classfy,bookrecord.classfy);
        strcpy(p->author,bookrecord.author);
        strcpy(p->publisher,bookrecord.publisher);
        p->price=bookrecord.price;
        book_head->book_next=p;
        book_head=p;
    }
    fclose(fp);
}
/*保存数据至文件*/
void Savebook(struct Book *book_head,int e)
{
    struct Book *p;
    FILE *fp;
    if(e==0)
    {
        fp=fopen("books.txt","a+");/*以追加的方式方式打开可读写文件*/
    }
    else
    {
        fp=fopen("books.txt","w+");/*以读写的方式创建一个文件，w+不追加*/
    }
    if(fp==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    p=book_head;
    while(p->book_next!=NULL)/*指针从头结点开始，遍历至尾节点，依次输出输的信息*/
    {
        p=p->book_next;
        fprintf(fp,"%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
        fprintf(fp,"\n");
    }
    rewind(fp);
    fclose(fp);
    if(e==0)
    {
        printf("已将图书数据保存至books.txt文件！\n");
    }
    else
    {
        printf("已将更新后的图书数据保存至books.txt文件！\n");
    }
}
/*存放借书数据至文件夹*/
void Savepeople(struct People *people_head,int e)
{
    struct People *p;
    FILE *fp;
    if(e==0)
    {
        fp=fopen("borrowpeople.txt","a+");/*以追加的方式方式打开可读写文件*/
    }
    else
    {
        fp=fopen("borrowpeople.txt","w+");/*以读写的方式创建一个文件，w+不追加*/
    }
    if(fp==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    p=people_head;
    while(p->people_next!=NULL)/*指针从头结点开始，遍历至尾节点，依次输出输的信息*/
    {
        p=p->people_next;
        fprintf(fp,"%10s%10s%10d%10s%10d%10s%10s\n",p->peoplename,p->cla,p->number,p->bookname,p->id,p->borrowdata,p->returndata);
        fprintf(fp,"\n");
    }
    rewind(fp);
    fclose(fp);
    if(e==0)
    {
        printf("已将图书数据保存至borrowpeople.txt文件！\n");
    }
    else
    {
        printf("已将更新后的图书数据保存至borrowpeople.txt文件！\n");
    }
}
/*从文件中复制结束数据至内存*/
void Copypeople(struct People *people_head)
{
    struct People peoplerecord;/*对象*/
    FILE *fp;
    fp=fopen("borrowpeople.txt","r");
    if(fp==NULL)
    {
        printf("Cannot open the file!\n");
        exit(0);
    }
    while((fscanf(fp,"%s%s%d%s%d%s%s",peoplerecord.peoplename,peoplerecord.cla,&peoplerecord.number,peoplerecord.bookname,&peoplerecord.id,peoplerecord.borrowdata,peoplerecord.returndata))!=EOF)
    {
        struct People *p;
        p=(struct People *)malloc(sizeof(struct People));
        p->people_next=NULL;
        strcpy(p->peoplename,peoplerecord.peoplename);/*"."是对对象成员的调用，”->"是指针中的成员,姓名*/
        strcpy(p->cla,peoplerecord.cla);/*班级*/
        p->number=peoplerecord.number;/*学号*/
        strcpy(p->bookname,peoplerecord.bookname);/*书名*/
        p->id=peoplerecord.id;/*书的编号*/
        strcpy(p->borrowdata,peoplerecord.borrowdata);/*借书日期*/
        strcpy(p->returndata,peoplerecord.returndata);/*还书日期*/
        people_head->people_next=p;
        people_head=p;
    }
    fclose(fp);
}
int main(void)
{
    struct Book *book_head;
    struct People *people_head;
    book_head=Createbook();
    people_head=Createpeople();
    Copybook(book_head);
    Copypeople(people_head);
    int choice;
    printf("————————————————图书管理系统————————————————\n");
    printf("————————(1)添加图书                  (2)修改图书——————————\n");
    printf("————————(3)删除图书                  (4)浏览图书——————————\n");
    printf("————————(5)查询图书(书名)            (6)查询图书(编号)———————\n");
    printf("————————(7)查询图书(作者)            (8)查询图书(出版社)—————\n");
    printf("————————(9)借阅图书                  (10)归还图书—————————\n");
    printf("————————————————(11)退出系统————————————————\n");
    printf("          请输入选项：");
    while(scanf("%d",&choice)!=EOF)
    {
        if(choice==11)
        {
            printf("——————————————感谢使用图书管理系统！——————————————\n");
            break;
        }
        switch(choice)
        {
            case 1:
                Addbook(book_head);
                break;
            case 2:
                Alterbook(book_head);
                break;
            case 3:
                Deletebook(book_head);
                break;
            case 4:
                Seebook(book_head);
                break;
            case 5:
                Searchbook_bookname(book_head);
                break;
            case 6:
                Searchbook_id(book_head);
                break;
            case 7:
                Searchbook_author(book_head);
                break;
            case 8:
                Searchbook_publisher(book_head);
                break;
            case 9:
                Borrowbook(people_head);
                break;
            case 10:
                Returnbook(people_head);
                break;
            default:
                printf("——————输入错误！请重新输入——————\n");
                break;
        }
        printf("\n");
        printf("          请输入选项：");
    }
    return 0;
}
