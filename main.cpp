#include <stdio.h>
//#ifndef APATH_H
#include "Apath.h"
#include <iostream>
#include <vector>
using namespace std;
//#endif

//Ϊ�򵥣��ɴ�Ѱ���������תΪ����ṹ������
//Լ����0�ǿ��ߵģ�1��ʾ�ϰ��ﲻ���ߣ�2��ʾ��㣬3��ʾ�յ㣬4��ʾ·��
int InputArray[10][10] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 0, 1, 0, 3, 0, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int main()
{
	vector<vector<int>> ResultPath;// �洢����·��
	int row = MAP_MAX_X, col = MAP_MAX_Y;
	//printf("hello world!\n");
	LNode **map = Translate_array(InputArray, row, col); //���ｫ����ĵ�ͼתΪ�ڵ�map�ĵ�ͼ
	output(map, 10, 10);
	LinkList open_List = InitList();     //���岢��ʼ��һ�������б�,open_ListΪLinkList��ָ�����
	LinkList close_List = InitList();    //һ������б�
	LNode* startLNode = find_start_LNode(map, row, col);
	LNode* endLNode = find_end_LNode(map, row, col);

	LNode* curLNode = startLNode;        //��ǰ�ڵ�=��ʼ�ڵ�
	curLNode->G = 0;        //����ڵ������ֵ
	count_LNode_H(curLNode, endLNode);
	count_LNode_F(curLNode);
	push_OpenList_Node(open_List, curLNode);        //�Ƚ���ʼ�ڵ���뿪���б�

	while (curLNode->data != 3)
	{
		//LNode *e = NULL;
		curLNode = pop_OpenList_minNode(open_List);
		insert_Into_CloseList(curLNode, close_List);
		//2���鿴�����Χ�ĵ��Ƿ��ڿ����б�����ڼ��룬�ڼ�⾭���õ�Fֵ�Ƿ���С�ȣ�
		check_around_curNode(curLNode, endLNode, open_List, map);
	}
	while (endLNode->path_next)
	{
		vector<int> temp;
		temp.push_back(endLNode->path_next->x);
		temp.push_back(endLNode->path_next->y);
		//printf("x:%d---y:%d\n", endLNode->path_next->x, endLNode->path_next->y);
		endLNode->path_next = endLNode->path_next->path_next;
		ResultPath.push_back(temp);
	}
	for (vector<vector<int>>::iterator it = ResultPath.end() - 1; it >= ResultPath.begin(); it--)
	{
		cout << "(" << (*it)[0]<<","<<(*it)[1] << ") --> ";
		if (it == ResultPath.begin()) { break; }
	}
	cout << "(" << endLNode->x << ","<< endLNode->y <<")" << endl;
	getchar();
	return 0;
}
