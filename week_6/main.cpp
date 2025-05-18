#include "function.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        cerr << "Too much arguments." << endl;
        exit(1);
    }
    else if (argc < 4)
    {
        cerr << "Not enough arguments." << endl;
        exit(2);
    }
    string input_file_path = argv[2], output_file_path = argv[3], profit_tax_file_path = argv[1];
    ifstream fin(input_file_path);
    ofstream fout(output_file_path);
    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Cannot open input file." << endl;
        exit(3);
    }
    else
    {
        vector<Company> company_list = readCompanyList(profit_tax_file_path);
        HashTable *profit_tax_table = createHashTable(company_list);
        string company;
        while (getline(fin, company))
        {
            stringstream stream(company);
            string company_name;
            getline(stream, company_name, '|');
            Company *company_found = search(profit_tax_table, company_name);
            if (company_found == nullptr)
            {
                fout << "Cannot find this company." << endl;
            }
            else
            {
                fout << company_found->name << "|" << company_found->profit_tax << "|" << company_found->address << endl;
            }
        }
        deleteHashTable(profit_tax_table);
        fin.close();
        fout.close();
    }
    return 0;
}

long long modPower(int a, int n, int m)
{
    long long ans = 1;
    while (n > 0)
    {
        if (n % 2  == 1)
        {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        n /= 2;
    }
    return ans;
}

Company* createCompany(const Company &company)
{
    Company *new_company = new Company;
    new_company->name = company.name;
    new_company->profit_tax = company.profit_tax;
    new_company->address = company.address;
    return new_company;
}

vector<Company> readCompanyList(string file_name)
{
    vector<Company> company_list;
    ifstream fin(file_name);
    if (!fin.is_open())
    {
        cerr << "Cannot open file." << endl;
        exit(1);
    }
    else
    {
        string line;
        getline(fin, line);
        while (getline(fin, line))
        {
            stringstream stream(line);
            string name, profit_tax, address;
            getline(stream, name, '|');
            getline(stream, profit_tax, '|');
            getline(stream, address, '|');
            company_list.push_back({name, profit_tax, address});
        }
        fin.close();
        return company_list;
    }
}

long long hashString(string company_name)
{
    long long remainder = 0;
    string s;
    if (company_name.length() <= 20)
    {
        s = company_name;
    }
    else
    {
        s = company_name.substr(company_name.length() - 20, 20);
    }
    for (int i = 0; i < s.length(); i++)
    {
        remainder += s[i] * modPower(31, i, 2000);
    }
    return remainder % 2000;
}

HashTable *createHashTable(vector<Company> company_list)
{
    HashTable *table = new HashTable;
    for (int i = 0; i < 2000; i++)
    {
        table->company_table[i] = nullptr;
        table->occupied[i] = false;
    }
    for (const Company &company : company_list)
    {
        long long position = hashString(company.name);
        while (table->occupied[position] == true)
        {
            position = (position + 1) % 2000;
        }
        table->company_table[position] = createCompany(company);
        table->occupied[position] = true;
    }
    return table;
}

void insert(HashTable *hash_table, Company company)
{
    int i = hashString(company.name);
    while (hash_table->occupied[i] == true)
    {
        i = (i + 1) % 2000;
    }
    hash_table->company_table[i] = new Company(company);
    hash_table->occupied[i] = true;
}

Company *search(HashTable *hash_table, string company_name)
{
    int i = hashString(company_name);
    while (i < 2000 && i >= 0)
    {
        if (hash_table->company_table[i]->name == company_name)
        {
            return hash_table->company_table[i];
        }
        i++;
    }
    return nullptr;
}

void deleteHashTable(HashTable *table)
{
    for (int i = 0; i < 2000; i++)
    {
        while (table->occupied[i] == false)
        {
            i++;
        }
        delete table->company_table[i];
        table->occupied[i] = false;
    }
    delete table;
}
