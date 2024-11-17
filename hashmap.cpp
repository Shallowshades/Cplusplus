#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <sstream>
#include <forward_list>
#include <unordered_map>

using namespace std;

const double eps = 1e-6;

using pii = pair<int, int>;
using pdd = pair<double, double>;
using vec = pair<double, double>;

/// <summary>
/// unordered_map
/// </summary>
template<typename key_type, typename value_type>
class hashmap {
public:
    hashmap() {
        m_iSize = 0;
        m_iHashVal = 1e3 + 7;
        m_vecNums.resize(m_iHashVal);
    }
    ~hashmap() = default;

    size_t size() const { return m_iSize; }

    /// <summary>
    /// 查询是否存在
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    bool find(const key_type& key) const {
        size_t idx = hash<key_type>()(key) % m_iHashVal;
        for (auto& elem : m_vecNums[idx]) {
            if (elem.first == key)
                return true;
        }
        return false;
    }

    /// <summary>
    /// 获取对于key的value 
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    value_type& get(const key_type& key) {
        //std::cout << "get reference" << std::endl;
        size_t idx = hash<key_type>()(key) % m_iHashVal;
        for (auto& elem : m_vecNums[idx]) {
            if (elem.first == key)
                return elem.second;
        }
        ++m_iSize;
        m_vecNums[idx].push_front({ key, value_type() });
        return m_vecNums[idx].front().second;
    }

    //TODO: 使用[]赋值时,查找不到,如何转为赋值
    // 先set一个赋值? 如何判断其为赋值情况而不是获取情况
    // 临时构造一个 (非常消耗)

    /// <summary>
    /// 重载[], 获取相对于key的value reference
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    value_type& operator[] (key_type key) {
        return get(key);
    }

    /// <summary>
    /// 设定key的value
    /// </summary>
    /// <param name="key"></param>
    /// <param name="val"></param>
    void set(const key_type& key, const value_type& val) {

        size_t idx = hash<key_type>()(key) % m_iHashVal;

        for (auto& elem : m_vecNums[idx]) {
            if (elem.first == key) {
                elem.second = val;
                return;
            }
        }
        // error
        ++m_iSize;
        m_vecNums[idx].push_front(pair<key_type, value_type>{key, val});
    }

    /// <summary>
    /// 删除key的键值对
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    bool earse(const key_type& key) {
        size_t idx = hash<key_type>()(key) % m_iHashVal;
        if (!m_vecNums[idx].empty()) {
            for (auto& elem : m_vecNums[idx]) {
                if (elem.first == key) {
                    m_vecNums[idx].remove(elem);
                    --m_iSize;
                    return true;
                }
            }
        }
        return false;
    }

    //private:
public:

    // TODO: 扩容的触发机制 如何判定效率低下?


    /// <summary>
    /// 扩容
    /// </summary>
    void expansion() {
        // 获取大于hashval 2倍的一个质数
        size_t newHashVal = get_next_prime();
        VecFListPKV tmp(newHashVal);
        for (auto& flist : m_vecNums) {
            for (auto& elem : flist) {
                size_t tmpIdx = hash<key_type>()(elem.first) % newHashVal;
                //size_t idx = hash<key_type>()(elem.first) % m_iHashVal;
                tmp[tmpIdx].push_front(std::move(elem));
            }
        }
        m_iHashVal = newHashVal;
        m_vecNums.swap(tmp);
    }
    /// <summary>
    /// 获取下一个质数
    /// </summary>
    /// <returns></returns>
    size_t get_next_prime() {
        size_t num = (m_iHashVal << 1) + 1;
        for (size_t i = num; ; ++i) {
            bool isPrime = true;
            for (size_t j = 3; j * j <= i; ++j) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return i;
        }
    }

private:
    using VecFListPKV = vector<forward_list<pair<key_type, value_type>>>;
    VecFListPKV m_vecNums;		// 存储数组
    size_t m_iHashVal;			// Hash值
    size_t m_iSize;				// 存储数目
};


int main() {

    try {
        hashmap<int, int> m;
        m.set(2, 10);
        m.set(1009, 10);
        m.set(20, 100);
        m.set(200, 1000);
        //std::cout << m.hash() << std::endl;
        std::cout << m.get(2) << std::endl;
        std::cout << m.get(20) << std::endl;
        std::cout << m.get(200) << std::endl;
        m.expansion();
        //std::cout << m.hash() << std::endl;
        std::cout << m.get(2) << std::endl;
        std::cout << m.get(20) << std::endl;
        std::cout << m.get(200) << std::endl;
        std::cout << m.get(1009) << std::endl;
        std::cout << m.size() << std::endl;

        m[2] = 11;
        m[20] = 111;
        m[200] = 1111;

        std::cout << m[2] << std::endl;
        std::cout << m[20] << std::endl;
        std::cout << m[200] << std::endl;
        m[2001] = 200;
        std::cout << m[2001] << std::endl;
        std::cout << m.size() << std::endl;

        m.earse(20);
        std::cout << m.size() << std::endl;
        std::cout << m[2] << std::endl;
        std::cout << m[200] << std::endl;
        std::cout << m[2001] << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

