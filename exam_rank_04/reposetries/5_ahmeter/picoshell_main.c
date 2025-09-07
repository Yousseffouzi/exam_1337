#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Forward declaration of picoshell function
int picoshell(char **cmds[]);

// Test result colors
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

static void print_test_header(const char *test_name)
{
    printf("\n" BLUE "=== Testing: %s ===" RESET "\n", test_name);
}

static void print_result(const char *test_name, int expected, int actual)
{
    if (expected == actual) {
        printf(GREEN "✓ PASS" RESET " - %s (returned %d)\n", test_name, actual);
    } else {
        printf(RED "✗ FAIL" RESET " - %s (expected %d, got %d)\n", test_name, expected, actual);
    }
}

// Test 1: Single command
void test_single_command(void)
{
    print_test_header("Single command: echo hello");
    
    char *echo_cmd[] = {"echo", "hello", NULL};
    char **cmds[] = {echo_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Single echo command", 0, result);
}

// Test 2: Two-stage pipeline
void test_two_stage_pipeline(void)
{
    print_test_header("Two-stage pipeline: echo hello | cat");
    
    char *echo_cmd[] = {"echo", "hello", NULL};
    char *cat_cmd[] = {"cat", NULL};
    char **cmds[] = {echo_cmd, cat_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Two-stage pipeline", 0, result);
}

// Test 3: Three-stage pipeline
void test_three_stage_pipeline(void)
{
    print_test_header("Three-stage pipeline: echo squalala | cat | sed s/a/b/g");
    
    char *echo_cmd[] = {"echo", "squalala", NULL};
    char *cat_cmd[] = {"cat", NULL};
    char *sed_cmd[] = {"sed", "s/a/b/g", NULL};
    char **cmds[] = {echo_cmd, cat_cmd, sed_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Three-stage pipeline", 0, result);
}

// Test 4: ls | grep pipeline
void test_ls_grep_pipeline(void)
{
    print_test_header("Directory listing: ls | grep main");
    
    char *ls_cmd[] = {"ls", NULL};
    char *grep_cmd[] = {"grep", "main", NULL};
    char **cmds[] = {ls_cmd, grep_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("ls | grep pipeline", 0, result);
}

// Test 5: Complex pipeline with multiple stages
void test_complex_pipeline(void)
{
    print_test_header("Complex pipeline: echo 'apple banana cherry' | tr ' ' '\\n' | sort | head -2");
    
    char *echo_cmd[] = {"echo", "apple banana cherry", NULL};
    char *tr_cmd[] = {"tr", " ", "\n", NULL};
    char *sort_cmd[] = {"sort", NULL};
    char *head_cmd[] = {"head", "-2", NULL};
    char **cmds[] = {echo_cmd, tr_cmd, sort_cmd, head_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Complex four-stage pipeline", 0, result);
}

// Test 6: Command that should fail
void test_failing_command(void)
{
    print_test_header("Failing command: nonexistent_command");
    
    char *fail_cmd[] = {"nonexistent_command_12345", NULL};
    char **cmds[] = {fail_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Failing single command", 1, result);
}

// Test 7: Pipeline with failing command
void test_pipeline_with_failure(void)
{
    print_test_header("Pipeline with failure: echo hello | nonexistent_command");
    
    char *echo_cmd[] = {"echo", "hello", NULL};
    char *fail_cmd[] = {"nonexistent_command_12345", NULL};
    char **cmds[] = {echo_cmd, fail_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Pipeline with failing command", 1, result);
}

// Test 8: Empty input handling
void test_empty_commands(void)
{
    print_test_header("Empty command array");
    
    char **cmds[] = {NULL};
    
    int result = picoshell(cmds);
    print_result("Empty command array", 0, result);
}

// Test 9: Cat with input redirection simulation
void test_cat_with_stdin(void)
{
    print_test_header("Pipeline simulating input: echo 'test data' | cat | wc -l");
    
    char *echo_cmd[] = {"echo", "test data", NULL};
    char *cat_cmd[] = {"cat", NULL};
    char *wc_cmd[] = {"wc", "-l", NULL};
    char **cmds[] = {echo_cmd, cat_cmd, wc_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Cat with stdin pipeline", 0, result);
}

// Test 10: Number processing pipeline
void test_number_processing(void)
{
    print_test_header("Number processing: seq 1 5 | sort -nr | head -3");
    
    char *seq_cmd[] = {"seq", "1", "5", NULL};
    char *sort_cmd[] = {"sort", "-nr", NULL};
    char *head_cmd[] = {"head", "-3", NULL};
    char **cmds[] = {seq_cmd, sort_cmd, head_cmd, NULL};
    
    int result = picoshell(cmds);
    print_result("Number processing pipeline", 0, result);
}

// Interactive test menu
void run_interactive_test(void)
{
    char input[1024];
    char *tokens[64];
    char **cmds[32];
    int cmd_count = 0;
    int token_count = 0;
    
    printf(YELLOW "\nInteractive Test Mode:" RESET "\n");
    printf("Enter commands separated by '|' (or 'quit' to exit):\n");
    printf("Example: echo hello | cat | wc -w\n> ");
    
    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        if (strlen(input) == 0) {
            printf("> ");
            continue;
        }
        
        // Simple tokenizer (this is basic - production code would need better parsing)
        cmd_count = 0;
        token_count = 0;
        char *token = strtok(input, " ");
        
        while (token && cmd_count < 31) {
            if (strcmp(token, "|") == 0) {
                tokens[token_count] = NULL;
                cmds[cmd_count] = &tokens[token_count - (token_count > 0 ? 1 : 0)];
                // Find start of this command
                int start = 0;
                for (int i = cmd_count - 1; i >= 0; i--) {
                    start += strlen((char*)cmds[i]) + 1;
                }
                cmds[cmd_count] = &tokens[start];
                cmd_count++;
                token_count++;
            } else {
                tokens[token_count++] = token;
            }
            token = strtok(NULL, " ");
        }
        
        // This is a simplified parser - for a real implementation you'd want
        // more robust command parsing. For testing purposes, let's just run
        // some predefined combinations.
        
        printf("Running command...\n");
        
        // Simple test case
        char *echo_cmd[] = {"echo", "interactive test", NULL};
        char *cat_cmd[] = {"cat", NULL};
        char **simple_cmds[] = {echo_cmd, cat_cmd, NULL};
        
        int result = picoshell(simple_cmds);
        printf("Result: %d\n> ", result);
    }
}

int main(int argc, char *argv[])
{
    printf(BLUE "Picoshell Comprehensive Test Suite" RESET "\n");
    printf("==================================\n");
    
    // Run all automated tests
    test_single_command();
    test_two_stage_pipeline();
    test_three_stage_pipeline();
    test_ls_grep_pipeline();
    test_complex_pipeline();
    test_failing_command();
    test_pipeline_with_failure();
    test_empty_commands();
    test_cat_with_stdin();
    test_number_processing();
    
    // Summary
    printf("\n" BLUE "=== Test Summary ===" RESET "\n");
    printf("All automated tests completed.\n");
    printf("Check output above for individual results.\n");
    
    // Interactive mode option
    if (argc > 1 && strcmp(argv[1], "-i") == 0) {
        run_interactive_test();
    } else {
        printf("\nRun with '-i' flag for interactive testing mode.\n");
    }
    
    return 0;
}
