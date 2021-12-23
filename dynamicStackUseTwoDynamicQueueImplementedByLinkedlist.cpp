/*program for using two dynamic queues to serve as dynamic stack.
* team members:
* 1 ahmed adel ahmed elrefae. (security)
* 2 ahmed taher salah.		  (security)
* 3 asmaa alaa abdelmohsen.   (security)
* 4 khaled waleed kamal.	  (security)
* 5 ahmed elmetwally elzeky.  (security)
* 6 mohammad khaled omara.	  (networking)
*/
#include <iostream>
#include <conio.h>

using namespace std;

/*the struct of each created node in the list.*/
struct Node {
	/*any node conatians two main things.*/
	/*first
	the information or the data.*/
	/*which is int here.*/
	int item;
	/*second
	is the pointer to the next node.*/
	Node* next;
	/*the constructor of the node*/
	Node(int item) {
		this->item = item;//taking the data to assign it.
		this->next = NULL;//making its pointer not to point any thing.
	}//end constructor
	/*the destructor of the node*/
	~Node() {
		next = NULL;//making its pointer not to point any thing after deleting it.
	}//end destructor
};//end struct
/*the class of the dynamic queue
used to serve for stack (Last in First out)*/
/*we combined the class of stack and the class of queue in one class*/
class DynamicQueue {
	/*we used only one class containing functions of the dynamic queue and
	functions of the dynamic stack using dynamic queues*/
	////////////////////////////
	//first, the private members for the queue.
	/*the two pointers of the queue one pointing at the first node
	and the other one is pointing at the last node.*/
	Node* front, * rear;
	//you can change it to public to use both stack and queue functions in different objects
private:
	/*queue insert rear function to add node in the queue
	return nothing
	parameters int for the data in node
	*/
	void insertRear(int item) {
		//steps for creating node.
		// 1- create new node and sending data to constractor.
		Node* newNode = new Node(item);
		// 2- check if new node is created or not.
		if (newNode == NULL) {
			cout << "error no space in memory\n";
			return;
		}//end if
		// 3- check if linked list is empty or not as it is the first node.
		if (rear == NULL) {
			front = rear = newNode;
			return;
		}//end if
		// 4- making the pointer of last node to point to the added node.
		rear->next = newNode;
		// 5- moving the queue rear pointer to last node.
		rear = newNode;
	}// end insertRear
	/*queue remove front function to remove node in the queue
	return int the data type
	parameters nothing*/
	int removeFront() {
		//steps for deleting node and returning data in it.
		//1- check if queue is empty.
		if (front == NULL) {
			cout << "stack is empty \n";
			//we returned a value to not use exit(0).
			return -912390898;//a value to know that the queue is empty.
		}//end if
		//2- create temp node to point at the next node after the node to be deleted.
		Node* temp = front->next;
		//3- take the data from the node before deleting it.
		int data = front->item;
		//4- delete the first node.
		delete front;
		//5- making the queue front pointer point at the second node again.
		front = temp;
		//checking if it was the last node.
		if (front == NULL) {
			rear = NULL;//making the queue empty.
		}
		//6- returning the data.
		return data;
	}//end removeFront
	/*queue get front function to see the data in the first node
	return int the data type
	parameters nothing*/
	int getFront() {
		//steps to get first node data.
		//1- check if the queue is empty.
		if (front == NULL) {
			cout << "stack is empty \n";
			//we returned a value to not use exit(0).
			return -912390898;//a value to know that the queue is empty.
		}//end if
		//2- return the data in first node.
		return front->item;
	}//end getFront
	/*queue display function to print all data in the nodes in the queue
	return nothig
	parameters nothing
	*/
	void displayQueue() {
		//steps to print all data in queue.
		//1- check if queue is empty.
		if (front == NULL) {
			cout << "stack is empty " << endl;
			return;
		}//end if
		//2- create temp node = to front to not change the front pointer.
		Node* temp = front;
		//3- print all values till reach the last node.
		while (temp != NULL) {
			cout << temp->item << " ";//print
			temp = temp->next;//update temp to next node.
		} // end while
	}//end displayQueue
	//end of private members in the class.
public:// second, the public members for the stack.
	//constructor of the class.
	DynamicQueue() {
		front = rear = NULL;//making pointers not to point at any thing.
	}//end constructor
	//destructor of the class.
	~DynamicQueue() {
		//steps to delete all pointers of all nodes and make them point at nothing.
		//1- create temp node.
		Node* temp = NULL;
		//2- loop to delete each node next pointer.
		while (front != NULL) {
			temp = front->next;//catching next node before deleting the front.
			delete front;//deleting the front.
			front = temp;//the update of the loop.
		}//end while
		front = temp = rear = NULL;//making all pointers point to nothing.
	}//end destructor
	/*stack push function to push data to the primary queue
	return nothing
	parameters int data to be sent to insertFront function*/
	void push(int item) {
		/*there are two ideas to push the items in the first node so that pop it and
		display it easly*/
		DynamicQueue q2;//create temp queue 
		q2.insertRear(item);//creating node in the temp queue and sending data to it
		/*
		//idea 1 (slower than idea 2) (big(O) = n)
		//inserting all nodes from primary queue to temp queue after adding
		//the node to be pushed in the temp queue then swap them.
		Node* temp = front;
		while (temp != NULL) {
			q2.insertRear(temp->item);
			temp = temp->next;
			delete front;
			front = temp;
		}
		//swaping the two queues.
		front = q2.front;
		//making front of temp queue not to point to the list to not delete the list.
		q2.front = NULL;
		*/
		//idea 2 (faster than idea 1) (big(O)=1)
		//just merge the temp queue to primary queue after adding push node to temp queue 
		//then swape them.
		q2.front->next = front;//merging the two queues.
		//swaping the two queues.
		front = q2.front;
		//making front of temp queue not to point to the list to not delete the list.
		q2.front = NULL;
	}//end push
	/*stack peak function to see the what is in top
	return int the data type
	parameters nothing*/
	int peak() {
		//return the value int front of the queue
		return getFront();//call getFront of the queue.
	}//end peak
	/*stack pop function to get then delete the top data
	return int the data type
	parameters nothing*/
	int pop() {
		//return the value int front of the queue
		return removeFront();//call removeFront of the queue.
	}//end pop
	/*stack print function to display all data in queue but in First in Last out
	return nothing
	parameter nothing*/
	void print() {
		/*the data in the queue list are already arranged in stack order
		as we used push function change technique*/
		cout << "the elements in the stack are: ";
		displayQueue();//simply call the displayQueue function of the queue members.
	}//end print
};//end class DynamicQueue
//---------------------------------------------------
//main function
int main() {
	DynamicQueue stack;//creating the primary queue to use it as stack.
	char selectionInput;//char for the selection from menu to switch.
	int valuePush;//the variable to save the entered value to be pushed to stack.
	//the menu cout.
	cout << "program for using two dynamic queues to serve as dynamic stack.\n";
	cout << "Choose \n";
	cout << "1- to push.\n2- to pop.\n3- to print.\n4- to peak.\n5- to exit.\n";
	selectionInput = _getch();//taking the choosed from menu.
	do {
		//switch to select as what the user want to do.
		switch (selectionInput) {
		case '1'://push selection
		{
			cout << "\npush selected\n";
			cout << "enter the value to push: ";
			cin >> valuePush;
			stack.push(valuePush);//push value to stack.
		}//end case '1'
		break;
		case '2'://pop selection
		{
			cout << "\npop selected\n";
			if (stack.peak() != -912390898)//check if empty.
				cout << "the poped value is: " << stack.pop();
		}//end case '2'
		break;
		case '3'://print selection
		{
			cout << "\nprint selected\n";
			if (stack.peak() != -912390898) //check if empty.
				stack.print();//print stack.
		}//end case '3'
		break;
		case '4'://peak selection
		{
			cout << "\npeak selected\n";
			if (stack.peak() != -912390898)//check if empty.
				cout << "the peak value is: " << stack.peak();
		}//end case '4'
		break;
		case '5'://exit selection
		{
			cout << "\nexiting the program\n";
			system("puase");
			exit(0);
		}//end case '5'
		default:
			cout << "\ninvalid input, please enter from 1 to 5 ";
			break;
		}//end switch
		//choose again.
		cout << "\nchoose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)\n";
		selectionInput = _getch();
	} while (true);//end do while
	system("pause");
	return 0;
}
/*the output of this program:
* run #1:
program for using two dynamic queues to serve as dynamic stack.
Choose
1- to push.
2- to pop.
3- to print.
4- to peak.
5- to exit.

push selected
enter the value to push: 1

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 2

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 3

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 4

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 5

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 5 4 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 5 4 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 4 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 4
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 4 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 4
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 3
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 3
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 2
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 2
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

invalid input, please enter from 1 to 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

invalid input, please enter from 1 to 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

//////////////////////////////////////////////////////
*run #2:
* program for using two dynamic queues to serve as dynamic stack.
Choose
1- to push.
2- to pop.
3- to print.
4- to peak.
5- to exit.

push selected
enter the value to push: 1

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 2

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 3

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 3
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 3 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 3
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 2
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 2 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 2
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
the peak value is: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 1
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

peak selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 4

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

push selected
enter the value to push: 5

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
the elements in the stack are: 5 4
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

pop selected
the poped value is: 4
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

print selected
stack is empty

choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

invalid input, please enter from 1 to 5
choose (1- to push. 2- to pop. 3- to print. 4- to peak. 5- to exit.)

*/