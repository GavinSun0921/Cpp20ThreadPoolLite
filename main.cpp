#include <cstdio>

#include "include/thread_pool_lite.hpp"

double worker(int k) {
  double res = 4.0 / (2 * k + 1.0);
  return k % 2 == 0 ? res : -1.0 * res;
}

double pi(int n) {
  ThreadPoolExecutor pool;
  std::vector<std::future<double>> futures;
  futures.reserve(n);
  for (int i = 0; i < n; ++i) {
    futures.push_back(pool.submit(worker, i));
  }
  double p = 0.0;
  for (auto &future : futures) {
    p += future.get();
  }
  return p;
}

int main() {
  printf("Pi = %.12f\n", pi(1'000'000));
  return 0;
}
