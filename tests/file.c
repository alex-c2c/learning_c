#include "file.h"
#include "../include/errno.h"
#include "../include/file.h"
#include <stdint.h>
#include <stdio.h>

#include <limits.h>
#include <unistd.h>

void test_file(void) {
    printf("test_file: Start\n");

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("[Debug][file] test_file: cwd - '%s'\n", cwd);
    } else {
        fprintf(stderr, "[Error][file] test_file: unable to get cwd\n");
        exit(ERROR_GET_CWD);
    }

    /* this path CAN be relative to where the program is run! */
    char input_file_path[PATH_MAX];
    sprintf(input_file_path, "%s/%s", cwd, "data/input_tile_data.txt");
    char output_file_path[PATH_MAX];
    sprintf(output_file_path, "%s/%s", cwd, "data/output_tile_data.txt");

    char ***data = malloc(sizeof(char **));
    if (data == NULL) {
        fprintf(stderr, "[Error][test_file] test_file: unable to malloc data\n");
        exit(ERROR_MALLOC_FAILED);
    }

    size_t line_count = 0;
    int read_result = file_read(data, &line_count, input_file_path);

    if (read_result != 0) {
        printf("[Error][test_file] test_file: unable to read from file\n");
        return;
    }

    printf("test_file: data pointer = %p\n", data);
    printf("test_file: *data pointer = %p\n", *data);
    printf("test_file: **data pointer = %p\n", **data);
    file_print_data(*data, line_count);

    int write_result = file_write(*data, line_count, output_file_path);

    /* free the lines (char*) */
    for (size_t i = 0; i < line_count; i++) {
        free((*data)[i]);
    }

    /* free the array holding the lines (char**) */
    free(*data);

    /* free the pointer holding the address of the array (char***) */
    free(data);
}
