/*
ID: borisd22
TASK: shopping
LANG: C++
*/

#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfProducts 5

ifstream fin ("shopping.in");
ofstream fout ("shopping.out");

bool debugMode = false;

struct Product
{
    int type;
    int amount;
};

struct Offer
{
    vector<Product> products;
    int price;
};

vector<Offer> offers;
vector<Product> basket;

int price[MaxNumberOfProducts];

int minPrice[MaxNumberOfProducts + 1][MaxNumberOfProducts + 1][MaxNumberOfProducts + 1][MaxNumberOfProducts + 1][MaxNumberOfProducts + 1];

void Input()
{
    int numberOfOffers;
    Read >> numberOfOffers;

    for (int i = 0; i < numberOfOffers; i++)
    {
        Offer newOffer;

        int numberOfProducts;
        Read >> numberOfProducts;

        for (int j = 0; j < numberOfProducts; j++)
        {
            Product newProduct;

            Read >> newProduct.type >> newProduct.amount;
            newOffer.products.push_back(newProduct);
        }

        Read >> newOffer.price;

        offers.push_back(newOffer);
    }

    int numberOfProducts;
    Read >> numberOfProducts;

    map<int, int> typeFilter;
    for (int i = 0; i < numberOfProducts; i++)
    {
        Product newProduct;

        Read >> newProduct.type >> newProduct.amount;
        typeFilter[newProduct.type] = i;
        newProduct.type = i;

        int newPrice;
        Read >> newPrice;
        price[i] = newPrice;

        basket.push_back(newProduct);
    }

    for (int i = offers.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < offers[i].products.size(); j++)
        {
            if (typeFilter.find(offers[i].products[j].type) == typeFilter.end())
            {
                offers.pop_back();
                break;
            }
            offers[i].products[j].type = typeFilter[offers[i].products[j].type];
        }
    }
}

void InitMinPrice()
{
    for (int a = 0; a <= MaxNumberOfProducts; a++)
    {
        for (int b = 0; b <= MaxNumberOfProducts; b++)
        {
            for (int c = 0; c <= MaxNumberOfProducts; c++)
            {
                for (int d = 0; d <= MaxNumberOfProducts; d++)
                {
                    for (int e = 0; e <= MaxNumberOfProducts; e++)
                    {
                        minPrice[a][b][c][d][e] = -1;
                    }
                }
            }
        }
    }
}

int GetMinPrice(vector<int> amounts)
{
    if (minPrice[amounts[0]][amounts[1]][amounts[2]][amounts[3]][amounts[4]] != -1)
    {
        return minPrice[amounts[0]][amounts[1]][amounts[2]][amounts[3]][amounts[4]];
    }

    int result = 1 << 30;

    for (int i = 0; i < offers.size(); i++)
    {
        vector<int> currAmounts;
        for (int i = 0; i < amounts.size(); i++)
        {
            currAmounts.push_back(amounts[i]);
        }

        bool canUse = true;
        for (int j = 0; j < offers[i].products.size(); j++)
        {
            currAmounts[offers[i].products[j].type] -= offers[i].products[j].amount;
            if (currAmounts[offers[i].products[j].type] < 0)
            {
                canUse = false;
                break;
            }
        }

        if (canUse)
        {
            result = min(result, offers[i].price + GetMinPrice(currAmounts));
        }
    }

    if (result == 1 << 30)
    {
        result = 0;
        for (int i = 0; i < MaxNumberOfProducts; i++)
        {
            result += amounts[i] * price[i];
        }
    }

    minPrice[amounts[0]][amounts[1]][amounts[2]][amounts[3]][amounts[4]] = result;
    return result;
}

int main()
{
    Input();

    if (debugMode)
    {
        Write << "Products in basket:" << endl;
        for (int i = 0; i < basket.size(); i++)
        {
            Write << basket[i].type << " " << basket[i].amount << endl;
        }
        Write << endl;

        Write << "Offers:" << endl;
        for (int i = 0; i < offers.size(); i++)
        {
            Write << "    Products in offer:" << endl;
            for (int j = 0; j < offers[i].products.size(); j++)
            {
                Write << "    " << offers[i].products[j].type << " " << offers[i].products[j].amount << endl;
            }
            Write << "    Offer price: " << offers[i].price << endl;
            Write << endl;
        }
    }

    InitMinPrice();

    Write << GetMinPrice({(basket.size() > 0) ? basket[0].amount : 0, (basket.size() > 1) ? basket[1].amount : 0,
    (basket.size() > 2) ? basket[2].amount : 0, (basket.size() > 3) ? basket[3].amount : 0, (basket.size() > 4) ? basket[4].amount : 0}) << endl;

    return 0;
}
