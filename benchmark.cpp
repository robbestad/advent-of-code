#include <benchmark/benchmark.h>
#include "source/day_6/main.h"
#include "source/day_5/main.h"
#include "source/day_4/main.h"
#include "source/days/7.h"
#include "source/days/7_2.h"
#include "source/days/8.h"
#include "source/days/8_2.h"
#include "source/days/9.h"

/*
#include "source/days/10.h"
 #include "source/days/11.h"
#include "source/days/12.h"
#include "source/days/13.h"
#include "source/days/14.h"
#include "source/days/15.h"
#include "source/days/16.h"
#include "source/days/17.h"
#include "source/days/18.h"
#include "source/days/19.h"
#include "source/days/20.h"
#include "source/days/21.h"
#include "source/days/22.h"
#include "source/days/23.h"
#include "source/days/24.h"
#include "source/days/25.h"

 */
static void BM_4_1(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(day4::part1());
    }
}

static void BM_4_2(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(day4::part1());
    }
}

static void BM_5(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(day5::solve());
    }
}

static void BM_6_1(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(day6::part1());
    }
}

static void BM_6_2(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(day6::part2());
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

static void BM_9_1(benchmark::State &state) {
    day9::parse_input("input/9.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day9::part1());
    }
}

static void BM_9_2_Kent(benchmark::State &state) {
    day9::parse_input("input/9.txt");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day9::part2());
    }
}

/*
static void BM_10_1(benchmark::State &state) {
    day10::parse_input("input/10_input");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day10::part1());
    }
}

static void BM_10_2(benchmark::State &state) {
    day10::parse_input("input/10_input");
    for (auto _ : state) {
        benchmark::DoNotOptimize(day10::part2());
    }
}
*/

//BENCHMARK(BM_4_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_4_2)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_5)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_6_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_6_2)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_7_1)->Unit(benchmark::kMillisecond);
//BENCHMARK(BM_7_2)->Unit(benchmark::kMillisecond);
//BENCHMARK(BM_8_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_8_1)->RangeMultiplier(2)->Range(1<<0, 1<<12)->Complexity()->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_8_2)->Unit(benchmark::kMillisecond);

//BENCHMARK(BM_9_1_1)->Unit(benchmark::kMicrosecond);
//BENCHMARK(BM_9_1_2)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_9_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_9_2_Kent)->Unit(benchmark::kMicrosecond);

/*
BENCHMARK(BM_10_1)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_10_2)->Unit(benchmark::kMicrosecond);
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