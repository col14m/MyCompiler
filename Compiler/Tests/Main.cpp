#define _CRT_SECURE_NO_WARNINGS

#include "../Sources/BinaryTree.h"
#include "../Sources/LingAnaliz.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

char *FileInBuf(char* fileName)
{
	struct _stat info;
	int fh = 0, result = 0;
	
	if ((fh = _open(fileName, _O_RDONLY)) == -1)
	{
		printf("+\n");
		return NULL;
	}

	result = _fstat(fh, &info);
	if (result != 0)
	{
		printf("res\n");
		return NULL;
	}
	printf("%ld\n", info.st_size);
	char *buf = (char*)calloc(info.st_size + 1, sizeof(char));
	if (buf == NULL)
		return NULL;
	printf ("%d", _read(fh, buf, info.st_size));
	//buf[info.st_size] = '\0';
	_close(fh);
	printf("%s", buf);
	return buf;


}
int main()
{
	typedef BinaryTreeNode Node;
	//Node t1(NodeValue(NUMBER, 2)), t2(NodeValue(OPERAND, "sin")), *t3 = new Node(NodeValue(VARIABLE, "x")), *t4 = new Node(NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	//t2.InsertLeft(t4);
	//t2.InsertRight(t3);
	//t2.DumpToGraph("testGraph");
	//printf("%d", IsComparison("fywufu843"));
	//char *test = "x = 5 + 2 ; while ( x < 5 ) { x = x + 5 ; }";
	//LingAnaliz t;
	//t.ParseTextAndConvertToArrayNodes(test);
	//printf("%s", FileInBuf(".\\Logs\\test.txt"));
	LingAnaliz analiz("while ( x < 2 ) //ahsjhaj");
	analiz.ParseTextAndConvertToArrayNodes();
	analiz.Dump();
	


	
	system("pause");
	return 0;
}
