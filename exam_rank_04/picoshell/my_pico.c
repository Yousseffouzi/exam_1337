/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pico.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:28:04 by yofouzi           #+#    #+#             */
/*   Updated: 2025/09/09 16:46:31 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pico.h"

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
