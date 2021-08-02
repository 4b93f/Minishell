/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:59:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/30 18:58:26 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    assert(argc == 2);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Le fils lit dans le tube */
        close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */

        

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {                    /* Le père écrit argv[1] dans le tube */
        close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);       /* Le lecteur verra EOF */
        wait(NULL);             /* Attente du fils */
        exit(EXIT_SUCCESS);
    }
}