#!/bin/bash

#---------------------------------------------------------------------
# YOU NEED TO ADD THE FLAG -fsanitize=thread TO YOUR COMPILER/MAKEFILE
# THE TESTS ARE BASED ON EXIT CODE, IT SHOULD BE EITHER 0 OR 1 FOR SUCCES
#---------------------------------------------------------------------

# Check if the executable is run with "bonus" as the second argument
if [[ $# -lt 1 || "$1" != "bonus" ]]; then
    PHILO="philo"
else
	PHILO="philo_bonus"
fi

# Compile the philo executable
make -C $PHILO

# Define the path to the philo executable
PHILO_EXEC="./$PHILO/$PHILO"

# Function to run fsanitize=thread test
run_tsan_test() {
	local TEST_NAME="$1"
	local TIMEOUT="10"
	local COMMAND="$PHILO_EXEC ${@:2}"  # Get all arguments after the first two
	shift
	echo -n "Running $TEST_NAME ... "
	timeout "$TIMEOUT" $COMMAND &> /dev/null
	local EXIT_CODE=$?
	if [ $EXIT_CODE -eq 0 ] || [ $EXIT_CODE -eq 1 ]; then
		echo -e "\e[32mOK :)\e[0m"
	elif [ $EXIT_CODE -eq 124 ]; then
		echo -e "\e[31mTimeout: No philosopher died :(\e[0m"
	else
		echo -e "\e[31mThreadSanitizer error\e[0m"
		$COMMAND
	fi
}

# Function to run a test with a timeout
run_test_with_timeout() {
	local TEST_NAME="$1"
	local TIMEOUT="10"
	local COMMAND="$PHILO_EXEC ${@:2}"  # Get all arguments after the first two
	echo -n "Running $TEST_NAME ... "
	if timeout "$TIMEOUT" $COMMAND &> /dev/null; then
		echo -e "\e[31mSomeone died :(\e[0m"
	else
		echo -e "\e[32mOK :)\e[0m"
	fi
}

# Test case 1: Run philo with 1 philosopher
run_tsan_test "TEST 1" 1 800 200 200

# Test case 2: Run philo with 5 philosophers, no one should die; break after 10 seconds
run_test_with_timeout "TEST 2" 5 800 200 200

# Test case 3: Run philo with 5 philosophers, each needing to eat 7 times
run_tsan_test "TEST 3" 5 800 200 200 7

# Test case 4: Run philo with 4 philosophers, no one should die; break after 10 seconds
run_test_with_timeout "TEST 4" 4 410 200 200

# Test case 5: Run philo with 4 philosophers, setting time to die, eat, and sleep to 0
run_tsan_test "TEST 5" 4 0 0 0

# Test case 6: Run philo with 4 philosophers, on should die
run_tsan_test "TEST 6" 4 310 200 100

make fclean -C $PHILO
