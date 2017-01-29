#include <vector>
#include <iostream>
#include <unordered_map>

int CalculateModulo(int arg1, int arg2)
{
    std::cout << "Calculating modulo\n";
    return arg1 % arg2;
}

class ModuloCalculator
{
    class Arguments
    {
    public:
        Arguments(int first, int second)
        {
            this->first = first;
            this->second = second;
        }
        
        bool operator == (Arguments const& rhs) const
        {
            return first == rhs.first && second == rhs.second;
        }
        
        int first;
        int second;
    };
    
    struct KeyHasher
    {
        std::size_t operator()(const Arguments& k) const
        {
            return (k.first << 16) | k.second;
        }
    };
    
public:
    int Calculate(int arg1, int arg2)
    {
        Arguments args(arg1, arg2);
        std::unordered_map<Arguments, int, KeyHasher>::iterator it = m_cache.find(args);
        if (it != m_cache.end())
        {
            return it->second;
        }
        int result = CalculateModulo(arg1, arg2);
        m_cache[args] = result;
        return result;
    }
    
private:
    std::unordered_map<Arguments, int, KeyHasher> m_cache;
};

int main()
{
    ModuloCalculator calculator;
    
    std::cout << calculator.Calculate(7, 2) << "\n";
    std::cout << calculator.Calculate(12, 5) << "\n";
    std::cout << calculator.Calculate(7, 2) << "\n";
}
