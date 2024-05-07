#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

//liczba pionkow w grze
int aPieces = 12;
int bPieces = 12;

void title()																								//tytuł
{
	cout << endl;
	cout << "*       *        *        * * *         * *          *        * * *     *     *" << endl;
	cout << "*       *       * *       *     *     *     *       * *       *    *     *   *" << endl;
	cout << "*       *      *   *      *     *    *             *   *      * * *       * *" << endl;
	cout << "*   *   *     * * * *     * * *      *            * * * *     *     *      *" << endl;
	cout << "* *   * *    *       *    *     *     *     *    *       *    *     *      *" << endl;
	cout << "*       *   *         *   *      *      * *     *         *   * * *        *" << endl;
	cout << endl;
}

void boardCreating(char board[32][64])																		//stworzenie tablicy początkowe
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if ((i % 8 == 5 || i % 8 == 6) && (j % 16 > 0 && j % 16 < 7))									//wstawienie pionkow
			{
				board[i][j] = 'b';
			}
			else if ((i % 8 == 1 || i % 8 == 2) && (j % 16 > 8 && j % 16 < 15))
			{
				board[i][j] = 'b';
			}
			else
			{
				board[i][j] = ' ';
			}
		}
	}

	for (int i = 12; i < 20; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			board[i][j] = ' ';
		}
	}

	for (int i = 20; i < 32; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if ((i % 8 == 5 || i % 8 == 6) && (j % 16 > 0 && j % 16 < 7))
			{
				board[i][j] = 'a';
			}
			else if ((i % 8 == 1 || i % 8 == 2) && (j % 16 > 8 && j % 16 < 15))
			{
				board[i][j] = 'a';
			}
			else
			{
				board[i][j] = ' ';
			}
		}
	}
}

void boardDrawing(char board[32][64])																		//wyswietlenie tablicy
{
	//ustawienia dla zmiany kolorow
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int iFieldNumber = -1;
	int jFieldNumber = -1;

	title();

	cout.width(3);																							//wypisanie wspolrzednych literowych
	cout << " ";
	cout << "  a";
	cout.width(8);
	cout << "b";
	cout.width(8);
	cout << "c";
	cout.width(8);
	cout << "d";
	cout.width(8);
	cout << "e";
	cout.width(8);
	cout << "f";
	cout.width(8);
	cout << "g";
	cout.width(8);
	cout << "h";
	cout << endl;

	for (int i = 0; i < 32; i++)
	{
		if (i % 4 == 0)																				
		{
			iFieldNumber++;
		}
		if (i % 4 == 1)
		{
			cout << " " << 8 - iFieldNumber << " ";															//wypisanie wspolrzednych cyfrowych
		}
		else
		{
			cout.width(3);
			cout << " ";
		}
		for (int j = 0; j < 64; j++)
		{
			if (j % 8 == 0)
			{
				jFieldNumber++;
			}
			if ((iFieldNumber + jFieldNumber) % 2 == 0)														//tworzenie pol  szachowych
			{
				SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			}
			else
			{
				if (board[i][j] == 'a')																		//ustawienie pionkow gracza A na kolor czerwony			
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | BACKGROUND_RED);
				}
				else if (board[i][j] == 'b')																//ustawienie pionkow gracza B na kolor bialy
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				}
				else if (board[i][j] == 'c' || board[i][j] == 'd')											//ustawienie koloru na zolty dla pionka nieaktywnego
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				}
				else if (board[i][j] == 'o')																//podswietlenie zaznaczonego pionka
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				}
				else
				{
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
			}
			cout << board[i][j];
		}
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);					//kolory domyslne
		if (i % 4 == 1)
		{
			cout << " " << 8 - iFieldNumber << " ";
		}
		else
		{
			cout.width(3);
			cout << " ";
		}
		cout << endl;
	}
	cout.width(3);
	cout << " ";
	cout << "  a";
	cout.width(8);
	cout << "b";
	cout.width(8);
	cout << "c";
	cout.width(8);
	cout << "d";
	cout.width(8);
	cout << "e";
	cout.width(8);
	cout << "f";
	cout.width(8);
	cout << "g";
	cout.width(8);
	cout << "h";

	cout << endl;
}

void whichGamer(char gamer, string txt)																		//wypisanie tekstu z przypisanym kolorem dla gracza
{
	//ustawienia dla zmiany kolorow
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (gamer == 'A')
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
	}
	cout << endl << txt << gamer << endl;

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);						//kolory domyslne
}

void howManyPieces()																						//wypisanie ile zostalo aktywnych pionkow
{
	//ustawienia dla zmiany kolorow
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << endl << "Zostalo aktywnych pionkow: ";
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);
	cout << aPieces;

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); //kolory domyslne
	cout << " " << bPieces << endl;
}

bool checkingPosition(char board[32][64], char* x, char* y)													//sprawdza czy istnieje takie pole
{
	if (*y >= 65 && *y <= 72)
	{
		*y += 32;
	}
	if (*x < 49 || *x > 56 || *y < 97 || *y > 104)
	{
		return false;
	}
	return true;
}

bool checkingIfExist(char board[32][64], char* x, char* y, char gamer)										//sprawdza czy jest tam pionek gracza
{
	if (board[(56 - int(*x)) * 4 + 1][(int(*y) - 97) * 8 + 1] != gamer)
	{
		return false;
	}
	return true;
}

bool checkingPossibilities(char board[32][64], char* x, char* y, char gamer)								//sprawdza czy ten pionek moze sie ruszyc
{
	char opponent{};
	if (gamer == 'a')
	{
		opponent = 'b';
	}
	else
	{
		opponent = 'a';
	}
	int i = (56 - int(*x)) * 4 + 1;
	int j = (int(*y) - 97) * 8 + 1;

	if (i > 4)																								//jesli moze przesunac sie o minimum jedno w gore
	{
		if (j > 8)																							//o jedno w lewo
		{
			if (board[i - 4][j - 8] == ' ')
			{
				return true;
			}
		}
		if (j < 56)																							//o jedno w prawo
		{
			if (board[i - 4][j + 8] == ' ')
			{
				return true;
			}
		}
		if (i > 8)																							//o dwa w gore
		{
			if (j > 16)																						//o dwa w lewo
			{
				if (board[i - 4][j - 8] == opponent)
				{
					if (board[i - 8][j - 16] == ' ')
					{
						return true;
					}
				}
			}
			if (j < 48)																						//o dwa w prawo
			{
				if (board[i - 4][j + 8] == opponent)
				{
					if (board[i - 8][j + 16] == ' ')
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool checkingIfBlank(char board[32][64], char* x, char* y)													//sprawdza czy miejsce jest wolne
{
	int i = (56 - int(*x)) * 4 + 1;
	int j = (int(*y) - 97) * 8 + 1;
	if (board[i][j] != ' ')
	{
		return false;
	}
	return true;
}

void removingOpponent(char board[32][64], int x, int y, int opponent)										//usuwanie pionka przeciwnika
{
	for (int i = 0; i < 6; i++)
	{
		board[x][y + i] = ' ';
	}
	for (int i = 0; i < 6; i++)
	{
		board[x + 1][y + i] = ' ';
	}
	if (opponent == 'a')
	{
		aPieces--;
	}
	else
	{
		bPieces--;
	}
}

bool checkingMoving(char board[32][64], char xStart, char yStart, char xEnd, char yEnd, char gamer)			//spradza czy taki ruch jest dozwolony
{
	char opponent{};
	if (gamer == 'a')
	{
		opponent = 'b';
	}
	else
	{
		opponent = 'a';
	}
	int i = (56 - int(xStart)) * 4 + 1;
	int j = (int(yStart) - 97) * 8 + 1;
	if (((xEnd - xStart) == 1) && (abs(yEnd - yStart) == 1))
	{
		return true;
	}
	else if (abs(xEnd - xStart) == 2)
	{
		if ((yEnd - yStart) == 2 && board[i - 4][j + 8] == opponent)
		{
			removingOpponent(board, i - 4, j + 8, opponent);
			return true;
		}
		else if ((yEnd - yStart) == -2 && board[i - 4][j - 8] == opponent)
		{
			removingOpponent(board, i - 4, j - 8, opponent);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void whereStart(char board[32][64], char* x, char* y, char gracz)											//pobiera wspolrzedne poczatkowe i sprawdza warunki
{
	cout << endl << "Ktory pionek chcesz przesunac? ";
	cin >> *x >> *y;
	if (checkingPosition(board, x, y) == false)
	{
		cout << "Podales zle dane, sproboj jeszcze raz (zatwierdz enterem najpierw liczbe, potem litere)";
		whereStart(board, x, y, gracz);
	}
	else if (checkingIfExist(board, x, y, gracz) == false)
	{
		cout << "W tym miejscu nie ma Twojego pionka, sproboj jeszcze raz";
		whereStart(board, x, y, gracz);
	}
	else if (checkingPossibilities(board, x, y, gracz) == false)
	{
		cout << "Ten pionek nie ma jak sie ruszyc, sproboj jeszcze raz";
		whereStart(board, x, y, gracz);
	}
}

void whereEnd(char board[32][64], char xStart, char yStart, char* x, char* y, char gracz)					//pobiera wspolrzedne docelowe i sprawdza warunki
{

	cout << endl << "Gdzie chcesz postawic pionek? ";
	cin >> *x >> *y;
	char xEnd = *x;
	char yEnd = *y;
	if (checkingPosition(board, x, y) == false)
	{
		cout << "Podales zle dane, sproboj jeszcze raz (zatwierdz enterem najpierw liczbe, potem litere)";
		whereEnd(board, xStart, yStart, x, y, gracz);
	}
	else if (checkingMoving(board, xStart, yStart, xEnd, yEnd, gracz) == false)
	{
		cout << "Pionek nie moze wykonac takiego ruchu, sproboj jeszcze raz";
		whereEnd(board, xStart, yStart, x, y, gracz);
	}
	else if (checkingIfBlank(board, x, y) == false)
	{
		cout << "Tutaj jest inny pionek, sproboj jeszcze raz";
		whereEnd(board, xStart, yStart, x, y, gracz);
	}
}

void toBoardReverse(char board[32][64], char boardReverse[32][64])												//odwraca tablice dla nasteonego gracza
{
	int k = 31;
	for (int i = 0; i < 32; i++)
	{
		int l = 63;
		for (int j = 0; j < 64; j++)
		{
			boardReverse[i][j] = board[k][l--];
		}
		k--;
	}
	boardDrawing(boardReverse);
}

void fieldHighlight(char board[32][64], char x, char y)														//podswietlenie pola wybranego pionka
{
	int xHighlight = (56 - int(x)) * 4;
	int yHighlight = (int(y) - 97) * 8;
	for (int i = yHighlight; i <= yHighlight + 7; i++)
	{
		board[xHighlight][i] = 'h';
	}
	board[xHighlight + 1][yHighlight] = 'h';
	board[xHighlight + 2][yHighlight] = 'h';
	board[xHighlight + 1][yHighlight + 7] = 'h';
	board[xHighlight + 2][yHighlight + 7] = 'h';
	for (int i = yHighlight; i <= yHighlight + 7; i++)
	{
		board[xHighlight + 3][i] = 'h';
	}
	boardDrawing(board);
}

void fieldNotHighlight(char board[32][64], char x, char y)													//usuniecie podswietlenia
{
	int xHighlight = (56 - int(x)) * 4;
	int yHighlight = (int(y) - 97) * 8;
	for (int i = yHighlight; i <= yHighlight + 7; i++)
	{
		board[xHighlight][i] = ' ';
	}
	board[xHighlight + 1][yHighlight] = ' ';
	board[xHighlight + 2][yHighlight] = ' ';
	board[xHighlight + 1][yHighlight + 7] = ' ';
	board[xHighlight + 2][yHighlight + 7] = ' ';
	for (int i = yHighlight; i <= yHighlight + 7; i++)
	{
		board[xHighlight + 3][i] = ' ';
	}
}

void changingToPieceOff(char board[32][64], char xNew, char yNew, char gracz)								//zmiana w nieaktywnego pionka
{
	board[xNew + 1][yNew + 1] = gracz + 2;
	board[xNew + 1][yNew + 6] = gracz + 2;
	board[xNew + 2][yNew + 1] = gracz + 2;
	board[xNew + 2][yNew + 6] = gracz + 2;

	if (gracz == 'a')
	{
		aPieces--;
	}
	else
	{
		bPieces--;
	}
}

void changingPiece(char board[32][64], char xStart, char yStart, char xEnd, char yEnd, char gracz)			//przesuniecie pionka
{
	int xOld = (56 - int(xStart)) * 4;
	int yOld = (int(yStart) - 97) * 8;
	int xNew = (56 - int(xEnd)) * 4;
	int yNew = (int(yEnd) - 97) * 8;

	for (int i = 1; i <= 6; i++)
	{
		board[xOld + 1][yOld + i] = ' ';
		board[xNew + 1][yNew + i] = gracz;
	}
	for (int i = 1; i <= 6; i++)
	{
		board[xOld + 2][yOld + i] = ' ';
		board[xNew + 2][yNew + i] = gracz;
	}
	if (xNew == 0)
	{
		changingToPieceOff(board, xNew, yNew, gracz);
	}
	else if (yNew == 0)
	{
		if (board[xNew - 2][yNew + 9] == gracz + 2)
		{
			changingToPieceOff(board, xNew, yNew, gracz);
		}
	}
	else if (yNew == 56)
	{
		if (board[xNew - 2][yNew - 3] == gracz + 2)
		{
			changingToPieceOff(board, xNew, yNew, gracz);
		}
	}
	else
	{
		if ((board[xNew - 2][yNew + 9] == gracz + 2) && (board[xNew - 2][yNew - 3] == gracz + 2))
		{
			changingToPieceOff(board, xNew, yNew, gracz);
		}
	}
}

int main()
{
	//ustawienie okna konsoli
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 600, 800, SWP_SHOWWINDOW); }

	char board[32][64]{};
	char boardReverse[32][64]{};
	char xStart{}, yStart{}, xEnd{}, yEnd{};

	boardCreating(board);
	boardDrawing(board);

	while (aPieces > 0)
	{
		//gracz A
		whichGamer('A', "Ruch gracza ");
		whereStart(board, &xStart, &yStart, 'a');
		system("cls");
		fieldHighlight(board, xStart, yStart);
		whichGamer('A', "Ruch gracza ");
		whereEnd(board, xStart, yStart, &xEnd, &yEnd, 'a');
		system("cls");
		fieldNotHighlight(board, xStart, yStart);
		changingPiece(board, xStart, yStart, xEnd, yEnd, 'a');
		boardDrawing(board);
		howManyPieces();
		system("pause");
		system("cls");
		if (bPieces == 0)
		{
			boardDrawing(board);
			whichGamer('A', "Wygral gracz ");
			break;
		}
		//gracz B
		toBoardReverse(board, boardReverse);
		whichGamer('B', "Ruch gracza ");
		whereStart(boardReverse, &xStart, &yStart, 'b');
		system("cls");
		fieldHighlight(boardReverse, xStart, yStart);
		whichGamer('B', "Ruch gracza ");
		whereEnd(boardReverse, xStart, yStart, &xEnd, &yEnd, 'b');
		system("cls");
		fieldNotHighlight(boardReverse, xStart, yStart);
		changingPiece(boardReverse, xStart, yStart, xEnd, yEnd, 'b');
		boardDrawing(boardReverse);
		howManyPieces();
		system("pause");
		system("cls");

		//przypisanie odwroconej tablicy do zwyklej
		toBoardReverse(boardReverse, board);
	}
	if (aPieces == 0)
	{
		whichGamer('B', "Wygral gracz ");
	}
}