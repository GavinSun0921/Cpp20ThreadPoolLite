# Cpp20ThreadPoolLite

**Cpp20ThreadPoolLite** 是一个基于 C++20 标准实现的轻量级线程池，旨在帮助学习和掌握线程池的基本概念和实现细节。该项目展示了如何利用现代 C++20 特性构建一个高效的线程池，并通过计算圆周率的示例程序展示其使用方式。

## 项目结构
```text
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
├── include
│   └── thread_pool_lite.hpp
└── main.cpp
```
- CMakeLists.txt: CMake 构建配置文件。
- LICENSE: 许可证文件，详细说明了项目的使用和分发条款。
- README.md: 本文档，提供项目的详细信息和使用说明。
- build/: 构建目录，包含编译生成的文件。
- include/: 头文件目录，包含 thread_pool_lite.hpp 文件。
- main.cpp: 示例程序，演示了如何使用线程池计算圆周率。

## 示例程序
`main.cpp` 文件中包含了一个示例程序，该程序使用线程池计算圆周率 (π) 的值。以下是示例代码：
```cpp
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

```

该程序使用 **ThreadPoolExecutor** 类来并行计算圆周率，展示了如何提交任务到线程池，并汇总结果。