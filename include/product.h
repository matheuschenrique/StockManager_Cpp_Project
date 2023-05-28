#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <list>
#include <chrono>

using namespace std;

enum class ProductType {
    Default = 0,
    Book,
    Electronics,
    Clothing,
    Food,
    Other
};

class Product
{
public:
    Product(int code, string &name, float cost_price);
    ~Product(){};
    virtual void calculate_total_price() const = 0;
private:
    int code;
    string name;
    int quantity;
    float cost_price;
    float sale_price;
};

class Book : public Product{
public:
    Book(int code, string &name, float cost_price);
    ~Book(){};
    void calculate_total_price()  const override;
    void set_cover_style();
private:
    int cover_style;
};

class Electronics : public Product {
public:
    Electronics(int code, string &name, float cost_price);
    ~Electronics(){ delete manufacturing_date; };
    void calculate_total_price()  const override;
    void set_manufacturing_date();
private:
    tm *manufacturing_date;
};

class Clothing : public Product {
public:
    Clothing(int code, string &name, float cost_price);
    ~Clothing(){};
    void calculate_total_price()  const override;
    void set_size();
private:
    string size;
};

class Food : public Product {
public:
    Food(int code, string &name, float cost_price);
    ~Food(){ delete expiration_date; };
    void calculate_total_price()  const override;
    void set_expiration_date();
private:
    tm *expiration_date;
};

class Other : public Product {
public:
    Other(int code, string &name, float cost_price);
    ~Other(){};
    void calculate_total_price()  const override;
};

void insert_product(list<Product*> &list);


#endif