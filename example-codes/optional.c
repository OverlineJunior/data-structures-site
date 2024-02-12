#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int data;
	bool is_something;
} Optional;

Optional something(int data) {
	return (Optional) {
		.data = data,
		.is_something = true
	};
}

Optional nothing(void) {
	return (Optional) {
		.data = 0,
		.is_something = false
	};
}

int expect_something(Optional opt) {
	if (opt.is_something) {
		return opt.data;
	} else {
		printf("Error: Expected something, got nothing\n");
		exit(EXIT_FAILURE);
	}
}

int main(void) {
	Optional a = something(42);
	Optional b = nothing();

	printf("Dado: %i\n", expect_something(a)); // 42.
	printf("Dado: %i\n", expect_something(b)); // Error.
}
