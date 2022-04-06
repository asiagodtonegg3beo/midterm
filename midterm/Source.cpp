#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<list>
#include<queue>

using namespace std;

/* 節點結構 */
class Node {
public:
	int data; //節點權重大小
	int index; //節點號碼
	Node* left; //左鏈結
	Node* right; //右鏈結
};

int id = 0;
/* 節點建構函數 */
Node* createnode(int data) { //O(1)
	Node* t = new Node();
	t->data = data;
	t->left = NULL;
	t->right = NULL;
	t->index = id;
	id++;
	return t;
}

/* 插入函數，以 level order traversal 建立 tree */ //時間複雜度O(n) 空間複雜度O(n[queue q]+1[Node root])=O(n)
Node* insert(Node *root,int data) {

	/* 建立新的節點 */

	queue <Node* >q;
	q.push(root);

	/* 如果樹根是空的，給定一個新節點給root */
	if (root == NULL) {
		root = createnode(data);
		return root;
	}

	while (!q.empty()) {
		Node* t = q.front();

		// 左節點為空，放置新的節點，並回到樹根
		if (t->left == NULL) {
			t->left = createnode(data);
			return root;
		}
		else {// 左節點不為空，放到queue裡
			q.push(t->left);
		}

		// 右節點為空，放置新的節點，並回到樹根
		if (t->right == NULL) {
			t->right = createnode(data);
			return root;
		}
		else { //右節點不為空，放到queue裡
			q.push(t->right);
		}
		q.pop();
	}
	



}

/* 列印函數 */


void print(Node* root) {
	if (root == NULL)
		return;

	/* 將tree送入queue讀取 */
	queue <Node*> q;
	q.push(root);

	/* 樹根->左子樹->右子樹 */
	while (!q.empty()) {
		/* 印出目前的值，使用層序(level order traversal)方式列印 */
		Node* t = q.front(); // 取head的值
		printf("%d ", t->data);
		
		/* 左節點不為空,加入queue裡 */
		if (t->left != NULL) {
			q.push(t->left);
		}
		/* 右節點不為空,加入queue裡 */
		if (t->right != NULL) {
			q.push(t->right);
		}
		q.pop(); // 刪除head的值
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


void root_to_leaf_sum(Node* root, int sum,list<Node*> path, list<Node*>& result) { //時間複雜度O(n)，空間複雜度O(n+n+n+1)
	/* base case：整棵樹為空 */
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
	/* base case：如果為葉節點(末端)，回傳data值 */
	if (root->left == NULL && root->right == NULL) {

		if (sum == max)
		{
			result = path;
		}
		return;
	}
	/* 以遞迴方式計算左子樹總和*/
	root_to_leaf_sum(root->left, sum, path, result);

	/* 以遞迴方式計算右子樹總和*/
	root_to_leaf_sum(root->right, sum, path, result);


}



/* 主程式 */
int main() {
	Node* root = NULL;     //樹根
	list <Node *>result; // result：Max-weight結果； t：Max-weight暫存
	list <Node *>t     ; // result：Max-weight結果； t：Max-weight暫存
	int h;             // level
	int sum = 0;       // Max-weight總和
	int weight; // 亂數
	cout << "請輸入 h 的值: ";
	cin >> h;
	cout << endl;
	cout << "輸出" << endl;

	/* 印出每節點編號及節點的weight */
	for (int i = 0; i < pow(2,h+1)-1; i++) { //時間複雜度O(n) 空間複雜度O(n)
		weight = rand()%100;
		cout << "node[" << i << "]" << " 的 weight 為 " << weight << endl;
		root = insert(root, weight);
	}
	/* 計算root~leaf的weight總和 */
	root_to_leaf_sum(root,sum,t,result);

	cout << "Max-weight path : ";
	sum = print_1(result);
	printf("\n");

	cout << "Path weight: "  <<sum<< endl;
}