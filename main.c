#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM_OF_TRIES_ON_DRAWING 100000
#define BLANK ' '


//  Function prototypes

void printMenu();

void initialiseBoard(int lines, int cols, char board[lines][cols]);

bool isInsideBoard(int line, int col, int lines, int cols);

bool isValidPlace(int figureType, int line, int col, int lines, int cols, char board[lines][cols]);

void drawOnBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols]);

void printBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols]);

void cleanStdin(void);


int main()
{
    int lines = 20;
    int columns = 80;

    char board[lines][columns];

    srand(time(NULL));

    while (true)
    {
        printMenu();

        initialiseBoard(lines, columns, board);

        int figureType = -1;

        printf("Digite o tipo de figura basica desejada:\n");

        if (!scanf("%d", &figureType))
        {
            printf("Invalid value.\n");
            cleanStdin();
            continue;
        }
        else if (figureType < 1 || figureType > 5)
        {
            figureType = 5;
        }


        int numFigures = 0;

        printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio):\n");

        if (!scanf("%d", &numFigures))
        {
            printf("Invalid value.\n");
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

        while (true)
        {
            drawOnBoard(figureType, numFigures, lines, columns, board);

            printBoard(figureType, numFigures, lines, columns, board);

            int userChoice = -1;

            printf("\nAperte qualquer tecla para utilizar os mesmos valores, se não digite 0.\n");

            if (!scanf("%d", &userChoice) || userChoice != 0)
            {
                cleanStdin();
                initialiseBoard(lines, columns, board);
                continue;
            }

            break;
        }

        int userChoice = -1;

        printf("\nAperte qualquer tecla para utilizar um novo quadro, se não digite 0.\n");

        if (!scanf("%d", &userChoice) || userChoice != 0)
        {
            cleanStdin();
            initialiseBoard(lines, columns, board);
            continue;
        }

        break;
    }

    return 0;
}


/*
 *  Prints the menu out.
 */
void printMenu()
{
    printf("\nPROGRAMA GERADOR DE OBRA DE ARTE:\n"
           "=================================\n"
           "Escolha o tipo de figura basica a ser usada para criar a obra:\n"
           "1 - asterisco simples.\n"
           "2 - simbolo de soma com asteriscos.\n"
           "3 - letra X com asteriscos.\n"
           "4 - figuras aleatorias\n"
           "5 ou qualquer outro numero – opcao de obra de arte criada pelo aluno\n");
}


/*
 *  Initialises the board with determined characters.
 *
 *  @param      board      pointer for a matrix.
 *  @param      lines      number of lines.
 *  @param      cols       number of columns.
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


/*
 *  Checks if a figure would be inside a board's boundaries.
 *
 *  @param      line       line to check.
 *  @param      col        column to check.
 *  @param      lines      number of lines.
 *  @param      cols       number of columns.
 *  @return                whether the figure is inside the board.
 */
bool isInsideBoard(int line, int col, int lines, int cols)
{
    return line + 1 > 0 &&
           line + 1 < lines - 1 &&
           line - 1 > 0 &&
           line - 1 < lines - 1 &&
           col - 1 > 0 &&
           col - 1 < cols - 1 &&
           col + 1 > 0 &&
           col + 1 < cols - 1;
}


/*
 *  Checks if a figure would be inserted in a valid place.
 *
 *  @param      figureType      type of figure.
 *  @param      board           pointer for a matrix.
 *  @param      line            line to check.
 *  @param      col             column to check.
 *  @param      lines           number of lines.
 *  @param      cols            number of columns.
 *  @return                     whther the position is valid.
 */
bool isValidPlace(int figureType, int line, int col, int lines, int cols, char board[lines][cols])
{

    if (figureType == 1)
    {
        return board[line][col] == BLANK;
    }
    else if (figureType == 2)
    {
        return isInsideBoard(line, col, lines, cols) &&
               board[line][col] == BLANK &&
               board[line + 1][col] == BLANK &&
               board[line - 1][col] == BLANK &&
               board[line][col + 1] == BLANK &&
               board[line][col - 1] == BLANK;
    }
    else if (figureType == 3)
    {
        return isInsideBoard(line, col, lines, cols) &&
               board[line][col] == BLANK &&
               board[line + 1][col - 1] == BLANK &&
               board[line + 1][col + 1] == BLANK &&
               board[line - 1][col + 1] == BLANK &&
               board[line - 1][col - 1] == BLANK;
    }
    else if (figureType == 5)
    {
        return isInsideBoard(line, col, lines, cols) &&
               board[line][col] == BLANK &&
               board[line + 1][col] == BLANK &&
               board[line - 1][col] == BLANK &&
               board[line][col + 1] == BLANK &&
               board[line][col - 1] == BLANK &&
               board[line - 1][col + 1] == BLANK &&
               board[line - 1][col - 1] == BLANK;
    }

    return true;
}


/*
 *  Draws a figure on a board.
 *
 *  @param      figureType      type of figure.
 *  @param      numFigures      number of figures.
 *  @param      lines           number of lines.
 *  @param      cols            number of columns.
 *  @param      board           pointer for a matrix.
 */
void drawOnBoard(int figureType, int numFigures, int lines, int cols, char board[lines][cols])
{
    int numberOfTries = 0;
    int totalDrawnFigures = 0;

    while (numberOfTries < MAX_NUM_OF_TRIES_ON_DRAWING && totalDrawnFigures < numFigures)
    {
        int randomLine = rand() % (lines - 1) + 1;
        int randomColumn = rand() % (cols - 1) + 1;

        if (!isValidPlace(figureType, randomLine, randomColumn, lines, cols, board))
        {
            numberOfTries++;
            continue;
        }

        if (figureType == 1)
        {
            board[randomLine][randomColumn] = '*';
        }
        else if (figureType == 2)
        {
            board[randomLine][randomColumn] = '*';
            board[randomLine + 1][randomColumn] = '*';
            board[randomLine - 1][randomColumn] = '*';
            board[randomLine][randomColumn + 1] = '*';
            board[randomLine][randomColumn - 1] = '*';
        }
        else if (figureType == 3)
        {
            board[randomLine][randomColumn] = '*';
            board[randomLine + 1][randomColumn - 1] = '*';
            board[randomLine + 1][randomColumn + 1] = '*';
            board[randomLine - 1][randomColumn + 1] = '*';
            board[randomLine - 1][randomColumn - 1] = '*';
        }
        else if (figureType == 4)
        {
            int randomFigure = rand() % 3 + 1;

            if (!isValidPlace(randomFigure, randomLine, randomColumn, lines, cols, board))
            {
                numberOfTries++;
                continue;
            }

            if (randomFigure == 1)
            {
                board[randomLine][randomColumn] = '*';
            }
            else if (randomFigure == 2)
            {
                board[randomLine][randomColumn] = '*';
                board[randomLine + 1][randomColumn] = '*';
                board[randomLine - 1][randomColumn] = '*';
                board[randomLine][randomColumn + 1] = '*';
                board[randomLine][randomColumn - 1] = '*';
            }
            else if (randomFigure == 3)
            {
                board[randomLine][randomColumn] = '*';
                board[randomLine + 1][randomColumn - 1] = '*';
                board[randomLine + 1][randomColumn + 1] = '*';
                board[randomLine - 1][randomColumn + 1] = '*';
                board[randomLine - 1][randomColumn - 1] = '*';
            }
        }
        else
        {
            board[randomLine][randomColumn] = ' ';
            board[randomLine + 1][randomColumn] = '|';
            board[randomLine - 1][randomColumn] = 'o';
            board[randomLine][randomColumn + 1] = '\\';
            board[randomLine][randomColumn - 1] = '(';
            board[randomLine - 1][randomColumn + 1] = ')';
            board[randomLine - 1][randomColumn - 1] = '>';
        }

        totalDrawnFigures++;
    }
}


/*
 *  Prints board out.
 *
 *  @param      lines      number of lines.
 *  @param      cols       number of columns.
 *  @param      board      pointer for a matrix.
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