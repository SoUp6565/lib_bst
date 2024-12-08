#include <iostream>

using namespace std;

class node
{
private:
    int data;
    int weight;
    node *lchild;
    node *rchild;

public:
    node(int d);
    node *insertI(int k);
    node *insertR(int k);
    bool searchI(int k);
    bool searchR(int k);
    void inOrder();
    void preOrder();
    void postOrder();
    int height();
    bool isBst(int min, int max);
    friend ostream &operator<<(ostream &os, node &c)
    {
        os << "data: " << c.data << endl;
        os << "weight: " << c.weight << endl;
        os << "lc: " << c.lchild << endl;
        os << "rc " << c.rchild << endl;
        return os;
    }
    friend istream &operator>>(istream &is, node &c)
    //non crea la root
    {
        cout << " data:" << endl;
        int d;
        is>>d;
        c.insertI(d);
        return is;
    }
    ~node() {};
};

node::node(int d)
{
    data = d;
    weight = 1;
    lchild = nullptr;
    rchild = nullptr;
}

node *node::insertI(int k)
{
    node *helper{this};
    while (helper != NULL)
    {
        if (k > helper->data)
        {
            if (helper->rchild == nullptr)
            {
                helper->rchild = new node(k);
                break;
            }
            else
            {
                helper = helper->rchild;
            }
        }
        else
        {
            if (helper->lchild == nullptr)
            {
                helper->lchild = new node(k);
                break;
            }
            else
            {
                helper = helper->lchild;
            }
        }
    }

    return this;
}

void node::inOrder()
{
    if (this == nullptr)
        return;
    lchild->inOrder();
    cout << data << " ";
    rchild->inOrder();
}

node *node::insertR(int k)
{
    if (this == nullptr)
    {
        return new node(k);
    }

    if (data == k)
    {
        weight += 1;
        return this;
    }

    if (k < data)
    {
        if (lchild == nullptr)
        {
            lchild = new node(k);
        }
        {
            lchild->insertR(k);
        }
    }
    else
    {
        if (rchild == nullptr)
        {
            rchild = new node(k);
        }
        {
            rchild->insertR(k);
        }
    }
    return this;
}

bool node::searchR(int k)
{
    if (this == nullptr)
    {
        return false;
    }

    if (data == k)
    {
        return true;
    }

    if (k < data)
    {
        if (lchild == nullptr)
        {
            return false;
        }
        else
        {
            return lchild->searchR(k);
        }
    }
    else
    {
        if (rchild == nullptr)
        {
            return false;
        }
        else
        {
            return rchild->searchR(k);
        }
    }
    return false;
}

bool node::searchI(int k)
{
    node *helper{this};
    while (helper != NULL)
    {
        if (helper->data == k)
        {
            return true;
        }
        else
        {
            if (k > helper->data)
            {
                if (helper->data == k)
                {
                    return true;
                }
                else
                {
                    helper = helper->rchild;
                }
            }
            else
            {
                if (helper->data == k)
                {
                    return true;
                }
                else
                {
                    helper = helper->lchild;
                }
            }
        }
    }
    return false;
}

void node::preOrder()
{
    if (this == nullptr)
        return;
    cout << data << " ";
    lchild->preOrder();
    rchild->preOrder();
}

void node::postOrder()
{
    if (this == nullptr)
        return;
    lchild->postOrder();
    rchild->postOrder();
    cout << data << " ";
}

int node::height()
{
    if (this == nullptr)
        return 0;

    int altSx{lchild->height()};

    int altDx{rchild->height()};

    if ((altDx + 1) > (altSx + 1))
    {
        return altDx + 1;
    }
    else
    {
        return altSx + 1;
    }
}

bool node::isBst(int min, int max)
{ // da correggire
    if (this == nullptr)
    {
        return true;
    }
    if (data <= min || data >= max)
    {
        return false;
    }

    return lchild->isBst(min, data) && rchild->isBst(data, max);
}

/*
struct node{//f
    int value;
    int ntimes;
    node* lchild;
    node* rchild;
    node(int v){
        value=v;
        ntimes=1;
        lchild=nullptr;
        rchild=nullptr;
    }
};

node* inserimentoRic(node* r, int k){//f
    if (r==NULL)
    {
        return new node(k);
    }

    if (r->value==k)
    {
        r->ntimes+=1;
        return r;
    }

    if (k < r->value)
    {
        r->lchild=inserimentoRic(r->lchild,k);
    }
    else{
        r->rchild=inserimentoRic(r->rchild,k);
    }

    return r;
}

node* inserimentoNonRic(node* r, int k){//f
    node* helper{r};
    while (helper!=NULL)
    {
        if (k>helper->value)
        {
            if (helper->rchild==nullptr)
            {
                helper->rchild=new node(k);
                break;
            }
            else{
                helper=helper->rchild;
            }
        }
        else{
            if (helper->lchild==nullptr)
            {
                helper->lchild=new node(k);
                break;
            }
            else{
                helper=helper->lchild;
            }
        }
    }

    return r;
}

bool ricerca(node* r, int k){//f
    node* helper{r};
    while (helper!=NULL)
    {
        if (helper->value==k)
        {
            return true;
        }
        else{
            if (k>helper->value)
            {
                if (helper->value==k)
                {
                    return true;
                }
                else{
                    helper=helper->rchild;
                }
            }
            else{
                if (helper->value==k)
                {
                    return true;
                }
                else{
                    helper=helper->lchild;
                }
            }
        }

    }
    return false;
}

node* eliminazione(node* &r, int k){ //verificare sempre prima la presenza del valore k nel bst con la funzione ricerca
    if (ricerca(r,k)==true)
    {
        if (k < r->value)
        {
            if (r->lchild->value==k)
            {
                if (r->lchild->lchild!=nullptr && r->lchild->rchild!=nullptr)
                {
                    node* minDest = r->lchild->rchild;
                    node* dad = r->lchild;
                    while (minDest->lchild != nullptr) {
                        dad = minDest;
                        minDest = minDest->lchild;
                    }

                    int temp = r->lchild->value;
                    r->lchild->value = minDest->value;
                    minDest->value = temp;

                    if (dad->lchild == minDest) {
                        delete minDest;
                        dad->lchild = nullptr;
                    } else {
                        delete minDest;
                        dad->rchild = nullptr;
                    }

                    return r;
                }
                else if (r->lchild->lchild!=nullptr || r->lchild->rchild!=nullptr)
                {
                    node helper(0);
                    if (r->lchild->lchild!=nullptr)
                    {
                        helper.value=r->lchild->value;
                        r->lchild->value=r->lchild->lchild->value;
                        r->lchild->lchild->value=helper.value;

                        delete r->lchild->lchild;
                        r->lchild->lchild=nullptr;
                        return r;
                    }
                    else{
                        helper.value=r->lchild->value;
                        r->lchild->value=r->lchild->rchild->value;
                        r->lchild->rchild->value=helper.value;

                        delete r->lchild->rchild;
                        r->lchild->rchild=nullptr;
                        return r;
                    }
                }
                else{
                    delete r->lchild;
                    r->lchild=nullptr;
                    return r;
                }
            }
            r->lchild=eliminazione(r->lchild,k);
        }
        else if (k==r->value) //root
        {
            if (r->lchild == nullptr && r->rchild == nullptr) {
                delete r;
                r = nullptr;
            }
            else if (r->lchild == nullptr || r->rchild == nullptr) {
                node* temp;
                if (r->lchild != nullptr) {
                    temp = r->lchild;
                } else {
                    temp = r->rchild;
                }
                delete r;
                r = temp;
            }
            else {

                node* minDest = r->rchild;
                node* dad = r;
                while (minDest->lchild != nullptr) {
                    dad = minDest;
                    minDest = minDest->lchild;
                }
                int temp = r->value;
                r->value = minDest->value;
                minDest->value = temp;
                if (dad->lchild == minDest) {
                    delete minDest;
                    dad->lchild = nullptr;
                } else {
                    delete minDest;
                    dad->rchild = nullptr;
                }
            }
            return r;
        }
        else{
            if (r->rchild->value==k)
            {
                if (r->rchild->lchild!=nullptr && r->rchild->rchild!=nullptr)
                {

                    node* minDest = r->rchild->rchild;
                    node* dad = r->rchild;
                    while (minDest->lchild != nullptr) {
                        dad = minDest;
                        minDest = minDest->lchild;
                    }

                    int temp = r->rchild->value;
                    r->rchild->value = minDest->value;
                    minDest->value = temp;

                    if (dad->lchild == minDest) {
                        delete minDest;
                        dad->lchild = nullptr;
                    } else {
                        delete minDest;
                        dad->rchild = nullptr;
                    }

                    return r;
                }
                else if (r->rchild->lchild!=nullptr || r->rchild->rchild!=nullptr)
                {
                    node helper(0);
                    if (r->lchild->lchild!=nullptr)
                    {
                        helper.value=r->rchild->value;
                        r->rchild->value=r->rchild->lchild->value;
                        r->rchild->lchild->value=helper.value;

                        delete r->rchild->lchild;
                        r->rchild->lchild=nullptr;
                        return r;
                    }
                    else{
                        helper.value=r->rchild->value;
                        r->rchild->value=r->rchild->rchild->value;
                        r->rchild->rchild->value=helper.value;

                        delete r->rchild->rchild;
                        r->rchild->rchild=nullptr;
                        return r;
                    }
                }
                else{
                    delete r->rchild;
                    r->rchild=nullptr;
                    return r;
                }
            }
            r->rchild=eliminazione(r->rchild,k);
        }

        return r;
    }
    else{
        cout<<"non è presente nel bst"<<endl;
        return r;
    }
}

void preOrder(node* r) {//f

    if (r == nullptr) return;

    cout << r->value << " ";

    preOrder(r->lchild);

    preOrder(r->rchild);

}

void InOrder(node* r){//f
    if (r == nullptr) return;

    InOrder(r->lchild);

    cout << r->value << " ";

    InOrder(r->rchild);
}

void PostOrder(node* r){//f
    if (r == nullptr) return;

    PostOrder(r->lchild);

    PostOrder(r->rchild);

    cout << r->value << " ";
}


int altezza(node* r){//f
    if (r == nullptr) return 0;

    int altSx{altezza(r->lchild)};

    int altDx{altezza(r->rchild)};

    if ((altDx+1)>(altSx+1))
    {
        return altDx+1;
    }
    else{
        return altSx+1;
    }
}



bool isBst(node* r, int min, int max){ //usare <limits.h> quando passi i valore int (INT_MIN e INT_MAX)
    if (r==nullptr)
    {
        return true;
    }
    if (r->value<=min||r->value>=max)
    {
        return false;
    }

    return isBst(r->lchild,min,r->value)&&isBst(r->rchild,r->value,max);

}

*/
