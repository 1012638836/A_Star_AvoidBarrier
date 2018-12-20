#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>


#ifndef APATH_H
#define APATH_H
#endif

#define TURE 1
#define FAULT 0

//Լ����0�ǿ��ߵģ�1��ʾ�ϰ��ﲻ���ߣ�2��ʾ��㣬3��ʾ�յ㣬4��ʾ·��
#define int_0 0
#define int_1 1
#define int_2 2
#define int_3 3
#define int_4 4

#define MAP_MAX_X 10   //��ͼ�߽磬��ά�����С
#define MAP_MAX_Y 10

typedef struct LNode {
	int data;    //��Ӧ�����е���ֵ
	int F;   //F = G + H;
	int G;   //G������� A �ƶ���ָ��������ƶ����ۣ����ŵ���÷�������ɵ�·��
	int H;   //H����ָ���ķ����ƶ����յ� B �Ĺ���ɱ�
	int x, y;   //��Ӧ�����е�����
	bool OPen_flag;  //�ڿ����б���Ϊ1������Ϊ0
	bool Close_flag;  //�ڹر��б���Ϊ1������Ϊ0
	struct LNode* next;                    //������������
	struct LNode* path_next;            //���������ҵ���·��
}LNode, *LinkList;

LinkList InitList();  //����һ����ʼ��������
LNode** malloc_array2D(int row, int col);
void free_array2D(LNode **arr);
LNode** Translate_array(int array[10][10], int row, int col);    //��һ����ͨ���鷭��Ϊ������ڵ������
void output(LNode **array, int row, int col);

LNode* find_start_LNode(LNode** Arr, int row, int col);    //���������ҵ�ʼ��
LNode* find_end_LNode(LNode** Arr, int row, int col);        //���������ҵ��յ�

															 //������ЩҪ�����ˣ���д��
bool isExist_ALNode_in_List(LNode* curLNode, LinkList L_OpenList);    //�鿴�ڵ��Ƿ��������У��ڷ���ture,���ڷ���fault
																	  //�Թر��б��еĵ�ǰ�ڵ���м�飬������Χ�Ľڵ��Ƿ���OpenList���������:��ӽ�ȥ���ڣ���龭������������G�Ƿ���С���ǣ��޸ģ����ǣ����޸�
																	  //LNode* check_CloseList_curLNode(LNode* curLNode, LNode* endLNode, LinkList L_OpenList, LinkList L_CloseList, LNode** Arr);   

LNode* pop_OpenList_minNode(LinkList L_OpenList);        //���ؿ����б���Fֵ��С�Ľڵ�
void push_OpenList_Node(LinkList L, LNode *elem);   //����һ���ڵ㲢����
bool insert_Into_CloseList(LNode* min_Open, LinkList L_CloseList);//����OpenList��Fֵ��С�Ľڵ㵽CloseList��ȥ


int count_LNode_G(LNode* curLNode, LNode* aheadLNode);        //����ڵ��Gֵ
int count_LNode_H(LNode* curLNode, LNode* endLNode);        //����ڵ��Hֵ
int count_LNode_F(LNode* curLNode);        //����ڵ��Fֵ

bool isExist_openList(LNode* curLNode);    //�鿴�ڵ��Ƿ��������У��ڷ���ture,���ڷ���fault
bool isExist_closeList(LNode* curLNode);
bool isobstacle(LNode* curLNode);
void check_around_curNode(LNode* cur, LNode* endLNode, LinkList open_list, LNode** Arr);        //�����Χ�Ľڵ㣬�Ƿ���ʼ��뿪���б�

