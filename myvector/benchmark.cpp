#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cassert>
#include <random>
#include "myvector.hpp"

using namespace std::chrono;

// ─── Timer helper ────────────────────────────────────────────────────────────
struct Timer {
    time_point<high_resolution_clock> start;
    std::string label;
    Timer(const std::string& l) : label(l), start(high_resolution_clock::now()) {}
    double stop() {
        auto end = high_resolution_clock::now();
        return duration<double, std::milli>(end - start).count();
    }
};

// ─── Correctness tests ───────────────────────────────────────────────────────
void test_correctness() {
    std::cout << "\n=== CORRECTNESS TESTS ===\n";

    // push_back + size
    {
        myvector<int> v;
        for (int i = 0; i < 100; ++i) v.push_back(i);
        assert(v.size() == 100);
        for (int i = 0; i < 100; ++i) assert(v[i] == i);
        std::cout << "[PASS] push_back / operator[]\n";
    }

    // copy constructor
    {
        myvector<int> a;
        for (int i = 0; i < 50; ++i) a.push_back(i);
        myvector<int> b = a;
        assert(b.size() == a.size());
        for (size_t i = 0; i < a.size(); ++i) assert(b[i] == a[i]);
        b[0] = 999;
        assert(a[0] == 0); // deep copy check
        std::cout << "[PASS] copy constructor (deep copy)\n";
    }

    // move constructor
    {
        myvector<int> a;
        for (int i = 0; i < 50; ++i) a.push_back(i);
        myvector<int> b = std::move(a);
        assert(b.size() == 50);
        assert(a.size() == 0); // a must be empty
        std::cout << "[PASS] move constructor\n";
    }

    // copy assignment
    {
        myvector<int> a, b;
        for (int i = 0; i < 30; ++i) a.push_back(i);
        b = a;
        assert(b.size() == a.size());
        b[0] = 999;
        assert(a[0] == 0);
        std::cout << "[PASS] copy assignment (deep copy)\n";
    }

    // move assignment
    {
        myvector<int> a, b;
        for (int i = 0; i < 30; ++i) a.push_back(i * 2);
        b = std::move(a);
        assert(b[0] == 0 && b[1] == 2);
        assert(a.size() == 0);
        std::cout << "[PASS] move assignment\n";
    }

    // self-assignment
    {
        myvector<int> a;
        for (int i = 0; i < 10; ++i) a.push_back(i);
        a = a;
        assert(a.size() == 10 && a[5] == 5);
        std::cout << "[PASS] self-assignment\n";
    }

    std::cout << "All correctness tests passed.\n";
}

// ─── Benchmark helpers ───────────────────────────────────────────────────────
constexpr int N_SMALL  = 100'000;
constexpr int N_LARGE  = 5'000'000;
constexpr int N_REPEAT = 5;

template<typename Vec>
double bench_push_back(int n) {
    Timer t("push_back");
    Vec v;
    for (int i = 0; i < n; ++i) v.push_back(i);
    return t.stop();
}

template<typename Vec>
double bench_copy(int n) {
    Vec src;
    for (int i = 0; i < n; ++i) src.push_back(i);
    Timer t("copy");
    Vec dst = src;
    return t.stop();
}

template<typename Vec>
double bench_sequential_read(int n) {
    Vec v;
    for (int i = 0; i < n; ++i) v.push_back(i);
    Timer t("read");
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum += v[i];
    (void)sum;
    return t.stop();
}

template<typename Vec>
double bench_random_access(int n) {
    Vec v;
    for (int i = 0; i < n; ++i) v.push_back(i);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, n - 1);
    Timer t("random");
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum += v[dist(rng)];
    (void)sum;
    return t.stop();
}

// ─── Run + print a benchmark row ─────────────────────────────────────────────
template<typename F1, typename F2>
void run_bench(const std::string& name, F1 fn_my, F2 fn_std) {
    double my_total = 0, std_total = 0;
    for (int i = 0; i < N_REPEAT; ++i) {
        my_total  += fn_my();
        std_total += fn_std();
    }
    double my_avg  = my_total  / N_REPEAT;
    double std_avg = std_total / N_REPEAT;
    double ratio   = my_avg / std_avg;

    std::printf("  %-30s  my: %7.2f ms   std: %7.2f ms   ratio: %.2fx %s\n",
        name.c_str(), my_avg, std_avg, ratio,
        ratio < 1.1 ? "[OK]" : ratio < 2.0 ? "[SLOW]" : "[VERY SLOW]");
}

// ─── Main ────────────────────────────────────────────────────────────────────
int main() {
    test_correctness();

    std::cout << "\n=== BENCHMARKS (average of " << N_REPEAT << " runs) ===\n\n";

    std::cout << "-- Small N = " << N_SMALL << " --\n";
    run_bench("push_back (int)",
        [] { return bench_push_back<myvector<int>>(N_SMALL); },
        [] { return bench_push_back<std::vector<int>>(N_SMALL); });

    run_bench("copy constructor",
        [] { return bench_copy<myvector<int>>(N_SMALL); },
        [] { return bench_copy<std::vector<int>>(N_SMALL); });

    run_bench("sequential read",
        [] { return bench_sequential_read<myvector<int>>(N_SMALL); },
        [] { return bench_sequential_read<std::vector<int>>(N_SMALL); });

    run_bench("random access",
        [] { return bench_random_access<myvector<int>>(N_SMALL); },
        [] { return bench_random_access<std::vector<int>>(N_SMALL); });

    std::cout << "\n-- Large N = " << N_LARGE << " --\n";
    run_bench("push_back (int)",
        [] { return bench_push_back<myvector<int>>(N_LARGE); },
        [] { return bench_push_back<std::vector<int>>(N_LARGE); });

    run_bench("sequential read",
        [] { return bench_sequential_read<myvector<int>>(N_LARGE); },
        [] { return bench_sequential_read<std::vector<int>>(N_LARGE); });

    run_bench("random access",
        [] { return bench_random_access<myvector<int>>(N_LARGE); },
        [] { return bench_random_access<std::vector<int>>(N_LARGE); });

    std::cout << "\n-- push_back with std::string (move vs copy) --\n";
    run_bench("push_back (string, lvalue)",
        [] {
            myvector<std::string> v;
            std::string s = "hello_benchmark_string";
            Timer t("");
            for (int i = 0; i < N_SMALL; ++i) v.push_back(s);
            return t.stop();
        },
        [] {
            std::vector<std::string> v;
            std::string s = "hello_benchmark_string";
            Timer t("");
            for (int i = 0; i < N_SMALL; ++i) v.push_back(s);
            return t.stop();
        });

    run_bench("push_back (string, rvalue)",
        [] {
            myvector<std::string> v;
            Timer t("");
            for (int i = 0; i < N_SMALL; ++i) v.push_back(std::string("hello_benchmark_string"));
            return t.stop();
        },
        [] {
            std::vector<std::string> v;
            Timer t("");
            for (int i = 0; i < N_SMALL; ++i) v.push_back(std::string("hello_benchmark_string"));
            return t.stop();
        });

    std::cout << "\nDone.\n";
    return 0;
}