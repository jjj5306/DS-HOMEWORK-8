/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */


#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);


int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
	printf("2020039071 JoJunHwa \n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}


/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* p;
	if (h->rlink == h) //리스트에 값이 없다면 h만 free
	{
		free(h);
		return 0;
	}
	if (h->rlink->rlink == h) // 리스트에 값이 하나이면 그 값 free
		free(h->rlink);
	else // 아니라면 차례로 free
	{
		p = h->rlink->rlink;
		while (p != h)
		{
			free(p->llink);
			p = p->rlink;
		}
		//반복문을 나왔으므로 h다음의 값 부터 마지막 값 빼고는 다 free 됨
		free(p->llink);
	}
	free(h); // 리스트의 값들을 다 free 한 후 headNode 도 free
	return 0;
}


void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	if (h->rlink == h) //빈 리스트이면 
	{
		node->key = key;
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	else
	{
		p = h->rlink;
		node->key = key;
		while (p->rlink != h)
			p = p->rlink;
		//반복문을 나왔다면 p는 리스트의 가장 마지막을 가리키고 있다
		p->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = p;
	}
	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* p;
	listNode* pre;
	if (h->rlink == h) //리스트가 비어있다면
	{
		printf("Already empty list\n");
		return 0;
	}
	else if (h->rlink->rlink == h) //리스트에 원소가 하나라면
	{
		p = h->rlink; //p는 리스트의 첫 번째 값을 가리킨다
		p->rlink = NULL;
		p->llink = NULL;
		free(p);
		h->rlink = h;
		h->llink = h;
	}
	else //리스트에 원소가 두 개 이상이라면
	{
		p = h->rlink->rlink; //p는 두 번째 값을
		pre = h->rlink; //pre는 첫 번째 값을 가리킨다
		while (p->rlink != h)
		{
			p = p->rlink;
			pre = pre->rlink;
		}
		//반복문을 나왔으므로 p는 가장 마지막을 가리키고 있다
		p->rlink = NULL;
		p->llink = NULL;
		pre->rlink = h;
		h->llink = pre;
		free(p);
	}
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (h->rlink == h) //빈 리스트이면 
	{
		node->key = key;
		node->rlink = h;
		node->llink = h;
		h->rlink = node;
		h->llink = node;
	}
	else 
	{
		node->key = key;
		node->rlink = h->rlink;
		node->llink = h;
		h->rlink->llink = node;
		h->rlink = node;
	}
	return 1;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* p = h->rlink;
	if (p == h) // 리스트가 비어있다면
	{
		printf("Already empty list\n");
		return 0;
	}
	else if (p->rlink == h) //리스트에 원소가 하나라면
	{
		p->llink = NULL;
		p->rlink = NULL;
		free(p);
		h->rlink = h;
		h->llink = h;
	}
	else //리스트에 원소가 두 개 이상이라면
	{
		h->rlink = p->rlink;
		p->rlink->llink = h;
		p->llink = NULL;
		p->rlink = NULL;
		free(p);
	}
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}


/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	node->key = key; //node에 memory allocation 후 key 값 저장
	if (h->rlink == h) //리스트에 값이 하나도 없다면
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	else if (h->rlink->rlink == h) //리스트에 값이 하나라면
	{
		if (h->rlink->key >= key) //리스트의 맨 앞에 삽입해야 한다면
		{
			node->rlink = h->rlink;
			node->llink = h;
			h->rlink->llink = node;
			h->rlink = node;
		}
		else //그 값이 key보다 작다면 그 뒤에 삽입
		{
			node->llink = h->rlink;
			node->rlink = h;
			h->rlink->rlink = node;
			h->llink = node;
		}
	}
	else //리스트에 값이 두 개 이상이라면
	{
		if (h->rlink->key >= key) //리스트의 맨 앞에 삽입해야 한다면
		{
			node->rlink = h->rlink;
			node->llink = h;
			h->rlink->llink = node;
			h->rlink = node;
		}
		else //리스트의 두 번째 이상의 자리에 삽입해야 한다면
		{
			p = h->rlink; //r은 첫 번째 원소를 가리키고 있다
			while (p->key < key && p->rlink != h) //리스트의 값이 key보다 크거나 같거나 마지막에 도달 할 때 까지 p를 이동시킴
				p = p->rlink;
			// 반복문을 나왔으므로 리스트의 끝에 도달했거나 p의 전 위치에 삽입하면 된다.
			if (p->key >= key) //삽입할 곳을 찾았다면
			{
				node->rlink = p;
				node->llink = p->llink;
				p->llink->rlink = node;
				p->llink = node;
			}
			else // 못찾았다면 끝에 삽입
			{
				p->rlink = node;
				node->llink = p;
				node->rlink = h;
				h->llink = node;
			}
		}
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	listNode* pre;
	if (h->rlink == h) //리스트가 비어있다면
		printf("Already empty list\n");
	else if (h->rlink->rlink == h) //리스트에 원소가 하나이고
	{
		if (h->rlink->key == key) //그 원소가 key와 같다면
		{
			free(h->rlink); //그 원소를 free 한다
			h->rlink = h;
			h->llink = h;
		}
		else
			printf("Not in list\n");
	}
	else //리스트에 원소가 두 개 이상이라면
	{
		if (h->rlink->key == key) //첫 번째 원소를 삭제해야 한다면
		{
			p = h->rlink->rlink;
			pre = p->llink;
			pre->llink = NULL;
			pre->rlink = NULL;
			h->rlink = p;
			p->llink = h;
			free(pre);
		}
		else
		{
			p = h->rlink->rlink;
			pre = p->llink;
			while (p->rlink != h && p->key != key) //p가 key와 같거나 p가 리스트의 끝에 도달한다면 반복문 종료
			{
				p = p->rlink;
				pre = pre->rlink;
			}
			if (p->key == key) //p가 가리키는 key가 key와 같다면 그 부분 삭제
			{
				if (p->rlink == h) //마지막 원소를 삭제해야 한다면 h의 llink와 pre의 rlink 수정해야 함
				{
					p->llink = NULL;
					p->rlink = NULL;
					pre->rlink = h;
					h->llink = pre;
					free(p);
					return 1;
				}
				else
				{
					p->rlink->llink = pre;
					pre->rlink = p->rlink;
					p->rlink = NULL;
					p->llink = NULL;
					free(p);
					return 1;
				}
			}
			else
				printf("Not in list\n"); //아니라면 리스트에 없는 것
		}
	}
	return 0;
}

