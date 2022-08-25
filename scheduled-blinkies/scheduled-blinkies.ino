// To handle base case of below recursive
// Variadic function Template
void print() {
}

// Variadic function Template that takes
// variable number of arguments and prints
// all of them.
template <typename T, typename... Types>
  void print(T var1, Types... var2) {

  print(var2...);
}

void setup() {
  print(1, 2, 3.14,
        "Pass me any "
        "number of arguments",
        "I will print\n");

}

void loop() {

}
