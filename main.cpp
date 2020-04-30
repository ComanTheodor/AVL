#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
struct avl {
   int di;
   struct avl *s;
   struct avl *d;
}*d;
class avl_tree {
   public:
      int inaltime(avl *);
      int difference(avl *);
      avl *dd_rotat(avl *);
      avl *ss_rotat(avl *);
      avl *sd_rotat(avl*);
      avl *ds_rotat(avl *);
      avl * balance(avl *);
      avl * insert(avl*, int);
      void show(avl*, int);
      void inorder(avl *);
      void preorder(avl *);
      void postorder(avl*);
      avl_tree() {
         d = NULL;
      }
};
int avl_tree::inaltime(avl *t) {
   int h = 0;
   if (t != NULL) {
      int s_inaltime = inaltime(t->s);
      int d_inaltime = inaltime(t->d);
      int max_inaltime = max(s_inaltime, d_inaltime);
      h = max_inaltime + 1;
   }
   return h;
}
int avl_tree::difference(avl *t) {
   int s_inaltime = inaltime(t->s);
   int d_inaltime = inaltime(t->d);
   int b_factor = s_inaltime - d_inaltime;
   return b_factor;
}
avl *avl_tree::dd_rotat(avl *parent) {
   avl *t;
   t = parent->d;
   parent->d = t->s;
   t->s = parent;
   cout<<"Rotatie Dreapta-Dreapta";
   return t;
}

avl *avl_tree::ss_rotat(avl *parent) {
   avl *t;
   t = parent->s;
   parent->s = t->d;
   t->d = parent;
   cout<<"Rotatie Stanga-Stanga";
   return t;
}

avl *avl_tree::sd_rotat(avl *parent) {
   avl *t;
   t = parent->s;
   parent->s = dd_rotat(t);
   cout<<"Rotatie Stanga-Dreapta";
   return ss_rotat(parent);
}
avl *avl_tree::ds_rotat(avl *parent) {
   avl *t;
   t = parent->d;
   parent->d = ss_rotat(t);
   cout<<"Rotatie Dreapta-Stanga";
   return dd_rotat(parent);
}

avl *avl_tree::balance(avl *t) {
   int bal_factor = difference(t);
   if (bal_factor > 1) {
      if (difference(t->s) > 0)
         t = ss_rotat(t);
      else
         t = sd_rotat(t);
   } else if (bal_factor < -1) {
      if (difference(t->d) > 0)
         t = ds_rotat(t);
      else
         t = dd_rotat(t);
   }
   return t;
}
avl *avl_tree::insert(avl *d, int v) {
   if (d == NULL) {
      d = new avl;
      d->di = v;
      d->s = NULL;
      d->d = NULL;
      return d;
   } else if (v< d->di) {
      d->s = insert(d->s, v);
      d = balance(d);
   } else if (v >= d->di) {
      d->d = insert(d->d, v);
      d = balance(d);
   } return d;
}
void avl_tree::show(avl *p, int s) {
   int i;
   if (p != NULL) {
      show(p->d, s+ 1);
      cout<<" ";
      if (p == d)
         cout << "Root -> ";
      for (i = 0; i < s&& p != d; i++)
         cout << " ";
         cout << p->di;
         show(p->s, s + 1);
   }
}
void avl_tree::inorder(avl *t) {
   if (t == NULL)
      return;
      inorder(t->s);
      cout << t->di << " ";
      inorder(t->d);
}
void avl_tree::preorder(avl *t) {
   if (t == NULL)
      return;
      cout << t->di << " ";
      preorder(t->s);
      preorder(t->d);
}
void avl_tree::postorder(avl *t) {
   if (t == NULL)
      return;
      postorder(t ->s);
      postorder(t ->d);
      cout << t->di << " ";
}

int main() {
   int c, i;
   avl_tree avl;
   while (1) {
      cout << "1.Introdu element in arbore" << endl;
      cout << "2.show Balanced AVL Tree" << endl;
      cout << "3.InOrder traversal" << endl;
      cout << "4.PreOrder traversal" << endl;
      cout << "5.PostOrder traversal" << endl;
      cout << "6.Iesire" << endl;
      cout << "Alege o optiune: ";
      cin >> c;
      switch (c) {
         case 1:
            cout << "Alege o valoare care sa fie introdusa: ";
            cin >> i;
            d = avl.insert(d, i);
         break;
         case 2:
            if (d == NULL) {
               cout << "Arborele este gol" << endl;
               continue;
            }
            cout << "Arborele AVL este balansat:" << endl;
            avl.show(d, 1);
            cout<<endl;
         break;
         case 3:
            cout << "Inorder Traversal:" << endl;
            avl.inorder(d);
            cout << endl;
         break;
         case 4:
            cout << "Preorder Traversal:" << endl;
            avl.preorder(d);
            cout << endl;
         break;
         case 5:
            cout << "Postorder Traversal:" << endl;
            avl.postorder(d);
            cout << endl;
         break;
         case 6:
            exit(1);
         break;
         default:
            cout << "Alegere grersita" << endl;
      }
   }
   return 0;
}






















