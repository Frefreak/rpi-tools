#!/usr/bin/env python

import sys

# <PREAMBLE> + <1 bit reverse separator> <8 bit msg length> + <msg>

# length in micro seconds for one bit
BIT_LEN = 512

# prefix to identify a message start
PREAMBLE = "c4r50nz"

pin = 2
init_level = 0

recv = "digitalRead(pin)"

preamble_bits = ''.join([bin(ord(ch))[2:] for ch in PREAMBLE])
preamble_bits = "10" * 10 + "10010110"

print(preamble_bits, file=sys.stderr)

def gen_states(n, code):
    return f"""case {n}: {code}; break;"""

states = [gen_states(0, f"if ({recv} == 1) {{state = 1; timer_init();}}")]

while preamble_bits[0] == '0':
    preamble_bits = preamble_bits[1:]

prev = None
count = None
bit_pattern = []
for ch in preamble_bits:
    if ch != prev:
        if prev:
            bit_pattern.append((prev, count))
        prev = ch
        count = 1
    else:
        count += 1
bit_pattern.append((prev, count))
print(bit_pattern, file=sys.stderr)
for idx, (level, cnt) in enumerate(bit_pattern):
    states.append(gen_states(idx + 1, f"""Serial.print("State {idx+1} ");temp = check_passed_time(); Serial.println(temp); if (round(temp/ {BIT_LEN}) == {cnt}) {{state = {idx + 2};}} else {{state = 0;}}"""))

states.append(gen_states(len(bit_pattern) + 1, "{detachInterrupt(digitalPinToInterrupt(pin)); handle_message(); attachInterrupt(digitalPinToInterrupt(pin), notified, CHANGE);}"))


# ================================
print(f"""volatile unsigned long mark;
volatile bool has_data = 0;
long temp;
int pin = {pin};
bool buffer[256];
void timer_init() {{
  mark = micros();
}}

unsigned long check_passed_time() {{
  unsigned long now = micros();
  unsigned long diff = now - mark;
  if (diff < 0)
    diff += 0xffffffff;
  mark = now;
  return diff;
}}

void real_handle_msg(int len) {{
  Serial.println(len);
}}

void handle_message() {{
  int len = 0;
  delayMicroseconds({BIT_LEN / 2});
  for (int i = 0; i < 8; i++) {{
    len = (len << 1) | {recv};
    delayMicroseconds({BIT_LEN});
  }}
  for (int i = 0; i < len; i++) {{
    buffer[i] = {recv};
    delayMicroseconds({BIT_LEN});
  }}
  real_handle_msg(len);
}}

void notified() {{
  has_data = 1;
}}

void setup() {{
  attachInterrupt(digitalPinToInterrupt(pin), notified, CHANGE);
  Serial.begin(115200);
  pinMode(pin, INPUT);
}}

void loop() {{
  int state = 0;
  while (1) {{
    while (!has_data) ;
    has_data = 0;
    switch (state) {{
""")
for st in states:
    print('    ' + st)

print("""
    }
  }
}
""")
