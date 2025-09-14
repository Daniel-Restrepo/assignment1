// main.c
// reads test cases from A1_tests_File.txt and runs three main functions:
//   i.   div_convert
//   ii.  sub_convert
//   iii. print_tables
//
// for conversion tests: compares actual vs expected; prints PASS/FAIL.
// At the end: prints a summary of conversion tests.

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

// trims spaces/tabs at the start of a string
static char* ltrim(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    return s;
}

int main(void) {
    // opens test file
    const char *filenames[] = {
        "a1_test_file.txt",
        NULL
    };

    FILE *fp = NULL;
    for (int i = 0; filenames[i]; ++i) {
        fp = fopen(filenames[i], "r");
        if (fp) {
            printf("Opened test file: %s\n\n", filenames[i]);
            break;
        }
    }
    if (!fp) {
        //catch for not finding error
        printf("Error: Could not open test file.\n");
        return 1;
    }

    char line[256];
    int conv_total = 0;  // total conversion tests
    int conv_passed = 0; // conversion tests passed

    while (fgets(line, sizeof(line), fp)) {
        char *p = ltrim(line);

        // Skip comments (anything that is #) and blank lines
        if (*p == '\0' || *p == '\n' || *p == '#')
        continue;

        char func_name[32] = {0};
        if (sscanf(p, "%31s", func_name) != 1)
        continue;

        if (strcmp(func_name, "div_convert") == 0) {
            uint32_t n = 0;
            int base = 10;
            char expected[128] = {0};
            if (sscanf(p + strlen(func_name), "%u %d %127s", &n, &base, expected) == 3) {
                char got[128];
                div_convert(n, base, got);

                conv_total++;
                if (strcmp(expected, got) == 0) {
                    printf("div_convert(%u, %d): expected=%s got=%s  [PASS]\n", n, base, expected, got);
                    conv_passed++;
                } else {
                    printf("div_convert(%u, %d): expected=%s got=%s  [FAIL]\n", n, base, expected, got);
                }
            }
        } else if (strcmp(func_name, "sub_convert") == 0) {
            uint32_t n = 0;
            int base = 10;
            char expected[128] = {0};
            if (sscanf(p + strlen(func_name), "%u %d %127s", &n, &base, expected) == 3) {
                char got[128];
                sub_convert(n, base, got);

                conv_total++;
                if (strcmp(expected, got) == 0) {
                    printf("sub_convert(%u, %d): expected=%s got=%s  [PASS]\n", n, base, expected, got);
                    conv_passed++;
                } else {
                    printf("sub_convert(%u, %d): expected=%s got=%s  [FAIL]\n", n, base, expected, got);
                }
            }
        } else if (strcmp(func_name, "print_tables") == 0) {
            uint32_t n = 0;
            if (sscanf(p + strlen(func_name), "%u", &n) == 1) {
                printf("\n=== print_tables(%u) ===\n", n);
                print_tables(n);
                printf("[end print_tables]\n\n");
            }
        }
    }

    fclose(fp);

    // Summary for the conversion tests
    printf("\nSummary: %d/%d conversion tests passed, %d failed\n", conv_passed, conv_total, conv_total - conv_passed);

    return 0;
}