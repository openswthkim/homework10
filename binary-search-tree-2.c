/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 구조체 node 생성
	int key; // 정수형 변수 선언
	struct node *left; // 구조체 포인터 left 선언
	struct node *right; // 구조체 포인터 right 선언
} Node;

/* for stack */
#define MAX_STACK_SIZE 		20 // 스택 사이즈를 20으로 고정
Node* stack[MAX_STACK_SIZE]; // 크기가 MAX_STACK_SIZE인 스택 생성
int top = -1; // 스택 초기화

Node* pop(); // 스택 삭제 함수
void push(Node* aNode); // 스택 삽입 함수

/* for queue */
#define MAX_QUEUE_SIZE		20 // 큐 사이즈를 20으로 고정
Node* queue[MAX_QUEUE_SIZE]; // 크기가 MAX_QUEUE_SIZE인 큐 생성
int front = -1; 
int rear = -1; // 큐 초기화

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */
void printStack();

int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	Node* head = NULL;
        printf("[----- [Taehyung Kim] [2020039024] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // z를 입력 받은 경우
			initializeBST(&head); // initializeBST 함수 호출
			break;
		case 'q': case 'Q': // q를 입력 받은 경우
			freeBST(head); // freeBST 함수 호출
			break; 
		case 'i': case 'I': // i를 입력 받은 경우
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력 받음
			insert(head, key); // insert함수 호출
			break;
		case 'd': case 'D': // d를 입력 받은 경우
			printf("Your Key = "); 
			scanf("%d", &key); // key값 입력 받음
			deleteNode(head, key); // deleteNode함수 호출
			break;

		case 'r': case 'R': // r을 입력 받은 경우
			recursiveInorder(head->left); // 재귀적 중위 순회
			break;
		case 't': case 'T': // t를 입력 받은 경우
			iterativeInorder(head->left); // 반복적 중위 순회
			break;

		case 'l': case 'L': // l을 입력 받은 경우
			levelOrder(head->left); // 레벨 순서 순회
			break;

		case 'p': case 'P': // p를 입력 받은 경우
			printStack(); // 스택 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // Node의 크기만큼 포인터 h에 메모리 할당
	(*h)->left = NULL;	/* root */ // 포인터 h의 left에 NULL 저장
	(*h)->right = *h; // 포인터 h의 right에 포인터 h 저장
	(*h)->key = -9999; // 포인터 h의 key에 -9999 저장

	top = -1; // 스택 초기화

	front = rear = -1; // 큐 초기화

	return 1;
}



void recursiveInorder(Node* ptr) // 재귀적 중위 순회
{
	if(ptr) {
		recursiveInorder(ptr->left); // ptr의 left 재귀적 중위 순회
		printf(" [%d] ", ptr->key); // ptr의 key 출력
		recursiveInorder(ptr->right); // ptr의 right 재귀적 중위 순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // 반복적 중위 순회
{
	for(;;)
	{
		for(; node; node = node->left) // node의 left노드 만큼 반복
			push(node); // node 삽입
		node = pop(); // node 삭제

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right; // node에 node의 right 저장 
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨 순서 순회
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); // 큐에 삽입

	for(;;)
	{
		ptr = deQueue(); // 큐에서 삭제
		if(ptr) {
			printf(" [%d] ", ptr->key); // ptr의 key 출력

			if(ptr->left) // ptr의 left노드가 존재하면
				enQueue(ptr->left); // ptr의 left노드를 큐에 삽입
			if(ptr->right) // ptr의 right노드가 존재하면
				enQueue(ptr->right); // ptr의 right노드를 큐에 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Node의 크기만큼 newNode 포인터에 메모리 할당
	newNode->key = key; // newNode의 key에 key 저장
	newNode->left = NULL; // newNode의 left에 NULL 저장
	newNode->right = NULL; // newNode의 right에 NULL 저장

	if (head->left == NULL) { // head의 left가 NULL이면
		head->left = newNode; // head의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // 포인터 ptr에 head의 left 저장

	Node* parentNode = NULL; // 포인터 parentNode에 NULL 저장
	while(ptr != NULL) { // ptr이 NULL이 아닐 동안 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr의 key가 key값 보다 작으면
			ptr = ptr->right; // ptr에 ptr의 right 저장
		else
			ptr = ptr->left; // ptr에 ptr의 left 저장
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // parentNode의 key가 key보다 크면
		parentNode->left = newNode; // parentNode의 left에 newNode 대입
	else
		parentNode->right = newNode; // parentNode의 right에 newNode 대입
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { // head가 NULL이면
		printf("\n Nothing to delete!!\n"); // 출력
		return -1;
	}

	if (head->left == NULL) { // head의 left가 NULL이면
		printf("\n Nothing to delete!!\n"); // 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; // 포인터 root에 head의 left 저장



	Node* parent = NULL; // 포인터 parent를 NULL로 초기화
	Node* ptr = root; // 포인터 ptr에 root 저장

	while((ptr != NULL)&&(ptr->key != key)) { // ptr이 NULL이 아니고 ptr의 key가 입력받은 key가 아닐 동안 반복
		if(ptr->key != key) { // ptr의 key가 입력받은 key가 아니면

			parent = ptr;	/* save the parent */

			if(ptr->key > key) // ptr의 key가 입력받은 key보다 크면
				ptr = ptr->left; // ptr에 ptr의 left 저장
			else 
				ptr = ptr->right; // ptr에 ptr의 right 저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key); // 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) // ptr의 left가 NULL이면서 ptr의 right가 NULL일 때
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) // parent의 left가 ptr일 때
				parent->left = NULL; // parent의 left에 NULL 저장
			else
				parent->right = NULL; // parent의 right에 NULL 저장
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // head의 left에 NULL 저장

		}

		free(ptr); // ptr 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // ptr의 left가 NULL이거나 ptr의 right가 NULL일 때
	{
		Node* child; // Node의 포인터 child 선언
		if (ptr->left != NULL) // ptr의 left가 NULL이 아니면
			child = ptr->left; // child에 ptr의 left 저장
		else
			child = ptr->right; // child에 ptr의 right 저장

		if(parent != NULL) // parent가 NULL이 아니면
		{
			if(parent->left == ptr) // parent의 left가 ptr 이라면
				parent->left = child; // parent의 left에 child 저장
			else
				parent->right = child; // parent의 right에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root에 child 저장
		}

		free(ptr); // ptr에 할당된 메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; // Node 포인터 candidate 선언
	parent = ptr; // parent에 ptr 저장


	candidate = ptr->right; // candidate에 ptr의 right 저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // candidate의 left가 NULL이 아닐 동안 반복
	{
		parent = candidate; // parent에 candidate 저장
		candidate = candidate->left; // candidate에 candidate의 left 저장
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // parent의 right가 candidate랑 같으면
		parent->right = candidate->right; // parent의 right에 candidate의 right 저장
	else
		parent->left = candidate->right; // parent의 left에 candidate의 right 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ptr의 key에 candidate의 key 저장

	free(candidate); // candidate에 할당된 메모리 해제
	return 1;
}


void freeNode(Node* ptr) // 노드 메모리 해제
{
	if(ptr) { // ptr이 NULL이 아니면
		freeNode(ptr->left); // ptr의 left 노드 메모리 해제
		freeNode(ptr->right); // ptr의 right 노드 메모리 해제
		free(ptr); // ptr 해제
	}
}

int freeBST(Node* head) // 트리 메모리 해제
{

	if(head->left == head) // head의 left가 head라면
	{
		free(head); // head 노드 해제
		return 1;
	}

	Node* p = head->left; // 포인터 p에 head의 left 저장

	freeNode(p); // p의 노드 해제

	free(head); // head 노드 해제
	return 1;
}



Node* pop() // 스택에서 삭제
{
	if (top < 0) return NULL; // top이 0보다 작으면 NULL 리턴
	return stack[top--]; // stack[top]을 반환하고 1 감소
}

void push(Node* aNode) // 스택에 노드 추가
{
	stack[++top] = aNode; // top을 1 증가시키고 aNode를 할당
}


void printStack() // 스택 출력
{
	int i = 0; // 정수형 변수 선언
	printf("--- stack ---\n");
	while(i <= top) // i가 top보다 작거나 같을 동안 반복
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); // stack[i]->key 출력
	}
}


Node* deQueue() // 노드 삭제하는 함수
{
	if (front == rear) { // front와 rear가 같으면
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; // // NULL 반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front를 다음 위치로 이동
	return queue[front]; // queue의 front 리턴

}

void enQueue(Node* aNode) // 노드 추가하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear를 다음 위치로 이동
	if (front == rear) { // front와 rear가 같으면
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // queue[rear]에 aNode 저장
}