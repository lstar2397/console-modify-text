#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

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

char* ModifyString(char *prefix, char *string, int size)
{
	int ch, len;
	bool isPrinted;

	isPrinted = false;
	while (1)
	{
		if (!isPrinted)
		{
			printf("\r%s%s", prefix, string);
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
					string[len - 1] = '\0';
					printf("\b \b");
				}
			}
			else
			{
				len = strlen(string);
				if (len < size - 1)
				{
					string[len] = ch;
					string[len + 1] = '\0';
				}
			}
			isPrinted = false;
		}
	}
	printf("\n");
	return string;
}