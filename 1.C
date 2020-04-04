#include<stdio.h>

#include<stdlib.h>

#include<time.h>

#include<stack>

#include<windows.h>







using std::stack;



int ch2num ( const char &ch )  

{

	int num ( -1 );

	switch ( ch )

	{

	case'#':

		num = 0;

		break;

	case'+':

		num = 1;

		break;

	case'-':

		num = 2;

		break;

	case'*':

		num = 3;

		break;

	case'/':

		num = 4;

		break;

	case'(':

		num = 5;

		break;

	case')':

		num = 6;

		break;

	}

	return num;

}



int operator_2 ( const int &num1, const int &num2, const char &ch )  

{

	int num ( -1 );

	switch ( ch )

	{

	case'+':

		num = num2 + num1;

		break;

	case'-':

		num = num2 - num1;

		break;

	case'*':

		num = num2 * num1;

		break;

	case'/':

		num = num2 / num1;

		break;

	}

	return num;

}



int compare[5][6] = { { 0 }, { 1, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 } }; 



int Calculation ( char *str, int i ) 
{

	stack<int>S_num;  

	stack<char>S_ch;

	while ( !S_ch.empty() )

		S_ch.pop();

	S_ch.push ( '#' );

	while ( !S_num.empty() )

		S_num.pop();

	int tnum ( 0 );

	for ( int i ( 0 ); str[i] != '\0'; )

	{

		if ( '0' <= str[i] && str[i] <= '9' ) 

		{

			tnum *= 10;

			tnum += str[i] - '0';

			++i;

		}

		else if ( str[i] == '(' )  

		{

			S_ch.push ( '(' );

			++i;

		}

		else if ( str[i] == ')' )

		{

			S_num.push ( tnum );

			char ch = S_ch.top();  

			if ( ch != '(' )

			{

				S_ch.pop();

				int num1 = S_num.top();

				S_num.pop();

				int num2 = S_num.top();

				S_num.pop();

				tnum = operator_2 ( num1, num2, ch );

			}

			else

			{

				tnum = S_num.top();

				S_num.pop();

			}

			S_ch.pop();

			++i;

		}

		else

		{

			S_num.push ( tnum );

			tnum = 0;

			if ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 1 )  

				S_ch.push ( str[i] );

			else

			{

				while ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 0 ) 
				{

					char ch = S_ch.top();

					S_ch.pop();

					int num1 = S_num.top();

					S_num.pop();

					int num2 = S_num.top();

					S_num.pop();

					S_num.push ( operator_2 ( num1, num2, ch ) );

				}

				S_ch.push ( str[i] );

			}

			++i;

		}

	}

	S_num.push ( tnum );

	char ch ( '\0' );

	while ( ( ch = S_ch.top() ) != '#' ) 
	{

		S_ch.pop();

		int num1 = S_num.top();

		S_num.pop();

		int num2 = S_num.top();

		S_num.pop();

		S_num.push ( operator_2 ( num1, num2, ch ) );

	}

	FILE *fpWrite = fopen ( "Answers.txt", "a" );  

	if ( fpWrite == NULL )

	{

		return 0;

	}

	fprintf ( fpWrite, "Answer%d:\t%d\n", i, S_num.top() );

	return 1;

}