#include <iostream>
#include <ctime>

using namespace std;

const int CountGraphs = 7;
const int width = 4;
int selectedArray[CountGraphs];
int selectedArray_count = 0;
int selectedArray_previous[CountGraphs];
int selectedArray_previous_count = 0;
int array[CountGraphs][CountGraphs];
int func[CountGraphs][2] = { 0 };
int array1[CountGraphs - 1][CountGraphs][3] = { 0 };
int array1_length[CountGraphs - 1] = { 0 };

void setArrayCountGraphsull() // все массивы приравниваю к -1
{
	for (int i = 0; i < CountGraphs; i++)
	{
		for (int j = 0; j < CountGraphs; j++)
		{
			array[i][j] = -1;
		}
	}
	for (int i = 0; i < CountGraphs; i++)
	{
		selectedArray_previous[i] = -1;
	}
	for (int i = 0; i < CountGraphs; i++)
	{
		selectedArray[i] = -1;
	}
}

void getSimmiliarArray(){
    for(int i = 0; i < CountGraphs; i++){
        for(int j = 0; j < CountGraphs; j++){
            array[i][j] = array[j][i];
        }
    }
}

void getRandomArray() // ЗАПОЛНЕНИЕ МАССИВА РАНДОМНЫМИ ЧИСЛАМИ
{
	array[0][1] = 1 + rand() % 90;
	array[0][3] = 1 + rand() % 90;
	array[1][0] = 1 + rand() % 90;
	array[3][0] = 1 + rand() % 90;

	for (int i = 1; i < CountGraphs; i++)
	{
		for (int j = i + 1; ((j < width + i + 1) && (j < CountGraphs)); j++)
		{
			array[i][j] = 1 + rand() % 90;
			array[j][i] = 1 + rand() % 90;
		}
	}
	for (int j = 1; j < CountGraphs; j++)
	{
		for (int i = j + 1; ((i < width + j + 1) && (i < CountGraphs)); i++)
		{
			array[i][j] = 1 + rand() % 90;
		}
	}
	getSimmiliarArray();
	for (int i = 0; i < CountGraphs; i++)
	{
		cout.width(4);
		cout << i + 1;
	}
	cout << "\n";
	cout << endl;
	for (int i = 0; i < CountGraphs; i++)
	{
		cout << i + 1;
		for (int j = 0; j < CountGraphs; j++)
		{
			if (array[i][j] == -1)
			{
				cout.width(4);
				cout << '0';
			}
			else
			{
				cout.width(4);
				cout << array[i][j];
			}

		}
		cout << endl;
	}
}

void getConnectedVertices(int k) { // ПОИСК НА СВЯЗАННЫЕ ВЕРШИНЫ
	for (int i = k + 1; i < CountGraphs; i++)
	{
		if (array[k][i] != -1)
		{
			bool flag = false;
			for (int j = 0; j < selectedArray_count; j++)
			{
				if (selectedArray[j] == i)
					flag = true;
			}
			if (!flag)
			{
				selectedArray[selectedArray_count] = i;
				++selectedArray_count;
			}
		}
	}
}

void step(int k) // ВЫВОД ЭТАПОВ
{
    cout << "ЭТАП " << k - 1 << endl;
	cout << endl;
	cout.width(4);
	cout << "x" << k;
	selectedArray_count = 0;
	for (int i = 0; i < selectedArray_previous_count; i++)
	{
		getConnectedVertices(selectedArray_previous[i]);
		cout.width(4);
		cout << "x" << k - 1 << "=" << selectedArray_previous[i] + 1;

	}
	cout.width(4);
	cout << "f" << k << "(x" << k << ")";
	cout.width(20);
	cout << "     оптимальное решение" ;
	cout << endl;
	cout << endl;
	for (int i = 0; i < selectedArray_count; i++)
	{
		cout.width(4);
		cout << selectedArray[i] + 1;
		int minNumber = 1000;
		for (int j = 0; j < selectedArray_previous_count; j++)
		{
			if (selectedArray[i] > selectedArray_previous[j])
			{
				if (array[selectedArray_previous[j]][selectedArray[i]] == -1)
				{
					cout.width(7);
					cout << "0";
				}
				else
				{
					int minNumberTransfer = array[selectedArray_previous[j]][selectedArray[i]] + array1[k - 2][j][1];
					if (minNumberTransfer > 0)
					{
						cout.width(7);
						cout << minNumberTransfer;
						if (minNumberTransfer < minNumber)
						{
							minNumber = minNumberTransfer;
							array1[k - 1][i][1] = minNumber;
							array1[k - 1][i][2] = selectedArray_previous[j];
						}
					}
				}
			}
			else
			{
				cout.width(7);
				cout << "0";
			}
		}
		array1[k - 1][i][0] = selectedArray[i];
		array1_length[k - 1] = selectedArray_count;
		cout.width(10);
		cout << array1[k - 1][i][1];
		cout.width(15);
		cout << array1[k - 1][i][2] + 1 << endl;
	}
}


void searching(int i)
{
	int k = array1_length[i] - 1;
	cout << array1[i][k][0] + 1;
	while (1)
	{
		i--;
		for (int j = 0; j < array1_length[i]; j++)
		{
			if (array1[i][j][0] == array1[i + 1][k][2])
			{
				cout << " - " << array1[i][j][0] + 1; // ВЫВОД КРАТЧАЙШЕГО ПУТИ
				k = j;
				break;
			}
		}
		if (i == 0)
		{
			break;
		}
	}
}

void getOptimumSolution() // получение оптимального решения
{
	int k = 2;
	selectedArray_previous[0] = 0;
	selectedArray_previous_count = 1;
	for (int j = 1; j < CountGraphs; j++)
	{
		step(k);
		for (int i = 0; i < CountGraphs; i++)
		{
			if (selectedArray[i] == CountGraphs - 1)
			{
				selectedArray[i] = -1;
				--selectedArray_count;
			}
			else
			{
				selectedArray_previous[i] = selectedArray[i];
				selectedArray[i] = -1;
			}
		}
		selectedArray_previous_count = selectedArray_count;
		selectedArray_count = 0;
		k++;
	}
	int minNumber = 100000;
	for (int i = CountGraphs - 2; i > -1; i--)
	{
		if (array1[i][array1_length[i] - 1][0] == CountGraphs - 1)
		{
			if (array1[i][array1_length[i] - 1][1] < minNumber)
			{
				minNumber = array1[i][array1_length[i] - 1][1];
			}
		}
	}
	for (int i = CountGraphs - 2; i > -1; i--)
	{
		if (array1[i][array1_length[i] - 1][0] == CountGraphs - 1)
		{
			if (array1[i][array1_length[i] - 1][1] == minNumber)
			{
				cout << "\nКратчайший маршрут из 1 вершины в 7: ";
				searching(i);
				cout << "\nКратчайший путь длина: " << array1[i][array1_length[i] - 1][1];
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	setArrayCountGraphsull();
	getRandomArray();
	getOptimumSolution();
	system("pause");
	return 0;
}
