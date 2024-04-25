
#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <string>
class ALI;

class Instruction {
public:
    virtual ~Instruction() {}
    virtual bool execute(ALI& ali) = 0;
    virtual std::string to_string() const = 0;
protected:
    Instruction() {}
};



class DecInstruction : public Instruction {
public:
    explicit DecInstruction(const std::string& symbol);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    std::string symbol;
};





class LdiInstruction : public Instruction {
public:
    explicit LdiInstruction(int value);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    int value;
};

class StrInstruction : public Instruction {
public:
    explicit StrInstruction(const std::string& symbol);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    std::string symbol;
};

class XchInstruction : public Instruction {
public:
    XchInstruction();
    bool execute(ALI& ali) override;
    std::string to_string() const override;
};

class JmpInstruction : public Instruction {
public:
    explicit JmpInstruction(int address);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    int address;
};

class JzsInstruction : public Instruction {
public:
    explicit JzsInstruction(int address);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    int address;
};

class JvsInstruction : public Instruction {
public:
    explicit JvsInstruction(int address);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    int address;
};

class AddInstruction : public Instruction {
public:
    AddInstruction();
    bool execute(ALI& ali) override;
    std::string to_string() const override;
};

class SubInstruction : public Instruction {
public:
    SubInstruction();
    bool execute(ALI& ali) override;
    std::string to_string() const override;
};

class HltInstruction : public Instruction {
public:
    HltInstruction();
    bool execute(ALI& ali) override;
    std::string to_string() const override;
};

class LdaInstruction : public Instruction {
public:
    explicit LdaInstruction(const std::string& symbol);
    bool execute(ALI& ali) override;
    std::string to_string() const override;
private:
    std::string symbol;
};




#endif // INSTRUCTION_HPP
