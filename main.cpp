#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

struct dataStructure {
	float a[3];
	int b;
	char c[5];
	float d;
};

struct keyField {
	float a;
	float b;
	float c;
	float index;
};

bool operator < (const keyField& lhs, const keyField& rhs) {
	if (lhs.a == rhs.a) {
		if (lhs.b == rhs.b) {
			return lhs.c < rhs.c;
		}
		else {
			return lhs.b < rhs.b;
		}
	}
	else {
		return lhs.a < rhs.a;
	}
}

bool operator > (const keyField& lhs, const keyField& rhs) {
	return rhs < lhs;
}

bool operator == (const keyField& lhs, const keyField& rhs) {
	if (lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c) { return true; }
	else { return false; }
}

void generationData(vector<dataStructure>& data, const int length) {
	char char_array[] =
	{ 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U',
	'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e',
	'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z' };
	for (int i = 0; i < length; ++i) {
		dataStructure temp;
		for (auto& i : temp.a) {
			i = rand() % 15 + 10;
			//cin >> i;
		}
		temp.b = rand() % 200 + 100;
		for (auto& i : temp.c) {
			int index_random_char = rand() % 51;
			char random_char = char_array[index_random_char];
			i = random_char;
		}
		temp.d = rand() % 1500 + 1000;
		data.push_back(temp);
	}
}

void printData(const vector<dataStructure>& data) {
	for (const auto& i : data) {
		for (const auto& j : i.a) {
			cout << setw(2) << j << ' ';
		}
		cout << "| " << i.b << " | ";
		for (const auto& j : i.c) {
			cout << j << ' ';
		}
		cout << "| " << i.d << endl;
	}
}

void swapStructure(keyField& lhs, keyField& rhs) {
	keyField temp;
	temp = lhs;
	lhs = rhs;
	rhs = temp;
}

void sortKeyField(vector<keyField>& generalReference) {
	for (int i = 0; i < generalReference.size() - 1; ++i) {
		bool flag = false;
		for (int j = 0; j < generalReference.size() - i - 1; ++j) {
			if (generalReference[j] > generalReference[j + 1]) {
				swapStructure(generalReference[j], generalReference[j + 1]);
				flag = true;
			}
		}
		if (flag == false) { break; }
	}
}

void printMenu() {
	cout << endl << "interval or single value?" << endl
		<< "[1] - single value" << endl
		<< "[2] - interval" << endl
		<< "[3] - Exit" << endl;
}

vector<int> binarySearch(const vector<keyField>& generalReference, keyField& value) {
	vector<int> result;
	int left = 0;
	int right = generalReference.size();
	int resIndex = -1;
	while (right != left) {
		int middle = (right + left) / 2;
		if (value == generalReference[middle]) {
			result.push_back(middle);
			if (middle != 0) {
				int leftValues = middle - 1;
				while (value == generalReference[leftValues]) {
					result.push_back(leftValues);
					leftValues--;
					if (leftValues == -1) { break; }
				}
			}
			if (middle != generalReference.size() - 1) {
				int rightValues = middle + 1;
				while (value == generalReference[rightValues]) {
					result.push_back(rightValues);
					rightValues++;
					if (rightValues == generalReference.size()) { break; }
				}
			}
			sort(result.begin(), result.end());
			return result;
		}
		if (value > generalReference[middle]) {
			if (middle == left) {
				return result;
			}
			left = middle;
		}
		else { right = middle; }
	}
}

int binarySearchInterval(const vector<keyField>& generalReference, keyField& value, char key) {
	int result;
	int left = 0;
	int right = generalReference.size();
	int resIndex = -1;
	while (right - left > 1) {
		int middle = (right + left) / 2;
		if (value == generalReference[middle]) {
			return middle;
		}
		if (value > generalReference[middle]) {
			left = middle;
		}
		else { right = middle; }
	}
	if (key == 'l') {
		return right;
	}
	else {
		return left;
	}

}

int main() {
	srand(time(NULL));
	const int N = 10;

	vector<dataStructure> allData;
	generationData(allData, N);
	cout << "***Generated data***" << endl;
	printData(allData);
	cout << endl;

	vector<keyField> generalReference;
	for (int i = 0; i < allData.size(); ++i) {
		keyField temp;
		temp.a = allData[i].a[0];
		temp.b = allData[i].a[1];
		temp.c = allData[i].a[2];
		temp.index = i;
		generalReference.push_back(temp);
	}
	sortKeyField(generalReference);
	cout << "***General reference***" << endl;
	cout << "***Key field > index***" << endl;
	for (const auto& i : generalReference) {
		cout << i.a << " " << i.b << " " << i.c << " > " << i.index << endl;
	}

	printMenu();
	int command;
	while (cin >> command) {
		if (command == 1) {
			keyField value;
			value.index = -1;
			cout << "value: ";
			cin >> value.a >> value.b >> value.c;
			vector<int> foundItems = binarySearch(generalReference, value);
			if (foundItems.size() != 0) {
				cout << "Found:" << endl;
				for (int t = 0; t < foundItems.size(); ++t) {
					for (const auto& j : allData[generalReference[foundItems[t]].index].a) {
						cout << setw(2) << j << ' ';
					}
					cout << "| " << allData[generalReference[foundItems[t]].index].b << " | ";
					for (const auto& j : allData[generalReference[foundItems[t]].index].c) {
						cout << j << ' ';
					}
					cout << "| " << allData[generalReference[foundItems[t]].index].d << endl;
				}
			}
			else { cout << "Not found" << endl; }
		}
		else if (command == 2) {
			keyField intervalLeft;
			intervalLeft.index = -1;
			keyField intervalRight;
			intervalRight.index = -1;
			cout << "interval [left]: ";
			cin >> intervalLeft.a >> intervalLeft.b >> intervalLeft.c;
			int temp1 = binarySearchInterval(generalReference, intervalLeft, 'l');
			cout << "interval [Right]: ";
			cin >> intervalRight.a >> intervalRight.b >> intervalRight.c;
			int temp2 = binarySearchInterval(generalReference, intervalRight, 'r');
			cout << "Found:" << endl;
			for (int t = temp1; t <= temp2; ++t) {
				for (const auto& j : allData[generalReference[t].index].a) {
					cout << setw(2) << j << ' ';
				}
				cout << "| " << allData[generalReference[t].index].b << " | ";
				for (const auto& j : allData[generalReference[t].index].c) {
					cout << j << ' ';
				}
				cout << "| " << allData[generalReference[t].index].d << endl;
			}
		}
		else if (command == 3) { return 0; }
		else { cout << "Unknown command" << endl; }
		printMenu();
	}
}