#include <math.h>
#include <stdio.h>

//4. ctg(x) (вычислите сумму первых 5 членов р€да)
double ctg(double x) {
	
	double result;
	double cos, sin;

	__asm {

		finit
		fld1; наращивает счетчик
		fld1; 1 st(5) здесь хранитс€ текущее значение факториала
		fld1; 2 st(4) здесь хранитс€ множитель дл€ факториала

		fld		qword ptr x; тут собираем общий результат st(3)
		fldz;	тут собираем общий член st(2)
		fld		qword ptr x; st(1) немен€ющийс€ x
		fld		qword ptr x; x^n st(0)

		mov		ecx, 10
		mov		eax, 2
	LOOP_FOR_COMMON_TERM_SIN:

		;вычисл€ем x^n
		fmul	st(0), st(1)
		fmul	st(0), st(1)
		
		fxch	st(2); начинаем собирать общий член
		fadd	st(0), st(2)

		;вычисл€ем факториал x! -> (x+2)!
		fxch	st(4)
		fadd	st(0), st(6); наращиваем коэффициент
		fmul	st(5), st(0) ;наращиваем факториал
		fadd	st(0), st(6); наращиваем коэффициент
		fmul	st(5), st(0); наращиваем факториал
		fxch	st(4)

		;делим n*x^n на факториал
		fdiv	st(0), st(5)

		mov		edx, ecx
		and		edx, 1
		cmp		edx, 0
		je		IS_ODD_SIN
		jmp		IS_EVEN_SIN

	IS_ODD_SIN:
		fchs

	IS_EVEN_SIN:
		;суммируем общий член
		fadd	st(3), st(0)
		
		;готовимс€ к новому циклу
		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_SIN

		fxch	st(3)
		fstp	qword ptr sin


		;теперь считаем косинус
		finit
		fld1; наращивает счетчик
		fld1; 2 st(5) здесь хранитс€ текущее значение факториала

		fadd	st(0), st(0)

		fld1; 2 st(4) здесь хранитс€ множитель дл€ факториала

		fadd	st(0), st(0)

		fld1	; тут собираем общий результат st(3)
		fldz;	тут собираем общий член st(2)
		fld		qword ptr x; st(1) немен€ющийс€ x
		fld1	; x^n st(0)

		mov		ecx, 10
		mov		eax, 2
	LOOP_FOR_COMMON_TERM_COS:

		;вычисл€ем x^n
		fmul	st(0), st(1)
		fmul	st(0), st(1)

		fxch	st(2); начинаем собирать общий член
		fadd	st(0), st(2)

		;делим n* x^ n на факториал
		fdiv	st(0), st(5)

		; вычисл€ем факториал x!-> (x + 2)!
		fxch	st(4)
		fadd	st(0), st(6); наращиваем коэффициент
		fmul	st(5), st(0); наращиваем факториал
		fadd	st(0), st(6); наращиваем коэффициент
		fmul	st(5), st(0); наращиваем факториал
		fxch	st(4)

		mov		edx, ecx
		and		edx, 1
		cmp		edx, 0
		je		IS_ODD_COS
		jmp		IS_EVEN_COS

	IS_ODD_COS:
		fchs

	IS_EVEN_COS:
		;суммируем общий член
		fadd	st(3), st(0)

		; готовимс€ к новому циклу
		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_COS

		fxch	st(3)
		fstp	qword ptr cos

		;наконец, считаем котангенс
		finit
		fld		qword ptr sin
		fld		qword ptr cos
		fdiv	st(0), st(1)
		fstp	qword ptr result

	}
	return result;
}