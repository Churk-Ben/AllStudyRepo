#pragma once
#include <string>

class MachinePet {
public:
    explicit MachinePet(const std::string& nickname_);
    virtual ~MachinePet() = default;
    const std::string& get_nickname() const { return nickname; }
    virtual std::string talk() const = 0;
private:
    std::string nickname;
};

inline MachinePet::MachinePet(const std::string& nickname_) : nickname(nickname_) {}

class PetCat : public MachinePet {
public:
    using MachinePet::MachinePet;
    std::string talk() const override { return "miao wu~"; }
};

class PetDog : public MachinePet {
public:
    using MachinePet::MachinePet;
    std::string talk() const override { return "wang wang~"; }
};
