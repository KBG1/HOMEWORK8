/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //별칭 listNode, 정수형 변수 key와 Node구조체의 포인터 llink와 rlink를 가지는 구조체 Node선언
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { //별칭 headNode, Node구조체의 포인터 first를 변수로 가지는 구조체 Head 선언
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); //headNode 구조체의 이중 포인터 h를 변수로 하는 정수형 함수 initialize 함수 선언

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 freeList 선언

int insertNode(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertNode 함수 선언
int insertLast(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertLast 함수 선언
int insertFirst(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertFirst 함수 선언
int deleteNode(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 deleteNode 함수 선언
int deleteLast(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 deleteLast 함수 선언
int deleteFirst(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 deleteFirst 함수 선언
int invertList(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 invertList 함수 선언
 
void printList(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 void형 printList 함수 선언


int main()
{
	char command; //문자형 변수 command, 기능 입력에 사용
	int key; //정수형 변수 key 선언
	headNode* headnode=NULL; //headnode를 NULL로 초기화

	do{
		printf("---------------2019062022---------------Kim Beom Gyu------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //원하는 기능 입력

		switch(command) {  //각 키에 맞는 기능 실현
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

	}while(command != 'q' && command != 'Q'); //q나 Q가 나오면 시스템 종료

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) // 포인터 변수 h가 NULL이 아니면 
		freeList(*h); //freeList함수 실행

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //포인터변수 h에 headNode의 크기만큼의 동적메모리 할당
	(*h)->first = NULL; //포인터 변수h의 first에 NULL 대입
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //h의 first를 listNode구조체 포인터변수 p에 대입

	listNode* prev = NULL; //listNode구조체 prev에 NULL 대입
	while(p != NULL) { //p가 NULL이 아니라면
		prev = p; //p값을 prev로 
		p = p->rlink; //p의 rlink를 p로
		free(prev); //prev에 할당된 메모리 반환
	}
	free(h); //h에 할당된 메모리 반환
	return 0;
}


void printList(headNode* h) {
	int i = 0; //정수형 변수 i 0으로 초기화
	listNode* p; //listNode구조체 포인터 변수 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL이면
		printf("Nothing to print....\n");  //출력할게 없다
		return;
	}

	p = h->first; //h의 first를 p에 대입

	while(p != NULL) { //p가 NULL이 아니면
		printf("[ [%d]=%d ] ", i, p->key);  //i의 값과 p의 key값 출력
		p = p->rlink; //p의 rlink를 p에 대입
		i++; //i값 1 증가(아이템 수 증가)
	}

	printf("  items = %d\n", i); //현재 들어가있는 item의 갯수 i 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 구조체 포인터변수 node에 listNode 크기만큼의 동적메모리 할당
	node->key = key; //key값을 node의 key값에
	node->rlink = NULL; // node의 rlink,
	node->llink = NULL; //llink값에 NULL값 대입

	if (h->first == NULL) //h의 first가 NULL이면
	{
		h->first = node; //node값을 h의 first에 대입
		return 0; 
	}

	listNode* n = h->first; //listNode 구조체 포인터 변수 n에 h의 first값 대입
	while(n->rlink != NULL) { //n의 rlink가 NULL이 아니면
		n = n->rlink; //n의 rlink의 값을 n에 대입
	}
	n->rlink = node; //n의 rlink에 node 값 대입
	node->llink = n; //n의 값을 node의 llink에 대입
	return 0; 
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
 
	if (h->first == NULL) //h의 first가 NULL이면
	{
		printf("nothing to delete.\n");  //삭제할게 없습니다.
		return 0;
	}

	listNode* n = h->first; //h의 first값을 listNode 구조체 포인터 변수 n의 값에 대입
	listNode* trail = NULL; //listNode구조체 포인터 변수 trail 값 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { //n의 rlink가 NULL인경우
		h->first = NULL; //h의 first값 초기화
		free(n); //n 메모리 반환
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { //n의 rlink가 NULL이 아니면
		trail = n; //n의 값을 trail로
 		n = n->rlink; //n의 rlink값을 n으로 
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail의 rlink값 초기화
	free(n); //n의 메모리 반환

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 포인터변수 node에 listNode크기만큼의 동적 메모리 할당
	node->key = key; //key값을 node의 key값에
	node->rlink = node->llink = NULL; //node의 rlink,llink초기화

	if(h->first == NULL) //h의 first가 NULL이면
	{
		h->first = node; //node 값을 h의 first에 대입
		return 1;
	}

	node->rlink = h->first; //h의 first값을 node의 rlink에 
	node->llink = NULL; //node의 llink값을 초기화

	listNode *p = h->first; //h의 first값을 listNode 구조체 포인터 변수 p에 대입
	p->llink = node; //node값을 p의 llink에 
	h->first = node; //node값을 h의 first에 대입

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이면
	{
		printf("nothing to delete.\n"); //삭제불가
		return 0;
	}
	listNode* n = h->first; //h의 first를 listNode구조체 포인터변수 n에 대입
	h->first = n->rlink; //n의 rlink값을 h의 first에 대입

	free(n); //n 메모리 반환

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //h의 first값이 NULL이면
		printf("nothing to invert...\n"); //뒤집을 것이 없다
		return 0;
	}
	listNode *n = h->first; //listNode 구조체 포인터변수 n에 h의 first값을
	listNode *trail = NULL; //listNode 구조체 포인터변수 trail 값 초기화 
	listNode *middle = NULL;//listNode 구조체 포인터변수 middle값 초기화

	while(n != NULL){ //n에 값이 있다면
		trail = middle; //middle을 trail로
		middle = n; //n값을 middle로
 		n = n->rlink; //n의 rlink를 n에
		middle->rlink = trail; //trail값은 middle의 rlink에
		middle->llink = n; //n값을 middle의 llink에 대입
	}

	h->first = middle; //middle값을 h의 first에 대입

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체의 변수 node에 listNode크기만큼의 동적 메모리 할당
	node->key = key; //key값을 node의 key값에 대입
	node->llink = node->rlink = NULL; //node의 rlink와 llink 초기화

	if (h->first == NULL) //h의 first에 값이 없으면
	{
		h->first = node; //node값을 대입
		return 0;
	}

	listNode* n = h->first; //listNode구조체 변수 n에 h의 first값 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n에 값이 있으면 반복
		if(n->key >= key) { //key값이 n의 key값보다 작거나 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 h의 first값과 같으면
				insertFirst(h, key); //키를 맨 앞에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //n의 값을 node의 rlink로
				node->llink = n->llink; //n의 llink값을 node의 llink로
				n->llink->rlink = node; //n의 llink의 rlink값에 node 대입
			}
			return 0;
		}

		n = n->rlink; //n의 rlink값을 n에 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //못찾은경우, 뒤에 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 first에 값 없으면
	{
		printf("nothing to delete.\n"); //삭제 못함
		return 1;
	}

	listNode* n = h->first; //h의 first값을 listNode구조체 변수 n에 대입

	while(n != NULL) { //n에 값이 있다면
		if(n->key == key) { //n의 key값이 key값과 동일하다면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //h의 first 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //h의 last 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 rlink값을 n의 llink의 rlink에
				n->rlink->llink = n->llink; //n의 llink값을 n의 rlink의 llink값에 대입
				free(n); //메모리 반환
			}
			return 1;
		}

		n = n->rlink; //n의 rlink값을 n으로
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //찾지못하면, 입력된 키와 함께 오류메세지 출력
	return 1;
}


