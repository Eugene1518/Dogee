#pragma once
/**
 * https://www.cnblogs.com/skywang12345/p/3624291.html
 * C++ ����: �����
 *
 * @author skywang
 * @modified by Menooker
 * @date 2013/11/07
 * @modified date 2018/10/26
 */

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_ 
#include <DogeeBase.h>
#include <DogeeMacro.h>
#include <iomanip>
#include <iostream>
namespace Dogee
{
	namespace RBTreeNameSpace
	{
		enum RBTColor { RED, BLACK };
	}

	template <class T, class TV>
	class RBTNode : public DObject {
	public:
		
		DefBegin(DObject);
		Def(key, T);            // �ؼ���(��ֵ)
		Def(value, TV);
		Def(color, RBTreeNameSpace::RBTColor);    // ��ɫ
		Def(left, Ref<RBTNode>);    // ����
		Def(right, Ref<RBTNode>);    // �Һ���
		Def(parent, Ref<RBTNode>); // �����
		DefEnd();

		RBTNode(ObjectKey okey) :DObject(okey) {}
		RBTNode(ObjectKey okey, T key, TV value, RBTreeNameSpace::RBTColor c, Ref<RBTNode> p, Ref<RBTNode> l, Ref<RBTNode> r) :
			DObject(okey) {
			self->key = key;
			self->value = value;
			self->color = c;
			self->parent = p;
			self->left = l;
			self->right = r;
		}
	};

	template <class T, class TV>
	class DMap:public DObject {
	private:
		DefBegin(DObject);
		Def(mRoot, Ref<RBTNode<T, TV>>);    // �����
		
	public:
		DefEnd();
		DMap(ObjectKey okey);
		~DMap();

		// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
		Ref<RBTNode<T, TV>>  search(const T& key);

		// ������С��㣺������С���ļ�ֵ��
		Ref<RBTNode<T, TV>> minimum();
		// ��������㣺���������ļ�ֵ��
		Ref<RBTNode<T, TV>> maximum();

		// �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
		Ref<RBTNode<T, TV>>  successor(Ref<RBTNode<T, TV>> x);
		// �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
		Ref<RBTNode<T, TV>>  predecessor(Ref<RBTNode<T, TV>> x);

		// �����(keyΪ�ڵ��ֵ)���뵽�������
		void insert(T key, TV value);

		// ɾ�����(keyΪ�ڵ��ֵ)
		void remove(T key);

		// ���ٺ����
		void destroy();

		// ��ӡ�����
		void print();


		Ref<RBTNode<T, TV>> upperBound(const T& key) 
		{
			Ref<RBTNode<T, TV>> ub;
			upperBound(self->mRoot.get(), key, ub);
			return ub;
		}

		Ref<RBTNode<T, TV>> lowerBound(const T& key) 
		{
			Ref<RBTNode<T, TV>> lb;
			lowerBound(self->mRoot.get(), key, lb);
			return lb;
		}
	private:


		void upperBound(Ref<RBTNode<T, TV>>  root, const T& key, Ref<RBTNode<T, TV>>& ub) const;

		void lowerBound(Ref<RBTNode<T, TV>>  root, const T& key, Ref<RBTNode<T, TV>>& lb) const;

		// (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
		Ref<RBTNode<T, TV>>  search(Ref<RBTNode<T, TV>>  x, const T& key) const;

		// ������С��㣺����treeΪ�����ĺ��������С��㡣
		Ref<RBTNode<T, TV>>  minimum(Ref<RBTNode<T, TV>>  tree);
		// ��������㣺����treeΪ�����ĺ����������㡣
		Ref<RBTNode<T, TV>>  maximum(Ref<RBTNode<T, TV>>  tree);

		// ����
		void leftRotate(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  x);
		// ����
		void rightRotate(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  y);
		// ���뺯��
		void insertNode(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  node);
		// ������������
		void insertFixUp(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  node);
		// ɾ������
		void remove(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>> node);
		// ɾ����������
		void removeFixUp(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>> node, Ref<RBTNode<T, TV>> parent);

		// ���ٺ����
		void destroy(Ref<RBTNode<T, TV>>  tree);

		// ��ӡ�����
		void print(Ref<RBTNode<T, TV>>  tree, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RBTreeNameSpace::RED)
#define rb_is_black(r)  ((r)->color==RBTreeNameSpace::BLACK)
#define rb_set_black(r)  do { (r)->color = RBTreeNameSpace::BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RBTreeNameSpace::RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
	};

	/*
	 * ���캯��
	 */
	template <class T, class TV>
	DMap<T, TV>::DMap(ObjectKey okey) :DObject(okey)
	{
		self->mRoot = nullptr;
	}

	/*
	 * ��������
	 */
	template <class T, class TV>
	DMap<T, TV>::~DMap()
	{
		destroy();
	}

	/*
	 * (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	 */
	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::search(Ref<RBTNode<T, TV>>  x, const T& key) const
	{
		if (x == nullptr || x->key == key)
			return x;

		if (key < x->key)
			return search(x->left, key);
		else
			return search(x->right, key);
	}

	template <class T, class TV>
	void DMap<T, TV>::upperBound(Ref<RBTNode<T, TV>>  root, const T& key, Ref<RBTNode<T, TV>>& ub) const
	{
		if (root == nullptr) {
			return;
		}
		if (root->key > key) {
			ub = root;
			upperBound(root->left.get(), key, ub);
		}
		else {
			upperBound(root->right.get(), key, ub);
		}
	}

	template <class T, class TV>
	void DMap<T, TV>::lowerBound(Ref<RBTNode<T, TV>>  root, const T& key, Ref<RBTNode<T, TV>>& lb) const
	{
		if (root == nullptr) {
			return;
		}
		if (root->key >= key) {
			lb = root;
			lowerBound(root->left.get(), key, lb);
		}
		else {
			lowerBound(root->right.get(), key, lb);
		}
	}

	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::search(const T& key)
	{
		return search(self->mRoot, key);
	}

	/*
	 * ������С��㣺����treeΪ�����ĺ��������С��㡣
	 */
	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::minimum(Ref<RBTNode<T, TV>>  tree)
	{
		if (tree == nullptr)
			return nullptr;

		while (tree->left != nullptr)
			tree = tree->left;
		return tree;
	}

	template <class T, class TV>
	Ref<RBTNode<T, TV>> DMap<T, TV>::minimum()
	{
		Ref<RBTNode<T, TV>> p = minimum(self->mRoot);
		return p;
	}

	/*
	 * ��������㣺����treeΪ�����ĺ����������㡣
	 */
	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::maximum(Ref<RBTNode<T, TV>>  tree)
	{
		if (tree == nullptr)
			return nullptr;

		while (tree->right != nullptr)
			tree = tree->right;
		return tree;
	}

	template <class T, class TV>
	Ref<RBTNode<T, TV>> DMap<T, TV>::maximum()
	{
		Ref<RBTNode<T, TV>> p = maximum(self->mRoot);
		return p;
	}

	/*
	 * �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
	 */
	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::successor(Ref<RBTNode<T, TV>> x)
	{
		// ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
		if (x->right != nullptr)
			return minimum(x->right);

		// ���xû���Һ��ӡ���x���������ֿ��ܣ�
		// (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
		// (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
		Ref<RBTNode<T, TV>>  y = x->parent;
		while ((y != nullptr) && (x == y->right))
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	/*
	 * �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
	 */
	template <class T, class TV>
	Ref<RBTNode<T, TV>>  DMap<T, TV>::predecessor(Ref<RBTNode<T, TV>> x)
	{
		// ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
		if (x->left != nullptr)
			return maximum(x->left);

		// ���xû�����ӡ���x���������ֿ��ܣ�
		// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
		// (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
		Ref<RBTNode<T, TV>>  y = x->parent;
		while ((y != nullptr) && (x == y->left))
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	/*
	 * �Ժ�����Ľڵ�(x)��������ת
	 *
	 * ����ʾ��ͼ(�Խڵ�x��������)��
	 *      px                              px
	 *     /                               /
	 *    x                               y
	 *   /  \      --(����)-->           / \                #
	 *  lx   y                          x  ry
	 *     /   \                       /  \
	 *    ly   ry                     lx  ly
	 *
	 *
	 */
	template <class T, class TV>
	void DMap<T, TV>::leftRotate(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  x)
	{
		// ����x���Һ���Ϊy
		Ref<RBTNode<T, TV>> y = x->right;

		// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
		// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
		auto yv = y->left.get();
		x->right = yv;
		if (y->left != nullptr)
			y->left->parent = x;

		// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
		auto xv = x->parent.get();
		y->parent = xv;

		if (xv == nullptr)
		{
			root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
			self->mRoot = y;
		}
		else
		{
			if (xv->left == x)
				xv->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
			else
				xv->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		}

		// �� ��x�� ��Ϊ ��y�����ӡ�
		y->left = x;
		// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
		x->parent = y;
	}

	/*
	 * �Ժ�����Ľڵ�(y)��������ת
	 *
	 * ����ʾ��ͼ(�Խڵ�y��������)��
	 *            py                               py
	 *           /                                /
	 *          y                                x
	 *         /  \      --(����)-->            /  \                     #
	 *        x   ry                           lx   y
	 *       / \                                   / \                   #
	 *      lx  rx                                rx  ry
	 *
	 */
	template <class T, class TV>
	void DMap<T, TV>::rightRotate(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  y)
	{
		// ����x�ǵ�ǰ�ڵ�����ӡ�
		Ref<RBTNode<T, TV>> x = y->left;

		// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
		// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
		auto tempv = x->right.get();
		y->left = tempv;
		if (x->right != nullptr)
			x->right->parent = y;

		// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
		auto yv = y->parent.get();
		x->parent = yv;
		if (yv == nullptr)
		{
			root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
			self->mRoot = x;
		}
		else
		{
			if (y == yv->right)
				yv->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
			else
				yv->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
		}

		// �� ��y�� ��Ϊ ��x���Һ��ӡ�
		x->right = y;

		// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
		y->parent = x;
	}

	/*
	 * �����������������
	 *
	 * ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
	 * Ŀ���ǽ������������һ�ź������
	 *
	 * ����˵����
	 *     root ������ĸ�
	 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
	 */
	template <class T, class TV>
	void DMap<T, TV>::insertFixUp(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  node)
	{
		Ref<RBTNode<T, TV>> parent, gparent;

		// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
		while ((parent = rb_parent(node))!=nullptr && rb_is_red(parent))
		{
			gparent = rb_parent(parent);

			//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
			if (parent == gparent->left)
			{
				// Case 1����������ڵ��Ǻ�ɫ
				{
					Ref<RBTNode<T, TV>> uncle = gparent->right;
					if (uncle!=nullptr && rb_is_red(uncle))
					{
						rb_set_black(uncle);
						rb_set_black(parent);
						rb_set_red(gparent);
						node = gparent;
						continue;
					}
				}

				// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
				if (parent->right == node)
				{
					Ref<RBTNode<T, TV>> tmp;
					leftRotate(root, parent);
					tmp = parent;
					parent = node;
					node = tmp;
				}

				// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
				rb_set_black(parent);
				rb_set_red(gparent);
				rightRotate(root, gparent);
			}
			else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
			{
				// Case 1����������ڵ��Ǻ�ɫ
				{
					Ref<RBTNode<T, TV>> uncle = gparent->left;
					if (uncle!=nullptr && rb_is_red(uncle))
					{
						rb_set_black(uncle);
						rb_set_black(parent);
						rb_set_red(gparent);
						node = gparent;
						continue;
					}
				}

				// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
				if (parent->left == node)
				{
					Ref<RBTNode<T, TV>> tmp;
					rightRotate(root, parent);
					tmp = parent;
					parent = node;
					node = tmp;
				}

				// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
				rb_set_black(parent);
				rb_set_red(gparent);
				leftRotate(root, gparent);
			}
		}

		// �����ڵ���Ϊ��ɫ
		rb_set_black(root);
	}

	/*
	 * �������뵽�������
	 *
	 * ����˵����
	 *     root ������ĸ����
	 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
	 */
	template <class T, class TV>
	void DMap<T, TV>::insertNode(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>>  node)
	{
		Ref<RBTNode<T, TV>> y = nullptr;
		Ref<RBTNode<T, TV>> x = root;

		// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
		while (x != nullptr)
		{
			y = x;
			if (node->key < x->key)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y != nullptr)
		{
			if (node->key < y->key)
				y->left = node;
			else
				y->right = node;
		}
		else
			root = node;

		// 2. ���ýڵ����ɫΪ��ɫ
		node->color = RBTreeNameSpace::RED;

		// 3. ������������Ϊһ�Ŷ��������
		insertFixUp(root, node);
	}

	/*
	 * �����(keyΪ�ڵ��ֵ)���뵽�������
	 *
	 * ����˵����
	 *     tree ������ĸ����
	 *     key ������ļ�ֵ
	 */
	template <class T, class TV>
	void DMap<T, TV>::insert(T key, TV value)
	{
		Ref<RBTNode<T, TV>> z = nullptr;

		// ����½����ʧ�ܣ��򷵻ء�
		z = NewObj<RBTNode<T, TV>>( key, value, RBTreeNameSpace::BLACK, nullptr, nullptr, nullptr);

		Ref< RBTNode<T, TV>> outroot = self->mRoot;
		insertNode(outroot, z);
		self->mRoot = outroot;
	}

	/*
	 * �����ɾ����������
	 *
	 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
	 * Ŀ���ǽ������������һ�ź������
	 *
	 * ����˵����
	 *     root ������ĸ�
	 *     node �������Ľڵ�
	 */
	template <class T, class TV>
	void DMap<T, TV>::removeFixUp(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>> node, Ref<RBTNode<T, TV>> parent)
	{
		Ref<RBTNode<T, TV>> other;

		while ((!node || rb_is_black(node)) && node != root)
		{
			if (parent->left == node)
			{
				other = parent->right;
				if (rb_is_red(other))
				{
					// Case 1: x���ֵ�w�Ǻ�ɫ��  
					rb_set_black(other);
					rb_set_red(parent);
					leftRotate(root, parent);
					other = parent->right;
				}
				if ((!other->left || rb_is_black(other->left)) &&
					(!other->right || rb_is_black(other->right)))
				{
					// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
					rb_set_red(other);
					node = parent;
					parent = rb_parent(node);
				}
				else
				{
					if (!other->right || rb_is_black(other->right))
					{
						// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
						rb_set_black(other->left);
						rb_set_red(other);
						rightRotate(root, other);
						other = parent->right;
					}
					// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
					rb_set_color(other, rb_color(parent));
					rb_set_black(parent);
					rb_set_black(other->right);
					leftRotate(root, parent);
					node = root;
					break;
				}
			}
			else
			{
				other = parent->left;
				if (rb_is_red(other))
				{
					// Case 1: x���ֵ�w�Ǻ�ɫ��  
					rb_set_black(other);
					rb_set_red(parent);
					rightRotate(root, parent);
					other = parent->left;
				}
				if ((!other->left || rb_is_black(other->left)) &&
					(!other->right || rb_is_black(other->right)))
				{
					// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
					rb_set_red(other);
					node = parent;
					parent = rb_parent(node);
				}
				else
				{
					if (!other->left || rb_is_black(other->left))
					{
						// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
						rb_set_black(other->right);
						rb_set_red(other);
						leftRotate(root, other);
						other = parent->left;
					}
					// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
					rb_set_color(other, rb_color(parent));
					rb_set_black(parent);
					rb_set_black(other->left);
					rightRotate(root, parent);
					node = root;
					break;
				}
			}
		}
		if (node)
			rb_set_black(node);
	}

	/*
	 * ɾ�����(node)�������ر�ɾ���Ľ��
	 *
	 * ����˵����
	 *     root ������ĸ����
	 *     node ɾ���Ľ��
	 */
	template <class T, class TV>
	void DMap<T, TV>::remove(Ref<RBTNode<T, TV>>  &root, Ref<RBTNode<T, TV>> node)
	{
		Ref<RBTNode<T, TV>> child, *parent;
		RBTreeNameSpace::RBTColor color;

		// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
		if ((node->left != nullptr) && (node->right != nullptr))
		{
			// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
			// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
			Ref<RBTNode<T, TV>> replace = node;

			// ��ȡ��̽ڵ�
			replace = replace->right;
			while (replace->left != nullptr)
				replace = replace->left;

			// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
			if (rb_parent(node))
			{
				if (rb_parent(node)->left == node)
					rb_parent(node)->left = replace;
				else
					rb_parent(node)->right = replace;
			}
			else
				// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
				root = replace;

			// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
			// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
			child = replace->right;
			parent = rb_parent(replace);
			// ����"ȡ���ڵ�"����ɫ
			color = rb_color(replace);

			// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
			if (parent == node)
			{
				parent = replace;
			}
			else
			{
				// child��Ϊ��
				if (child)
					rb_set_parent(child, parent);
				parent->left = child;

				replace->right = node->right;
				rb_set_parent(node->right, replace);
			}

			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;

			if (color == RBTreeNameSpace::BLACK)
				removeFixUp(root, child, parent);

			delete node;
			return;
		}

		if (node->left != nullptr)
			child = node->left;
		else
			child = node->right;

		parent = node->parent;
		// ����"ȡ���ڵ�"����ɫ
		color = node->color;

		if (child)
			child->parent = parent;

		// "node�ڵ�"���Ǹ��ڵ�
		if (parent)
		{
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			root = child;

		if (color == RBTreeNameSpace::BLACK)
			removeFixUp(root, child, parent);
		delete node;
	}

	/*
	 * ɾ��������м�ֵΪkey�Ľڵ�
	 *
	 * ����˵����
	 *     tree ������ĸ����
	 */
	template <class T, class TV>
	void DMap<T, TV>::remove(T key)
	{
		Ref<RBTNode<T, TV>> node;

		// ����key��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
		if ((node = search(self->mRoot, key)) != nullptr)
			remove(self->mRoot, node);
	}

	/*
	 * ���ٺ����
	 */
	template <class T, class TV>
	void DMap<T, TV>::destroy(Ref<RBTNode<T, TV>>  tree)
	{
		if (tree == nullptr)
			return;

		if (tree->left != nullptr)
			return destroy(tree->left);
		if (tree->right != nullptr)
			return destroy(tree->right);

		DelObj(tree);
	}

	template <class T, class TV>
	void DMap<T, TV>::destroy()
	{
		destroy(self->mRoot.get());
	}

	/*
	 * ��ӡ"���������"
	 *
	 * key        -- �ڵ�ļ�ֵ
	 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
	 *               -1����ʾ�ýڵ������ĸ���������;
	 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
	 */
	template <class T, class TV>
	void DMap<T, TV>::print(Ref<RBTNode<T, TV>>  tree, T key, int direction)
	{
		if (tree != nullptr)
		{
			if (direction == 0)    // tree�Ǹ��ڵ�
				std::cout << std::setw(2) << tree->key.get() << "(B) is root" << std::endl;
			else                // tree�Ƿ�֧�ڵ�
				std::cout << std::setw(2) << tree->key.get() << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << std::setw(2) << key << "'s " << std::setw(12) << (direction == 1 ? "right child" : "left child") << std::endl;

			print(tree->left, tree->key, -1);
			print(tree->right, tree->key, 1);
		}
	}

	template <class T, class TV>
	void DMap<T, TV>::print()
	{
		if (self->mRoot != nullptr)
			print(self->mRoot, self->mRoot->key, 0);
	}
}
#endif