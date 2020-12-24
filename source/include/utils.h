//
// Created by Sven Anders Robbestad on 08/12/2020.
//
#include <fstream>
#include <string>
#include <vector>

#ifndef AOC_UTILS_H
#define AOC_UTILS_H


namespace utils {

    template<typename T>
    std::vector<T> read_all_lines(std::string path) {
        std::string line;
        std::vector<T> lines;
        std::ifstream f(path);
        while (std::getline(f, line)) {
            if constexpr (std::is_same<T, std::string>::value) {
                lines.push_back(line);
            } else if constexpr (std::is_same<T, int>::value) {
                lines.push_back(std::stoi(line));
            } else if constexpr (std::is_same<T, long long>::value) {
                lines.push_back(std::stoll(line));
            }
        }
        f.close();
        return lines;
    }

    std::string tail(std::string const &source, size_t const length) {
        if (length >= source.size()) { return source; }
        return source.substr(source.size() - length);
    }

    std::vector<std::vector<std::string>> separate_datasets(std::vector<std::string> input) {
        std::vector<std::vector<std::string>> dataSets = {};
        std::vector<std::string> dataSet = {};
        for (auto &line : input) {
            if (line.length() == 0) {
                dataSets.push_back(dataSet);
                dataSet = {};
            } else {
                dataSet.push_back(line);
            }
        }
        if (dataSet.size() != 0) {
            dataSets.push_back(dataSet);
        }
        return dataSets;
    }

    std::vector<std::string> split(std::string s, std::string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    std::string unicode_to_utf8(int unicode) {
        std::string s;

        if (unicode >= 0 && unicode <= 0x7f)  // 7F(16) = 127(10)
        {
            s = static_cast<char>(unicode);

            return s;
        } else if (unicode <= 0x7ff)  // 7FF(16) = 2047(10)
        {
            unsigned char c1 = 192, c2 = 128;

            for (int k = 0; k < 11; ++k) {
                if (k < 6) c2 |= (unicode % 64) & (1 << k);
                else c1 |= (unicode >> 6) & (1 << (k - 6));
            }

            s = c1;
            s += c2;

            return s;
        } else if (unicode <= 0xffff)  // FFFF(16) = 65535(10)
        {
            unsigned char c1 = 224, c2 = 128, c3 = 128;

            for (int k = 0; k < 16; ++k) {
                if (k < 6) c3 |= (unicode % 64) & (1 << k);
                else if (k < 12) c2 |= (unicode >> 6) & (1 << (k - 6));
                else c1 |= (unicode >> 12) & (1 << (k - 12));
            }

            s = c1;
            s += c2;
            s += c3;

            return s;
        } else if (unicode <= 0x1fffff)  // 1FFFFF(16) = 2097151(10)
        {
            unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

            for (int k = 0; k < 21; ++k) {
                if (k < 6) c4 |= (unicode % 64) & (1 << k);
                else if (k < 12) c3 |= (unicode >> 6) & (1 << (k - 6));
                else if (k < 18) c2 |= (unicode >> 12) & (1 << (k - 12));
                else c1 |= (unicode >> 18) & (1 << (k - 18));
            }

            s = c1;
            s += c2;
            s += c3;
            s += c4;

            return s;
        } else if (unicode <= 0x3ffffff)  // 3FFFFFF(16) = 67108863(10)
        { ;  // actually, there are no 5-bytes unicodes
        } else if (unicode <= 0x7fffffff)  // 7FFFFFFF(16) = 2147483647(10)
        { ;  // actually, there are no 6-bytes unicodes
        } else;  // incorrect unicode (< 0 or > 2147483647)

        return "";
    }

    template<typename E>
    std::string toBinary(E e) noexcept {
        std::string r;
        while (e != 0) {
            r = (e % 2 == 0 ? "0" : "1") + r;
            e /= 2;
        }
        return r;
    }

    template<typename T>
    T reverse(T n, size_t b = sizeof(T) * std::numeric_limits<T>::digits) {
        T rv = 0;
        for (size_t i = 0; i < b; ++i, n >>= 1) {
            rv = (rv << 1) | (n & 0x01);
        }
        return rv;
    }

    template<typename T>
    long bin_to_dec(T n) {
        T num = n;
        auto dec_value = 0;
        // Initializing base value to 1, i.e 2^0
        auto base = 1;
        auto temp = num;
        while (temp) {
            auto last_digit = temp % 10;
            temp = temp / 10;
            dec_value += last_digit * base;
            base = base * 2;
        }
        return dec_value;
    }

    template<typename T>
    T get_digit(T n, size_t position) {
        std::vector<T> vec_digits;
        while (n > 0) {
            vec_digits.emplace_back(n % 10);
            n = n / 10;
        }
        std::reverse(vec_digits.begin(),vec_digits.end());
        return vec_digits.at(position);
    }

    template<typename T>
    std::vector<T> get_digits(T n) {
        std::vector<T> vec_digits;
        while (n > 0) {
            vec_digits.emplace_back(n % 10);
            n = n / 10;
        }
        std::reverse(vec_digits.begin(),vec_digits.end());
        return vec_digits;
    }

    template<typename T>
    std::deque<T> get_digits_to_qu(T n) {
        std::ostringstream os;
        std::string digits = os.str();
        std::deque<T> digits_qu;
        while (n > 0) {
            digits_qu.push_back(n % 10);
            n = n / 10;
        }
        return digits_qu;
    }
    template<typename T>
    void remove_intersection(const std::vector<T>& a, std::vector<T>& b){
        std::unordered_multiset<T> st;
        st.insert(a.begin(), a.end());
        st.insert(b.begin(), b.end());
        auto predicate = [&st](const T& k){ return st.count(k) > 1; };
        //a.erase(std::remove_if(a.begin(), a.end(), predicate), a.end());
        b.erase(std::remove_if(b.begin(), b.end(), predicate), b.end());
    }

    template<typename T>
    void remove_intersection_qu(std::vector<T> a, std::vector<T>& b,std::deque<T>& out){
        std::vector<T> temp{};
        for(auto val:b)
            temp.emplace_back(val);
        std::unordered_multiset<T> st;
        st.insert(a.begin(), a.end());
        st.insert(b.begin(), b.end());
        auto predicate = [&st](const T& k){ return st.count(k) > 1; };
        a.erase(std::remove_if(a.begin(), a.end(), predicate), a.end());
        out.clear();
        for(auto val:temp)
            out.push_back(val);
    }


}
#endif //AOC_UTILS_H
