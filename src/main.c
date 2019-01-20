#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <Windows.h>

void gotoxy(int x, int y);
void getxy(int *x, int *y);
char* ModifyString(char*, char*, int);

int main()
{
	char text[64] = "Lorem Ipsum";

	printf("Before: %s\n", text);
	ModifyString("Text: ", text, sizeof(text));
	printf("After: %s\n", text);
	system("pause");

	return 0;
}

void gotoxy(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void getxy(int *x, int *y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;
	}
}

char* ModifyString(char *prefix, char *string, int size)
{
	int x, y;
	int ch, ch2, len;
	bool isPrinted, *is2Byte = (bool*)calloc(size, sizeof(bool));

	for (size_t i = 0; i < strlen(string); i++)
	{
		if (((unsigned char)string[i] & 0x80) == 0x80)
		{
			is2Byte[i + 1] = true;
			i++;
		}
	}

	getxy(&x, &y);
	isPrinted = false;
	while (1)
	{
		if (!isPrinted)
		{
			gotoxy(x, y);
			printf("%s%s", prefix, string);
			isPrinted = true;
		}
		if (_kbhit())
		{
			ch = _getch();
			if (ch == '\r') break;
			if (ch == '\b')
			{
				len = strlen(string);
				if (len > 0)
				{
					if (1 < len && is2Byte[len - 1])
					{
						is2Byte[len - 1] = false;
						string[len - 2] = '\0';
						printf("\b\b  \b\b");
					}
					else
					{
						string[len - 1] = '\0';
						printf("\b \b");
					}
				}
			}
			else
			{
				len = strlen(string);
				if (((unsigned char)ch & 0x80) == 0x80)
				{
					if (len < size - 2)
					{
						ch2 = _getch();
						string[len] = ch;
						string[len + 1] = ch2;
						string[len + 2] = '\0';
						is2Byte[len + 1] = true;
					}
				}
				else
				{
					if (len < size - 1)
					{
						string[len] = ch;
						string[len + 1] = '\0';
					}
				}
			}
			isPrinted = false;
		}
	}
	printf("\n");
	free(is2Byte);
	return string;
}