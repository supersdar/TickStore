#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
		if (strcmp(argv[i], "--path") == 0)
		{
			if (i + 1 < argc)
			{
				cout << argv[i + 1] << endl;
			}
			else
			{
				//�������������˳�����
				cout << "��ʹ�� --path Path ���ô洢·��" << endl;
			}
			break;
		}
	}
	getchar();
	return 0;
}