#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day16/sample.txt"
#else
#define INPUT_FILE "./src/day16/inputs.txt"
#endif

static char tabs[4096] = {[0 ... 4095] = '\t'};
static int table_depth = 0;

#define ptable(key, value, bits)                                            \
  do {                                                                      \
    printf("%.*s\"" key "\": { \"value\": %d, \"bits\": \"0b", table_depth, \
           tabs, value);                                                    \
    print_bits(value, bits, "\" },\n");                                     \
  } while (0)

void print_bits(uint8_t bits, uint8_t len, char *end) {
  assert(len > 0);

  for (uint8_t i = len; i > 0; i--) {
    printf("%d", (bits >> (i - 1)) & 1);
  }
  printf("%s", end);
}

// decode `n` nibbles (4 bits) from `tranmission`
size_t decode_n(char *transmission, size_t n, uint8_t out[n]) {
  size_t i;
  for (i = 0; i < n; i++) {
    char c = transmission[i];
    if (c == '\0' || c == '\n') break;

    int value = c >= '0' && c <= '9' ? c - '0' : c - 'A' + 10;
    if (value < 0 || value > 15) printf("%d %d\n", value, c);
    assert(value >= 0 && value <= 15);

    out[i] = value;
  }

  return i;
}

uint32_t nbits_at(uint8_t *packet, size_t n, size_t i) {
  uint32_t num = 0;
  for (size_t j = i; j < i + n; j++) {
    const size_t base = j / 4;
    const size_t xbit = j % 4;

    const uint8_t bits = packet[base];
    const uint8_t bitx = (bits & (1 << (3 - xbit))) != 0;

    // printf("base: %zu\txbit: %zu\tbitx: %d\n", base, xbit, bitx);
    // print_bits(packet[base], 4, "\n&");
    // print_bits(1<<3-xbit, 4, "\n");

    num = ((num) << 1) | bitx;
  }
  return num;
}

uint8_t tbits_at(uint8_t *packet, size_t i) { return nbits_at(packet, 3, i); }

void dump_packet(uint8_t *packet, size_t len) {
  for (size_t i = 0; i < len; i += 1)
    print_bits(nbits_at(packet, 4, i * 4), 4, "");
  printf("\n");
}

// return the packet lenght
void parse_packet(uint8_t *packet, uint32_t *position, uint32_t *total) {
  printf("%.*s{\n", table_depth, tabs);
  table_depth++;

  ptable("Position", *position, 32);

  uint32_t pos = *position;

  uint8_t version = tbits_at(packet, pos);
  ptable("Ver", version, 3);
  pos += 3;

  uint8_t type = tbits_at(packet, pos);
  ptable("Type", type, 3);
  pos += 3;

  *total += version;

  if (type == 4) {
    uint32_t val = 0, b = 0;
    while (pos < UINT32_MAX - 5) {
      uint32_t value = nbits_at(packet, 5, pos) & 0b11111;
      pos += 5;
      b += 4;
      val = (val << 4) | (value & 0b1111);
      if (((value >> 4) & 1) == 0) break;
    }
    ptable("Val", val, b);

  } else {
    uint8_t length_type = nbits_at(packet, 1, pos) != 0;
    ptable("LType", length_type, 3);
    pos += 1;

    if (length_type == 0) {
      uint32_t length = nbits_at(packet, 15, pos);
      ptable("Length", length, 15);
      pos += 15;

      length += pos;
      printf("%.*s\"SubPackets\": [\n", table_depth, tabs);
      while (pos < length) {
        parse_packet(packet, &pos, total);
      }
      printf("%.*s]\n", table_depth, tabs);
    } else {
      uint32_t length = nbits_at(packet, 11, pos);
      ptable("Length", length, 11);
      pos += 11;

      printf("%.*s\"SubPackets\": [\n", table_depth, tabs);
      for (size_t i = 0; i < length; i++) {
        parse_packet(packet, &pos, total);
      }
      printf("%.*s]\n", table_depth, tabs);
    }
  }
  *position = pos;

  table_depth--;
  printf("%.*s},\n", table_depth, tabs);
}

void part_one(char *input) {
  char *raw_packet = toktok(&input, "\n");

  // decode the packet
  size_t packet_len = input - raw_packet - 1;
  uint8_t *packet = calloc(packet_len, sizeof(uint8_t));

  size_t len = decode_n(raw_packet, packet_len, packet);
  printf("Packet size | hex: %zu   bin: %zu\n", packet_len, packet_len * 4);
  assert(len == packet_len);

  uint32_t result = 0;
  uint32_t position = 0;

  // dump_packet(packet, packet_len);

  // parse the packet and get the sum of the versions
  parse_packet(packet, &position, &result);

  assert(position < packet_len * 4);

  printf("Sum of all packets version: %d\n", result);
}

void part_two(char *input) {}

int main(void) {
  char *input = read_file(INPUT_FILE);

#ifdef PARTONE
  printf("Running part one...\n");
  part_one(input);
#else
  printf("Running part two...\n");
  part_two(input);
#endif

  free(input);
  return 0;
}
