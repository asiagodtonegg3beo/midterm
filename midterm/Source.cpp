#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<list>
#include<queue>

using namespace std;

/* �`�I���c */
class Node {
public:
	int data; //�`�I�v���j�p
	int index; //�`�I���X
	Node* left; //���쵲
	Node* right; //�k�쵲
};

int id = 0;
/* �`�I�غc��� */
Node* createnode(int data) { //O(1)
	Node* t = new Node();
	t->data = data;
	t->left = NULL;
	t->right = NULL;
	t->index = id;
	id++;
	return t;
}

/* ���J��ơA�H level order traversal �إ� tree */ //�ɶ�������O(n) �Ŷ�������O(n[queue q]+1[Node root])=O(n)
Node* insert(Node *root,int data) {

	/* �إ߷s���`�I */

	queue <Node* >q;
	q.push(root);

	/* �p�G��ڬO�Ū��A���w�@�ӷs�`�I��root */
	if (root == NULL) {
		root = createnode(data);
		return root;
	}

	while (!q.empty()) {
		Node* t = q.front();

		// ���`�I���šA��m�s���`�I�A�æ^����
		if (t->left == NULL) {
			t->left = createnode(data);
			return root;
		}
		else {// ���`�I�����šA���queue��
			q.push(t->left);
		}

		// �k�`�I���šA��m�s���`�I�A�æ^����
		if (t->right == NULL) {
			t->right = createnode(data);
			return root;
		}
		else { //�k�`�I�����šA���queue��
			q.push(t->right);
		}
		q.pop();
	}
	



}

/* �C�L��� */


void print(Node* root) {
	if (root == NULL)
		return;

	/* �Ntree�e�JqueueŪ�� */
	queue <Node*> q;
	q.push(root);

	/* ���->���l��->�k�l�� */
	while (!q.empty()) {
		/* �L�X�ثe���ȡA�ϥμh��(level order traversal)�覡�C�L */
		Node* t = q.front(); // ��head����
		printf("%d ", t->data);
		
		/* ���`�I������,�[�Jqueue�� */
		if (t->left != NULL) {
			q.push(t->left);
		}
		/* �k�`�I������,�[�Jqueue�� */
		if (t->right != NULL) {
			q.push(t->right);
		}
		q.pop(); // �R��head����
	}
}

int print_1(list <Node *> &path) { //O(1[sum]+1[counter]) = O(1)
	int sum = 0;
	list<Node*>::iterator i;
	int counter = 0;
	for (i = path.begin(); i != path.end(); i++)
	{
		cout << "[" << (*i)->index <<"]" ;
		
		sum += (*i)->data;
		if (counter == path.size()-1) {
			break;
		}
		counter++;
		printf("-->");

	}
	return sum;
}


void root_to_leaf_sum(Node* root, int sum,list<Node*> path, list<Node*>& result) { //�ɶ�������O(n)�A�Ŷ�������O(n+n+n+1)
	/* base case�G��ʾ𬰪� */
	if (root == NULL) {
		return;
	}
	static int max;
	path.push_back(root);
	sum += root->data;
	if (sum > max)
	{
		max = sum;
	}
	/* base case�G�p�G�����`�I(����)�A�^��data�� */
	if (root->left == NULL && root->right == NULL) {

		if (sum == max)
		{
			result = path;
		}
		return;
	}
	/* �H���j�覡�p�⥪�l���`�M*/
	root_to_leaf_sum(root->left, sum, path, result);

	/* �H���j�覡�p��k�l���`�M*/
	root_to_leaf_sum(root->right, sum, path, result);


}



/* �D�{�� */
int main() {
	Node* root = NULL;     //���
	list <Node *>result; // result�GMax-weight���G�F t�GMax-weight�Ȧs
	list <Node *>t     ; // result�GMax-weight���G�F t�GMax-weight�Ȧs
	int h;             // level
	int sum = 0;       // Max-weight�`�M
	int weight; // �ü�
	cout << "�п�J h ����: ";
	cin >> h;
	cout << endl;
	cout << "��X" << endl;

	/* �L�X�C�`�I�s���θ`�I��weight */
	for (int i = 0; i < pow(2,h+1)-1; i++) { //�ɶ�������O(n) �Ŷ�������O(n)
		weight = rand()%100;
		cout << "node[" << i << "]" << " �� weight �� " << weight << endl;
		root = insert(root, weight);
	}
	/* �p��root~leaf��weight�`�M */
	root_to_leaf_sum(root,sum,t,result);

	cout << "Max-weight path : ";
	sum = print_1(result);
	printf("\n");

	cout << "Path weight: "  <<sum<< endl;
}