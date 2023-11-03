#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum DayOfTheWeek
{
	SUN=0, MON, TUE, WED, THU, FRI, SAT
};


enum DayOfTheWeek get_first_dotw(int year, int month);
_Bool is_leap_year(int year);
void print_calendar(char **schedules, int year, int month);
int get_days_of_month(int month, _Bool is_leap);
int get_days_of_year_month(int year, int month);
char* input_line();

void handle_schedule_add(char **schedules, int dayCount); // 1. 일정 입력
void handle_schedule_delete(char **schedules, int dayCount); // 2. 일정 삭제
void handle_schedule_check(char **schedules, int dayCount, int year, int month); // 3. 일정 확인


int main(void)
{
	int year, month = 0;
	printf("년을 입력하세요 : ");
	scanf("%d", &year);
	do
	{
		printf("월을 입력하세요 : ");
		scanf("%d", &month);
	} while(month < 1 || month > 12);

	int dayCount = get_days_of_year_month(year, month);
	char *schedules[31];
	for(int i = 0; i < dayCount; i++)
	{
		schedules[i] = NULL;
	}

	_Bool exit = 0;
	do
	{
		system("clear");
		print_calendar(schedules, year, month);
		printf("\n\n\n\n\n");
		printf(
				"1. 일정 입력        "
				"2. 일정 삭제        "
				"3. 일정 확인        "
				"4. 종료\n\n"
		);

		int menu = 0;
		do
		{
			printf("메뉴를 입력하세요 : ");
			scanf("%d", &menu);
		} while(menu < 1 || menu > 4);

		switch(menu)
		{
			case 1: handle_schedule_add(schedules, dayCount); break;
			case 2: handle_schedule_delete(schedules, dayCount); break;
			case 3: handle_schedule_check(schedules, dayCount, year, month); break;
			case 4: exit = 1; break;
		}

	} while(exit == 0);

}


void handle_schedule_add(char **schedules, int dayCount)
{
	int day = -1;
	do
	{
		printf("날짜를 입력하세요 : ");
		scanf("%d", &day);
		if(day == 0) return;
	} while(day < 1 || day > dayCount || schedules[day-1] != NULL);
	
	printf("일정을 입력하세요 : ");
	char *schedule = input_line();
	// 평가사항에 없는 기능: schedule이 비었을 경우 스킵
	if(strlen(schedule) == 0)
	{
		free(schedule);
		return;
	}

	schedules[day-1] = schedule;
}


void handle_schedule_delete(char **schedules, int dayCount)
{
	int day = -1;
	do
	{
		printf("날짜를 입력하세요 : ");
		scanf("%d", &day);
		if(day == 0) return;
	} while(day < 1 || day > dayCount || schedules[day-1] == NULL);

	free(schedules[day-1]);
	schedules[day-1] = NULL;
}


void handle_schedule_check(char **schedules, int dayCount, int year, int month)
{
	int day = -1;
	do
	{
		printf("날짜를 입력하세요 : ");
		scanf("%d", &day);
		if(day == 0) return;
	} while(day < 1 || day > dayCount || schedules[day-1] == NULL);

	printf("%d년 %d월 %d일 일정은 %s입니다.", year, month, day, schedules[day-1]);
	getchar(); // TODO: termios getch()로 바꾸기
	getchar();
}


void print_calendar(char **schedules, int year, int month)
{
	printf("\n");
	printf("                   ");
	printf("           %4d년 %2d월           \n\n", year, month);
	printf("                   ");
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n\n");
	printf("                   ");

	enum DayOfTheWeek startDay = get_first_dotw(year, month);
	int dayCount = get_days_of_year_month(year, month);

	for(int i = 0; i < startDay; i++)
	{
		printf("     ");
	}
	for(int d = 1; d <= dayCount; d++)
	{
		if(d < 10) printf(" ");
		printf("%c", schedules[d-1] != NULL ? '*' : ' ');
		printf("%d  ", d);
		if((startDay + d - 1) % 7 == 6)
		{
			printf("\n\n");
			printf("                   ");
		}
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

int get_days_of_year_month(int year, int month)
{
	_Bool is_leap = is_leap_year(year);
	return get_days_of_month(month, is_leap);
}

int get_days_of_month(int month, _Bool is_leap)
{
	switch(month)
	{
		case  1:
		case  3:
		case  5:
		case  7:
		case  8:
		case 10:
		case 12: return 31;

		case  4:
		case  6:
		case  9:
		case 11: return 30;

		case  2: return is_leap ? 29 : 28;

		default: return 0;
	}
}

char* input_line()
{
	int size = 0, alloc_size = 0, ch;
	char *res = NULL, *old;

	while(1)
	{
		ch = getchar();
		if(ch == '\n')
		{
			if(size == 0) continue;
			else break;
		}

		size++;
		if(size > alloc_size)
		{
			alloc_size += alloc_size / 2 > 1 ? alloc_size / 2 : 1;
			old = res;
			res = (char*) malloc(alloc_size * sizeof(char));
			for(int i = 0; i < size-1; i++)
			{
				res[i] = old[i];
			}
			if(old != NULL) free(old);
		}
		res[size-1] = ch;
	}

	old = res;
	res = (char*) malloc((size+1) * sizeof(char));
	for(int i = 0; i < size; i++)
	{
		res[i] = old[i];
	}
	res[size] = '\0';
	if(old != NULL) free(old);

	return res;
}