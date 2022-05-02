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

typedef struct Node { //별명 listNode, 정수형 변수 key와 Node구조체의 포인터 llink와 rlink를 가지는 구조체 Node선언
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);  //headNode 구조체의 이중포인터 h를 변수로 하는 정수형 함수 initialize 함수 선언
int freeList(listNode* h);  //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 freeList 함수 선언
int insertLast(listNode* h, int key);//headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertLast 함수 선언
int deleteLast(listNode* h);  //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 deleteList 함수 선언
int insertFirst(listNode* h, int key);//headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertFirst 함수 선언
int deleteFirst(listNode* h);  //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 deleteFirst 함수 선언
int invertList(listNode* h); //headNode 구조체의 포인터 h를 변수로 하는 정수형 함수 invertList 함수 선언 

int insertNode(listNode* h, int key);//headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertNode 함수 선언
int deleteNode(listNode* h, int key);//headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 deleteNode 함수 선언

void printList(listNode* h);  //headNode 구조체의 포인터 h를 변수로 하는 void형 함수 PrintList 함수 선언



int main()
{
	char command; //문자형 변수 command 선언
	int key; //정수형 변수 key선언
	listNode* headnode=NULL; //listNode구조체 포인터 변수 headnode 선언 및 초기화

	do{
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
		scanf(" %c", &command); //scanf를 통해 입력받은 문자를 command에 저장

		switch(command) { //각 커맨드에 맞는 기능 실행
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

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //포인터변수 h에 값이 없으면
		freeList(*h); //포인터 변수 h에 대해 freeList 함수 실행

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //*h에 listNode구조체 크기만큼 동적 메모리 할당, 이를 위해 stdlib라이브러리 호출
	(*h)->rlink = *h; 
	(*h)->llink = *h; //*h의 좌우link에 *h값 할당
	(*h)->key = -9999; //*h의 key값에 -9999할당
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) //h의 우측link가 h라면,
	{
		free(h); //h에 할당된 메모리 해제
		return 1; 
	}

	listNode* p = h->rlink; //h의 rlink값을 p에 대입

	listNode* prev = NULL; //listNode구조체의 포인터변수 prev 초기화
	while(p != NULL && p != h) { //p에 값이 있으나 h와 값이 다를 때
		prev = p; //p값을 prev로
		p = p->rlink; //p의 rlink를 p로
		free(prev); //prev에 할당된 메모리 해제
	}
	free(h); //h에 할당된 메모리 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0; //정수형 변수 i 0으로 초기화
	listNode* p; //listNode구조체 포인터 변수 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h에 값 없으면
		printf("Nothing to print....\n"); //오류메세지 출력
		return;
	}

	p = h->rlink; //h의 rlink를 p에 할당

	while(p != NULL && p != h) { //p에 값이 있지만 h와는 다를 때
		printf("[ [%d]=%d ] ", i, p->key); //이때까지 넣었던 값들 번호와 함께 출력
		p = p->rlink; //p의 rlink를 p로
		i++; //i값은 계속 증가시켜 번호를 나타내게함
	}
	printf("  items = %d\n", i); //들어가있는 element의 수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //headnode의 좌, 우측 link와 head 주소값 출력

	i = 0; //i 초기화( 밑에서 써야함)
	p = h->rlink; //h의 rlink를 p에
	while(p != NULL && p != h) { 
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //주소값 출력
		p = p->rlink; //p의 rlink를 p에
		i++; //i값 계속 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //h에 값 없으면 오류

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 구조체 크기만큼의 동적 메모리 할당
	node->key = key; //key값을 node의 key값에
	node->rlink = NULL; 
	node->llink = NULL; //node의 좌우측link값 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */ //h의 rlink가 h와 값이 같으면
	{
		h->rlink = node; //node값을 h의 rlink, llink에 대입
		h->llink = node; 
		node->rlink = h; //h값은 node의 rlink, llink에 대입
		node->llink = h;
	} else {
		h->llink->rlink = node; //아니라면, h의 llink의 rlink에 node값 대입
		node->llink = h->llink; //h의 llink를 node의 llink에 대입
		h->llink = node; //node값을 h의 llink에 대입
		node->rlink = h; //h의 값을 node의 rlink에 할당
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //h의 llink가 h와 같거나 h에 값이 들어가 있을 때( h의 llink도 NULL이 아니어야 한다는 말?)
	{
		printf("nothing to delete.\n"); //삭제 할 것이 없다는 메세지 출력
		return 1;
	}

	listNode* nodetoremove = h->llink; //h의 llink값을 listNode구조체 포인터변수 nodetoremove에 대입

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의 llink의 rlink에 h값 대입
	h->llink = nodetoremove->llink; //nodetoremove의 llink에 h의 llink 대입

	free(nodetoremove); //nodetoremove에 할당된 메모리 반환

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //구조체 포인터변수 node에 listNode 구조체 크기만큼의 동적메모리 할당
	node->key = key; //key값을 node의 key값에, node의 rlink,llink값은 초기화
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink; //h의 rlink를 node의 rlink로
	h->rlink->llink = node; //node값은 h의 rlink의 llink로
	node->llink = h; //h의 값은 node의 llink로
	h->rlink = node;//node값은 h의 rlink로


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //h에 값이 있거나 h의 rlink가 h와 같을 때 
	{
		printf("nothing to delete.\n"); //삭제할 것이 없음
		return 0;
	}

	listNode* nodetoremove = h->rlink; //deleteLast와는 다르게 rlink값을 대입함

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink; //deleteLast와 반대로 수행
 
 	free(nodetoremove);//메모리 반환

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //역순으로 재배치할 리스트가 없을 때 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //h의 rlink를 *n에
	listNode *trail = h; //h값을 *trail과 *middle에 각각 할당
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //h의 rlink를 llink에 대입함

	while(n != NULL && n != h){ //n이NULL이 아니고, h와 같지 않을 때만 반복
		trail = middle; // middle을 trail로
		middle = n; //n은 middle로
		n = n->rlink; //n의 rlink는 n으로,
		middle->rlink = trail; //trail은 middle의 rlink로
		middle->llink = n; //n은 middle의 llink로 할당, 반복해서 위치 역순으로 변경
	}

	h->rlink = middle; //middle에는 h의 rlink값 대입함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h가 NULL이면 오류

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 크기만큼의 동적메모리 할탕
	node->key = key; //key값을 node의 key값에, node의 rlink,llink값은 초기화
	node->llink = node->rlink = NULL;

	if (h->rlink == h) //h의 rlink가 h와 같으면
	{
		insertFirst(h, key); //insertFist함수 실행
		return 1;
	}

	listNode* n = h->rlink; //h의 rlink를 listNode구조체 포인터 변수 n에 삽입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 H와 다르고, 값이 있을 때
		if(n->key >= key) { //또, n의 key값이 입력된 key보다 클 때 
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //h의 rlink가 n과 같을 때
				insertFirst(h, key); //맨 앞 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //n의 값을 node의 rlink에
				node->llink = n->llink; //n의 llink는 node의 llink에
				n->llink->rlink = node; //node값은 n의 llink의 rlink에
				n->llink = node; //또 n의 llink에 할당, ( n-> llink == n->llink->rlink)
			}
			return 0;
		}

		n = n->rlink; //n의 rlink값을 n에 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //찾지못하면 마지막에 추가, insertLast함수 실행
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) //h의 rlink가 h와 같거나 h의 값이NULL이 아닐 때
	{
		printf("nothing to delete.\n"); //삭제할게 없다
		return 0;
	}

	listNode* n = h->rlink; //h의rlink값을 구조체 n에대입

	while(n != NULL && n != h) { //n에 값이 있고, h와는 다를 시
		if(n->key == key) { //key값이 n의 key와 같을 때
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //맨앞 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 rlink를 n의 llink의rlink에,
				n->rlink->llink = n->llink; //n의 llink를 n의 rlink의 llink에
				free(n); //n 메모리 반환
			}
			return 0;
		}

		n = n->rlink; //n의 rlink값을 n에 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //오류메세지 출력과 키를 보여줌
	return 0;
}


