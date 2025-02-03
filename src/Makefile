# for i in $(ls *.c); do echo "${i%.*}: $i"; echo -e "\tclang -std=c23 -Wall -Wextra -Werror -o ${i%.*} $i"; done > Makefile

basename: basename.c
	clang -std=c23 -Wall -Wextra -Werror -o basename basename.c
cat: cat.c
	clang -std=c23 -Wall -Wextra -Werror -o cat cat.c
cp: cp.c
	clang -std=c23 -Wall -Wextra -Werror -o cp cp.c
echo: echo.c
	clang -std=c23 -Wall -Wextra -Werror -o echo echo.c
head: head.c
	clang -std=c23 -Wall -Wextra -Werror -o head head.c
ls: ls.c
	clang -std=c23 -Wall -Wextra -Werror -o ls ls.c
mv: mv.c
	clang -std=c23 -Wall -Wextra -Werror -o mv mv.c
tail: tail.c
	clang -std=c23 -Wall -Wextra -Werror -o tail tail.c
touch: touch.c
	clang -std=c23 -Wall -Wextra -Werror -o touch touch.c
