# Random Number Generator API Documentation

This document provides detailed information about a custom random number generator implementation in C.

## Overview

The API provides a set of functions for generating random numbers with various distributions and formats. It uses a state-based approach, allowing for multiple independent random number generators to be used simultaneously.

## Types

### `random_state_t`

```c
typedef struct {
    int next_index;
    int next_p_index;
    int seed_array[SEED_ARRAY_SIZE];
} random_state_t;
```

A structure that holds the state of the random number generator.

- `next_index`: The next index in the seed array to be used
- `next_p_index`: The next p-index in the seed array to be used
- `seed_array`: An array of 56 integers used to generate random numbers

## Constants

- `SEED_ARRAY_SIZE`: Set to 56, defines the size of the seed array
- `MSEED`: Set to 161803398, used in the initialization process

## Functions

### `random_init`

```c
void random_init(random_state_t* state, int seed);
```

Initializes a random number generator state with a given seed.

#### Parameters
- `state`: Pointer to the random state structure to initialize
- `seed`: An integer seed value

#### Description
This function sets up the initial state of the random number generator. It uses the provided seed to generate a sequence of numbers that will be used for subsequent random number generation.

---

### `random_internal_sample`

```c
int random_internal_sample(random_state_t* state);
```

Generates the next random number in the sequence.

#### Parameters
- `state`: Pointer to the current random state

#### Returns
An integer between 0 and INT_MAX

#### Description
This is an internal function that generates the next random number in the sequence. It updates the state of the generator and returns a new random value.

---

### `random_next`

```c
int random_next(random_state_t* state, int min_value, int max_value);
```

Generates a random integer within a specified range.

#### Parameters
- `state`: Pointer to the current random state
- `min_value`: The minimum value (inclusive)
- `max_value`: The maximum value (inclusive)

#### Returns
A random integer between min_value and max_value, or -1 if min_value > max_value

#### Description
This function generates a random integer that falls within the specified range [min_value, max_value].

---

### `random_next_max`

```c
int random_next_max(random_state_t* state, int max_value);
```

Generates a random integer between 0 and a specified maximum value.

#### Parameters
- `state`: Pointer to the current random state
- `max_value`: The maximum value (exclusive)

#### Returns
A random integer between 0 (inclusive) and max_value (exclusive), or -1 if max_value < 0

#### Description
This function generates a random integer that is less than the specified maximum value.

---

### `random_next_double`

```c
double random_next_double(random_state_t* state);
```

Generates a random double between 0.0 and 1.0.

#### Parameters
- `state`: Pointer to the current random state

#### Returns
A random double between 0.0 (inclusive) and 1.0 (exclusive)

#### Description
This function generates a random floating-point number in the range [0.0, 1.0).

---

### `random_next_bytes`

```c
void random_next_bytes(random_state_t* state, unsigned char* buffer, int size);
```

Fills a buffer with random bytes.

#### Parameters
- `state`: Pointer to the current random state
- `buffer`: Pointer to the buffer to fill with random bytes
- `size`: The number of bytes to generate

#### Description
This function fills the provided buffer with random bytes. It generates 'size' number of random bytes and stores them in the buffer.

## Example Usage

```c
random_state_t state;
random_init(&state, 12345); // Initialize with seed 12345

int random_int = random_next(&state, 1, 100); // Get random int between 1 and 100
double random_float = random_next_double(&state); // Get random double between 0 and 1

unsigned char buffer[10];
random_next_bytes(&state, buffer, 10); // Fill buffer with 10 random bytes
```

## Notes

- The random number generator uses a variation of the subtractive random number generator algorithm
- It's not cryptographically secure and should not be used for security purposes
- The period of the random number generator is approximately 2^55

