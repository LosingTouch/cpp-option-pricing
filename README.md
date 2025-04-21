# cpp-option-pricing

![CMake on multiple platforms](https://github.com/LosingTouch/cpp-option-pricing/actions/workflows/cmake-multi-platform.yml/badge.svg)

Modern‑C++ library for pricing vanilla, digital, Asian, and American options with

* **Black–Scholes** (closed form & Monte Carlo + antithetic variates)  
* **Cox–Ross–Rubinstein** binomial trees (European & American)

Written as coursework for *C++ for Finance* — now open‑sourced as a hiring portfolio.

---

## ✨ Key features

| Feature | Implementation |
|---------|----------------|
| Closed‑form Black–Scholes price & Delta | `BlackScholesPricer` |
| Monte Carlo with antithetic variance‑reduction | `BlackScholesMCPricer` |
| CRR binomial tree (pricing + early exercise) | `CRRPricer` + template `BinaryTree<T>` |
| Path‑dependent Asian options | `AsianOption`, `AsianCallOption`, `AsianPutOption` |
| American vanilla options | `AmericanCallOption`, `AmericanPutOption` |
| Cross‑platform CI | Ubuntu / macOS / Windows via GitHub Actions |

---

## 📂 Folder structure
```
include/            # .h interfaces  
src/                # .cpp implementations  
docs/               # PDF report & project spec  
tests/              # (Catch2 tests go here)  
CMakeLists.txt      # single‑file CMake build script  
.github/workflows/  # CI pipeline  
```

---

## 🛠️ Build & run

> **Prerequisites:** CMake ≥ 3.15 and a C++17 compiler  
> (g++ ≥ 9, clang ≥ 10, or MSVC ≥ 2019).

```bash
# clone
git clone https://github.com/LosingTouch/cpp-option-pricing.git
cd cpp-option-pricing

# configure + build (Release)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

```cpp
#include "BlackScholesPricer.h"

CallOption call(1.0 /*T*/, 100.0 /*K*/);
BlackScholesPricer pricer(&call, 100.0, 0.05, 0.2);
double price = pricer();   // ≈ 10.45
```

---

## 📜 License

MIT — see `LICENSE`.


