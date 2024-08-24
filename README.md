# Cpp20ThreadPoolLite

[![C++](https://img.shields.io/badge/support-C%2B%2B20%20or%20later-blue?style=flat&logo=cplusplus)](https://github.com/topics/cpp) [![CMake](https://img.shields.io/badge/support-v3.28%20or%20later-blue?style=flat&logo=cmake)](https://cmake.org/) [![update](https://img.shields.io/github/last-commit/GavinSun0921/Cpp20ThreadPoolLite)](https://github.com/GavinSun0921/Cpp20ThreadPoolLite/commits)

**Cpp20ThreadPoolLite** 是一个基于 C++20 标准实现的轻量级线程池，旨在帮助学习和掌握线程池的基本概念和实现细节。该项目展示了如何利用现代 C++20 特性构建一个高效的线程池，并通过计算圆周率的示例程序展示其使用方式。

## 项目结构
```text
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build (ignored)
├── include
│   └── thread_pool_lite.hpp
└── main.cpp
```
- CMakeLists.txt: CMake 构建配置文件。
- LICENSE: 许可证文件，详细说明了项目的使用和分发条款。
- README.md: 本文档，提供项目的详细信息和使用说明。
- build/: 构建目录，包含编译生成的文件。（未同步）
- include/: 头文件目录，包含 thread_pool_lite.hpp 文件。
- main.cpp: 示例程序，演示了如何使用线程池计算圆周率。

## 示例程序
`main.cpp` 文件中包含了一个示例程序，该程序使用线程池计算圆周率 (π) 的值。

计算圆周率的方法是 **莱布尼茨级数**（Leibniz series）的变种形式，它是一种经典的计算 π（圆周率）的无穷级数。具体来说，这种方法利用了如下的公式：

$$
\pi = 4 \times \left ( 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \cdots \right )
$$

公式可以写成：

$$
\pi = 4 \times \sum_{k=0}^{\infty} \frac{(-1)^k}{2k + 1}
$$

这种方法的**收敛性**比较慢，也就是说，需要计算非常多的项才能得到较为准确的 π 值。不过，使用并行计算可以一定程度上加速这个过程。以下是示例代码：
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

### 并行计算

该程序使用 **ThreadPoolExecutor** 类来并行计算圆周率，代码中使用了一个线程池，将每一项的计算任务分配给不同的线程，从而并行计算多个项的值。每个线程计算一个 $\frac{(-1)^k}{2k+1}$ 项，然后通过 `std::future` 获取这些结果并累加，最终得到 π 的近似值。

## 许可证
该项目使用 MIT 许可证。

## 贡献

欢迎贡献代码和提出建议！请参阅 [贡献指南](https://docs.github.com/en/get-started/exploring-projects-on-github/contributing-to-a-project) 了解更多信息。

