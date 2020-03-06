#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct Book/*�ṹ��*/
{
    char bookname[20];/*����*/
    int id ;/*��ı��*/
    char classfy[20];/*��ķ���*/
    char author[20];/*����*/
    char publisher[20];/*������*/
    float price;/*�۸�*/
    struct Book *book_next;/*�����ָ����*/
};
struct People
{
    char peoplename[20];/* ����*/
    char cla[20];/*�༶*/
    int number;/*ѧ��*/
    char bookname[20];/*����*/
    int id;/*��ı��*/
    char borrowdata[20];/*��������*/
    char returndata[20];/*��������*/
    struct People *people_next;
};
struct Book *Create();/*��������*/
void Savebook(struct Book *book_head,int e);/*����������ݱ��浽�ļ�,e������¼�Ƿ�׷��*/
void Copybook(struct Book *book_head);/*���ļ��и���ͼ���¼����ʼ������*/
void Addbook(struct Book *book_head);/*���ͼ��*/
void Alterbook(struct Book *book_head);/*�޸�ͼ����Ϣ*/
void Deletebook(struct Book *book_head);/*ɾ��ͼ��*/
void Seebook(struct Book *book_head);/*���ͼ��*/
void Searchbook_bookname(struct Book *book_head);/*ͨ��������ѯͼ��*/
void Searchbook_id(struct Book *book_head);/*ͨ����Ų�ѯͼ��*/
void Searchbook_author(struct Book *book_head);/*ͨ�����߲�ѯͼ��*/
void Searchbook_publisher(struct Book *book_head);/*ͨ���������ѯͼ��*/
void Savepeople(struct People *people_head,int e);/*��Ž�����˵�����*/
void Copypeople(struct People *people_head);/*���ļ��и��ƽ����������ڴ�*/
void Borrowbook(struct People *people_head);/*����*/
void Returnbook(struct People *people_head);/*����*/
/*�½���ͷ�ڵ�*/
struct Book *Createbook()
{
    struct Book *book_head;
    book_head=(struct Book *)malloc(sizeof(struct Book));/*����ͷ���ռ�*/
    book_head->book_next=NULL;/*ͷ���ָ�����ʼ������Ϊ��*/
    return book_head;
}
struct People *Createpeople()
{
    struct People *people_head;
    people_head=(struct People *)malloc(sizeof(struct People));/*����ͷ���ռ�*/
    people_head->people_next=NULL;/*ͷ���ָ�����ʼ������Ϊ��*/
    return people_head;
}
/*���ͼ��*/
void Addbook(struct Book *book_head)
{
    struct Book *s,*p;/*����ָ�������sָ���½ڵ�*/
    char flag='y';/*����flag�������û��ظ�����*/
    p=book_head;
    while(p->book_next!=NULL)/*����������β�ڵ�*/
    {
        p=p->book_next;
    }
    while(flag=='y')/*�����¿ռ䣬�������ݣ���ӽ�����*/
    {
        s=(struct Book *)malloc(sizeof(struct Book));
        printf(" ������������");
        fflush(stdin);/*������뻺������Ϊ��ȷ����Ӱ���������ݶ�ȡ*/
        scanf("%s",s->bookname);
        printf(" ��������ı�ţ�");
        fflush(stdin);
        scanf("%d",&s->id);
        printf(" ��������ķ��ࣺ");
        fflush(stdin);
        scanf("%s",s->classfy);
        printf(" ���������ߣ�");
        fflush(stdin);
        scanf("%s",s->author);
        printf(" ��������������ƣ�");
        fflush(stdin);
        scanf("%s",s->publisher);
        printf(" ��������ļ۸�");
        fflush(stdin);
        scanf("%f",&s->price);
        printf("\n");
        p->book_next=s;/*���½ڵ�s��ӽ���������ƽ�����ƶ�*/
        p=s;
        s->book_next=NULL;
        printf("��������������ӳɹ���������������\n");
        printf("�������������Ƿ������ӣ�y��n������������\n");
        fflush(stdin);
        scanf("%c",&flag);
        if(flag=='y') continue;
        else if(flag=='n') break;
    }
    int e=0;
    Savebook(book_head,e);/*�������ļ�*/
}
/*�޸�ͼ����Ϣ*/
void Alterbook(struct Book *book_head)
{
    struct Book *p;
    int t=0;/*t���������ж��Ƿ��ҵ���*/
    char name[20];
    p=book_head;
    printf("������Ҫ�޸���Ϣ��������");
    scanf("%s",name);
    while(p->book_next!=NULL)
    {
        p=p->book_next;
        if(strcmp(p->bookname,name)==0)
        {
            t=1;
            printf(" �������޸ĺ��������");
            fflush(stdin);/*������뻺������Ϊ��ȷ����Ӱ���������ݶ�ȡ*/
            scanf("%s",p->bookname);
            printf(" �������޸ĺ����ı�ţ�");
            fflush(stdin);
            scanf("%d",&p->id);
            printf(" �������޸ĺ����ķ��ࣺ");
            fflush(stdin);
            scanf("%s",p->classfy);
            printf(" �������޸ĺ�����ߣ�");
            fflush(stdin);
            scanf("%s",p->author);
            printf(" �������޸ĺ�ĳ��������ƣ�");
            fflush(stdin);
            scanf("%s",p->publisher);
            printf(" �������޸ĺ����ļ۸�");
            fflush(stdin);
            scanf("%f",&p->price);
            printf("\n");
        }
    }
    if(t==0)
        printf("������������û���ҵ��Ȿ��ļ�¼��������������\n");
    int e=1;
    Savebook(book_head,e);
}
/*ɾ��ͼ��*/
void Deletebook(struct Book *book_head)
{
    struct Book *p,*q;
    int t=0;/*��¼�Ƿ���ɾ������*/
    char name[20];
    p=q=book_head;
    printf("������Ҫɾ�������������");
    scanf("%s",name);
    printf("\n");
    while(p!=NULL)
    {
        if(strcmp(p->bookname,name)==0)
        {
            t++;
            for(;q->book_next!=p;)/*�ҵ���Ҫɾ���ڵ����һ���ڵ�q*/
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
        printf("������������ɾ���ɹ���������������\n");
    }
    else
    {
       printf("������������û���ҵ�Ҫɾ�����飡������������\n");
    }
    //Save_updata(book_head);
    int e=1;
    Savebook(book_head,e);
}
/*���ͼ����Ϣ*/
void Seebook(struct Book *book_head)
{
    struct Book *p;
    if(book_head==NULL||book_head->book_next==NULL)/*�ж��ļ������Ƿ�Ϊ��*/
    {
        printf("������������û��ͼ���¼������������\n");
    }
    else
    {
        p=book_head;
        printf("      ����       ���       ����        ����       ������       �۸�\n");
        while(p->book_next!=NULL)/*ָ���ͷ��㿪ʼ������β�ڵ㣬�������ͼ����Ϣ*/
        {
            p=p->book_next;
            printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
        }
    }
}
/*ͨ��������ѯͼ��*/
void Searchbook_bookname(struct Book *book_head)
{
    struct Book *p;
    char name[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*�ж��ļ������Ƿ�Ϊ��*/
    {
        printf("������������������������ͼ���ļ�Ϊ�գ�������������������������\n");
    }
    else
    {
        printf("��������Ҫ���ҵ����������");
        fflush(stdin);
        scanf("%s",name);
        printf("\n");
        while(p->book_next!=NULL)/*ָ���ͷ��������β�ڵ㣬����ͼ����Ϣ*/
        {
            p=p->book_next;
            if(strcmp(p->bookname,name)==0)
            {
                printf("����������������������������ͼ�����ҵ���ͼ����Ϣ���£�����������������������������\n");
                printf("      ����       ���       ����        ����       ������       �۸�\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("������������������������������ѯ��ϣ�����������������������������\n");
    }
}
/*ͨ����Ų�ѯͼ��*/
void Searchbook_id(struct Book *book_head)
{
    struct Book *p;
    int bookid;
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*�ж��ļ������Ƿ�Ϊ��*/
    {
        printf("������������������������ͼ���ļ�Ϊ�գ�������������������������\n");
    }
    else
    {
        printf("��������Ҫ���ҵ���ı�ţ�");
        fflush(stdin);
        scanf("%d",&bookid);
        printf("\n");
        while(p->book_next!=NULL)/*ָ���ͷ��������β�ڵ㣬����ͼ����Ϣ*/
        {
            p=p->book_next;
            if((p->id)==bookid)
            {
                printf("����������������������������ͼ�����ҵ���ͼ����Ϣ���£�����������������������������\n");
                printf("      ����       ���       ����        ����       ������       �۸�\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("��������������������������ѯ��ϣ�������������������������\n");
    }
}
/*ͨ�����߲�ѯͼ��*/
void Searchbook_author(struct Book *book_head)
{
    struct Book *p;
    char authorname[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*�ж��ļ������Ƿ�Ϊ��*/
    {
        printf("������������������������ͼ���ļ�Ϊ�գ�������������������������\n");
    }
    else
    {
        printf("��������Ҫ���ҵ�������ߣ�");
        fflush(stdin);
        scanf("%s",authorname);
        printf("\n");
        while(p->book_next!=NULL)/*ָ���ͷ��������β�ڵ㣬����ͼ����Ϣ*/
        {
            p=p->book_next;
            if(strcmp(p->author,authorname)==0)
            {
                printf("����������������������������ͼ�����ҵ���ͼ����Ϣ���£�����������������������������\n");
                printf("      ����       ���       ����        ����       ������       �۸�\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("��������������������������ѯ��ϣ�������������������������\n");
    }
}
/*ͨ���������ѯͼ��*/
void Searchbook_publisher(struct Book *book_head)
{
    struct Book *p;
    char pub[20];
    p=book_head;
    if(book_head==NULL||book_head->book_next==NULL)/*�ж��ļ������Ƿ�Ϊ��*/
    {
        printf("������������������������ͼ���ļ�Ϊ�գ�������������������������\n");
    }
    else
    {
        printf("��������Ҫ���ҵ���ĳ����磺");
        fflush(stdin);
        scanf("%s",pub);
        printf("\n");
        while(p->book_next!=NULL)/*ָ���ͷ��������β�ڵ㣬����ͼ����Ϣ*/
        {
            p=p->book_next;
            if(strcmp(p->publisher,pub)==0)
            {
                printf("����������������������������ͼ�����ҵ���ͼ����Ϣ���£�����������������������������\n");
                printf("      ����       ���       ����        ����       ������       �۸�\n");
                printf("%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
            }
        }
        if(p->book_next==NULL)
            printf("��������������������������ѯ��ϣ�������������������������\n");
    }
}
/*����*/
void Borrowbook(struct People *people_head)
{
    struct People *s,*p;/*����ָ�������sָ���½ڵ�*/
    char flag='y';/*����flag�������û��ظ�����*/
    p=people_head;
    while(p->people_next!=NULL)/*����������β�ڵ�*/
    {
        p=p->people_next;
    }
    while(flag=='y')/*�����¿ռ䣬�������ݣ���ӽ�����*/
    {
        s=(struct People *)malloc(sizeof(struct People));
        printf(" ���������������");
        fflush(stdin);/*������뻺������Ϊ��ȷ����Ӱ���������ݶ�ȡ*/
        scanf("%s",s->peoplename);
        printf(" ������༶��");
        fflush(stdin);
        scanf("%s",s->cla);
        printf(" ������ѧ�ţ�");
        fflush(stdin);
        scanf("%d",&s->number);
        printf(" ������������");
        fflush(stdin);
        scanf("%s",s->bookname);
        printf(" ��������ı�ţ�");
        fflush(stdin);
        scanf("%d",&s->id);
        printf(" ������������ڣ�");
        fflush(stdin);
        scanf("%s",s->borrowdata);
        printf(" �����뻹�����ڣ�");
        fflush(stdin);
        scanf("%s",s->returndata);
        printf("\n");
        p->people_next=s;/*���½ڵ�s��ӽ���������ƽ�����ƶ�*/
        p=s;
        s->people_next=NULL;
        printf("����������������ɹ���������������\n");
        printf("�������������Ƿ�������飿y��n������������\n");
        fflush(stdin);
        scanf("%c",&flag);
        if(flag=='y') continue;
        else if(flag=='n') break;
    }
    int e=0;
    Savepeople(people_head,e);/*�������ļ�*/
}
/*����*/
void Returnbook(struct People *people_head)
{
    struct People *p,*q;
    int t=0;/*��¼�Ƿ���ɾ���ļ�¼*/
    int bookid;
    p=q=people_head;
    printf("������Ҫ������ı�ţ�");
    scanf("%d",&bookid);
    printf("\n");
    while(p!=NULL)
    {
        if((p->id)==bookid)
        {
            t++;
            for(;q->people_next!=p;)/*�ҵ���Ҫɾ���ڵ����һ���ڵ�q*/
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
        printf("����������������ɹ���������������\n");
    }
    else
    {
       printf("������������û���ҵ�������Ϣ������ʧ�ܣ�������������\n");
    }
    int e=1;
    Savepeople(people_head,e);
}
/*���ļ��и���ͼ���¼����ʼ������*/
void Copybook(struct Book *book_head)
{
    struct Book bookrecord;/*����*/
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
        strcpy(p->bookname,bookrecord.bookname);/*"."�ǶԶ����Ա�ĵ��ã���->"��ָ���еĳ�Ա*/
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
/*�����������ļ�*/
void Savebook(struct Book *book_head,int e)
{
    struct Book *p;
    FILE *fp;
    if(e==0)
    {
        fp=fopen("books.txt","a+");/*��׷�ӵķ�ʽ��ʽ�򿪿ɶ�д�ļ�*/
    }
    else
    {
        fp=fopen("books.txt","w+");/*�Զ�д�ķ�ʽ����һ���ļ���w+��׷��*/
    }
    if(fp==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    p=book_head;
    while(p->book_next!=NULL)/*ָ���ͷ��㿪ʼ��������β�ڵ㣬������������Ϣ*/
    {
        p=p->book_next;
        fprintf(fp,"%10s%10d%12s%12s%12s%12.2f\n",p->bookname,p->id,p->classfy,p->author,p->publisher,p->price);
        fprintf(fp,"\n");
    }
    rewind(fp);
    fclose(fp);
    if(e==0)
    {
        printf("�ѽ�ͼ�����ݱ�����books.txt�ļ���\n");
    }
    else
    {
        printf("�ѽ����º��ͼ�����ݱ�����books.txt�ļ���\n");
    }
}
/*��Ž����������ļ���*/
void Savepeople(struct People *people_head,int e)
{
    struct People *p;
    FILE *fp;
    if(e==0)
    {
        fp=fopen("borrowpeople.txt","a+");/*��׷�ӵķ�ʽ��ʽ�򿪿ɶ�д�ļ�*/
    }
    else
    {
        fp=fopen("borrowpeople.txt","w+");/*�Զ�д�ķ�ʽ����һ���ļ���w+��׷��*/
    }
    if(fp==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    p=people_head;
    while(p->people_next!=NULL)/*ָ���ͷ��㿪ʼ��������β�ڵ㣬������������Ϣ*/
    {
        p=p->people_next;
        fprintf(fp,"%10s%10s%10d%10s%10d%10s%10s\n",p->peoplename,p->cla,p->number,p->bookname,p->id,p->borrowdata,p->returndata);
        fprintf(fp,"\n");
    }
    rewind(fp);
    fclose(fp);
    if(e==0)
    {
        printf("�ѽ�ͼ�����ݱ�����borrowpeople.txt�ļ���\n");
    }
    else
    {
        printf("�ѽ����º��ͼ�����ݱ�����borrowpeople.txt�ļ���\n");
    }
}
/*���ļ��и��ƽ����������ڴ�*/
void Copypeople(struct People *people_head)
{
    struct People peoplerecord;/*����*/
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
        strcpy(p->peoplename,peoplerecord.peoplename);/*"."�ǶԶ����Ա�ĵ��ã���->"��ָ���еĳ�Ա,����*/
        strcpy(p->cla,peoplerecord.cla);/*�༶*/
        p->number=peoplerecord.number;/*ѧ��*/
        strcpy(p->bookname,peoplerecord.bookname);/*����*/
        p->id=peoplerecord.id;/*��ı��*/
        strcpy(p->borrowdata,peoplerecord.borrowdata);/*��������*/
        strcpy(p->returndata,peoplerecord.returndata);/*��������*/
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
    printf("��������������������������������ͼ�����ϵͳ��������������������������������\n");
    printf("����������������(1)���ͼ��                  (2)�޸�ͼ�顪������������������\n");
    printf("����������������(3)ɾ��ͼ��                  (4)���ͼ�顪������������������\n");
    printf("����������������(5)��ѯͼ��(����)            (6)��ѯͼ��(���)��������������\n");
    printf("����������������(7)��ѯͼ��(����)            (8)��ѯͼ��(������)����������\n");
    printf("����������������(9)����ͼ��                  (10)�黹ͼ�顪����������������\n");
    printf("��������������������������������(11)�˳�ϵͳ��������������������������������\n");
    printf("          ������ѡ�");
    while(scanf("%d",&choice)!=EOF)
    {
        if(choice==11)
        {
            printf("������������������������������лʹ��ͼ�����ϵͳ������������������������������\n");
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
                printf("����������������������������롪����������\n");
                break;
        }
        printf("\n");
        printf("          ������ѡ�");
    }
    return 0;
}
