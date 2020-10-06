#include "PPP.hpp"

#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>

struct big {
    uint64_t data;
    uint8_t c;
    uint64_t gap;
    uint16_t ali;
    char buf[1024];
    uint8_t comment;
};

const std::vector<std::pair<int, big>> v(10000, {42, {69, 'c', 666, 65535, {0}, 255}});

const std::vector<std::pair<int, long>> v0(10000, {42, 69});

std::vector v2 {
    std::make_pair(0, 1l),
    std::make_pair(1, 2l),
    std::make_pair(2, 3l),
    std::make_pair(3, 4l),
    std::make_pair(4, 5l)
};

std::vector<std::pair<int, long>> v3 {
    {0, 1l},
    {1, 2l},
    {2, 3l},
    {3, 4l},
    {4, 5l}
};

void Index(benchmark::State &state)
{
    for (auto _ : state) {
        for (int i = 0; i < v.size(); i++) {
            benchmark::DoNotOptimize(i);
            auto [a, b] = v[i];
            benchmark::DoNotOptimize(a);
            benchmark::DoNotOptimize(b);
        }
    }

}
BENCHMARK(Index);


void Range(benchmark::State &state)
{
    for (auto _ : state) {
        for (int i = 0; auto [a, b] : v) {
            benchmark::DoNotOptimize(i++);
            benchmark::DoNotOptimize(a);
            benchmark::DoNotOptimize(b);
        }
    }
}
BENCHMARK(Range);


void Iterator(benchmark::State &state)
{
    for (auto _ : state) {
        int i = 0;
        for (auto it = std::begin(v); it != std::end(v); ++it) {
            auto [a, b] = *it;
            benchmark::DoNotOptimize(i++);
            benchmark::DoNotOptimize(a);
            benchmark::DoNotOptimize(b);
        }
    }

}
BENCHMARK(Iterator);


void EnumerateRange(benchmark::State &state)
{
    for (auto _ : state) {
        for (auto [i, p] : ppp::enumerate(v)) {
            auto [a, b] = p;
            benchmark::DoNotOptimize(i);
            benchmark::DoNotOptimize(a);
            benchmark::DoNotOptimize(b);
        }
    }
}
BENCHMARK(EnumerateRange);


void EnumerateIterator(benchmark::State &state)
{
    for (auto _ : state) {
        auto en = ppp::enumerate(v);
        for (auto it = std::begin(en); it != std::end(en); ++it) {
            auto [i, p] = *it;
            auto [a, b] = p; // auto [a, b] = it->second; // should be equivalent but is actualy x100 slower
            benchmark::DoNotOptimize(i);
            benchmark::DoNotOptimize(a);
            benchmark::DoNotOptimize(b);
        }
    }
}
BENCHMARK(EnumerateIterator);


BENCHMARK_MAIN();
