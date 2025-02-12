#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_in_file(const char *search_term, FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    
    while (getline(&line, &len, fp) != -1) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);  
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
   
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    const char *search_term = argv[1];

    
    if (argc == 2) {
        search_in_file(search_term, stdin);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            
            search_in_file(search_term, fp);
            fclose(fp);
        }
    }

    return 0;
}
