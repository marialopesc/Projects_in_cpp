#ifndef REGISTER_H
#define REGISTER_H

class Register {

public:
    int value;

    Register();  // Constructor
    int getValue() const;  // Getter
    void setValue(int newValue);  // Setter
    void reset();  // Reset the register value
};

#endif // REGISTER_H
