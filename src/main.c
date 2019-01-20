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
	int ch, ch2, len;
	bool isPrinted, is2Byte, *twoByte = (bool*)calloc(size, sizeof(bool));

	for (size_t i = 0; i < strlen(string); i++)
	{
		if (((unsigned char)string[i] & 0x80) == 0x80)
		{
			twoByte[i + 1] = true;
			i++;
		}
	}

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
					is2Byte = false;
					if (1 < len && twoByte[len - 1])
					{
						twoByte[len - 1] = false;
						string[len - 2] = '\0';
						is2Byte = true;
						printf("\b\b  \b\b");
					}
					if (!is2Byte)
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
						twoByte[len + 1] = true;
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
	free(twoByte);
	return string;
}