#include<iostream>
#include<list>
#include<queue>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
//building struct with default constructor and print function
struct building {
	int id;
	string name;
	int capacity;
	//constructors for building
	building() {
		id = 0;
		name = " ";
		capacity = 0;
	}

	building(int id1, string name1, int capacity1) {
		id = id1;
		name = name1;
		capacity = capacity1;
	}

	//print fuction for building
	void print() {
		cout << "the building's name is " << name << " the building's id is " << id << " the building's capacity is " << capacity << endl;
	}

};
//binarytree class with its functions
struct node {
	building value;
	node* left;
	node* right;

};
class btree {
public:

	node* root;

	btree() {
		root = NULL;
	}

	//function to destroy the whole tree
	void destroy_tree(node* leaf) {
		if (leaf != NULL) {
			destroy_tree(leaf->left);
			destroy_tree(leaf->right);
			delete leaf;
		}
	}

	void insert(building key, node* leaf) {

		if (key.id < leaf->value.id) {
			if (leaf->left != NULL) {
				insert(key, leaf->left);
			}
			else {
				leaf->left = new node;
				leaf->left->value = key;
				leaf->left->left = NULL;
				leaf->left->right = NULL;
			}
		}
		else if (key.id >= leaf->value.id) {

			if (leaf->right != NULL) {
				insert(key, leaf->right);
			}
			else {
				leaf->right = new node;
				leaf->right->value = key;
				leaf->right->right = NULL;
				leaf->right->left = NULL;
			}
		}

	}
	//function to insert
	void insert(building key) {

		if (root != NULL) {
			insert(key, root);
		}
		else {
			root = new node;
			root->value = key;
			root->left = NULL;
			root->right = NULL;
		}

	}
	//search that returns a pointer to the node if found
	node* search(building key, node* leaf) {
		if (leaf != NULL) {
			if (key.id == leaf->value.id) {
				return leaf;
			}
			if (key.id < leaf->value.id) {
				return search(key, leaf->left);
			}
			else {
				return search(key, leaf->right);
			}
		}
		else {
			return NULL;
		}
	}

	node* search(building key) {
		return search(key, root);
	}

	void destroy_tree() {
		destroy_tree(root);
	}

	void inorder_print() {
		inorder_print(root);
		cout << "\n";
	}

	void inorder_print(node* leaf) {
		if (leaf != NULL) {
			inorder_print(leaf->left);
			leaf->value.print();
			inorder_print(leaf->right);
		}
	}
	//search bool fucntion for the delete function
	bool Searchifthere(node* root, building value)
	{
		if (root == NULL)
			return false;
		else if (root->value.id == value.id)
		{
			return true;
		}
		else if (value.id < root->value.id)
			Searchifthere(root->left, value);
		else if (value.id > root->value.id)
			Searchifthere(root->right, value);
	}
	//find min node to help the delete function
	node* findMin(node* root)
	{
		while (root->left != NULL)
		{
			root = root->left;
		}
		return root;
	}
	//variable to be used later
	bool c = false;
	//function to delete a node
	node* Delete(node* root, building value)
	{
		c = Searchifthere(root, value);
		if (root == NULL)
			return root;
		else if (value.id < root->value.id)
		{
			root->left = Delete(root->left, value);
		}
		else if (value.id > root->value.id)
		{
			root->right = Delete(root->right, value);
		}

		// Node deletion
		else
		{
			//case 1: Leaf Node
			if (root->left == NULL && root->right == NULL)
			{
				delete root;
				root = NULL;
				return root;
			}
			//case 2: one child
			else if (root->left == NULL)
			{
				struct node* temp = root;
				root = root->right;
				delete temp;
				return root;
			}
			else if (root->right == NULL)
			{
				struct node* temp = root;
				root = root->left;
				delete temp;
				return root;
			}
			//case 3: 2 child
			else
			{
				struct node* temp = findMin(root->right);
				root->value = temp->value;
				root->right = Delete(root->right, temp->value);
			}
		}
		return root;
	}
};
//building node that connects the street and the buildings and thier lines' capacity
class buildingnode {
public:
	int totalcapacity;
	int maxcapacity;
	btree buildingtree;

	//constructors for the building nodes
	buildingnode() {
		totalcapacity = 0;
		maxcapacity = totalcapacity;
		buildingtree;
	}

	buildingnode(btree buildingtree1, int totalcapacity1) {
		totalcapacity = totalcapacity1;
		buildingtree = buildingtree1;
		maxcapacity = totalcapacity;
	}

	//print function for the building node
	void printbuildingtree() {
		cout << "the total capacity left is " << totalcapacity << " of " << maxcapacity << " the buildings are :" << endl;
		buildingtree.inorder_print();
		cout << endl;
	}

};
//street node that contains the streets and the array of lines with its functions
struct streetnode {
	string name;
	int id;
	int size;
	buildingnode* buildingnodearray;

	//constructors for the street  node
	streetnode() {
		name = " ";
		id = 0;
		size = 0;
		buildingnodearray = new buildingnode[size];
	}

	streetnode(string name1, int id1) {
		name = name1;
		id = id1;
		size = 0;
		buildingnodearray = new buildingnode[size];
	}

	//print function to print the streetnode
	void printstreetnode() {
		cout << "the name of the street is " << name << " the id of the street is " << id << endl;
		for (int i = 0; i < size; i++) {
			cout << "the line " << i + 1 << " has :" << endl;
			buildingnodearray[i].printbuildingtree();
		}
	}

	//function to extend the lenght of the array
	buildingnode* extendarray(buildingnode* oldArray, int& size) {
		int newSize = size + 1;
		buildingnode* newArray = new buildingnode[newSize];
		for (int i = 0; i < size; i++) {
			newArray[i] = oldArray[i];
		}
		delete[] oldArray;
		size++;
		oldArray = new buildingnode[size];
		oldArray = newArray;
		return oldArray;
	}

	//function to insert btree into the array of lines
	void insertbuildingnode(buildingnode building) {
		buildingnodearray = extendarray(buildingnodearray, size);
		buildingnodearray[size - 1] = building;
	}
	int returnarraysize() {
		return size;
	}

};
//struct of the area
struct area {
	string name;
	int id;
	list<streetnode> streets;

	//constructors
	area() {
		name = " ";
		id = 0;
	}
	area(string name1, int id1) {
		name = name1;
		id = id1;
	}

	//print fucntion
	void printarea() {
		list<streetnode>::iterator it;
		cout << "the area name is " << name << " the area id is " << id << endl;
		for (it = streets.begin(); it != streets.end(); it++) {
			(it)->printstreetnode();
			cout << endl;
		}
	}

};
//goales remaining :
//check print functions
int main() {
	vector <area>vector;
	//the menu
	while (true) {
		int temp;
		cout << "press 1 to access area " << endl;
		cout << "press 2 to access street " << endl;
		cout << "press 3 to access building " << endl;
		cout << "press 4 to access print" << endl;
		cout << "press 5 to access exit" << endl;
		cin >> temp;
		//area
		if (temp == 1) {
			int temp1;
			cout << "press 1 to add" << endl;
			cout << "press 2 to delete" << endl;
			cout << "press 3 to update" << endl;
			cin >> temp1;
			//add area
			if (temp1 == 1) {
				string name;
				int id;
				bool checkarea = false;
				cout << "insert the id" << endl;
				cin >> id;
				cout << "insert the name" << endl;
				cin >> name;
				area area1(name, id);
				std::vector<area>::iterator it;
				//check if area with the same id existed before 
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == id) {
						checkarea = true;
					}
				}
				//add area if it doesnt exist 
				if (checkarea == false) {
					vector.push_back(area1);
				}
				else {
					cout << "the area is already inserted" << endl;
				}
			}
			//delete area
			else if (temp1 == 2) {
				int id;
				cout << "insert the id" << endl;
				cin >> id;
				bool check = false;
				std::vector<area>::iterator it;
				//search for the area
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == id) {
						//if found delete it
						vector.erase(it);
						check = true;
						break;
					}
				}
				//in case area doesnt exist
				if (check == false) {
					cout << "The area does not exist " << endl;
				}
			}
			//update for the area change its name
			else if (temp1 == 3) {
				string name;
				int id;
				cout << "insert the id" << endl;
				cin >> id;
				cout << "insert the new name" << endl;
				cin >> name;
				bool check = false;
				std::vector<area>::iterator it;
				//search for the area
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == id) {
						//if found update area
						it->id = id;
						it->name = name;
						check = true;
					}
				}
				//in case area doesnt exist
				if (check == false) {
					cout << "The area does not exist " << endl;
				}
			}
			else {
				cout << "Function does not exist please go back to menu for more information " << endl;
			}
		}
		//for street
		else if (temp == 2)
		{
			int temp1;
			cout << "press 1 to add" << endl;
			cout << "press 2 to delete" << endl;
			cout << "press 3 to update" << endl;
			cin >> temp1;
			//add street
			if (temp1 == 1) {
				string name;
				int idstreet;
				int idarea;
				int numberoflines;
				int linecapacity = 0;
				cout << "insert the area id" << endl;
				cin >> idarea;
				cout << "insert the street id" << endl;
				cin >> idstreet;
				cout << "insert the name" << endl;
				cin >> name;
				cout << "insert the number of lines" << endl;
				cin >> numberoflines;
				bool checkarea = false;
				bool checkstreet = false;
				//
				streetnode street1(name, idstreet);
				btree buildings;
				buildingnode buildingnode(buildings, linecapacity);
				for (int i = 0; i < numberoflines; i++) {
					cout << "insert the line capacity of line " << i + 1 << endl;
					cin >> linecapacity;
					buildingnode.maxcapacity = linecapacity;
					buildingnode.totalcapacity = linecapacity;
					street1.insertbuildingnode(buildingnode);
				}
				//
				std::vector<area>::iterator it;
				//search for the area
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == idarea) {
						checkarea = true;
						//if found add the given street
						std::list<streetnode>::iterator it1;
						//search for the area
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == idstreet) {
								checkstreet = true;
							}
						}
						if (checkstreet == false) {
							it->streets.push_back(street1);
						}
						else {
							cout << "The street already exist " << endl;
						}
					}
				}
				//in case area doesnt exist
				if (checkarea == false) {
					cout << "The area does not exist " << endl;
				}
			}
			//search and delete street
			else if (temp1 == 2) {
				int idstreet;
				int idarea;
				cout << "insert the area id" << endl;
				cin >> idarea;
				cout << "insert the street id" << endl;
				cin >> idstreet;
				bool areacheck = false;
				bool streetcheck = false;
				std::vector<area>::iterator it;
				//search for the area
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == idarea) {
						areacheck = true;
						std::list<streetnode>::iterator it1;
						//search for the street
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == idstreet) {
								//if found delete the street from the lsit
								it->streets.erase(it1);
								streetcheck = true;
								break;
							}
						}
					}
				}
				//in case area and street doesnt exist
				if (areacheck == false) {
					cout << "The area does not exist " << endl;
				}
				if (streetcheck == false) {
					cout << "The street does not exist " << endl;
				}
			}
			//update street by changing name
			else if (temp1 == 3) {
				string name;
				int idstreet;
				int idarea;
				cout << "insert the area id" << endl;
				cin >> idarea;
				cout << "insert the street id" << endl;
				cin >> idstreet;
				cout << "insert the new name" << endl;
				cin >> name;
				bool areacheck = false;
				bool streetcheck = false;
				std::vector<area>::iterator it;
				//search for the area
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == idarea) {
						areacheck = true;
						std::list<streetnode>::iterator it1;
						//search for the street
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == idstreet) {
								//change the street name
								it1->name = name;
								streetcheck = true;
							}
						}
					}
				}
				//in case the street or area doesnt exist
				if (areacheck == false) {
					cout << "The area does not exist" << endl;
				}
				if (streetcheck == false) {
					cout << "The street does not exist" << endl;
				}
			}
			else {
			cout << "Function does not exist please go back to menu for more information " << endl;
			}
		}
		//for buildings
		else if (temp == 3) {
			int temp1;
			cout << "press 1 to add" << endl;
			cout << "press 2 to delete" << endl;
			cout << "press 3 to update" << endl;
			cin >> temp1;
			//add the building
			if (temp1 == 1) {
				int streetid;
				int linenumber;
				string buildingname;
				int buildingid;
				int buildingcapacity;
				int areaid;
				cout << "insert the area id" << endl;
				cin >> areaid;
				cout << "insert the street id" << endl;
				cin >> streetid;
				cout << "insert the building id" << endl;
				cin >> buildingid;
				cout << "insert the line number" << endl;
				cin >> linenumber;
				cout << "insert the name of the building" << endl;
				cin >> buildingname;
				cout << "insert the building capacity" << endl;
				cin >> buildingcapacity;
				//later use


				//cout << "insert the building payment" << endl;
				//cin >> buildingpayment;
				bool checkarea = false;
				bool checkstreet = false;
				bool checkbuilding = false;
				bool checkline = false;
				//create the building to be added
				building building1(buildingid, buildingname, buildingcapacity);
				std::vector<area>::iterator it;
				//search for the area and check if existed
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == areaid) {
						checkarea = true;
						std::list<streetnode>::iterator it1;
						//search for the street and check if existed
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == streetid) {
								checkstreet = true;
								//check for the line and check if existed
								if (it1->size >= linenumber) {
									checkline = true;
									//search for the building and check if it existed
									if (it1->buildingnodearray[linenumber - 1].buildingtree.Searchifthere(it1->buildingnodearray[linenumber - 1].buildingtree.root, building1) == true) {
										checkbuilding = true;
									}
									//if the builidng doesnt already exist add it
									else {
										//check if the capacity of tthe line can handle the capcity of the buidling
										if (it1->buildingnodearray[linenumber - 1].totalcapacity > building1.capacity) {
											//add the building
											it1->buildingnodearray[linenumber - 1].buildingtree.insert(building1);
											//update the totla capacty of the line
											it1->buildingnodearray[linenumber - 1].totalcapacity = it1->buildingnodearray[linenumber - 1].totalcapacity - building1.capacity;
										}
										//if capacity of the building exceeds the capacity of the line
										else {
											cout << "The capacity of the building exceeds the remaing capacity of the line " << endl;
										}
									}
								}
							}
						}
					}
				}
				//if the area doesnt exist
				if (checkarea == false) {
					cout << "The area does not exist " << endl;
				}
				//if street doesnt exist
				else if (checkstreet == false) {
					cout << "The street does not exist " << endl;
				}
				//if the line doesnt exist
				else if (checkline == false) {
					cout << "The line does not exist " << endl;
				}
				//if the building arealdy exists
				else if (checkbuilding == true) {
					cout << "The building already exists " << endl;
				}

			}
			//remove the building
			else if (temp1 == 2) {
				int streetid;
				int linenumber;
				string buildingname = "";
				int buildingid;
				int buildingcapacity = 0;
				int areaid;
				cout << "insert the area id" << endl;
				cin >> areaid;
				cout << "insert the street id" << endl;
				cin >> streetid;
				cout << "insert the line number" << endl;
				cin >> linenumber;
				cout << "insert the building id" << endl;
				cin >> buildingid;
				bool checkarea = false;
				bool checkstreet = false;
				bool checkline = false;
				bool checkbuilding = false;
				//search in areas
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == areaid) {
						checkarea = true;
						std::list<streetnode>::iterator it1;
						//search in streets using idof street
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == streetid) {
								checkstreet = true;
								building building1(buildingid, buildingname, buildingcapacity);
								if (it1->size >= linenumber) {
									checkline = true;
									//when found check if the building id exist
									if (it1->buildingnodearray[linenumber - 1].buildingtree.Searchifthere(it1->buildingnodearray[linenumber - 1].buildingtree.root, building1) == true) {
										checkbuilding = true;
										//if yes update the total capacity by adding the capacity of the building that is being removed to the total capacity
										it1->buildingnodearray[linenumber - 1].totalcapacity = it1->buildingnodearray[linenumber - 1].totalcapacity + it1->buildingnodearray[linenumber - 1].buildingtree.search(building1)->value.capacity;
										//remove the buidling
										it1->buildingnodearray[linenumber - 1].buildingtree.Delete(it1->buildingnodearray[linenumber - 1].buildingtree.root, building1);
										break;
									}
								}
							}
						}
					}
				}
				if (checkarea == false) {
					cout << "The area does not exist" << endl;
				}
				if (checkstreet == false) {
					cout << "The street does not exist" << endl;
				}
				if (checkline == false) {
					cout << "The line does not exist" << endl;
				}
				if (checkbuilding == false) {
					cout << "The building does not exist" << endl;
				}
			}
			//update the building
			else if (temp1 == 3) {
				int streetid;
				int linenumber;
				string buildingname;
				int buildingid;
				int buildingcapacity;
				int areaid;
				cout << "insert the area id" << endl;
				cin >> areaid;
				cout << "insert the street id" << endl;
				cin >> streetid;
				cout << "insert the line number" << endl;
				cin >> linenumber;
				cout << "insert the building id" << endl;
				cin >> buildingid;
				cout << "insert the name of the building" << endl;
				cin >> buildingname;
				cout << "insert the building capacity" << endl;
				cin >> buildingcapacity;
				bool checkarea = false;
				bool checkstreet = false;
				bool checkline = false;
				bool checkbuilding = false;
				//search in the areas
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == areaid) {
						checkarea = true;
						std::list<streetnode>::iterator it1;
						//search in the streets
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							//if street find try to update the building
							if (it1->id == streetid) {
								checkstreet = true;
								building building1(buildingid, buildingname, buildingcapacity);
								if (it1->size >= linenumber) {
									checkline = true;
									//search for the building id that you want to update
									if (it1->buildingnodearray[linenumber - 1].buildingtree.Searchifthere(it1->buildingnodearray[linenumber - 1].buildingtree.root, building1) == true) {
										checkbuilding = true;
										//check if the capacity of the line can hold the capacity of the new building by adding the old building capacity to the line and checking the new capacity ifgreater than the capacity of the given building
										if (it1->buildingnodearray[linenumber - 1].totalcapacity + it1->buildingnodearray[linenumber - 1].buildingtree.search(building1)->value.capacity > building1.capacity) {
											//if yes update the new capacity of the total capacity and update the building
											it1->buildingnodearray[linenumber - 1].totalcapacity = it1->buildingnodearray[linenumber - 1].totalcapacity + it1->buildingnodearray[linenumber - 1].buildingtree.search(building1)->value.capacity;
											it1->buildingnodearray[linenumber - 1].buildingtree.search(building1)->value = building1;
											it1->buildingnodearray[linenumber - 1].totalcapacity = it1->buildingnodearray[linenumber - 1].totalcapacity - building1.capacity;

										}
										else {
											cout << "There is no enough capacity to insert the building here" << endl;
										}
									}
								}
							}
						}
					}
				}
				//if street or building doesnt exist
				if (checkarea == false) {
					cout << "The area does not exist" << endl;
				}
				if (checkstreet == false) {
					cout << "The street does not exist" << endl;
				}
				if (checkline == false) {
					cout << "The line does not exist" << endl;
				}
				if (checkbuilding == false) {
					cout << "The building does not exist" << endl;
				}
			}
			else {
			cout << "Function does not exist please go back to menu for more information " << endl;
			}
		}
		//print fucntions
		else if (temp == 4) {

			int temp1;
			cout << "press 1 to list the area " << endl;
			cout << "press 2 to list streets " << endl;
			cout << "press 3 to list building in a specific line " << endl;
			cout << "press 4 to list the line with highest capacity and the capacity used from it " << endl;
			cout << "press 5 to list the whole map" << endl;
			cin >> temp1;
			//area listing
			if (temp1 == 1) {
				//printing the areas in the vector
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					cout << "the area's name is " << it->name << " the area's id is " << it->id << endl;
				}
			}
			//street listing
			else if (temp1 == 2) {
				int areaid;
				cout << "please enter the area id" << endl;
				cin >> areaid;
				bool areacheck = false;
				//search for the area using its id and print the streets name and id in the spceific area
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == areaid) {
						areacheck = true;
						cout << "the the area " << it->name << " of id " << it->id << endl;
						std::list<streetnode>::iterator it1;
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							cout << "the street name is " << it1->name << " the street id is " << it1->id << endl;
						}
					}
				}
				//if area deosnt exist
				if (areacheck == false) {
					cout << "The area does not exist" << endl;
				}
			}
			//specific line print
			else if (temp1 == 3) {
				bool areacheck = false;
				bool streetcheck = false;
				bool linecheck = false;
				int areaid;
				int streetid;
				int numberofline;
				cout << "please enter the area id" << endl;
				cin >> areaid;
				cout << "please enter the street id" << endl;
				cin >> streetid;
				cout << "please enter the number of line you want to choose" << endl;
				cin >> numberofline;
				//search for the line using the areaid in the areas and then the streets using the street id
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					if (it->id == areaid) {
						areacheck = true;
						std::list<streetnode>::iterator it1;
						for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
							if (it1->id == streetid) {
								streetcheck = true;
								//if not print line doesnt exist
								if (numberofline > it1->size) {
									cout << "This line does not exist " << endl;
								}
								//if we find the line print it
								else {
									it1->buildingnodearray[numberofline - 1].printbuildingtree();
								}
							}
						}
					}
					//print if area or line not found
					if (areacheck == false) {
						cout << "The area does not exist " << endl;
					}
					if (streetcheck == false) {
						cout << "The street does not exist" << endl;
					}
				}
			}
			//max line print
			else if (temp1 == 4) {
				int maxcapacityline = 0;
				int areaid;
				int streetid;
				int linenumber;
				//get the max capacity line
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					std::list<streetnode>::iterator it1;
					for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
						for (int i = 0; i < it1->size; i++) {
							if (maxcapacityline < it1->buildingnodearray[i].maxcapacity) {
								maxcapacityline = it1->buildingnodearray[i].maxcapacity;
								areaid = it->id;
								streetid = it1->id;
								linenumber = i + 1;
							}
						}
					}
				}
				//print the line after deciding the max capacity
				std::vector<area>::iterator it3;
				for (it3 = vector.begin(); it3 != vector.end(); it3++) {
					if (it3->id == areaid) {
						std::list<streetnode>::iterator it4;
						for (it4 = it3->streets.begin(); it4 != it3->streets.end(); it4++) {
							if (it4->id == streetid) {
								cout << "The line with the highest capacity is of the area's id : " << areaid << " street id " << streetid << " and line number " << linenumber << endl;
								it4->buildingnodearray[linenumber - 1].printbuildingtree();
							}
						}
					}
				}
			}
			//whole map print
			else if (temp1 == 5) {
				std::vector<area>::iterator it;
				for (it = vector.begin(); it != vector.end(); it++) {
					cout << "The area's name is " << it->name << " The area's id is " << it->id << " with the following streets :" << endl;
					cout << endl;
					std::list<streetnode>::iterator it1;
					for (it1 = it->streets.begin(); it1 != it->streets.end(); it1++) {
						cout << "The street name is " << it1->name << " the street id is " << it1->id << "with the following lines :" << endl;
						cout << endl;
						for (int i = 0; i < it1->size; i++) {
							it1->buildingnodearray[i].printbuildingtree();
						}
					}
				}
			}
			else {
			cout << "Function does not exist please go back to menu for more information " << endl;
			}

		}
		else if(temp==5) {
			break;
		}
		else {
		cout << "Function does not exist please go back to menu for more information " << endl;
			}
	}

}

