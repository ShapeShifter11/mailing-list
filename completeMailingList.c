#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct address {
    char name [30];
    char street [40];
    char city [20];
    char state [3];
    char zip [11];
    struct address *next;
    struct address *prior;
};

struct address *start;
struct address *last;
struct address *find(char *);

void enter(void), search(void), save(void);
void load(void), list(void);
void mldelete(struct address **, struct address **);
void dls_store(struct address *i, struct address **start, struct address **last);
void inputs(char *, char *, int), display(struct address *);
int menu_select(void);

int main(void){

    start = last = NULL;

    for(;;){
        switch (menu_select()){
            case 1: enter();
                break;
            case 2: mldelete(&start, &last);
                break;
            case 3: list();
                break;
            case 4: search();
                break;
            case 5: save();
                break;
            case 6: load();
                break;
            case 7: exit(0);
        }
    }
    return 0;
}

int menu_select(void){
    char s[80];

    int c;

    printf("1. Enter a name\n"
    "2. Delete a name\n"
    "3. List the file\n"
    "4. Search\n"
    "5. Save the file\n"
    "6. Load the file\n"
    "7. Quit\n");

    do{
        printf("Enter your choice: ");
        gets(s);
        c = atoi(s);
    }while(c < 0 || c > 7);
    return c;
}

void enter(void){
    struct address *info;

    for(;;){
        info = (struct address *)malloc(sizeof(struct address));
        if(!info){
            printf("\nOut of memmory\n");
            return;
        }
        inputs("Enter name: ", info->name, 30);
        if(!info->name[0]) break;
        inputs("Enter street: ", info->street, 40);
        inputs("Enter city: ", info->city, 20);
        inputs("Enter state: ", info->state, 3);
        inputs("Enteer zip: ", info->zip, 10);

        dls_store(info, &start, &last);
    }
}

/*this func will input a string in to the length in "count", 
and will prevent it from being overrun, also display a prompting msg*/

void inputs(char *prompt, char *s, int count){
    char p[255];

    do{
        printf(prompt);
        fgets(p, 254, stdin);
        if(strlen(p) > count) printf("\nMsg too long\n");
    }while(strlen(p) > count);

    p[strlen(p)-1] = 0;
    strcpy(s, p);
}

void dls_store(struct address *i, struct address **start, struct address **last){
    struct address *old, *p;

    if(*last == NULL){ /* first element in list*/
        i->next = NULL;
        i->prior = NULL;
        *last = i;
        *start = i;
        return;
    }
    p = *start;
    
    old = NULL;

    while(p){
        if(strcmp(p->name, i->name)<0){
            old = p;
            p = p->next;
        } else {
            if(p->prior) {
                p->prior->next = i;
                i->next = p;
                i->prior = p->prior;
                p->prior = i;
                return;
            }
            i->next = p;
            i->prior = NULL;
            p->prior = i;
            *start = i;
            return;
        }
    }
    old->next = i;
    i->next = NULL;
    i->prior = old;
    *last = i;
    return;
}

void mldelete(struct address **start, struct address **last){
    struct address *info;
    char s[80];

    inputs("Enter name: ", s, 30);
    info = find(s);
    if(info){
        if(*start == info){
            *start = info->next;
            if(*start) (*start)->prior = NULL;
            else *last = NULL;
        }else{
            info->prior->next = info->next;
            if(info!=(*last)) info->next->prior = info->prior;
            else *last = info->prior;
        }
        free(info);
    }
}

struct address *find(char *name){
    struct address *info;

    info = start;
    while(info){
        if(!strcmp(name, info->name)) return info;
        info = info->next;
    }
    printf("\nname not fount\n");
    return NULL;
}

void list(void){
    struct address *info;

    info = start;
    while(info){
        display(info);
        info = info->next;
    }
    printf("\n\n");
}

void display(struct address *info){
    printf("%s\n", info->name);
    printf("%s\n", info->street);
    printf("%s\n", info->city);
    printf("%s\n", info->state);
    printf("%s\n", info->zip);
    printf("\n\n");
}

void search(void){
    char name[40];
    struct address *info;

    printf("Enter a name to find: ");
    gets(name);
    info = find(name);
    if(!info) printf("not found\n");
    else display(info);
}

void save(void){
    struct address *info;

    FILE *fp;

    fp = fopen("mlist", "wb");
    if(!fp){
        printf("cannot open file\n");
        exit(1);
    }
    printf("\nsaving file\n");

    info = start;
    while(info){
        fwrite(info, sizeof(struct address), 1, fp);
        info = info->next;
    }
    fclose(fp);
}

void load(void){
    struct addres *info;
    FILE *fp;

    fp = fopen("mlist", "rb");
    if(!fp){
        printf("cannot open\n");
        exit(1);
    }
    while(start){
        info = start->next;
        free(info);
        start = info;
    }
    start = last = NULL;

    printf("\nloading file\n");

    while(!feof(fp)){
        info = (struct address *)malloc(sizeof(struct address));
        if(!info){
            pritf("Out of memory");
            return;
        }
        if(1 != fread(info, sizeof(struct address), 1, fp)) break;
        dls_store(info, &start, &last);
    }
    fclose(fp);
}