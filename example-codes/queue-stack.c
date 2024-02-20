// The queue's implementation would be similar, with queue and dequeue functions instead of push and pop, inserting and removing a value from the beginning of the list respectively.
typedef struct {
	int values[32];
	int top;
} Stack;

Stack new_stack() {
    return (Stack) {
		.values = {},
		.top = -1
	};
}

void push(Stack* stack, int value) {
    if (stack->top >= 32)
		return;

    stack->values[stack->top] = value;
    stack->top++;
}

int pop(Stack* stack) {
	if (stack->top <= 0)
		return -1;

	stack->top--;
	return stack->values[stack->top];
}

int peek(Stack* stack) {
	if (stack->top <= 0)
		return -1;

    return stack->values[stack->top - 1];
}

int is_empty(Stack* stack) {
    return stack->top == 0;
}
