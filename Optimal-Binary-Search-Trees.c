#include <stdio.h>
#include <stdlib.h>
#define Max 15

struct nodetype {
	char data[10];
	float p;
	struct nodetype* left;
	struct nodetype* right;
} typedef nodetype;

struct nodetype* makeNode(); //node 생성함수
void inputData(); //데이터 입력
void optsearchtree(); //optimal root값 탐색
nodetype* tree(int i, int j); //tree 생성
void inorder(struct nodetype* T); //tree 출력
void preorder(struct nodetype* T); //tree의 level과 방향 출력


struct nodetype* root = NULL; //node 초기화
nodetype* key[Max];
int n; //입력받을 데이터의 수
float A[Max][Max]; //평균 탐색 횟수
int R[Max][Max]; //A[i][j]에 최적값을 넣는 순간의 k값
int level = 0; //node의 level
int tmp = 0;
int tmp2 = 0;


//node 생성 함수
struct nodetype* makeNode() {
	struct nodetype* newnode;
	newnode = (struct nodetype*)malloc(sizeof(struct nodetype));
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}


//데이터 입력받는 함수
void inputData() {
	int i, j;
	printf("데이터 갯수를 입력하세요 : ");
	scanf_s("%d", &n);
	printf("\n");

	for (i = 1; i <= n; i++) {
		key[i] = makeNode();
		printf("key%d의 데이터를 입력하세요 : ", i);
		scanf_s("%s", &key[i]->data);
		printf("key%d의 선택확률을 입력하세요 : ", i);
		scanf_s("%f", &key[i]->p);
	}
	printf("\n");
}


//평균 탐색 횟수가 최소가 되는 node 찾는 함수 
void optsearchtree() {
	int i, j, k, diagonal;
	float min;

	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = key[i]->p;
		R[i][i] = i;
		R[i][i - 1] = 0;
	}

	A[n + 1][n] = 0;
	R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) {
			float psum = 0;
			j = i + diagonal;
			for (k = i; k <= j; k++) {
				psum = psum + key[k]->p;
			}

			for (k = i; k <= j; k++) {
				min = A[i][k - 1] + A[k + 1][j] + psum;
				if (min < A[i][j]) {
					A[i][j] = min;
					R[i][j] = k;
				}
			}
		}
	}
}


//tree 생성함수
nodetype* tree(int i, int j) {
	int k;
	nodetype* p;
	k = R[i][j];

	if (k == 0)
		return NULL;
	else {
		p = key[k];
		p->left = tree(i, k - 1);
		p->right = tree(k + 1, j);
		return p;
	}
}


//tree 출력함수
void inorder(struct nodetype* T) {
	if (T != NULL) {
		inorder(T->left);
		printf("%s ", T->data);
		inorder(T->right);
	}
}


//tree의 level과 방향을 나타내는 함수
void preorder(struct nodetype* T) {
	if (T != NULL) {
		printf("%s -> ", T->data);
		printf("%d level", level);

		if (level == 0) //root
			printf("(root)");

		else if (level != 0 && tmp2 == 0) //left, right 구별
			printf("(left)");
		else if (level != 0 && tmp2 == 1)
			printf("(right)");
		printf("\n");
		level++;
		tmp2 = 0;
		preorder(T->left);
		level++;
		tmp2 = 1;
		preorder(T->right);
	}

	else {
		tmp++;
		level--;

		if (tmp == 2) {
			level--;
			tmp = 0;
		}
	}
}


int main() {
	int i, j;

	inputData(); //데이터 입력함수 호출

	for (i = 1; i <= n + 1; i++) {
		for (j = 0; j <= n; j++) {
			A[i][j] = 10;
		}
	}

	for (i = 1; i <= n; i++) { //각 key에 데이터 입력
		printf("key[%d] : ", i);
		printf("%s ", key[i]->data);
		printf("%.3f\n", key[i]->p);
	}
	printf("\n");

	optsearchtree(); //평균 탐색 횟수가 최소가 되는 node 찾는 함수 호출

	printf("<Matrix A>\n"); //모든 경우에 대한 평균 탐색횟수
	for (i = 1; i <= n + 1; i++) {
		for (j = i - 1; j <= n; j++) {
			printf("A[%d][%d] = %6.3f  ", i, j, A[i][j]);
		}
		printf("\n");
	}

	printf("\n<Matrix R>\n"); //A[i][j]에 최적값을 넣는 순간의 k값
	for (i = 1; i <= n + 1; i++) {
		for (j = i - 1; j <= n; j++) {
			printf("R[%d][%d] = %d  ", i, j, R[i][j]);
		}
		printf("\n");
	}

	printf("\n탐색시간을 최소로 하는 root node : %s\n", key[R[1][n]]->data);

	printf("\n탐색시간을 최소로 하는 Tree의 탐색 : ");
	root = tree(1, n); //tree 구성
	inorder(root); //구성된 tree 탐색
	printf("\n\n<각 노드의 level>\n");
	preorder(root); //구성된 tree의 각 node의 level과 방향 표시
	return 0;
}