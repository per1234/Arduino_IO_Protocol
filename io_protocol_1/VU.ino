#define N1 21
#define N2 28
#define N3 35
#define N4 42
#define N5 49
#define N6 56
#define N7 63
#define N8 70

#define L1 2
#define L2 3
#define L3 4
#define L4 5
#define L5 6
#define L6 7
#define L7 8
#define L8 9

void VU_setup() {
  pinMode (L1, OUTPUT);
  pinMode (L2, OUTPUT);
  pinMode (L3, OUTPUT);
  pinMode (L4, OUTPUT);
  pinMode (L5, OUTPUT);
  pinMode (L6, OUTPUT);
  pinMode (L7, OUTPUT);
  pinMode (L8, OUTPUT);
}

void VU_up (int val) {
  digitalWrite (L1, (val>=N1));
  digitalWrite (L2, (val>=N2));
  digitalWrite (L3, (val>=N3));
  digitalWrite (L4, (val>=N4));
  digitalWrite (L5, (val>=N5));
  digitalWrite (L6, (val>=N6));
  digitalWrite (L7, (val>=N7));
  digitalWrite (L8, (val>=N8));
}

void VU_down (int val) {
  digitalWrite (L1, (val<=N1));
  digitalWrite (L2, (val<=N2));
  digitalWrite (L3, (val<=N3));
  digitalWrite (L4, (val<=N4));
  digitalWrite (L5, (val<=N5));
  digitalWrite (L6, (val<=N6));
  digitalWrite (L7, (val<=N7));
  digitalWrite (L8, (val<=N8));
}

