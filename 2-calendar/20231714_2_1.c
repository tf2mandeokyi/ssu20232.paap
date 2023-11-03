#include <stdio.h>

enum DayOfTheWeek
{
	SUN=0, MON, TUE, WED, THU, FRI, SAT
};

enum DayOfTheWeek get_first_dotw(int year, int month);
_Bool is_leap_year(int year);
void print_calendar(int year, int month);
int get_days_of_month(int month, _Bool is_leap);

int main(void)
{
	int year, month;
	printf("년을 입력하세요 : ");
	scanf("%d", &year);
	printf("월을 입력하세요 : ");
	scanf("%d", &month);

	print_calendar(year, month);
}

void print_calendar(int year, int month)
{
	printf("           %4d년 %2d월           \n", year, month);
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

	enum DayOfTheWeek startDay = get_first_dotw(year, month);
	_Bool is_leap = is_leap_year(year);
	int dayCount = get_days_of_month(month, is_leap);

	for(int i = 0; i < startDay; i++)
	{
		printf("     ");
	}
	for(int d = 1; d <= dayCount; d++)
	{
		if(d < 10) printf("  %d  ", d);
		else       printf(" %d  " , d);
		if((startDay + d - 1) % 7 == 6) printf("\n");
	}
	printf("\n");
}

enum DayOfTheWeek get_first_dotw(int year, int month)
{
	// 1년 1월 1일을 월요일로 설정
	int daySum = MON;

	// 1년부터 year-1년까지 일수를 더하면서 계산
	for(int y = 1; y < year; y++)
	{
		_Bool is_leap = is_leap_year(y);
		daySum += is_leap ? 366 : 365;
	}

	// year년 1월에서 year년 month-1월까지 일수를 더하면서 계산
	_Bool is_leap = is_leap_year(year);
	for(int m = 1; m < month; m++)
	{
		daySum += get_days_of_month(m, is_leap);
	}

	return daySum % 7;
}

_Bool is_leap_year(int year)
{
	if     (year % 400 == 0) return 1; // 400년 윤년
	else if(year % 100 == 0) return 0; // 100년 평년
	else if(year %   4 == 0) return 1; // 4년 윤년
	else                     return 0; // 평년
}

int get_days_of_month(int month, _Bool is_leap)
{
	switch(month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return is_leap ? 29 : 28;
		default:
			return 0;
	}
}