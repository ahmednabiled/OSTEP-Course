#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    char current_char = '\0';
    int count = 0;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            
            printf("wzip: cannot open file %s\n", argv[i]);
            exit(1);
        }
        
        char buffer[4096];  
        size_t bytes_read;  

        while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
            for (size_t j = 0; j < bytes_read; j++) {
                char c = buffer[j];

                
                if (count == 0 || c != current_char) {
                    if (count > 0) {
                        
                        fwrite(&count, sizeof(int), 1, stdout);
                        fwrite(&current_char, sizeof(char), 1, stdout);
                    }
                    
                    current_char = c;
                    count = 1;
                } else {
                    
                    count++;
                }
            }
        }

        fclose(fp);
    }

    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&current_char, sizeof(char), 1, stdout);
    }

    return 0;
}
