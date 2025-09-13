#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


#define pic picoshell


#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"


void print_test_header(const char *test_name);
void print_result(const char *test_name, int expected, int actual);
void test_single_command(void);
void test_two_stage_pipeline(void);
void test_three_stage_pipeline(void);
void test_ls_grep_pipeline(void);
void test_complex_pipeline(void);
void test_failing_command(void);
void test_pipeline_with_failure(void);
void test_empty_commands(void);
void test_cat_with_stdin(void);
void test_number_processing(void);
void run_interactive_test(void);


int picoshell1(char **cmds[]);
int picoshell2(char **cmds[]);
int picoshell3(char **cmds[]);
int picoshell4(char **cmds[]);
int picoshell5(char **cmds[]);
int picoshell6(char **cmds[]);
int picoshell7(char **cmds[]);
int picoshell8(char **cmds[]);
int picoshell(char **cmds[]);

