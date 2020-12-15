#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <sys/statvfs.h>
#include <time.h>

//
// Disk wiper and obfuscator
//
// by GerH, Dec 2020
//
char* randomString(int size, bool moreASCII) {
    int i;
    char *res = malloc(size + 1);
    for(i = 0; i < size; i++) {
	if(moreASCII){
		res[i] = 'A' + (random() % 126);
	}
	else
		res[i] = 'A' + (random() % 26);
    }
    res[i] = '\0';
    return res;
}

// create a random filename. mp4 file with (current date - random up to 5 years back) in its name.
char* randomFilename(){
	//Format: YYYYmmdd_hhmmss.mp4
	//5y in secs = 157852800

	time_t mytime;
	mytime = time(NULL);
	// random int between 0 and 157852800
	int randDeduction = rand() % 157852800;
	mytime = mytime - randDeduction;
	//printf(ctime(&mytime));//zB   Wed Dec 26 08:13:35 2018

    	struct tm* current_time;
    	current_time = localtime(&mytime);

	char filename[1000] = "";
	snprintf( filename, sizeof(filename), "%d%02d%02d_%02d%02d%02d.mp4", 
		(current_time->tm_year + 1900), 
		(current_time->tm_mon + 1), 
		current_time->tm_mday, 
		current_time->tm_hour,
		current_time->tm_min,
		current_time->tm_sec);

	char* filenameNoLo = malloc (sizeof (char) * 1000);
	strcpy(filenameNoLo, filename);
	//printf("filenameNoLo: %s\n", filenameNoLo);
	return filenameNoLo;
}

bool quitProgram(char str[1000]){
	if(str[0] == '\0')
		printf("\nCommand not recognized!\n");
	else
		printf("\nCommand \"%s\" not recognized!\n", str);
	return 0;
}

int main()
{
	printf("#############################\n");
	printf("# Disk wiper and obfuscator #\n");
	printf("#                           #\n");
	printf("# by GerH, 2020             #\n");
	printf("#############################\n");
	printf("type 'man' for info\n");

	while(true){
		// user input
		char str[1000]; 
		scanf("%[^\n]%*c", str); 
		printf(">%s", str); 

		if(strcmp(str, "man") == 0){
			printf("\nman  - manual\n");
			printf("quit - exit program\n");
			printf("wipe - wipe deleted files on a disk\n");
			printf("  usage:     wipe <PATH> (-co/-ro) (-wr/-wf) <num1> (-r) <num2>\n");
			printf("  example 1: wipe \"/media/amnesia/Lego USB\" -co -wr 1\n");
			printf("  example 2: wipe /media/amnesia/LegoUSB -ro -wf 3\n");
			printf("  example 2: wipe /media/amnesia/LegoUSB -ro -wf 1 -r 5000\n");
			printf("  <PATH>    - path to a folder on the disk that should be used for the disk wipe operation.\n");
			printf("  -co       - clear overwrite (whitespaces in a file)\n");
			printf("  -ro       - random overwrite (random ascii characters in a file)\n");
			printf("  -wr       - write random (filenames are random)\n");
			printf("  -wf       - write filenames (use fake filenames [obfuscate data])\n");
			printf("  <num1>    - number of overwrites (rounds)\n");
			printf("  <num2>    - optional: How much space to overwrite. In GB. Per deafult, up to 1 TB will be overwritten. (smallest size: 0.1 GB)\n");
			printf("  -r        - optional: use more random file sizes\n");
		}
		else if(strcmp(str, "quit") == 0 || strcmp(str, "exit") == 0){
			return 0;
		}
		else{
			// user choice:
			char inputPath[1000] = "";
			bool clearOverwrite = false;
			bool writeFilenames = false;
			int roundNum = 1;   		// number of overwrites
			bool randomFileSizes = false;
			int totalSize = 10000; 		// totalSize * 100 MB  will be overwritten
			
			//check if quotation marks found
			int commandIter = 0;
			if(strchr(str, '\"') == 0){ 	//no
				int init_size = strlen(str);
				char delim[] = " ";
				char *ptr = strtok(str, delim);
				while (ptr != NULL)
				{
					if(commandIter == 0){
						//first part is "wipe"
						if(strcmp(ptr, "wipe") != 0)
							return quitProgram(ptr);
					}
					else if(commandIter == 1){
						//second part is the path
						strcpy(inputPath, ptr);
					}
					else if(commandIter == 2){
						if(strcmp(ptr, "-co") == 0)
							clearOverwrite = true;
						else if(strcmp(ptr, "-ro") == 0)
							clearOverwrite = false;
						else
							return quitProgram("");
					}
					else if(commandIter == 3){
						if(strcmp(ptr, "-wr") == 0)
							writeFilenames = false;
						else if(strcmp(ptr, "-wf") == 0)
							writeFilenames = true;
						else
							return quitProgram("");
					}
					else if(commandIter == 4)
						roundNum = atoi(ptr);
					else if(commandIter == 5){
						if(strcmp(ptr, "-r") == 0)
							randomFileSizes = true;
					}
					else if(commandIter == 6){
						double d;
						sscanf(ptr, "%lf", &d);
						totalSize = d * 10;
					}
					ptr = strtok(NULL, delim);
					commandIter++;
				}
			}
			else{				//yes
				int init_size = strlen(str);
				char delim[] = "\"";
				char *ptr = strtok(str, delim);
				while (ptr != NULL)
				{
					if(commandIter == 0){
						//remove last whitespace
						if(ptr[strlen(ptr)-1] == ' ')
							ptr[strlen(ptr)-1] = '\0';
						//first part is "wipe"
						if(strcmp(ptr, "wipe") != 0)
							return quitProgram(ptr);
					}
					if(commandIter == 1){
						//second part is the path
						strcpy(inputPath, ptr);
					}
					else if(commandIter == 2){
						//third part
						
						int init_size = strlen(ptr);
						char delim2[] = " ";

						char *ptr2 = strtok(ptr, delim2);

						while (ptr2 != NULL)
						{
							commandIter++;
							if(commandIter == 3){
								if(strcmp(ptr2, "-co") == 0)
									clearOverwrite = true;
								else if(strcmp(ptr2, "-ro") == 0)
									clearOverwrite = false;
								else
									return quitProgram("");
							}
							else if(commandIter == 4){
								if(strcmp(ptr2, "-wr") == 0)
									writeFilenames = false;
								else if(strcmp(ptr2, "-wf") == 0)
									writeFilenames = true;
								else
									return quitProgram("");
							}
							else if(commandIter == 5)
								roundNum = atoi(ptr2);
							else if(commandIter == 6){
								if(strcmp(ptr2, "-r") == 0)
									randomFileSizes = true;
							}
							else if(commandIter == 7){
								double d;
								sscanf(ptr2, "%lf", &d);
								totalSize = d * 10;
							}
							ptr2 = strtok(NULL, delim2);
						}
					}
					ptr = strtok(NULL, delim);
					commandIter++;
				}
			}
			// output the input
			printf("\n\n>input path: %s\n>clear overwrite: ", inputPath);
			if(clearOverwrite)
				printf("yes");
			else
				printf("no");

			printf("\n>write filenames: ");
			if(writeFilenames)
				printf("yes");
			else
				printf("no");
			printf("\n>number of rounds: %i\n>random file sizes: ", roundNum);
			if(randomFileSizes)
				printf("yes");
			else
				printf("no");
			printf("\n>total size: %i GB\n", (totalSize/10));
			
			
			printf("\nOverwriting deleted files, please wait");
			int totalSizeWritten = 0;
			for( int round = 0; round < roundNum; round = round + 1 ){
			
				if(roundNum > 1)
					printf("\nstarting round %i\n", round+1);

				//memory allocation
				char **tempFilepaths = (char **)malloc(totalSize * sizeof(char *)); 
				for (int z=0; z<totalSize; z++)
				     tempFilepaths[z] = (char *)malloc(500 * sizeof(char));

				//write temp files
				int numOfFiles = 0;
				bool quitApp = false;
				for( int a = 0; a < totalSize; a = a + 1 ){

					//create path with random filename
					numOfFiles++;
					char currentInputPath[1000] = "";
					strcpy(currentInputPath, inputPath);

					char* tempFileName;
					if(writeFilenames)
						tempFileName = randomFilename();
					else
						tempFileName = randomString(40, false);
					char* tempFullPath = strcat(strcat(currentInputPath, "/"), tempFileName);
		
					strcpy(tempFilepaths[a], tempFullPath);
		
					FILE *newFile = NULL;
					newFile = fopen(tempFullPath ,"a");
		
					int sz = ftell(newFile);
					int previousSz = sz;
					int fileSize = 100000000;
					if(randomFileSizes)
						fileSize = (int)(fileSize*0.9) + (rand() % (int)(fileSize*0.5));
					int iteration = 0;

					//write temp file
					while(sz < fileSize){

						//write into file
						if(clearOverwrite)
							fprintf(newFile, "                                        ");
						else
							fprintf(newFile, randomString(40, true));

						//measure temp file size
						previousSz = sz;
						fseek(newFile, 0L, SEEK_END);
						sz = ftell(newFile);
						if(iteration % 10 == 0){
							//quit conditions
							if(sz == 0 && previousSz == 0 && iteration == 0  ||  sz == previousSz && iteration > 0)
								quitApp = true;
						}
						//display one dot per overwritten MB
						if(iteration % 25000 == 0){
							printf(".");
							fflush(stdout); 
						}
						iteration++;
						if(quitApp)
							break;
					}

					//quit if no more space available
					totalSizeWritten = totalSizeWritten + (sz / 1000000);
					fclose(newFile);
					if(quitApp  ||  totalSizeWritten > (totalSize * 100))
						break;
				}

				//delete temp files
				for( int a = 0; a < numOfFiles; a = a + 1 ){
					//printf("delete (%i): %s\n", a, tempFilepaths[a]);
					//delete
					if (remove(tempFilepaths[a]) == 0) 
						;
						//printf("Deleted successfully\n"); 
					else
						printf("\nUnable to delete the temp file (%i) \"%s\". Please delete it manually. Sorry there. \n", a, tempFilepaths[a]);
				};

				//free memory
				for (int z=0; z<totalSize; z++)
					free(tempFilepaths[z]);
				free(tempFilepaths);

				if(roundNum > 1)
					printf("round %i finished!\n", round+1);
			}

			// final output & let user quit
			printf("\nProcess finished! %i MB in \"%s\" were successfully overwritten.\n", totalSizeWritten, inputPath);
			printf("\nquit? (Y/n)\n");
			char strQuit[1]; 
			scanf("%[^\n]%*c", strQuit); 
			printf(">%s\n", strQuit); 
			if(strcmp(strQuit, "quit") == 0 || strcmp(strQuit, "Y") == 0 || strcmp(strQuit, "y") == 0 || strcmp(strQuit, "exit") == 0)
				return 0;
		}
	}
	return 0;
}
