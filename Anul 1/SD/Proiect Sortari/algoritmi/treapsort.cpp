#include <vector>
#include <iostream>
#include <ctime>
#include <random>

namespace treapsort
{
    class Treap
    {
    public:
        struct nod
        {
            int val, priority;
            nod *fiuSt, *fiuDr;
        };
        Treap(nod *root = nullptr)
        {
            this->root = root;
            srand(time(0));
        }
        ~Treap()
        {
            Delete(root);
        }
        void Insert(int val)
        {
            Insert(root, rand(), val);
        }
        void GetOrder(std::vector<int> &ret)
        {
            DFS(root, ret);
        }
        void Split(int val, Treap &st, Treap &dr)
        {
            nod *retSt, *retDr;
            Split(root, val, retSt, retDr);
            st = Treap(retSt);
            dr = Treap(retDr);
        }
        //that > this
        void Join(Treap &that)
        {
            root = Join(root, that.root);
            that = Treap();
        }
    private:
        void Delete(nod *current)
        {
            if(current == nullptr)
                return;
            Delete(current->fiuSt);
            Delete(current->fiuDr);
            delete current;
            current = nullptr;
        }
        void DFS(nod *current, std::vector<int> &ret)
        {
            if(current == nullptr)
                return;
            DFS(current->fiuSt, ret);
            ret.push_back(current->val);
            DFS(current->fiuDr, ret);
        }
        void Split(nod *current, int val, nod * &st, nod * &dr)
        {
            if(current == nullptr)
                st = dr = nullptr;
            else if(val < current->val)
            {
                dr = current;
                Split(current->fiuSt, val, st, current->fiuSt);
            }
            else
            {
                st = current;
                Split(current->fiuDr, val, current->fiuDr, dr);
            }
        }
        nod * Join(nod * st, nod * dr)
        {
            if(st == nullptr)
                return dr;
            if(dr == nullptr)
                return st;
            if(st->priority >= dr->priority)
            {
                st = Join(st->fiuDr, dr);
                return st;
            }
            dr = Join(st, dr->fiuSt);
            return dr;
        }
        void Insert(nod * &current, int priority, int val)
        {
            if(current == nullptr || priority > current->priority)
            {
                nod * st, * dr;
                Split(current, val, st, dr);
                current = new nod;
                current->val = val, current->priority = priority;
                current->fiuSt = st, current->fiuDr = dr;
                return;
            }
            if(val < current->val)
                Insert(current->fiuSt, priority, val);
            else
                Insert(current->fiuDr, priority, val);
        }
        nod * root;
    };

    void Sort(std::vector<int> &v)
    {
        Treap treap;
        for(int x:v)
            treap.Insert(x);
        v.clear();
        treap.GetOrder(v);
    }
}
