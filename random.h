#pragma once

#include <stdlib.h>

#define SEED_ARRAY_SIZE 56
#define MSEED 161803398

// Structure to hold the state of the random number generator
typedef struct {
    int next_index;
    int next_p_index;
    int seed_array[SEED_ARRAY_SIZE];
} random_state_t;

// Initialize the random number generator with a seed
void random_init(random_state_t* state, int seed);

// Generate the next random number in the sequence
int random_internal_sample(random_state_t* state);

// Generate a random integer within the specified range [min_value, max_value]
int random_next(random_state_t* state, int min_value, int max_value);

// Generate a random integer between 0 (inclusive) and max_value (exclusive)
int random_next_max(random_state_t* state, int max_value);

// Generate a random double between 0.0 and 1.0
double random_next_double(random_state_t* state);

// Fill a buffer with random bytes
void random_next_bytes(random_state_t* state, unsigned char* buffer, int size);

// Implementation of the functions

void random_init(random_state_t* state, int seed) {
    int mj = MSEED - abs(seed);
    state->seed_array[55] = mj;
    int mk = 1;

    for (int i = 1; i < 55; i++) {
        int ii = (21 * i) % 55;
        state->seed_array[ii] = mk;
        mk = mj - mk;
        if (mk < 0) {
            mk += INT_MAX;
        }
        mj = state->seed_array[ii];
    }

    for (int k = 1; k < 5; k++) {
        for (int i = 1; i < SEED_ARRAY_SIZE; i++) {
            state->seed_array[i] -= state->seed_array[1 + (i + 30) % 55];
            if (state->seed_array[i] < 0) {
                state->seed_array[i] += INT_MAX;
            }
        }
    }

    state->next_index = 0;
    state->next_p_index = 21;
}

int random_internal_sample(random_state_t* state) {
    int locINext = state->next_index;
    int locINextp = state->next_p_index;

    if (++locINext >= SEED_ARRAY_SIZE) {
        locINext = 1;
    }
    if (++locINextp >= SEED_ARRAY_SIZE) {
        locINextp = 1;
    }

    int retVal = state->seed_array[locINext] - state->seed_array[locINextp];

    if (retVal < 0) {
        retVal += INT_MAX;
    }

    state->seed_array[locINext] = retVal;
    state->next_index = locINext;
    state->next_p_index = locINextp;

    return retVal;
}

int random_next(random_state_t* state, int min_value, int max_value) {
    if (min_value > max_value) {
        return -1;  // Error: invalid range
    }

    long range = (long)max_value - (long)min_value;
    return (int)((double)random_internal_sample(state) * ((double)range / INT_MAX)) + min_value;
}

int random_next_max(random_state_t* state, int max_value) {
    if (max_value < 0) {
        return -1;  // Error: invalid max value
    }

    return (int)((double)random_internal_sample(state) * ((double)max_value / INT_MAX));
}

double random_next_double(random_state_t* state) {
    return (double)random_internal_sample(state) * (1.0 / INT_MAX);
}

void random_next_bytes(random_state_t* state, unsigned char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = (unsigned char)(random_internal_sample(state) % 256);
    }
}