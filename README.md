*****************************************************************
* COMP 304 Project 3 : OS File System 304 (FS304)		*
* Spring 2017							*
* Koç University						*
* Batuhan Kalender - Kutlay Hanlı				*
*****************************************************************

This is a summary since we documented our implementation while we’re coding. You can find further information about our procedures inside .h document, next to commands.

Added bool type. “typedef enum { false, true } bool;”

Added _file struct. “typedef struct 
{
	int size;
	char blocks[3][1024];
} _file;”

Added helper functions	“int compareBufferContents(char*, char*);”
			“bool requestBlocks(int, int *);”

————————————————————————————————————————————————————————————————————————

compare
•	Started compare same as ls procedure. First thought about using ls() function but since it just prints the result and doesn’t hold them, decided to reflect it instead. 

*	Command starts like ls() in order to find desired files. After a file is found, we held its block and buffer numbers in blk1,blk2 and bfr1,bfr2 variables.
Since there’re maximum of 3 blocks and 4 buffers; while testing files inside a directory with variable *k* (in for loop, until 12), block number of the file will be equal to k / 4 (k = i*4 + j where i is the block number and j is the buffer number) and buffer number of the file will be equal to k % 4.

*	We created 2 bool variables called isF1p and isF1p. When we find File 1, isF1p will be set to true, same for file 2.

*	After search operation is done, we checked whether isF1p and isF2p are true. 
	—	If yes, System will print a note saying their block and buffer numbers. Then will read those files’ information into directory entries using readFS304 command. After further information is gathered through inode bitmap, all of their content (XX,YY,ZZ) will be written into char variables of size 1024 using readFS304 method.
	**	We compared each part of the files separately (i.e. file1’s XX’s with file2’s XX’s) with our function called compareBufferContents. This function’s inputs are 2 strings. First, it compares those 2 strings’ lengths. Then checks if their *i’th* (in for loop, until smaller string’s length) char are equal. If not, result is incremented by 1.
	—	If no, system prints the name of the file that wasn’t found. 

————————————————————————————————————————————————————————————————————————

rename -used as rname because of conflict in some libraries-
*	Again, we started this command the way we did in “compare”. After we found the file/dictionary, we compared them using C’s “strncmp” function.
*	We used different ‘if’s to rename directories and files, just because we can.

————————————————————————————————————————————————————————————————————————

copy
*	Same process as rename and compare. Returns errors if they occur.
	— If requested name belongs to a directory, system prints “Copy failed.”
	— If it’s a file; 
		— First system reads its source file, finds how many blocks are used. Then requests that many blocks. Also requests for inodes.
		— Looks whether there’s place in current directory, requests blocks if needed.
		— If error occurs during this operations, returns borrowed and unused resources.
		— After copying, it updates both block maps and inode table.