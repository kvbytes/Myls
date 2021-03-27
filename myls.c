/* 
*  myls - simplified "ls" command
*  CS 570 - Operating Systems
*  Spring 2021
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	struct dirent *dstr; // from sys/types
	DIR *dp;
	char hidden[] = "-h"; // show hidden arguments command
	char cwd[PATH_MAX]; 

	// show files for current directory
	// no arguments are given in this case
	if (argc == 1) {
		dp = opendir(".");
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		while (dstr = readdir(dp)) {
			if (dstr->d_name[0] != '.') {
				printf("%s\n", dstr->d_name);
			}
		}
	}

	// show files for other directories
	else if (argc > 1 && strcmp(argv[1], hidden)){
		int i;
		for (i = 1; i <= argc - 1; i++) {
			// error if directory doesn't exist
			if ((dp = opendir(argv[i])) == NULL) {
				printf("Cannot access %s\n", argv[i]);
			}
			// print files including directory name, no hidden files
			else {
				printf("%s\n", argv[i]);
				while (dstr = readdir(dp)) {
					if (dstr->d_name[0] != '.') {
						printf("%s\n", dstr->d_name);
					}
				}
			}
		}
	}

	// cases that show hidden files
	else {

		// show current directory files
		if (argc == 2) {
			dp = opendir(".");
			printf("%s\n", getcwd(cwd, sizeof(cwd)));
			while (dstr = readdir(dp)) {
				printf("%s\n", dstr->d_name);
			}
		}

		// show files for other/multiple directories
		else {
			// declare outside for edoras
			int i;
			for (i=2; i <= argc-1; i++) {

				// error if directory doesn't exist
				if ((dp = opendir(argv[i])) == NULL) {
					printf("Cannot access %s\n", argv[i]);
				}
				// print files including directory name
				else {
					printf("%s\n", argv[i]);
					while (dstr = readdir(dp)) {
						printf("%s\n", dstr->d_name);
					}
				}
			}
		}
	}
	closedir(dp);
}