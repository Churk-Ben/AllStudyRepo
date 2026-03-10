#pragma once
#include <string>
#include <vector>
#include <memory>

enum class ToyType
{
    Cat,
    Dog,
    Robot
};

class Toy
{
public:
    Toy(std::string name_, ToyType type_);
    virtual ~Toy() = default;
    virtual std::string name_str() const;
    virtual std::string type_str() const;
    virtual void special() const = 0;

protected:
    std::string name;
    ToyType type;
};

class CatToy : public Toy
{
public:
    CatToy(const std::string &n);
    void special() const override;
};

class DogToy : public Toy
{
public:
    DogToy(const std::string &n);
    void special() const override;
};

class RobotToy : public Toy
{
public:
    RobotToy(const std::string &n);
    void special() const override;
};

class ToyFactory
{
public:
    void add_cat(const std::string &name);
    void add_dog(const std::string &name);
    void add_robot(const std::string &name);
    void display_all() const;

private:
    std::vector<std::unique_ptr<Toy>> toys;
};
