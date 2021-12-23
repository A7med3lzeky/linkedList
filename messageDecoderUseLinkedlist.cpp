/*program for decoding message.
* team members:
* 1 ahmed adel ahmed elrefae. (security)
* 2 ahmed taher salah.		  (security)
* 3 asmaa alaa abdelmohsen.   (security)
* 4 khaled waleed kamal.	  (security)
* 5 ahmed elmetwally elzeky.  (security)
* 6 mohammad khaled omara.	  (networking)
*/
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
// Nodes struct holding data and pointer at next.
struct Node {
	//data section.
	char item;//the charcter in the node
	int characterPosition;//position of the character in the node
	//pointer to next node.
	Node* next;
	//constructor of nodes
	//arguments char and int for the data.
	Node(char item, int pos = 0)
	{
		this->item = item;
		this->next = NULL;
		characterPosition = pos;
	}
	//destructor of nodes
	~Node() {
		next = NULL;//making next pointer point to nothing.
	}
};//end struct Node
//class for the linked list 
class LinkedList {
	//two pointers, one points at first node and the other points at the last node
	Node* head, * tail;
public:
	//constructor of the class.
	LinkedList() {
		head = tail = NULL;//making the pointers point to nothing.
	}
	//destructor of the class.
	~LinkedList() {
		//steps to delete all pointers of all nodes and make them point at nothing.
		//1- create temp node.
		Node* temp = NULL;
		//2- loop to delete each node next pointer.
		while (head != NULL) {
			temp = head->next;//catching next node before deleting the front.
			delete head;//deleting the front.
			head = temp;//the update of the loop.
		}//end while
		head = temp = tail = NULL;//making all pointers point to nothing.
	}
	/*queue display function to print all data in the nodes in the list
	return nothing
	parameters nothing
	*/
	void DisplayList() {
		//steps to print all data in list.
		//1- check if list is empty.
		if (head == NULL) {
			cout << "list is empty " << endl;
			return;
		}//end if
		//2- create temp node = to front to not change the head pointer.
		Node* temp = head;
		//3- print all values till reach the last node.
		while (temp != NULL) {
			cout << temp->item;//print
			temp = temp->next;//update temp to next node.
		} // end while
	}//end displayList
	/*insert list function to add node in the list from first
	return nothing
	parameters int and char for the data in node
	int for position
	char for the character
	*/
	void insertFirst(char item, int pos) {
		//steps for creating node.
		// 1- create new node and sending data to constractor.
		Node* newNode = new Node(item, pos);
		// 2- check if new node is created or not.
		if (newNode == NULL) {
			cout << "error no space in memory\n";
			return;
		}//end if
		// 3- check if linked list is empty or not as it is the first node.
		if (head == NULL) {
			head = tail = newNode;//as if it is the only node.
			return;
		}//end if
		// 4- making the pointer of new node to point to the first node.
		newNode->next = head;
		// 5- moving the list head to new node which is first now.
		head = newNode;
	}//end insertFirst
	/*list insert last function to add node in the list from last
	return nothing
	parameters int and char for the data in node
	int for position
	char for the character
	*/
	void insertLast(char item, int pos) {
		//steps for creating node.
		// 1- create new node and sending data to constractor.
		Node* newNode = new Node(item, pos);
		// 2- check if new node is created or not
		if (newNode == NULL) {
			cout << "error no space in memory\n";
			return;
		}
		// 3- check if linked list is empty or not 
		if (head == NULL) {
			head = tail = newNode;//as if it is the only node.
			return;
		}
		// 4-making the last node pointer point at the new node.
		tail->next = newNode;
		// 5-moving the tail to last node.
		tail = newNode;
	}//end insertLast
	/*an insertPosition function to add the characters in the list arranged with there
	* position so that the list is arranged.
	* return nothing
	* parameters int and char for the data in node
	*int for position
	*char for the character
	*/
	void insertPosition(int pos, char item) {
		//first check if position is negative.
		if (pos < 0) {
			cout << "error 1\n";
			return;
		}
		//second check if the position is 0.
		if (pos == 0) {
			insertFirst(item, pos);//add at first.
			return;
		}
		//third check if position is positive.
		// 1- if there is no nodes in the list.
		if (head == NULL) {
			insertFirst(item, pos);//add at first.
			return;
		}
		// 2- if there is only one node in the list.
		if (head == tail && head != NULL) {
			//check if position to be added is smaller than first node position.
			if (pos < head->characterPosition)
				insertFirst(item, pos);//if true then add at first.
			else//if false then add at last.
				insertLast(item, pos);
			return;
		}
		// 3-the other conditions are if there is two nodes or more.
		// if the position to be added is smaller than first node position but in two nodes or more.
		if (pos < head->characterPosition) {
			insertFirst(item, pos);//add at first.
			return;
		}
		//else add it at the right position in the list.
		//two pointers to point at two consecutive nodes.
		Node* prev = head;//prev pointer to point at node x.
		Node* temp = head->next;//temp pointer to point at node after node x.
		//while the position of node to be added is greater than temp position then 
		//move to next two nodes.
		while (temp != NULL && pos > temp->characterPosition) {
			temp = temp->next;//update temp.
			prev = prev->next;//update prev.
		}//end while
		// 1- create new node and sending data to constractor.
		Node* newNode = new Node(item, pos);
		// 2- check if new node is created or not.
		if (newNode == NULL) {
			cout << "error no space in memory\n";
			return;
		}
		// 3- check if new node is now the last node.
		if (temp == NULL)
			tail = newNode;//make the last point to new node.
		// 4- make the new node pointer point at temp.
		newNode->next = temp;
		// 5- linking the new node with the prev node.
		prev->next = newNode;
	}//end insertPosition
};//end class LinkedList
///////////////////////////////////////////////
//main function
int main1() {
	//position to take the position from user and hold it.
	//error as flag.
	int position = 0, error = 0;
	//esc the character of restart or not.
	//character is to ensure every input character has its own position.
	char esc = 0, character = '!';
	//string to take the input from user.
	string encodedMessage;
	do {
		LinkedList linkedList;//object from class LinkedList
		encodedMessage = "";//initialize the string and reseting it.
		cout << "please enter encoded message with -1 for ending of message\n";
		getline(cin, encodedMessage);//input the hole line.
		//loop to scan each character in the encodedMessage.
		for (int i = 0; i < encodedMessage.length(); i++) {
			//check if the end of input reached.
			if (encodedMessage[i] == '-') {
				break;
			}//end if
			//check if it is character.
			if (isalpha(encodedMessage[i])) {
				character = encodedMessage[i];//hold it in variable.
			}//end if
			//check if it is digit as it is the position of prev character.
			else if (isdigit(encodedMessage[i])) {
				//if position added with no character 
				if (character == '!') {
					//a1 2 b3
					error = 2;
					break;
				}//end if
				position = encodedMessage[i] - '0';//convert to int then hold it in position.
				//loop for input position containing more than one digit.
				while (isdigit(encodedMessage[++i])) {
					position = position * 10;
					position = position + (encodedMessage[i] - '0');
				}
				i--;//decrement to read this char again if it is character.
				//then add character to list with its position.
				linkedList.insertPosition(position, character);
				character = '!';//reset the character.
			}//end else if
			//check if space or tap 
			else if (encodedMessage[i] == ' ' || encodedMessage[i] == '\t')
			{
				continue;
			}//end else if
		}//end for
		//check if error occured.
		if (error == 2) {
			linkedList.~LinkedList();//first empty the list.
			error = 0;//second reset the flag.
			//third output the error message.
			cout << "invalid input error 2\n";
			cout << "please put the number after each character\n";
			cout << "please enter valid input\n";
			continue;//restart.
		}//end if
		//out put the result decoded message.
		cout << "your decoded message is: ";
		linkedList.DisplayList();//calling the display list.
		cout << "\nDo you need to exit  (Y/N): \n";//ask if restart or exit.
		esc = _getch();
	} while (esc == 'n' || esc == 'N');//end do while
	//system("pause");
	return 0;
}//end main.
/*the output of this program:
* run #1:
please enter encoded message with -1 for ending of message
e 2 b 1 a 3 h 5 c 4 d -1
your decoded message is: beach
Do you need to exit  (Y/N):
please enter encoded message with -1 for ending of message
e 2 b 1 a 3  d -1
your decoded message is: bea
Do you need to exit  (Y/N):

////////////////////////////////////////////////
*run #2:
please enter encoded message with -1 for ending of message
e6 a1 z8 m3 e4 k10 d5 l7 h2 a9 y11 p-1
your decoded message is: ahmedelzaky
Do you need to exit  (Y/N):
please enter encoded message with -1 for ending of message
d5 a1 m3 e4 h2 a6 e8 d7 l9 -1
your decoded message is: ahmedadel
Do you need to exit  (Y/N):

*/
