void display1(struct node* head){
    while (head){
        printf("%d",head->data);
        head=head->next;
    }
}
void display(struct BigInteger h){
    display1(h->L);
}
struct node * reverse(struct node *h){
    struct node *cur=h;
    struct node *prev=0;
    struct node *new=0;
    while (cur!=0){
        new=cur->next;
        cur->next=prev;
        prev=cur;
        cur=new;
    }
    return prev;
}
struct node * frontzeroterminator(struct node * head){
    while(head && head->data==0){
        head=head->next;
    }
    return head;
}
int compare(struct node *list1, struct node *list2) {
    // Compare lengths first
    int len1 = 0, len2 = 0;
    struct node *temp = list1;
    while (temp) {
        len1++;
        temp = temp->next;
    }
    temp = list2;
    while (temp) {
        len2++;
        temp = temp->next;
    }
    if (len1 > len2) return 1;
    if (len1 < len2) return 0;
    
    
    list1=reverse(list1);
    list2=reverse(list2);
    //If lengths are equal, compare digit by digit
    while (list1 && list2) {
        if (list1->data > list2->data) return 1;
        if (list1->data < list2->data) return 0;
        list1 = list1->next;
        list2 = list2->next;
    }
    
    list1=reverse(list1);
    list2=reverse(list2);
    return 1;
}
void inserthead(struct node** head, int val){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=val;
    new->next=0;
    if((*head)==0){
        *head=new;
        return ;
    }
    new->next=*head;
    *head=new;
}
struct node * convert(char *s){
    struct node* h=0;
    int i,c;
    for (i=0;s[i]!='\0';i++){
        c=s[i]-'0';
        inserthead(&h,c);
    }
    return h;
}
//addition 
struct node* addition(struct node *h1,struct node* h2){
    struct node *h=0;
    int val,f=0;
    while(h1&&h2){
        val=h1->data+h2->data+f;
        f=0;
        if (val>9){
            val=val-10;
            f=1;
        }
        else{
            f=0;
        }
        inserthead(&h,val);
        h2=h2->next;
        h1=h1->next;
    }
    while(h1){
        val=h1->data+f;
        f=0;
        if (val>9){
            val=val-10;
            f=1;
        }
        inserthead(&h,val);
        h1=h1->next;
    }
    while(h2){
        val=h2->data+f;
        f=0;
        if (val>9){
            val=val-10;
            f=1;
        }
        inserthead(&h,val);
        h2=h2->next;
    }
    if (f==1){
        inserthead(&h,1);
    }
    return h;
}
// multiply
struct node * multiply(struct node *h1, struct node *h2) {
    if (h1==0||h2==0) {
        struct node *result=(struct node *)malloc(sizeof(struct node));
        result->data=0;
        result->next=NULL;
        return result;
    }
    struct node *result=convert("0"); // Initialize result with 0

    struct node *h2Digit=h2;
    int shift=0;
    while (h2Digit) {
        int digit=h2Digit->data;
        struct node *tempResult=0;
        struct node *tempnode=h1;
        int carry=0;

        while (tempnode) {
            int product=tempnode->data * digit + carry;
            carry=product/10;
            inserthead(&tempResult,product%10);
            tempnode=tempnode->next;
        }

        if (carry>0) {
            inserthead(&tempResult,carry);
        }
        
        tempResult=reverse(tempResult);
        for (int i=0;i<shift;i++) {
            inserthead(&tempResult,0);
        }

        result = addition(result,tempResult);
        result=reverse(result);

        h2Digit=h2Digit->next;
        shift++;
    }
    result=reverse(result);
    return result;
}

//Subtraction
struct node* Subtraction(struct node*h1,struct node *h2){
    struct node* h=0;
    int val,b=0;
    while(h1&&h2){
        if ((h1->data)<h2->data){
            val=10+(h1->data)-(h2->data);
            h1->next->data=h1->next->data-1;
            inserthead(&h,val);
        }
        if ((h1->data)>=h2->data){
            val=h1->data-h2->data;
            inserthead(&h,val);
        }
        h1=h1->next;
        h2=h2->next;
    }
    while (h1){
        if ((h1->data)<0){
            val=10+(h1->data);
            h1->next->data=h1->next->data-1;
            inserthead(&h,val);
        }
        if ((h1->data)>=0){
            val=h1->data;
            inserthead(&h,val);
        }
        h1=h1->next;
    }
    if(!h){
        struct node* newnode=(struct node * )malloc(sizeof(struct node));
        newnode->data=0;
        newnode->next=NULL;
            h=newnode;
    }
    return h;
}
struct node* division(struct node* h1,struct node *h2){
    struct node* one=NULL;
    inserthead(&one,1);
    struct node *res=convert("0");
    struct node* h3=h1;
    int c=0;
    while(compare(h3,h2)==1){
        h3=Subtraction(h3,h2);
        h3=reverse(h3);
        res=addition(res,one);
        res=reverse(res);
    }
    // res=reverse(res);
    return res;
}
struct BigInteger initialize(char *s){
    struct BigInteger a;
    a->L=convert(s);
    return a;
}
struct BigInteger add(struct BigInteger a,struct BigInteger b){
    struct BigInteger c;
    c->L=addition(a->L,b->L);
    return c;
}
struct BigInteger sub(struct BigInteger a,struct BigInteger b){
    struct BigInteger c;
    c->L=Subtraction(a->L,b->L);
    return c;
}
struct BigInteger mul(struct BigInteger a,struct BigInteger b){
    struct BigInteger c;
    c->L=multiply(a->L,b->L);
    return c;
}
struct BigInteger div1(struct BigInteger a,struct BigInteger b){
    struct BigInteger c;
    c->L=division(a->L,b->L);
    return c;
}
