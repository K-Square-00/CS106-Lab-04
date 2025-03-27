#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void f1()
{
	printf("\ninside f1()\n");

	int b1 = 444; // 444 == 0x1bc
	int b2 = 888; // 888 == 0x378
	char b3 = 'f'; // 'f' == 0x66
	char b4[5] = "abcd";
	int b5 = 4605768; // 4605768 == 0x00464748

	int* p1 = NULL;
	int* p2 = NULL;

	p1 = &b1;
	p2 = &b2;


	printf("    b1 = %d, b2 = %d, b3 = %c, b4 = %s, b5 = 0x%x\n", b1, b2, b3, b4, b5);

	printf("\n    before p1 == p2:\n");
	printf("    p1 = %p, p2 = %p\n", p1, p2);
	printf("   *p1 = %d, *p2 = %d\n", *p1, *p2);

	p1 = p2;

	printf("\n    after p1 == p2:\n");
	printf("    p1 = %p, p2 = %p\n", p1, p2);
	printf("   *p1 = %d, *p2 = %d\n", *p1, *p2);
}


// Copy string to another string, no overflow
void f2a()
{
	printf("\ninside f2a()\n");

	char r1[8] = "UUUU3UU"; // 'U' == 0x55, '3' == 0x33
	char r2[8] = "ffff3ff"; // 'f' == 0x66
	char r3[16] = "wwww3"; // 'w' == 0x77

	printf("    before copying\n");
	printf("    r1 = %s\n", r1);
	printf("    r2 = %s\n", r2);
	printf("    r3 = %s\n", r3);

	// copy the string in r3 to r1
	int i = 0;
	while (r3[i] != '\0') {
		r1[i] = r3[i];
		i++;
	}
	r1[i] = '\0';

	printf("\n    after copying\n");
	printf("    r1 = %s\n", r1);
	printf("    r2 = %s\n", r2);
	printf("    r3 = %s\n", r3);

}

// Copy string to another string, overflow
void f2b()
{
        printf("\ninside f2b()\n");

		char r1[8] = "UUUU3UU"; // 'U' == 0x55, '3' == 0x33
        char r2[8] = "ffff3ff"; // 'f' == 0x66
        char r3[16] = "wwww3wwww3wwww3"; // 'w' == 0x77

        printf("    before copying\n");
        printf("    r1 = %s\n", r1);
        printf("    r2 = %s\n", r2);
        printf("    r3 = %s\n", r3);

        // copy the string in r3 to r1
        int i = 0;
        while (r3[i] != '\0') {
                r1[i] = r3[i];
                i++;
        }
        r1[i] = '\0';

        printf("\n    after copying\n");
        printf("    r1 = %s\n", r1);
        printf("    r2 = %s\n", r2);
        printf("    r3 = %s\n", r3);

}


// Read the contents of a file named input into buf, then copy a string from buf into y.s1
void f3() 
{
	printf("\ninside f3()\n");

	struct {
		char s1[8];
		int  i1;
		char c1;
	} y;

	// Initialize the struct y
	strcpy(y.s1, "abcd"); // abcd\0 == 0x61 0x62 0x63 0x64 0x00
	y.i1 = 4660; // 4660 == 0x1234
	y.c1 = 'f';  // 'f'  == 0x66 

	char buf[16] = { '\0' };

	{
		// Don't try to understand every single line of code inside this block
		// Just understand that this opens a file and reads its contents into buf

		// Try to open a file named "input" and read its contents into buf
		FILE* fp = NULL;
		fp = fopen("input", "rb");

		// If the file was not found, return
		if (fp == NULL) {
			printf("    input not found\n");
			return;
		}

		// Read the contents of the file into buf
		// sizeof(char) == 1 , sizeof(buf) == 16
		int num_bytes_read = fread(buf, sizeof(char), sizeof(buf), fp);
		printf("    num_bytes_read = %d\n", num_bytes_read);
	}

	// Copy the contents of buf to s1
	strcpy(y.s1, buf);

	// Print variable values
	printf("    y.s1 = %s\n", y.s1);
	printf("    y.i1 = %d\n", y.i1);
	printf("    y.c1 = %c\n", y.c1);

	// Print buf in hex
	printf("\n    Contents of buf, in hex:\n");
	for (int i = 0; i < sizeof(buf); i++) {
		if (i % 8 == 0) {
			printf("\n    ");
		}
		printf("0x%.2x    ", (unsigned char) buf[i]);
	}
	printf("\n");
}


int main(int argc, char* argv[])
{
	int a1 = 123;
	int a2 = 567;

	printf("\ninside main()\n");
	printf("    a1 = %d, a2 = %d\n", a1, a2);

	f1();
	f2a();
	f2b();
	f3();

	return 0;
}
