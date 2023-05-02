#include <memory>

#include "ISAAC.h"

ISAAC::ISAAC() : count(0), a(0), b(0), c(0), keysSet(false)
{
    for (int i = 0; i < size; ++i)
    {
        memory[i] = 0;
        results[i] = 0;
    }
}

void ISAAC::setKeys(int seed[], int seedLen)
{
    keysSet = true;
    memcpy(results, seed, seedLen);
    initialize(true);
}

void ISAAC::reset()
{
    for (int i = 0; i < size; i++)
    {
        memory[i] = 0x00;
        results[i] = 0x00;
    }

    a = b = c = 0;
}

int ISAAC::getNextValue()
{
    if (count-- == 0)
    {
        isaac();
        count = size - 1;
    }
    return results[count];
}

void ISAAC::isaac()
{
    int i, j, x, y;
    b += ++c;
    for (i = 0, j = size / 2; i < size / 2;)
    {
        x = memory[i];
        a ^= a << 13;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= (unsigned int)a >> 6;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= a << 2;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= (unsigned int)a >> 16;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;
    }

    for (j = 0; j < size / 2;)
    {
        x = memory[i];
        a ^= a << 13;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= (unsigned int)a >> 6;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= a << 2;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;

        x = memory[i];
        a ^= (unsigned int)a >> 16;
        a += memory[j++];
        memory[i] = y = memory[(x & mask) >> 2] + a + b;
        results[i++] = b = memory[((y >> sizeLog) & mask) >> 2] + x;
    }
}

void ISAAC::initialize(bool flag)
{
    int i;
    int a, b, c, d, e, f, g, h;

    a = b = c = d = e = f = g = h = ratio;

    for (i = 0; i < 4; ++i)
    {
        a ^= b << 11;
        d += a;
        b += c;
        b ^= (unsigned int)c >> 2;
        e += b;
        c += d;
        c ^= d << 8;
        f += c;
        d += e;
        d ^= (unsigned int)e >> 16;
        g += d;
        e += f;
        e ^= f << 10;
        h += e;
        f += g;
        f ^= (unsigned int)g >> 4;
        a += f;
        g += h;
        g ^= h << 8;
        b += g;
        h += a;
        h ^= (unsigned int)a >> 9;
        c += h;
        a += b;
    }

    for (i = 0; i < size; i += 8)
    {
        if (flag)
        {
            a += results[i];
            b += results[i + 1];
            c += results[i + 2];
            d += results[i + 3];
            e += results[i + 4];
            f += results[i + 5];
            g += results[i + 6];
            h += results[i + 7];
        }

        a ^= b << 11;
        d += a;
        b += c;
        b ^= (unsigned int)c >> 2;
        e += b;
        c += d;
        c ^= d << 8;
        f += c;
        d += e;
        d ^= (unsigned int)e >> 16;
        g += d;
        e += f;
        e ^= f << 10;
        h += e;
        f += g;
        f ^= (unsigned int)g >> 4;
        a += f;
        g += h;
        g ^= h << 8;
        b += g;
        h += a;
        h ^= (unsigned int)a >> 9;
        c += h;
        a += b;
        memory[i] = a;
        memory[i + 1] = b;
        memory[i + 2] = c;
        memory[i + 3] = d;
        memory[i + 4] = e;
        memory[i + 5] = f;
        memory[i + 6] = g;
        memory[i + 7] = h;
    }

    if (flag)
    {
        for (i = 0; i < size; i += 8)
        {
            a += memory[i];
            b += memory[i + 1];
            c += memory[i + 2];
            d += memory[i + 3];
            e += memory[i + 4];
            f += memory[i + 5];
            g += memory[i + 6];
            h += memory[i + 7];
            a ^= b << 11;
            d += a;
            b += c;
            b ^= (unsigned int)c >> 2;
            e += b;
            c += d;
            c ^= d << 8;
            f += c;
            d += e;
            d ^= (unsigned int)e >> 16;
            g += d;
            e += f;
            e ^= f << 10;
            h += e;
            f += g;
            f ^= (unsigned int)g >> 4;
            a += f;
            g += h;
            g ^= h << 8;
            b += g;
            h += a;
            h ^= (unsigned int)a >> 9;
            c += h;
            a += b;
            memory[i] = a;
            memory[i + 1] = b;
            memory[i + 2] = c;
            memory[i + 3] = d;
            memory[i + 4] = e;
            memory[i + 5] = f;
            memory[i + 6] = g;
            memory[i + 7] = h;
        }
    }

    isaac();
    count = size;
}

bool ISAAC::areKeysSet()
{
    return keysSet;
}
