CC = gcc
CFLAGS = -Wall -g

EXECUTABLE = makro
SOURCES = makro.c core/*.c debug/*.c memory/*.c structures/*.c
INCLUDE = -I include/

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(INCLUDE)

TESTS = ../tests/

.PHONY: test
test: $(EXECUTABLE)
	@count = 1; \
	totalCount = $(ls $(TESTS) | wc -l); \
	passCount = 0; \
	@for testFile in $(TESTS)/*; do \
		if ./$(EXECUTABLE) $$testFile; then \
			echo "Makro Test [$$count / $$totalCount] $$testFile: PASS"; \
			passCount = $$((passCount + 1)); \
		else \
			echo "Makro Test [$(count) / $(totalCount)] $$testFile: FAIL"; \
		fi; \
		count = $$((count + 1)); \
	
	done; \
	echo "Makro Tests [$$passCount / $$totalCount] passed";

.PHONY: clean
clean:
	del $(EXECUTABLE)
