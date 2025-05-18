#ifndef main_hpp
#define main_hpp
#include <string>
#include <vector>
using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

struct HashTable
{
    Company *company_table[2000];
    bool occupied[2000];
};

long long modPower(int a, int n, int m);
Company* createCompany(const Company &company);
vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable *createHashTable(vector<Company> company_list);
void insert(HashTable *hash_table, Company company);
Company *search(HashTable *hash_table, string company_name);
void deleteHashTable(HashTable *table);

#endif