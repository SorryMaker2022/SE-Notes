/*
 * Created by Sorrymaker2022 on 2022/05/19
 * A naive RBTree implementation
 */

#ifndef RBT_RB_TREE_H
#define RBT_RB_TREE_H

#define BLACK true
#define RED false

class RB_Tree
{
public:
    /* definition for RBTree node */
    class RB_Tree_Node
    {
    public:
        int key;
        bool color;
        RB_Tree_Node* parent;
        RB_Tree_Node* left_child;
        RB_Tree_Node* right_child;

        RB_Tree_Node() {};
        ~RB_Tree_Node() {};

        RB_Tree_Node(int key, bool color)
        {
            this -> key = key;
            this -> color = color;
            parent = nullptr;
            left_child = nullptr;
            right_child = nullptr;
        }
    };
    
    /* all leaf nodes' children are the same, namely sentinel */
    RB_Tree_Node* sentinel;
    RB_Tree_Node* root;

    RB_Tree()
    {
        sentinel = new RB_Tree_Node(-1, BLACK);
        sentinel -> left_child = sentinel;
        sentinel -> right_child = sentinel;
        sentinel -> parent = sentinel;
        root = sentinel;
    }

    ~RB_Tree() {};

    /* check whether a node is its parent's left child or right child */
    /* false for left and true for right */
    bool get_child_flag(RB_Tree_Node* child)
    {
        if(child -> parent -> key > child -> key)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    /* single right rotate */
    /* returns a pointer to the node on the original root's topological position on the tree */
    RB_Tree_Node* right_rotate(RB_Tree_Node* root)
    {
        if(root == sentinel)
        {
            return root;
        }
        RB_Tree_Node* rotate_temp = root -> left_child;
        root -> left_child = rotate_temp -> right_child;

        if(rotate_temp -> right_child != sentinel)
        {
            rotate_temp -> right_child -> parent = root;
        }
        rotate_temp -> parent = root -> parent;

        if(root -> parent == sentinel)
        {
            this -> root = rotate_temp;
        }
        else if(!(get_child_flag(root)))
        {
            root -> parent -> left_child = rotate_temp;
        }
        else
        {
            root -> parent -> right_child = rotate_temp;
        }

        rotate_temp -> right_child = root;
        root -> parent = rotate_temp;

        return root;
    }

    /* single left rotate */
    /* returns a pointer to the node on the original root's topological position on the tree */
    RB_Tree_Node* left_rotate(RB_Tree_Node* root)
    {
        if(root == sentinel)
        {
            return root;
        }
        RB_Tree_Node* rotate_temp = root -> right_child;
        root -> right_child = rotate_temp -> left_child;

        if(rotate_temp -> left_child != sentinel)
        {
            rotate_temp -> left_child -> parent = root;
        }
        rotate_temp -> parent = root -> parent;

        if(root -> parent == sentinel)
        {
            this -> root = rotate_temp;
        }
        else if(!(get_child_flag(root)))
        {
            root -> parent -> left_child = rotate_temp;
        }
        else
        {
            root -> parent -> right_child = rotate_temp;
        }

        rotate_temp -> left_child = root;
        root -> parent = rotate_temp;

        return root;
    }

    /* take INTRODUCTION TO ALGORITHMS as a reference */
    void insert_fixup(RB_Tree_Node* fix_node)
    {
        while(fix_node -> parent -> color == RED)
        {
            if(!(get_child_flag(fix_node -> parent)))
            {
                RB_Tree_Node* fix_temp = fix_node -> parent -> parent -> right_child;
                if(fix_temp -> color == RED)
                {
                    fix_node -> parent -> color = BLACK;
                    fix_temp -> color = BLACK;
                    fix_node -> parent -> parent -> color = RED;
                    fix_node = fix_node -> parent -> parent;
                }
                else if(get_child_flag(fix_node))
                {
                    fix_node = fix_node -> parent;
                    left_rotate(fix_node);
                }
                else
                {
                    fix_node -> parent -> color = BLACK;
                    fix_node -> parent -> parent -> color = RED;
                    right_rotate(fix_node -> parent -> parent);
                }
            }
            else
            {
                RB_Tree_Node* fix_temp = fix_node -> parent -> parent -> left_child;
                if(fix_temp -> color == RED)
                {
                    fix_node -> parent -> color = BLACK;
                    fix_temp -> color = BLACK;
                    fix_node -> parent -> parent -> color = RED;
                    fix_node = fix_node -> parent -> parent;
                }
                else if(!(get_child_flag(fix_node)))
                {
                    fix_node = fix_node -> parent;
                    right_rotate(fix_node);
                }
                else
                {
                    fix_node -> parent -> color = BLACK;
                    fix_node -> parent -> parent -> color = RED;
                    left_rotate(fix_node -> parent -> parent);
                }
            }
            sentinel -> color = BLACK;
            root -> color = BLACK;
        }
        root -> color = BLACK;
        return;
    }

    /* insert as if the tree were a BST, then fix up to balance */
    int insert(int key)
    {
        RB_Tree_Node* insert_temp = sentinel;
        RB_Tree_Node* insert_next = root;

        while(insert_next != sentinel)
        {
            insert_temp = insert_next;
            if(key == insert_next -> key)
            {
                return 1;
            }
            else if(key < insert_next -> key)
            {
                insert_next = insert_next -> left_child;
            }
            else
            {
                insert_next = insert_next -> right_child;
            }
        }

        RB_Tree_Node* new_node = new RB_Tree_Node(key, RED);
        new_node -> parent = insert_temp;

        if(insert_temp == sentinel)
        {
            root = new_node;
        }
        else if(get_child_flag(new_node))
        {
            insert_temp -> right_child = new_node;
        }
        else
        {
            insert_temp -> left_child = new_node;
        }

        new_node -> left_child = sentinel;
        new_node -> right_child = sentinel;
        insert_fixup(new_node);

        return 0;
    }

    /* take INTRODUCTION TO ALGORITHMS as a reference */
    void erase_fixup(RB_Tree_Node* fix_node)
    {
        while((fix_node != root) && (fix_node -> color == BLACK))
        {
            if(!get_child_flag(fix_node))
            {
                RB_Tree_Node* fix_handler = fix_node -> parent -> right_child;

                if(fix_handler -> color == RED)
                {
                    fix_handler -> color = BLACK;
                    fix_node -> parent -> color = RED;
                    left_rotate(fix_node -> parent);
                    fix_handler = fix_node -> parent -> right_child;
                }

                if((fix_handler -> left_child -> color == BLACK) && (fix_handler -> right_child -> color == BLACK))
                {
                    fix_handler -> color = RED;
                    fix_node = fix_node -> parent;
                }
                else if(fix_handler -> right_child -> color == BLACK)
                {
                    fix_handler -> left_child -> color = BLACK;
                    fix_handler -> color = RED;
                    right_rotate(fix_handler);
                    fix_handler = fix_node -> parent -> right_child;
                }

                fix_handler -> color = fix_node -> parent -> color;
                fix_node -> parent -> color = BLACK;
                fix_handler -> right_child -> color = BLACK;
                left_rotate(fix_node -> parent);
                fix_node = root;
            }
            else
            {
                RB_Tree_Node* fix_handler = fix_node -> parent -> left_child;

                if(fix_handler -> color == RED)
                {
                    fix_handler -> color = BLACK;
                    fix_node -> parent -> color = RED;
                    right_rotate(fix_node -> parent);
                    fix_handler = fix_node -> parent -> left_child;
                }

                if((fix_handler -> left_child -> color == BLACK) && (fix_handler -> right_child -> color == BLACK))
                {
                    fix_handler -> color = RED;
                    fix_node = fix_node -> parent;
                }
                else if(fix_handler -> left_child -> color == BLACK)
                {
                    fix_handler -> right_child -> color = BLACK;
                    fix_handler -> color = RED;
                    left_rotate(fix_handler);
                    fix_handler = fix_node -> parent -> left_child;
                }

                fix_handler -> color = fix_node -> parent -> color;
                fix_node -> parent -> color = BLACK;
                fix_handler -> left_child -> color = BLACK;
                right_rotate(fix_node -> parent);
                fix_node = root;
            }
        }
        fix_node -> color = BLACK;
        return;
    }

    /* erase as if the tree were a BST, then fix up to balance */
    void erase_transplant(RB_Tree_Node* transplant_old, RB_Tree_Node* transplant_new)
    {
        if(transplant_old -> parent == sentinel)
        {
            root = transplant_new;
        }
        else if(!(get_child_flag(transplant_old)))
        {
            transplant_old -> parent -> left_child = transplant_new;
        }
        else
        {
            transplant_old -> parent -> right_child = transplant_new;
        }
        transplant_new -> parent = transplant_old -> parent;
        return;
    }

    int erase(int key)
    {
        RB_Tree_Node* erase_temp = root;
        while(erase_temp != sentinel)
        {
            if(erase_temp -> key == key)
            {
                break;
            }
            else if(erase_temp -> key < key)
            {
                erase_temp = erase_temp -> right_child;
            }
            else
            {
                erase_temp = erase_temp -> left_child;
            }
        }
        if(erase_temp == sentinel)
        {
            return 1;
        }

        RB_Tree_Node* erase_handler1 = erase_temp;
        RB_Tree_Node* erase_handler2 = sentinel;
        bool original_color = erase_handler1 -> color;

        if(erase_temp -> left_child == sentinel)
        {
            erase_handler2 = erase_temp -> right_child;
            erase_transplant(erase_temp, erase_temp -> right_child);
        }
        else if(erase_temp -> right_child == sentinel)
        {
            erase_handler2 = erase_temp -> left_child;
            erase_transplant(erase_temp, erase_temp -> left_child);
        }
        else
        {
            erase_handler1 = erase_temp -> right_child;
            while(erase_handler1 -> left_child != sentinel)
            {
                erase_handler1 = erase_handler1 -> left_child;
            }

            erase_handler2 = erase_handler1 -> right_child;
            if(erase_handler1 -> parent == erase_temp)
            {
                erase_handler2 -> parent = erase_handler1;
            }
            else
            {
                erase_transplant(erase_handler1, erase_handler1 -> right_child);
                erase_handler1 -> right_child = erase_temp -> right_child;
                erase_handler1 -> right_child -> parent = erase_temp;
            }

            erase_transplant(erase_temp, erase_handler1);
            erase_handler1 -> left_child = erase_temp -> left_child;
            erase_handler1 -> left_child -> parent = erase_handler1;
            erase_handler1 -> color = erase_temp -> color;
        }

        if(original_color == BLACK)
        {
            erase_fixup(erase_handler2);
        }
        return 0;
    }

    /* search as if the tree were a BST */
    int search(int key)
    {
        RB_Tree_Node* search_temp = root;

        if(root == sentinel)
        {
            return 0;
        }
        else
        {
            while(search_temp != sentinel)
            {
                if(search_temp -> key == key)
                {
                    return 1;
                }
                else if(search_temp -> key < key)
                {
                    search_temp = search_temp -> right_child;
                }
                else if(search_temp -> key > key)
                {
                    search_temp = search_temp -> left_child;
                }
            }
        }
        return 0;
    }

    /* a function to measure how balanced the tree is */
    int get_tree_height(RB_Tree_Node* root)
    {
        if(root == sentinel)
        {
            return  0;
        }
        else
        {
            int left_height = get_tree_height(root -> left_child);
            int right_height = get_tree_height(root -> right_child);
            if(left_height > right_height)
            {
                return left_height + 1;
            }
            else
            {
                return right_height + 1;
            }
        }
    }
};

#endif //RBT_RB_TREE_H
