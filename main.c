#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM_OF_TRIES_ON_DRAWING 100000
#define BLANK ' '


//  Function prototypes
void printBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols]);

void initialiseBoard(int lines, int cols, char board[lines][cols]);

void printOptions();

void drawOnBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols]);

void cleanStdin(void);


int main()
{
    char board[20][80];

    initialiseBoard(20, 80, board);

    srand(time(NULL));

    while (true)
    {
        printOptions();


        int figureType = -1;

        printf("Digite o tipo de figura basica desejada:\n");
        if (!scanf("%d", &figureType) && figureType < 1 || figureType > 3)
        {
            printf("Invalid option.\n");
            cleanStdin();
            continue;
        }


        int numFigures = 0;

        printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio):\n");

        if (!scanf("%d", &numFigures))
        {
            printf("Invalid option.\n");
            cleanStdin();
            continue;
        }
        else if (figureType <= 0)
        {
            numFigures = (rand() % 100) + 1;
        }
        else if (numFigures > 100)
        {
            numFigures = 100;
        }


        drawOnBoard(figureType, numFigures, 20, 80, board);
        printBoard(figureType, numFigures, 20, 80, board);

        break;
    }

    return 0;
}


/*
 *  Initialises the board with determined characters.
 *
 *  @param     board     pointer for the matrix.
 *  @param     lines     number of lines.
 *  @param     cols      number of columns.
 */
void initialiseBoard(int lines, int cols, char board[lines][cols])
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((i % (lines - 1)) == 0)
            {
                board[i][j] = '-';
            }
            else if ((j % (cols - 1)) == 0)
            {
                board[i][j] = '|';
            }
            else
            {
                board[i][j] = BLANK;
            }
        }
    }
}


void drawOnBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols])
{
    int numberOfTries = 0;
    int totalDrawnFigures = 0;

    while (numberOfTries < MAX_NUM_OF_TRIES_ON_DRAWING && totalDrawnFigures < numFigures)
    {
        int randomLine = rand() % lines;
        int randomColumn = rand() % cols;

        if (board[randomLine][randomColumn] != BLANK)
        {
            numberOfTries++;
            continue;
        }

        board[randomLine][randomColumn] = '*';
        totalDrawnFigures++;
    }
}


/*
 *  Prints board out.
 *
 *  @param     board     pointer for the matrix.
 *  @param     lines     number of lines.
 *  @param     cols      number of columns.
 */
void printBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols])
{
    printf("\nValores: tipo de figura: %d, número de figuras: %d\n", figureType, numFigures);

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", board[i][j]);
        }

        printf("\n");
    }
}


/*
 *  Prints the menu out.
 */
void printOptions()
{
    printf("PROGRAMA GERADOR DE OBRA DE ARTE:\n"
           "=================================\n"
           "Escolha o tipo de figura basica a ser usada para criar a obra:\n"
           "1 - asterisco simples.\n"
           "2 - simbolo de soma com asteriscos.\n"
           "3 - letra X com asteriscos.\n"
           "4 - figuras aleatorias\n"
           "5 ou qualquer outro numero – opcao de obra de arte criada pelo aluno\n");
}


/*
 *  Clears stdin to avoid problems with the "scanf()" function.
 */
void cleanStdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}