#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define BUFFER_SIZE_WRITE 1024

int pythonObfuscator ( char *fileName ) {
    
    char buffer[BUFFER_SIZE];
    char buffer_write[BUFFER_SIZE_WRITE];
    char *python_file_name = fileName;

    int python_file_descriptor = open(python_file_name, O_RDONLY);
    int python_file_descriptor_write = open(python_file_name, O_WRONLY);

    if (python_file_descriptor == -1) {
        printf("Error opening file %s\n", python_file_name);
        return -1;
    }
    
    while (read(python_file_descriptor, buffer, BUFFER_SIZE) > 0) {
        int i = 0;
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == '\n') {
                buffer_write[i] = '\n';
            } else {
                buffer_write[i] = buffer[i] ^ 0xFF;
            }
        }
        write(python_file_descriptor_write, buffer_write, BUFFER_SIZE);
    }
    close(python_file_descriptor);
    close(python_file_descriptor_write);
    return 0;

}
int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: python_obfuscator.c <file_name>\n");
        return -1;
    }
    pythonObfuscator(argv[1]);
    return 0;
}
