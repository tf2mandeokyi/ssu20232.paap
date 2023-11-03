// 프로그래밍응용및실습 과제1
// 20231714 김민재

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct card
{
	char shape;
	char num[3];
};


// 족보 확인 함수 목록
_Bool royal_straight_flush(struct card mycard[]);
_Bool back_straight_flush(struct card mycard[]);
_Bool straight_flush(struct card mycard[]);
_Bool four_card(struct card mycard[]);
_Bool full_house(struct card mycard[]);
_Bool flush(struct card mycard[]);
_Bool mountain(struct card mycard[]);
_Bool back_straight(struct card mycard[]);
_Bool straight(struct card mycard[]);
_Bool triple(struct card mycard[]);
_Bool two_pair(struct card mycard[]);
_Bool one_pair(struct card mycard[]);

int test_deck(struct card mycard[]);
void print_cards_type(int deck_number);

_Bool straight_num_check(struct card mycard[]); 
int* cards_get_count_array(struct card mycard[]);
int n_of_a_kind_count(struct card mycard[], int n);
_Bool numstr_arr_match(struct card mycard[], char *n1, char *n2, char *n3, char *n4, char *n5);

// 메인 화면 명령번호 함수 목록
void handle_manual_input();
void handle_random_generation();

// 입력 함수 목록
char* input_line();

// 기타 함수 목록
int numstr_to_index(char *numstr);
const char* index_to_numstr(int index);
int shape_to_index(char shape);
char index_to_shape(int index);
void generate_random_cards(struct card mycard[]);


int main(void)
{
	srand(time(NULL));
	_Bool end = 0;
	int input_num;

	while(end == 0)
	{
		printf("1. 직접 입력        2. 랜덤 생성        3. 종료\n");
		printf("\n");
		printf("번호를 입력하세요 : ");

		do
		{
			int input_retry = 0;
			scanf("%d", &input_num);
			switch(input_num)
			{
				case 1:
					printf("\n");
					handle_manual_input();
					break;
				case 2:
					printf("\n");
					handle_random_generation();
					break;
				case 3:
					end = 1;
					break;
				default:
					input_retry = 1;
			}
			if(input_retry == 0) break;
			printf("\n");
			printf("잘못된 번호입니다. 다시 입력해주세요 : ");
		} while(1);

		if(end == 0) printf("\n===============================================================\n"); // 정확히 63개
	}
	return 0;
}


void handle_manual_input()
{
	struct card mycard[5];
	printf("5개의 카드 정보를 입력하세요.\n");

	// 입력
	for(int i = 0; i < 5; i++)
	{
		printf("%d번 카드 무늬와 숫자 : ", i+1);
		char *line_buf = input_line();
		
		int line_len = strlen(line_buf);
		if(line_len < 3 || 4 < line_len)
		{
			printf("입력이 잘못됐습니다. 다시 시도하세요\n");
			i--; continue;
		}

		char shape = line_buf[0];
		if(shape_to_index(shape) == -1)
		{
			printf("잘못된 무늬입니다. 다시 시도하세요\n");
			i--; continue;
		}

		if(numstr_to_index(line_buf+2) == -1)
		{
			printf("잘못된 숫자입니다. 다시 시도하세요\n");
			i--; continue;
		}

		mycard[i].shape = shape;
		mycard[i].num[0] = line_buf[2];
		mycard[i].num[1] = line_buf[3];
		mycard[i].num[2] = line_buf[4];
		free(line_buf);
	}

	int deck_number = test_deck(mycard);
	printf("결과 : ");
	print_cards_type(deck_number);
}

void handle_random_generation()
{
	int set_number;
	struct card mycard[5];
	int mycard_index[5];
	int try = 0;

	printf("1.  royal_straight_flush    2.  back_straight_flush\n");
	printf("3.  straight_flush          4.  four_card          \n");
	printf("5.  full_house              6.  flush              \n");
	printf("7.  mountain                8.  back_straight      \n");
	printf("9.  straight                10. triple             \n");
	printf("11. two_pair                12. one_pair           \n");
	printf("\n");
	printf("무슨 족보를 생성할까요? ");

	do
	{
		scanf("%d", &set_number);
		if(1 <= set_number && set_number <= 12) break;
		printf("잘못된 족보입니다. 다시 입력해주세요 : ");
	} while(0);

	do
	{
		try++;
		generate_random_cards(mycard);
    } while(test_deck(mycard) != set_number);

	printf("생성된 카드 : ");
	for(int i = 0; i < 5; i++)
	{
		printf("%c %s", mycard[i].shape, mycard[i].num);
		if(i != 4) printf(", ");
	}
	printf("\n");
	printf("%d번 족보를 생성하기 위한 카드 생성 시도 : %d번", set_number, try);
}

int test_deck(struct card mycard[])
{
	if     (royal_straight_flush(mycard)) return  1;
	else if( back_straight_flush(mycard)) return  2;
	else if(      straight_flush(mycard)) return  3;
	else if(           four_card(mycard)) return  4;
	else if(          full_house(mycard)) return  5;
	else if(               flush(mycard)) return  6;
	else if(            mountain(mycard)) return  7;
	else if(       back_straight(mycard)) return  8;
	else if(            straight(mycard)) return  9;
	else if(              triple(mycard)) return 10;
	else if(            two_pair(mycard)) return 11;
	else if(            one_pair(mycard)) return 12;
	else                                  return  0;
}

void print_cards_type(int deck_number)
{
	switch(deck_number)
	{
		case  1: printf("로얄 스트레이트 플러쉬"); break;
		case  2: printf("백 스트레이트 플러쉬");   break;
		case  3: printf("스트레이트 플러쉬");      break;
		case  4: printf("포카드");                 break;
		case  5: printf("풀하우스");               break;
		case  6: printf("플러쉬");                 break;
		case  7: printf("마운틴");                 break;
		case  8: printf("백스트레이트");           break;
		case  9: printf("스트레이트");             break;
		case 10: printf("트리플");                 break;
		case 11: printf("투 페어");                break;
		case 12: printf("원 페어");                break;
		default: printf("노 페어");                break;
	}
}

void generate_random_cards(struct card mycard[])
{
	int mycard_index[5];
	for(int i = 0; i < 5; i++)
	{
		mycard_index[i] = rand() % 52;
		for(int j = 0; j < i; j++)
		{
			if(mycard_index[j] == mycard_index[i]) { i--; break; }
		}
	}

	for(int i = 0; i < 5; i++)
	{
		mycard[i].shape = index_to_shape(mycard_index[i] / 13);
		strcpy(mycard[i].num, index_to_numstr(mycard_index[i] % 13));
	}
}

/**
 * 한 줄을 입력받음. 빈 줄은 스킵함.
 * scanf("%s")가 동작이 이상하고 buf 배열 크기를 딱 정해야 한다는 게 빡쳐서 이 함수를 만들게 됨
 */
char* input_line()
{
	int size = 0, alloc_size = 0, ch;
	char *res = NULL, *old;

	while(1)
	{
		// size가 0인지 확인해야 하기 때문에 getchar()를 while()의 조건식 안에 넣지 못함.
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

/**
 * @return "A"부터 "K"까지 차례대로 0, 1, ..., 12. 만약 올바른 번호가 아니라면 -1
 */
int numstr_to_index(char *numstr)
{
	const char numstr_array[13][3] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	for(int i = 0; i < 13; i++)
	{
		if(strcmp(numstr, numstr_array[i]) == 0) return i;
	}
	return -1;
}

const char* index_to_numstr(int index)
{
	const char numstr_array[13][3] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	return index >= 0 && index < 13 ? numstr_array[index] : "";
}

int shape_to_index(char shape)
{
	const char shape_array[5] = "SDHC";
	for(int i = 0; i < 4; i++)
	{
		if(shape == shape_array[i]) return i;
	}
	return -1;
}

char index_to_shape(int index)
{
	const char shape_array[5] = "SDHC";
	return index >= 0 && index < 4 ? shape_array[index] : '\0';
}

_Bool numstr_arr_match(struct card mycard[], char *n1, char *n2, char *n3, char *n4, char *n5)
{
	_Bool match[5] = { 0 }; // 차례대로 n1, n2, n3, n4, n5
	for(int i = 0; i < 5; i++)
	{
		char *numstr = mycard[i].num;
		if     (strcmp(numstr, n1) == 0) match[0] = 1;
		else if(strcmp(numstr, n2) == 0) match[1] = 1;
		else if(strcmp(numstr, n3) == 0) match[2] = 1;
		else if(strcmp(numstr, n4) == 0) match[3] = 1;
		else if(strcmp(numstr, n5) == 0) match[4] = 1;
	}
	
	for(int i = 0; i < 5; i++)
	{
		if(!match[i]) return 0;
	}
	return 1;
}

/**
 * 경고: 리턴 배열 사용한 후 free()로 메모리 해제하기
 * @return 크기 13의 개수 배열. [0]부터 "A"의 개수, 그 다음부터 [1]은 "2", [2]는 "3", ..., [12]는 "K"
 */
int* cards_get_count_array(struct card mycard[])
{
	int *count_array = calloc(13, sizeof(int)); // 순서대로
	for(int i = 0; i < 5; i++)
	{
		char *numstr = mycard[i].num;
		int index = numstr_to_index(numstr);
		if(index == -1) continue;
		count_array[index]++;
	}
	return count_array;
}

int n_of_a_kind_count(struct card mycard[], int n)
{
	int result = 0;
	int *count_array = cards_get_count_array(mycard);
	
	for(int i = 0; i < 13; i++)
	{
		if(count_array[i] == n) result++;
	}

	free(count_array);
	return result;
}

/**
 * 스트레이트용 숫자 확인 함수.
 * straight()에선 flush인 경우를 따로 빼야 하기 때문에 (아님 말고) 이 코드를 분리시킴.
 */
_Bool straight_num_check(struct card mycard[])
{
	int *count_array = cards_get_count_array(mycard);
	int straight_count = 0;
	_Bool result = 0;

	for(int i = 0; i < 13; i++)
	{
		if(count_array[i] == 0)
		{
			if(straight_count != 0) break; // 실패; 중간에 "끊어져" 있음
		}
		else if(count_array[i] == 1)
		{
			straight_count++;
			if(straight_count == 5) { result = 1; break; } // 성공. return을 안 쓰는 이유는 count_array를 free시켜야 하기 때문에
		}
		else break; // 스트레이트라면 중복이 뜨면 안 됨 -> 실패
	}

	free(count_array);
	return result;
}

_Bool royal_straight_flush(struct card mycard[])
{
	return flush(mycard) && numstr_arr_match(mycard, "10", "J", "Q", "K", "A");
}

_Bool back_straight_flush(struct card mycard[])
{
	return flush(mycard) && numstr_arr_match(mycard, "A", "2", "3", "4", "5");
}

_Bool straight_flush(struct card mycard[])
{
	return flush(mycard) && straight_num_check(mycard);
}

_Bool four_card(struct card mycard[])
{
	return n_of_a_kind_count(mycard, 4);
}

_Bool full_house(struct card mycard[])
{
	return n_of_a_kind_count(mycard, 2) == 1 && n_of_a_kind_count(mycard, 3) == 1;
}

_Bool flush(struct card mycard[])
{
	char common_shape = mycard[0].shape;
	for(int i = 1; i < 5; i++)
	{
		if(mycard[i].shape != common_shape) return 0;
	}
	return 1;
}

_Bool mountain(struct card mycard[])
{
	// "!flush(mycard)" 뺄 수도 있었는데 "모든 무늬가 같지는 않고"라는 말 때문에 빼면 점수 깎일까봐 붙임
	return !flush(mycard) && numstr_arr_match(mycard, "10", "J", "Q", "K", "A");
}

_Bool back_straight(struct card mycard[])
{
	return !flush(mycard) && numstr_arr_match(mycard, "A", "2", "3", "4", "5");
}

_Bool straight(struct card mycard[])
{
	return !flush(mycard) && straight_num_check(mycard);
}

_Bool triple(struct card mycard[])
{
	return n_of_a_kind_count(mycard, 3) == 1;
}

_Bool two_pair(struct card mycard[])
{
	return n_of_a_kind_count(mycard, 2) == 2;
}

_Bool one_pair(struct card mycard[])
{
	return n_of_a_kind_count(mycard, 2) == 1;
}
