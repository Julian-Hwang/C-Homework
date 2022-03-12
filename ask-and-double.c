#include <stdio.h>
#include <string.h>

struct values //구조체를 이용해 값을 입력받을 변수 4개를 생성해준다.
{
	int n1, n2;
	double x1, x2;
};

void print_values(struct values *s1) //변수를 출력해줄 함수이다.
{
	printf("n1=%d, n2=%d, x1=%f, x2=%f\n", s1->n1, s1->n2, s1->x1, s1->x2);
}

void double_values(struct values *s1) //입력받은 변수를 2배로 곱해준다.
{
	s1->n1 = s1->n1 * 2;
	s1->n2 = s1->n2 * 2;
	s1->x1 = s1->x1 * 2;
	s1->x2 = s1->x2 * 2;
}

int main()
{
	struct values s; //처음에 선언한 구조체를 s로 선언한다.

	s.n1 = 1; //변수를 입력받는다.
	s.n2 = 2;
	s.x1 = 0.1;
	s.x2 = 0.2;

	print_values(&s); //처음 입력받은 변수를 출력한다.
	double_values(&s); //두배로 곱해주는 함수로 변수를 곱해준다.
	print_values(&s); //두배로 곱해진 변수를 출력한다.

	return 0;
}
