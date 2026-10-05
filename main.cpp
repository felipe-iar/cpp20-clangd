#include <array>
#include <cstdint>
#include <span>


int main() {

  std::array<uint8_t, 2U> testArray { 0U, 1U };
  std::span<uint8_t> testSpan { testArray };
  const bool test = not false;

  return test;
}
