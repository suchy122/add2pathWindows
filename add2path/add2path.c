#include <direct.h> // _getcwd
#include <stdlib.h> // free, perror
#include <stdio.h>  // printf
#include <string.h> // strlen

char cwd[1024];
char* pPath;
char full[_MAX_PATH];

void getCwd() {
    getcwd(cwd, sizeof(cwd));
}

void getPath() {
    pPath = getenv("PATH");
}

void delPath() {
    printf("Path istnieje, usuwanie");
    char cmd[1024] = "setx /M PATH \"%PATH:";
    strcat(cmd, cwd);
    strcat(cmd, ";");
    strcat(cmd, "=%");
    strcat(cmd, "\"");
    system(cmd);
}

void addPath() {
    printf("Path nie istnieje, dodawanie");
    char cmd[1024] = "setx /M PATH \"%PATH%;";
    strcat(cmd, cwd);
    strcat(cmd, "\"");
    system(cmd);
}

void delPath2(char* src) {
    printf("Path istnieje, usuwanie\n");
    char cmd[1024] = "setx /M PATH \"%PATH:";
    _fullpath(cwd, src, _MAX_PATH);
	printf("%s",cwd);
    strcat(cmd, cwd);
    strcat(cmd, ";");
    strcat(cmd, "=%");
    strcat(cmd, "\"");
    system(cmd);
}

void addPath2(char* src) {
    printf("Path nie istnieje, dodawanie\n");
    char cmd[1024] = "setx /M PATH \"%PATH%;";
	_fullpath(cwd, src, _MAX_PATH);
	printf("%s",cwd);
    strcat(cmd, cwd);
    strcat(cmd, "\"");
    //printf(cmd);
    system(cmd);
}

int main(int argc, char* argv[])
{
    getPath();
    if (argc == 1)
    {
        printf("Korzystanie z aktualnego katalogu:\n");
        getCwd();
        if (strstr(pPath, cwd) != NULL) {
            delPath();
        }
        else {
            addPath();
        }
    }
    else if (argc == 2)
    {
        printf("Korzystanie z podanego katalogu:\n");
        char* src = argv[1];
        _fullpath(cwd, src, _MAX_PATH);
        if (strstr(pPath, cwd) != NULL) {
            delPath2(src);
        }
        else {
            addPath2(src);
        }
    }
    else
    {
        perror("Invalid amount of arguments!\n");
        exit(EXIT_FAILURE);
    }

}

