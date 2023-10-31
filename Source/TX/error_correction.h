#pragma once

class Checksum
{
private:

    int data;

public:

    Checksum() : data(0) {}

    void updateData(int value);
    
};