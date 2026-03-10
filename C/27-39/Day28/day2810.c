#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    switch (n)
    {
    case 1:
        printf(
            "X\n");
        break;
    case 2:
        printf(
            "X X\n"
            " X \n"
            "X X\n");
        break;
    case 3:
        printf(
            "X X   X X\n"
            " X     X \n"
            "X X   X X\n"
            "   X X   \n"
            "    X    \n"
            "   X X   \n"
            "X X   X X\n"
            " X     X \n"
            "X X   X X\n");
        break;
    case 4:
        printf(
            "X X   X X         X X   X X\n"
            " X     X           X     X \n"
            "X X   X X         X X   X X\n"
            "   X X               X X   \n"
            "    X                 X    \n"
            "   X X               X X   \n"
            "X X   X X         X X   X X\n"
            " X     X           X     X \n"
            "X X   X X         X X   X X\n"
            "         X X   X X         \n"
            "          X     X          \n"
            "         X X   X X         \n"
            "            X X            \n"
            "             X             \n"
            "            X X            \n"
            "         X X   X X         \n"
            "          X     X          \n"
            "         X X   X X         \n"
            "X X   X X         X X   X X\n"
            " X     X           X     X \n"
            "X X   X X         X X   X X\n"
            "   X X               X X   \n"
            "    X                 X    \n"
            "   X X               X X   \n"
            "X X   X X         X X   X X\n"
            " X     X           X     X \n"
            "X X   X X         X X   X X\n");
        break;
    case 5:
        printf(
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "   X X               X X                                 X X               X X   \n"
            "    X                 X                                   X                 X    \n"
            "   X X               X X                                 X X               X X   \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "         X X   X X                                             X X   X X         \n"
            "          X     X                                               X     X          \n"
            "         X X   X X                                             X X   X X         \n"
            "            X X                                                   X X            \n"
            "             X                                                     X             \n"
            "            X X                                                   X X            \n"
            "         X X   X X                                             X X   X X         \n"
            "          X     X                                               X     X          \n"
            "         X X   X X                                             X X   X X         \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "   X X               X X                                 X X               X X   \n"
            "    X                 X                                   X                 X    \n"
            "   X X               X X                                 X X               X X   \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "                           X X   X X         X X   X X                           \n"
            "                            X     X           X     X                            \n"
            "                           X X   X X         X X   X X                           \n"
            "                              X X               X X                              \n"
            "                               X                 X                               \n"
            "                              X X               X X                              \n"
            "                           X X   X X         X X   X X                           \n"
            "                            X     X           X     X                            \n"
            "                           X X   X X         X X   X X                           \n"
            "                                    X X   X X                                    \n"
            "                                     X     X                                     \n"
            "                                    X X   X X                                    \n"
            "                                       X X                                       \n"
            "                                        X                                        \n"
            "                                       X X                                       \n"
            "                                    X X   X X                                    \n"
            "                                     X     X                                     \n"
            "                                    X X   X X                                    \n"
            "                           X X   X X         X X   X X                           \n"
            "                            X     X           X     X                            \n"
            "                           X X   X X         X X   X X                           \n"
            "                              X X               X X                              \n"
            "                               X                 X                               \n"
            "                              X X               X X                              \n"
            "                           X X   X X         X X   X X                           \n"
            "                            X     X           X     X                            \n"
            "                           X X   X X         X X   X X                           \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "   X X               X X                                 X X               X X   \n"
            "    X                 X                                   X                 X    \n"
            "   X X               X X                                 X X               X X   \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "         X X   X X                                             X X   X X         \n"
            "          X     X                                               X     X          \n"
            "         X X   X X                                             X X   X X         \n"
            "            X X                                                   X X            \n"
            "             X                                                     X             \n"
            "            X X                                                   X X            \n"
            "         X X   X X                                             X X   X X         \n"
            "          X     X                                               X     X          \n"
            "         X X   X X                                             X X   X X         \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            "   X X               X X                                 X X               X X   \n"
            "    X                 X                                   X                 X    \n"
            "   X X               X X                                 X X               X X   \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n"
            " X     X           X     X                             X     X           X     X \n"
            "X X   X X         X X   X X                           X X   X X         X X   X X\n");
        break;
    default:
        break;
    }
    return 0;
}