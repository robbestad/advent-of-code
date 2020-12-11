#include <benchmark/benchmark.h>
#include "source/2020/7.h"
#include "source/2020/7_2.h"
#include "source/2020/8.h"
#include "source/2020/8_2.h"
#include "source/2020/9.h"
#include "source/2020/10.h"
#include "source/2019/1.h"
#include "source/2020/11.h"

/*
#include "source/2020/12.h"
#include "source/2020/13.h"
#include "source/2020/14.h"
#include "source/2020/15.h"
#include "source/2020/16.h"
#include "source/2020/17.h"
#include "source/2020/18.h"
#include "source/2020/19.h"
#include "source/2020/20.h"
#include "source/2020/21.h"
#include "source/2020/22.h"
#include "source/2020/23.h"
#include "source/2020/24.h"
#include "source/2020/25.h"

 */
static void BM_2019_2(benchmark::State &state) {
    auto day2019input = day2019_1::parse_input("input/2019_1.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day2019_1::part2(day2019input));
    }
}



static void BM_7_1(benchmark::State &state) {
    day7::parse_input("input/7_input.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day7::solve());
    }
}

static void BM_7_2(benchmark::State &state) {
    day7b::parse_input("input/7_input.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day7b::solve());
    }
}

static void BM_8_1(benchmark::State &state) {
    day8::parse_input("input/8_input.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day8::solve());
    }
}

static void BM_8_2(benchmark::State &state) {
    day8_2::parse_input("input/8_input.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day8_2::solve());
        benchmark::ClobberMemory();
    }
}

static void BM_9_1_fast(benchmark::State &state) {
    day9::parse_input("input/9.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day9::part1fast());
    }
}
static void BM_9_1_slow(benchmark::State &state) {
    day9::parse_input("input/9.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day9::part1slow());
    }
}

static void BM_9_2_Kent(benchmark::State &state) {
    day9::parse_input("input/9.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day9::part2());
    }
}

static void BM_10_2(benchmark::State &state) {
    auto input = day10::parse_input("input/10.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day10::count(input));
    }
}
static void BM_10_2_FAST(benchmark::State &state) {
    auto input = day10::parse_input("input/10.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day10::part2fast(input));
    }
}

static void BM_11_1(benchmark::State &state) {
    auto input = day11::parse_input("input/11.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day11::part1(input));
    }
}
static void BM_11_2(benchmark::State &state) {
    auto input = day11::parse_input("input/11.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day11::part2(input));
    }
}
/*
static void BM_10_2(benchmark::State &state) {
    day10::parse_input("input/10_input");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day10::part2());
    }
}
*/

//BENCHMARK(BM_7_1)->Unit(benchmark::kMillisecond);
//BENCHMARK(BM_7_2)->Unit(benchmark::kMillisecond);
//BENCHMARK(BM_8_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_8_1)->RangeMultiplier(2)->Range(1<<0, 1<<12)->Complexity()->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_8_2)->Unit(benchmark::kMillisecond);

//BENCHMARK(BM_9_1_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_9_1_2)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_9_1_fast)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_9_1_slow)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_9_2_Kent)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_10_2)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_10_2_FAST)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_2019_2)->Unit(benchmark::kMicrosecond);

BENCHMARK(BM_11_1)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_11_2)->Unit(benchmark::kMillisecond);

/*
BENCHMARK(BM_11_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_11_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_12_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_12_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_13_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_13_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_14_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_14_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_15_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_15_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_16_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_16_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_17_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_17_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_18_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_10_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_19_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_19_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_20_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_20_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_21_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_21_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_22_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_22_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_23_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_23_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_24_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_24_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_25_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_25_2)->Unit(benchmark::kMicrosecond);
*/

BENCHMARK_MAIN();