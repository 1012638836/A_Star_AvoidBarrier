#include "Apath.h"

LinkList InitList()
{
	LinkList L = (LinkList)malloc(sizeof(LNode));
	if (L == NULL)
	{
		printf("Defeat!");
		exit(1);
	}
	/*
		memset����ʹ�÷�����
		��L��ָ���ĳһ���ڴ��е�ÿ���ֽڵ�����ȫ������Ϊ0����Ĵ�С����
		sizeof(LNode),�������ͨ��Ϊ��������ڴ�����ʼ���������䷵��ָ��L��ָ��
	*/
	memset(L, 0, sizeof(LNode));
	return L;
}//LinkList()

LNode** malloc_array2D(int row, int col)
{
	LNode** map = (LNode**)malloc(row * sizeof(LNode*) + row*col * sizeof(LNode));
	LNode* head = (LNode*)(map + row);
	for (int i = 0; i < row; ++i)
		map[i] = head + i*col;
	return map;
}

LNode** Translate_array(int array[][10], int row, int col)
{
	LNode **map = malloc_array2D(10, 10);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			(map[i] + j)->data = array[i][j];
			(map[i] + j)->G = 0;
			(map[i] + j)->H = 0;
			(map[i] + j)->F = 0;    //(map[i] + j)->G + (map[i] + j)->H;
			(map[i] + j)->x = i;
			(map[i] + j)->y = j;
			(map[i] + j)->Close_flag = 0;
			(map[i] + j)->OPen_flag = 0;
			(map[i] + j)->next = NULL;
			(map[i] + j)->path_next = NULL;
		}
	return map;
}//Translate_array()

void free_array2D(LNode **arr)
{
	free(arr);
}

void output(LNode** array, int row, int col)  //��ά����ķ��ʱ���ָ��λ����������������ܽ���
{
	//for (int i = 0; i < row; ++i)
	//    for (int j = 0; j < col; ++j)
	//    {
	//        (array[i] + j)->F = j;
	//    }
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%d\t", (array[i] + j)->data);
		}
		printf("\n");
	}
}

LNode* find_start_LNode(LNode** Arr, int row, int col)    //���������ҵ�ʼ��
{
	LNode* start_LNode = NULL;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (2 == (Arr[i] + j)->data)
			{
				start_LNode = (Arr[i] + j);
				//���H=0,G=0,F=0
				start_LNode->G = 0;
				start_LNode->H = 0;
				start_LNode->F = 0;        //��㣬��Ĭ������ֵΪ0
				return start_LNode;        //���ؽڵ�
			}
		}
	}
	return NULL;
}
LNode* find_end_LNode(LNode** Arr, int row, int col)        //���������ҵ��յ�
{
	LNode* end_LNode = NULL;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (3 == (Arr[i] + j)->data)
			{
				end_LNode = (*(Arr + i) + j);
				end_LNode->F = 0;
				end_LNode->G = 0;
				end_LNode->H = 0;
				return end_LNode;        //���ؽڵ�
			}
		}
	}
	return NULL;
}

int count_LNode_G(LNode* curLNode, LNode* aheadLNode)        //����ڵ��Gֵ
{
	if (curLNode->x == aheadLNode->x && curLNode->y == aheadLNode->y)
		return 0;
	if (aheadLNode->x - curLNode->x != 0 && aheadLNode->y - curLNode->y != 0)
		curLNode->G = aheadLNode->G + 14;
	else
		curLNode->G = aheadLNode->G + 10;
	return curLNode->G;
}
int count_LNode_H(LNode* curLNode, LNode* endLNode)        //����ڵ��Hֵ
{
	curLNode->H = abs(endLNode->x - curLNode->x) * 10 + abs(endLNode->y - curLNode->y) * 10;
	return curLNode->H;
}
int count_LNode_F(LNode* curLNode)        //����ڵ��Fֵ
{
	curLNode->F = curLNode->G + curLNode->H;
	return curLNode->F;
}

void push_OpenList_Node(LinkList L, LNode *elem)        //����С�����˳��
{
	/*
		p��q�������ܽ᣺p��q��ʼ������ָ�������ͷ���(head)��ָ��,*q�ĳ�ԱFֵ��Զ��*elem�ĳ�ԱFֵС
		*p�ĳ�ԱFֵ��Զ��*elem�ĳ�ԱFֵ��Ҳ����˵elem�ڵ���q��pǰ���룬���Բο�141�е�142�д���
	*/
	LNode *p, *q;
	p = q = L;
	while (p->next != NULL && p->F < elem->F)
	{
		q = p;
		p = p->next;
	}
	if (p->F < elem->F) q = p;//�����̹淶�ܺã���p->next==NULLʱ��Ҳ����ָ��q�ĺ������elem�ڵ�
	elem->next = q->next;
	q->next = elem;
	//����ɹ�����������ֵOPen_flag = 1
	elem->OPen_flag = 1;
}
LNode* pop_OpenList_minNode(LinkList L_OpenList)        //���ؿ����б���Fֵ��С�Ľڵ�
{
	LNode *elem = NULL;
	if (L_OpenList->next)        //Ϊ�˰�ȫ����ֹ���ʿ�ָ��
	{
		L_OpenList->next->OPen_flag = 0;
		elem = L_OpenList->next;
		L_OpenList->next = L_OpenList->next->next;
		elem->next = NULL;
	}
	else
		printf("have a NULL point in pop_OpenList_mimNode()");
	return elem;
}
bool insert_Into_CloseList(LNode* min_Open, LinkList L_CloseList)//����OpenList��Fֵ��С�Ľڵ㵽CloseList��ȥ
{
	//����CloseList�еĽڵ㲢����Ҫ����,����ͷ�巨
	min_Open->next = L_CloseList->next;
	L_CloseList->next = min_Open;
	min_Open->Close_flag = 1;
	return TURE;
}

bool isExist_openList(LNode* curLNode)
{
	return curLNode->OPen_flag;
}
bool isExist_closeList(LNode* curLNode)
{
	return curLNode->Close_flag;
}
bool isobstacle(LNode* curLNode)
{
	if (curLNode->data == 1)
		return TURE;
	else
		return FAULT;
}
bool isJoin(LNode* cur)        //�ýڵ��Ƿ���Լ��뿪���б�
{
	if (cur->x > -1 && cur->y > -1)            //�߽���
	{
		if (!isExist_closeList(cur) && !isobstacle(cur))        //�Ȳ��ڹر��б��Ҳ�����ϰ���
		{
			return TURE;
		}
		else
			return FAULT;
	}
	return FAULT;
}
void insert_open(LNode *Node, LNode* ahead, LNode* endLNode, LinkList open_list, LNode** Arr)
{
	if (isJoin(Node))
	{
		if (isExist_openList(Node))
		{
			if (Node->x - ahead->x != 0 && Node->y - ahead->y != 0) {
				/*
				if (Node->F > (ahead->F + 14))
				{
					count_LNode_G(Node, ahead);
					count_LNode_F(Node);        //Hֵû�иı䣬���Ի���ԭ����ֵ
					Node->path_next = ahead;        //Ҳ�����ٲ���
				}
				*/
				if (Node->G >= (ahead->G + 14))
				{
					count_LNode_G(Node, ahead);
					count_LNode_F(Node);        //Hֵû�иı䣬���Ի���ԭ����ֵ
					Node->path_next = ahead;        //Ҳ�����ٲ���
				}
			}
			else {
				/*
				if (Node->F > (ahead->F + 10))
				{
					count_LNode_G(Node, ahead);
					count_LNode_F(Node);        //Hֵû�иı䣬���Ի���ԭ����ֵ
					Node->path_next = ahead;        //Ҳ�����ٲ���
				}
				*/
				if (Node->G >= (ahead->G + 10))
				{
					count_LNode_G(Node, ahead);
					count_LNode_F(Node);        //Hֵû�иı䣬���Ի���ԭ����ֵ
					Node->path_next = ahead;        //Ҳ�����ٲ���
				}
			}
		}
		else {
			count_LNode_G(Node, ahead);
			count_LNode_H(Node, endLNode);
			count_LNode_F(Node);
			Node->path_next = ahead;
			push_OpenList_Node(open_list, Node);
		}
	}
}
void check_around_curNode(LNode* cur, LNode* endLNode, LinkList open_list, LNode** Arr)
{
	/*
		����Ϊʲô����x��y�����ƣ���Ϊ��������Arr��ͨ��ָ����ʵġ���x==5,y==0ʱ��Arr[x]+y-1�ȼ���Arr[4][9]
	*/
	int x = cur->x;
	int y = cur->y;
	if (y > 0) {	//  y��Сȡ1
		insert_open(Arr[x] + y - 1, cur, endLNode, open_list, Arr);
	}
	if (y < MAP_MAX_Y - 1) {	//  y���ȡ8
		insert_open(Arr[x] + y + 1, cur, endLNode, open_list, Arr);
	}
	if (x < MAP_MAX_X - 1) {	//  x���ȡ8
		insert_open(Arr[x + 1] + y, cur, endLNode, open_list, Arr);
	}
	if (x < MAP_MAX_X - 1 && y > 0) {
		insert_open(Arr[x + 1] + y - 1, cur, endLNode, open_list, Arr);
	}
	if (x < MAP_MAX_X - 1 && y < MAP_MAX_Y - 1) {
		insert_open(Arr[x + 1] + y + 1, cur, endLNode, open_list, Arr);
	}
	if (x > 0) {
		insert_open(Arr[x - 1] + y, cur, endLNode, open_list, Arr);
	}
	if (x > 0 && y < MAP_MAX_Y - 1) {
		insert_open(Arr[x - 1] + y + 1, cur, endLNode, open_list, Arr);
	}
	if (x > 0 && y > 0) {
		insert_open(Arr[x - 1] + y - 1, cur, endLNode, open_list, Arr);
	}	
}
