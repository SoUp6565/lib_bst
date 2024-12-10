#include <iostream>

using namespace std;

class Node
{
private:
    int data;
    int weight;
    Node *lchild;
    Node *rchild;

public:
    Node(int d);
    Node() {};
    Node *insertI(int k);
    Node *insertR(int k);
    bool searchI(int k);
    bool searchR(int k);
    void inOrder();
    void preOrder();
    void postOrder();
    int height();
    friend ostream &operator<<(ostream &os, Node &c)
    {
        os << "data: " << c.data << endl;
        os << "weight: " << c.weight << endl;
        if (c.lchild != nullptr)
        {
            os << "lc: " << c.lchild->data << endl;
        }
        else
        {
            os << "lc: " << nullptr << endl;
        }
        if (c.rchild != nullptr)
        {
            os << "rc " << c.rchild->data << endl;
        }
        else
        {
            os << "rc: " << nullptr << endl;
        }

        return os;
    }
    friend istream &operator>>(istream &is, Node *&c)
    {
        if (c == nullptr)
        {
            cout << " data:" << endl;
            int d;
            is >> d;
            c = new Node(d);
        }
        else
        {
            cout << " data:" << endl;
            int d;
            is >> d;
            c->data = d;
            c->lchild = nullptr;
            c->rchild;
        }

        return is;
    }
    Node *deleteNode(int k);
    bool isBst();
    ~Node() {};
};

Node::Node(int d)
{
    data = d;
    weight = 1;
    lchild = nullptr;
    rchild = nullptr;
}

Node *Node::insertI(int k)
{
    Node *helper{this};
    while (helper != NULL)
    {
        if (k > helper->data)
        {
            if (helper->rchild == nullptr)
            {
                helper->rchild = new Node(k);
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
                helper->lchild = new Node(k);
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

void Node::inOrder()
{
    if (this == nullptr)
        return;
    lchild->inOrder();
    cout << data << " ";
    rchild->inOrder();
}

Node *Node::insertR(int k)
{
    if (this == nullptr)
    {
        return new Node(k);
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
            lchild = new Node(k);
        }
        {
            lchild->insertR(k);
        }
    }
    else
    {
        if (rchild == nullptr)
        {
            rchild = new Node(k);
        }
        {
            rchild->insertR(k);
        }
    }
    return this;
}

bool Node::searchR(int k)
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

bool Node::searchI(int k)
{
    Node *helper{this};
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

void Node::preOrder()
{
    if (this == nullptr)
        return;
    cout << data << " ";
    lchild->preOrder();
    rchild->preOrder();
}

void Node::postOrder()
{
    if (this == nullptr)
        return;
    lchild->postOrder();
    rchild->postOrder();
    cout << data << " ";
}

int Node::height()
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

bool Node::isBst()
{
    if (lchild != NULL)
    {
        if (lchild->data < data)
        {
            bool helper;
            helper = lchild->isBst();
            if (helper == false)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    if (rchild != NULL)
    {
        if (rchild->data > data)
        {
            bool helper;
            helper = rchild->isBst();
            if (helper == false)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

Node *Node::deleteNode(int k)
{
    if (searchR(k) == true)
    {
        if (k < data)
        {
            if (lchild->data == k)
            {
                if (lchild->lchild != nullptr && lchild->rchild != nullptr)
                {
                    Node *minDest = lchild->rchild;
                    Node *dad = lchild;
                    while (minDest->lchild != nullptr)
                    {
                        dad = minDest;
                        minDest = minDest->lchild;
                    }

                    int temp = lchild->data;
                    lchild->data = minDest->data;
                    minDest->data = temp;

                    if (dad->lchild == minDest)
                    {
                        delete minDest;
                        dad->lchild = nullptr;
                    }
                    else
                    {
                        delete minDest;
                        dad->rchild = nullptr;
                    }

                    return this;
                }
                else if (lchild->lchild != nullptr || lchild->rchild != nullptr)
                {
                    Node helper(0);
                    if (lchild->lchild != nullptr)
                    {
                        helper.data = lchild->data;
                        lchild->data = lchild->lchild->data;
                        lchild->lchild->data = helper.data;

                        delete lchild->lchild;
                        lchild->lchild = nullptr;
                        return this;
                    }
                    else
                    {
                        helper.data = lchild->data;
                        lchild->data = lchild->rchild->data;
                        lchild->rchild->data = helper.data;

                        delete lchild->rchild;
                        lchild->rchild = nullptr;
                        return this;
                    }
                }
                else
                {
                    delete lchild;
                    lchild = nullptr;
                    return this;
                }
            }
            lchild = lchild->deleteNode(k);
        }
        else if (k == data) // root
        {
            if (lchild == nullptr && rchild == nullptr)
            {
                delete this;
            }
            else if (lchild == nullptr || rchild == nullptr)
            {
                Node *temp;
                if (lchild != nullptr)
                {
                    temp = lchild;
                }
                else
                {
                    temp = rchild;
                }
                delete this;
                *this = *temp;
            }
            else
            {

                Node *minDest = rchild;
                Node *dad = this;
                while (minDest->lchild != nullptr)
                {
                    dad = minDest;
                    minDest = minDest->lchild;
                }
                int temp = data;
                data = minDest->data;
                minDest->data = temp;
                if (dad->lchild == minDest)
                {
                    delete minDest;
                    dad->lchild = nullptr;
                }
                else
                {
                    delete minDest;
                    dad->rchild = nullptr;
                }
            }
            return this;
        }
        else
        {
            if (rchild->data == k)
            {
                if (rchild->lchild != nullptr && rchild->rchild != nullptr)
                {

                    Node *minDest = rchild->rchild;
                    Node *dad = rchild;
                    while (minDest->lchild != nullptr)
                    {
                        dad = minDest;
                        minDest = minDest->lchild;
                    }

                    int temp = rchild->data;
                    rchild->data = minDest->data;
                    minDest->data = temp;

                    if (dad->lchild == minDest)
                    {
                        delete minDest;
                        dad->lchild = nullptr;
                    }
                    else
                    {
                        delete minDest;
                        dad->rchild = nullptr;
                    }

                    return this;
                }
                else if (rchild->lchild != nullptr || rchild->rchild != nullptr)
                {
                    Node helper(0);
                    if (lchild->lchild != nullptr)
                    {
                        helper.data = rchild->data;
                        rchild->data = rchild->lchild->data;
                        rchild->lchild->data = helper.data;

                        delete rchild->lchild;
                        rchild->lchild = nullptr;
                        return this;
                    }
                    else
                    {
                        helper.data = rchild->data;
                        rchild->data = rchild->rchild->data;
                        rchild->rchild->data = helper.data;

                        delete rchild->rchild;
                        rchild->rchild = nullptr;
                        return this;
                    }
                }
                else
                {
                    delete rchild;
                    rchild = nullptr;
                    return this;
                }
            }
            rchild = rchild->deleteNode(k);
        }

        return this;
    }
    else
    {
        cout << "non è presente nel bst" << endl;
        return this;
    }
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

node* eliminazione(node* &r, int k){ //verificare sempre prima la presenza del valore k nel bst con la funzione ricerca//f
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
