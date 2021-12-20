# Advent of Code - 2021

## About

I decided to start Advent of Code this year because it looked like a cool experience (It's my very first time doing something like that), each challenge is really fun and creative. That said, I decided to do it in C, considering it's a language I have a good familiarity with.

I separated each challenge in its respective directory, consisting of a `main.c` file (the main code), `inputs.txt` (challenge input), `sample.txt` (the sample input).
There is also a lib for functions used in multiple challenges.

Each challenge is created dynamically using the `new_day.sh` script. It copy some templates to the challenge directory and update the Makefile automatically.

## Testing

To build a challenge, simply create a `build` directory and run `make dayX`, where `X` is a valid day number.

You can also build all challenges with `make all`