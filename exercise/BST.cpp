#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template <typename elemType>
class BinaryTree;
template <typename valType>
class BTnode;

template <typename valType>
ostream& foo(ostream& os, const BTnode<valType>& bt);

template <typename valType>
class BTnode {

    friend class BinaryTree<valType>;

public:
    BTnode(const valType& val);

    const valType& value() const { return _val; }
    int            occurs() const { return _cnt; }

    void remove_value(const valType&, BTnode*&);
    void insert_value(const valType&);
    bool find_value(const valType&) const;

    void preorder(BTnode*, ostream&) const;
    void inorder(BTnode*, ostream&) const;
    void postorder(BTnode*, ostream&) const;

    static void lchild_leaf(BTnode* leaf, BTnode* subtree);

private:
    int     _cnt;
    valType _val;
    BTnode* _lchild;
    BTnode* _rchild;

    void display_val(BTnode* pt, ostream& os) const;
    BTnode(const BTnode&);
    BTnode& operator=(const BTnode&);
};

template <typename valType>
inline BTnode<valType>::BTnode(const valType& val) : _val(val) {
    _cnt    = 1;
    _lchild = _rchild = 0;
}

template <typename valType>
void BTnode<valType>::insert_value(const valType& val) {
    if(val == _val) {
        ++_cnt;
        (*BinaryTree<valType>::os()) << "BTnode::insert_value: increment count(" << val << " : " << _cnt << ")\n";
        return;
    }

    if(val < _val) {
        if(!_lchild) {
            _lchild = new BTnode(val);
            (*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at left child( " << val << ")\n";
        }
        else
            _lchild->insert_value(val);
    }
    else {
        if(!_rchild) {
            _rchild = new BTnode(val);
            (*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at right child( " << val << ")\n";
        }
        else
            _rchild->insert_value(val);
    }
}

template <typename valType>
bool BTnode<valType>::find_value(const valType& val) const {
    if(val == _val)
        return true;

    if(val < _val) {
        if(!_lchild)
            return false;
        else
            return _lchild->find_value(val);
    }
    else {
        if(!_rchild)
            return false;
        else
            return _rchild->find_value(val);
    }
}

//找到叶子节点,并将leaf变为新叶
template <typename valType>
void BTnode<valType>::lchild_leaf(BTnode* leaf, BTnode* subtree) {
    while(subtree->_lchild)
        subtree->_lchild;
    subtree->_lchild = leaf;
}

//移除
//右子树代替 左子树放在右子树的左子叶上
//无右子树 左子树代替
//当前处于某节点中 prev代表当前节点
//*& *代表的只是指向 &取址才可修改
template <typename valType>
void BTnode<valType>::remove_value(const valType& val, BTnode*& prev) {
    if(val < _val) {
        if(!_lchild)
            return;  // not present
        else
            _lchild->remove_value(val, _lchild);
    }
    else if(val > _val) {
        if(!_rchild)
            return;  // not present
        else
            _rchild->remove_value(val, _rchild);
    }
    else {
        if(_rchild) {
            prev = _rchild;
            if(_lchild) {
                if(!prev->_lchild)
                    prev->_lchild = _lchild;
                else
                    BTnode<valType>::lchild_leaf(_lchild, prev->_lchild);
            }
        }
        else
            prev = _lchild;
        delete this;  //删除当前结点
    }
}

template <typename valType>
inline void BTnode<valType>::display_val(BTnode* pt, ostream& os) const {
    os << pt->_val;
    if(pt->_cnt > 1)
        os << "(" << pt->_cnt << ")";
    else
        os << " ";
}

template <typename valType>
void BTnode<valType>::preorder(BTnode* pt, ostream& os) const {
    if(pt) {
        display_val(pt, os);
        if(pt->_lchild)
            preorder(pt->_lchild, os);
        if(pt->_rchild)
            preorder(pt->_rchild, os);
    }
}

template <typename valType>
void BTnode<valType>::inorder(BTnode* pt, ostream& os) const {
    if(pt) {
        display_val(pt, os);
        if(pt->_lchild)
            preorder(pt->_lchild, os);
        if(pt->_rchild)
            preorder(pt->_rchild, os);
    }
}

template <typename valType>
void BTnode<valType>::postorder(BTnode* pt, ostream& os) const {
    if(pt) {
        display_val(pt, os);
        if(pt->_lchild)
            preorder(pt->_lchild, os);
        if(pt->_rchild)
            preorder(pt->_rchild, os);
    }
}

template <typename elemType>
class BinaryTree {
public:
    BinaryTree() : _root(0) {}
    BinaryTree(const vector<elemType>& vec) {
        _root = 0;
        for(int i = 0; i < vec.size(); ++i)
            insert(vec[i]);
    };
    BinaryTree(const BinaryTree& rhs) { copy(_root, rhs._root); };
    ~BinaryTree() { clear(); }
    BinaryTree& operator=(const BinaryTree& rhs) {
        if(this != &rhs) {
            clear();
            copy(_root, rhs._root);
        }
    };

    void insert(const vector<elemType>& vec) {
        for(int i = 0; i < vec.size(); ++i)
            insert(vec[i]);
    }
    void insert(const elemType& elem) {
        if(!_root) {
            (*BinaryTree<elemType>::os()) << "BinaryTree::insert: root( " << elem << ")\n";
            _root = new BTnode<elemType>(elem);
        }
        else
            _root->insert_value(elem);
    }
    void remove(const elemType& elem) {
        if(_root) {
            if(_root->_val == elem)
                remove_root();
            else
                _root->remove_value(elem, _root);
        }
    }
    void clear() {
        clear(_root);
        _root = 0;
    }

    bool empty() { return _root == 0; }

    void inorder(ostream& os = *_current_os) const { _root->inorder(_root, os); }
    void postorder(ostream& os = *_current_os) const { _root->postorder(_root, os); }
    void preorder(ostream& os = *_current_os) const { _root->preorder(_root, os); }

    bool     find(const elemType&) const;
    ostream& print(ostream& os = *_current_os, void (BinaryTree<elemType>::*traversal)(ostream&) const = &BinaryTree<elemType>::inorder) const {
        (this->*traversal)(os);
        return os;
    }

    static void current_os(ostream* os) {
        if(os)
            _current_os = os;
    }
    static ostream* os() { return _current_os; }

private:
    BTnode<elemType>* _root;
    static ostream*   _current_os;

    void copy(BTnode<elemType>*& tar, BTnode<elemType>* src);
    void clear(BTnode<elemType>* pt) {
        if(pt) {
            clear(pt->_lchild);
            clear(pt->_rchild);
            delete pt;
        }
    }
    void remove_root() {
        if(!_root)
            return;
        BTnode<elemType>* tmp = _root;

        if(_root->_rchild) {
            _root                   = _root->_rchild;
            BTnode<elemType>* lc    = tmp->_lchild;
            BTnode<elemType>* newlc = _root->_lchild;

            // if left child of root is non_null
            // attach it as leaf to left substree

            if(lc) {
                if(!newlc)
                    _root->_lchild = lc;
                else
                    BTnode<elemType>::lchild_leaf(lc, newlc);
            }
        }
        else
            _root = _root->_lchild;

        delete tmp;
    }
};

int main() {

    string str;
    cin >> str;
    cout << str << "\n";

    return 0;
}