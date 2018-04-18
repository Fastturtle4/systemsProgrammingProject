/* Skeletal project 1 for CS270, according to the specifications of Spring 2018
   Author: Raphael Finkel 12/2017
*/

//Paul Barrett
//prog1.c

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define ERRMSG 50
#define FOUR 4

//handle the p command
void commandP(const char stringfile[], int length){
	char output[length*2];	//initialize char array of length*2 (to be safe)
	int lengthoffile;	//create int value to store length of the file
	FILE *file;		//create file
	file = fopen(stringfile, "r");	//open file
	fseek(file, 0L, SEEK_END);
	lengthoffile = ftell(file);	//go to end of file, store length in lengthoffile variable using ftell
	fseek(file, 0L, SEEK_SET);	//move position back to beginning of the file
	if(length<=lengthoffile){	//if length is not too large, read each byte into output and then print
		fread(output, length, 1, file);
		printf("%s\n", output);
	} else {			//if requested length is too long, give error message
		printf("File %s is not long enough for input: %i\n", stringfile, length);
	}
	fclose(file);		//close the file
}
//handle the L command
void commandL(const char stringfile[], int length){
	FILE *file;			//create file
	file = fopen(stringfile, "r");	//open file
	int offset;			//create offset int
	fseek(file, 0L, SEEK_END);
	offset = ftell(file);		//store length of file in offset using ftell and fseek
	if(length <= offset){		//if length is not too large, create char array output, set position in file to
		char output[length*2];	//offset - length (length of file - requested length) and then
		fseek(file, offset-length, SEEK_SET);	//read from that position to the end of the file and store in output
		fread(output, length, 1, file);		//finally, print output
		printf("%s\n", output);
	} else {			//if requested length is too long, give error message
		printf("File %s is not long enough for input: %i\n", stringfile, length);
	}
	fclose(file);		//close the file
}
//handle the i command
void commandI(const char stringfile[], int length){
	int output[length]; 		//create int array of size length
	FILE *file;			//create file
	file = fopen(stringfile, "r");	//open file
	fseek(file, 0L, SEEK_END);	//find length of file and store in int lengthoffile 
	int lengthoffile = ftell(file);
	if (lengthoffile/FOUR >= length){	//if the requested length is not larger than the length of the file divided by 4
		fseek(file, 0L, SEEK_SET);	//set position back to the beginning
		fread(&output, FOUR*length, 1, file);	//read every 4 bytes and store in output
		for(int i = 0; i < length; i+=1){	//print the output array with a space between each number using for loop
			printf("%i ", output[i]);
		}	
	} else {					//if requested length is too long, give error message
		printf("File %s is not long enough for input: %i\n", stringfile, length);
	}
	printf("\n");	//print newline 
	fclose(file);	//close the file
}
//handle the x command
void commandX(const char stringfile[], int length){
	int output[length];			//create int output array of size length
	FILE *file;				//create file
	file = fopen(stringfile, "r");		//open file
	fseek(file, 0L, SEEK_END);		//find length of file and store in lengthoffile
	int lengthoffile = ftell(file);
	unsigned int buffer[length];		//create unsigned int array of size length called buffer
	if (lengthoffile >= length){		//if the requested length is not too long
		fseek(file, 0L, SEEK_SET);	//read into output array
		fread(&output, length, 1, file);
		buffer[0] = output[0];		//set buffer[0] to output [0]
		for(int i = 1; i < length-1; i+=1){		//populate buffer with buffer[i] XOR output[i+1]
			buffer[i] = buffer[i]^output[i+1];
		}
		printf("%03o\n", buffer[length]);	//print the last element of buffer in octal with size 3
	} else {					//if requested length is too long, give error message
		printf("File %s is not long enough for input: %i\n", stringfile, length);
	}
	printf("\n");	//print newline
	fclose(file);	//close the file
}

void handleCommands(const char *argv[]) {
	char line[MAXLINE];
	while (1) { // each command
		(void) fgets(line, MAXLINE, stdin);
		int length, errorScan;				//create length and errorScan ints
		errorScan = sscanf(line, "%*s%i", &length);	//read command, store length into length int
		char errormsg1[ERRMSG] = "Incorrect format. Use [command] [positive number]\n";	//error message for incorrect format
		
		switch (line[0]) {
			case 'q': exit(0); //exit command
				  break;
				  
			case 'e': printf("%s\n", argv[0]); 	//print name of program (argv[0])
				  break;

			case 'p': if(errorScan != 1 || length<0) {printf("%s", errormsg1); break;}	//errorScan will have 1 argument for correct input
				  commandP(argv[1], length);				//if errorScan != 1 or length is negative show errormessage and break
				  break;						//otherwise, call commandP function

			case 'L': if(errorScan != 1 || length<0) {printf("%s", errormsg1); break;}	//" ..... "
				  commandL(argv[1], length);				//otherwise, call commandL function
				  break;

			case 'i': if(errorScan != 1 || length<0) {printf("%s", errormsg1); break;}	//" ..... "
				  commandI(argv[1], length);				//otherwise, call commandI function
				  break;

			case 'x': if(errorScan != 1 || length<0) {printf("%s", errormsg1); break;}	//" ..... "
				  commandX(argv[1], length);				//otherwise, call commandX function
				  break;

			default:  printf("Unrecognized command. Choices are q, e, p, L, i, and x\n"); break; //if no valid command is given
		} // switch line[0]									     //show error message
	} // each command
} // handleCommands

int main(int argc, const char *argv[]) {
	handleCommands(argv);
} // main
