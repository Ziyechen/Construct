#pragma once

//输入某二叉树前序遍历和中序遍历的结果，清重建出该二叉树
//假设前序遍历和中序遍历的结果没有重复数字


#include <iostream>
#include <assert.h>
using namespace std;

//假如输入前序遍历{1, 2, 4, 7, 3, 5, 6, 8}，中序遍历{4, 7, 2, 1, 5, 3, 8, 6}，
//请重建出二叉树并返回头结点，二叉树结点如下:
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode *m_nLeft;
	BinaryTreeNode *m_nRight;

	BinaryTreeNode(int x)
		:m_nValue(x)
		, m_nLeft(NULL)
		, m_nRight(NULL)
	{}
};

BinaryTreeNode *_ConstructCore(int *startPrevOrder, int *endPrevOrder
	, int *startInOrder, int *endInOrder)
{
	//先序遍历的第一个数字是根节点的值
	int rootValue = startPrevOrder[0];
	BinaryTreeNode *root = new BinaryTreeNode(rootValue);

	if (startPrevOrder == endPrevOrder)
	{
		if (startInOrder == endInOrder && *startPrevOrder == *startInOrder)
			return root;
		else
			throw exception("Invalid input.");
	}

	//在中序遍历中找到根节点的值
	int *rootInOrder = startInOrder;

	while (rootInOrder <= endInOrder && *rootInOrder != rootValue)
		++rootInOrder;

	if (rootInOrder == endInOrder && *rootInOrder != rootValue)
		throw exception("Invalid input.");

	int leftSize = rootInOrder - startInOrder;
	int *leftPrevOrderEnd = startPrevOrder + leftSize;

	if (leftSize > 0)
	{
		//构建左子树
		root->m_nLeft = _ConstructCore(startPrevOrder + 1, leftPrevOrderEnd,
			startInOrder, rootInOrder - 1);
	}
	if (leftSize < endPrevOrder - startPrevOrder)
	{
		//构建右子树
		root->m_nRight = _ConstructCore(leftPrevOrderEnd + 1, endPrevOrder,
			rootInOrder + 1, endInOrder);
	}

	return root;
}

BinaryTreeNode *Construct(int *prevOrder, int *inOrder, int size)
{
	if (prevOrder == NULL || inOrder == NULL || size <= 0)
		return NULL;

	return _ConstructCore(prevOrder, prevOrder + size - 1, inOrder, inOrder + size - 1);
}

//先序遍历二叉树
void PrevOrder_Print(BinaryTreeNode *root)
{
	if (root == NULL)
		return;

	cout << root->m_nValue << " ";

	PrevOrder_Print(root->m_nLeft);
	PrevOrder_Print(root->m_nRight);
}

//测试用例
void TestConstruct()
{
	int prevOrder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	int size = sizeof(prevOrder) / sizeof(prevOrder[0]);

	BinaryTreeNode *root = Construct(prevOrder, inOrder, size);

	PrevOrder_Print(root);
	cout << endl;
}
