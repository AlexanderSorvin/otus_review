#include <set>
#include "ip.hpp"
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    
    try
    {
        std::vector<ip<v4>> ip_pool;
        ip_pool.reserve(1000);

        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.emplace_back(split(v.at(0), '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ip<v4>>());

        for (auto i : ip_pool)
        {
            std::cout << i << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        {
            auto first = std::find_if(ip_pool.cbegin(), ip_pool.cend(),
                                      [](const ip<v4> &e) { return e.filter(1); });

            auto last = std::find_if_not(first, ip_pool.cend(),
                                         [](const ip<v4> &e) { return e.filter(1); });

            for (auto i = first; i != last; i++)
            {
                std::cout << *i << std::endl;
            }
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        {
            auto first = std::find_if(ip_pool.cbegin(), ip_pool.cend(),
                                      [](const ip<v4> &e) { return e.filter(46, uint8_t(70)); });

            auto last = std::find_if_not(first, ip_pool.cend(),
                                         [](const ip<v4> &e) { return e.filter(46, uint8_t(70)); });

            for (auto i = first; i != last; i++)
            {
                std::cout << *i << std::endl;
            }
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        {
            for (auto i : ip_pool)
            {
                if (i.filter_mask(46))
                    std::cout << i << std::endl;
            }
        }

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
