/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:18:08 by vzurera-          #+#    #+#             */
/*   Updated: 2023/12/13 23:18:08 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

# define NC   		"\x1b[0m"
# define BLACK   	"\x1b[30m"
# define RED     	"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE   	"\x1b[37m"

static void test_get_next_line(int fd, int end)
{
    char    *line;

    while ((line = get_next_line(fd)) != NULL)
        free(line);
    if (line != NULL)
        printf(RED"KO  "NC);
    else
        printf(GREEN"OK  "NC);
    if (end)
        printf("\n");
}

int main(void)
{
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) return 1;
    char file_path[256];

    int fd1;

    printf("\t");
    fd1 = open("./non_existing_file.txt", O_RDONLY);
    if (fd1 < 0) 
        printf(GREEN"OK  "NC);
    else
    {
        printf(RED"KO  "NC);
        close(fd1);
    }

    test_get_next_line(42, 0);

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/empty", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }
    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/1byte", home_dir);
    fd1 = open(file_path, O_RDONLY);
     if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }
    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/2byte", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/41_no_nl", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/42_with_nl", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/alternate_line_nl_with_nl", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/big_line_no_nl", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  "NC);
    else
    {
        test_get_next_line(fd1, 0);
        close(fd1);
    }

    snprintf(file_path, sizeof(file_path), "%s/francinette/tests/get_next_line/gnlTester/files/big_line_with_nl", home_dir);
    fd1 = open(file_path, O_RDONLY);
    if (fd1 < 0) 
        printf(RED"KO  \n"NC);
    else
    {
        test_get_next_line(fd1, 1);
        close(fd1);
    }
    return (0);
}
