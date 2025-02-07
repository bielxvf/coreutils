build:
	mkdir build

basename: build src/basename.c
	clang -std=c23 -Wall -Wextra -Werror -o build/basename src/basename.c

cat: build src/cat.c
	clang -std=c23 -Wall -Wextra -Werror -o build/cat src/cat.c

cp: build src/cp.c
	clang -std=c23 -Wall -Wextra -Werror -o build/cp src/cp.c

echo: build src/echo.c
	clang -std=c23 -Wall -Wextra -Werror -o build/echo src/echo.c

head: build src/head.c
	clang -std=c23 -Wall -Wextra -Werror -o build/head src/head.c

ls: build src/ls.c
	clang -std=c23 -Wall -Wextra -Werror -o build/ls src/ls.c

mv: build src/mv.c
	clang -std=c23 -Wall -Wextra -Werror -o build/mv src/mv.c

tail: build src/tail.c
	clang -std=c23 -Wall -Wextra -Werror -o build/tail src/tail.c

touch: build src/touch.c
	clang -std=c23 -Wall -Wextra -Werror -o build/touch src/touch.c
