#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <list>
#include <ctime>
#include <limits>
#include <algorithm>

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
    Product() = default;
    Product(int code, const std::string &name, float cost_price);
    ~Product() {};
    bool operator==(const Product &other) const;
    virtual void calculate_total_price();
    virtual void set_details();
    virtual void print() const;
    int code;
    std::string name;
    int quantity;
    float cost_price;
    float sale_price;
};

class Book : public Product{
public:
    Book(int code, const std::string &name, float cost_price);
    ~Book() {};
    void calculate_total_price() override;
    void set_details() override;
    void print()  const override;
    void set_cover_style();
private:
    int cover_style;
};

class Electronics : public Product {
public:
    Electronics(int code, const std::string &name, float cost_price);
    ~Electronics();
    void calculate_total_price() override;
    void set_details() override;
    void print()  const override;
    void set_manufacturing_date();
private:
    std::tm *manufacturing_date;
};

class Clothing : public Product {
public:
    Clothing(int code, const std::string &name, float cost_price);
    ~Clothing() {};
    void calculate_total_price() override;
    void set_details() override;
    void print()  const override;
    void set_size();
private:
    std::string size;
};

class Food : public Product {
public:
    Food(int code, const std::string &name, float cost_price);
    ~Food();
    void calculate_total_price() override;
    void set_details() override;
    void print()  const override;
    void set_expiration_date();
private:
    std::tm *expiration_date;
};

class Other : public Product {
public:
    Other(int code, const std::string &name, float cost_price);
    ~Other() {};
    void calculate_total_price() override;
    void set_details() override;
    void print()  const override;
};

void insert_date(std::tm *destiny);
void insert_product(std::list<Product*> &list);
void print_list(const std::list<Product*> &list);
Product *search_by_name(std::list<Product*> &list, const std::string &name);
Product *search_by_code(std::list<Product*> &list, const int code);
void update_stock(std::list<Product*> &list);

#endif